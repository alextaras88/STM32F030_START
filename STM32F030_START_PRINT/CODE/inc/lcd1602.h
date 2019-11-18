#ifndef _LCD1602_H_
#define _LCD1602_H_

#include "stm32f0xx.h"
#include "delay.h"

/******************************************************************************/
#define DELAY_LCD   130
/******************************************************************************/
#define RS_LOW			GPIOB->BSRR |= GPIO_BSRR_BR_14;
#define RS_HIGH			GPIOB->BSRR |= GPIO_BSRR_BS_14;

#define E_LOW				GPIOB->BSRR |= GPIO_BSRR_BR_15;
#define E_HIGH			GPIOB->BSRR |= GPIO_BSRR_BS_15;

#define D4_LOW			GPIOC->BSRR |= GPIO_BSRR_BR_9;
#define D4_HIGH			GPIOC->BSRR |= GPIO_BSRR_BS_9;

#define D5_LOW			GPIOC->BSRR |= GPIO_BSRR_BR_6;
#define D5_HIGH			GPIOC->BSRR |= GPIO_BSRR_BS_6;

#define D6_LOW			GPIOC->BSRR |= GPIO_BSRR_BR_8;
#define D6_HIGH			GPIOC->BSRR |= GPIO_BSRR_BS_8;

#define D7_LOW			GPIOC->BSRR |= GPIO_BSRR_BR_7;
#define D7_HIGH			GPIOC->BSRR |= GPIO_BSRR_BS_7;
/******************************************************************************/
void lcd1602_GPIO_Init(void);
void lcd1602_Write_Data(uint8_t data);
void lcd1602_Command(uint8_t command);
void lcd1602_Data(uint8_t data);
void lcd1602_Clear(void);
void lcd1602_SendChar(char cr);
void lcd1602_String(char* str);
void lcd1602_Set_Pos(uint8_t x, uint8_t y);
void lcd1602_Init(void);
/******************************************************************************/

/******************************************************************************/

#endif /* _LCD1602_H_ */

