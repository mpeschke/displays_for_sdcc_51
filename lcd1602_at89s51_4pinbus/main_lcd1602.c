#include "hd44780_pinbus.h"

void main() {
    int i = 32767;

    disp_start(2,16);

    disp_put_cur(0,0);
    disp_printf("THIS IS LINE 01");
    disp_put_cur(1,0);
    disp_printf("%s      ", "Int test: ");
    while(i--)
    {
        lcd_wait_512t(255);
        disp_put_cur(1,10);
        disp_printf("%s", "      ");
        disp_put_cur(1,10);
        disp_printf("%d", i);
    };

    while(1);
}