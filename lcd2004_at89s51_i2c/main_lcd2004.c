#include "delay.h"
#include "hd44780_i2cbus.h"

void main(void)
{
    lcdinit(
        LCD1602_4BITMODE  | LCD1602_2LINE           | LCD1602_5x8DOTS,
        LCD1602_DISPLAYON | LCD1602_CURSOROFF       | LCD1602_BLINKOFF,
        LCD1602_ENTRYLEFT | LCD1602_ENTRYSHIFTDEC,
        LCD1602_BACKLIGHT
        );
    while(1)
    {
        lcdwritestring("ABCDEFGHIJKLMNOPQRST");
        lcdsetcursor(0, 1);
        lcdwritestring("UVXWYZabcdefghijklmn");
        delay_ms(2000);
        lcdsetcursor(0, 2);
        lcdwritestring("opqrstuvxwyz12345678");
        lcdsetcursor(0, 3);
        lcdwritestring("90.,-><+/@&!%'[]{}_|");
        delay_ms(2000);
        lcdclear();
        for(unsigned int i = 0; i<20; i++)
        {
            lcdwrite('.');
            delay_ms(250);
        }
        lcdclear();
    }
}