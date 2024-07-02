/*
 * main.c
 *
 *  Created on: May 20, 2024
 *      Author: ZonghuanWu
 */

#include "ch32v20x.h"

#include "huansic_config.h"
#include "huansic_irq.h"
#include "huansic_chronos.h"

int main(void) {
	SystemCoreClockUpdate();
	huansic_chronos_init();

	while(1) {
		huansic_delay_ms(100);
	}
}
