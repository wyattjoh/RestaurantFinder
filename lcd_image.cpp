/*
 * Routine for drawing an image patch from the SD card to the LCD display.
 */
		
#include "debug.h"

#include <Adafruit_GFX.h>		// Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>

#include "lcd_image.h"
#include "structures.h"

/* Draws the referenced image to the LCD screen.
 *
 * img				: the image to draw
 * tft				: the initialized tft struct
 * source->x, source->y		: the upper-left corner of the image patch to draw
 * dest->x, dest->y		: the upper-left corner of the screen to draw to
 * width, height : controls the size of the patch drawn.
 */
void lcd_image_draw(
	lcd_image_t *img,
	Adafruit_ST7735 *tft,
	coord_t *source,
	coord_t *dest,
	uint16_t width,
	uint16_t height
)
{
	File file;
	
	#if DEBUG
	Serial.print("Pre width: ");
	Serial.print(width);
	Serial.print(", Pre height: ");
	Serial.println(height);
	Serial.print("source->x: ");
	Serial.print(source->x);
	Serial.print(", source->y: ");
	Serial.println(source->y);
	#endif

	if(dest->x + width >= tft->width())
	{
		width = tft->width() - dest->x;
	}
	
	if(dest->y + height >= tft->height())
	{
		height = tft->height() - dest->y;
	}

	#if DEBUG
	Serial.print("dest->x: ");
	Serial.print(dest->x);
	Serial.print(", dest->y: ");
	Serial.println(dest->y);
	Serial.print("width: ");
	Serial.print(width);
	Serial.print(", height: ");
	Serial.println(height);
	Serial.println("");
	#endif

	// Open requested file on SD card if not already open
	if ((file = SD.open(img->file_name)) == NULL) {
		Serial.print("File not found:'");
		Serial.print(img->file_name);
		Serial.println('\'');
		return;	// how do we inform the caller than things went wrong?
	}

	// Setup display to receive window of pixels
	tft->setAddrWindow(dest->x, dest->y, dest->x+width-1, dest->y+height-1);

	for (uint16_t row=0; row < height; row++) {
		uint16_t pixels[width];

		uint32_t pos;

		// Seek to start of pixels to read from, need 32 bit arith for big images
		pos = ( (uint32_t) source->y + (uint32_t) row) *
						(2 * (uint32_t) img->ncols) + (uint32_t) source->x * 2;
		file.seek(pos);

		// Read row of pixels
		if (file.read((uint8_t *) pixels, 2 * width) != 2 * width) {
		Serial.println("SD Card Read Error!");
			file.close();
			return;
		}
	
		// Send pixels to display
		for (uint16_t col=0; col < width; col++) {
			uint16_t pixel = pixels[col];
		
			// pixel bytes in reverse order on card
			pixel = (pixel << 8) | (pixel >> 8);
			tft->pushColor(pixel);
		}
	}

	file.close();
}
