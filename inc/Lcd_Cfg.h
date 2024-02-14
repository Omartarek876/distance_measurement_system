/*
 * main.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Omar Tarek
 */

#ifndef INC_LCD_CFG_H_
#define INC_LCD_CFG_H_

#include "Dio.h"

#define LCD_MODE_4_BIT  1
#define LCD_MODE_8_BIT  2


/**
 * Options:
 *  LCD_MODE_4_BIT
 *  LCD_MODE_8_BIT
*/
#define LCD_MODE    LCD_MODE_8_BIT

/* LCD Control Pins */
#define LCD_PIN_RS  DIO_PORTB,DIO_PIN1
#define LCD_PIN_RW  DIO_PORTB,DIO_PIN2
#define LCD_PIN_EN  DIO_PORTB,DIO_PIN3
/* LCD Data Pins */
#if (LCD_MODE == LCD_MODE_8_BIT)
#define LCD_PIN_D0  DIO_PORTA,DIO_PIN0
#define LCD_PIN_D1  DIO_PORTA,DIO_PIN1
#define LCD_PIN_D2  DIO_PORTA,DIO_PIN2
#define LCD_PIN_D3  DIO_PORTA,DIO_PIN3
#endif
#define LCD_PIN_D4  DIO_PORTA,DIO_PIN4
#define LCD_PIN_D5  DIO_PORTA,DIO_PIN5
#define LCD_PIN_D6  DIO_PORTA,DIO_PIN6
#define LCD_PIN_D7  DIO_PORTA,DIO_PIN7

#endif /* INC_LCD_CFG_H_ */
