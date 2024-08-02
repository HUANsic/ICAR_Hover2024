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
#include "usart2.h"

int main(void) {
	SystemCoreClockUpdate();
	chronos_init();
	USART2_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
	while(1) {
		huansic_delay_ms(100);
	}
}
