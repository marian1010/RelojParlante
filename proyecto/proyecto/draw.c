#include <lcd.h>
#include <s3c44b0x.h>

#include "draw.h"

extern uint8 font[];

void lcd_putchar_x10( uint16 x, uint16 y, uint8 color, char ch )
{
    uint8 line, row;
    uint8 *bitmap;

    bitmap = font + ch*16;
    for( line=0; line<16*8; line++ )
        for( row=0; row<8*8; row++ )
            if( bitmap[line/8] & (0x80 >> row/8) ){
            	 lcd_putpixel( x+row, y+line, color );
            }
            else{
    			lcd_putpixel( x+row, y+line, WHITE);
            }

}


void lcd_puts_x10( uint16 x, uint16 y, uint8 color, char *s )
{
	uint32 i=0;
    while(*(s+i)!='\0'){
    	lcd_putchar_x10(x,y,color,*(s+i));
		x+=8*10;
		i++;
	}

}

void lcd_putintx10( uint16 x, uint16 y, uint8 color, int32 i )
{
	char buf[10 + 1];
	char *p = buf + 10;
	uint8 num=0;
	*p = '\0';
	if(i==0){
		*--p=('0'+num);
	}
    while(i){
		num=i%10;
		*--p=('0'+num);
		i=i/10;
	}
	lcd_puts_x10(x,y,color,p);
}
