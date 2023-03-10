################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := cmsis_rcc_systick_gpio_0.v
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
cmsis_rcc_systick_gpio_0.v.elf \

MAP_FILES += \
cmsis_rcc_systick_gpio_0.v.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
cmsis_rcc_systick_gpio_0.v.list \

OBJCOPY_HEX += \
cmsis_rcc_systick_gpio_0.v.hex \


# All Target
all: main-build

# Main-build Target
main-build: cmsis_rcc_systick_gpio_0.v.elf secondary-outputs

# Tool invocations
cmsis_rcc_systick_gpio_0.v.elf cmsis_rcc_systick_gpio_0.v.map: $(OBJS) $(USER_OBJS) C:\Users\DimaBez\STM32CubeIDE\workspace_1.11.2\cmsis_rcc_systick_gpio_0.v\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "cmsis_rcc_systick_gpio_0.v.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\DimaBez\STM32CubeIDE\workspace_1.11.2\cmsis_rcc_systick_gpio_0.v\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="cmsis_rcc_systick_gpio_0.v.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

cmsis_rcc_systick_gpio_0.v.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "cmsis_rcc_systick_gpio_0.v.list"
	@echo 'Finished building: $@'
	@echo ' '

cmsis_rcc_systick_gpio_0.v.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "cmsis_rcc_systick_gpio_0.v.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) cmsis_rcc_systick_gpio_0.v.elf cmsis_rcc_systick_gpio_0.v.hex cmsis_rcc_systick_gpio_0.v.list cmsis_rcc_systick_gpio_0.v.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
