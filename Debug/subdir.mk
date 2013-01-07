################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../luces.c \
../matematicas.c \
../material.c \
../modelado.c \
../otras_escenas.c \
../revolucion.c \
../texturas.c 

OBJS += \
./luces.o \
./matematicas.o \
./material.o \
./modelado.o \
./otras_escenas.o \
./revolucion.o \
./texturas.o 

C_DEPS += \
./luces.d \
./matematicas.d \
./material.d \
./modelado.d \
./otras_escenas.d \
./revolucion.d \
./texturas.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include -I/usr/lib/gcc/x86_64-linux-gnu/4.7/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


