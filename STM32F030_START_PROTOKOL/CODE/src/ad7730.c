#include "ad7730.h"

/******************************************************************************/
void ad7730_spi_Init(void){
	
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
	
	// PA0 CS
	GPIOA->MODER |= GPIO_MODER_MODER0_0;   			 			 			// OUT PA_0
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_0;  							 			// Push pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_1;	     	 			// High speed
	CS_AD7730_HIGH;
	
	// PA4 RESET
	GPIOA->MODER |= GPIO_MODER_MODER4_0;   			 			 			// OUT PA_4
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_4;  							 			// Push pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_1;	     	 			// High speed
	RESET_AD7730_HIGH;
	
	// PA1 - REDY
	
	// SPI1 INIT
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;											// Clock SPI1

	SPI1->CR1 |= SPI_CR1_BR_2 | SPI_CR1_BR_0;       				// Spi Clock div 48MHz/64 (750KHz)
	SPI1->CR1 &= ~SPI_CR1_CPOL;
	SPI1->CR1 |= SPI_CR1_CPHA;
	SPI1->CR2 &= ~SPI_CR2_DS;
	SPI1->CR2 |= SPI_CR2_DS_0 |SPI_CR2_DS_1 | SPI_CR2_DS_2; // 8 bit data;
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;													// MSB First
	SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;									// Software slave management & Internal slave select
	SPI1->CR1 |= SPI_CR1_MSTR;															// SPI Master Mode

	SPI1->CR1 |= SPI_CR1_SPE;																// SPI Enable

}
/******************************************************************************/
void ad7730_Reset(void){
	
	RESET_AD7730_LOW;
	Delay_ms(200);
	RESET_AD7730_HIGH;
	Delay_ms(200);

}
/******************************************************************************/
void ad7730_Init(void){
	
	ad7730_spi_Init();
	
	ad7730_Reset();
//----------------------------------
	CS_AD7730_LOW;
	
	Spi_Transfer(SPI1, FILTER_REG);			// FILTER_REG
	
	Spi_Transfer(SPI1, 0x80);			
	Spi_Transfer(SPI1, 0x00);
	Spi_Transfer(SPI1, 0x10);
//----------------------------------		
	Spi_Transfer(SPI1, DAC_REG);   			// DAC_REG
	
	Spi_Transfer(SPI1, 0x23);
	
//----------------------------------
	ad7730_Full_Scale_Calibration();
//----------------------------------
	ad7730_Zero_Calibration();
//----------------------------------
  CS_AD7730_HIGH;
	
}
/******************************************************************************/
uint32_t ad7730_GetData(void){
	
  uint32_t value = 0;
	uint8_t buff[3];
	uint8_t i = 0;
	
	CS_AD7730_LOW;
	
	Spi_Transfer(SPI1, MODE_REG);	 		// MODE_REG
	
	Spi_Transfer(SPI1, 0x21);
	Spi_Transfer(SPI1, 0x80);
	Spi_Transfer(SPI1, 0x21);
	
	CS_AD7730_HIGH;
	
	GPIOA->ODR &= ~GPIO_ODR_6;	
	DRDY_AD7730; 	
	
  CS_AD7730_LOW;
	
	for(i=0;i<3; i++){
		
		buff[i] = Spi_Transfer(SPI1, 0x00);
	
	}

	Spi_Transfer(SPI1, 0x30);
	
	CS_AD7730_HIGH;

	value += (buff[0]<<16);
	value += (buff[1]<<8);
	value += (buff[2]<<0);
	
	return value;
	
}
/******************************************************************************/
void ad7730_Zero_Calibration(void){
	
	Spi_Transfer(SPI1, MODE_REG);	  // MODE_REG
	
	Spi_Transfer(SPI1, 0x90);		// Zero-Scale Self-Calibration Mode		
	Spi_Transfer(SPI1, 0x80);
		
  DRDY_AD7730;
	Delay_ms(1000); 
}
/******************************************************************************/
void ad7730_Full_Scale_Calibration(void){
	
	Spi_Transfer(SPI1, MODE_REG);	  // MODE_REG
	
	Spi_Transfer(SPI1, 0xA0);		// Zero-Scale Self-Calibration Mode		
	Spi_Transfer(SPI1, 0x80);
	
  DRDY_AD7730;
	Delay_ms(2000);	 
}
/******************************************************************************/
uint32_t ad7730_Read_REG(uint8_t reg){
	
	uint32_t data = 0;
	uint8_t i = 0;
	uint8_t buff[3];
	
	CS_AD7730_LOW;
	Spi_Transfer(SPI1, 0x10|reg);	
  CS_AD7730_HIGH;  

	CS_AD7730_LOW;	
	for(i=0;i<3;i++){
		
		buff[i] = Spi_Transfer(SPI1, 0x00);
	
	}
	Spi_Transfer(SPI1, 0x30);
	
	CS_AD7730_HIGH; 
	
	data += (buff[0]<<16);
	data += (buff[1]<<8);
	data += (buff[2]<<0);

	return data;
 
}
/******************************************************************************/
uint32_t ad7730_Get_Zero(uint8_t time){
	
	uint32_t zero = 0;
	uint8_t i;
	
	for(i = 0; i<time; i++){
		
		zero += ad7730_GetData();
		Delay_ms(50);
		
	}
	zero/=(uint32_t)time;
	
	return zero;
	
}
/******************************************************************************/
float ad7730_Get_Weight(uint32_t time, float coff, uint32_t zero){
	
	float weight = 0;
	uint32_t i;
	
	for( i = 0; i<time; i++){
		
		weight += (float)ad7730_GetData();
	}
	
	weight /= time;
	weight -= (float)zero;
	weight /= coff;
	
	return (float)weight;

}
/******************************************************************************/
float ad7730_Get_Coff(uint16_t ves){
	
	uint32_t zero = 0;
	uint32_t weight1 = 0;
	
	zero = ad7730_Get_Zero(20);
	zero = 0;
	zero = ad7730_Get_Zero(20);
	GPIOB->ODR |= GPIO_ODR_1;
	Delay_ms(5000);
	
  weight1 = ad7730_Get_Zero(20); 
	GPIOB->ODR &= ~GPIO_ODR_1;
	
	return (float)(weight1 - zero)/ves;

}
/******************************************************************************/
