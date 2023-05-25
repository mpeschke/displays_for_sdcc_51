/*
MIT License
Copyright (c) 2019 Ken Yap
Permission is hereby granted, free of charge, to any person obtaining a copy of this 
software and associated documentation files (the "Software"), to deal in the Software 
without restriction, including without limitation the rights to use, copy, modify, merge, 
publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons 
to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <8051.h>
#include "delay.h"
#include "lcd1602.h"
#include "i2c.h"

// TODO: Implement parameters for displayfn, displayctrl, displaymode
// TODO: Implement delays during R/W for fast crystal oscillators (see src/hd44780_pinbus.c)

#define COLS 16
#define ROWS 2

static unsigned char displayfn = 	LCD1602_4BITMODE 	| LCD1602_1LINE 	| LCD1602_5x8DOTS;
static unsigned char displayctrl = 	LCD1602_DISPLAYON 	| LCD1602_CURSOROFF | LCD1602_BLINKOFF;
static unsigned char displaymode = 	LCD1602_ENTRYLEFT 	| LCD1602_ENTRYSHIFTDEC;
static unsigned char backlight = 	LCD1602_BACKLIGHT;

static void expanderwrite(unsigned char value)
{
	i2cstart();
	i2csendaddr();
	i2csend(value | backlight);
	i2cstop();
}

inline void pulseenable(unsigned char value)
{
	expanderwrite(value | En);
	expanderwrite(value | ~En);
}

static void write4bits(unsigned char value)
{
	expanderwrite(value);
	pulseenable(value);
}

static void command(unsigned char value)
{
	write4bits(value & 0xf0);
	write4bits((value << 4) & 0xf0);
}

static void data(unsigned char value)
{
	write4bits((value & 0xf0) | Rs);
	write4bits(((value << 4) & 0xf0) | Rs);
}

void lcd1602init()
{
	i2cinit();
	delay_ms(50);
	expanderwrite(backlight);
	delay_ms(50);
	write4bits(0x03 << 4);
	// > 4.1 ms
	delay_ms(5);
	write4bits(0x03 << 4);
	// > 4.1 ms
	delay_ms(5);
	write4bits(0x03 << 4);
	// > 150 us
	DELAY_10_TIMES_US(16); // 160 us
	write4bits(0x02 << 4);

	displayfn = LCD1602_4BITMODE | LCD1602_2LINE | LCD1602_5x8DOTS;
	command(LCD1602_FUNCTIONSET | displayfn);
	displayctrl = LCD1602_DISPLAYON | LCD1602_CURSOROFF | LCD1602_BLINKOFF;
	lcd1602displayon();
	lcd1602clear();
	displaymode = LCD1602_ENTRYLEFT | LCD1602_ENTRYSHIFTDEC;
	command(LCD1602_ENTRYMODESET | displaymode);
	lcd1602home();
}

void lcd1602clear()
{
	command(LCD1602_CLEARDISPLAY);
	delay_ms(2);
}

void lcd1602home()
{
	command(LCD1602_RETURNHOME);
	delay_ms(2);
}

// hardcoded for 16x2
void lcd1602setcursor(unsigned char col, unsigned char row)
{command(LCD1602_SETDDRAMADDR | col + row * 0x40);}

void lcd1602displayon()
{
	displayctrl != LCD1602_DISPLAYON;
	command(LCD1602_DISPLAYCONTROL | displayctrl);
}

void lcd1602displayoff()
{
	displayctrl &= ~LCD1602_DISPLAYON;
	command(LCD1602_DISPLAYCONTROL | displayctrl);
}

void lcd1602cursoron()
{
	displayctrl |= LCD1602_CURSORON;
	command(LCD1602_DISPLAYCONTROL | displayctrl);
}

void lcd1602cursoroff()
{
	displayctrl &= ~LCD1602_CURSORON;
	command(LCD1602_DISPLAYCONTROL | displayctrl);
}

void lcd1602backlighton()
{
	backlight = LCD1602_BACKLIGHT;
	expanderwrite(0);
}

void lcd1602backlightoff()
{
	backlight = LCD1602_NOBACKLIGHT;
	expanderwrite(0);
}

void lcd1602write(unsigned char value)
{data(value);}

void lcd1602writestring(unsigned char str[])
{
	unsigned int i = 0;

	while (str[i] != '\0')
    {
        data(str[i]);
        i++;
    }
}
