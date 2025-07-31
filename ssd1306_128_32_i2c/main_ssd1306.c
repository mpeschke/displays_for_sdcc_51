#include "ssd1306_i2cbus.h"
#include "delay.h"

static unsigned char* pMessage = "128x32 Oled Interface";

// A SSD1306 128x32 OLED display module can render four text lines using the font embbeded in the library (32 hardware lines divided by 8).
void main(void)
{
    OLED_Init();
    OLED_SetCursor(0,0);
    OLED_DisplayString(pMessage);
    delay_ms(2000);
    OLED_Clear();
    OLED_SetCursor(1,0);
    OLED_DisplayString(pMessage);
    delay_ms(2000);
    OLED_Clear();
    OLED_SetCursor(2,0);
    OLED_DisplayString(pMessage);
    delay_ms(2000);
    OLED_Clear();
    OLED_SetCursor(3,0);
    OLED_DisplayString(pMessage);
    while(1);
}