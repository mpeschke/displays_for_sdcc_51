#define	ADDR 0x3F
#define	SDA	 P3_6
#define	SCL	 P3_7

extern void i2cinit();
extern void i2cstart();
extern void i2crestart();
extern void i2cstop();
extern void i2cack();
extern void i2cnakk();
extern unsigned char i2csendaddr();
extern unsigned char i2csend(unsigned char);
extern unsigned char i2cread();
