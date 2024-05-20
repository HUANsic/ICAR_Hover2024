################################################################################
# MRS Version: 1.9.1
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Hardware/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Propeller.hex \

SECONDARY_LIST += \
Propeller.lst \

SECONDARY_SIZE += \
Propeller.siz \


# All Target
all: Propeller.elf secondary-outputs

# Tool invocations
Propeller.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "D:\CH32\Propeller\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"Propeller.map" --specs=nano.specs --specs=nosys.specs -o "Propeller.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
Propeller.hex: Propeller.elf
	@	riscv-none-embed-objcopy -O ihex "Propeller.elf"  "Propeller.hex"
	@	@
Propeller.lst: Propeller.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "Propeller.elf" > "Propeller.lst"
	@	@
Propeller.siz: Propeller.elf
	@	riscv-none-embed-size --format=berkeley "Propeller.elf"
	@	@
# Other Targets
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) Propeller.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
