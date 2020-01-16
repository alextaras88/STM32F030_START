#include "usart.h"

 uint8_t rx_buffer[32];
 uint8_t tx_buffer[32];

/*********************************************************************/
void USART1_Init(void){
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;											// Clock GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;										// Clock USART1
	
	// PA2 TX
	GPIOA->MODER |= GPIO_MODER_MODER2_1;										// AF output PP 
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;	     	 	    	// High speed
	
	// PA3 RX
	GPIOA->MODER  |= GPIO_MODER_MODER3_1;										// Floating input
	
	// PA4 RS485 RX_TX
	GPIOA->MODER   |= GPIO_MODER_MODER4_0;   			 			 		// OUT PA_4
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_4;  							 			// Push pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;	     	 			  // High speed
	
	RS485_TX_LOW;
	
	GPIOA->AFR[0] |= (1<<8)|(1<<12);												// PA2, PA3 - GPIO AF1
	
	
	USART1->CR1 |= USART_CR1_OVER8;													// 8 bit data
	USART1->BRR = 0x0340;																		// 115200
	//USART1->BRR = 0x2710;																		// 9600
	
	USART1->CR1 |= USART_CR1_TE;                 
	USART1->CR1 |= USART_CR1_RE;                 
	USART1->CR1 |= USART_CR1_RXNEIE; 
  USART1->CR1 |= USART_CR1_UE; 	
	
	//NVIC_EnableIRQ(USART1_IRQn);
	
}
/*********************************************************************/
void USART1_Send (char chr){  
	
	while (!(USART1->ISR & USART_ISR_TC));
	USART1->TDR = chr;
	
}
/*********************************************************************/
void USART1_Send_String (char* str){           
	
	uint8_t i = 0;
	
	while(str[i])
	USART1_Send(str[i++]);
	
}
/*********************************************************************/
void USART1_Send_Buffer(uint8_t *pBuff, uint16_t Len){
	
	while (Len--){
		
    USART1_Send(*(pBuff++));
	
	}
}
/*********************************************************************/
void USART1_DMA_Init(void){
	
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	//Tx DMA	
	DMA1_Channel2->CPAR = (uint32_t)&USART1->TDR;
	DMA1_Channel2->CMAR = (uint32_t)&tx_buffer[0];
	DMA1_Channel2->CNDTR =  32;													// Size buffer
	
	DMA1_Channel2->CCR  &= ~DMA_CCR_CIRC;								// Disenable cycle mode
	DMA1_Channel2->CCR  &= ~DMA_CCR_PINC;								// Disenable increment pointer periphery
	
	DMA1_Channel2->CCR  &= ~DMA_CCR_PSIZE;							// Size data periphery - 8 bit
	DMA1_Channel2->CCR  &= ~DMA_CCR_MSIZE; 							// Size data memory - 8 bit
	
	DMA1_Channel2->CCR  |=  DMA_CCR_DIR;								// Read: memory -> periphery
	DMA1_Channel2->CCR  |=  DMA_CCR_MINC;								// Disenable increment pointer memory
	
	USART1->CR3        |=  USART_CR3_DMAT;
	
	//Rx DMA
	DMA1_Channel3->CMAR = (uint32_t)&rx_buffer[0];       //адрес буфера приемника
	DMA1_Channel3->CPAR = (uint32_t)&USART1->RDR;      	 //адрес регистра данных приемника
	DMA1_Channel3->CNDTR = 20;                         	 //для приемника
	DMA1_Channel3->CCR |= DMA_CCR_MINC;
	DMA1_Channel3->CCR |= DMA_CCR_CIRC;
	DMA1_Channel3->CCR |= DMA_CCR_TEIE;
	DMA1_Channel3->CCR |= DMA_CCR_TCIE; 
	DMA1_Channel3->CCR |= DMA_CCR_EN;
	
	NVIC_EnableIRQ (DMA1_Channel2_3_IRQn);
	
	USART1->CR3        |=  USART_CR3_DMAR;
	
	
}
/*********************************************************************/
void USART1_DMA_Send(uint16_t len){
	
	DMA1_Channel2->CCR  &= ~DMA_CCR_EN;      
  DMA1_Channel2->CNDTR =  len; 
	DMA1->IFCR          |=  DMA_IFCR_CTCIF2;
	DMA1_Channel2->CCR  |=  DMA_CCR_EN;	
  
}
uint8_t USART1_DMA_Send_Buffer(uint8_t command, uint8_t * data,uint8_t end, uint16_t len){
	
	uint16_t i = 0;
	uint16_t cnt = 0;
	tx_buffer[0] = command;
	
	for(i = 0; i<len; i++){
		
		tx_buffer[i+1] = data[i];
		cnt++;
		
	}
	
	rx_buffer[len+1] = end;
	
	USART1_DMA_Send(len+2);
	
	if(cnt == len){
		
		return 1;
	
	}
	
	else return 0;
	
}
/*********************************************************************/
void USART1_DMA_RX(void){
	
	uint16_t i = 0;
	
 if ((DMA1_Channel3->CNDTR & 0x0000FFFF) < 14)
	 
 {
	 
	 for (i = 0 ; i < (14 - (DMA1_Channel3->CNDTR & 0x0000FFFF)) ; i ++){
	 
	 }

	 USART1->CR1 &= ~USART_CR1_RE;             
   DMA1_Channel3->CCR &= ~DMA_CCR_EN;
   DMA1_Channel3->CNDTR &= 0xFFFF0000;                     
   DMA1_Channel3->CCR |= DMA_CCR_EN;
   USART1->CR1 |= USART_CR1_RE;            
 
 }
}
/*********************************************************************/
//void USART1_IRQHandler (void){
//	
//	if (USART1->ISR & USART_ISR_RXNE){
//		
//			USART1->ISR &= ~USART_ISR_RXNE;
//		
//		if (USART1->RDR == '0'){
//			
//			GPIOB->ODR &= ~GPIO_ODR_1;
//			USART1_Send_String ("OFF_LED\r\n");
//			
//		}
//		
//		if (USART1->RDR == '1'){
//			
//			GPIOB->ODR |= GPIO_ODR_1;
//			USART1_Send_String ("ON_LED\r\n");
//		}
//		
//	}
//	
//}
/*********************************************************************/
//void DMA1_Channel2_3_IRQHandler(void){
// 
// if(DMA1->ISR & DMA_ISR_TCIF3){
//	 
//	 DMA1_Channel3->CCR &=~ DMA_CCR_EN;
//	 DMA1->ISR |=  DMA_ISR_TCIF3;
//	 // WORCK
//	 DMA1->IFCR |= DMA_IFCR_CTCIF3;
//	 DMA1_Channel3->CNDTR=20;
//   DMA1_Channel3->CCR |= DMA_CCR_EN;
//	
// }      
// 
// //Если передана половина буфера
// if(DMA1->ISR & DMA_ISR_HTIF3){
//	 
//	 DMA1->ISR |= DMA_ISR_HTIF3;
//	 
// }
// 
// //Если произошла ошибка при обмене
// if(DMA1->ISR & DMA_ISR_TEIF3) {
//	 
//	 DMA1->ISR |= DMA_ISR_TEIF3;
//	  
// } 
//}
/////////////////////////////////////////////////////////////////
