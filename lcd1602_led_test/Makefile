all: build_hex flash_write
build_hex: sdcc_build_hex
flash_write: avrdude_flash_write
flash_verify: avrdude_flash_verify
flash_erase: avrdude_flash_erase

# Build the led test into a HEX file.
sdcc_build_hex: hd44780_pinbus.h
	sdcc hd44780_pinbus.h
	packihx hd44780_pinbus.ihx > main_lcd1602.hex

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