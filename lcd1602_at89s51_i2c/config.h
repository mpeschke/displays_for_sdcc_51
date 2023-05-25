// Set in this file all the parameters for the circuit.

// 1) The I2C slave address of the LCD1602 I2C module.
#define	ADDR        0x3F

// 2) The I2C pins.
#define	SDA	        P3_6
#define	SCL	        P3_7

// 3) The crystal oscillator/resonator speed (in Hz).
#define XTAL_FREQ   22118400
#define MCU_CYCLE   12