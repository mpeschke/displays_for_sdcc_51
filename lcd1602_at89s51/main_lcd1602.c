#include <mcs51/8051.h> 
#include "../inc/hd44780.h"

void main() {
    int i = 32767;

    disp_start(2,16);

    disp_put_cur(0,0);
    disp_printf("THIS IS LINE 01");
    disp_put_cur(1,0);
    disp_printf("Int test: %d", i);
    disp_cur_on();
    while(1);
}