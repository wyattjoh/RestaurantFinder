#ifndef _RESTAURANT_H
#define _RESTAURANT_H


#include <SD.h>
#include "../structures.h"
#include "../mem_syms.h"

#include "map.h"

#include "../config.h"

Restaurant buffer[8];
int bufferIndex;

void get_restaurant(Sd2Card *card,int i, Restaurant *r)
{
	if(bufferIndex != RESTRAURANT_START_BLOCK + i/8)
	{
		card->readBlock(RESTRAURANT_START_BLOCK + i/8, (uint8_t *) buffer);
		bufferIndex = RESTRAURANT_START_BLOCK + i/8;
	}
	
	(*r) = buffer[i%8];
}


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
		
		#if DEBUG
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