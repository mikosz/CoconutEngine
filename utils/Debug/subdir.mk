################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../frustum.cpp \
../log.cpp \
../octree.cpp \
../plane.cpp \
../propertiesfilesettings.cpp \
../timemanager.cpp \
../vector3d.cpp 

OBJS += \
./frustum.o \
./log.o \
./octree.o \
./plane.o \
./propertiesfilesettings.o \
./timemanager.o \
./vector3d.o 

CPP_DEPS += \
./frustum.d \
./log.d \
./octree.d \
./plane.d \
./propertiesfilesettings.d \
./timemanager.d \
./vector3d.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/mikosz/work/coconutengine/utils" -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -pthreads -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


