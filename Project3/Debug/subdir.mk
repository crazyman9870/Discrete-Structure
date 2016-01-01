################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DatalogProgram.cpp \
../Parameter.cpp \
../Parser.cpp \
../Predicate.cpp \
../Rule.cpp \
../Scanner.cpp \
../Token.cpp \
../main3.cpp 

OBJS += \
./DatalogProgram.o \
./Parameter.o \
./Parser.o \
./Predicate.o \
./Rule.o \
./Scanner.o \
./Token.o \
./main3.o 

CPP_DEPS += \
./DatalogProgram.d \
./Parameter.d \
./Parser.d \
./Predicate.d \
./Rule.d \
./Scanner.d \
./Token.d \
./main3.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


