################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/AQM0802.c \
../Core/Src/MPU6500.c \
../Core/Src/getEquationOfStateParameters.c \
../Core/Src/getEquationOfStateParameters_initialize.c \
../Core/Src/getEquationOfStateParameters_terminate.c \
../Core/Src/getServoEquationOfStateParameters.c \
../Core/Src/getServoEquationOfStateParameters_initialize.c \
../Core/Src/getServoEquationOfStateParameters_terminate.c \
../Core/Src/kalmanFilter.c \
../Core/Src/kalmanFilter_initialize.c \
../Core/Src/kalmanFilter_terminate.c \
../Core/Src/main.c \
../Core/Src/servoStateFeedback.c \
../Core/Src/servoStateFeedback_initialize.c \
../Core/Src/servoStateFeedback_terminate.c \
../Core/Src/stateFeedback.c \
../Core/Src/stateFeedback_initialize.c \
../Core/Src/stateFeedback_terminate.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

CPP_SRCS += \
../Core/Src/ADC.cpp \
../Core/Src/Battery.cpp \
../Core/Src/Encoder.cpp \
../Core/Src/FollowingSensor.cpp \
../Core/Src/IMU.cpp \
../Core/Src/IdleStateController.cpp \
../Core/Src/InvertedControl.cpp \
../Core/Src/LineFollowign.cpp \
../Core/Src/Logger.cpp \
../Core/Src/Motor.cpp \
../Core/Src/RunningStateController.cpp \
../Core/Src/SideSensor.cpp \
../Core/Src/UI.cpp \
../Core/Src/VelocityControl.cpp \
../Core/Src/cppMain.cpp \
../Core/Src/sdCard.cpp 

C_DEPS += \
./Core/Src/AQM0802.d \
./Core/Src/MPU6500.d \
./Core/Src/getEquationOfStateParameters.d \
./Core/Src/getEquationOfStateParameters_initialize.d \
./Core/Src/getEquationOfStateParameters_terminate.d \
./Core/Src/getServoEquationOfStateParameters.d \
./Core/Src/getServoEquationOfStateParameters_initialize.d \
./Core/Src/getServoEquationOfStateParameters_terminate.d \
./Core/Src/kalmanFilter.d \
./Core/Src/kalmanFilter_initialize.d \
./Core/Src/kalmanFilter_terminate.d \
./Core/Src/main.d \
./Core/Src/servoStateFeedback.d \
./Core/Src/servoStateFeedback_initialize.d \
./Core/Src/servoStateFeedback_terminate.d \
./Core/Src/stateFeedback.d \
./Core/Src/stateFeedback_initialize.d \
./Core/Src/stateFeedback_terminate.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 

OBJS += \
./Core/Src/ADC.o \
./Core/Src/AQM0802.o \
./Core/Src/Battery.o \
./Core/Src/Encoder.o \
./Core/Src/FollowingSensor.o \
./Core/Src/IMU.o \
./Core/Src/IdleStateController.o \
./Core/Src/InvertedControl.o \
./Core/Src/LineFollowign.o \
./Core/Src/Logger.o \
./Core/Src/MPU6500.o \
./Core/Src/Motor.o \
./Core/Src/RunningStateController.o \
./Core/Src/SideSensor.o \
./Core/Src/UI.o \
./Core/Src/VelocityControl.o \
./Core/Src/cppMain.o \
./Core/Src/getEquationOfStateParameters.o \
./Core/Src/getEquationOfStateParameters_initialize.o \
./Core/Src/getEquationOfStateParameters_terminate.o \
./Core/Src/getServoEquationOfStateParameters.o \
./Core/Src/getServoEquationOfStateParameters_initialize.o \
./Core/Src/getServoEquationOfStateParameters_terminate.o \
./Core/Src/kalmanFilter.o \
./Core/Src/kalmanFilter_initialize.o \
./Core/Src/kalmanFilter_terminate.o \
./Core/Src/main.o \
./Core/Src/sdCard.o \
./Core/Src/servoStateFeedback.o \
./Core/Src/servoStateFeedback_initialize.o \
./Core/Src/servoStateFeedback_terminate.o \
./Core/Src/stateFeedback.o \
./Core/Src/stateFeedback_initialize.o \
./Core/Src/stateFeedback_terminate.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

CPP_DEPS += \
./Core/Src/ADC.d \
./Core/Src/Battery.d \
./Core/Src/Encoder.d \
./Core/Src/FollowingSensor.d \
./Core/Src/IMU.d \
./Core/Src/IdleStateController.d \
./Core/Src/InvertedControl.d \
./Core/Src/LineFollowign.d \
./Core/Src/Logger.d \
./Core/Src/Motor.d \
./Core/Src/RunningStateController.d \
./Core/Src/SideSensor.d \
./Core/Src/UI.d \
./Core/Src/VelocityControl.d \
./Core/Src/cppMain.d \
./Core/Src/sdCard.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../FATFS/Target -I../FATFS/App -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ADC.d ./Core/Src/ADC.o ./Core/Src/ADC.su ./Core/Src/AQM0802.d ./Core/Src/AQM0802.o ./Core/Src/AQM0802.su ./Core/Src/Battery.d ./Core/Src/Battery.o ./Core/Src/Battery.su ./Core/Src/Encoder.d ./Core/Src/Encoder.o ./Core/Src/Encoder.su ./Core/Src/FollowingSensor.d ./Core/Src/FollowingSensor.o ./Core/Src/FollowingSensor.su ./Core/Src/IMU.d ./Core/Src/IMU.o ./Core/Src/IMU.su ./Core/Src/IdleStateController.d ./Core/Src/IdleStateController.o ./Core/Src/IdleStateController.su ./Core/Src/InvertedControl.d ./Core/Src/InvertedControl.o ./Core/Src/InvertedControl.su ./Core/Src/LineFollowign.d ./Core/Src/LineFollowign.o ./Core/Src/LineFollowign.su ./Core/Src/Logger.d ./Core/Src/Logger.o ./Core/Src/Logger.su ./Core/Src/MPU6500.d ./Core/Src/MPU6500.o ./Core/Src/MPU6500.su ./Core/Src/Motor.d ./Core/Src/Motor.o ./Core/Src/Motor.su ./Core/Src/RunningStateController.d ./Core/Src/RunningStateController.o ./Core/Src/RunningStateController.su ./Core/Src/SideSensor.d ./Core/Src/SideSensor.o ./Core/Src/SideSensor.su ./Core/Src/UI.d ./Core/Src/UI.o ./Core/Src/UI.su ./Core/Src/VelocityControl.d ./Core/Src/VelocityControl.o ./Core/Src/VelocityControl.su ./Core/Src/cppMain.d ./Core/Src/cppMain.o ./Core/Src/cppMain.su ./Core/Src/getEquationOfStateParameters.d ./Core/Src/getEquationOfStateParameters.o ./Core/Src/getEquationOfStateParameters.su ./Core/Src/getEquationOfStateParameters_initialize.d ./Core/Src/getEquationOfStateParameters_initialize.o ./Core/Src/getEquationOfStateParameters_initialize.su ./Core/Src/getEquationOfStateParameters_terminate.d ./Core/Src/getEquationOfStateParameters_terminate.o ./Core/Src/getEquationOfStateParameters_terminate.su ./Core/Src/getServoEquationOfStateParameters.d ./Core/Src/getServoEquationOfStateParameters.o ./Core/Src/getServoEquationOfStateParameters.su ./Core/Src/getServoEquationOfStateParameters_initialize.d ./Core/Src/getServoEquationOfStateParameters_initialize.o ./Core/Src/getServoEquationOfStateParameters_initialize.su ./Core/Src/getServoEquationOfStateParameters_terminate.d ./Core/Src/getServoEquationOfStateParameters_terminate.o ./Core/Src/getServoEquationOfStateParameters_terminate.su ./Core/Src/kalmanFilter.d ./Core/Src/kalmanFilter.o ./Core/Src/kalmanFilter.su ./Core/Src/kalmanFilter_initialize.d ./Core/Src/kalmanFilter_initialize.o ./Core/Src/kalmanFilter_initialize.su ./Core/Src/kalmanFilter_terminate.d ./Core/Src/kalmanFilter_terminate.o ./Core/Src/kalmanFilter_terminate.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/sdCard.d ./Core/Src/sdCard.o ./Core/Src/sdCard.su ./Core/Src/servoStateFeedback.d ./Core/Src/servoStateFeedback.o ./Core/Src/servoStateFeedback.su ./Core/Src/servoStateFeedback_initialize.d ./Core/Src/servoStateFeedback_initialize.o ./Core/Src/servoStateFeedback_initialize.su ./Core/Src/servoStateFeedback_terminate.d ./Core/Src/servoStateFeedback_terminate.o ./Core/Src/servoStateFeedback_terminate.su ./Core/Src/stateFeedback.d ./Core/Src/stateFeedback.o ./Core/Src/stateFeedback.su ./Core/Src/stateFeedback_initialize.d ./Core/Src/stateFeedback_initialize.o ./Core/Src/stateFeedback_initialize.su ./Core/Src/stateFeedback_terminate.d ./Core/Src/stateFeedback_terminate.o ./Core/Src/stateFeedback_terminate.su ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

