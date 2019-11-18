#include "ads131e08.h"

/******************************************************************************/
void ads131_spi_Init(void){
	
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
	CS_ADS131_HIGH;
	
	// PA4 RESET
	GPIOA->MODER |= GPIO_MODER_MODER4_0;   			 			 			// OUT PA_4
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_4;  							 			// Push pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4_1;	     	 			// High speed
	RESET_ADS131_HIGH;
	
	// PB1 START
	GPIOB->MODER |= GPIO_MODER_MODER1_0;   			 			 			// OUT PB_1
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_1;  							 			// Push pull
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_1;	     	 			// High speed
	START_ADS131_HIGH;
	
	// PA1 - REDY

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
/******************************************************************************/
void ads131_RESET_HW(void){
	
	RESET_ADS131_LOW;
	Delay_ms(100);
	RESET_ADS131_HIGH;
	Delay_ms(100);

}
/******************************************************************************/
void ads131_RESET_SW(void){
	
	CS_ADS131_LOW;
	Delay_ms(100);
	Spi_Transfer(SPI1, 0x06);
	Delay_ms(100);
	CS_ADS131_HIGH;

}
/******************************************************************************/
void ads131_WREG(uint8_t addr, uint8_t data){
	
	uint8_t reg = ( addr & 0x1F ) | 0x40;
	
	CS_ADS131_LOW;
	Delay_ms(20);
	Spi_Transfer(SPI1, reg);
	Spi_Transfer(SPI1, 0x01);
	Spi_Transfer(SPI1, data);
	Delay_ms(20);
	CS_ADS131_HIGH;

}
/******************************************************************************/
uint8_t ads131_RREG(uint8_t reg){
	
	uint8_t data[2];
	uint8_t addr = ( reg & 0x1F ) | 0x20;
	
	CS_ADS131_LOW;
	Delay_ms(5);
  while(!(GPIOA->IDR & GPIO_IDR_1)){}
	Spi_Transfer(SPI1, addr);
	Spi_Transfer(SPI1, 0x01);
	data[0] = Spi_Transfer(SPI1, 0x00);
	data[1] = Spi_Transfer(SPI1, 0x00);
	Delay_ms(5);
	CS_ADS131_HIGH;
	
	return data[0];
		
}
/******************************************************************************/
void ads131_Init(void){
	
	ads131_spi_Init();
	ads131_RESET_HW();
	
	START_ADS131_HIGH;
	
	ads131_Stop_Read_Continuous_Mode();
	Delay_ms(100);
	// CONFIG SET
	
	ads131_WREG(CONFIG_REG_1, 0x96);
	Delay_ms(100);
	ads131_WREG(CONFIG_REG_2, 0xF4);
	Delay_ms(100);
	ads131_WREG(CONFIG_REG_3, 0x60);
	Delay_ms(100);
	
	// CHANELS SET
	ads131_WREG(CH1_CONFIG, 0x60);
	Delay_ms(100);
	ads131_WREG(CH2_CONFIG, 0x60);
	Delay_ms(100);
	ads131_WREG(CH3_CONFIG, 0x60);
	Delay_ms(100);
	ads131_WREG(CH4_CONFIG, 0x60);
	Delay_ms(100);
	ads131_WREG(CH5_CONFIG, 0x60);
	Delay_ms(100);
	ads131_WREG(CH6_CONFIG, 0x60);
	Delay_ms(100);
	ads131_WREG(CH7_CONFIG, 0x60);
	Delay_ms(100);
	ads131_WREG(CH8_CONFIG, 0x60);
	Delay_ms(100);
	
	START_ADS131_HIGH;
	
}
/******************************************************************************/
void ads131_Start_Read_Singal_Mode(void){
	
	CS_ADS131_LOW;
	Delay_ms(100);
	Spi_Transfer(SPI1, 0x12);
	Delay_ms(100);
	CS_ADS131_HIGH;

}
/******************************************************************************/
void ads131_Stop_Read_Continuous_Mode(void){
	
	CS_ADS131_LOW;
	Delay_ms(100);
	Spi_Transfer(SPI1, 0x11);
	Delay_ms(100);
	CS_ADS131_HIGH;

}
/******************************************************************************/
void ads131_Start_Read_Continuous_Mode(void){
	
	CS_ADS131_LOW;
	Delay_ms(100);
	Spi_Transfer(SPI1, 0x10);
	Delay_ms(100);
	CS_ADS131_HIGH;

}
/******************************************************************************/
void ads131_Start_SW(void){
	
	CS_ADS131_LOW;
	Delay_ms(100);
	Spi_Transfer(SPI1, 0x08);
	Delay_ms(100);
	CS_ADS131_HIGH;

}
/******************************************************************************/
void ads131_Offset(void){
	
	CS_ADS131_LOW;
	Delay_ms(100);
	Spi_Transfer(SPI1, 0x1A);
	Delay_ms(100);
	CS_ADS131_HIGH;
	Delay_ms(200);

}
/******************************************************************************/
void ads131_Read_Data_Single(void){
	
	uint8_t i = 0;
	
	START_ADS131_HIGH;
  while(!(GPIOA->IDR & GPIO_IDR_1)){}
	CS_ADS131_LOW;
		
	Spi_Transfer(SPI1, 0x12);
		
	for(i=0;i<27;i++){
		
		spi_buff[i] = Spi_Transfer(SPI1, 0x00);
	
	}
	
	CS_ADS131_HIGH;
	
	adc_ch[0] = (int32_t)((spi_buff[3]<<24) + (spi_buff[4]<<16) +(spi_buff[5]<<8));
	adc_ch[0] = adc_ch[0] >> 8;
	
	adc_ch[1] = (int32_t)((spi_buff[6]<<24) + (spi_buff[7]<<16) +(spi_buff[8]<<8));
	adc_ch[1] = adc_ch[1] >> 8;
	
	adc_ch[2] = (int32_t)((spi_buff[9]<<24) + (spi_buff[10]<<16) +(spi_buff[11]<<8));
	adc_ch[2] = adc_ch[2] >> 8;
	
	adc_ch[3] = (int32_t)((spi_buff[12]<<24) + (spi_buff[13]<<16) +(spi_buff[14]<<8));
	adc_ch[3] = adc_ch[3] >> 8;
	
	adc_ch[4] = (int32_t)((spi_buff[15]<<24) + (spi_buff[16]<<16) +(spi_buff[17]<<8));
	adc_ch[4] = adc_ch[4] >> 8;
	
	adc_ch[5] = (int32_t)((spi_buff[18]<<24) + (spi_buff[19]<<16) +(spi_buff[20]<<8));
	adc_ch[5] = adc_ch[5] >> 8;
	
	adc_ch[6] = (int32_t)((spi_buff[21]<<24) + (spi_buff[22]<<16) +(spi_buff[23]<<8));
	adc_ch[6] = adc_ch[6] >> 8;
	
	adc_ch[7] = (int32_t)((spi_buff[24]<<24) + (spi_buff[25]<<16) +(spi_buff[26]<<8));
	adc_ch[7] = adc_ch[7] >> 8;
	
}
/******************************************************************************/
void ads131_Read_Data_Continuous(void){
	
	uint8_t i = 0;
	
  while(!(GPIOA->IDR & GPIO_IDR_1)){}	
	CS_ADS131_LOW;
		
	for(i=0;i<27;i++){
		
		spi_buff[i] = Spi_Transfer(SPI1, 0x00);
	
	}
	
	CS_ADS131_HIGH;
	
	adc_ch[0] = (int32_t)((spi_buff[3]<<24) + (spi_buff[4]<<16) +(spi_buff[5]<<8));
	adc_ch[0] = adc_ch[0] >> 8;
	
	adc_ch[1] = (int32_t)((spi_buff[6]<<24) + (spi_buff[7]<<16) +(spi_buff[8]<<8));
	adc_ch[1] = adc_ch[1] >> 8;
	
	adc_ch[2] = (int32_t)((spi_buff[9]<<24) + (spi_buff[10]<<16) +(spi_buff[11]<<8));
	adc_ch[2] = adc_ch[2] >> 8;
	
	adc_ch[3] = (int32_t)((spi_buff[12]<<24) + (spi_buff[13]<<16) +(spi_buff[14]<<8));
	adc_ch[3] = adc_ch[3] >> 8;
	
	adc_ch[4] = (int32_t)((spi_buff[15]<<24) + (spi_buff[16]<<16) +(spi_buff[17]<<8));
	adc_ch[4] = adc_ch[4] >> 8;
	
	adc_ch[5] = (int32_t)((spi_buff[18]<<24) + (spi_buff[19]<<16) +(spi_buff[20]<<8));
	adc_ch[5] = adc_ch[5] >> 8;
	
	adc_ch[6] = (int32_t)((spi_buff[21]<<24) + (spi_buff[22]<<16) +(spi_buff[23]<<8));
	adc_ch[6] = adc_ch[6] >> 8;
	
	adc_ch[7] = (int32_t)((spi_buff[24]<<24) + (spi_buff[25]<<16) +(spi_buff[26]<<8));
	adc_ch[7] = adc_ch[7] >> 8;
	
}
/******************************************************************************/
float ads131_Get_V(int32_t ch){
	
	return (float)((ch*VFSR_ADS131*1000)/FSR_ADS131);

}
/******************************************************************************/
 

