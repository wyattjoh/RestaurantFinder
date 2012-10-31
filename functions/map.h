#ifndef _MAP_H
#define _MAP_H

#import "../debug.h"

// These constants are for the 2048 by 2048 map.
int16_t map_width = 2048;
int16_t map_height = 2048;
int32_t map_north = 5361858;  
int32_t map_west = -11368652;
int32_t map_south = 5340953; 
int32_t map_east = -11333496;

// These functions convert between x/y map position and lat/lon 
// (and vice versa.)
int32_t x_to_lon(int16_t x) {
    return map(x, 0, map_width, map_west, map_east);
}

int32_t y_to_lat(int16_t y) {
    return map(y, 0, map_height, map_north, map_south);
}

int16_t lon_to_x(int32_t lon) {
    return map(lon, map_west, map_east, 0, map_width);
}

int16_t lat_to_y(int32_t lat) {
    return map(lat, map_north, map_south, 0, map_height);
}

/*
* manhattan_dist
*
* from: first set of coord_t
* to: second set of coord_t
* ovr: overflow flag
*/
uint16_t manhattan_dist(coord_t *from, coord_t *to, int *ovr)
{
	uint32_t distance_x; // The x distance that we are computing
	uint32_t distance_y; // The y distance that we are computing
	uint32_t distance_total = 0; // The value of distance that we will be returning
	
	distance_x = abs(from->x - to->x); // Compute X param
	
	distance_y = abs(from->y - to->y); // Compute Y param
	
	#if DEBUG
	Serial.print("x: ");
	Serial.print(distance_x);
	Serial.print(", y: ");
	Serial.println(distance_y);
	#endif
	
	distance_total = distance_x + distance_y; // Calculate the sum
	
	// Verify if overflow occured by comparing the 32 vs 16 bit versions of the same, if an overflow occured, then it will show here.
	if(distance_total != (uint16_t) distance_total)
	{
		*ovr = 1; // Set overflow flag
		return 0; // return 0
	}
	
	return (uint16_t)distance_total; // return casted variable
}

#endif