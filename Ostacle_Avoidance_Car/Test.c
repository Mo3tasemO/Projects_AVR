/*
 * Test.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Moatasem
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "LCD.h"
#include "icu.h"
#include "std_types.h"
#include "gpio.h"
#include "common_macros.h"
#include "PMW.h"
// Define pins
#define TRIG PB0
#define ECHO PB1
#define SERVO PB2
#define IN1 PC0
#define IN2 PC1
#define IN3 PC2
#define IN4 PC3




// Initialize motor driver
void init_motor_driver() {
	DDRC |= (1 << IN1) | (1 << IN2) | (1 << IN3) | (1 << IN4);  // Set motor driver pins as outputs
}

// Motor control functions
void move_forward() {
	PORTC |= (1 << IN1);
	PORTC &= ~(1 << IN2);
	PORTC |= (1 << IN3);
	PORTC &= ~(1 << IN4);
}

void move_backward() {
	PORTC &= ~(1 << IN1);
	PORTC |= (1 << IN2);
	PORTC &= ~(1 << IN3);
	PORTC |= (1 << IN4);
}

void turn_left() {
	PORTC &= ~(1 << IN1);
	PORTC &= ~(1 << IN2);
	PORTC |= (1 << IN3);
	PORTC &= ~(1 << IN4);
}

void turn_right() {
	PORTC |= (1 << IN1);
	PORTC &= ~(1 << IN2);
	PORTC &= ~(1 << IN3);
	PORTC &= ~(1 << IN4);
}

void stop_car() {
	PORTC &= ~(1 << IN1);
	PORTC &= ~(1 << IN2);
	PORTC &= ~(1 << IN3);
	PORTC &= ~(1 << IN4);
}


/*************Global values **********************/
uint16_t left_distance;
uint16_t right_distance;
uint16_t distance = 0;

int main() {

	SREG = (1<<7);
	init_motor_driver();
	Ultrasonic_init();
	LCD_init();

	set_servo_angle(1500);  // Center the servo initially

	LCD_clearScreen();
	while (1) {

		distance = Ultrasonic_readDistance();
		move_forward();


		set_servo_angle(1500);

		if (distance < 15) {  // Obstacle detected
			stop_car();
			LCD_clearScreen();
			LCD_displayString("car is stoped");
			_delay_ms(1500);
			LCD_clearScreen();


			set_servo_angle(1000);  // Scan left
			LCD_displayString("Scan left");
			left_distance = Ultrasonic_readDistance();

			_delay_ms(1500);

			set_servo_angle(2000);  // Scan right
			right_distance = Ultrasonic_readDistance();
			LCD_clearScreen();
			LCD_displayString("Scan  right");

			_delay_ms(1500);
			set_servo_angle(1500);  // Center servo again
			LCD_clearScreen();

			if (left_distance > right_distance) {
				turn_left();
				LCD_clearScreen();
				LCD_displayString("turn_left");
				_delay_ms(500);
			} else {
				turn_right();
				LCD_clearScreen();
				LCD_displayString("turn_right");
				_delay_ms(500);
			}
		} else {
			move_forward();
		}
	}
}
