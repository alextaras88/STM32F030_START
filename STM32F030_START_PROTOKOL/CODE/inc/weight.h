#ifndef _WEIGHT_H_
#define _WEIGHT_H_

#include "stm32f0xx.h"

#include "delay.h"
#include "ads1220.h"


int32_t ads1220_GetZero(uint8_t time);
float ads1220_GetWeight(uint32_t time, float coff, int32_t zero);
float ads1220_GetCoff(uint8_t time, uint16_t weight);


#endif /* _WEIGHT_H_ */

