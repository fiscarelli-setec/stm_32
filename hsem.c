#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_hsem.h"

void HSEM_Init(void) {
    __HAL_RCC_HSEM_CLK_ENABLE(); // Abilita il clock per HSEM
}

uint8_t HSEM_Acquire(uint8_t sem_id) {
    return HAL_HSEM_FastTake(sem_id) == HAL_OK;
}

void HSEM_Release(uint8_t sem_id) {
    HAL_HSEM_Release(sem_id, 0);
}
