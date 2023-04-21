// This is a helper test to compute/validate the accuracy of the MCU delay functions. Making a LED flicker at 1 second interval.
#include <mcs51/8051.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

#define LED P1_5

void lcd_wait_512t(uint8_t t)
{
    uint8_t i;
    while(--t) {
        i = 255;
        while(--i);
    }
    return;
}

void main() {
    while(1)
    {
        LED = 0;
        lcd_wait_512t(255); // 456.963 ms
        lcd_wait_512t(255); // 456.963 ms
        lcd_wait_512t(48); //   86.019 ms (86.074 ms to complete 1000 ms)
        LED = 1;
        lcd_wait_512t(255); // 456.963 ms
        lcd_wait_512t(255); // 456.963 ms
        lcd_wait_512t(48); //   86.019 ms (86.074 ms to complete 1000 ms)
    };
}

// Counting the instructions in the _lcd_wait_512t function gives us the following formula, based on a machine cycle of 12 oscillator periods:
// (12 + t*(12+12+12+24+24) + t*255*(12+12+12+24+24) + 24)/MCU_CYCLE

// ;	hd44780_pinbus.h:10: void lcd_wait_512t(uint8_t t)
// ;	-----------------------------------------
// ;	 function lcd_wait_512t
// ;	-----------------------------------------
// _lcd_wait_512t:
// 	mov	r7,dpl      12 oscillator periods
// ;	hd44780_pinbus.h:13: while(--t) {
// 00104$:          ( * t)
// 	mov	a,r7        12 oscillator periods
// 	dec	a           12 oscillator periods
// 	mov	r7,a        12 oscillator periods
// 	jz	00106$      24 oscillator periods
// ;	hd44780_pinbus.h:14: i = 255;
// 	mov	r6,#0xff    24 oscillator periods
// ;	hd44780_pinbus.h:15: while(--i);
// 00101$:          ( * 255)
// 	mov	a,r6        12 oscillator periods
// 	dec	a           12 oscillator periods
// 	mov	r6,a        12 oscillator periods
// 	jz	00104$      24 oscillator periods
// 	sjmp	00101$  24 oscillator periods
// 00106$:
// ;	hd44780_pinbus.h:17: return;
// ;	hd44780_pinbus.h:18: }
// 	ret             24 oscillator periods

// For a 12 MHz crystal oscillator on a microcontroller with a machine cycle of 12 oscillator periods:
// Example for t=48.030691964 (48):
// (12 + 48*(84) + 48*255*(84) + 24)/12 = 1032228/12 = 86019 ns = 86.019 ms
