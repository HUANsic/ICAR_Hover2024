/*
 * main.c
 *
 *  Created on: May 20, 2024
 *      Author: ZonghuanWu
 */

#include "ch32v20x.h"
#include "huansic_config.h"
#include "huansic_util.h"
#include "usart2.h"
#include "opt.h"

int main(void) {
	SystemCoreClockUpdate();
	Delay_Init();
	USART2_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
    huansic_led_init();
    opt_init();
	while(1) {
		Delay_Ms(2000);
		huansic_led1_turn();
        Serial_SendSensorData(get_opt_data());
        Serial_SendByteData(62);
	}
}
