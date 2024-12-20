#include "stm32h7xx_hal.h"
#include "system_stm32h7xx.h"
#include "adc.h"
#include "dma.h"
#include "hsem.h"
#include <stdio.h>

#define ADC_BUFFER_SIZE 64
volatile uint16_t adc1_buffer[ADC_BUFFER_SIZE];

// Dichiarazioni delle funzioni
void SystemClock_Config(void);
void Process_ADC_Data(volatile uint16_t *buffer, uint32_t size);

int main(void) {
    HAL_Init();
    SystemClock_Config();

    Configure_ADC1();
    Configure_DMA1();

    // Avvia la conversione ADC con DMA
    Start_ADC_DMA(&hadc1, (uint32_t*)adc1_buffer, ADC_BUFFER_SIZE);

    while (1) {
        if (HSEM_Acquire(0)) {
            // Processa i dati raccolti
            Process_ADC_Data(adc1_buffer, ADC_BUFFER_SIZE);
            HSEM_Release(0);
        }
    }

    return 0;
}

void Process_ADC_Data(volatile uint16_t *buffer, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        printf("ADC Value[%lu]: %u\n", i, buffer[i]);
    }
}

void HAL_ADCEx_EndOfSamplingCallback(ADC_HandleTypeDef *hadc) {
    // Gestione completamento conversione
}

void HAL_ADCEx_LevelOutOfWindow3Callback(ADC_HandleTypeDef *hadc) {
    // Gestione livello fuori finestra
}

void HAL_ADCEx_InjectedQueueOverflowCallback(ADC_HandleTypeDef *hadc) {
    // Gestione overflow
}

void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc) {
    // Gestione completamento conversione iniettata
}

void HAL_ADCEx_LevelOutOfWindow2Callback(ADC_HandleTypeDef *hadc) {
    // Gestione del livello fuori finestra per ADC2
}