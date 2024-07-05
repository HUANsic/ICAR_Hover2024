#include <opt.h>

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

void opt_init() {
    opt_gpio_init();

}

opt_data_typedef get_opt_data() {
    opt_data.front_dx = fopt_read_reg(REG_DELTA_X);
    opt_data.front_dy = fopt_read_reg(REG_DELTA_Y);
    opt_data.rear_dx = ropt_read_reg(REG_DELTA_X);
    opt_data.rear_dy = ropt_read_reg(REG_DELTA_Y);
//    opt_data.front_dx = -17;
//    opt_data.front_dy = 34;
//    opt_data.rear_dx = -17;
//    opt_data.rear_dy = 34;
    return opt_data;
}

