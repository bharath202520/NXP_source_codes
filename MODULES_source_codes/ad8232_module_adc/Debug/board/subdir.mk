################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/hardware_init.c \
../board/pin_mux.c 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/hardware_init.d \
./board/pin_mux.d 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/hardware_init.o \
./board/pin_mux.o 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c board/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_RW612ETA2I -DCPU_RW612ETA2I_cm33_nodsp -DMCUXPRESSO_SDK -DFSL_SDK_DRIVER_QUICK_ACCESS_ENABLE=1 -DSDK_DEBUGCONSOLE=1 -DMCUX_META_BUILD -DRW612_SERIES -DBOOT_HEADER_ENABLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\source" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\flash_config" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\drivers" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\CMSIS" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\CMSIS\m-profile" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\device" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\device\periph" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\utilities" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\utilities\str" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\utilities\debug_console_lite" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\uart" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxClBuffer\inc" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxClBuffer\inc\internal" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxClCore\inc" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxClEls\inc" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxClEls\inc\internal" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxClMemory\inc" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxClMemory\inc\internal" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxCsslMemory\inc" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxCsslMemory\inc\internal" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxCsslCPreProcessor\inc" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxCsslDataIntegrity\inc" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxCsslFlowProtection\inc" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxCsslParamIntegrity\inc" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\comps\mcuxCsslSecureCounter\inc" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\compiler" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\platforms\rw61x" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\src\platforms\rw61x\inc" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\component\els_pkc\includes\platform\rw61x" -I"C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\board" -O0 -fno-common -g3 -gdwarf-4 -c -ffunction-sections -fdata-sections -fno-builtin -mcpu=cortex-m33+nodsp -imacros "C:\Users\admin\Downloads\FRDM_RW612_NXP_Controller-main\FRDM_RW612_NXP_Controller-main\ADC_Examples\frdmrw612_adc_ad8232_signals\source\mcux_config.h" -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m33+nodsp -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board

clean-board:
	-$(RM) ./board/board.d ./board/board.o ./board/clock_config.d ./board/clock_config.o ./board/hardware_init.d ./board/hardware_init.o ./board/pin_mux.d ./board/pin_mux.o

.PHONY: clean-board

