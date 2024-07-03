/*
 * huansic_motor.c
 *
 *  Created on: Jul 3, 2024
 *      Author: ZonghuanWu
 */

#include "huansic_motor.h"

void huansic_motor_init(void) {
	GPIO_InitTypeDef GPIO_InitStructure = { 0 };
	TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM8, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13 | GPIO_Pin_12;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;		// PD11
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Period = 3840 - 1;	// 96MHz / 25kHz - 1
	TIM_TimeBaseInitStructure.TIM_Prescaler = 0;	// full speed!!
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(TIM4, ENABLE);
	TIM_ARRPreloadConfig(TIM8, ENABLE);
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM8, ENABLE);
}

void huansic_motor_set(MotorName motor, float val){
	val = val > 1 ? 1 : (val < -1 ? -1 : val);		// constrain
	if(motor & Fan){
		if(val < 0){
			TIM8->CH1CVR = 0;
			TIM8->CH2CVR = (uint16_t)(-val * 3840);
		} else {
			TIM8->CH1CVR = (uint16_t)(val * 3840);
			TIM8->CH2CVR = 0;
		}
	}
	if(motor & LeftProp){
		if(val < 0){
			TIM4->CH1CVR = 0;
			TIM4->CH2CVR = (uint16_t)(-val * 3840);
		} else {
			TIM4->CH1CVR = (uint16_t)(val * 3840);
			TIM4->CH2CVR = 0;
		}
	}
	if(motor & RightProp){
		if(val < 0){
			TIM4->CH3CVR = 0;
			TIM4->CH4CVR = (uint16_t)(-val * 3840);
		} else {
			TIM4->CH3CVR = (uint16_t)(val * 3840);
			TIM4->CH4CVR = 0;
		}
	}
}

inline void huansic_motor_enable(void){
	GPIO_WriteBit(GPIOD, GPIO_Pin_11, 1);
}

inline void huansic_motor_disable(void){
	GPIO_WriteBit(GPIOD, GPIO_Pin_11, 0);
}
