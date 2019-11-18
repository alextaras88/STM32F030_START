#include "usart.h"

/*********************************************************************/
void USART1_Init(void){
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;											// Clock GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;										// Clock USART1
	
	// PA2 TX
	GPIOA->MODER |= GPIO_MODER_MODER2_1;										// AF output PP 
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;	     	 	    	// High speed
	
	// PA3 RX
	GPIOA->MODER &= ~GPIO_MODER_MODER3;											// Floating input
	
	GPIOA->AFR[0] |= (1<<8)|(1<<12);												// PA2, PA3 - GPIO AF1
	
	
	USART1->CR1 |= USART_CR1_OVER8;													// 8 bit data
	USART1->BRR = 0x0340;
	
	USART1->CR1 |= USART_CR1_TE;                 
	USART1->CR1 |= USART_CR1_RE;                 
	USART1->CR1 |= USART_CR1_UE;                 

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

