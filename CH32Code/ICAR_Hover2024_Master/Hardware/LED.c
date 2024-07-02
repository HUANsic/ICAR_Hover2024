#include "LED.h"

void LED1_Init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��GPIO�˿�ʱ��

    GPIO_InitTypeDef  GPIO_InitStructure;                //����һ��GPIO_InitTypeDef���͵Ľṹ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //����GPIO����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //����GPIOģʽΪ�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //����GPIO������ٶ�
    GPIO_Init(GPIOB, &GPIO_InitStructure);               //���ÿ⺯������ʼ��GPIOB

    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}

void LED1_ON(){
    GPIO_SetBits(GPIOB, GPIO_Pin_0);
}

void LED1_OFF(){
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}




void LED2_Init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//ʹ��GPIO�˿�ʱ��

    GPIO_InitTypeDef  GPIO_InitStructure;                //����һ��GPIO_InitTypeDef���͵Ľṹ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //����GPIO����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //����GPIOģʽΪ�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //����GPIO������ٶ�
    GPIO_Init(GPIOE, &GPIO_InitStructure);               //���ÿ⺯������ʼ��GPIOB

    GPIO_ResetBits(GPIOE, GPIO_Pin_10);
}

void LED2_ON(){
    GPIO_SetBits(GPIOE, GPIO_Pin_10);
}

void LED2_OFF(){
    GPIO_ResetBits(GPIOE, GPIO_Pin_10);
}

