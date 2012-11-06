/*  CMPUT 296/114 - Assignment 2 - Due 2012-11-05

    Version 1.0 2012-11-05
    
    By: Wyatt Johnson (1230799), Andre Charest (1342401)
    
*/

#include "debug.h"

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>

#include "lcd_image.h"
#include "structures.h"
#include "functions/drawings.h"
#include "functions/restaurant.h"
#include "functions/map.h"
#include "functions/printRestaurant.h"
#include "config.h"

// standard U of A library settings, assuming Atmel Mega SPI pins
#define SD_CS    5  // Chip select line for SD card
#define TFT_CS   6  // Chip select line for TFT display
#define TFT_DC   7  // Data/command line for TFT
#define TFT_RST  8  // Reset line for TFT (or connect to +5V)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
 
Sd2Card card;

lcd_image_t map_image = { "yeg-big.lcd", 2048, 2048 };

coord_t c_zero = {0,0}; // A zero vector to be used by functions needing to add an element to the 0,0 position
coord_t iniJoy; // Initial position of joystick, to be read in setup
coord_t JoyStick; // Current position of joystick
coord_t OldJoyStick; // Old postion of joystick, to be used to compare with old stick
coord_t cursor_map; // position of the cursor on the map (0->2048,0->2048)
coord_t map_tile; // Position of the map tile to redraw 
coord_t map_redraw; // Position of the maps tile to redraw 

cursor_t cursor = {0,0}; // Initial cursor position 

coord_t m_map = {928,898}; // Initial position of the map

volatile bool state = 0; // State as set by the joystick inturupt pin as defined in the config.h file

/*
*	buttonPress
*
*	@arguments: none
*	@return: none
*	@function: modify volitile state variable from a hardware inturupt
*
*/

void buttonPress()
{
	state = !state;
}

void setup(void) {
	Serial.begin(9600);
  
	// set buttonPin to INPUT and 
	// turn on internal pull up resistor 
	pinMode(BUTTJOY, INPUT);
	digitalWrite(BUTTJOY, HIGH);
  
	// establish interrupts on joystick button falling (when the button is initially pushed)
	// NOTE: BUTTJOY has been set up with a debounced circut
	attachInterrupt(BUTTJOY, buttonPress, FALLING);
  
	// Define the cursor radius to be 2 pixles
	cursor.r = CURSOR_RADIUS;
  
	// Read initial joystick position
	iniJoy.x = analogRead(HORZJOY);
	iniJoy.y = analogRead(VERTJOY);
  
	// If your TFT's plastic wrap has a Red Tab, use the following:
	tft.initR(INITR_REDTAB);   // initialize a ST7735R chip, red tab
	// If your TFT's plastic wrap has a Green Tab, use the following:
	//tft.initR(INITR_GREENTAB); // initialize a ST7735R chip, green tab

	#if DEBUG
	Serial.print("Initializing SD card...");
	#endif
	if (!SD.begin(SD_CS))
	{
		Serial.println("failed!");
		return;
	}
	#if DEBUG
	Serial.println("OK!");
	#endif
  
	// test out reading blocks from the SD card
	if (!card.init(SPI_HALF_SPEED, SD_CS)) {
		#if DEBUG
		Serial.println("Raw SD Initialization has failed");
		#endif
		while (1) {};  // Just wait, stuff exploded.
	}
	
	// Centers map on pre-selected coord
	m_map.x = m_map.x - tft.width()/2;
	m_map.y = m_map.y - tft.height()/2;
	
	// Places cursor in the center of the screen
	cursor.position.x = (int) tft.width()/2.;
	cursor.position.y = (int) tft.height()/2.;

	// clear to blue
	tft.fillScreen(tft.Color565(137, 207, 240));
	
	// Added for debug purposes
	#if DEBUG
	Serial.print("TFT Height: ");
	Serial.print( tft.height() );
	Serial.print(", TFT Width: ");
	Serial.println( tft.width() );
	#endif

	// Draw initial screen
	lcd_image_draw(&map_image, &tft, &m_map, &c_zero,  tft.width(), tft.height());
	// Draw Cursor on map
	drawCursor(&tft, &cursor);
}

void loop() {
	// Calculate the position of the map that we are redrawing behind the old cursor
	map_redraw.x = cursor.position.x - cursor.r;
	map_redraw.y = cursor.position.y - cursor.r;
	
	// Calculate the source tile of the map that we are palcing
	map_tile.x = map_redraw.x + m_map.x;
	map_tile.y = map_redraw.y + m_map.y;
	
	// Ini redraw parameter, will be used to indicate that a redraw is required
	bool redraw = 0;
	
	// Analog read into joystick parameters
	JoyStick.x = analogRead(HORZJOY);
	JoyStick.y = analogRead(VERTJOY);
	
	// If there is a deviation from the initial readings, this indicates that there might be some redrawing required
	if(iniJoy.x != JoyStick.x || iniJoy.y != JoyStick.y)
	{
		moveJoystick(&JoyStick, &cursor, &tft, &redraw);
		moveCursorOff(&map_image, &tft, &cursor, &m_map, &redraw);
	}
	
	if(state)
	{
		// Determine the location of the cursor on the image file
		cursor_map.x = m_map.x + cursor.position.x;
		cursor_map.y = m_map.y + cursor.position.y;
		
		#if DEBUG
		Serial.print("Mapped (X,Y) Coord> (");
		Serial.print(cursor_map.x);
		Serial.print(",");
		Serial.print(cursor_map.y);
		Serial.println(")");
		
		Serial.print("Mapped (LON,LAT) Coord> (");
		Serial.print(x_to_lon(cursor_map.x));
		Serial.print(",");
		Serial.print(y_to_lat(cursor_map.y));
		Serial.println(")");
		#endif
		
		// Sets our page number to be zero
		uint16_t page = 1;
		
		// Prints loading screen to tft while loading and sorting get processed
		loadingScreen(&card, &tft);
		
		// Define RestDist structure for holding the distances from the different rest's
		// NOTE: As rest is an array, it does not need to be dereferenced
		RestDist rest[TOTAL_REST];
		
		// Load the restraunts from the SD card into the restdist array
		loadRest(&card, rest, &cursor_map, TOTAL_REST);
		
		// Use the comb sort algorithm to sort the list of restraunts
		comb_sort(rest, TOTAL_REST);
		
		// Print page 1 of the sorted list
		printRest(&card, &tft, rest, page);
		
		while(state)
		{
			// Reads the current position of the joystick
			JoyStick.y = analogRead(VERTJOY);
			
			/*
			* Checks whether the joystick has moved (selecting other restraunts from list) and prints the restraunt according the page passed, with added support for checking that you do not go over the amount of restraunts that were loaded.
			*/
			if(JoyStick.y > 800 && page != 1)
			{
				printRest(&card, &tft, rest, --page);
			}
			else if(JoyStick.y < 250 && (page - 1)*PAGESIZE + PAGESIZE < TOTAL_REST)
			{
				printRest(&card, &tft, rest, ++page);
			}
		}
		
		// Redraw the map
		lcd_image_draw(&map_image, &tft, &m_map, &c_zero, tft.width(), tft.height());
		
		// Redraw the cursor in its old position
		drawCursor(&tft, &cursor);
		
		// Set the redraw parameter to be zero
		redraw = 0;
	}
	
	/*
	*	This will redraw the map over the old cursor, and redraw the cursor in the new position if the cursor has been indicated as moved.
	*/
	
	if(redraw == 1)
	{
		// Included for DEBUG purposes
		#if DEBUG
		// Determine the location of the cursor on the image file
		cursor_map.x = m_map.x + cursor.position.x;
		cursor_map.y = m_map.y + cursor.position.y;
		
		Serial.print("Mapped (X,Y) Coord> (");
		Serial.print(cursor_map.x);
		Serial.print(",");
		Serial.print(cursor_map.y);
		Serial.println(")");
		
		Serial.print("Mapped (LON,LAT) Coord> (");
		Serial.print(x_to_lon(cursor_map.x));
		Serial.print(",");
		Serial.print(y_to_lat(cursor_map.y));
		Serial.println(")");
		#endif
		
		
		// Redraw the map in front of the old cursor
		lcd_image_draw(&map_image, &tft, &map_tile, &map_redraw, cursor.r*2+1, cursor.r*2+1);
		
		// Draw the new cursor at the new position
		drawCursor(&tft, &cursor);
	}
}
