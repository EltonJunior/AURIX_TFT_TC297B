################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BaseSw/iLLD/TC29B/Tricore/Scu/Std/IfxScuCcu.c \
../src/BaseSw/iLLD/TC29B/Tricore/Scu/Std/IfxScuEru.c \
../src/BaseSw/iLLD/TC29B/Tricore/Scu/Std/IfxScuWdt.c 

OBJS += \
./src/BaseSw/iLLD/TC29B/Tricore/Scu/Std/IfxScuCcu.o \
./src/BaseSw/iLLD/TC29B/Tricore/Scu/Std/IfxScuEru.o \
./src/BaseSw/iLLD/TC29B/Tricore/Scu/Std/IfxScuWdt.o 

C_DEPS += \
./src/BaseSw/iLLD/TC29B/Tricore/Scu/Std/IfxScuCcu.d \
./src/BaseSw/iLLD/TC29B/Tricore/Scu/Std/IfxScuEru.d \
./src/BaseSw/iLLD/TC29B/Tricore/Scu/Std/IfxScuWdt.d 


# Each subdirectory must supply rules for building sources it contributes
src/BaseSw/iLLD/TC29B/Tricore/Scu/Std/%.o: ../src/BaseSw/iLLD/TC29B/Tricore/Scu/Std/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"../h" -fno-common -Os -g2 -Wall -pipe -DAPPKIT_TC297TFT -fstrict-volatile-bitfields @"C:/AURIX_TFT_Board/Default/Default.i" -fshort-double -mcpu=tc29xx -fdata-sections -ffunction-sections -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


