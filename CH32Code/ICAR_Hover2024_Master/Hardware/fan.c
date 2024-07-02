#include "fan.h"

void Fan_Init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);            //开启TIM2的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//使能GPIO端口时钟

    GPIO_InitTypeDef  GPIO_InitStructure;                //定义一个GPIO_InitTypeDef类型的结构体
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7; //配置GPIO引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;     //设置GPIO模式为推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    //设置GPIO口输出速度
    GPIO_Init(GPIOC, &GPIO_InitStructure);               //调用库函数，初始化GPIOB

    //GPIO_ResetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);           //设置引脚输出低电平

    /*时基单元初始化*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              //定义结构体变量
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式，选择向上计数
    TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;                 //计数周期，即ARR的值
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1440 - 1;              //预分频器，即PSC的值
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStructure);             //将结构体变量交给TIM_TimeBaseInit，配置TIM3的时基单元

    /*输出比较初始化*/
    TIM_OCInitTypeDef TIM_OCInitStructure;                          //定义结构体变量
    TIM_OCStructInit(&TIM_OCInitStructure);                         //结构体初始化，若结构体没有完整赋值则最好执行此函数，给结构体所有成员都赋一个默认值，避免结构体初值不确定的问题
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //输出比较模式，选择PWM模式1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //输出极性，选择为高，若选择极性为低，则输出高低电平取反
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //输出使能
    TIM_OCInitStructure.TIM_Pulse = 0;                              //初始的CCR值
    TIM_OC1Init(TIM8, &TIM_OCInitStructure);                        //将结构体变量交给TIM_OC3Init，配置TIM3的输出比较通道3
    TIM_OC2Init(TIM8, &TIM_OCInitStructure);                        //将结构体变量交给TIM_OC4Init，配置TIM3的输出比较通道4

    /*TIM使能*/
    TIM_Cmd(TIM8, ENABLE);          //使能TIM3，定时器开始运行
    TIM_CtrlPWMOutputs(TIM8, ENABLE);   //使能PWM输出
}

void Fan1_Duty(uint8_t duty){
    TIM_SetCompare1(TIM8, duty);
}

void Fan2_Duty(uint8_t duty){
    TIM_SetCompare2(TIM8, duty);
}
