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
#include "i2c.h"
#include "delay.h"

void i2cinit() __naked
{
    SDA = 1;
    delay_5us();
    SCL = 1;
    delay_5us();
    __asm__("ret");
}

void i2cstart() __naked
{
    SDA = 0;
    delay_5us();
    SCL = 0;
    delay_5us();
    __asm__("ret");
}

void i2crestart() __naked
{
    SDA = 1;
    delay_5us();
    SCL = 1;
    delay_5us();
    SDA = 0;
    delay_5us();
    SCL = 0;
    delay_5us();
    __asm__("ret");
}

void i2cstop() __naked
{
    SCL = 0;
    delay_5us();
    SDA = 0;
    delay_5us();
    SCL = 1;
    delay_5us();
    SDA = 1;
    delay_5us();
    __asm__("ret");
}

void i2cack() __naked
{
    SDA = 0;
    delay_5us();
    SCL = 1;
    delay_5us();
    SCL = 0;
    delay_5us();
    SDA = 1;
    delay_5us();
    __asm__("ret");
}

void i2cnak() __naked
{
    SDA = 1;
    delay_5us();
    SCL = 1;
    delay_5us();
    SCL = 0;
    delay_5us();
    SDA = 1;
    delay_5us();
    __asm__("ret");
}

unsigned char i2csendaddr()
{return i2csend(ADDR << 1);}

unsigned char i2csend(unsigned char data)
{
    unsigned char i;

    for (i = 0; i < 8; i++) {
        if (data & 0x80)
            SDA = 1;
        else
            SDA = 0;

        delay_5us();
        SCL = 1;
        delay_5us();
        SCL = 0;
        delay_5us();

        data <<= 1;
    }

    SDA = 1;
    delay_5us();
    SCL = 1;
    i = SDA;
    delay_5us();
    SCL = 0;
    delay_5us();

    return i;
}

unsigned char i2cread()
{
    unsigned char i;
    unsigned char data = 0;

    for (i = 0; i < 8; i++) {
        data <<= 1;
        data |= SDA;
        SCL = 1;
        delay_5us();
        SCL = 0;
        delay_5us();
    }
    return data;
}
