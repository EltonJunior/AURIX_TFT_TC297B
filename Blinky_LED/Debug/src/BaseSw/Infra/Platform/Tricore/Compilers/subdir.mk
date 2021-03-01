################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerDcc.c \
../src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerGhs.c \
../src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerGnuc.c \
../src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerTasking.c 

OBJS += \
./src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerDcc.o \
./src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerGhs.o \
./src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerGnuc.o \
./src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerTasking.o 

C_DEPS += \
./src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerDcc.d \
./src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerGhs.d \
./src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerGnuc.d \
./src/BaseSw/Infra/Platform/Tricore/Compilers/CompilerTasking.d 


# Each subdirectory must supply rules for building sources it contributes
src/BaseSw/Infra/Platform/Tricore/Compilers/%.o: ../src/BaseSw/Infra/Platform/Tricore/Compilers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"../h" -fno-common -Os -g2 -Wall -pipe -DAPPKIT_TC297TFT -fstrict-volatile-bitfields @"C:/AURIX_TFT_Board/Blinky_LED/Default.i" -fshort-double -mcpu=tc29xx -fdata-sections -ffunction-sections -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


