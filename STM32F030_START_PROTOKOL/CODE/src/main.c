#include "main.h"

char str[20];
char str1[20];
extern uint8_t rx_buffer[32];
extern uint8_t tx_buffer[32];
uint8_t owen_addr;
uint16_t hash;
uint8_t bT[4];
float Temp, Volts, Weight;
uint8_t status = 0;
uint16_t i;

uint8_t dma_cndt = 20;

float ConvertByteToFloat(uint8_t * buff);
void Timer16_Init(void);

int main(void){
	
	Clock_Init();
	Delay_Init();
	GPIO_Init();
	
	USART1_Init();
	USART1_DMA_Init();
	I2c_Init();
	ssd1306_Init();
	Timer16_Init();
//USART1_Send_String ("Test USART\r\n");
	
	ssd1306_SetCursor(20, 0);
	ssd1306_WriteString("OWEN_485", Font_11x18, White);
	ssd1306_UpdateScreen();
	
	while(1){
				

	}
}
///////////////////////////////////////////////////////////////
void DMA1_Channel2_3_IRQHandler(void){
 
 if(DMA1->ISR & DMA_ISR_TCIF3){
	 
	 DMA1_Channel3->CCR &=~ DMA_CCR_EN;
	 DMA1->ISR |=  DMA_ISR_TCIF3;
	 
	 /*********************
	 Обработка принятого пакета в прерывании DMA
	 *********************/
	 //i = 1;     // Статус принятого пакета, если обрабатывать прирывание в основном цикле
	 owen_addr = Convert_OwenData_To_Data(rx_buffer[1], rx_buffer[2]);
	 hash =   (Convert_OwenData_To_Data(rx_buffer[5], rx_buffer[6])<<8);	
	 hash +=   Convert_OwenData_To_Data(rx_buffer[7], rx_buffer[8]);
	 
	 if(owen_addr == 0x05 && hash == 0xB8DF){
		 
		 bT[0] = 0x00;
		 bT[1] = Convert_OwenData_To_Data(rx_buffer[13], rx_buffer[14]);
	   bT[2] = Convert_OwenData_To_Data(rx_buffer[11], rx_buffer[12]);
	   bT[3] = Convert_OwenData_To_Data(rx_buffer[9], rx_buffer[10]);
		
		 Temp = ConvertByteToFloat(bT);
		 sprintf(str, "%u ""%.1f$C ", owen_addr, Temp );
		 ssd1306_SetCursor(0, 22);
	   ssd1306_WriteString(str, Font_11x18, White);
	   ssd1306_UpdateScreen();
		
		 dma_cndt = 22;
		 status = 1;
		
	}
	
	if(owen_addr == 0x10){
		
		if(hash == 0x7F46){ // Значение в mV
			
			bT[0] = Convert_OwenData_To_Data(rx_buffer[15], rx_buffer[16]);
			bT[1] = Convert_OwenData_To_Data(rx_buffer[13], rx_buffer[14]);
			bT[2] = Convert_OwenData_To_Data(rx_buffer[11], rx_buffer[12]);
			bT[3] = Convert_OwenData_To_Data(rx_buffer[9],  rx_buffer[10]);
		
			Volts = ConvertByteToFloat(bT);
			sprintf(str, "%u ""%.3fmV ", owen_addr, Volts);
			ssd1306_SetCursor(0, 42);
			ssd1306_WriteString(str, Font_11x18, White);
			ssd1306_UpdateScreen();
		
		}
		
		if(hash == 0x399C){ // Значение физической величины
			
			bT[0] = Convert_OwenData_To_Data(rx_buffer[15], rx_buffer[16]);
			bT[1] = Convert_OwenData_To_Data(rx_buffer[13], rx_buffer[14]);
			bT[2] = Convert_OwenData_To_Data(rx_buffer[11], rx_buffer[12]);
			bT[3] = Convert_OwenData_To_Data(rx_buffer[9],  rx_buffer[10]);
		
			Weight = ConvertByteToFloat(bT);
			sprintf(str, "%u ""%.3fKg ", owen_addr, Weight);
			ssd1306_SetCursor(0, 42);
			ssd1306_WriteString(str, Font_11x18, White);
			ssd1306_UpdateScreen();
		
		}
		
		dma_cndt = 20;
		status =0;
	
	}
			
   /*********************/
	 DMA1->IFCR |= DMA_IFCR_CTCIF3;
	 DMA1_Channel3->CNDTR =  dma_cndt;
   DMA1_Channel3->CCR |= DMA_CCR_EN;
	
 }      
 //Если передана половина буфера
 if(DMA1->ISR & DMA_ISR_HTIF3){
	 
	 DMA1->ISR |= DMA_ISR_HTIF3;
	 
 }
 
 //Если произошла ошибка при обмене
 if(DMA1->ISR & DMA_ISR_TEIF3) {
	 
	 DMA1->ISR |= DMA_ISR_TEIF3;
	  
 } 
}
////////////////////////////////////////////////////////////
float ConvertByteToFloat(uint8_t * buff){
	
	float *res;
	uint8_t x[4];
	uint8_t i;
	
	for(i=0;i<4; i++){
		
		x[i] = buff[i];
	
	}
	res = (float *)x;
	
	return res[0];

}
////////////////////////////////////////////////////////////
void Timer16_Init(void){
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;									// enable clock for basic TIM4
	
	TIM16->PSC = 4800-1;																	// div, frequency  10khz
  TIM16->ARR = 2000; 																		// count to 10khz/5000 - 2Hz
  TIM16->DIER |= TIM_DIER_UIE; 													// enable interrupt for timer
  TIM16->CR1 |= TIM_CR1_CEN; 														// start count
  NVIC_EnableIRQ(TIM16_IRQn); 

}
////////////////////////////////////////////////////////////
void TIM16_IRQHandler(void){
	
	 TIM16->SR &= ~TIM_SR_UIF;
	
   if(status == 0){
		 
		 TRM101_GetTemperature(5);    //Два раза в секунду отправляем запрос температуры в ТРМ101 
	  
	 }
	 if(status == 1){
		 
		 MB110_224_Get_Value(16, MB110_GET_WEIGHT);     //Два раза в секунду отправляем запрос температуры в MB110 
	  
	 }
	 
	 GPIOB->ODR ^= GPIO_ODR_1;
	
	}
////////////////////////////////////////////////////////////

	
