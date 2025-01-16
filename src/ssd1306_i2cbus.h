#include "config.h"

#define SSD1306_DISPLAY_OFF                  0xAE
#define SSD1306_SET_DISPLAY_CLOCK_DIV_RATIO  0xD5
#define SSD1306_SET_MULTIPLEX_RATIO          0xA8
#define SSD1306_SET_DISPLAY_OFFSET           0xD3
#define SSD1306_SET_START_LINE               0x40
#define SSD1306_CHARGE_PUMP                  0x8D
#define SSD1306_MEMORY_ADDR_MODE             0x20
#define SSD1306_SET_SEGMENT_REMAP            0xA0
#define SSD1306_COM_SCAN_DIR_DEC             0xC8
#define SSD1306_SET_COM_PINS                 0xDA
#define SSD1306_SET_CONTRAST_CONTROL         0x81
#define SSD1306_SET_PRECHARGE_PERIOD         0xD9
#define SSD1306_SET_VCOM_DESELECT            0xDB
#define SSD1306_DISPLAY_ALL_ON_RESUME        0xA4
#define SSD1306_NORMAL_DISPLAY               0xA6
#define SSD1306_DISPLAY_ON                   0xAF
#define SSD1306_SET_COLUMN_ADDR              0x21
#define SSD1306_SET_PAGE_ADDR                0x22
#define SSD1306_DATA_CONTINUE                0x40
#define SSD1306_COMMAND                      0x00
#define C_OledLastLine_U8                    0x07u

extern void OLED_Init(void);
extern void OLED_DisplayChar(unsigned char ch);
extern void OLED_DisplayString(unsigned char *);
extern void OLED_Clear(void);
extern void OLED_SetCursor(unsigned char lineNumber,unsigned char cursorPosition);
extern void OLED_GoToNextLine(void);
