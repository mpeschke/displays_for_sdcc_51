/*
    Delay code copied from this repository: https://github.com/retiredfeline/8051-tuner/
    on 2023-05-24. MIT license:

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    Adapted to use the delay library in this repository to accommodate different
    crystal oscillator frequencies and the i2c protocol library.

    Fixed functions lcd1602backlighton() and lcd1602backlightoff(), they were reversed.
*/

// TODO: rename this file (and all references) to hd44780_i2c_pcf8574a.h.

// commands
#define LCD1602_CLEARDISPLAY    0x01
#define LCD1602_RETURNHOME      0x02
#define LCD1602_ENTRYMODESET    0x04
#define LCD1602_DISPLAYCONTROL  0x08

#define LCD1602_CURSORSHIFT     0x10
#define LCD1602_FUNCTIONSET     0x20
#define LCD1602_SETCGRAMADDR    0x40
#define LCD1602_SETDDRAMADDR    0x80

// flags for display entry mode
#define LCD1602_ENTRYRIGHT      0x00
#define LCD1602_ENTRYLEFT       0x02

#define LCD1602_ENTRYSHIFTDEC   0x00
#define LCD1602_ENTRYSHIFTINC   0x01

// flags for display on/off control
#define LCD1602_DISPLAYOFF      0x00
#define LCD1602_DISPLAYON       0x04

#define LCD1602_CURSOROFF       0x00
#define LCD1602_CURSORON        0x02

#define LCD1602_BLINKOFF        0x00
#define LCD1602_BLINKON         0x01

// flags for display/cursor shift
#define LCD1602_DISPLAYMOVE     0x08
#define LCD1602_CURSORMOVE      0x00
#define LCD1602_MOVERIGHT       0x04
#define LCD1602_MOVELEFT        0x00

// flags for function set
#define LCD1602_4BITMODE        0x00
#define LCD1602_8BITMODE        0x10

#define LCD1602_1LINE           0x00
#define LCD1602_2LINE           0x08

#define LCD1602_5x8DOTS         0x00
#define LCD1602_5x10DOTS        0x04

// flags for backlight control
#define LCD1602_NOBACKLIGHT     0x00
#define LCD1602_BACKLIGHT       0x08

#define Rs                      0x01 // Register select bit
#define Rw                      0x02 // Read/Write bit
#define En                      0x04 // Enable bit

extern void lcd1602init();
extern void lcd1602clear();
extern void lcd1602home();
extern void lcd1602setcursor(unsigned char col, unsigned char row);
extern void lcd1602displayon();
extern void lcd1602displayoff();
extern void lcd1602cursoron();
extern void lcd1602cursoroff();
extern void lcd1602write(unsigned char c);
extern void lcd1602writestring(unsigned char str[]);
