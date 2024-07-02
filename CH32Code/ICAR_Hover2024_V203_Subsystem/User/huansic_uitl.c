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
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;
	TIM_TimeBaseInitStructure.TIM_Prescaler = SystemCoreClock / 1000 - 1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init( TIM1, &TIM_OCInitStructure);
	TIM_OC2Init( TIM1, &TIM_OCInitStructure);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_OC1PreloadConfig( TIM1, TIM_OCPreload_Disable);
	TIM_OC2PreloadConfig( TIM1, TIM_OCPreload_Disable);
	TIM_ARRPreloadConfig( TIM1, ENABLE);
	TIM_Cmd( TIM1, ENABLE);
}

void huansic_led1_set(float bri) {
	if (bri < 0)
		bri = 0;
	if (bri > 1)
		bri = 1;
	TIM1->CH1CVR = (uint16_t) (bri * 1000);
}

void huansic_led2_set(float bri) {
	if (bri < 0)
		bri = 0;
	if (bri > 1)
		bri = 1;
	TIM1->CH2CVR = (uint16_t) (bri * 1000);
}
