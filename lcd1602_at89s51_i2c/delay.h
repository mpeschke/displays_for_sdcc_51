// Supported crystal oscillator/resonator speeds.
// https://en.wikipedia.org/wiki/Crystal_oscillator_frequencies
// Obs: thousand separator here is comma (,) decimal separator is a period (.)

// Planned supported frequencies:
// 32.768   KHz (allows binary divisions to 1 Hz)
//  4       MHz
// 10       MHz
// 12       MHz
// 16       MHz
// 18,432   KHz (UART clock allows integer division to common baud rates up to 230,400(x16x5) or 576,000(x16x2). Audio clock allows integer division for 48 / 96 / 192 ksps. Integer division for 50 Hz and 60 Hz.)
// 20       MHz
// 22,118.4 KHz (UART clock allows integer division to common baud rates up to 460,800(x16x3) or 921600(x8x3). Twice the 11.0592 MHz frequency.)
// 25       MHz

// Crystal Oscillator/Resonator speed. Comment/uncomment here the crystal you are using.
#define XTAL_FREQ 12000000

// Implemented frequencies:
#if XTAL_FREQ == 12000000
// Account for the 6 cycles to initialize/push the stack (initializing the us parameter and pushing the stack for the timer_delay_us function).
// Use these values to be sure the functions will take exactly DELAY_US_X microseconds.
#define DELAY_US_50     23   // CYCLES = 19 + 26    + 3 + 2
#define DELAY_US_100    73   // CYCLES = 19 + 76    + 3 + 2
#define DELAY_US_2000   1973 // CYCLES = 19 + 1976  + 3 + 2
#define DELAY_US_4200   4173 // CYCLES = 19 + 4176  + 3 + 2
#define DELAY_US_50000  49973// CYCLES = 19 + 49976 + 3 + 2

extern void timer_delay_us(unsigned int us);
extern void timer_delay_ms(unsigned int ms);

// // The 2 cycles of lcall are already accounted for.
// static void timer_delay5_us() __naked           // 2 cycle instruction (lcall	_delay5us)
// {
// 	__asm__("nop");                             // 1 cycle instruction (nop)
// 	__asm__("ret");                             // 2 cycle instruction (ret)
// }                                               // -----------------------------------
//                                                 // 5 cycles             TOTAL
#endif
