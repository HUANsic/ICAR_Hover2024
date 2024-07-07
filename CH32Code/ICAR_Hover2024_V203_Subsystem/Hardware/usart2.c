#include <usart2.h>
#include "huansic_util.h"

u8 USART2_RxData;       //串口接收数据
u8 USART2_RxFlag;       //串口接收标志位

u8 UART6_RxData;       //串口接收数据
u8 UART6_RxFlag;       //串口接收标志位

u8 UART7_RxData;       //串口接收数据
u8 UART7_RxFlag;       //串口接收标志位

void USART2_Init(uint32_t baudrate){
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART2, ENABLE);
}

void USART2_IRQHandler(void)__attribute__((interrupt("WCH-Interrupt-fast")));
void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)        //判断是否是UART5的接收事件触发的中断
    {
        USART2_RxData = USART_ReceiveData(USART2);
        if(USART2_RxData == 0x11){
            USART2_RxFlag = 1;
            huansic_led2_turn();
        }
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);         //清除标志位
    }
}

/**
  * 函    数：获取串口接收数据包标志位
  * 参    数：无
  * 返 回 值：串口接收数据包标志位，范围：0~1，接收到数据包后，标志位置1，读取后标志位自动清零
  */
uint8_t USART2_GetRxFlag(void)
{
    if (USART2_RxFlag == 1)         //如果标志位为1
    {
        USART2_RxFlag = 0;
        return 1;                   //则返回1，并自动清零标志位
    }
    return 0;                       //如果标志位为0，则返回0
}

uint8_t USART2_GetRxData(void){
    return USART2_RxData;
}


/**
  * 函    数：串口发送一个字节
  * 参    数：Byte 要发送的一个字节
  * 返 回 值：无
  */
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART2, Byte);       //将字节数据写入数据寄存器，写入后USART自动生成时序波形
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);   //等待发送完成
    /*下次写入数据寄存器会自动清除发送完成标志位，故此循环后，无需清除标志位*/
}

void Serial_SendByteData(uint8_t Byte) {
    Serial_SendByte(0x00);
    Serial_SendByte(Byte);
    Serial_SendByte(0xff);
}

void Serial_SendSensorData(opt_data_typedef opt_data) {
    Serial_SendByte(0x01);
    Serial_SendByte((uint16_t)opt_data.front_dx >> 8);
    Serial_SendByte((uint16_t)opt_data.front_dx);
    Serial_SendByte((uint16_t)opt_data.front_dy >> 8);
    Serial_SendByte((uint16_t)opt_data.front_dy);
    Serial_SendByte((uint16_t)opt_data.rear_dx >> 8);
    Serial_SendByte((uint16_t)opt_data.rear_dx);
    Serial_SendByte((uint16_t)opt_data.rear_dy >> 8);
    Serial_SendByte((uint16_t)opt_data.rear_dy);
    Serial_SendByte(0x8f);
}


/**
  * 函    数：串口发送一个字符串
  * 参    数：String 要发送字符串的首地址
  * 返 回 值：无
  */
void Serial_SendString(char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i ++)//遍历字符数组（字符串），遇到字符串结束标志位后停止
    {
        Serial_SendByte(String[i]);     //依次调用Serial_SendByte发送每个字节数据
    }
}


/**
  * 函    数：次方函数（内部使用）
  * 返 回 值：返回值等于X的Y次方
  */
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;    //设置结果初值为1
    while (Y --)            //执行Y次
    {
        Result *= X;        //将X累乘到结果
    }
    return Result;
}

/**
  * 函    数：串口发送数字
  * 参    数：Number 要发送的数字，范围：0~4294967295
  * 参    数：Length 要发送数字的长度，范围：0~10
  * 返 回 值：无
  */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i ++)       //根据数字长度遍历数字的每一位
    {
        Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');    //依次调用Serial_SendByte发送每位数字
    }
}

