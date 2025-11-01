/*
 * ECG + ADC Example using AD8232 and FRDM-RW612
 * Measures ECG signal and calculates heart rate every 10 seconds
 */

#include "fsl_debug_console.h"
#include "fsl_common.h"
#include "app.h"
#include "fsl_adc.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#define SAMPLE_COUNT    2000          // total samples in 10 seconds (200 samples/sec)
#define SAMPLE_INTERVAL_US 5000       // sampling interval = 5ms → 200Hz
#define ECG_DURATION_SEC   10
#define MIN_PEAK_DISTANCE  80
#define K_FACTOR           0.55

volatile bool g_conversionDataReady = false;
static uint16_t ecg_buffer[SAMPLE_COUNT];

void DEMO_ADC_IRQHANDLER(void)
{
    if ((ADC_GetStatusFlags(DEMO_ADC_BASE) & kADC_DataReadyInterruptFlag) != 0UL)
    {
        g_conversionDataReady = true;
        ADC_ClearStatusFlags(DEMO_ADC_BASE, kADC_DataReadyInterruptFlag);
    }
}

/* Function to count ECG peaks dynamically */
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
    return peaks;
}

/* Function to classify heart rate */
void classify_ecg(int peaks)
{
    float bpm = (peaks * 60.0f) / ECG_DURATION_SEC;
    PRINTF("\r\nDetected Peaks: %d\r\n", peaks);
    PRINTF("Calculated Heart Rate: %.1f BPM\r\n", bpm);

    if (bpm < 60.0f)
        PRINTF("ECG: Bradycardia (Slow Heart Rate)\r\n");
    else if (bpm > 100.0f)
        PRINTF("ECG: Tachycardia (Fast Heart Rate)\r\n");
    else
        PRINTF("ECG: Normal Heart Rate\r\n");

    PRINTF("---------------------------------------------\r\n");
}

int main(void)
{
    adc_config_t adcConfig;

    BOARD_InitHardware();

    PRINTF("\r\n--- ADC + ECG Peak Detection Example ---\r\n");
    PRINTF("Sampling AD8232 ECG signal for %d seconds...\r\n", ECG_DURATION_SEC);

    ADC_GetDefaultConfig(&adcConfig);
    adcConfig.vrefSource = kADC_VrefExternal;
    adcConfig.inputMode = kADC_InputSingleEnded;
    adcConfig.conversionMode = kADC_ConversionOneShot;
    adcConfig.inputGain = kADC_InputGain1;
    adcConfig.resolution = kADC_Resolution12Bit;
    adcConfig.fifoThreshold = kADC_FifoThresholdData1;
    adcConfig.averageLength = kADC_Average8;
    adcConfig.enableInputGainBuffer = true;
    adcConfig.enableADC = true;

    ADC_Init(DEMO_ADC_BASE, &adcConfig);
    ADC_ClearStatusFlags(DEMO_ADC_BASE, kADC_DataReadyInterruptFlag);
    ADC_SetScanChannel(DEMO_ADC_BASE, kADC_ScanChannel0, DEMO_ADC_CHANNEL_SOURCE);
    ADC_EnableInterrupts(DEMO_ADC_BASE, kADC_DataReadyInterruptEnable);
    EnableIRQ(DEMO_ADC_IRQn);

    if (ADC_DoAutoCalibration(DEMO_ADC_BASE, kADC_CalibrationVrefInternal) != kStatus_Success)
    {
        PRINTF("\r\nCalibration Failed!\r\n");
        return 0;
    }
    PRINTF("Calibration Success!\r\n");

    while (1)
    {
        PRINTF("\r\nCollecting ECG samples...\r\n");

        for (int i = 0; i < SAMPLE_COUNT; i++)
        {
            ADC_DoSoftwareTrigger(DEMO_ADC_BASE);
            while (!g_conversionDataReady)
                ;
            ecg_buffer[i] = ADC_GetConversionResult(DEMO_ADC_BASE);
            g_conversionDataReady = false;
            ADC_StopConversion(DEMO_ADC_BASE);
            SDK_DelayAtLeastUs(SAMPLE_INTERVAL_US, CLOCK_GetFreq(kCLOCK_CoreSysClk));
        }

        int peaks = count_peaks_auto(ecg_buffer, SAMPLE_COUNT);
        classify_ecg(peaks);
    }
}
