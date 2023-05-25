#include <at89x51.h>
#include "delay.h"
#include "config.h"

#define __CYCLES_PER_MS 1000.0/(1000000.0/(XTAL_FREQ/MCU_CYCLE))

// -------- A function with more instructions is fitter for faster crystals ------
#if (XTAL_FREQ/MCU_CYCLE)   < 100000
  // Divide by 11 achieved experimentally for XTAL_FREQ = 1 MHz
  #define CALL_DELAY      delay_x10_cycles(__CYCLES_PER_MS/11)
#elif (XTAL_FREQ/MCU_CYCLE) < 2000000
  #define CALL_DELAY      delay_x10_cycles(__CYCLES_PER_MS/10)
#else
  #define CALL_DELAY      delay_x100_cycles(__CYCLES_PER_MS/100)
#endif
// ----------------------------------------------------------------

#pragma disable_warning 85

void delay_x10_cycles(uint8_t x10cycles)        // 2 cycles (lcall)
/* Total cycles = 2 + 2 + 1 + 1 + 2 + (x10cycles-1)*(8 + 2) + 2 =
                = 10 + 10*(x10cycles-1) = 10 (1 + x10cycles - 1) =
                = 10 * x10cycles                                                  */
{
   __asm
           mov  r7,dpl                          // 2 cycles
           dec  r7                              // 1 cycle
           mov  a, r7                           // 1 cycle
           jz   end_delay_x10_cycles            // 2 cycles
    loop_delay_x10_cycles:                      // ---------------------------------------------
           mov  r6,#3                           // 1 cycle   //                        //
    loop_delay_10_cycles:                                    //                        //
           djnz r6,loop_delay_10_cycles         // 2 cycles  //                        //
           nop                                  // 1 cycle   //--> 1+2*3+1 = 8 cycles. //
           djnz r7,loop_delay_x10_cycles        // 2 cycles                            // --> 8 + 2 = 10 cycles.
    end_delay_x10_cycles:                       // ---------------------------------------------
	__endasm;
}                                               // 2 cycles (ret)

// ----------------------------------------------------------------
void delay_x100_cycles(uint8_t x100cycles)      // 2 cycles (lcall)
{
   __asm
           mov  r7,dpl                          // 2 cycles
           dec  r7                              // 1 cycle
           mov  a, r7                           // 1 cycle
           mov  r6,#44                          // 1 cycle
    loop_delay_x100_cycles_init:
           djnz r6,loop_delay_x100_cycles_init  // 2x44 = 88 cycles
           nop                                  // 1 cycle
           jz   end_delay_x100_cycles           // 2 cycles
    loop_delay_x100_cycles:                     // ---------------------------------------------
           mov  r5,#48                          // 1 cycle   //                        //
    loop_delay_100_cycles:                                   //                        //
           djnz r5,loop_delay_100_cycles        // 2 cycles  //                        //
           nop                                  // 1 cycle   //--> 1+2*48+1 = 98 cycles//
           djnz r7,loop_delay_x100_cycles       // 2 cycles                            // --> 98 + 2 = 100 cycles
    end_delay_x100_cycles:                      // ---------------------------------------------
	__endasm;
                                                // 2 cycles (ret)
}

// ----------------------------------------------------------------
void delay_ms(uint16_t ms)
{
//    while(ms--)
//        CALL_DELAY;
//  The while loops were optimized using asm blocks, stripping
//  unnecessary instructions to produce an exact delay time.
__asm
        mov     r3,dpl
        mov     r4,dph
delay_ms_lib_loop:
        dec     r3
        cjne    r3,#0xff,delay_ms_lib_seguir
        dec     r4
delay_ms_lib_seguir:
        mov     a,r3
        orl     a,r4
        jz      delay_ms_lib_fin
__endasm;

        CALL_DELAY;

__asm
        sjmp    delay_ms_lib_loop
delay_ms_lib_fin:
__endasm;
}

// Number of additional cycles for this function to take 5us to run: (2+1+X+2)*(1000000÷(CLOCK÷12)=5
// (5+X)*(1000000÷(CLOCK÷12))=5
// Examples:
// (12       MHz) = (5+X)*(1000000÷(12000000÷12))=5 -> 5+X=5                      -> X=0
// (16       MHz) = (5+X)*(1000000÷(16000000÷12))=5 -> 3.75+0.75X=5               -> X=1.666666667 (round to 2)
// (18432000  Hz) = (5+X)*(1000000÷(18432000÷12))=5 -> 3.255208333+0.651041667X=5 -> X=2.679999999 (round to 3)
// (22118400  Hz) = (5+X)*(1000000÷(22118400÷12))=5 -> 2.71267361+0.542534722X=5  -> X=4.216000004 (round to 5)
// (25       MHz) = (5+X)*(1000000÷(25000000÷12))=5 -> 2.4+0.48X=5                -> X=5.416666667 (round to 6)
void delay_5us() __naked       // 2 cycle instruction (lcall _delay5us)
{
__asm__("nop");                // 1 cycle instruction (nop)
#if XTAL_FREQ == 16000000      // X=1.666666667 (round to 2)
__asm__("nop");                // 1 cycle instruction
__asm__("nop");                // 1 cycle instruction
#endif
#if XTAL_FREQ == 18432000      // X=2.679999999 (round to 3)
__asm__("nop");                // 1 cycle instruction
__asm__("nop");                // 1 cycle instruction
__asm__("nop");                // 1 cycle instruction
#endif
#if XTAL_FREQ == 22118400      // X=4.216000004 (round to 5)
__asm__("nop");                // 1 cycle instruction
__asm__("nop");                // 1 cycle instruction
__asm__("nop");                // 1 cycle instruction
__asm__("nop");                // 1 cycle instruction
__asm__("nop");                // 1 cycle instruction
#endif
#if XTAL_FREQ == 25000000      // X=5.416666667 (round to 6)
__asm__("nop");                // 1 cycle instruction
__asm__("nop");                // 1 cycle instruction
__asm__("nop");                // 1 cycle instruction
__asm__("nop");                // 1 cycle instruction
__asm__("nop");                // 1 cycle instruction
__asm__("nop");                // 1 cycle instruction
#endif
__asm__("ret");                // 2 cycle instruction (ret)
}
                               // -----------------------------------
                               // 5+X cycles             TOTAL