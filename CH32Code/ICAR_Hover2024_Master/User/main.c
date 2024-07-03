/*
 * main.c
 *
 *  Created on: May 20, 2024
 *      Author: ZonghuanWu
 */

#include "ch32v30x.h"

#include "huansic_chronos.h"
#include "huansic_util.h"
#include "huansic_motor.h"

void blinkLater(uint32_t ms);

uint8_t state = 1;

int main(void) {
	SystemCoreClockUpdate();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	huansic_led_init();
	huansic_chronos_init();
	huansic_motor_init();
	huansic_chronos_schedule(huansic_chronos_milliseconds() + 2000, blinkLater);
	huansic_motor_enable();
	while(1) {
//		huansic_led2_set(0);
//		huansic_delay_ms(500);
//		huansic_led2_set(1);
//		huansic_delay_ms(500);
	}
}

void blinkLater(uint32_t ms) {
	huansic_chronos_schedule(huansic_chronos_milliseconds() + 2000, blinkLater);
	huansic_led2_set(state);
	huansic_motor_set(Fan | RightProp | LeftProp, state ? 0.1 : 0.3);
	state = !state;
}
