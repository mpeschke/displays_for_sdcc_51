all: build_hex flash
build_hex: sdcc_build_hex
flash: avrdude_flash

sdcc_build_hex: main_lcd1602.c
	sdcc -c ../src/hd44780.c
	sdar -rc hd44780.lib hd44780.rel
	sdcc main_lcd1602.c hd44780.lib -L hd44780.lib
	packihx main_lcd1602.ihx > main_lcd1602.hex

# Change here the USB port of your setup.
usb_port = /dev/cu.usbserial-RCBB_4OK6P3
avrdude_flash: main_lcd1602.hex
	avrdude -C ../conf/AT89S5x.conf -c stk500v1 -P $(usb_port) -p 89s51 -b 19200 -U flash:w:'$(PWD)/main_lcd1602.hex'

clean:
	rm -f *.ihx *.lnk *.lst *.map *.rel *.rst *.sym *.asm *.lk *.mem *.lib