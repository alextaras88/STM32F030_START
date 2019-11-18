#ifndef _AD7730_H_
#define _AD7730_H_

#include "stm32f0xx.h"
#include "spi.h"
#include "delay.h"

/******************************************************************************/
#define		  CS_AD7730_LOW 	    GPIOA->BSRR = GPIO_BSRR_BR_0;
#define 	  CS_AD7730_HIGH 	  	GPIOA->BSRR = GPIO_BSRR_BS_0;

#define		  RESET_AD7730_LOW 	  GPIOA->BSRR = GPIO_BSRR_BR_4;
#define 	  RESET_AD7730_HIGH 	GPIOA->BSRR = GPIO_BSRR_BS_4;
#define     DRDY_AD7730					while((GPIOA->IDR & GPIO_IDR_1) == 0);
/******************************************************************************/
#define     COM_REG							0x00
#define     STATUS_REG					0x00
#define     DATA_REG   					0x01
#define     MODE_REG   					0x02
#define     FILTER_REG 				  0x03
#define     DAC_REG    					0x04
#define     OFFSET_REG  				0x05
#define     GAIN_REG   					0x06
#define     TEST_REG   					0x07
/******************************************************************************/
void ad7730_spi_Init(void);
void ad7730_Reset(void);
void ad7730_Init(void);
uint32_t ad7730_GetData(void);

void ad7730_Zero_Calibration(void);
void ad7730_Full_Scale_Calibration(void);
uint32_t ad7730_Read_REG(uint8_t reg);

uint32_t ad7730_Get_Zero(uint8_t time);
float ad7730_Get_Weight(uint32_t time, float coff, uint32_t zero);
float ad7730_Get_Coff(uint16_t ves);

/******************************************************************************/


#endif /* _AD7730_H_ */

