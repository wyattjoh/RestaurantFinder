/*  CMPUT 296/114 - Assignment 2 - Due 2012-11-05

    Version 1.0 2012-11-05
    
    By: Wyatt Johnson (1230799), Andre Charest (1342401)
    
*/

#ifndef _Structures_H
#define _Structures_H

		// Defines the structure for holding coord_t information
		typedef struct {
			int16_t x;
			int16_t y;
		} coord_t;

		// Defines the structure used to store the cursor information
		typedef struct {
			coord_t position;
			uint16_t r;
		} cursor_t;

		// Defines the structure used to store the Restaurant information
		typedef struct {
		  int32_t latitude_scaled;  // Scaled by 100 000
		  int32_t longitude_scaled; // Scaled by 100 000
		  int8_t  rating;           // Average rating, scale from 0 - 10
		  char name[55];            // Always null terminated
  
		} Restaurant;

		// Defines the structure used to store the RestDist Inforamtion
		typedef struct {
			uint16_t index;
			uint16_t dist;
		} RestDist;

#endif
