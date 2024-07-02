/*
 * main.c
 *
 *  Created on: May 20, 2024
 *      Author: ZonghuanWu
 */

#include "ch32v30x.h"

#include "huansic_chronos.h"
#include "huansic_util.h"
#include "OLED.h"

int main(void) {
	SystemCoreClockUpdate();
	huansic_chronos_init();
	huansic_led_init();

	huansic_led2_set(0.8);
	huansic_delay_ms(5000);
    huansic_led2_set(0.1);
	while(1) {
		huansic_delay_ms(500);
		huansic_led2_set(0.8);

		huansic_delay_ms(500);
	    huansic_led2_set(0.1);
	}
}
