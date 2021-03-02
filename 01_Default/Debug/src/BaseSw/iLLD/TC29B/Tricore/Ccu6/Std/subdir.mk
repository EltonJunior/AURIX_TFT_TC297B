################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BaseSw/iLLD/TC29B/Tricore/Ccu6/Std/IfxCcu6.c 

OBJS += \
./src/BaseSw/iLLD/TC29B/Tricore/Ccu6/Std/IfxCcu6.o 

C_DEPS += \
./src/BaseSw/iLLD/TC29B/Tricore/Ccu6/Std/IfxCcu6.d 


# Each subdirectory must supply rules for building sources it contributes
src/BaseSw/iLLD/TC29B/Tricore/Ccu6/Std/%.o: ../src/BaseSw/iLLD/TC29B/Tricore/Ccu6/Std/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"../h" -fno-common -Os -g2 -Wall -pipe -DAPPKIT_TC297TFT -fstrict-volatile-bitfields @"C:/AURIX_TFT_Board/Default/Default.i" -fshort-double -mcpu=tc29xx -fdata-sections -ffunction-sections -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


