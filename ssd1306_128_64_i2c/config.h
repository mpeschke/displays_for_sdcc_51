// Set in this file all the parameters for the circuit.

// 1) The I2C slave address of the SSD1306 I2C module.
#define ADDR        0x3c

// 2) The I2C pins.
#define SDA         P3_6
#define SCL         P3_7

// 3) The crystal oscillator/resonator speed (in Hz).
#define XTAL_FREQ   22118400
#define MCU_CYCLE   12

// 4) SSD1306 settings for an OLED 128x64 display module.

// Number of total display hardware lines. Because the font in this library has 5x8 pixel characters, this module can render eight text lines.
#define SSD1306_SET_MULTIPLEX_RATIO_VALUE   0x3F
// This value matches the OLED 128x64 display module's panel hardware layout (with remap disabled).
#define SSD1306_SET_COM_PINS_VALUE          0x12