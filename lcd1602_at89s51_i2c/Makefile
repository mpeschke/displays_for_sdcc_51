all: build_hex flash_write
build_hex: sdcc_build_hex
flash_write: avrdude_flash_write
flash_verify: avrdude_flash_verify
flash_erase: avrdude_flash_erase

sdcc_build_hex: main_lcd1602.c
	sdcc -I . -I ../src/ -c ../src/delay.c
	sdar -rc delay.lib delay.rel
	sdcc -I . -I ../src/ -c ../src/i2c.c
	sdar -rc i2c.lib i2c.rel
	sdcc -I . -I ../src/ -c ../src/lcd1602.c
	sdar -rc lcd1602.lib lcd1602.rel
	sdcc -I . -I ../src/ main_lcd1602.c delay.lib i2c.lib lcd1602.lib -L delay.lib i2c.lib lcd1602.lib
	packihx main_lcd1602.ihx > main_lcd1602.hex

# Change here the USB port of your setup.
usb_port = /dev/ttyUSB0
avrdude_flash_write: main_lcd1602.hex
	avrdude -C ../conf/AT89S5x.conf -c stk500v1 -P $(usb_port) -p 89s51 -b 19200 -U flash:w:'$(PWD)/main_lcd1602.hex'

avrdude_flash_verify: main_lcd1602.hex
	avrdude -C ../conf/AT89S5x.conf -c stk500v1 -P $(usb_port) -p 89s51 -b 19200 -U flash:v:'$(PWD)/main_lcd1602.hex'

avrdude_flash_erase:
	avrdude -C ../conf/AT89S5x.conf -c stk500v1 -P $(usb_port) -p 89s51 -b 19200 -e

clean:
	rm -f *.lnk
	rm -f *.ihx
	rm -f *.lst
	rm -f *.map
	rm -f *.rel
	rm -f *.rst
	rm -f *.sym
	rm -f *.asm
	rm -f *.lk
	rm -f *.mem
	rm -f *.lib