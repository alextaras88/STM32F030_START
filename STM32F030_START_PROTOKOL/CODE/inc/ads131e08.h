#ifndef _ADS131E08_H_
#define _ADS131E08_H_

#include "stm32f0xx.h"
#include "spi.h"
#include "delay.h"

 uint8_t spi_buff[30];
 int32_t adc_ch[8];


/******************************************************************************/
#define		  CS_ADS131_LOW 	    GPIOA->BSRR = GPIO_BSRR_BR_0;
#define 	  CS_ADS131_HIGH 	  	GPIOA->BSRR = GPIO_BSRR_BS_0;

#define		  RESET_ADS131_LOW 	  GPIOA->BSRR = GPIO_BSRR_BR_4;
#define 	  RESET_ADS131_HIGH 	GPIOA->BSRR = GPIO_BSRR_BS_4;

#define		  START_ADS131_LOW 	  GPIOB->BSRR = GPIO_BSRR_BR_1;
#define 	  START_ADS131_HIGH 	GPIOB->BSRR = GPIO_BSRR_BS_1;
/******************************************************************************/
#define     ID_REG						0x00
#define     CONFIG_REG_1			0x01
#define     CONFIG_REG_2			0x02
#define     CONFIG_REG_3			0x03

#define     CH1_CONFIG				0x05
#define     CH2_CONFIG				0x06
#define     CH3_CONFIG				0x07
#define     CH4_CONFIG				0x08
#define     CH5_CONFIG				0x09
#define     CH6_CONFIG				0x0A
#define     CH7_CONFIG				0x0B
#define     CH8_CONFIG				0x0C
/******************************************************************************/
#define PGA_ADS131 		12
#define VREF_ADS131 	5.000
#define VFSR_ADS131 	VREF_ADS131/PGA_ADS131
#define FSR_ADS131 		(((long int)1<<23)-1)
/******************************************************************************/
void ads131_spi_Init(void);

void ads131_RESET_HW(void);
void ads131_RESET_SW(void);

void ads131_WREG(uint8_t addr, uint8_t data);
uint8_t ads131_RREG(uint8_t reg);
void ads131_Init(void);

void ads131_Start_Read_Singal_Mode(void);
void ads131_Start_Read_Continuous_Mode(void);
void ads131_Stop_Read_Continuous_Mode(void);
void ads131_Start_SW(void);
void ads131_Offset(void);

void ads131_Read_Data_Single(void);
void ads131_Read_Data_Continuous(void);

float ads131_Get_V(int32_t ch);
/******************************************************************************/


#endif /* _ADS131E08_H_ */

