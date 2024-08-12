/*
 * main.c
 *
 *  Created on: May 20, 2024
 *      Author: ZonghuanWu
 */

#include "ch32v30x.h"

#include "huansic_chronos.h"
#include "huansic_util.h"
#include "huansic_comm.h"
#include "huansic_motor.h"
//#include "dvp.h"
//#include "ov.h"
//#include "usart2.h"

uint8_t state;
float dc = 0;
void blinkLater(uint32_t ms);
int main(void) {
	SystemCoreClockUpdate();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//USART_Printf_Init(115200);
//    USART2_Init(115200);
//    printf("SystemClk:%d\r\n",SystemCoreClock);
//    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());

//    huansic_subsys_init();

	util_init();
	huansic_motor_init();
	huansic_motor_enable();
	huansic_chronos_init();
	huansic_chronos_schedule(huansic_chronos_milliseconds() + 500, blinkLater);

//	huansic_led2_turn();
//    huansic_delay_ms(500);
//    huansic_led2_turn();
//    huansic_delay_ms(500);

//    while(OV2640_Init()){
//        printf("Camera Model Err\r\n");
//        huansic_led2_turn();
//    }
//    RGB565_Mode_Init();
//    printf("RGB565_MODE\r\n");
//    DVP_Init();

	while(1) {
//		huansic_led2_set(1);
//		huansic_delay_ms(500);
//		huansic_led2_set(0);
//		huansic_delay_ms(500);
//		if(USART2_GetRxFlag() == 1){
//            printf("%d\n", USART2_GetRxData());
//        }
	}
}

void blinkLater(uint32_t ms) {
	huansic_chronos_schedule(huansic_chronos_milliseconds() + 2000, blinkLater);
	util_led2_set(state);
	dc = dc + 0.1;
	if(dc == 1)
		dc = 0;
	huansic_motor_set(Fan | RightProp | LeftProp, state ? -0.3 : -0.8);/*state ? 0.1 : 0.3*/
	state = !state;
}
