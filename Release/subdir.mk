################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../arducar.cpp \
../color.cpp 

LINK_OBJ += \
./arducar.cpp.o \
./color.cpp.o 

CPP_DEPS += \
./arducar.cpp.d \
./color.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
arducar.cpp.o: ../arducar.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/pau/eclipse/cpp-2020-12/Eclipse.app/Contents/Eclipse//arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"/Users/pau/eclipse/cpp-2020-12/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.8.3/cores/arduino" -I"/Users/pau/eclipse/cpp-2020-12/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.8.3/variants/mega" -I"/Users/pau/eclipse/cpp-2020-12/Eclipse.app/Contents/Eclipse/arduinoPlugin/libraries/Plotter/2.4.1/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

color.cpp.o: ../color.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/Users/pau/eclipse/cpp-2020-12/Eclipse.app/Contents/Eclipse//arduinoPlugin/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10812 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR     -I"/Users/pau/eclipse/cpp-2020-12/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.8.3/cores/arduino" -I"/Users/pau/eclipse/cpp-2020-12/Eclipse.app/Contents/Eclipse/arduinoPlugin/packages/arduino/hardware/avr/1.8.3/variants/mega" -I"/Users/pau/eclipse/cpp-2020-12/Eclipse.app/Contents/Eclipse/arduinoPlugin/libraries/Plotter/2.4.1/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

