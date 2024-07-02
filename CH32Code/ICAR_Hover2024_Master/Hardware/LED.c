#include "LED.h"

void LED1_Init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能GPIO端口时钟

    GPIO_InitTypeDef  GPIO_InitStructure;                //定义一个GPIO_InitTypeDef类型的结构体
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //配置GPIO引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //设置GPIO模式为推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //设置GPIO口输出速度
    GPIO_Init(GPIOB, &GPIO_InitStructure);               //调用库函数，初始化GPIOB

    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}

void LED1_ON(){
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

void LED1_OFF(){
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}




void LED2_Init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//使能GPIO端口时钟

    GPIO_InitTypeDef  GPIO_InitStructure;                //定义一个GPIO_InitTypeDef类型的结构体
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //配置GPIO引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //设置GPIO模式为推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //设置GPIO口输出速度
    GPIO_Init(GPIOE, &GPIO_InitStructure);               //调用库函数，初始化GPIOB

    GPIO_ResetBits(GPIOE, GPIO_Pin_10);
}

void LED2_ON(){
    GPIO_SetBits(GPIOE, GPIO_Pin_10);
}

void LED2_OFF(){
    GPIO_ResetBits(GPIOE, GPIO_Pin_10);
}

