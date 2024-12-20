#ifndef HSEM_H
#define HSEM_H

#include <stdint.h>
void HSEM_Init(void);
uint8_t HSEM_Acquire(uint8_t sem_id);
void HSEM_Release(uint8_t sem_id);

#endif // HSEM_H
