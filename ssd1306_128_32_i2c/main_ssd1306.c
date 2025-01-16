#include "ssd1306_i2cbus.h"
#include "delay.h"

static unsigned char* pMessage = "Oled Interface";

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