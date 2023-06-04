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
#include "hd44780_i2cbus.h"
#include "i2c.h"

// TODO: Implement delays during R/W for fast crystal oscillators (see src/hd44780_pinbus.c)

static unsigned char _displayfn =    LCD1602_4BITMODE    | LCD1602_1LINE     | LCD1602_5x8DOTS;
static unsigned char _displayctrl =  LCD1602_DISPLAYON   | LCD1602_CURSOROFF | LCD1602_BLINKOFF;
static unsigned char _displaymode =  LCD1602_ENTRYLEFT   | LCD1602_ENTRYSHIFTDEC;
static unsigned char _backlight =    LCD1602_BACKLIGHT;

static void expanderwrite(unsigned char value)
{
    i2cstart();
    i2csendaddr();
    i2csend(value | _backlight);
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

void lcdinit(
    unsigned char displayfn,
    unsigned char displayctrl,
    unsigned char displaymode,
    unsigned char backlight
    )
{
    _displayfn = displayfn;
    _displayctrl = displayctrl;
    _displaymode = displaymode;
    _backlight = backlight;

    i2cinit();
    delay_ms(50);
    expanderwrite(_backlight);
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

    command(LCD1602_FUNCTIONSET | _displayfn);
    lcddisplayon();
    lcdclear();
    command(LCD1602_ENTRYMODESET | _displaymode);
    lcdhome();
}

void lcdclear()
{
    command(LCD1602_CLEARDISPLAY);
    delay_ms(2);
}

void lcdhome()
{
    command(LCD1602_RETURNHOME);
    delay_ms(2);
}

// Supports 2 and 4 row displays.
void lcdsetcursor(unsigned char col, unsigned char row)
{
    unsigned char addr = col;
    if(_displayfn & LCD1602_2LINE)
        switch(row) {
            case 3:
                addr += 0x54;
                break;
            case 2:
                addr += 0x14;
                break;
            case 1:
                addr += 0x40;
                break;
            default:
                break;
            }

    command(LCD1602_SETDDRAMADDR | addr);
}

void lcddisplayon()
{
    _displayctrl != LCD1602_DISPLAYON;
    command(LCD1602_DISPLAYCONTROL | _displayctrl);
}

void lcddisplayoff()
{
    _displayctrl &= ~LCD1602_DISPLAYON;
    command(LCD1602_DISPLAYCONTROL | _displayctrl);
}

void lcdcursoron()
{
    _displayctrl |= LCD1602_CURSORON;
    command(LCD1602_DISPLAYCONTROL | _displayctrl);
}

void lcdcursoroff()
{
    _displayctrl &= ~LCD1602_CURSORON;
    command(LCD1602_DISPLAYCONTROL | _displayctrl);
}

void lcdbacklighton()
{
    _backlight = LCD1602_BACKLIGHT;
    expanderwrite(0);
}

void lcdbacklightoff()
{
    _backlight = LCD1602_NOBACKLIGHT;
    expanderwrite(0);
}

void lcdwrite(unsigned char value)
{data(value);}

void lcdwritestring(unsigned char str[])
{
    unsigned int i = 0;

    while (str[i] != '\0')
    {
        data(str[i]);
        i++;
    }
}
