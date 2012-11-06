/*  CMPUT 296/114 - Assignment 2 - Due 2012-11-05

    Version 1.0 2012-11-05
    
    By: Wyatt Johnson (1230799), Andre Charest (1342401)
    
*/

#ifndef _RESTAURANT_H
#define _RESTAURANT_H


#include <SD.h>
#include "../structures.h"
#include "../mem_syms.h"

#include "map.h"

#include "../config.h"

// Get the restaurant from the SD card given a specific index as defined using the preciously stated preprocessor comamnds
void get_restaurant(Sd2Card *card, int i, Restaurant *r)
{
	static Restaurant cached_buffer[8];
	
	static uint32_t cached_start_block = 0;
	
	if(cached_start_block != RESTRAURANT_START_BLOCK + i/8)
	{
		card->readBlock(RESTRAURANT_START_BLOCK + i/8, (uint8_t *) cached_buffer);
		cached_start_block = RESTRAURANT_START_BLOCK + i/8;
	}
	
	(*r) = cached_buffer[i%8];
}

// Load the RestDist array with elements from the SD card for sorting
void loadRest(Sd2Card *card, RestDist *rest, coord_t *cursor_map, int length)
{
	int overflow;
	coord_t restCoord;
	for(int i = 0; i < length; i++)
	{
		rest[i].index = i;
		
		Restaurant rpt;
		get_restaurant(card,i,&rpt);
		restCoord.x = lon_to_x(rpt.longitude_scaled);
		restCoord.y = lat_to_y(rpt.latitude_scaled);
		
		#if DEBUG == 2
		Serial.print("x: ");
		Serial.print(restCoord.x);
		Serial.print(", y: ");
		Serial.print(restCoord.y);
		
		Serial.print(" -> VS <- ");
		Serial.print("x: ");
		Serial.print(cursor_map->x);
		Serial.print(", y: ");
		Serial.println(cursor_map->y);
		#endif
		
		rest[i].dist = manhattan_dist(cursor_map, &restCoord, &overflow);
	}
}

// Sorting algorithm adapted to work correctly using unsigned intergers within the arduino enviroment from http://en.wikipedia.org/wiki/Comb_sort, this method is a factor of 10 times faster than the propsed bubble sort algorithm that was developed in class, as tested on a 64bit mac machine running an Intel 2.9GHz i7 Processor
void comb_sort(RestDist *input, size_t size) {
	RestDist swap;
	size_t i, gap = size;
	bool swapped = false;
	
	while ((gap > 1) || swapped)
	{
		if (gap > 1)
		{
			gap = (size_t)((double)gap / 1.247330950103979);
		}
		
		swapped = false;
		
		for (i = 0; gap + i < size; ++i)
		{
			if (input[i].dist > input[i + gap].dist)
			{
				swap = input[i];
				input[i] = input[i + gap];
				input[i + gap] = swap;
				swapped = true;
			}
		}
	}
}


#endif