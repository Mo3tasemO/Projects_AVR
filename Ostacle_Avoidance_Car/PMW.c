/*
 * PMW.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Moatasem
 */

#include "avr/io.h"

#include "gpio.h"
#include "PMW.h"
#include "std_types.h"
#include "LCD.h"
#include <util/delay.h>


void set_servo_angle(uint16 angle)
{
    // Set the PWM pin as output
    GPIO_setupPinDirection(PORT_ID_PMW, PIN_ID_PMW, PIN_OUTPUT);

    // Reset Timer 1 counter
    TCNT1 = 0;

    // Set the PWM duty cycle
    OCR1A = angle;

    // Configure Timer 1 for Fast PWM mode (ICR1 as TOP), non-inverting mode, and prescaler of 8
    TCCR1A = (1 << WGM11) | (1 << COM1A1);
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS11);

    // Set the TOP value for Timer 1 to configure the PWM frequency (20 ms period)
    ICR1 = 19999; // For 8 MHz clock and prescaler of 8
}











