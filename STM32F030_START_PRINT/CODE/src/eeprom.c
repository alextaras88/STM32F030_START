#include "eeprom.h"
#include "delay.h"

/******************************************************************************/
void eeprom_Write_one(uint16_t addr, uint8_t data){
	
	i2c_Start_addr(I2C1, EEPROM_ADDR, _I2C_MASTER_WRITE);
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_START, (uint8_t)(addr>>8));
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_CONT, (uint8_t) addr);
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_FINISH, data);
	
}
/******************************************************************************/
uint8_t eeprom_Read_one(uint16_t addr){
	
	uint8_t dat;
	
	i2c_Start_addr(I2C1, EEPROM_ADDR, _I2C_MASTER_WRITE);
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_START, (uint8_t)(addr>>8));
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_FINISH, (uint8_t) addr);
	
	i2c_Start_addr(I2C1, EEPROM_ADDR, _I2C_MASTER_READ);
	i2c_Read(I2C1, &dat, _I2C_MASTER_SINGLE_RECEIVE);
	
	return dat;

}
/******************************************************************************/
void eeprom_Write_Buff(uint16_t addr, uint8_t *buff, uint16_t size){
	
	uint16_t i;
	
	i2c_Start_addr(I2C1, EEPROM_ADDR, _I2C_MASTER_WRITE);
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_START, (uint8_t)(addr>>8));
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_CONT, (uint8_t) addr);
	
	for(i = 0;i<size; i++){
		
		if(i<(size-1)){
		
		i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_CONT, buff[i]);
		
		}
		else{
		
		i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_FINISH, buff[i]);
			
		}
				
	}
	
}
/******************************************************************************/
void eeprom_Read_Buff(uint16_t addr, uint8_t *buff, uint16_t size){
	
	uint16_t i = 0;
	
	i2c_Start_addr(I2C1, EEPROM_ADDR, _I2C_MASTER_WRITE);
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_START, (uint8_t)(addr>>8));
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_FINISH, (uint8_t) addr);
	Delay_ms(10);
	i2c_Start_addr(I2C1, EEPROM_ADDR, _I2C_MASTER_READ);
	I2C1->CR2 |= (uint32_t)(1 << 16) | I2C_CR2_RELOAD | I2C_CR2_START ;  
  while (!(I2C1->ISR & I2C_ISR_RXNE)){}  
	
	for(i = 0;i<size; i++){
			
		if(i<(size)){
		
		i2c_Read(I2C1, &buff[i], _I2C_MASTER_BURST_RECEIVE_CONT );
		Delay_ms(10);
		
		}
		else{
		
		i2c_Read(I2C1, &buff[i], _I2C_MASTER_BURST_RECEIVE_FINISH );
			
		}			
	}
}
/******************************************************************************/
void eeprom_WriteFloat(uint16_t addr, float data){
	
	uint8_t *byte;
	uint8_t i = 0;
	
  byte = (uint8_t *)&data;
	i2c_BUSY(I2C1);
	i2c_Start_addr(I2C1, EEPROM_ADDR, _I2C_MASTER_WRITE);
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_START, (uint8_t)(addr>>8));
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_CONT, (uint8_t) addr);
	Delay_ms(5);
	for(i = 0;i<4; i++){
		
		if(i<(3)){
		
		i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_CONT, byte[i]);
		Delay_ms(5);
		}
		else{
		
		i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_FINISH, byte[i]);
			
		}			
	}
}

/******************************************************************************/
float eeprom_ReadFloat(uint16_t addr){
	
	uint8_t i = 0;
	float *res;
	uint8_t x[4];
	i2c_BUSY(I2C1);
	i2c_Start_addr(I2C1, EEPROM_ADDR, _I2C_MASTER_WRITE);
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_START, (uint8_t)(addr>>8));
	i2c_Write(I2C1, _I2C_MASTER_BURST_SEND_FINISH, (uint8_t) addr);

	i2c_Start_addr(I2C1, EEPROM_ADDR, _I2C_MASTER_READ);
	I2C1->CR2 |= (uint32_t)(1 << 16) | I2C_CR2_RELOAD | I2C_CR2_START ;  
  while (!(I2C1->ISR & I2C_ISR_RXNE)){}  
	
	for(i = 0;i<4; i++){
			
		if(i<3){
		
		i2c_Read(I2C1, &x[i], _I2C_MASTER_BURST_RECEIVE_CONT );
		Delay_ms(10);
		
		}
		else{
		
		  i2c_Read(I2C1, &x[i], _I2C_MASTER_BURST_RECEIVE_FINISH );
			
		}			
	}
	
	res = (float *)&x;
	
	return res[0];

}
/******************************************************************************/

