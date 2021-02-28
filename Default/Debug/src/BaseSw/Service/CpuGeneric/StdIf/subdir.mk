################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.c \
../src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_Pos.c \
../src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_PwmHl.c \
../src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_Timer.c 

OBJS += \
./src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.o \
./src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_Pos.o \
./src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_PwmHl.o \
./src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_Timer.o 

C_DEPS += \
./src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.d \
./src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_Pos.d \
./src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_PwmHl.d \
./src/BaseSw/Service/CpuGeneric/StdIf/IfxStdIf_Timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/BaseSw/Service/CpuGeneric/StdIf/%.o: ../src/BaseSw/Service/CpuGeneric/StdIf/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"../h" -fno-common -Os -g2 -Wall -pipe -DAPPKIT_TC297TFT -fstrict-volatile-bitfields @"C:/AURIX_TFT_Board/Default/Default.i" -fshort-double -mcpu=tc29xx -fdata-sections -ffunction-sections -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


