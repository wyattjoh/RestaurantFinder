#ifndef _FUNCTIONS_DRAWINGS_H
#define _FUNCTIONS_DRAWINGS_H

void drawCursor(Adafruit_ST7735 *tft, coord_t *cursor)
{
	tft->drawPixel(cursor->x, cursor->y, tft->Color565(0x00, 0x00, 0x00));
	//tft->drawCircle(cursor->x, cursor->y, cursor->r-1, tft->Color565(0,0,0));
	//tft->drawCircle(cursor->x, cursor->y, cursor->r, tft->Color565(137, 207, 240));
	tft->drawCircle(cursor->x, cursor->y, cursor->r, tft->Color565(0, 0, 0));
}

void moveJoystick(coord_t *JoyStick, coord_t *cursor, Adafruit_ST7735 *tft, uint16_t cursor_speed, bool *redraw)
{
	if(JoyStick->x > 600)
	{
		cursor->x -= cursor_speed;
		if(JoyStick->x > 800)
		{
			cursor->x -= cursor_speed + 1;
		}
		*redraw = 1;
	}
	else if(JoyStick->x < 450)
	{
		cursor->x += cursor_speed;
		if(JoyStick->x < 250)
		{
			cursor->x += cursor_speed + 1;
		}
		*redraw = 1;
	}
	
	if(JoyStick->y > 600)
	{
		cursor->y -= cursor_speed;
		if(JoyStick->y > 800)
		{
			cursor->y -= cursor_speed + 1;
		}
		*redraw = 1;
	}
	else if(JoyStick->y < 450)
	{
		cursor->y += cursor_speed;
		if(JoyStick->y < 250)
		{
			cursor->y += cursor_speed + 1;
		}
		*redraw = 1;
	}
}

bool moveCursorOff(lcd_image_t *map_image, Adafruit_ST7735 *tft, coord_t *cursor, coord_t *m_map, bool *redraw)
{
	coord_t c_zero = {0,0};
	
	if( tft->width() - cursor->x < cursor->r )
	{
		#if DEBUG
			Serial.print("Map At: ");
			Serial.println(m_map->x);
		#endif
		
		m_map->x += 84;
		cursor->x = 42 - cursor->r + 2;
		
		#if DEBUG
			Serial.print("Map Redrawn to: ");
			Serial.println(m_map->x);
		#endif
		
		lcd_image_draw(map_image, tft, m_map, &c_zero, tft->width(), tft->height());
		drawCursor(tft, cursor);
		
		*redraw = 0;
	}
	else if( cursor->x < cursor->r )
	{
		#if DEBUG
			Serial.print("Map At: ");
			Serial.println(m_map->x);
		#endif
		
		m_map->x -= 84;
		cursor->x = 84 + cursor->r + 2;
		
		#if DEBUG
			Serial.print("Map Redrawn to: ");
			Serial.println(m_map->x);
		#endif
		
		lcd_image_draw(map_image, tft, m_map, &c_zero, tft->width(), tft->height());
		drawCursor(tft, cursor);
		
		*redraw = 0;
	}
	else if( tft->height() - cursor->y < cursor->r )
	{
		#if DEBUG
			Serial.print("Map At: ");
			Serial.println(m_map->y);
		#endif
		
		m_map->y += 94;
		cursor->y = 52 - cursor->r + 2;
		
		#if DEBUG
			Serial.print("Map Redrawn to: ");
			Serial.println(m_map->y);
		#endif
		
		lcd_image_draw(map_image, tft, m_map, &c_zero, tft->width(), tft->height());
		drawCursor(tft, cursor);
		
		*redraw = 0;
	}
	else if( cursor->y < cursor->r )
	{
		#if DEBUG
			Serial.print("Map At: ");
			Serial.println(m_map->y);
		#endif
		
		m_map->y -= 94;
		cursor->y = 94 + cursor->r + 2;
		
		#if DEBUG
			Serial.print("Map Redrawn to: ");
			Serial.println(m_map->y);
		#endif
		
		lcd_image_draw(map_image, tft, m_map, &c_zero, tft->width(), tft->height());
		drawCursor(tft, cursor);
		
		*redraw = 0;
	}
}

#endif