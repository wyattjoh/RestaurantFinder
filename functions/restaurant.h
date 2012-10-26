#ifndef _RESTAURANT_H
#define _RESTAURANT_H


#include <SD.h>
#include "../structures.h"
#include "../mem_syms.h"

#define RESTRAURANT_START_BLOCK 4000000
#define BLOCK_LEN 512

void get_restaurant(Sd2Card *card, int i, Restaurant *r)
{
	
	Restaurant buffer[BLOCK_LEN/sizeof(Restaurant)];
	card->readBlock(RESTRAURANT_START_BLOCK + i/8, (uint8_t *)buffer);
	
	*r = buffer[i%8];
	
}

#endif