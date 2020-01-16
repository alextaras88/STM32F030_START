#ifndef _USART_H_
#define _USART_H_

#include "stm32f0xx.h"

#define RS485_TX_HIGH  GPIOA->BSRR |= GPIO_BSRR_BS_4
#define RS485_TX_LOW   GPIOA->BSRR |= GPIO_BSRR_BR_4

void USART1_Init(void);
void USART1_Send (char chr);
void USART1_Send_String (char* str);
void USART1_Send_Buffer(uint8_t *pBuff, uint16_t Len);
void USART1_DMA_Init(void);
void USART1_DMA_Send(uint16_t len);

uint8_t USART1_DMA_Send_Buffer(uint8_t command, uint8_t * data,uint8_t end, uint16_t len);
void USART1_DMA_RX(void);


#endif /* _USART_H_ */

