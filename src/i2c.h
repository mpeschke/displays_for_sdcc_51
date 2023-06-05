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

    Original code is a bit banging that implements the I2C protocol.
    Adapted to use the delay library in this repository to accommodate different
    crystal oscillator frequencies.

    Fixed bug in the i2cread() function, adding a final 5us delay at the end
    to make it work correctly.
*/
#include "config.h"

extern void i2cinit();
extern void i2cstart();
extern void i2crestart();
extern void i2cstop();
extern void i2cack();
extern void i2cnakk();
extern unsigned char i2csendaddr();
extern unsigned char i2csend(unsigned char);
extern unsigned char i2cread();
