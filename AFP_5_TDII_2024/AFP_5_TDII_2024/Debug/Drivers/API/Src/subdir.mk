################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/Src/API_Alarm.c \
../Drivers/API/Src/API_Debounce.c \
../Drivers/API/Src/API_Delay.c \
../Drivers/API/Src/API_Display.c \
../Drivers/API/Src/API_GPIO.c \
../Drivers/API/Src/API_System.c \
../Drivers/API/Src/API_i2c.c \
../Drivers/API/Src/API_keypad_4x4.c \
../Drivers/API/Src/Globals.c 

OBJS += \
./Drivers/API/Src/API_Alarm.o \
./Drivers/API/Src/API_Debounce.o \
./Drivers/API/Src/API_Delay.o \
./Drivers/API/Src/API_Display.o \
./Drivers/API/Src/API_GPIO.o \
./Drivers/API/Src/API_System.o \
./Drivers/API/Src/API_i2c.o \
./Drivers/API/Src/API_keypad_4x4.o \
./Drivers/API/Src/Globals.o 

C_DEPS += \
./Drivers/API/Src/API_Alarm.d \
./Drivers/API/Src/API_Debounce.d \
./Drivers/API/Src/API_Delay.d \
./Drivers/API/Src/API_Display.d \
./Drivers/API/Src/API_GPIO.d \
./Drivers/API/Src/API_System.d \
./Drivers/API/Src/API_i2c.d \
./Drivers/API/Src/API_keypad_4x4.d \
./Drivers/API/Src/Globals.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/Src/%.o Drivers/API/Src/%.su Drivers/API/Src/%.cyclo: ../Drivers/API/Src/%.c Drivers/API/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/ASUS/STM32CubeIDE/AFP4/PD-V2/Drivers/API/Inc" -I"C:/Users/ASUS/STM32CubeIDE/AFP4/PD-V2/Drivers/API/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-API-2f-Src

clean-Drivers-2f-API-2f-Src:
	-$(RM) ./Drivers/API/Src/API_Alarm.cyclo ./Drivers/API/Src/API_Alarm.d ./Drivers/API/Src/API_Alarm.o ./Drivers/API/Src/API_Alarm.su ./Drivers/API/Src/API_Debounce.cyclo ./Drivers/API/Src/API_Debounce.d ./Drivers/API/Src/API_Debounce.o ./Drivers/API/Src/API_Debounce.su ./Drivers/API/Src/API_Delay.cyclo ./Drivers/API/Src/API_Delay.d ./Drivers/API/Src/API_Delay.o ./Drivers/API/Src/API_Delay.su ./Drivers/API/Src/API_Display.cyclo ./Drivers/API/Src/API_Display.d ./Drivers/API/Src/API_Display.o ./Drivers/API/Src/API_Display.su ./Drivers/API/Src/API_GPIO.cyclo ./Drivers/API/Src/API_GPIO.d ./Drivers/API/Src/API_GPIO.o ./Drivers/API/Src/API_GPIO.su ./Drivers/API/Src/API_System.cyclo ./Drivers/API/Src/API_System.d ./Drivers/API/Src/API_System.o ./Drivers/API/Src/API_System.su ./Drivers/API/Src/API_i2c.cyclo ./Drivers/API/Src/API_i2c.d ./Drivers/API/Src/API_i2c.o ./Drivers/API/Src/API_i2c.su ./Drivers/API/Src/API_keypad_4x4.cyclo ./Drivers/API/Src/API_keypad_4x4.d ./Drivers/API/Src/API_keypad_4x4.o ./Drivers/API/Src/API_keypad_4x4.su ./Drivers/API/Src/Globals.cyclo ./Drivers/API/Src/Globals.d ./Drivers/API/Src/Globals.o ./Drivers/API/Src/Globals.su

.PHONY: clean-Drivers-2f-API-2f-Src

