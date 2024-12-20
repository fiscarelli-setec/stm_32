#ifndef ADC_H
#define ADC_H

#include "stm32h7xx_hal.h"

extern ADC_HandleTypeDef hadc1; // Dichiarazione esterna di hadc1
extern ADC_HandleTypeDef hadc3;
void Configure_ADC1(void);
void Configure_ADC3(void);
void Start_ADC_DMA(ADC_HandleTypeDef *hadc, uint32_t *buffer, uint32_t size);

#endif // ADC_H
