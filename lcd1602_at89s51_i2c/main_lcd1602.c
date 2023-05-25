#include "delay.h"
#include "lcd1602.h"

void main(void)
{
	lcd1602init();
	while(1)
	{
		lcd1602writestring("ABCDEFGHIJKLMNOP");
		lcd1602setcursor(0, 1);
		lcd1602writestring("QRSTUVXWYZabcdef");
		delay_ms(2000);
		lcd1602home();
		lcd1602writestring("ghijklmnopqrstuv");
		lcd1602setcursor(0, 1);
		lcd1602writestring("xwyz1234567890.,");
		delay_ms(2000);
		lcd1602home();
		lcd1602writestring("-></\\|!?()=+@#$&");
		lcd1602setcursor(0, 1);
		lcd1602writestring("*_");
		delay_ms(2000);
		for(unsigned int i = 0; i<14; i++)
		{
			lcd1602write('.');
			delay_ms(250);
		}
		lcd1602home();
	}
}