################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../bitmap.cpp \
../camera.cpp \
../colour.cpp \
../graphics.cpp \
../heightmap.cpp \
../light.cpp 

OBJS += \
./bitmap.o \
./camera.o \
./colour.o \
./graphics.o \
./heightmap.o \
./light.o 

CPP_DEPS += \
./bitmap.d \
./camera.d \
./colour.d \
./graphics.d \
./heightmap.d \
./light.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/mikosz/work/coconutengine/utils" -I"/home/mikosz/work/coconutengine/graphics" -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


