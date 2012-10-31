#ifndef _Structures_H
#define _Structures_H

typedef struct {
	int16_t x;
	int16_t y;
} coord_t;

typedef struct {
	coord_t position;
	uint16_t r;
} cursor_t;

typedef struct {
  int32_t latitude_scaled;  // Scaled by 100 000
  int32_t longitude_scaled; // Scaled by 100 000
  int8_t  rating;           // Average rating, scale from 0 - 10
  char name[55];            // Always null terminated
  
} Restaurant;

typedef struct {
	uint16_t index;
	uint16_t dist;
} RestDist;

#endif
