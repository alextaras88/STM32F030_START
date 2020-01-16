#ifndef _ADS1220_H_
#define _ADS1220_H_

#include "stm32f0xx.h"
#include "spi.h"
#include "delay.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>
/****************************************************/
#define PGA 1
#define VREF 2.500
#define VFSR VREF/PGA
#define FSR (((long int)1<<23)-1)

#define		  CS_ADS1220_LOW 	    GPIOA->BSRR = GPIO_BSRR_BR_0;
#define 	  CS_ADS1220_HIGH 	  GPIOA->BSRR = GPIO_BSRR_BS_0;

#define			CONFIG_REG0 0x00
#define 		CONFIG_REG1 0x01
#define			CONFIG_REG2 0x02
#define 		CONFIG_REG3 0x03
/****************************************************/
void ads1220_SPI_Init(void);
void ads1220_WREG(uint8_t reg, uint8_t data);
uint8_t ads1220_RREG(uint8_t reg);
void ads1220_Init(void);
int32_t ads1220_GetData(void);
float ads1220_Get_temp(void);
float ads1220_Get_V(void);
/****************************************************/


#endif /* _ADS1220_H_ */

