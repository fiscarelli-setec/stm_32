#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "hsem.h"
#include "system_stm32h7xx.h"

#define ADC_BUFFER_SIZE 64
volatile uint16_t adc3_buffer[ADC_BUFFER_SIZE];

// Dichiarazioni delle funzioni
void SystemClock_Config(void);
#include <stdio.h>

void Process_ADC_Data(volatile uint16_t *buffer, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        printf("ADC3 Value[%lu]: %u\n", i, buffer[i]);
    }
}


int main(void) {
    // Inizializzazione HAL
    HAL_Init();

    // Configura il clock di sistema
    SystemClock_Config();

    // Configurazione ADC3 e DMA3
    Configure_ADC3();
    Configure_DMA3();

    // Avvia la conversione ADC con DMA
    Start_ADC_DMA(&hadc3, (uint32_t*)adc3_buffer, ADC_BUFFER_SIZE);

    while (1) {
        if (HSEM_Acquire(0)) {
            // Processa i dati raccolti da ADC3
            Process_ADC_Data(adc3_buffer, ADC_BUFFER_SIZE);
            HSEM_Release(0);
        }
    }
    return 0;
}

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc) {
    // Callback per conversione completata (vuota se non necessaria)
}

void HAL_ADCEx_EndOfSamplingCallback(ADC_HandleTypeDef *hadc) {
    // Callback per fine campionamento
}

void HAL_ADCEx_LevelOutOfWindow2Callback(ADC_HandleTypeDef *hadc) {
    // Callback per livello fuori finestra (vuota se non necessaria)
}

void HAL_ADCEx_LevelOutOfWindow3Callback(ADC_HandleTypeDef *hadc) {
    // Callback per livello fuori finestra (vuota se non necessaria)
}

void HAL_ADCEx_InjectedQueueOverflowCallback(ADC_HandleTypeDef *hadc) {
    // Callback per overflow della coda (vuota se non necessaria)
}

