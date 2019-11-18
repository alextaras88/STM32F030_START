#ifndef _USART_H_
#define _USART_H_

#include "stm32f0xx.h"

void USART1_Init(void);
void USART1_Send (char chr);
void USART1_Send_String (char* str);

void USART1_Send_Buffer(uint8_t *pBuff, uint16_t Len);

#endif /* _USART_H_ */

