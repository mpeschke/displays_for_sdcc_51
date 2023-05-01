#include <8051.h>
#include "delay.h"

// How many oscillator periods to complete one instruction
#define MCU_CYCLE 12

// Time measurements to complete one instruction
// For a 12 MHz: 1000 ns
#define INST_CYCLE_NS (MCU_CYCLE*(1000000000/XTAL_FREQ))
// For a 12 MHz: 1 us
#define INST_CYCLE_US (MCU_CYCLE*(1000000/XTAL_FREQ))

                                                // 13 CYCLES = 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 2 + 2 + 1
inline void timer_delaystart(unsigned int count)// inline function, no lcall
{
    // clr	c                                   // 1 cycle instruction (clr	c)
    // clr	a                                   // 1 cycle instruction (clr	a)
    // subb	a,r6                                // 1 cycle instruction (subb	a,r6)
    // mov	r6,a                                // 1 cycle instruction (mov	r6,a)
    // clr	a                                   // 1 cycle instruction (clr	a)
    // subb	a,r7                                // 1 cycle instruction (subb	a,r7)
    // mov	r7,a                                // 1 cycle instruction (mov	r7,a)

    // turn off T0
	TR0 = 0;                                    // 1 cycle instruction (clr	_TR0)
	TH0 = count >> 8;                           // 2 cycle instruction (mov	_TH0,r7)
	TL0 = count & 0xff;                         // 2 cycle instruction (mov	_TL0,r6)
	// start T0
    TR0 = 1;                                    // 1 cycle instruction (setb _TR0)
}                                               // inline function, no ret

inline void timer_delaywait()                   // inline function, no lcall
{
	while (TF0 == 0);                           // 2 cycle instruction (jbc	 _TF0,00116$)
    TF0 = 0;                                    // 2 cycle instruction (sjmp 00102$)
}                                               // inline function, no ret

// The caller will have to push the stack (example for calling delayus(1000)):
// mov	dptr,#0x03e8                            // 2 cycle instruction (mov	dptr,#0x03e8)
// push	ar7                                     // 2 cycle instruction (push ar7)
// push	ar6                                     // 2 cycle instruction (push ar6

                                                // TOTAL CYCLES = 2(lcall) + 4(mov,mov) + 13(delaystart) + (DELAY_US_X CYCLES) + 3(op,op,op) + 2(ret)
void timer_delay_us(unsigned int us)
{
// mov	r6,dpl                                  // 2 cycle instruction
// mov	r7,dph                                  // 2 cycle instruction
	timer_delaystart(-us);                      // 13 cycles
	timer_delaywait();                          // us * (2 + 2)
    __asm__("nop");                             // 1 cycle instruction
    __asm__("nop");                             // 1 cycle instruction
    __asm__("nop");                             // 1 cycle instruction
}                                           // 2 cycle instruction (ret)

void timer_delay_ms(unsigned int ms)        // 2 cycle instruction (lcall _delay)
{
                                                // 2 cycle instruction (mov	r6,dpl)
                                                // 2 cycle instruction (mov	r7,dph)
	for (; ms > 0; ms--)
                                                // 2 cycle instruction (mov	a,r6)
                                                // 2 cycle instruction (orl	a,r7)
                                                // 2 cycle instruction (jz	00105$)
                                                // 2 cycle instruction (mov	dptr,#0x03e8)
		timer_delay_us(1000);                       // 2 + 2 + 2(lcall delayus) + () + 2 + 2
                                                // 2 cycle instruction (push ar7)
                                                // 2 cycle instruction (push ar6
                                                // ? delayus
                                                // 2 cycle instruction (pop	ar6)
                                                // 2 cycle instruction (pop	ar7)
}                                           // 2 cycle instruction (ret)