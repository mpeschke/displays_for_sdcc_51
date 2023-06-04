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
        lcdwritestring("ABCDEFGHIJKLMNOP");
        lcdsetcursor(0, 1);
        lcdwritestring("QRSTUVXWYZabcdef");
        delay_ms(2000);
        lcdhome();
        lcdwritestring("ghijklmnopqrstuv");
        lcdsetcursor(0, 1);
        lcdwritestring("xwyz1234567890.,");
        delay_ms(2000);
        lcdhome();
        lcdwritestring("-></\\|!?()=+@#$&");
        lcdsetcursor(0, 1);
        lcdwritestring("*_");
        delay_ms(2000);
        for(unsigned int i = 0; i<14; i++)
        {
            lcdwrite('.');
            delay_ms(250);
        }
        lcdhome();
    }
}