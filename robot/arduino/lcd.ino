
#include "lcd.h"

#ifdef LCD_ENABLED
	LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#endif


void lcd_init(void)
{
    #ifdef LCD_ENABLED
		lcd.init();
		lcd.backlight();
    #endif
}

void lcd_hello_world(void)
{
    #ifdef LCD_ENABLED

	lcd.setCursor(0,0);
	lcd.print("Hello, world!");
	lcd.setCursor(0, 1);
	lcd.print( millis() / 100);

    #endif
}

void lcd_print_top(char* woo)
{
    #ifdef LCD_ENABLED

    char buf[17];

    snprintf(
    	buf,
    	17,
    	"%s                 ",
    	woo);

	lcd.setCursor(0,0);
	lcd.print(buf);

	#endif
}

void lcd_print_bot(char* woo)
{
    #ifdef LCD_ENABLED

    char buf[17];

    snprintf(
    	buf,
    	17,
    	"%s                 ",
    	woo);

	lcd.setCursor(0,1);
	lcd.print(buf);

	#endif
}


