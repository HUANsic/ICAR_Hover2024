/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 USART Print debugging routine:
 UART5_Tx(PB4).
 This example demonstrates using UART5(PB4) as a print debug port output.

*/

#include "dvp.h"
#include "ov.h"
#include "debug.h"
#include "propeller.h"
#include "uart5.h"

/* Global typedef */

/* Global define */

/* Global Variable */





/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SystemCoreClockUpdate();
	Delay_Init();
	UART5_Init(115200);
	Propeller_Init();
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );


	while(OV2640_Init()){
        printf("Camera Model Err\r\n");
    }
    RGB565_Mode_Init();
    printf("RGB565_MODE\r\n");
    DVP_Init();



	while(1)
    {
	    if (Serial_GetRxFlag() == 1){
	        printf("%d\n", Serial_GetRxData());
	    }


	    printf("lu:%-5dru:%-5dlb:%-5drb:%-5dc:%-5d\n", GetGray_RGB565(0, 0), GetGray_RGB565(0, 59), GetGray_RGB565(79, 0), GetGray_RGB565(79, 59), GetGray_RGB565(40, 30));
	    //printf("%d\n", *(u8*)(0x2000A000 + 80 * 120 -1));
	    Delay_Ms(500);
	}
}

