################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../framework/SerialManager/Source/UART_Adapter/UART_Adapter.c 

OBJS += \
./framework/SerialManager/Source/UART_Adapter/UART_Adapter.o 

C_DEPS += \
./framework/SerialManager/Source/UART_Adapter/UART_Adapter.d 


# Each subdirectory must supply rules for building sources it contributes
framework/SerialManager/Source/UART_Adapter/%.o: ../framework/SerialManager/Source/UART_Adapter/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -DCPU_MKW41Z512VHT4 -DFSL_RTOS_FREE_RTOS -DFRDM_KW41Z -DFREEDOM -DCPU_MKW41Z512VHT4_cm0plus -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I../board -I../source -I../ -I../framework/OSAbstraction/Interface -I../framework/common -I../freertos -I../ieee_802.15.4/mac/source/App -I../ieee_802.15.4/mac/interface -I../ieee_802.15.4/phy/interface -I../framework/GPIO -I../framework/Keyboard/Interface -I../framework/TimersManager/Interface -I../framework/TimersManager/Source -I../framework/LED/Interface -I../framework/SerialManager/Source/SPI_Adapter -I../framework/SerialManager/Source/UART_Adapter -I../framework/SerialManager/Source/I2C_Adapter -I../framework/Flash/Internal -I../framework/MemManager/Interface -I../framework/Lists -I../framework/Messaging/Interface -I../framework/Panic/Interface -I../framework/RNG/Interface -I../framework/SerialManager/Interface -I../framework/ModuleInfo -I../framework/FunctionLib -I../framework/SecLib -I../framework/MWSCoexistence/Interface -I../drivers -I../CMSIS -I../utilities -I../framework/DCDC/Interface -I../framework/XCVR/MKW41Z4 -I../ieee_802.15.4/phy/source/MKW41Z -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -imacros "C:/Embebidos/Redes/frdmkw41z_wireless_examples_ieee_802_15_4_mwa_coordinator_freertos_ejemploClase/source/app_preinclude.h" -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


