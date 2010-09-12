################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../accelerationaction.cpp \
../actiondispatcher.cpp \
../actor.cpp \
../cameramoveaction.cpp \
../core.cpp \
../game.cpp \
../gamescreen.cpp \
../map.cpp \
../player.cpp 

OBJS += \
./accelerationaction.o \
./actiondispatcher.o \
./actor.o \
./cameramoveaction.o \
./core.o \
./game.o \
./gamescreen.o \
./map.o \
./player.o 

CPP_DEPS += \
./accelerationaction.d \
./actiondispatcher.d \
./actor.d \
./cameramoveaction.d \
./core.d \
./game.d \
./gamescreen.d \
./map.d \
./player.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/mikosz/work/coconutengine/ui" -I"/home/mikosz/work/coconutengine/core" -I"/home/mikosz/work/coconutengine/graphics" -I"/home/mikosz/work/coconutengine/utils" -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


