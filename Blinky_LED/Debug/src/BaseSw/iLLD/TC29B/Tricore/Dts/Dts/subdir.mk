################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BaseSw/iLLD/TC29B/Tricore/Dts/Dts/IfxDts_Dts.c 

OBJS += \
./src/BaseSw/iLLD/TC29B/Tricore/Dts/Dts/IfxDts_Dts.o 

C_DEPS += \
./src/BaseSw/iLLD/TC29B/Tricore/Dts/Dts/IfxDts_Dts.d 


# Each subdirectory must supply rules for building sources it contributes
src/BaseSw/iLLD/TC29B/Tricore/Dts/Dts/%.o: ../src/BaseSw/iLLD/TC29B/Tricore/Dts/Dts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"../h" -fno-common -Os -g2 -Wall -pipe -DAPPKIT_TC297TFT -fstrict-volatile-bitfields @"C:/AURIX_TFT_Board/Blinky_LED/Default.i" -fshort-double -mcpu=tc29xx -fdata-sections -ffunction-sections -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


