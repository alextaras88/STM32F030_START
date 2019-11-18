#ifndef _SPI_H_
#define _SPI_H_

#include "stm32f0xx.h"

/******************************************************************************/
#define SPI1_DR_8bit          (*(__IO uint8_t *)((uint32_t)&(SPIx->DR))) 

#define		    CS_LOW 	  GPIOB->ODR &= ~GPIO_ODR_1;
#define 	    CS_HIGH 	GPIOB->ODR |=  GPIO_ODR_1;

#define SPI_IS_BUSY(SPIx)         (((SPIx)->SR & (SPI_SR_TXE | SPI_SR_RXNE)) == 0 || ((SPIx)->SR & SPI_SR_BSY))
#define SPI_WAIT(SPIx)            while (SPI_IS_BUSY(SPIx))
/******************************************************************************/

void Spi_Init(void);
uint8_t Spi_Transfer(SPI_TypeDef* SPIx,uint8_t data);

#endif /* _SPI_H_ */


