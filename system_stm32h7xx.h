#ifndef SYSTEM_STM32H7XX_H
#define SYSTEM_STM32H7XX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Variabili globali per il clock */
extern uint32_t SystemCoreClock;      /*!< Clock del processore (Core Clock) */
extern uint32_t SystemD2Clock;        /*!< Clock del dominio D2 */
extern const uint8_t D1CorePrescTable[16]; /*!< Tabella dei divisori */

/* Funzioni di configurazione del sistema */
void SystemInit(void);
void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_STM32H7XX_H */
