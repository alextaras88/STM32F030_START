#ifndef _OWEN_485_H_
#define _OWEN_485_H_

#include "stm32f0xx.h"
#include "usart.h"
#include "delay.h"

/***********************************/
#define MB110_GET_VOLTS 		0x7F46
#define MB110_GET_WEIGHT 		0x399C
/***********************************/

/******************************************************************************/
void OWEN_485_Init(void);
int16_t CRC16(uint8_t * dataIN, uint16_t len);
uint16_t Convert_Data_To_OwenData(uint8_t dataIN);
uint8_t Convert_OwenData_To_Data(uint8_t byte1, uint8_t byte2);
/*************************/
void TRM101_GetTemperature(uint8_t addr);
void MB110_224_Get_Value(uint8_t addr, uint16_t hash);
/******************************************************************************/



#endif /* _OWEN_485_H_ */
