/*
 * draw.h
 *
 *  Created on: 24/01/2021
 *      Author: VUser
 */

#include <common_types.h>


#define BLACK       (0xf)
#define WHITE       (0x0)
#define LIGHTGRAY   (0x5)
#define DARKGRAY    (0xa)

void lcd_puts_x10( uint16 x, uint16 y, uint8 color, char *s );

void lcd_putintx10( uint16 x, uint16 y, uint8 color, int32 i );
