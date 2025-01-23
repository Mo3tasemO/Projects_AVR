/*
 * ICU.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Moatasem
 */

#include "avr/io.h"
#include "ICU.h"
#include "std_types.h"
#include "common_macros.h"
#include <avr/interrupt.h> /* For ICU ISR */
#include <util/delay.h>


#define TRIGGER_PIN  PB5 // Define the trigger pin
#define ECHO_PIN     PD2 // Echo pin (INT0)

volatile uint16_t timer_overflow_count = 0;
volatile uint16_t pulse_width = 0 ;
volatile uint8 flage = 0;


void Ultrasonic_init(void)
{
	// Set Trigger Pin as Output
	DDRB |= (1 << TRIGGER_PIN);
	// Set Echo Pin as Input
	DDRD &= ~(1 << ECHO_PIN);

	// Enable External Interrupt on INT0 (Rising Edge initially)
	MCUCR |= (1 << ISC00) | (1 << ISC01); // Rising edge on INT0
	GICR |= (1 << INT0);                 // Enable INT0

	// Initialize Timer 0 in normal mode with a prescaler of 8
	TCCR0 = (1 << CS01); // Prescaler = 8
	TCNT0 = 0;           // Clear Timer 0
	TIMSK |= (1 << TOIE0); // Enable Timer 0 overflow interrupt

}

void send_trigger_pulse(void)
{
	PORTB |= (1 << TRIGGER_PIN);  // Set Trigger Pin High
	_delay_us(10);                // Wait 10 µs
	PORTB &= ~(1 << TRIGGER_PIN); // Set Trigger Pin Low
}


uint16 Ultrasonic_readDistance(void)
{
	uint16 dis;
	send_trigger_pulse();

	while (flage !=1){
	dis = (pulse_width/58) ;
	}
	return dis;
}


ISR(INT0_vect)
{
	static uint8_t edge = 0;
	if (edge == 0) // Rising edge detected
	{
		TCNT0 = 0;               // Clear Timer 0
		timer_overflow_count = 0; // Reset overflow count
		MCUCR &= ~(1 << ISC00);  // Switch to falling edge
		edge = 1;
		flage = 0;

	}
	else // Falling edge detected
	{
		pulse_width = (timer_overflow_count * 256 + TCNT0) ; // Calculate pulse width
		flage = 1;
		MCUCR |= (1 << ISC00);  // Switch back to rising edge
		edge = 0;
	}
}

ISR(TIMER0_OVF_vect)
{
	timer_overflow_count++; // Increment overflow count
}


