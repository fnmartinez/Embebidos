################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include tp2/subdir.mk
-include tp1/subdir.mk
-include includes/lib/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Embebidos.lss \

FLASH_IMAGE += \
Embebidos.hex \

EEPROM_IMAGE += \
Embebidos.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Embebidos.elf secondary-outputs

# Tool invocations
Embebidos.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Embebidos.map -mmcu=atmega8515 -o "Embebidos.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Embebidos.lss: Embebidos.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Embebidos.elf  >"Embebidos.lss"
	@echo 'Finished building: $@'
	@echo ' '

Embebidos.hex: Embebidos.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex Embebidos.elf  "Embebidos.hex"
	@echo 'Finished building: $@'
	@echo ' '

Embebidos.eep: Embebidos.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Embebidos.elf  "Embebidos.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Embebidos.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8515 Embebidos.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) Embebidos.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
