#ifndef _Structures_H
#define _Structures_H

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t r;
} coord_t;

typedef struct {
  int32_t latitude_scaled;  // Scaled by 100 000
  int32_t longitude_scaled; // Scaled by 100 000
  int8_t  rating;           // Average rating, scale from 0 - 10
  char name[55];            // Always null terminated
  
} Restaurant;

#endif
