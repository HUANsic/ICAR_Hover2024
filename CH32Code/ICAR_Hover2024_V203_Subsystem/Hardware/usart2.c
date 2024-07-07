#include <usart2.h>
#include "huansic_util.h"

u8 USART2_RxData;       //���ڽ�������
u8 USART2_RxFlag;       //���ڽ��ձ�־λ

u8 UART6_RxData;       //���ڽ�������
u8 UART6_RxFlag;       //���ڽ��ձ�־λ

u8 UART7_RxData;       //���ڽ�������
u8 UART7_RxFlag;       //���ڽ��ձ�־λ

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
    if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)        //�ж��Ƿ���UART5�Ľ����¼��������ж�
    {
        USART2_RxData = USART_ReceiveData(USART2);
        if(USART2_RxData == 0x11){
            USART2_RxFlag = 1;
            huansic_led2_turn();
        }
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);         //�����־λ
    }
}

/**
  * ��    ������ȡ���ڽ������ݰ���־λ
  * ��    ������
  * �� �� ֵ�����ڽ������ݰ���־λ����Χ��0~1�����յ����ݰ��󣬱�־λ��1����ȡ���־λ�Զ�����
  */
uint8_t USART2_GetRxFlag(void)
{
    if (USART2_RxFlag == 1)         //�����־λΪ1
    {
        USART2_RxFlag = 0;
        return 1;                   //�򷵻�1�����Զ������־λ
    }
    return 0;                       //�����־λΪ0���򷵻�0
}

uint8_t USART2_GetRxData(void){
    return USART2_RxData;
}


/**
  * ��    �������ڷ���һ���ֽ�
  * ��    ����Byte Ҫ���͵�һ���ֽ�
  * �� �� ֵ����
  */
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART2, Byte);       //���ֽ�����д�����ݼĴ�����д���USART�Զ�����ʱ����
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);   //�ȴ��������
    /*�´�д�����ݼĴ������Զ����������ɱ�־λ���ʴ�ѭ�������������־λ*/
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
  * ��    �������ڷ���һ���ַ���
  * ��    ����String Ҫ�����ַ������׵�ַ
  * �� �� ֵ����
  */
void Serial_SendString(char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i ++)//�����ַ����飨�ַ������������ַ���������־λ��ֹͣ
    {
        Serial_SendByte(String[i]);     //���ε���Serial_SendByte����ÿ���ֽ�����
    }
}


/**
  * ��    �����η��������ڲ�ʹ�ã�
  * �� �� ֵ������ֵ����X��Y�η�
  */
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;    //���ý����ֵΪ1
    while (Y --)            //ִ��Y��
    {
        Result *= X;        //��X�۳˵����
    }
    return Result;
}

/**
  * ��    �������ڷ�������
  * ��    ����Number Ҫ���͵����֣���Χ��0~4294967295
  * ��    ����Length Ҫ�������ֵĳ��ȣ���Χ��0~10
  * �� �� ֵ����
  */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i ++)       //�������ֳ��ȱ������ֵ�ÿһλ
    {
        Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');    //���ε���Serial_SendByte����ÿλ����
    }
}

