################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/dvp.c \
../Hardware/ov.c \
../Hardware/propeller.c \
../Hardware/uart5.c 

OBJS += \
./Hardware/dvp.o \
./Hardware/ov.o \
./Hardware/propeller.o \
./Hardware/uart5.o 

C_DEPS += \
./Hardware/dvp.d \
./Hardware/ov.d \
./Hardware/propeller.d \
./Hardware/uart5.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/%.o: ../Hardware/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"D:\CH32\Propeller\Debug" -I"D:\CH32\Propeller\Hardware" -I"D:\CH32\Propeller\Core" -I"D:\CH32\Propeller\User" -I"D:\CH32\Propeller\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

