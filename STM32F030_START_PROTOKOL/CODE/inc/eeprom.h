#ifndef _EEPROM_H_
#define _EEPROM_H_

#include "stm32f0xx.h"
#include "i2c.h"

#define EEPROM_ADDR   0x57

/****************************************************************/
void eeprom_Write_one(uint16_t addr, uint8_t data);
uint8_t eeprom_Read_one(uint16_t addr);

void eeprom_Write_Buff(uint16_t addr, uint8_t *buff, uint16_t size);
void eeprom_Read_Buff(uint16_t addr, uint8_t *buff, uint16_t size);

void eeprom_WriteFloat(uint16_t addr, float data);
float eeprom_ReadFloat(uint16_t addr);
/****************************************************************/

#endif /* _EEPROM_H_ */


