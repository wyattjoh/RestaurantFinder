#ifndef _printRestaurant_h_
#define _printRestaurant_h_


void printRest (Adafruit_ST7735 *tft, RestDist *rest_dist){
	
	tft.fillScreen(ST7735_BLACK);
	tft.setTextColor(ST7735_WHITE);
	
	for (int i = 0; i < 10; i++){
		Restaurant r;
		get_restaurant(rest_dist[i].index, &r);
	}
	
	tft.println("These are the 10 closests restaurants to your location.");
	
	
	for (int i = 0; i < 10; i++;){
		tft.print(i+1);
		tft.print(". ");
		if (r.rating == 1){
			tft.println(r[i].name);
			tft.print("Rating: ");
			tft.println("*");
			tft.println("=========================");
			tft.println();
		
		if (r.rating == 2){
			tft.println(r[i].name);
			tft.print("Rating: ");
			tft.println("**");
			tft.println("=========================");
			tft.println();
		}
		if (r.rating == 3){
			tft.println(r[i].name);
			tft.print("Rating: ");
			tft.println("***");
			tft.println("=========================");
			tft.println();
		}
		if (r.rating == 4){
			tft.println(r[i].name);
			tft.print("Rating: ");
			tft.println("****");
			tft.println("=========================");
			tft.println();
		}
		if (r.rating == 5){
			tft.println(r[i].name);
			tft.print("Rating: ");
			tft.println("*****");
			tft.println("=========================");
			tft.println();
		}
		if (r.rating == 6){
			tft.println(r[i].name);
			tft.print("Rating: ");
			tft.println("******");
			tft.println("=========================");
			tft.println();
		}
		if (r.rating == 7){
			tft.println(r[i].name);
			tft.print("Rating: ");
			tft.println("*******");
			tft.println("=========================");
			tft.println();
		}
		if (r.rating == 8){
			tft.println(r[i].name);
			tft.print("Rating: ");
			tft.println("********");
			tft.println("=========================");
			tft.println();
		}
		if (r.rating == 9){
			tft.println(r[i].name);
			tft.print("Rating: ");
			tft.println("*********");
			tft.println("=========================");
			tft.println();
		}
		if (r.rating == 10){
			tft.println(r[i].name);
			tft.print("Rating: ");
			tft.println("**********");
			tft.println("=========================");
			tft.println();
			
	}
	
	
	
	
}
#endif