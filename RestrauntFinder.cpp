/* Simple Image Drawing
 *
 * Draws an image to the screen.  The image is stored in "parrot.lcd" on 
 * the SD card.  The image file contains only raw pixel byte-pairs.
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

// standard U of A library settings, assuming Atmel Mega SPI pins
#define SD_CS    5  // Chip select line for SD card
#define TFT_CS   6  // Chip select line for TFT display
#define TFT_DC   7  // Data/command line for TFT
#define TFT_RST  8  // Reset line for TFT (or connect to +5V)

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
 
Sd2Card card;

lcd_image_t map_image = { "yeg-big.lcd", 2048, 2048 };

// Joystick Settings
#define VERTJOY 1
#define HORZJOY 0
#define BUTTJOY 9

// Zoom Potentialometer Settings
#define ZOOMPOT 2

coord_t c_zero = {0,0};
coord_t iniJoy;
coord_t JoyStick;
coord_t OldJoyStick;
cursor_t cursor = {64,80};
coord_t cursor_map;
coord_t map_tile;
coord_t map_redraw;

coord_t m_map = {1000,1000};

void setup(void) {
  Serial.begin(9600);
  
  JoyStick.x = analogRead(HORZJOY);
  JoyStick.y = analogRead(VERTJOY);
  
  cursor.r = map(analogRead(ZOOMPOT),0,1023,3,15);
  
  iniJoy.x = JoyStick.x;
  iniJoy.y = JoyStick.y;
  
  // If your TFT's plastic wrap has a Red Tab, use the following:
  tft.initR(INITR_REDTAB);   // initialize a ST7735R chip, red tab
  // If your TFT's plastic wrap has a Green Tab, use the following:
  //tft.initR(INITR_GREENTAB); // initialize a ST7735R chip, green tab

  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
    return;
  }
  Serial.println("OK!");
  
// test out reading blocks from the SD card

    if (!card.init(SPI_HALF_SPEED, SD_CS)) {
        Serial.println("Raw SD Initialization has failed");
        while (1) {};  // Just wait, stuff exploded.
        }

  // clear to blue
  tft.fillScreen(tft.Color565(137, 207, 240));
  
  #if DEBUG
  Serial.print("TFT Height: ");
  Serial.print( tft.height() );
  Serial.print(", TFT Width: ");
  Serial.println( tft.width() );
  #endif
  
  lcd_image_draw(&map_image, &tft, &m_map, &c_zero,  tft.width(), tft.height());
  drawCursor(&tft, &cursor);
  
  Restaurant r;
  get_restaurant(&card,0,&r);
  
  Serial.println(r.name);
}

void loop() {
	
	map_redraw.x = cursor.position.x - cursor.r;
	map_redraw.y = cursor.position.y - cursor.r;
	
	map_tile.x = map_redraw.x + m_map.x;
	map_tile.y = map_redraw.y + m_map.y;
	
	bool redraw = 0;
	
	OldJoyStick = JoyStick;
	
	
    JoyStick.x = analogRead(HORZJOY);
    JoyStick.y = analogRead(VERTJOY);
	
	#if ZOOM
	if(cursor.r != map(analogRead(ZOOMPOT),0,1023,3,15))
	{
		lcd_image_draw(&map_image, &tft, &map_tile, &map_redraw, cursor.r*2+1, cursor.r*2+1);
		
		cursor.r = map(analogRead(ZOOMPOT),0,1023,3,15);
		
		drawCursor(&tft, &cursor);
		
		#if DEBUG
		Serial.print("Zoom Analog Level: ");
		Serial.println(cursor.r);
		#endif
	}
	#endif
	
	int cursor_speed = 2;
	
	if(iniJoy.x != JoyStick.x || iniJoy.y != JoyStick.y)
	{
		moveJoystick(&JoyStick, &cursor, &tft, cursor_speed, &redraw);
		moveCursorOff(&map_image, &tft, &cursor, &m_map, &redraw);
	}
	

	if(redraw == 1)
	{
		#if DEBUG
		Serial.print("cursor.x: ");
		Serial.print(cursor.position.x);
		Serial.print(", cursor.y: ");
		Serial.println(cursor.position.y);
		Serial.print("Cursor_map: ");
		Serial.print(cursor_map.x, DEC);
		Serial.print(", ");
		Serial.println(cursor_map.y, DEC);
		#endif
		
		cursor_map.x = map_tile.x + cursor.position.x;
		cursor_map.y = map_tile.y + cursor.position.y;
		
		lcd_image_draw(&map_image, &tft, &map_tile, &map_redraw, cursor.r*2+1, cursor.r*2+1);
		drawCursor(&tft, &cursor);
	}
}
