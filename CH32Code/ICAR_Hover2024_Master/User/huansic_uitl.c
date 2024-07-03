/*
 * huansic_uitl.c
 *
 *  Created on: May 21, 2024
 *      Author: ZonghuanWu
 */

#include "huansic_util.h"

int32_t huansic_map(int32_t input, int32_t old_floor, int32_t old_ceil, int32_t new_floor, int32_t new_ceil) {
	float temp = old_ceil - old_floor;
	float percentage = input - old_floor;
	percentage /= temp;
	temp = new_ceil - new_floor;
	percentage *= temp;
	percentage += old_floor;
	return (int32_t) percentage;
}

void huansic_led_init() {
	// PWM pin
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = SystemCoreClock / 1000 - 1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM3, &TIM_TimeBaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;	// turn off for now
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init( TIM3, &TIM_OCInitStructure);

	TIM_CtrlPWMOutputs(TIM3, ENABLE);
	TIM_OC3PreloadConfig( TIM3, TIM_OCPreload_Disable);
	TIM_ARRPreloadConfig( TIM3, ENABLE);
	TIM_Cmd( TIM3, ENABLE);

	// GPIO
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = 0xFC00;		// PE10~15
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	// turn off for now
	GPIO_WriteBit(GPIOE, 0xFC00, Bit_RESET);
}

void huansic_led1_set(float bri) {
	if (bri < 0)
		bri = 0;
	if (bri > 1)
		bri = 1;
	TIM3->CH3CVR = (uint16_t) (bri * 1000);
}

void huansic_led2_set(float bri) {
	GPIO_WriteBit(GPIOE, GPIO_Pin_10, bri < 0.5 ? 0 : 1);
}

void huansic_led3_set(float bri) {
	GPIO_WriteBit(GPIOE, GPIO_Pin_11, bri < 0.5 ? 0 : 1);
}

void huansic_led4_set(float bri) {
	GPIO_WriteBit(GPIOE, GPIO_Pin_12, bri < 0.5 ? 0 : 1);
}

void huansic_led5_set(float bri) {
	GPIO_WriteBit(GPIOE, GPIO_Pin_13, bri < 0.5 ? 0 : 1);
}

void huansic_led6_set(float bri) {
	GPIO_WriteBit(GPIOE, GPIO_Pin_14, bri < 0.5 ? 0 : 1);
}

void huansic_led7_set(float bri) {
	GPIO_WriteBit(GPIOE, GPIO_Pin_15, bri < 0.5 ? 0 : 1);
}

void huansic_led2_turn() {
    if(GPIO_ReadOutputDataBit(GPIOE,GPIO_Pin_10)){
        GPIO_ResetBits(GPIOE,GPIO_Pin_10);
    }
    else{
        GPIO_SetBits(GPIOE,GPIO_Pin_10);
    }
}
