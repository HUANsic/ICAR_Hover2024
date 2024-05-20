/********************************** (C) COPYRIGHT *******************************
* File Name          : ov.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : This file contains the headers of the OV2640.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "ov.h"

/* Start Camera list of initialization configuration registers */
const UINT8 OV2640_InitRegTbl[][2]=
{
	0xff, 0x00, 0x2c, 0xff,	0x2e, 0xdf,

	0xff, 0x01,	0x3c, 0x32,

	0x11, 0x00,	0x09, 0x02,	0x04, 0xD8,

	0x13, 0xe5,	0x13, 0xe0,                //Bit[2]:AGC 0:M 1:A, Bit[0] Exposure Control 0:M 1:A

	0x14, 0x48,	0x2c, 0x0c,	0x33, 0x78,	0x3a, 0x33,	0x3b, 0xfB,

	0x3e, 0x00,	0x43, 0x11,	0x16, 0x10,

	0x39, 0x92,

	0x35, 0xda,	0x22, 0x1a,	0x37, 0xc3,	0x23, 0x00,	0x34, 0xc0,	0x36, 0x1a,	0x06, 0x88,	0x07, 0xc0,	0x0d, 0x87,	0x0e, 0x41,	0x4c, 0x00,

	0x48, 0x00,	0x5B, 0x00,	0x42, 0x03,

	0x4a, 0x81,	0x21, 0x99,

	0x24, 0x40,	0x24, 0xff,                //Max M Luminance

	0x25, 0x38,	0x25, 0x00,                //Min M Luminance

	0x26, 0x82,	0x5c, 0x00,	0x63, 0x00,	0x46, 0x00,	0x0c, 0x3c,

	0x61, 0x70,	0x62, 0x80,	0x7c, 0x05,

	0x20, 0x80,	0x28, 0x30,	0x6c, 0x00,	0x6d, 0x80,	0x6e, 0x00,	0x70, 0x02,	0x71, 0x94,	0x73, 0xc1,	0x3d, 0x34,	0x5a, 0x57,

	0x12, 0x00,

	0x17, 0x11, 0x18, 0x75,	0x19, 0x01,	0x1a, 0x97,	0x32, 0x36,	0x03, 0x0f,	0x37, 0x40,

	0x4f, 0xca,	0x50, 0xa8,	0x5a, 0x23,	0x6d, 0x00,	0x6d, 0x38,

	0xff, 0x00,	0xe5, 0x7f,	0xf9, 0xc0,	0x41, 0x24,	0xe0, 0x14,	0x76, 0xff,	0x33, 0xa0,	0x42, 0x20,	0x43, 0x18,	0x4c, 0x00,	0x87, 0xd5,	0x88, 0x3f,	0xd7, 0x03,	0xd9, 0x10,	0xd3, 0x82,

	0xc8, 0x08,	0xc9, 0x80,

	0x7c, 0x00,	0x7d, 0x00,	0x7c, 0x03,	0x7d, 0x48,	0x7d, 0x48,	0x7c, 0x08,	0x7d, 0x20,	0x7d, 0x10,	0x7d, 0x0e,

	0x90, 0x00,	0x91, 0x0e,	0x91, 0x1a,	0x91, 0x31,	0x91, 0x5a,	0x91, 0x69,	0x91, 0x75,	0x91, 0x7e,	0x91, 0x88,	0x91, 0x8f,	0x91, 0x96,	0x91, 0xa3,	0x91, 0xaf,	0x91, 0xc4,	0x91, 0xd7,	0x91, 0xe8,	0x91, 0x20,

	0x92, 0x00,	0x93, 0x06,	0x93, 0xe3,	0x93, 0x05,	0x93, 0x05,	0x93, 0x00,	0x93, 0x04,	0x93, 0x00,	0x93, 0x00,	0x93, 0x00,	0x93, 0x00,	0x93, 0x00,	0x93, 0x00,	0x93, 0x00,

	0x96, 0x00,	0x97, 0x08,	0x97, 0x19,	0x97, 0x02,	0x97, 0x0c,	0x97, 0x24,	0x97, 0x30,	0x97, 0x28,	0x97, 0x26,	0x97, 0x02,	0x97, 0x98,	0x97, 0x80,	0x97, 0x00,	0x97, 0x00,

	0xc3, 0xef,

	0xa4, 0x00,	0xa8, 0x00,	0xc5, 0x11,	0xc6, 0x51,	0xbf, 0x80,	0xc7, 0x10,	0xb6, 0x66,	0xb8, 0xA5,	0xb7, 0x64,	0xb9, 0x7C,	0xb3, 0xaf,	0xb4, 0x97,	0xb5, 0xFF,	0xb0, 0xC5,	0xb1, 0x94,	0xb2, 0x0f,	0xc4, 0x5c,

	0xc0, 0xc8,	0xc1, 0x96,	0x8c, 0x00,	0x86, 0x3d,	0x50, 0x00,	0x51, 0x90,	0x52, 0x2c,	0x53, 0x00,	0x54, 0x00,	0x55, 0x88,

	0x5a, 0x90,	0x5b, 0x2C,	0x5c, 0x05,

	0xd3, 0x02,         //DVP PCLK时钟分频系数 DVP output speed control

	0xc3, 0xed,	0x7f, 0x00,

	0xda, 0x09,

	0xe5, 0x1f,	0xe1, 0x67,	0xe0, 0x00,	0xdd, 0x7f,	0x05, 0x00,
};

/* YUV422 */
const UINT8 OV2640_YUV422RegTbl[][2]=
{
	0xFF, 0x00,	0xDA, 0x00,	0xD7, 0x03,	0xDF, 0x00,	0x33, 0x80,	0x3C, 0x40,	0xe1, 0x77,	0x00, 0x00,
};

/* JPEG */
const UINT8 OV2640_JPEGRegTbl[][2]=
{
	0xff, 0x01,	0xe0, 0x14,	0xe1, 0x77,	0xe5, 0x1f,	0xd7, 0x03,	0xda, 0x10,	0xe0, 0x00,
};

/* RGB565 */
const UINT8 OV2640_RGB565RegTbl[][2]=
{
	0xFF, 0x00,	0xDA, 0x09,	0xD7, 0x03,	0xDF, 0x02,	0x33, 0xa0,	0x3C, 0x00,	0xe1, 0x67,
	0xff, 0x01,	0xe0, 0x00,	0xe1, 0x00,	0xe5, 0x00,	0xd7, 0x00,	0xda, 0x00,	0xe0, 0x00,
};

/*********************************************************************
 * @fn      SCCB_GPIO_Init
 *
 * @brief   Init SCCB GPIO.
 *
 * @return  none
 */
void SCCB_GPIO_Init(void)
{
	IIC_SCL_OUT;
	IIC_SDA_OUT;
	IIC_SCL_SET;
	IIC_SDA_SET;
}

/*********************************************************************
 * @fn      SCCB_Start
 *
 * @brief   Start Signal
 *
 * @return  none
 */
void SCCB_Start(void)
{
	IIC_SDA_SET;
	IIC_SCL_SET;
	Delay_Us(50);
	IIC_SDA_CLR;
	Delay_Us(50);
	IIC_SCL_CLR;
}

/*********************************************************************
 * @fn      SCCB_Stop
 *
 * @brief   Stop Signal
 *
 * @return  none
 */
void SCCB_Stop(void)
{
	IIC_SDA_CLR;
	Delay_Us(50);
	IIC_SCL_SET;
	Delay_Us(50);
	IIC_SDA_SET;
	Delay_Us(50);
}

/*********************************************************************
 * @fn      SCCB_No_Ack
 *
 * @brief   NAK Signal
 *
 * @return  none
 */
void SCCB_No_Ack(void)
{
	Delay_Us(50);
	IIC_SDA_SET;
	IIC_SCL_SET;
	Delay_Us(50);
	IIC_SCL_CLR;
	Delay_Us(50);
	IIC_SDA_CLR;
	Delay_Us(50);
}

/*********************************************************************
 * @fn      SCCB_WR_Byte
 *
 * @brief   Write One Byte
 *
 * @param   data
 *
 * @return  0 - Success
 *          other - Err
 */
UINT8 SCCB_WR_Byte(UINT8 data)
{
	UINT8 i,t;

	for(i=0; i<8; i++){
		if(data & 0x80){
			IIC_SDA_SET;
		}
		else{
		    IIC_SDA_CLR;
		}

		data <<= 1;
		Delay_Us(50);
		IIC_SCL_SET;
		Delay_Us(50);
		IIC_SCL_CLR;
	}

	IIC_SDA_IN;
	Delay_Us(50);
	IIC_SCL_SET;
	Delay_Us(50);

	if(SDA_IN_R)t=1;
	else t=0;

	IIC_SCL_CLR;
	IIC_SDA_OUT;

	return t;
}

/*********************************************************************
 * @fn      SCCB_RD_Byte
 *
 * @brief   Read One Byte
 *
 * @return  Read one byte data
 */
UINT8 SCCB_RD_Byte(void)
{
	UINT8 t=0,i;

	IIC_SDA_IN;

	for(i=8; i>0; i--){
		Delay_Us(50);
		IIC_SCL_SET;
		t=t<<1;

		if(SDA_IN_R)t++;

		Delay_Us(50);
		IIC_SCL_CLR;
	}

	IIC_SDA_OUT;

	return t;
}

/*********************************************************************
 * @fn      SCCB_WR_Reg
 *
 * @brief   Write camera Register
 *
 * @param   Reg_Adr - Register address
 *          Reg_Val - Register value
 *
 * @return  0 - Success
 *          other - Err
 */
UINT8 SCCB_WR_Reg(UINT8 Reg_Adr,UINT8 Reg_Val)
{
	UINT8 res=0;

	SCCB_Start();
	if(SCCB_WR_Byte(SCCB_ID))res=1;
	Delay_Us(100);
  	if(SCCB_WR_Byte(Reg_Adr))res=1;
  	Delay_Us(100);
  	if(SCCB_WR_Byte(Reg_Val))res=1;
  	SCCB_Stop();

  	return	res;
}

/*********************************************************************
 * @fn      SCCB_RD_Reg
 *
 * @brief   Read camera Register
 *
 * @return  Camera Register value
 */
UINT8 SCCB_RD_Reg(UINT8 Reg_Adr)
{
	UINT8 val=0;

	SCCB_Start();
	SCCB_WR_Byte(SCCB_ID);
	Delay_Us(100);
  	SCCB_WR_Byte(Reg_Adr);
  	Delay_Us(100);
	SCCB_Stop();
	Delay_Us(100);

	SCCB_Start();
	SCCB_WR_Byte(SCCB_ID|0X01);
	Delay_Us(100);
  	val=SCCB_RD_Byte();
  	SCCB_No_Ack();
  	SCCB_Stop();

  	return val;
}

/*********************************************************************
 * @fn      DVP_GPIO_Init
 *
 * @brief   Init DVP GPIO.
 *
 * @return  none
 */
void DVP_GPIO_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);     //ʹ����ض˿�ʱ��

    //PC3-PC13
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3 | GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_9 | GPIO_Pin_10  ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11  ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12  ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2  ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

}

/*********************************************************************
 * @fn      OV2640_Init
 *
 * @brief   Init OV2640
 *
 * @return  0 - Success
 *          1 - Err
 */
UINT8 OV2640_Init(void)
{
	UINT16 i=0;
	UINT16 reg;

	DVP_GPIO_Init();

	OV_PWDN_CLR;                //POWER ON
 	Delay_Ms(10);
 	OV_RESET_CLR;				//Reset OV2640
	Delay_Ms(10);
	OV_RESET_SET;				//Reset End

	SCCB_GPIO_Init();
	SCCB_WR_Reg(0xFF, 0x01);	//Register Bank Select Sensor address

 	SCCB_WR_Reg(0x12, 0x80);	//Reset All Register

 	Delay_Ms(50);

	//Read MID
	reg=SCCB_RD_Reg(0x1C);
	reg<<=8;
	reg|=SCCB_RD_Reg(0x1D);

	if(reg!=OV2640_MID)
	{
		printf("MID:%08x\r\n",reg);
		return 1;
	}

	//Read PID
	reg=SCCB_RD_Reg(0x0A);
	reg<<=8;
	reg|=SCCB_RD_Reg(0x0B);

	if(reg!=OV2640_PID)
	{
		printf("PID:%08x\r\n",reg);
		return 2;
	}

	for(i=0;i<sizeof(OV2640_InitRegTbl)/2;i++)
	{
	   	SCCB_WR_Reg(OV2640_InitRegTbl[i][0],OV2640_InitRegTbl[i][1]);
 	}

  	return 0;
}

/*********************************************************************
 * @fn      RGB565_Mode_Init
 *
 * @brief   Init RGB565 mode
 *
 * @return  none
 */
void RGB565_Mode_Init(void)
{
	OV2640_RGB565_Mode();
	OV2640_OutSize_Set(OV2640_RGB565_WIDTH,OV2640_RGB565_HEIGHT);
	OV2640_Speed_Set(28,1);
	//OV2640_Auto_Exposure(4);
	OV2640_Light_Mode(0);
}

/*********************************************************************
 * @fn      JPEG_Mode_Init
 *
 * @brief   Init JPEG mode
 *
 * @return  none
 */
void JPEG_Mode_Init(void)
{
	OV2640_JPEG_Mode();
  	OV2640_OutSize_Set(OV2640_JPEG_WIDTH,OV2640_JPEG_HEIGHT);
  	OV2640_Speed_Set(30,1);
}

/*********************************************************************
 * @fn      OV2640_JPEG_Mode
 *
 * @brief   JPEG Mode
 *
 * @return  none
 */
void OV2640_JPEG_Mode(void)
{
	UINT16 i=0;

	//YUV422
	for(i=0;i<(sizeof(OV2640_YUV422RegTbl)/2);i++)
	{
		SCCB_WR_Reg(OV2640_YUV422RegTbl[i][0],OV2640_YUV422RegTbl[i][1]);
	}
	//JPEG
	for(i=0;i<(sizeof(OV2640_JPEGRegTbl)/2);i++)
	{
		SCCB_WR_Reg(OV2640_JPEGRegTbl[i][0],OV2640_JPEGRegTbl[i][1]);
	}
}

/*********************************************************************
 * @fn      OV2640_RGB565_Mode
 *
 * @brief   RGB565 Mode
 *
 * @return  none
 */
void OV2640_RGB565_Mode(void)
{
	UINT16 i=0;

	//RGB565
	for(i=0;i<(sizeof(OV2640_RGB565RegTbl)/2);i++)
	{
		SCCB_WR_Reg(OV2640_RGB565RegTbl[i][0],OV2640_RGB565RegTbl[i][1]);
	}
//	for(i=0;i<(sizeof(OV2640_YUV422RegTbl)/2);i++)
//    {
//        SCCB_WR_Reg(OV2640_YUV422RegTbl[i][0],OV2640_YUV422RegTbl[i][1]);
//    }
}

/*********************************************************************
 * @fn      OV2640_OutSize_Set
 *
 * @brief   Set Image Resolution
 *
 * @param   Image_width -
 *          Image_height -
 *
 * @return  none
 */
UINT8 OV2640_OutSize_Set(UINT16 Image_width,UINT16 Image_height)
{
	UINT16 Out_Size_Width;
	UINT16 Out_Size_Height;
	UINT8 t;

	if((Image_width%4) || (Image_height%4))return 0x01;

	Out_Size_Width=Image_width/4;
	Out_Size_Height=Image_height/4;

	SCCB_WR_Reg(0XFF,0X00);
	SCCB_WR_Reg(0XE0,0X04);
	SCCB_WR_Reg(0X5A,Out_Size_Width&0XFF);
	SCCB_WR_Reg(0X5B,Out_Size_Height&0XFF);
	t=(Out_Size_Width>>8)&0X03;
	t|=(Out_Size_Height>>6)&0X04;
	SCCB_WR_Reg(0X5C,t);
	SCCB_WR_Reg(0XE0,0X00);

	return 0;
}

/*********************************************************************
 * @fn      OV2640_Speed_Set
 *
 * @brief   Set DVP PCLK
 *
 * @param   Pclk_Div - DVP output speed ctrl
 *          Xclk_Div - Crystal oscillator input frequency division
 *
 * @return  0 - Success
 *          other - Err
 */
void OV2640_Speed_Set(UINT8 Pclk_Div, UINT8 Xclk_Div)
{
	SCCB_WR_Reg(0XFF,0X00);
	SCCB_WR_Reg(0XD3,Pclk_Div);         //设置PCLK时钟分频系数 DVP output speed control 分频系数Pclk_Div

	SCCB_WR_Reg(0XFF,0X01);
	SCCB_WR_Reg(0X11,Xclk_Div);         //CLKRC分频系数为（Xclk_Div + 1）
}

















//自动曝光设置参数表,支持5个等级
const static u8 OV2640_AUTOEXPOSURE_LEVEL[5][8]=
{
    {
        0xFF,0x01,
        0x24,0x20,
        0x25,0x18,
        0x26,0x60,
    },
    {
        0xFF,0x01,
        0x24,0x34,
        0x25,0x1c,
        0x26,0x00,
    },
    {
        0xFF,0x01,
        0x24,0x3e,
        0x25,0x38,
        0x26,0x81,
    },
    {
        0xFF,0x01,
        0x24,0x48,
        0x25,0x40,
        0x26,0x81,
    },
    {
        0xFF,0x01,
        0x24,0x58,
        0x25,0x50,
        0x26,0x92,
    },
};

//OV2640自动曝光等级设置
//level:0~4
void OV2640_Auto_Exposure(u8 level)
{
    u8 i;
    u8* p=(u8*)OV2640_AUTOEXPOSURE_LEVEL[level];
    for(i=0;i<4;i++)
    {
        SCCB_WR_Reg(p[i*2],p[i*2+1]);
    }
}

//白平衡设置
//0:自动
//1:太阳sunny
//2,阴天cloudy
//3,办公室office
//4,家里home
void OV2640_Light_Mode(u8 mode)
{
    u8 regccval=0X5E;//Sunny
    u8 regcdval=0X41;
    u8 regceval=0X54;
    switch(mode)
    {
        case 0://auto
            SCCB_WR_Reg(0XFF,0X00);
            SCCB_WR_Reg(0XC7,0X10);//AWB ON
            return;
        case 2://cloudy
            regccval=0X65;
            regcdval=0X41;
            regceval=0X4F;
            break;
        case 3://office
            regccval=0X52;
            regcdval=0X41;
            regceval=0X66;
            break;
        case 4://home
            regccval=0X42;
            regcdval=0X3F;
            regceval=0X71;
            break;
    }
    SCCB_WR_Reg(0XFF,0X00);
    SCCB_WR_Reg(0XC7,0X40); //AWB OFF
    SCCB_WR_Reg(0XCC,regccval);
    SCCB_WR_Reg(0XCD,regcdval);
    SCCB_WR_Reg(0XCE,regceval);
}

//色度设置
//0:-2
//1:-1
//2,0
//3,+1
//4,+2
void OV2640_Color_Saturation(u8 sat)
{
    u8 reg7dval=((sat+2)<<4)|0X08;
    SCCB_WR_Reg(0XFF,0X00);
    SCCB_WR_Reg(0X7C,0X00);
    SCCB_WR_Reg(0X7D,0X02);
    SCCB_WR_Reg(0X7C,0X03);
    SCCB_WR_Reg(0X7D,reg7dval);
    SCCB_WR_Reg(0X7D,reg7dval);
}

//亮度设置（曝光补偿）
//0:(0X00)-2
//1:(0X10)-1
//2,(0X20) 0
//3,(0X30)+1
//4,(0X40)+2
void OV2640_Brightness(u8 bright)
{
  SCCB_WR_Reg(0xff, 0x00);
  SCCB_WR_Reg(0x7c, 0x00);
  SCCB_WR_Reg(0x7d, 0x04);
  SCCB_WR_Reg(0x7c, 0x09);
  SCCB_WR_Reg(0x7d, bright<<4);
  SCCB_WR_Reg(0x7d, 0x00);
}

//对比度设置
//0:-2
//1:-1
//2,0
//3,+1
//4,+2
void OV2640_Contrast(u8 contrast)
{
    u8 reg7d0val=0X20;//默认为普通模式
    u8 reg7d1val=0X20;
    switch(contrast)
    {
        case 0://-2
            reg7d0val=0X18;
            reg7d1val=0X34;
            break;
        case 1://-1
            reg7d0val=0X1C;
            reg7d1val=0X2A;
            break;
        case 3://1
            reg7d0val=0X24;
            reg7d1val=0X16;
            break;
        case 4://2
            reg7d0val=0X28;
            reg7d1val=0X0C;
            break;
    }
    SCCB_WR_Reg(0xff,0x00);
    SCCB_WR_Reg(0x7c,0x00);
    SCCB_WR_Reg(0x7d,0x04);
    SCCB_WR_Reg(0x7c,0x07);
    SCCB_WR_Reg(0x7d,0x20);
    SCCB_WR_Reg(0x7d,reg7d0val);
    SCCB_WR_Reg(0x7d,reg7d1val);
    SCCB_WR_Reg(0x7d,0x06);
}

//特效设置
//0:普通模式
//1,负片
//2,黑白
//3,偏红色
//4,偏绿色
//5,偏蓝色
//6,复古
void OV2640_Special_Effects(u8 eft)
{
    u8 reg7d0val=0X00;//默认为普通模式
    u8 reg7d1val=0X80;
    u8 reg7d2val=0X80;
    switch(eft)
    {
        case 1://负片
            reg7d0val=0X40;
            break;
        case 2://黑白
            reg7d0val=0X18;
            break;
        case 3://偏红色
            reg7d0val=0X18;
            reg7d1val=0X40;
            reg7d2val=0XC0;
            break;
        case 4://偏绿色
            reg7d0val=0X18;
            reg7d1val=0X40;
            reg7d2val=0X40;
            break;
        case 5://偏蓝色
            reg7d0val=0X18;
            reg7d1val=0XA0;
            reg7d2val=0X40;
            break;
        case 6://复古
            reg7d0val=0X18;
            reg7d1val=0X40;
            reg7d2val=0XA6;
            break;
    }
    SCCB_WR_Reg(0xff,0x00);
    SCCB_WR_Reg(0x7c,0x00);
    SCCB_WR_Reg(0x7d,reg7d0val);
    SCCB_WR_Reg(0x7c,0x05);
    SCCB_WR_Reg(0x7d,reg7d1val);
    SCCB_WR_Reg(0x7d,reg7d2val);
}

//彩条测试
//sw:0,关闭彩条
//   1,开启彩条(注意OV2640的彩条是叠加在图像上面的)
void OV2640_Color_Bar(u8 sw)
{
    u8 reg;
    SCCB_WR_Reg(0XFF,0X01);
    reg=SCCB_RD_Reg(0X12);
    reg&=~(1<<1);
    if(sw)reg|=1<<1;
    SCCB_WR_Reg(0X12,reg);
}

//设置图像输出窗口
//sx,sy,起始地址
//width,height:宽度(对应:horizontal)和高度(对应:vertical)
void OV2640_Window_Set(u16 sx,u16 sy,u16 width,u16 height)
{
    u16 endx;
    u16 endy;
    u8 temp;
    endx=sx+width/2;//V*2
    endy=sy+height/2;

    SCCB_WR_Reg(0XFF,0X01);
    temp=SCCB_RD_Reg(0X03);//读取Vref之前的值
    temp&=0XF0;
    temp|=((endy&0X03)<<2)|(sy&0X03);
    SCCB_WR_Reg(0X03,temp);//设置Vref的start和end的最低2位
    SCCB_WR_Reg(0X19,sy>>2);//设置Vref的start高8位
    SCCB_WR_Reg(0X1A,endy>>2);//设置Vref的end的高8位

    temp=SCCB_RD_Reg(0X32);//读取Href之前的值
    temp&=0XC0;
    temp|=((endx&0X07)<<3)|(sx&0X07);
    SCCB_WR_Reg(0X32,temp);//设置Href的start和end的最低3位
    SCCB_WR_Reg(0X17,sx>>3);//设置Href的start高8位
    SCCB_WR_Reg(0X18,endx>>3);//设置Href的end的高8位
}

//设置图像开窗大小
//由:OV2640_ImageSize_Set确定传感器输出分辨率从大小.
//该函数则在这个范围上面进行开窗,用于OV2640_OutSize_Set的输出
//注意:本函数的宽度和高度,必须大于等于OV2640_OutSize_Set函数的宽度和高度
//     OV2640_OutSize_Set设置的宽度和高度,根据本函数设置的宽度和高度,由DSP
//     自动计算缩放比例,输出给外部设备.
//width,height:宽度(对应:horizontal)和高度(对应:vertical),width和height必须是4的倍数
//返回值:0,设置成功
//    其他,设置失败
u8 OV2640_ImageWin_Set(u16 offx,u16 offy,u16 width,u16 height)
{
    u16 hsize;
    u16 vsize;
    u8 temp;

    if(width%4)
        return 1;
    if(height%4)
        return 2;

    hsize=width/4;
    vsize=height/4;
    SCCB_WR_Reg(0XFF,0X00);
    SCCB_WR_Reg(0XE0,0X04);
    SCCB_WR_Reg(0X51,hsize&0XFF);//设置H_SIZE的低八位
    SCCB_WR_Reg(0X52,vsize&0XFF);//设置V_SIZE的低八位
    SCCB_WR_Reg(0X53,offx&0XFF);//设置offx的低八位
    SCCB_WR_Reg(0X54,offy&0XFF);//设置offy的低八位

    temp=(vsize>>1)&0X80;
    temp|=(offy>>4)&0X70;
    temp|=(hsize>>5)&0X08;
    temp|=(offx>>8)&0X07;

    SCCB_WR_Reg(0X55,temp);//设置H_SIZE/V_SIZE/OFFX,OFFY的高位
    SCCB_WR_Reg(0X57,(hsize>>2)&0X80);//设置H_SIZE/V_SIZE/OFFX,OFFY的高位
    SCCB_WR_Reg(0XE0,0X00);

    return 0;
}

//该函数设置图像尺寸大小,也就是所选格式的输出分辨率
//UXGA:1600*1200,SVGA:800*600,CIF:352*288
//width,height:图像宽度和图像高度
//返回值:0,设置成功
//    其他,设置失败
u8 OV2640_ImageSize_Set(u16 width,u16 height)
{
    u8 temp;

    SCCB_WR_Reg(0XFF,0X00);
    SCCB_WR_Reg(0XE0,0X04);
    SCCB_WR_Reg(0XC0,(width)>>3&0XFF);//设置HSIZE的10:3位
    SCCB_WR_Reg(0XC1,(height)>>3&0XFF);//设置VSIZE的10:3位

    temp=(width&0X07)<<3;
    temp|=height&0X07;
    temp|=(width>>4)&0X80;

    SCCB_WR_Reg(0X8C,temp);
    SCCB_WR_Reg(0XE0,0X00);

    return 0;
}

