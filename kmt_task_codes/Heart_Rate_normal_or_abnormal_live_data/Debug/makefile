################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/str/subdir.mk
-include utilities/debug_console_lite/subdir.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include flash_config/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/els_pkc/src/comps/mcuxCsslParamIntegrity/src/subdir.mk
-include component/els_pkc/src/comps/mcuxCsslMemory/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClMemory/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClEls/src/subdir.mk
-include component/els_pkc/src/comps/mcuxClBuffer/src/subdir.mk
-include board/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Heart_Rate_normal_or_abnormal_live_data
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: Heart_Rate_normal_or_abnormal_live_data.axf

# Tool invocations
Heart_Rate_normal_or_abnormal_live_data.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -Xlinker -no-warn-rwx-segments -Xlinker -Map="Heart_Rate_normal_or_abnormal_live_data.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m33+nodsp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -T "Heart_Rate_normal_or_abnormal_live_data_Debug.ld" -o "Heart_Rate_normal_or_abnormal_live_data.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Heart_Rate_normal_or_abnormal_live_data.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Heart_Rate_normal_or_abnormal_live_data.axf"; # arm-none-eabi-objcopy -v -O binary "Heart_Rate_normal_or_abnormal_live_data.axf" "Heart_Rate_normal_or_abnormal_live_data.bin" ; # checksum -p RW612 -d "Heart_Rate_normal_or_abnormal_live_data.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
