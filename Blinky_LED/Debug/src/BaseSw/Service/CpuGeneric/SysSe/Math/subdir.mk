################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_AngleTrkF32.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_Cf32.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_Crc.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32_BitReverseTable.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32_TwiddleTable.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_IntegralF32.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LowPassPt1F32.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutAtan2F32.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutAtan2F32_Table.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutLSincosF32.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutLinearF32.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutSincosF32.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutSincosF32_Table.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_RampF32.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_WndF32_BlackmanHarrisTable.c \
../src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_WndF32_HannTable.c 

OBJS += \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_AngleTrkF32.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_Cf32.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_Crc.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32_BitReverseTable.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32_TwiddleTable.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_IntegralF32.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LowPassPt1F32.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutAtan2F32.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutAtan2F32_Table.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutLSincosF32.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutLinearF32.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutSincosF32.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutSincosF32_Table.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_RampF32.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_WndF32_BlackmanHarrisTable.o \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_WndF32_HannTable.o 

C_DEPS += \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_AngleTrkF32.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_Cf32.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_Crc.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32_BitReverseTable.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_FftF32_TwiddleTable.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_IntegralF32.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LowPassPt1F32.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutAtan2F32.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutAtan2F32_Table.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutLSincosF32.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutLinearF32.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutSincosF32.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_LutSincosF32_Table.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_RampF32.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_WndF32_BlackmanHarrisTable.d \
./src/BaseSw/Service/CpuGeneric/SysSe/Math/Ifx_WndF32_HannTable.d 


# Each subdirectory must supply rules for building sources it contributes
src/BaseSw/Service/CpuGeneric/SysSe/Math/%.o: ../src/BaseSw/Service/CpuGeneric/SysSe/Math/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"../h" -fno-common -Os -g2 -Wall -pipe -DAPPKIT_TC297TFT -fstrict-volatile-bitfields @"C:/AURIX_TFT_Board/Blinky_LED/Default.i" -fshort-double -mcpu=tc29xx -fdata-sections -ffunction-sections -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


