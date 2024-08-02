/*
 * huansic_util.h
 *
 *  Created on: May 21, 2024
 *      Author: ZonghuanWu
 */

#ifndef USER_HUANSIC_UTIL_H_
#define USER_HUANSIC_UTIL_H_

#include "ch32v30x.h"

typedef enum{
	LED_None = 0,
	LED1 = 0x02,
	LED2 = 0x04,
	LED3 = 0x08,
	LED4 = 0x10,
	LED5 = 0x20,
	LED6 = 0x40,
	LED7 = 0x80,
} LED_Typedef;

void util_init(void);

void util_led_set(LED_Typedef led, float bri);

#endif /* USER_HUANSIC_UTIL_H_ */
