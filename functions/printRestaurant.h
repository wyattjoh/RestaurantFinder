#ifndef _printRestaurant_h_
#define _printRestaurant_h_

void loadingScreen(Sd2Card *card, Adafruit_ST7735 *tft)
{
	tft->fillScreen(ST7735_WHITE);
	tft->setTextColor(ST7735_RED);
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

void printRest (Sd2Card *card, Adafruit_ST7735 *tft, RestDist *rest_dist, int page = 1){
	
	tft->setCursor(0,0);
	tft->setTextSize(1);
	
	tft->fillScreen(ST7735_BLACK);
	
	for (int i = (page - 1)*10; i < (page - 1)*10 + 10; i++){
		Restaurant r;
		get_restaurant(card,rest_dist[i].index, &r);
		
		tft->setTextColor(ST7735_YELLOW);
		tft->print(i+1);
		tft->print(". ");
		tft->setTextColor(ST7735_WHITE);
		tft->print(r.name);
		tft->print(" ");
		
		tft->setTextColor(ST7735_CYAN);
		
		for(int i = 0; i<r.rating/2; i++)
			tft->print("*");
		
		tft->println();
	}
}

#endif