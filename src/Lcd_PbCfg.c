/*
 * Lcd_PbCfg.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Omar Tarek
 */
#include "Lcd.h"

Lcd_ControlType Lcd_Configuration = {
    .display = LCD_DISPLAY_ON,
    .lines   = LCD_LINES_2,
    .font    = LCD_FONT_5X7,
    .cusror  = LCD_CURSOR_ON_BLINK_ON
};


