################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \

TOOLCHAIN_PATH := /mnt/c/Users/Giovanni/repos/DroneTheory/SingleTests/ToolChainDownloadTest/.env/gcc-arm-none-eabi-10.3-2021.10/bin/

BUILD_ARTIFACT_NAME := MacCompilation
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
MacCompilation.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
MacCompilation.list \

OBJCOPY_BIN += \
MacCompilation.bin \


# All Target
all: main-build

# Main-build Target
main-build: MacCompilation.elf secondary-outputs

# Tool invocations
MacCompilation.elf: $(OBJS) $(USER_OBJS) /Users/giovannirasera/repos/DroneTheory/SingleTests/STM32CubeIDETest/MacCompilation/STM32F446RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	$(TOOLCHAIN_PATH)arm-none-eabi-g++ -o "MacCompilation.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/Users/giovannirasera/repos/DroneTheory/SingleTests/STM32CubeIDETest/MacCompilation/STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="MacCompilation.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	$(TOOLCHAIN_PATH)arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

MacCompilation.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	$(TOOLCHAIN_PATH)arm-none-eabi-objdump -h -S $(EXECUTABLES) > "MacCompilation.list"
	@echo 'Finished building: $@'
	@echo ' '

MacCompilation.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	$(TOOLCHAIN_PATH)arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "MacCompilation.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) MacCompilation.bin MacCompilation.elf MacCompilation.list default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
