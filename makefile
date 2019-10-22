# PES Project Three Makefile
# Tristan Duenas
# References:
# https://github.com/ErichStyger/mcuoneclipse/blob/master/Examples/MCUXpresso/FRDM-KL25Z/MyMakeProject/makefile

############################
# Command for removing files
RM := rm -rf

############################
# Compiler
CC := arm-none-eabi-gcc

############################
# Linker
LL := arm-none-eabi-gcc

############################
# Binary/exectable to build
EXE := \
  ./debug/ECEN5813_Project_3.axf
 
############################
# List of object files
OBJS := \
  ./debug/main.o \
  ./debug/allocate_words.o \
  ./debug/free_words.o \
  ./debug/display_memory.o \
  ./debug/write_memory.o \
  ./debug/invert_block.o \
  ./debug/write_pattern.o \
  ./debug/gen_pattern.o \
  ./debug/verify_pattern.o \
  ./debug/get_address.o \
  ./debug/logger.o \
  ./debug/led_control.o \
  ./debug/timing_control.o \
  ./debug/mtb.o \
  ./debug/semihost_hardfault.o \
  ./debug/fsl_clock.o \
  ./debug/fsl_common.o \
  ./debug/fsl_flash.o \
  ./debug/fsl_gpio.o \
  ./debug/fsl_lpsci.o \
  ./debug/fsl_smc.o \
  ./debug/fsl_uart.o \
  ./debug/fsl_debug_console.o \
  ./debug/board.o \
  ./debug/clock_config.o \
  ./debug/peripherals.o \
  ./debug/pin_mux.o \
  ./debug/system_MKL25Z4.o \
  ./debug/startup_mkl25z4.o

############################
# List of dependency files
C_DEPS = \
  ./debug/main.d \
  ./debug/allocate_words.d \
  ./debug/free_words.d \
  ./debug/display_memory.d \
  ./debug/write_memory.d \
  ./debug/invert_block.d \
  ./debug/write_pattern.d \
  ./debug/verify_patter.d \
  ./debug/gen_pattern.d \
  ./debug/get_address.d \
  ./debug/logger.d \
  ./debug/led_control.d \
  ./debug/timing_control.d \
  ./debug/mtb.d \
  ./debug/semihost_hardfault.d \
  ./debug/fsl_clock.d \
  ./debug/fsl_common.d \
  ./debug/fsl_flash.d \
  ./debug/fsl_gpio.d \
  ./debug/fsl_lpsci.d \
  ./debug/fsl_smc.d \
  ./debug/fsl_uart.d \
  ./debug/fsl_debug_console.d \
  ./debug/board.d \
  ./debug/clock_config.d \
  ./debug/peripherals.d \
  ./debug/pin_mux.d \
  ./debug/system_MKL25Z4.d \
  ./debug/startup_mkl25z4.d
 
############################
# Include generated dependcy files (only if not clean target)
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

############################
# Compiler options
fb_run: CC_OPTIONS := -c -DFB_RUN -std=gnu99 -O0 -g -ffunction-sections -fdata-sections -fno-builtin -mcpu=cortex-m0plus -mthumb -DCPU_MKL25Z128VLK4 -D__USE_CMSIS -I"startup" -I"CMSIS" -I"source" -I"board" -I"drivers" -I"utilities"
fb_debug: CC_OPTIONS := -c -DFB_DEBUG -std=gnu99 -O0 -g -ffunction-sections -fdata-sections -fno-builtin -mcpu=cortex-m0plus -mthumb -DCPU_MKL25Z128VLK4 -D__USE_CMSIS -I"startup" -I"CMSIS" -I"source" -I"board" -I"drivers" -I"utilities"

############################
# Linker Options
LL_OPTIONS := -nostdlib -Xlinker -Map="debug/ECEN5813_Project_3.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m0plus -mthumb -T ECEN5813_Project_3_Debug.ld -o $(EXE)

############################
# Main (all) target
all:
# Referenced https://www.cmcrossroads.com/article/making-directories-gnu-make
fb_run: $(EXE)
	@echo "*** finished building ***"
fb_debug: $(EXE)
	@echo "*** finished building ***"
pc_run: 
	gcc source/main.c source/led_control.c source/timing_control.c source/allocate_words.c source/free_words.c source/display_memory.c source/write_memory.c source/invert_block.c source/write_pattern.c source/gen_pattern.c source/verify_pattern.c source/logger.c source/get_address.c -o debug/pc_run.exe -DPC_RUN -std=c99 -Wall -Werror
pc_debug:
	gcc source/main.c source/led_control.c source/timing_control.c source/allocate_words.c source/free_words.c source/display_memory.c source/write_memory.c source/invert_block.c source/write_pattern.c source/gen_pattern.c source/verify_pattern.c source/logger.c source/get_address.c -o  debug/pc_debug.exe -DPC_DEBUG -std=c99 -Wall -Werror

############################
# Clean target
clean:
	-$(RM) ./debug/*
	-@echo ' '

############################
# Rule to link the executable
$(EXE): $(OBJS) $(USER_OBJS) ECEN5813_Project_3_Debug.ld
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(LL) $(LL_OPTIONS) $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	
############################
# Rule to build the files in the source folder
./debug/%.o: ./source/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
############################
# Rule to build the files in the CMSIS folder
./debug/%.o: ./CMSIS/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
############################
# Rule to build the files in the startup folder
./debug/%.o: ./startup/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

############################
# Rule to build the files in the board folder
./debug/%.o: ./board/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

############################
# Rule to build the files in the drivers folder
./debug/%.o: ./drivers/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
############################
# Rule to build the files in the utilities folder
./debug/%.o: ./utilities/%.c
	@echo 'Building file: $<'
	$(CC) $(CC_OPTIONS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
