/*  CMPUT 296/114 - Assignment 2 - Due 2012-11-05

    Version 1.0 2012-11-05
    
    By: Wyatt Johnson (1230799), Andre Charest (1342401)
    
*/

#ifndef _config_h_
#define _config_h_

#define PAGESIZE 8

// Joystick Pin Settings
#define VERTJOY 1
#define HORZJOY 0
// Using inturupt pin 2, corrasponding to Digital Pin 21 on the MEGA 2560 Board
#define BUTTJOY 2

// SD Card defines
#define RESTRAURANT_START_BLOCK 4000000
#define BLOCK_LEN 512

// Restraunt settings
#define TOTAL_REST 1024

// Interface settings defining speed of cursor and the corection being used for the movement of the cursor
#define CURSOR_SPEED 2
#define CURSOR_RADIUS 2
#define RADIUS_CORRECTION 2

#endif