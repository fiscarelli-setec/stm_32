#include "stm32h7xx_hal.h"
#include "adc.h"
ADC_HandleTypeDef hadc1;

ADC_HandleTypeDef hadc3;
void Configure_ADC1(void) {
    __HAL_RCC_ADC12_CLK_ENABLE(); // Abilita il clock per ADC1

    // Configura i parametri base di ADC1
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc1.Init.ContinuousConvMode = ENABLE; // Modalità continua
    hadc1.Init.Overrun = ADC_OVR_DATA_PRESERVED; // Sovrascrittura
    hadc1.Init.NbrOfConversion = 1; // Numero di conversioni
    HAL_ADC_Init(&hadc1);

    // Configura il canale ADC (ad esempio, canale 1)
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

void Configure_ADC3(void) {
    __HAL_RCC_ADC3_CLK_ENABLE(); // Abilita il clock per ADC3

    // Configurazione base di ADC3
    hadc3.Instance = ADC3;
    hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadc3.Init.Resolution = ADC_RESOLUTION_12B;
    hadc3.Init.ScanConvMode = ADC_SCAN_ENABLE;
    hadc3.Init.ContinuousConvMode = ENABLE; // Modalità continua
    hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    hadc3.Init.Overrun = ADC_OVR_DATA_PRESERVED; // Sovrascrittura dati
    hadc3.Init.NbrOfConversion = 1; // Una sola conversione regolare per ciclo

    if (HAL_ADC_Init(&hadc3) != HAL_OK) {
        // Gestisci l'errore
        while (1);
    }

    // Configurazione del canale ADC
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_3; // Canale da usare (adatta alle tue esigenze)
    sConfig.Rank = ADC_REGULAR_RANK_1; // Prima posizione nella sequenza regolare
    sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;

    if (HAL_ADC_ConfigChannel(&hadc3, &sConfig) != HAL_OK) {
        // Gestisci l'errore
        while (1);
    }
}
void Start_ADC_DMA(ADC_HandleTypeDef *hadc, uint32_t *buffer, uint32_t size) {
    HAL_ADC_Start_DMA(hadc, buffer, size);
}
