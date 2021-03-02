################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AppSw/Tricore/Main/Cpu0_Main.c \
../src/AppSw/Tricore/Main/Cpu1_Main.c \
../src/AppSw/Tricore/Main/Cpu2_Main.c 

OBJS += \
./src/AppSw/Tricore/Main/Cpu0_Main.o \
./src/AppSw/Tricore/Main/Cpu1_Main.o \
./src/AppSw/Tricore/Main/Cpu2_Main.o 

C_DEPS += \
./src/AppSw/Tricore/Main/Cpu0_Main.d \
./src/AppSw/Tricore/Main/Cpu1_Main.d \
./src/AppSw/Tricore/Main/Cpu2_Main.d 


# Each subdirectory must supply rules for building sources it contributes
src/AppSw/Tricore/Main/%.o: ../src/AppSw/Tricore/Main/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"../h" -fno-common -Os -g2 -Wall -pipe -DAPPKIT_TC297TFT -fstrict-volatile-bitfields @"C:/AURIX_TFT_Board/02_Blinky_LED/Default.i" -fshort-double -mcpu=tc29xx -fdata-sections -ffunction-sections -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


