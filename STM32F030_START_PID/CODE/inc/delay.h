#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f0xx.h"

#define F_CPU 48000000UL
#define TimerTick		F_CPU/1000

/****************************************************************************/

void Delay_Init(void);
void Delay_ms(uint32_t dlyTicks);
void Delay_us(uint32_t us);

#endif /* _DELAY_H_ */
