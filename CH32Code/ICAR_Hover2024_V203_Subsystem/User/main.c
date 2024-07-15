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
#include "OLED.h"

int main(void) {
	SystemCoreClockUpdate();
	Delay_Init();
	USART2_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());
    huansic_led_init();
//    opt_init();
    OLED_Init();
	while(1) {
		Delay_Ms(2000);
//		huansic_led1_turn();
//		refresh_opt_data();
//        Serial_SendByteData(get_opt_data().front_interval / 10);
//        if(USART2_GetRxFlag()){
//            Serial_SendSensorData(get_opt_data());
//            reset_opt_data();
//        }
//	    OLED_ShowString(0, 0, "asdf", OLED_8X16);
//	    OLED_ShowNum(0, 16, USART2_GetRxData(), 3, OLED_8X16);
//	    OLED_Update();
	}
}
