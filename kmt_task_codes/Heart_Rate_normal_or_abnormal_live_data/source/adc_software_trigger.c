//
///*
//* Copyright 2020, 2023 NXP
//* All rights reserved.
//*
//* SPDX-License-Identifier: BSD-3-Clause
//*/
//
//// AD8232 ECG module connected to RW612 ADC input (e.g., GPIO_43)
//
//#include "fsl_debug_console.h"
//#include "fsl_common.h"
//#include "app.h"
//#include "fsl_adc.h"
//
///*******************************************************************************
//* Definitions
//******************************************************************************/
//
///*******************************************************************************
//* Variables
//******************************************************************************/
//volatile bool g_conversionDataReady = false;
//volatile uint32_t g_systickCounter = 0;
//
///*******************************************************************************
//* Prototypes
//******************************************************************************/
//void SysTick_Handler(void);
//uint32_t GetTicks(void);
//
///*******************************************************************************
//* Code
//******************************************************************************/
//
///* SysTick interrupt handler – runs every 1 ms */
//void SysTick_Handler(void)
//{
//   g_systickCounter++;
//}
//
///* Return the current tick count in milliseconds */
//uint32_t GetTicks(void)
//{
//   return g_systickCounter;
//}
//
///* ADC interrupt handler */
//void DEMO_ADC_IRQHANDLER(void)
//{
//   if ((ADC_GetStatusFlags(DEMO_ADC_BASE) & kADC_DataReadyInterruptFlag) != 0UL)
//   {
//       g_conversionDataReady = true;
//       ADC_ClearStatusFlags(DEMO_ADC_BASE, kADC_DataReadyInterruptFlag);
//   }
//}
//
//int main(void)
//{
//   adc_config_t adcConfig;
//
//   BOARD_InitHardware();
//
//   PRINTF("\r\nADC Software Trigger Example!\r\n");
//   PRINTF("Resolution: 12-bit\r\n");
//   PRINTF("Input Mode: Single-Ended\r\n");
//   PRINTF("Input Range: 0V to 1.2V\r\n");
//
//   /* Configure SysTick to generate interrupt every 1 ms */
//   if (SysTick_Config(SystemCoreClock / 1000U))
//   {
//       PRINTF("SysTick configuration failed!\r\n");
//       while (1);
//   }
//
//   /* Initialize ADC configuration */
//   ADC_GetDefaultConfig(&adcConfig);
//   adcConfig.vrefSource            = kADC_VrefExternal;   // Use external 1.2 V ref (for AD8232)
//   adcConfig.inputMode             = kADC_InputSingleEnded;
//   adcConfig.conversionMode        = kADC_ConversionOneShot;
//   adcConfig.inputGain             = kADC_InputGain1;
//   adcConfig.resolution            = kADC_Resolution12Bit;
//   adcConfig.fifoThreshold         = kADC_FifoThresholdData1;
//   adcConfig.averageLength         = kADC_Average8;
//   adcConfig.enableInputGainBuffer = true;
//   adcConfig.enableADC             = true;
//   adcConfig.enableInputBufferChop = false;
//
//   ADC_Init(DEMO_ADC_BASE, &adcConfig);
//
//   /* Calibrate ADC */
//   if (ADC_DoAutoCalibration(DEMO_ADC_BASE, kADC_CalibrationVrefInternal) != kStatus_Success)
//   {
//       PRINTF("\r\nCalibration Failed!\r\n");
//       return 0;
//   }
//
//   PRINTF("\r\nCalibration Success!\r\n");
//
//   ADC_ClearStatusFlags(DEMO_ADC_BASE, kADC_DataReadyInterruptFlag);
//   ADC_SetScanChannel(DEMO_ADC_BASE, kADC_ScanChannel0, DEMO_ADC_CHANNEL_SOURCE);
//   ADC_EnableInterrupts(DEMO_ADC_BASE, kADC_DataReadyInterruptEnable);
//   EnableIRQ(DEMO_ADC_IRQn);
//
//   PRINTF("\r\nStarting 10-second ADC capture...\r\n");
//
//   /* Get start time */
//   uint32_t startTicks = GetTicks();
//
//   while ((GetTicks() - startTicks) < 10000U)  // Run for 10 s
//   {
//       ADC_DoSoftwareTrigger(DEMO_ADC_BASE);
//       uint16_t data = ADC_GetConversionResult(DEMO_ADC_BASE);
//       PRINTF("%d,", data);   // Print ADC value
//       g_conversionDataReady = false;
//
//       ADC_StopConversion(DEMO_ADC_BASE);
//       SDK_DelayAtLeastUs(1000, CLOCK_GetFreq(kCLOCK_CoreSysClk)); // 5 ms delay
//   }
//
//   PRINTF("\r\n10-second data capture completed!\r\n");
//
//   while (1)
//   {
//       // Idle loop
//   }
//}





























/*
 * Copyright 2020, 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "app.h"
#include "fsl_adc.h"
#include <math.h>

/*******************************************************************************
 * Configuration
 ******************************************************************************/
#define SAMPLE_INTERVAL_US   5000          // 5ms per sample -> 200 samples/sec
#define ECG_DURATION_SEC     10            // Collect 10 seconds of data
#define MIN_PEAK_DISTANCE    80            // Minimum samples between peaks
#define K_FACTOR             2.0f          // Peak detection threshold sensitivity
#define TOTAL_SAMPLES        ((1000000 / SAMPLE_INTERVAL_US) * ECG_DURATION_SEC)

/*******************************************************************************
 * Globals
 ******************************************************************************/
volatile bool g_conversionDataReady = false;
uint16_t ecgBuffer[TOTAL_SAMPLES];   // ECG samples storage

/*******************************************************************************
 * ADC IRQ Handler
 ******************************************************************************/
void DEMO_ADC_IRQHANDLER(void)
{
    if ((ADC_GetStatusFlags(DEMO_ADC_BASE) & kADC_DataReadyInterruptFlag) != 0UL)
    {
        g_conversionDataReady = true;
        ADC_ClearStatusFlags(DEMO_ADC_BASE, kADC_DataReadyInterruptFlag);
    }
}

/*******************************************************************************
 * ECG Peak Detection
 ******************************************************************************/
int count_peaks_auto(const uint16_t *ecg, int length)
{
    long sum = 0;
    for (int i = 0; i < length; i++)
        sum += ecg[i];

    float mean = (float)sum / length;
    float variance = 0;
    for (int i = 0; i < length; i++)
        variance += powf((ecg[i] - mean), 2);
    variance /= length;
    float std_dev = sqrtf(variance);

    int threshold = (int)(mean + (K_FACTOR * std_dev));

    int peaks = 0;
    int last_peak_index = -MIN_PEAK_DISTANCE;

    for (int i = 1; i < length - 1; i++)
    {
        if (ecg[i] > threshold && ecg[i] > ecg[i - 1] && ecg[i] > ecg[i + 1])
        {
            if (i - last_peak_index > MIN_PEAK_DISTANCE)
            {
                peaks++;
                last_peak_index = i;
            }
        }
    }

    PRINTF("Mean=%.2f, StdDev=%.2f, Threshold=%d, Peaks=%d\r\n", mean, std_dev, threshold, peaks);
    return peaks;
}

/*******************************************************************************
 * Heart Rate Classification
 ******************************************************************************/
void classify_ecg(int peaks)
{
    float bpm = (peaks * 60.0f) / ECG_DURATION_SEC;

    PRINTF("Detected Peaks: %d\r\n", peaks);
    PRINTF("Calculated Heart Rate: %.1f BPM\r\n", bpm);

    if (bpm < 60.0f)
        PRINTF("Condition: Bradycardia (Slow HR)\r\n\r\n");
    else if (bpm > 100.0f)
        PRINTF("Condition: Tachycardia (Fast HR)\r\n\r\n");
    else
        PRINTF("Condition: Normal Heart Rate\r\n\r\n");
}

/*******************************************************************************
 * Main Function
 ******************************************************************************/
int main(void)
{
    adc_config_t adcConfig;
    BOARD_InitHardware();

    PRINTF("\r\n--- Live ECG Heart Rate Detection using AD8232 ---\r\n");
    PRINTF("Sampling Rate: 200 Hz | Duration: %d s | Resolution: 12-bit\r\n", ECG_DURATION_SEC);

    /* Configure ADC */
    ADC_GetDefaultConfig(&adcConfig);
    adcConfig.vrefSource            = kADC_Vref1P2V;
    adcConfig.inputMode             = kADC_InputSingleEnded;
    adcConfig.conversionMode        = kADC_ConversionOneShot;
    adcConfig.inputGain             = kADC_InputGain1;
    adcConfig.resolution            = kADC_Resolution12Bit;
    adcConfig.fifoThreshold         = kADC_FifoThresholdData1;
    adcConfig.averageLength         = kADC_Average16;
    adcConfig.enableInputGainBuffer = true;
    adcConfig.enableADC             = true;
    adcConfig.enableInputBufferChop = false;

    ADC_Init(DEMO_ADC_BASE, &adcConfig);

    if (ADC_DoAutoCalibration(DEMO_ADC_BASE, kADC_CalibrationVrefInternal) != kStatus_Success)
    {
        PRINTF("ADC Calibration Failed!\r\n");
        return 0;
    }

    ADC_ClearStatusFlags(DEMO_ADC_BASE, kADC_DataReadyInterruptFlag);
    ADC_SetScanChannel(DEMO_ADC_BASE, kADC_ScanChannel0, DEMO_ADC_CHANNEL_SOURCE);
    ADC_EnableInterrupts(DEMO_ADC_BASE, kADC_DataReadyInterruptEnable);
    EnableIRQ(DEMO_ADC_IRQn);

    while (1)
    {
        PRINTF("\r\n--- Collecting ECG data for %d seconds ---\r\n", ECG_DURATION_SEC);
        for (int i = 0; i < TOTAL_SAMPLES; i++)
        {
            ADC_DoSoftwareTrigger(DEMO_ADC_BASE);
            while (!g_conversionDataReady)
                ; // wait for ADC
            g_conversionDataReady = false;

            ecgBuffer[i] = ADC_GetConversionResult(DEMO_ADC_BASE);
            ADC_StopConversion(DEMO_ADC_BASE);

            SDK_DelayAtLeastUs(SAMPLE_INTERVAL_US, CLOCK_GetFreq(kCLOCK_CoreSysClk));
        }

        PRINTF("Data collection complete! Analyzing...\r\n");

        int peaks = count_peaks_auto(ecgBuffer, TOTAL_SAMPLES);
        classify_ecg(peaks);

        // Optional: show a few sample values
        PRINTF("First 10 ECG samples: ");
        for (int i = 0; i < 10; i++)
            PRINTF("%d ", ecgBuffer[i]);
        PRINTF("\r\n----------------------------------------\r\n");

        // Loop repeats: new 10-second ECG window starts
    }
}


