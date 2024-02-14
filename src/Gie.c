/*
 * main.c
 *
 *  Created on: Feb 14, 2024
 *      Author: Omar Tarek
 */


#include "StdTypes.h"
#include "Macros.h"
#include "Registers.h"
#include "Gie.h"

void Gie_Enable  (void)
{
    SET_BIT(SREG, 7);
}

void Gie_Disable (void)
{
    CLR_BIT(SREG, 7);
}
