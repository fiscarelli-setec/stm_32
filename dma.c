#include "stm32h7xx_hal.h"
#include "adc.h" // Include la dichiarazione di hadc1

DMA_HandleTypeDef hdma_adc1;

DMA_HandleTypeDef hdma_adc3;
void Configure_DMA1(void) {
    // Abilita il clock per DMA1
    __HAL_RCC_DMA1_CLK_ENABLE();

    // Configurazione base del DMA
    hdma_adc1.Instance = DMA1_Stream0;
    hdma_adc1.Init.Request = DMA_REQUEST_ADC1;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_HIGH;

    // Inizializza il DMA
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK) {
        // Gestisci l'errore
        while (1);
    }

    // Collega il DMA all'ADC
    __HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);
}

void Configure_DMA3(void) {
    // Abilita il clock per DMA3
    __HAL_RCC_DMA2_CLK_ENABLE();

    // Configurazione base del DMA
    hdma_adc3.Instance = DMA2_Stream0; // Assicurati che questa sia la stream corretta
    hdma_adc3.Init.Request = DMA_REQUEST_ADC3;
    hdma_adc3.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc3.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc3.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc3.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc3.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc3.Init.Mode = DMA_CIRCULAR; // Modalità circolare per uso continuo
    hdma_adc3.Init.Priority = DMA_PRIORITY_HIGH;

    // Inizializza il DMA
    if (HAL_DMA_Init(&hdma_adc3) != HAL_OK) {
        // Gestione errore
        while (1);
    }

    // Collega il DMA all'ADC3
    __HAL_LINKDMA(&hadc3, DMA_Handle, hdma_adc3);
}
