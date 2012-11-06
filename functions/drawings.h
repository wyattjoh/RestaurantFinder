/*  CMPUT 296/114 - Assignment 2 - Due 2012-11-05

    Version 1.0 2012-11-05
    
    By: Wyatt Johnson (1230799), Andre Charest (1342401)
    
*/

#ifndef _FUNCTIONS_DRAWINGS_H
#define _FUNCTIONS_DRAWINGS_H

#include "../config.h"


// Draws an updated cusor position based on an input of cursor_t struct
void drawCursor(Adafruit_ST7735 *tft, cursor_t *cursor)
{
	// Draws the inner color for the selection of the cursor
	tft->fillCircle(cursor->position.x, cursor->position.y, cursor->r, ST7735_CYAN);
	// Draws the outer circle for easier readability
	tft->drawCircle(cursor->position.x, cursor->position.y, cursor->r, ST7735_BLACK);
}

void moveJoystick(coord_t *JoyStick, cursor_t *cursor, Adafruit_ST7735 *tft, bool *redraw)
{
	// If the Joystick is further than 600, then it has moved far enough to justify moving the cursor
	if(JoyStick->x > 600)
	{
		// Move the cursor by one unit of CURSOR_SPEED
		cursor->position.x -= CURSOR_SPEED;
		// If 
		if(JoyStick->x > 800)
		{
			cursor->position.x -= CURSOR_SPEED + 1;
		}
		// Indicate that a redraw is required
		*redraw = 1;
	}
	// If the Joystick is smaller than 400, then it has moved far enough to justify moving the cursor
	else if(JoyStick->x < 450)
	{
		cursor->position.x += CURSOR_SPEED;
		if(JoyStick->x < 250)
		{
			cursor->position.x += CURSOR_SPEED + 1;
		}
		// Indicate that a redraw is required
		*redraw = 1;
	}
	
	// If the Joystick has moved more than 600 in the y direction, this justifys a move
	if(JoyStick->y > 600)
	{
		// Move one unit of CURSOR_SPEED in the y direction
		cursor->position.y -= CURSOR_SPEED;
		// If the Joystick has moved even more than preselected bounds, then advance further (increase the speed of the move)
		if(JoyStick->y > 800)
		{
			cursor->position.y -= CURSOR_SPEED + 1;
		}
		// Indicate that a redraw is required
		*redraw = 1;
	}
	// If the Joystick has moved more than 450 in the y direction, this justifys a move
	else if(JoyStick->y < 450)
	{
		// Move one unit of CURSOR_SPEED in the y direction
		cursor->position.y += CURSOR_SPEED;
		// If the Joystick has moved even more than preselected bounds, then advance further (increase the speed of the move)
		if(JoyStick->y < 250)
		{
			cursor->position.y += CURSOR_SPEED + 1;
		}
		// Indicate that a redraw is required
		*redraw = 1;
	}
}

bool moveCursorOff(lcd_image_t *map_image, Adafruit_ST7735 *tft, cursor_t *cursor, coord_t *m_map, bool *redraw)
{
	coord_t c_zero = {0,0};
	
	if( tft->width() - cursor->position.x <= 5 )
	{
		// Added for debug purposes to see all changes made to the map
		#if DEBUG
			Serial.print("Map At: ");
			Serial.println(m_map->x);
		#endif
		
		// Modify the map posion
		m_map->x += 84;
		cursor->position.x = 42 - cursor->r + RADIUS_CORRECTION;
		
		// Added for debug purposes to see all changes made to the map
		#if DEBUG
			Serial.print("Map Redrawn to: ");
			Serial.println(m_map->x);
		#endif
		
		// Redraw total map given new map positioning
		lcd_image_draw(map_image, tft, m_map, &c_zero, tft->width(), tft->height());
		drawCursor(tft, cursor);
		
		*redraw = 0;
	}
	else if( cursor->position.x  <= 5 )
	{
		// Added for debug purposes to see all changes made to the map
		#if DEBUG
			Serial.print("Map At: ");
			Serial.println(m_map->x);
		#endif
		
		// Modify the map posion
		m_map->x -= 84;
		cursor->position.x = 84 + RADIUS_CORRECTION;
		
		// Added for debug purposes to see all changes made to the map
		#if DEBUG
			Serial.print("Map Redrawn to: ");
			Serial.println(m_map->x);
		#endif
		
		// Redraw total map given new map positioning
		lcd_image_draw(map_image, tft, m_map, &c_zero, tft->width(), tft->height());
		drawCursor(tft, cursor);
		
		*redraw = 0;
	}
	else if( tft->height() - cursor->position.y <= 5 )
	{
		// Added for debug purposes to see all changes made to the map
		#if DEBUG
			Serial.print("Map At: ");
			Serial.println(m_map->y);
		#endif
		
		// Modify the map posion
		m_map->y += 94;
		cursor->position.y = 52 + RADIUS_CORRECTION;
		
		// Added for debug purposes to see all changes made to the map
		#if DEBUG
			Serial.print("Map Redrawn to: ");
			Serial.println(m_map->y);
		#endif
		
		// Redraw total map given new map positioning
		lcd_image_draw(map_image, tft, m_map, &c_zero, tft->width(), tft->height());
		drawCursor(tft, cursor);
		
		*redraw = 0;
	}
	else if( cursor->position.y <= 5 )
	{
		// Added for debug purposes to see all changes made to the map
		#if DEBUG
			Serial.print("Map At: ");
			Serial.println(m_map->y);
		#endif
		
		// Modify the map posion
		m_map->y -= 94;
		cursor->position.y = 94 + RADIUS_CORRECTION;
		
		// Added for debug purposes to see all changes made to the map
		#if DEBUG
			Serial.print("Map Redrawn to: ");
			Serial.println(m_map->y);
		#endif
		
		// Redraw total map given new map positioning
		lcd_image_draw(map_image, tft, m_map, &c_zero, tft->width(), tft->height());
		drawCursor(tft, cursor);
		
		*redraw = 0;
	}
}

#endif