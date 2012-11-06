/*  CMPUT 296/114 - Assignment 2 - Due 2012-11-05

    Version 1.0 2012-11-05
    
    By: Wyatt Johnson (1230799), Andre Charest (1342401)
    
*/

#ifndef _printRestaurant_h_
#define _printRestaurant_h_

#include "../config.h"

void loadingScreen(Sd2Card *card, Adafruit_ST7735 *tft)
{
	// Fill the screen with the color (background)
	tft->fillScreen(ST7735_BLACK);
	// Modify the text size
	tft->setTextSize(3);
	
	char string[] = "**************Loading**************";
	
	// Move the cursor to the first starting pixel
	tft->setCursor(0,0);
	
	tft->println();
	
	// Gradient for screen text
	int color = ST7735_GREEN;
	bool direction = 0;
	for(int i = 0; i < sizeof(string); i++)
	{
		if(color + 1 >= 0x0FFF)
			direction = 1;
		else if(direction == 1 && color - 1 <= ST7735_GREEN)
			direction = 0;
			
		if(direction)
			color += 1;
		else
			color -= 1;
			
		tft->setTextColor(color);
		tft->print(string[i]);
	}
	
}

void printRest (Sd2Card *card, Adafruit_ST7735 *tft, RestDist *rest_dist, uint16_t page){
	
	// Move the cursor to the first starting pixel
	tft->setCursor(0,0);
	// Modify the text size
	tft->setTextSize(1);
	tft->setTextWrap(true);
	
	// Load restaurant data from the SD card given a RestDist array struct
	Restaurant r[PAGESIZE];
	int restIndex = 0;
	for(int i = (page - 1)*PAGESIZE; i < (page - 1)*PAGESIZE + PAGESIZE; i++)
	{
		get_restaurant(card,rest_dist[i].index, &(r[restIndex]));
		restIndex++;
	}
	
	// Fill the screen with the color (background)
	tft->fillScreen(ST7735_RED);
	tft->setTextColor(ST7735_BLACK,ST7735_WHITE);
	
	// Print page number
	tft->print("Page ");
	tft->print(page);
	tft->print("/");
	tft->println(TOTAL_REST/PAGESIZE);
	tft->println();
	
	// Check if scrolling fast, if so dont display all the content, just the page inforamtion as displayed above
	if(analogRead(VERTJOY) > 1000 || analogRead(VERTJOY) < 50)
		return;
	
	// Print the restraunt information
	restIndex = 0;
	for (int i = (page - 1)*PAGESIZE; i < (page - 1)*PAGESIZE + PAGESIZE; i++){
		tft->setTextColor(ST7735_WHITE,ST7735_BLACK);
		tft->print(i+1);
		tft->print(".");
		tft->setTextColor(ST7735_WHITE);
		tft->print(" ");
		tft->print(r[restIndex].name);
		tft->print(" ");
		
		tft->setTextColor(ST7735_YELLOW,ST7735_BLACK);
		
		for(int i = 0; i<r[restIndex].rating/2; i++)
			tft->print("*");
		
		tft->println();
		
		#if DEBUG
		Serial.print("Rest Mapped Coord:");
		Serial.print(r[restIndex].longitude_scaled);
		Serial.print(", ");
		Serial.println(r[restIndex].latitude_scaled);
		#endif
		
		restIndex++;
	}
}

#endif