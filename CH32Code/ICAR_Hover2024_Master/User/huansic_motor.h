/*
 * huansic_motor.h
 *
 *  Created on: Jul 3, 2024
 *      Author: ZonghuanWu
 */

#ifndef USER_HUANSIC_MOTOR_H_
#define USER_HUANSIC_MOTOR_H_

#include "ch32v30x.h"

typedef enum {
	None = 0,
	Fan = 1,
	LeftProp = 2,
	RightProp = 4
} MotorName;

void huansic_motor_init(void);

void huansic_motor_set(MotorName motor, float val);

void huansic_motor_enable(void);

void huansic_motor_disable(void);

#endif /* USER_HUANSIC_MOTOR_H_ */
