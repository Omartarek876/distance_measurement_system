/*
 * main.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Omar Tarek
 */

// Include necessary libraries and header files
#include "StdTypes.h"
#include "Delay.h"
#include "Dio.h"
#include "Fcpu.h"
#include "lcd.h"
#include "macros.h"
#include "Registers.h"
#include "ExtInt.h"
#include "Gie.h"
#include "Gpt.h"
#include "Interrupts.h"

/*
 *  ULTRASONIC HAS 4 PINS :
 *   - VOLTAGE
 *   - TRIGGER
 *   - ECHO
 *   - GROUND
 */

// Define the trigger and echo pins for the ultrasonic sensor
#define US_TRIGGER_PIN    DIO_PORTD, DIO_PIN0
#define US_ECHO_PIN       DIO_PORTD, DIO_PIN3

// Function to trigger the ultrasonic sensor
void US_TRIGGER(void);

// Flag to indicate if the trigger operation is done
u8 trigger_flag = 0;

// Flag to indicate if the interrupt is fired (rising or falling edge)
u8 changed_edge_flag = 0;

// Counter incremented when a time overflow occurs
u32 timer_counter = 0;

// Time remaining in the timer register
u32 remain_time = 0;

// Total time that the waves take from emission to reception
f32 total_time = 0;

// Distance measured by the ultrasonic sensor
f32 total_distance = 0;

// Interrupt handler for Timer0 overflow
void Handler_Tim0_Ovf(void)
{
	timer_counter++;
}

// Interrupt handler for external interrupt (INT1)
void exint(void)
{
	if (trigger_flag == 1)
	{
		if (changed_edge_flag == 0)
		{
			// Reset the timer counter and set the flag for rising edge
			Gpt_SetCounterValue(GPT_CHANNEL_TIM0, 0);
			timer_counter = 0;
			changed_edge_flag = 1;
		}
		else
		{
			// Calculate the elapsed time and convert it to distance
			remain_time = Gpt_GetElapsedTime(GPT_CHANNEL_TIM0);

			// Calculate the distance between the ultrasonic and the object
			total_distance = ((timer_counter * 256 + remain_time) / 466);

			// Display the distance on the LCD
			Lcd_SetCursorPosition(0, 12);
			Lcd_DisplayNumber(total_distance);

			// Delay to allow time for reading before triggering again
			_delay_ms(400);

			// Reset the counters and flags for the next measurement
			timer_counter = 0;
			changed_edge_flag = 0;
			trigger_flag = 0;
		}
	}
}

int main(void)
{
	// Initialize LCD and Timer0
	Lcd_Init(&Lcd_Configuration);
	Gpt_Init(&Gpt_Configuration);

	// Enable Timer0 overflow interrupt
	Gpt_EnableInterrupt(GPT_INT_SOURCE_TIM0_OVF);
	Gpt_SetCallback(GPT_INT_SOURCE_TIM0_OVF, Handler_Tim0_Ovf);

	// Enable external interrupt (INT1) and set sense control to on-change
	ExtInt_EnableInterrupt(EXTINT_SOURCE_INT1);
	ExtInt_SetSenseControl(EXTINT_SOURCE_INT1, EXTINT_SENSE_ON_CHANGE);
	ExtInt_SetCallback(EXTINT_SOURCE_INT1, exint);

	// Set trigger pin as output and echo pin as input with pull-up resistor
	Dio_SetPinMode(US_TRIGGER_PIN, DIO_MODE_OUTPUT);
	Dio_SetPinMode(US_ECHO_PIN, DIO_MODE_INPUT_PULLUP);

	// Enable global interrupts
	Gie_Enable();

	// Display initial message on LCD
	Lcd_DisplayString("DISTANCE = ");

	while (1)
	{
		// Trigger the ultrasonic sensor
		US_TRIGGER();
		_delay_ms(50);
	}
}

// Function to trigger the ultrasonic sensor
void US_TRIGGER(void)
{
	if (trigger_flag == 0)
	{
		// Set the trigger pin to high for 20 milliseconds
		Dio_SetPinLevel(US_TRIGGER_PIN, DIO_HIGH);
		_delay_ms(20);

		// Set the trigger pin to low
		Dio_SetPinLevel(US_TRIGGER_PIN, DIO_LOW);

		// Set the flag to indicate the trigger operation is done
		trigger_flag = 1;
	}
}
