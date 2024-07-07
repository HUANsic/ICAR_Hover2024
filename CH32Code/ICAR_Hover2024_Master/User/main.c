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
#include "dvp.h"
#include "ov.h"
#include "usart2.h"

uint8_t state;

int main(void) {
	SystemCoreClockUpdate();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    USART2_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());

    huansic_subsys_init();
    huansic_led_init();
	huansic_chronos_init();
	huansic_motor_init();

	huansic_led1_turn();
    huansic_delay_ms(500);


    huansic_motor_enable();
    huansic_motor_set(Fan, 0.2);
    huansic_motor_set(LeftProp, 1);
    huansic_motor_set(RightProp, 1);

    while(OV2640_Init()){
        printf("Camera Model Err\r\n");
        huansic_led3_turn();
    }
    RGB565_Mode_Init();
    printf("RGB565_MODE\r\n");
    DVP_Init();

    uint32_t i = 0;

	while(1) {
	    huansic_led1_turn();
		huansic_led2_turn();
		printf("running, i = %d\n", i);
		i++;
		huansic_delay_ms(500);

//		if(USART2_GetRxFlag() == 1){
//            printf("%d\n", USART2_GetRxData());
//        }
//		if(get_subsys_data_flag() == 1){
//		    printf("byte data: %d\n", get_subsys_data());
//        }
//        UART7_SendByte(0x11);
//		while(! get_opt_data_flag());
//        printf("opt data: %d, %d, %d, %d\n", get_opt_data().front_dx, get_opt_data().front_dy, get_opt_data().rear_dx, get_opt_data().rear_dy);


	}
}

void blinkLater(uint32_t ms) {
	huansic_chronos_schedule(huansic_chronos_milliseconds() + 2000, blinkLater);
	huansic_led2_set(state);
	huansic_motor_set(Fan | RightProp | LeftProp, state ? 0.1 : 0.3);
	state = !state;
}
