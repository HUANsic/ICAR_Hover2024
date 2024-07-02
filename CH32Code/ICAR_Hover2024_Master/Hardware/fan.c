#include "fan.h"

void Fan_Init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);            //����TIM2��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//ʹ��GPIO�˿�ʱ��

    GPIO_InitTypeDef  GPIO_InitStructure;                //����һ��GPIO_InitTypeDef���͵Ľṹ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; //����GPIO����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //����GPIOģʽΪ�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //����GPIO������ٶ�
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //���ÿ⺯������ʼ��GPIOB

    //GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);           //������������͵�ƽ

    /*ʱ����Ԫ��ʼ��*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              //����ṹ�����
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ��ѡ�񲻷�Ƶ���˲������������˲���ʱ�ӣ���Ӱ��ʱ����Ԫ����
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //������ģʽ��ѡ�����ϼ���
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;                 //�������ڣ���ARR��ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1440 - 1;              //Ԥ��Ƶ������PSC��ֵ
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //�ظ����������߼���ʱ���Ż��õ�
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStructure);             //���ṹ���������TIM_TimeBaseInit������TIM3��ʱ����Ԫ

    /*����Ƚϳ�ʼ��*/
    TIM_OCInitTypeDef TIM_OCInitStructure;                          //����ṹ�����
    TIM_OCStructInit(&TIM_OCInitStructure);                         //�ṹ���ʼ�������ṹ��û��������ֵ�����ִ�д˺��������ṹ�����г�Ա����һ��Ĭ��ֵ������ṹ���ֵ��ȷ��������
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //����Ƚ�ģʽ��ѡ��PWMģʽ1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //������ԣ�ѡ��Ϊ�ߣ���ѡ����Ϊ�ͣ�������ߵ͵�ƽȡ��
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //���ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0;                              //��ʼ��CCRֵ
    TIM_OC1Init(TIM8, &TIM_OCInitStructure);                        //���ṹ���������TIM_OC3Init������TIM3������Ƚ�ͨ��3
    TIM_OC2Init(TIM8, &TIM_OCInitStructure);                        //���ṹ���������TIM_OC4Init������TIM3������Ƚ�ͨ��4

    /*TIMʹ��*/
    TIM_Cmd(TIM8, ENABLE);          //ʹ��TIM3����ʱ����ʼ����
    TIM_CtrlPWMOutputs(TIM8, ENABLE);   //ʹ��PWM���
}

void Fan1_Duty(uint8_t duty){
    TIM_SetCompare1(TIM8, duty);
}

void Fan2_Duty(uint8_t duty){
    TIM_SetCompare2(TIM8, duty);
}
