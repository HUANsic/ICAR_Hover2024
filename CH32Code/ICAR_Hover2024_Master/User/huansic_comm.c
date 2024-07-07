/*
 * huansic_comm.c
 *
 *  Created on: May 21, 2024
 *      Author: ZonghuanWu
 */

#include "huansic_comm.h"
#include "huansic_util.h"

uint8_t subsys_data;
uint8_t subsys_data_flag;
opt_data_typedef opt_data;
uint8_t opt_data_flag = 0;
uint8_t serial_status_flag = 0;

void huansic_subsys_init() {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	USART_InitTypeDef USART_InitStructure = { 0 };
	NVIC_InitTypeDef NVIC_InitStructure = { 0 };

	// apply changes
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);

	// set up TX and RX GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// set up UART
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	// apply changes
	USART_Init(UART7, &USART_InitStructure);

	// enable reception interrupt
	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);

	// set up NVIC
	NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;	// 2nd highest priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			// highest sub-priority
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	// apply changes
	NVIC_Init(&NVIC_InitStructure);

	// start UART
	USART_Cmd(UART7, ENABLE);
}

void __huansic_subsys_received(uint8_t data){
    subsys_data = data;
    subsys_data_flag = 1;
    huansic_led7_turn();
}

//void UART7_IRQHandler(void)__attribute__((interrupt("WCH-Interrupt-fast")));
//void UART7_IRQHandler() {
//	if (USART_GetITStatus(UART7, USART_IT_ORE)) {
//		USART_ReceiveData(UART7);
//		USART_ReceiveData(UART7);
//		USART_ClearFlag(UART7, USART_FLAG_ORE);
//	} else if (USART_GetITStatus(UART7, USART_IT_RXNE)) {
//		__huansic_subsys_received(USART_ReceiveData(UART7) & 0x0FF);
//		USART_ClearFlag(UART7, USART_FLAG_RXNE);
//	}
//}

void UART7_IRQHandler(void)__attribute__((interrupt("WCH-Interrupt-fast")));
void UART7_IRQHandler(void) {
    if (USART_GetITStatus(UART7, USART_IT_RXNE) == SET)        //判断是否是UART5的接收事件触发的中断
    {
        int8_t subsys_data_temp = USART_ReceiveData(UART7);
        subsys_data_flag = 1;
        if(serial_status_flag == 0 && subsys_data_temp == (int8_t)0x01) {
            serial_status_flag++;
        }
        else if(serial_status_flag == 1) {
            opt_data.front_dx = (int8_t)(subsys_data_temp << 8);
            serial_status_flag++;
        }
        else if(serial_status_flag == 2) {
            opt_data.front_dx = (int8_t)(subsys_data_temp);
            serial_status_flag++;
        }
        else if(serial_status_flag == 3) {
            opt_data.front_dy = (int8_t)(subsys_data_temp << 8);
            serial_status_flag++;
        }
        else if(serial_status_flag == 4) {
            opt_data.front_dy = (int8_t)(subsys_data_temp);
            serial_status_flag++;
        }
        else if(serial_status_flag == 5) {
            opt_data.rear_dx = (int8_t)(subsys_data_temp << 8);
            serial_status_flag++;
        }
        else if(serial_status_flag == 6) {
            opt_data.rear_dx = (int8_t)(subsys_data_temp);
            serial_status_flag++;
        }
        else if(serial_status_flag == 7) {
            opt_data.rear_dy = (int8_t)(subsys_data_temp << 8);
            serial_status_flag++;
        }
        else if(serial_status_flag == 8) {
            opt_data.rear_dy = (int8_t)(subsys_data_temp);
            serial_status_flag++;
        }
        else if(serial_status_flag == 9 && subsys_data_temp == (int8_t)0x8f) {
            serial_status_flag = 0;
            opt_data_flag = 1;
        }

        else if(serial_status_flag == 0 && subsys_data_temp == (int8_t)0x00) {
            serial_status_flag = 16;
        }
        else if(serial_status_flag == 16) {
            subsys_data = (uint8_t)subsys_data_temp;
            serial_status_flag++;
        }
        else if(serial_status_flag == 17 && subsys_data_temp == (int8_t)0xff) {
            serial_status_flag = 0;
            subsys_data_flag = 1;
        }
        else {
            serial_status_flag = 0;
//            printf("subsystem serial data receive logic error\n");
        }
        huansic_led7_turn();
        USART_ClearITPendingBit(UART7, USART_IT_RXNE);         //清除标志位
    }
}

uint8_t get_opt_data_flag() {
    return opt_data_flag;
}

opt_data_typedef get_opt_data() {
    opt_data_flag = 0;
    return opt_data;
}

uint8_t get_subsys_data_flag(void)
{
    if (subsys_data_flag == 1)         //如果标志位为1
    {
        subsys_data_flag = 0;
        return 1;                   //则返回1，并自动清零标志位
    }
    return 0;                       //如果标志位为0，则返回0
}

uint8_t get_subsys_data(void){
    return subsys_data;
}

void UART7_SendByte(uint8_t Byte) {
    USART_SendData(UART7, Byte);       //将字节数据写入数据寄存器，写入后USART自动生成时序波形
    while (USART_GetFlagStatus(UART7, USART_FLAG_TXE) == RESET);   //等待发送完成
    /*下次写入数据寄存器会自动清除发送完成标志位，故此循环后，无需清除标志位*/
}
