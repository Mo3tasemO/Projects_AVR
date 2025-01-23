/*
 * PMW.h
 *
 *  Created on: Dec 14, 2024
 *      Author: Moatasem
 */

#ifndef PMW_H_
#define PMW_H_


#define PORT_ID_PMW    PORTD_ID

#define PIN_ID_PMW     PIN5_ID

#define MAXMAM_DUTY_CYCLE   255


/*Description :
 * setup the timer 0 for PMW signal on OC0
 * input is duty cycle for 0 : 100
 * return none
 * */
void set_servo_angle(uint16 angle);

#endif /* PMW_H_ */
