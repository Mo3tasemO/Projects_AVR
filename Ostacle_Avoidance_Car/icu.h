/*
 * icu.h
 *
 *  Created on: Dec 14, 2024
 *      Author: Moatasem
 */

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

uint16 Ultrasonic_readDistance(void);

void Ultrasonic_init(void);
void send_trigger_pulse(void);

#endif /* ICU_H_ */
