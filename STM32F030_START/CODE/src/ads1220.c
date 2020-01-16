#include "ads1220.h"

/******************************************************************************/
void ads1220_SPI_Init(void){
	
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
	
	CS_ADS1220_HIGH;

	// SPI1 INIT
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;											// Clock SPI1

	SPI1->CR1 |= SPI_CR1_BR_2;       												// Spi Clock div 48MHz/32 (1.5MHz)
	SPI1->CR1 &= ~SPI_CR1_CPOL;
	SPI1->CR1 |= SPI_CR1_CPHA;
	SPI1->CR2 &= ~SPI_CR2_DS;
	SPI1->CR2 |= SPI_CR2_DS_0 |SPI_CR2_DS_1 | SPI_CR2_DS_2; // 8 bit data;
	SPI1->CR1 &= ~SPI_CR1_LSBFIRST;													// MSB First
	SPI1->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI;									// Software slave management & Internal slave select
	SPI1->CR1 |= SPI_CR1_MSTR;															// SPI Master Mode

	SPI1->CR1 |= SPI_CR1_SPE;																// SPI Enable
	
}
/************************************************************************************/
void ads1220_WREG(uint8_t reg, uint8_t data){
	
	CS_ADS1220_LOW;
	Delay_ms(5);
	Spi_Transfer(SPI1, 0x40|(reg<<2));
	Spi_Transfer(SPI1, data);
  Delay_ms(5);
	CS_ADS1220_HIGH;

}
/************************************************************************************/
uint8_t ads1220_RREG(uint8_t reg){
	
	uint8_t data;
	
	CS_ADS1220_LOW;
	Delay_ms(5);
	Spi_Transfer(SPI1, 0x20|(reg<<2));
	while(!(GPIOA->IDR & GPIO_IDR_1)){}
	data = Spi_Transfer(SPI1, 0x00);
	Delay_ms(5);
	CS_ADS1220_HIGH;
	
	return data;
}
/************************************************************************************/
void ads1220_Init(void){
	
	ads1220_SPI_Init();
	
	CS_ADS1220_LOW;
	Delay_ms(100);
	Spi_Transfer(SPI1, 0x06);						// Reset
	Delay_ms(100);
	CS_ADS1220_HIGH;
	
	ads1220_WREG(CONFIG_REG0 , 0x00);		// AINP = AIN0, AINN = AIN1, gain = 32, PGA enabled
	ads1220_WREG(CONFIG_REG1 , 0x24);		// DR = 45 SPS, normal, continuous conversion mode
	ads1220_WREG(CONFIG_REG2 , 0xD0);		// External voltage reference(AVDD-AVCC), simultaneous 50-Hz and 60-Hz rejection
	ads1220_WREG(CONFIG_REG3 , 0x00);		// No IDACs used
	
}
/************************************************************************************/
 int32_t ads1220_GetData(void){
	
	uint8_t i;
	static char buff[3];
  int32_t value = 0;
	 
	while(!(GPIOA->IDR & GPIO_IDR_1)){}
		
	CS_ADS1220_LOW;
		
	for(i=0;i<3;i++){
	buff[i] = Spi_Transfer(SPI1, 0xFF);
	}
	
	CS_ADS1220_HIGH;
		
	value = (int32_t)((buff[0]<<24) + (buff[1]<<16) +(buff[2]<<8));
	value = value >> 8;
		
	return value;
	
}
/************************************************************************************/
float ads1220_Get_temp(void){
	
	uint32_t data = 0;
	float temp = 0;
	
	uint8_t b1, b2, b3;
	
	CS_ADS1220_LOW;
	b1 = Spi_Transfer(SPI1, 0xFF);
	b2 = Spi_Transfer(SPI1, 0xFF);
	b3 = Spi_Transfer(SPI1, 0xFF);
	CS_ADS1220_HIGH;
	
	data += (b1<<16);
	data += (b2<<8);
	data += (b3<<0);
	
	data = (uint16_t)data>>2;
	temp = (float)data*0.03125;
	
	return temp;
	
}
/************************************************************************************/
float ads1220_Get_V(void){
	
	return (float)((ads1220_GetData()*VFSR)/FSR);

}
/************************************************************************************/

