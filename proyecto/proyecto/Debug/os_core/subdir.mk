################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../os_core/os_core.c \
../os_core/os_dbg_r.c \
../os_core/os_flag.c \
../os_core/os_mbox.c \
../os_core/os_mem.c \
../os_core/os_mutex.c \
../os_core/os_q.c \
../os_core/os_sem.c \
../os_core/os_task.c \
../os_core/os_time.c \
../os_core/ucos_ii.c 

OBJS += \
./os_core/os_core.o \
./os_core/os_dbg_r.o \
./os_core/os_flag.o \
./os_core/os_mbox.o \
./os_core/os_mem.o \
./os_core/os_mutex.o \
./os_core/os_q.o \
./os_core/os_sem.o \
./os_core/os_task.o \
./os_core/os_time.o \
./os_core/ucos_ii.o 

C_DEPS += \
./os_core/os_core.d \
./os_core/os_dbg_r.d \
./os_core/os_flag.d \
./os_core/os_mbox.d \
./os_core/os_mem.d \
./os_core/os_mutex.d \
./os_core/os_q.d \
./os_core/os_sem.d \
./os_core/os_task.d \
./os_core/os_time.d \
./os_core/ucos_ii.d 


# Each subdirectory must supply rules for building sources it contributes
os_core/os_core.o: ../os_core/os_core.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I../../BSP/include -I../../proyecto -I../../proyecto/os_port -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"os_core/os_core.d" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

os_core/os_dbg_r.o: ../os_core/os_dbg_r.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I../../BSP/include -I../../proyecto -I../../proyecto/os_port -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"os_core/os_dbg_r.d" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

os_core/os_flag.o: ../os_core/os_flag.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I../../BSP/include -I../../proyecto/os_port -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"os_core/os_flag.d" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

os_core/os_mbox.o: ../os_core/os_mbox.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I../../BSP/include -I../../proyecto/os_port -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"os_core/os_mbox.d" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

os_core/os_mem.o: ../os_core/os_mem.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I../../BSP/include -I../../proyecto/os_port -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"os_core/os_mem.d" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

os_core/os_mutex.o: ../os_core/os_mutex.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I../../BSP/include -I../../proyecto/os_port -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"os_core/os_mutex.d" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

os_core/os_q.o: ../os_core/os_q.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I../../BSP/include -I../../proyecto/os_port -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"os_core/os_q.d" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

os_core/os_sem.o: ../os_core/os_sem.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I../../BSP/include -I../../proyecto/os_port -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"os_core/os_sem.d" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

os_core/os_task.o: ../os_core/os_task.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I../../BSP/include -I../../proyecto/os_port -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"os_core/os_task.d" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

os_core/os_time.o: ../os_core/os_time.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I../../BSP/include -I../../proyecto/os_port -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"os_core/os_time.d" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

os_core/ucos_ii.o: ../os_core/ucos_ii.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I../../BSP/include -I../../proyecto/os_port -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"os_core/ucos_ii.d" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


