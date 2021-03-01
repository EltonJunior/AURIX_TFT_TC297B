################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm.c \
../src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Atom.c \
../src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Cmu.c \
../src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Dpll.c \
../src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tbu.c \
../src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tim.c \
../src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tom.c 

OBJS += \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm.o \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Atom.o \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Cmu.o \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Dpll.o \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tbu.o \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tim.o \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tom.o 

C_DEPS += \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm.d \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Atom.d \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Cmu.d \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Dpll.d \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tbu.d \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tim.d \
./src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tom.d 


# Each subdirectory must supply rules for building sources it contributes
src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/%.o: ../src/BaseSw/iLLD/TC29B/Tricore/Gtm/Std/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TriCore C Compiler'
	"$(TRICORE_TOOLS)/bin/tricore-gcc" -c -I"../h" -fno-common -Os -g2 -Wall -pipe -DAPPKIT_TC297TFT -fstrict-volatile-bitfields @"C:/AURIX_TFT_Board/Blinky_LED/Default.i" -fshort-double -mcpu=tc29xx -fdata-sections -ffunction-sections -mversion-info -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


