################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BaseSw/iLLD/TC29B/Tricore/Cpu/CStart/IfxCpu_CStart0.c \
../src/BaseSw/iLLD/TC29B/Tricore/Cpu/CStart/IfxCpu_CStart1.c \
../src/BaseSw/iLLD/TC29B/Tricore/Cpu/CStart/IfxCpu_CStart2.c 

OBJS += \
./src/BaseSw/iLLD/TC29B/Tricore/Cpu/CStart/IfxCpu_CStart0.o \
./src/BaseSw/iLLD/TC29B/Tricore/Cpu/CStart/IfxCpu_CStart1.o \
./src/BaseSw/iLLD/TC29B/Tricore/Cpu/CStart/IfxCpu_CStart2.o 

C_DEPS += \
./src/BaseSw/iLLD/TC29B/Tricore/Cpu/CStart/IfxCpu_CStart0.d \
./src/BaseSw/iLLD/TC29B/Tricore/Cpu/CStart/IfxCpu_CStart1.d \
./src/BaseSw/iLLD/TC29B/Tricore/Cpu/CStart/IfxCpu_CStart2.d 


# Each subdirectory must supply rules for building sources it contributes
src/BaseSw/iLLD/TC29B/Tricore/Cpu/CStart/%.o: ../src/BaseSw/iLLD/TC29B/Tricore/Cpu/CStart/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"../h" -fno-common -Os -g2 -Wall -pipe -DAPPKIT_TC297TFT -fstrict-volatile-bitfields @"C:/AURIX_TFT_Board/02_Blinky_LED/Default.i" -fshort-double -mcpu=tc29xx -fdata-sections -ffunction-sections -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


