#include "lcd_i2c.h"

uint8_t portlcd = 0;

/******************************************************************************/
void Write_i2c_lcd(uint8_t data){
	
	i2c_Start_addr(I2C1, LCD_I2C_ADDR, _I2C_MASTER_WRITE);
	i2c_Write(I2C1, _I2C_MASTER_SINGLE_SEND, data);

}
/******************************************************************************/
void send_halfbyte(uint8_t c){
	
	c<<=4;
  e_set(); 
  Delay_us(50);
  Write_i2c_lcd(portlcd|c);
  e_reset();  
  Delay_us(50);

}
/******************************************************************************/
void sendbyte(uint8_t c, uint8_t mode){
	
	if(mode == 0){rs_reset();}
  else{rs_set();}
	uint8_t hc=0;
  hc=c>>4;
  send_halfbyte(hc); 
	send_halfbyte(c);

}
/******************************************************************************/
void Lcd_i2c_Clear(void){
	
	sendbyte(0x01, 0);
	Delay_ms(4);
}
/******************************************************************************/
void Lcd_i2c_Send_char(char ch){
	
	sendbyte(ch,1);

}
/******************************************************************************/
void Lcd_i2c_Set_pos(uint8_t x, uint8_t y){
	
	switch(y){
		case 0:
			sendbyte(x|0x80,0);
			Delay_ms(1);
			break;
    
		case 1:
			sendbyte((0x40+x)|0x80,0);
			Delay_ms(1);
			break;

		case 2:
			sendbyte((0x14+x)|0x80,0);
			Delay_ms(1);
			break;

    case 3:
			sendbyte((0x54+x)|0x80,0);
			Delay_ms(1);
			break;

        }

}
/******************************************************************************/
void Lcd_i2c_Init(void){
	
	Delay_ms(15);
	send_halfbyte(0x03);
	Delay_ms(4);
	send_halfbyte(0x03);
	Delay_us(100);
	send_halfbyte(0x03);
	Delay_ms(1);
	send_halfbyte(0x02);
	Delay_ms(1);
	sendbyte(0x28, 0); 
	Delay_ms(1);
	sendbyte(0x0C, 0); 
	Delay_ms(1);
	sendbyte(0x6, 0); 
	Delay_ms(1);
	setled();
	setwrite();
	
	Lcd_i2c_Clear();

}
/******************************************************************************/
void Lcd_i2c_String(char* st){
	
	uint8_t  i=0;
  while(st[i]!=0){
		
		sendbyte(st[i],1);
		i++;
	
	}

}
/******************************************************************************/
void Lcd_i2c_Send_data(uint32_t data){
	
	Lcd_i2c_Send_char((data%100000000)/10000000 + 0x30);
  Lcd_i2c_Send_char((data%10000000)/1000000 + 0x30);
  Lcd_i2c_Send_char((data%1000000)/100000 + 0x30);
  Lcd_i2c_Send_char((data%100000)/10000 + 0x30);
  Lcd_i2c_Send_char((data%10000)/1000 + 0x30);
  Lcd_i2c_Send_char((data%1000)/100 + 0x30);
  Lcd_i2c_Send_char((data%100)/10 + 0x30);
  Lcd_i2c_Send_char(data%10 + 0x30);

}
/******************************************************************************/
void Lcd_i2c_Send_data_float(float data){
	
	Lcd_i2c_Send_char((unsigned char) (data) +0x30);
  Lcd_i2c_Send_char('.');
  Lcd_i2c_Send_char(((unsigned char) (data*10))%10 + 0x30);
  Lcd_i2c_Send_char(((unsigned char) (data*100))%10 + 0x30);
	Lcd_i2c_Send_char(((unsigned char) (data*1000))%10 + 0x30);
	Lcd_i2c_Send_char(((unsigned char) (data*10000))%10 + 0x30);
	Lcd_i2c_Send_char(((unsigned char) (data*100000))%10 + 0x30);

}
/******************************************************************************/



