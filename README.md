# HD44780 library for sdcc (8051 Intel-based Microntrollers)

This library provides support for HITACHI HD44780 based character LCDs (0801, 0802, 1601, 1602, 2004) and some compatible VFD variants like Noritake itron CU20045 (Light adjust available), with fast IO operation

+ Suitable for 8051 based MCUs with various crystals and instruction cycles (1T, 6T, 12T) as AUTOMATIC delay calculation is available

+ 4bit or 8bit M68 and i80 interface supported

+ Easy-to-use formattable print function `disp_printf(format, ...)` similar to normal `printf(format, ...)`

+ Build and deploy automation using make and avrdude with an AVRISP to flash the hex file into the microcontroller.

+ Three types of functions operating at different levels. It's recommended to use the high level functions. Look them up at the end of `hd44780_pinbus.h`


This library is designed for SDCC only and microcontrollers based on Intel 8051. Current tests use Atmel AT89S5x microcontroller family.  

# Build and Deploy

All projects in this repository assume:  

> 1. Code can be compiled by sdcc into an hex file.
>
> 2. Hex file can be flashed to a microcontroller flash memory, if they are supported by avrdude in the [conf/AT89S5x.conf](conf/AT89S5x.conf) file.

## Test with LCD1602 and Atmel AT89S51 - connecting 4 pins to the LCD

4bit M68 interface with R/#W in [lcd1602_at89s51_4pinbus](lcd1602_at89s51_4pinbus/)  

> Usage:
>
> 1. Get your hands on a AVRISP capable of flashing hex files to a AT89S51 microcontroller. There are several tutorials out there, the most popular are the ones using [Arduino](https://www.youtube.com/watch?v=Pdi-q-bamlI).
>
> 2. [Place the microcontroller on the AVRISP board](https://www.youtube.com/watch?v=isPWwbw70vc) (follow instructions until 02:47).  
>
> 3. Edit [lcd1602_at89s51_4pinbus/Makefile](lcd1602_at89s51_4pinbus/Makefile) to have your USB port in the `usb_port` variable.
>
> 4. From a terminal, run the commands:
> 
> 5. cd lcd1602_at89s51_4pinbus/
>
> 6. make

The make command will 1) build the source code and 2) flash the HEX file into the microcontroller's flash memory.  

Remove the microcontroller from the AVRISP board and place it in its circuit (see circuit's picture and diagram below)  

![](images/lcd1602_at89s51_4pinbus.jpg)  

![](images/lcd1602_at89s51_4pinbus_schematic.png)  

## Test with LCD2004

N/A, will post an update when I find one of these for testing. You can see the original test in the [original repository](https://github.com/apachiww/hd44780_for_sdcc_51).  

## Test with Noritake CU20045-UW VFD

N/A, will post an update when I find one of these for testing. You can see the original test in the [original repository](https://github.com/apachiww/hd44780_for_sdcc_51).  

## Test with PT6314 based VFM202MDAR2 VFD 

N/A, will post an update when I find one of these for testing. You can see the original test in the [original repository](https://github.com/apachiww/hd44780_for_sdcc_51).  
