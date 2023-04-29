#include "lcd1602.h"


void main(void)
{
	lcd1602init();
	lcd1602write('A');
	
	while(1);
}