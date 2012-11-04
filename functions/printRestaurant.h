#ifndef _printRestaurant_h_
#define _printRestaurant_h_

#include "../config.h"

void loadingScreen(Sd2Card *card, Adafruit_ST7735 *tft)
{
	tft->fillScreen(ST7735_BLACK);
	tft->setTextSize(3);
	
	char string[] = "**************Loading**************";
	
	tft->setCursor(0,0);
	
	tft->println();
	
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
	
	// tft->print("*******");
	// 	tft->print("Loading");
	// 	tft->println("*******");
	
}

void printRest (Sd2Card *card, Adafruit_ST7735 *tft, RestDist *rest_dist, uint16_t page){
	
	tft->setCursor(0,0);
	tft->setTextSize(1);
	tft->setTextWrap(true);
	
	Restaurant r[PAGESIZE];
	int restIndex = 0;
	for(int i = (page - 1)*PAGESIZE; i < (page - 1)*PAGESIZE + PAGESIZE; i++)
	{
		get_restaurant(card,rest_dist[i].index, &(r[restIndex]));
		restIndex++;
	}
	
	tft->fillScreen(ST7735_RED);
	tft->setTextColor(ST7735_BLACK,ST7735_WHITE);
	
	tft->print("Page ");
	tft->print(page);
	tft->print("/");
	tft->println(TOTAL_REST/PAGESIZE);
	tft->println();
	
	if(analogRead(VERTJOY) > 1000 || analogRead(VERTJOY) < 50)
		return;
	
	restIndex = 0;
	for (int i = (page - 1)*PAGESIZE; i < (page - 1)*PAGESIZE + PAGESIZE; i++){
		//Restaurant r;
		//get_restaurant(card,rest_dist[i].index, &r);
		
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
		restIndex++;
	}
}

#endif