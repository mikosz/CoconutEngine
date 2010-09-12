################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../button.cpp \
../eventhandler.cpp \
../gameview.cpp \
../positioneduielement.cpp \
../uielementfactory.cpp \
../window.cpp 

OBJS += \
./button.o \
./eventhandler.o \
./gameview.o \
./positioneduielement.o \
./uielementfactory.o \
./window.o 

CPP_DEPS += \
./button.d \
./eventhandler.d \
./gameview.d \
./positioneduielement.d \
./uielementfactory.d \
./window.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/mikosz/work/coconutengine/core" -I"/home/mikosz/work/coconutengine/ui" -I"/home/mikosz/work/coconutengine/utils" -I"/home/mikosz/work/coconutengine/graphics" -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


