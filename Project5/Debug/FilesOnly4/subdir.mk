################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../FilesOnly4/DatalogProgram.cpp \
../FilesOnly4/Parameter.cpp \
../FilesOnly4/Parser.cpp \
../FilesOnly4/Predicate.cpp \
../FilesOnly4/Rule.cpp \
../FilesOnly4/Scanner.cpp \
../FilesOnly4/Token.cpp \
../FilesOnly4/main3.cpp 

OBJS += \
./FilesOnly4/DatalogProgram.o \
./FilesOnly4/Parameter.o \
./FilesOnly4/Parser.o \
./FilesOnly4/Predicate.o \
./FilesOnly4/Rule.o \
./FilesOnly4/Scanner.o \
./FilesOnly4/Token.o \
./FilesOnly4/main3.o 

CPP_DEPS += \
./FilesOnly4/DatalogProgram.d \
./FilesOnly4/Parameter.d \
./FilesOnly4/Parser.d \
./FilesOnly4/Predicate.d \
./FilesOnly4/Rule.d \
./FilesOnly4/Scanner.d \
./FilesOnly4/Token.d \
./FilesOnly4/main3.d 


# Each subdirectory must supply rules for building sources it contributes
FilesOnly4/%.o: ../FilesOnly4/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


