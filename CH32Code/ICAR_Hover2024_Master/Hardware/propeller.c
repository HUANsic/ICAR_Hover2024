#include "propeller.h"

void Propeller_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);            //����TIM2��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIO�˿�ʱ��

    GPIO_InitTypeDef  GPIO_InitStructure;                //����һ��GPIO_InitTypeDef���͵Ľṹ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3; //����GPIO����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //����GPIOģʽΪ�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //����GPIO������ٶ�
    GPIO_Init(GPIOA, &GPIO_InitStructure);               //���ÿ⺯������ʼ��GPIOB

    /*ʱ����Ԫ��ʼ��*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              //����ṹ�����
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ��ѡ�񲻷�Ƶ���˲������������˲���ʱ�ӣ���Ӱ��ʱ����Ԫ����
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //������ģʽ��ѡ�����ϼ���
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;                 //�������ڣ���ARR��ֵ
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1440 - 1;              //Ԥ��Ƶ������PSC��ֵ
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //�ظ����������߼���ʱ���Ż��õ�
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);             //���ṹ���������TIM_TimeBaseInit������TIM2��ʱ����Ԫ

    /*����Ƚϳ�ʼ��*/
    TIM_OCInitTypeDef TIM_OCInitStructure;                          //����ṹ�����
    TIM_OCStructInit(&TIM_OCInitStructure);                         //�ṹ���ʼ�������ṹ��û��������ֵ�����ִ�д˺��������ṹ�����г�Ա����һ��Ĭ��ֵ������ṹ���ֵ��ȷ��������
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //����Ƚ�ģʽ��ѡ��PWMģʽ1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //������ԣ�ѡ��Ϊ�ߣ���ѡ����Ϊ�ͣ�������ߵ͵�ƽȡ��
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //���ʹ��
    TIM_OCInitStructure.TIM_Pulse = 0;                              //��ʼ��CCRֵ
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);                        //���ṹ���������TIM_OC1Init������TIM2������Ƚ�ͨ��1
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);                        //���ṹ���������TIM_OC2Init������TIM2������Ƚ�ͨ��2
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);                        //���ṹ���������TIM_OC3Init������TIM2������Ƚ�ͨ��3
    TIM_OC4Init(TIM2, &TIM_OCInitStructure);                        //���ṹ���������TIM_OC4Init������TIM2������Ƚ�ͨ��4

    /*TIMʹ��*/
    TIM_Cmd(TIM2, ENABLE);          //ʹ��TIM2����ʱ����ʼ����
    TIM_CtrlPWMOutputs(TIM2, ENABLE);   //ʹ��PWM���
}

void Propeller1_Duty(int16_t duty){
    if(duty >= 0){
        TIM_SetCompare1(TIM2, duty);
        TIM_SetCompare2(TIM2, 0);
    }
    else{
        TIM_SetCompare1(TIM2, 0);
        TIM_SetCompare2(TIM2, duty);
    }
}

void Propeller2_Duty(int16_t duty){
    if(duty >= 0){
        TIM_SetCompare3(TIM2, duty);
        TIM_SetCompare4(TIM2, 0);
    }
    else{
        TIM_SetCompare3(TIM2, 0);
        TIM_SetCompare4(TIM2, -duty);
    }
}

void Propeller_Enable(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//ʹ��GPIO�˿�ʱ��
    GPIO_InitTypeDef  GPIO_InitStructure;                //����һ��GPIO_InitTypeDef���͵Ľṹ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //����GPIO����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;     //����GPIOģʽΪ�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //����GPIO������ٶ�
    GPIO_Init(GPIOD, &GPIO_InitStructure);               //���ÿ⺯������ʼ��GPIOD
    //GPIO_WriteBit(GPIOD, GPIO_Pin_11, Bit_SET);
    GPIO_SetBits(GPIOD, GPIO_Pin_11);
};

