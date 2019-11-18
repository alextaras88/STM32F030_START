#ifndef _LCD_I2C_H_
#define _LCD_I2C_H_

#include "stm32f0xx.h"
#include "i2c.h"
#include "delay.h"

/******************************************************************************/
#define  LCD_I2C_ADDR		0x27
/******************************************************************************/
#define e_set()   			Write_i2c_lcd(portlcd|=0x04); 
#define e_reset()   		Write_i2c_lcd(portlcd&=~0x04);  
#define rs_set()   			Write_i2c_lcd(portlcd|=0x01); 
#define rs_reset()  		Write_i2c_lcd(portlcd&=~0x01);  
#define setled()    		Write_i2c_lcd(portlcd|=0x08); 
#define setwrite()   		Write_i2c_lcd(portlcd&=~0x02);  
/******************************************************************************/
void Write_i2c_lcd(uint8_t data);
void Lcd_i2c_Clear(void);
void Lcd_i2c_Send_char(char ch);
void Lcd_i2c_Set_pos(uint8_t x, uint8_t y);
void Lcd_i2c_Init(void);
void Lcd_i2c_String(char* st);
void Lcd_i2c_Send_data(uint32_t data);
void Lcd_i2c_Send_data_float(float data);
/******************************************************************************/

#endif /* _LCD_I2C_H_ */

