#include <dvp.h>
#include <OLED.h>
#include "huansic_util.h"
#include "huansic_motor.h"

/* DVP Work Mode */
#define RGB565_MODE   0
/* DVP Work Mode Selection */
#define DVP_Work_Mode    RGB565_MODE

uint32_t fps_count;

uint16_t threhold=25;

UINT32  JPEG_DVPDMAaddr0 = 0x20005000;
UINT32  JPEG_DVPDMAaddr1 = 0x20005000 + OV2640_JPEG_WIDTH;

//UINT32  RGB565_DVPDMAaddr0 = 0x2000A000;
//UINT32  RGB565_DVPDMAaddr1 = 0x2000A000 + RGB565_COL_NUM;

uint8_t Image_data[2][RGB565_COL_NUM];
UINT32  RGB565_DVPDMAaddr0 = (uint32_t)Image_data[0];
UINT32  RGB565_DVPDMAaddr1 = (uint32_t)Image_data[1];

uint8_t Image_Gray[IMGH][IMGW];
uint32_t Image_Gray_Address = (uint32_t)Image_Gray;
uint8_t Image_Bin[IMGH][IMGW];
uint32_t Image_Bin_Address = (uint32_t)Image_Bin;


volatile UINT32 frame_cnt = 0;
volatile UINT32 addr_cnt = 0;       //当前列数
volatile UINT32 href_cnt = 0;       //当前行数

volatile uint8_t reading_flag = 0;

uint32_t get_fps_count(){
    return fps_count;
}

void binarization(){
    for(uint16_t i = 0; i < IMGH; i++){
        for(uint16_t j = 0; j < IMGW; j++){
            if(Image_Gray[i][j] > threhold){
                Image_Bin[i][j] = 1;
            }
            else Image_Bin[i][j] = 0;
        }
    }
}

void DVP_IRQHandler (void) __attribute__((interrupt("WCH-Interrupt-fast")));

void DVP_Init(void){
    NVIC_InitTypeDef NVIC_InitStructure={0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DVP, ENABLE);

    DVP->CR0 &= ~RB_DVP_MSK_DAT_MOD;            //8位模式

    /* VSYNC銆丠SYNC - High level active */
    DVP->CR0 |= RB_DVP_D8_MOD | RB_DVP_V_POLAR; //VSYNC高电平数据有效
    DVP->CR1 &= ~((RB_DVP_ALL_CLR)| RB_DVP_RCV_CLR);    //取消接收逻辑、标志、FIFO复位
    DVP->ROW_NUM = RGB565_ROW_NUM;               // rows
    DVP->COL_NUM = RGB565_COL_NUM;               // cols

    DVP->DMA_BUF0 = RGB565_DVPDMAaddr0;      //DMA addr0
    DVP->DMA_BUF1 = RGB565_DVPDMAaddr1;      //DMA addr1

    /* Set frame capture rate */
    DVP->CR1 &= ~RB_DVP_FCRC;
    DVP->CR1 |= DVP_RATE_100P;  //帧率分频100%

    //Interupt Enable
    DVP->IER |= RB_DVP_IE_STP_FRM;
    DVP->IER |= RB_DVP_IE_FIFO_OV;
    DVP->IER |= RB_DVP_IE_FRM_DONE;
    DVP->IER |= RB_DVP_IE_ROW_DONE;
    DVP->IER |= RB_DVP_IE_STR_FRM;

    NVIC_InitStructure.NVIC_IRQChannel = DVP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    DVP->CR1 |= RB_DVP_DMA_EN;  //enable DMA
    DVP->CR0 |= RB_DVP_ENABLE;  //enable DVP
}

u32 DVP_ROW_cnt=0;

/*********************************************************************
 * @fn      DVP_IRQHandler
 *
 * @brief   This function handles DVP exception.
 *
 * @return  none
 */
void DVP_IRQHandler(void){
    huansic_led5_turn();
    if (DVP->IFR & RB_DVP_IF_ROW_DONE){      //行结束中断
        DVP->IFR &= ~RB_DVP_IF_ROW_DONE;  //clear Interrupt
//        DVP->CR0 &= ~RB_DVP_ENABLE;  //disable DVP
        if (addr_cnt%2){     //buf1 done
            addr_cnt++;
            for(int i=0;i<OV2640_RGB565_WIDTH;i+=5){
                if(!(href_cnt%5)){
                    Image_Gray[OV2640_RGB565_WIDTH/5 - i/5][href_cnt/5] = GetGray_RGB565(1, i);
                    if(GetGray_RGB565(1, i) > 25){
//                        OLED_DrawPoint(href_cnt/5, OV2640_RGB565_WIDTH/5 - i/5);
                    }
                }
            }
            //DVP->DMA_BUF1 += RGB565_COL_NUM * 2;
        }
        else{                //buf0 done
            addr_cnt++;
            for(int i=0;i<OV2640_RGB565_WIDTH;i+=5){
                if(!(href_cnt%5)){
                    Image_Gray[OV2640_RGB565_WIDTH/5 - i/5][href_cnt/5] = GetGray_RGB565(0, i);
                    if(GetGray_RGB565(0, i) > 25){
//                        OLED_DrawPoint(href_cnt/5, OV2640_RGB565_WIDTH/5 - i/5);
                    }
                }
            }
            //DVP->DMA_BUF0 += RGB565_COL_NUM * 2;
        }
//        DVP->CR0 |= RB_DVP_ENABLE;  //enable DVP
        href_cnt++;         //行计数器加1
    }

    if (DVP->IFR & RB_DVP_IF_FRM_DONE){      //帧接收完成中断
        DVP->IFR &= ~RB_DVP_IF_FRM_DONE;  //clear Interrupt
        DVP->DMA_BUF0 = RGB565_DVPDMAaddr0;      //DMA addr0
        DVP->DMA_BUF1 = RGB565_DVPDMAaddr1;      //DMA addr1
        addr_cnt = 0;
        href_cnt = 0;
//        DVP->CR0 &= ~RB_DVP_ENABLE;  //disable DVP
//        OLED_Update();
//        OLED_Clear();
        fps_count++;
//        DVP->CR0 |= RB_DVP_ENABLE;  //enable DVP
        reading_flag = 0;
    }

    if (DVP->IFR & RB_DVP_IF_STR_FRM){       //帧开始中断
        DVP->IFR &= ~RB_DVP_IF_STR_FRM;  //clear Interrupt
        frame_cnt++;                        //帧数计数器加1
        reading_flag = 1;
    }

    if (DVP->IFR & RB_DVP_IF_STP_FRM){       //帧结束中断标志
        DVP->IFR &= ~RB_DVP_IF_STP_FRM;
    }

    if (DVP->IFR & RB_DVP_IF_FIFO_OV){       //接收 FIFO 溢出中断标志
        DVP->IFR &= ~RB_DVP_IF_FIFO_OV;
        printf("FIFO OV\r\n");
    }
}

uint8_t GetReadingFlag(){
    return reading_flag;
}


u8 GetGray_RGB565(u8 href, u8 row){
    u16 r, g, b;
    u8 gray, buf0, buf1;
    u32 address = RGB565_DVPDMAaddr0 + href * RGB565_COL_NUM + row * 2;

//    if((RGB565_DVPDMAaddr0 + href * RGB565_COL_NUM + row * 2) % 4) address += 2;
//    else address -= 2;

    //DVP->CR0 &= ~RB_DVP_ENABLE;  //disable DVP

    buf0 = *(u8*)(address + 1);
    buf1 = *(u8*)address;

//    buf0 = buf0 << 2;
//    buf1 = buf1 << 2;

    r = (buf0) >> 3;
    g = (((buf0) & 0x07) << 3) + (((buf1) & 0xE0) >> 5);
    b = ((buf1) & 0x1F);
    gray = (r*38 + g*75 + b*15) >> 7;

    //DVP->CR0 |= RB_DVP_ENABLE;  //enable DVP
    return gray;
}


u8 GetGray_YUV422(u8 href, u8 row){
    u8 gray;
    u32 address = RGB565_DVPDMAaddr0 + href * RGB565_COL_NUM + row * 2;
    DVP->CR0 &= ~RB_DVP_ENABLE;  //disable DVP
    gray = *(u8*)address;
    DVP->CR0 |= RB_DVP_ENABLE;  //enable DVP
    return gray;
}

