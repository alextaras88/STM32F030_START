#include "spi.h"

/******************************************************************************/
void Spi_Init(void){
	
	// GPIO INIT
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;											// Clock GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;											// Clock GPIOB
	GPIOA->AFR[0] |= (0<<20)|(0<<24)|(0<<28);								// PA5, PA6, PA7 - GPIO AF0

	// PA5 SCK
	GPIOA->MODER |= GPIO_MODER_MODER5_1;										// AF
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_5;											// PP
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5;       				// Full Speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR5;											// No pull-up, pull-down

	// PA6 MISO
	GPIOA->MODER &= ~GPIO_MODER_MODER6;
  GPIOA->MODER |= GPIO_MODER_MODER6_1;										// INPUT Floating
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR6;

	// PA7 MOSI
	GPIOA->MODER |= GPIO_MODER_MODER7_1;										// AF
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_7;											// PP
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;       				// Full Speed
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR7;											// No pull-up, pull-down
	
	// PB1 CS
	GPIOB->MODER |= GPIO_MODER_MODER1_0;   			 			 			// OUT PB_1
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_1;  							 			// Push pull
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_1;	     	 			// High speed
	
	CS_HIGH;

	// SPI1 INIT
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;											// Clock SPI1

	SPI1->CR1 |= SPI_CR1_BR_0 ;       											// Spi Clock div 48MHz/32 (1.5MHz)
	SPI1->CR1 &= ~SPI_CR1_CPOL;
	SPI1->CR1 &= ~SPI_CR1_CPHA;
	SPI1->CR2 &= ~SPI_CR2_DS;
	SPI1->CR2 |= SPI_CR2_DS_0 |SPI_CR2_DS_1 | SPI_CR2_DS_2; // 8 bit data;
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;													// MSB First
	SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;									// Software slave management & Internal slave select
	SPI1->CR1 |= SPI_CR1_MSTR;															// SPI Master Mode

	SPI1->CR1 |= SPI_CR1_SPE;																// SPI Enable
	
}
/******************************************************************************/
uint8_t Spi_Transfer(SPI_TypeDef* SPIx,uint8_t data){
	
	SPI_WAIT(SPIx);
	SPI1_DR_8bit  = data;
	SPI_WAIT(SPIx);
	
	return SPI1_DR_8bit;

}
/******************************************************************************/

