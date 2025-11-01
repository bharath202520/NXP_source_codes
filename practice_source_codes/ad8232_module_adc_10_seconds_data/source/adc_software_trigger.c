
/*
* Copyright 2020, 2023 NXP
* All rights reserved.
*
* SPDX-License-Identifier: BSD-3-Clause
*/

// AD8232 ECG module connected to RW612 ADC input (e.g., GPIO_43)

#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "app.h"
#include "fsl_adc.h"

/*******************************************************************************
* Definitions
******************************************************************************/

/*******************************************************************************
* Variables
******************************************************************************/
volatile bool g_conversionDataReady = false;
volatile uint32_t g_systickCounter = 0;

/*******************************************************************************
* Prototypes
******************************************************************************/
void SysTick_Handler(void);
uint32_t GetTicks(void);

/*******************************************************************************
* Code
******************************************************************************/

/* SysTick interrupt handler – runs every 1 ms */
void SysTick_Handler(void)
{
   g_systickCounter++;
}

/* Return the current tick count in milliseconds */
uint32_t GetTicks(void)
{
   return g_systickCounter;
}

/* ADC interrupt handler */
void DEMO_ADC_IRQHANDLER(void)
{
   if ((ADC_GetStatusFlags(DEMO_ADC_BASE) & kADC_DataReadyInterruptFlag) != 0UL)
   {
       g_conversionDataReady = true;
       ADC_ClearStatusFlags(DEMO_ADC_BASE, kADC_DataReadyInterruptFlag);
   }
}

int main(void)
{
   adc_config_t adcConfig;

   BOARD_InitHardware();

   PRINTF("\r\nADC Software Trigger Example!\r\n");
   PRINTF("Resolution: 12-bit\r\n");
   PRINTF("Input Mode: Single-Ended\r\n");
   PRINTF("Input Range: 0V to 1.2V\r\n");

   /* Configure SysTick to generate interrupt every 1 ms */
   if (SysTick_Config(SystemCoreClock / 1000U))
   {
       PRINTF("SysTick configuration failed!\r\n");
       while (1);
   }

   /* Initialize ADC configuration */
   ADC_GetDefaultConfig(&adcConfig);
   adcConfig.vrefSource            = kADC_VrefExternal;   // Use external 1.2 V ref (for AD8232)
   adcConfig.inputMode             = kADC_InputSingleEnded;
   adcConfig.conversionMode        = kADC_ConversionOneShot;
   adcConfig.inputGain             = kADC_InputGain1;
   adcConfig.resolution            = kADC_Resolution12Bit;
   adcConfig.fifoThreshold         = kADC_FifoThresholdData1;
   adcConfig.averageLength         = kADC_Average8;
   adcConfig.enableInputGainBuffer = true;
   adcConfig.enableADC             = true;
   adcConfig.enableInputBufferChop = false;

   ADC_Init(DEMO_ADC_BASE, &adcConfig);

   /* Calibrate ADC */
   if (ADC_DoAutoCalibration(DEMO_ADC_BASE, kADC_CalibrationVrefInternal) != kStatus_Success)
   {
       PRINTF("\r\nCalibration Failed!\r\n");
       return 0;
   }

   PRINTF("\r\nCalibration Success!\r\n");

   ADC_ClearStatusFlags(DEMO_ADC_BASE, kADC_DataReadyInterruptFlag);
   ADC_SetScanChannel(DEMO_ADC_BASE, kADC_ScanChannel0, DEMO_ADC_CHANNEL_SOURCE);
   ADC_EnableInterrupts(DEMO_ADC_BASE, kADC_DataReadyInterruptEnable);
   EnableIRQ(DEMO_ADC_IRQn);

   PRINTF("\r\nStarting 10-second ADC capture...\r\n");

   /* Get start time */
   uint32_t startTicks = GetTicks();

   while ((GetTicks() - startTicks) < 10000U)  // Run for 10 s
   {
       ADC_DoSoftwareTrigger(DEMO_ADC_BASE);
       uint16_t data = ADC_GetConversionResult(DEMO_ADC_BASE);
       PRINTF("%d,", data);   // Print ADC value
       g_conversionDataReady = false;

       ADC_StopConversion(DEMO_ADC_BASE);
       SDK_DelayAtLeastUs(1000, CLOCK_GetFreq(kCLOCK_CoreSysClk)); // 5 ms delay
   }

   PRINTF("\r\n10-second data capture completed!\r\n");

   while (1)
   {
       // Idle loop
   }
}

