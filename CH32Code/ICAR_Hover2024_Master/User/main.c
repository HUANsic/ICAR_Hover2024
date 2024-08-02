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
#include "mco.h"
#include "img_process.h"
#include "pid.h"

extern uint8_t  Image_Gray[IMGH][IMGW];
extern uint8_t  Image_Bin[IMGH][IMGW];

int32_t error;

int main(void) {
	SystemCoreClockUpdate();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    USART2_Init(115200);
    printf("SystemClk:%d\r\n",SystemCoreClock);
    printf("ChipID:%08x\r\n", DBGMCU_GetCHIPID());

    huansic_subsys_init();
    huansic_led_init();
    huansic_motor_init();
    huansic_motor_enable();
	huansic_chronos_init();

	huansic_motor_init();
	mco_init();

	huansic_led1_turn();
    huansic_delay_ms(300);

    huansic_motor_enable();

    for(uint8_t i = 0; i <= 40; i++){
        huansic_motor_set(Fan, i / 40.0);
        huansic_motor_set(LeftProp, i / 40.0);
        huansic_motor_set(RightProp, i / 40.0);
        huansic_delay_ms(10);
    }

    while(OV2640_Init()){
        printf("Camera Model Err\r\n");
        huansic_led3_turn();
    }
    RGB565_Mode_Init();
    printf("RGB565_MODE\r\n");
    DVP_Init();

    uint32_t i = 0;
    uint32_t last_fps_count=0;
    uint8_t LeftPropGoal, RightPropGoal;
    float LeftPropDuty, RightPropDuty;

	while(1) {

//	    LeftPropDuty = 1;
//	    RightPropDuty = 1;
//	    if(huansic_chronos_milliseconds() % 1000 <= LeftPropDuty * 1000){
//	        LeftPropGoal = 1;
//	    }
//	    else{
//	        LeftPropGoal = 0;
//	    }
//	    if(huansic_chronos_milliseconds() % 1000 <= RightPropDuty * 1000){
//            RightPropGoal = 1;
//        }
//        else{
//            RightPropGoal = 0;
//        }
//
//	    if(GetReadingFlag() == 0){
//	        huansic_motor_set(LeftProp, LeftPropGoal);
//	        huansic_motor_set(RightProp, RightPropGoal);
//	    }

//		if(get_fps_count() != last_fps_count){
//		    huansic_motor_set(LeftProp, 0.8);
		    last_fps_count = get_fps_count();
            huansic_led2_turn();
            i++;
            printf("running, i = %d\n", i);
            printf("fps count = %d\n", get_fps_count());
            printf("error: %d\n", error);
            UART7_SendImageBin();

            binarization();
            threhold_update();
            Bin_Image_Filter();
            error = get_err();
            if(error > 0){
                huansic_led1_set(1);
            }
            else{
                huansic_led1_set(0);
            }
//            pid_prop_update(0, error);
//            huansic_delay_ms(20);
//            huansic_motor_set(LeftProp, 0);
//		}
        huansic_delay_ms(500);
	}
}
