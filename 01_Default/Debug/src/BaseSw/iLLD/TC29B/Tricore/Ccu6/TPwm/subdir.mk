################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BaseSw/iLLD/TC29B/Tricore/Ccu6/TPwm/IfxCcu6_TPwm.c 

OBJS += \
./src/BaseSw/iLLD/TC29B/Tricore/Ccu6/TPwm/IfxCcu6_TPwm.o 

C_DEPS += \
./src/BaseSw/iLLD/TC29B/Tricore/Ccu6/TPwm/IfxCcu6_TPwm.d 


# Each subdirectory must supply rules for building sources it contributes
src/BaseSw/iLLD/TC29B/Tricore/Ccu6/TPwm/%.o: ../src/BaseSw/iLLD/TC29B/Tricore/Ccu6/TPwm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"../h" -fno-common -Os -g2 -Wall -pipe -DAPPKIT_TC297TFT -fstrict-volatile-bitfields @"C:/AURIX_TFT_Board/Default/Default.i" -fshort-double -mcpu=tc29xx -fdata-sections -ffunction-sections -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


