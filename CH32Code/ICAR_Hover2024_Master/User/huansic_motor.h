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

#endif /* USER_HUANSIC_MOTOR_H_ */
