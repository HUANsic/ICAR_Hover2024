#include <opt.h>
#include "huansic_util.h"

#define FOPT_D(x)     GPIO_WriteBit(GPIOB, GPIO_Pin_7, (BitAction)(x))
#define FOPT_C(x)     GPIO_WriteBit(GPIOB, GPIO_Pin_6, (BitAction)(x))
#define ROPT_D(x)     GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)(x))
#define ROPT_C(x)     GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)(x))

// PAW3205DB REG
#define REG_PID1                        0x00
#define REG_PID2                        0x01
#define REG_Motion_Status               0x02
#define REG_DELTA_X                     0x03
#define REG_DELTA_Y                     0x04
#define REG_Operation_Mode              0x05
#define REG_Configuration               0x06
#define REG_Image_Quality               0x07
#define REG_Operation_State             0x08
#define REG_Write_Protect               0x09
#define REG_Sleep1_Setting              0x0A
#define REG_Enter_Time                  0x0B
#define REG_Sleep2_Setting              0x0C
#define REG_Image_Threshold             0x0D
#define REG_Image_Recognition           0x0E

opt_data_typedef opt_data={0};
uint32_t fopt_time_us=0;
uint32_t ropt_time_us=0;

void fopt_write_reg(uint8_t address, uint8_t data) {
    address |= 0x80;
    for(int i = 0; i < 8; i++){
        FOPT_C(0);
        FOPT_D(address & (0x80 >> i));
        FOPT_C(1);
        Delay_Us(3);
    }
    for(int i = 0; i < 8; i++){
        FOPT_C(0);
        FOPT_D(data & (0x80 >> i));
        FOPT_C(1);
        Delay_Us(3);
    }
}

uint8_t fopt_read_reg(uint8_t address) {
    uint8_t data=0;
    for(int i = 0; i < 8; i++){
        FOPT_C(0);
        FOPT_D(address & (0x80 >> i));
        FOPT_C(1);
        Delay_Us(3);
    }
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    for(int i = 0; i < 8; i++){
        FOPT_C(0);
        FOPT_C(1);
        data |= GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) << (7 - i);
        Delay_Us(3);
    }
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    return data;
}

void ropt_write_reg(uint8_t address, uint8_t data) {
    address |= 0x80;
    for(int i = 0; i < 8; i++){
        ROPT_C(0);
        ROPT_D(address & (0x80 >> i));
        ROPT_C(1);
        Delay_Us(3);
    }
    for(int i = 0; i < 8; i++){
        ROPT_C(0);
        ROPT_D(data & (0x80 >> i));
        ROPT_C(1);
        Delay_Us(3);
    }
}

uint8_t ropt_read_reg(uint8_t address) {
    uint8_t data=0;
    for(int i = 0; i < 8; i++){
        ROPT_C(0);
        ROPT_D(address & (0x80 >> i));
        ROPT_C(1);
        Delay_Us(3);
    }
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    for(int i = 0; i < 8; i++){
        ROPT_C(0);
        ROPT_C(1);
        data |= GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) << (7 - i);
        Delay_Us(3);
    }
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    return data;
}

void fopt_resync() {
    FOPT_C(0);
    Delay_Us(1);
    FOPT_C(1);
    Delay_Ms(2);
}

void ropt_resync() {
    ROPT_C(0);
    Delay_Us(1);
    ROPT_C(1);
    Delay_Ms(2);
}

uint8_t fopt_id(void) {
    return fopt_read_reg(REG_PID1);
};

uint8_t ropt_id(void) {
    return ropt_read_reg(REG_PID1);
};

void opt_gpio_init() {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void opt_timer_init(u16 arr,u16 psc) {  //定时器3初始化
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
    TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值    计数到5000为500ms
    TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    TIM_ITConfig(  //使能或者失能指定的TIM中断
    TIM3, //TIM2
    TIM_IT_Update  |  //TIM 中断源
    TIM_IT_Trigger,   //TIM 触发中断源
    ENABLE  //使能
        );
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    TIM_Cmd(TIM3, ENABLE);  //使能TIM3外设
}

//定时器3中断服务程序
__attribute__((interrupt("WCH-Interrupt-fast"))) void TIM3_IRQHandler(void) {  //TIM3中断
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) { //检查TIM3更新中断发生与否
        fopt_time_us ++;
        ropt_time_us ++;
    }
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源
}

void opt_init() {
    opt_gpio_init();
    opt_timer_init(11, 11);
}

void refresh_opt_data() {
    opt_data.front_interval += fopt_time_us;
    fopt_time_us = 0;
    if(fopt_read_reg(REG_Motion_Status) & 0x80){
        huansic_led1_set(1);
    }
    else{
        huansic_led1_set(0);
    }
    opt_data.front_dx += fopt_read_reg(REG_DELTA_X);
    opt_data.front_dy += fopt_read_reg(REG_DELTA_Y);
    opt_data.rear_interval += ropt_time_us;
    ropt_time_us = 0;
    ropt_read_reg(REG_Motion_Status);
    opt_data.rear_dx += ropt_read_reg(REG_DELTA_X);
    opt_data.rear_dy += ropt_read_reg(REG_DELTA_Y);
}

void reset_opt_data() {
    opt_data.front_interval = 0;
    opt_data.front_dx = 0;
    opt_data.front_dy = 0;
    opt_data.rear_interval = 0;
    opt_data.rear_dx = 0;
    opt_data.rear_dy = 0;
}

opt_data_typedef get_opt_data() {
//    opt_data.front_dx = -17;
//    opt_data.front_dy = 34;
//    opt_data.rear_dx = -17;
//    opt_data.rear_dy = 34;
    return opt_data;
}

