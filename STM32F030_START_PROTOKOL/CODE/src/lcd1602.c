#include "lcd1602.h"

/******************************************************************************/
void lcd1602_GPIO_Init(void){
	
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;								 	 	// Clock PORT B
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;								 		// Clock PORT C
	
	
	// RS
  GPIOB->MODER |= GPIO_MODER_MODER14_0;   			 			  // OUT  PB14
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_14;  							  // Push pull
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_1;	     	  // High speed
	RS_LOW;
	// E
	GPIOB->MODER |= GPIO_MODER_MODER15_0;   			 			  // OUT  PB15
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_15;  							  // Push pull
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15_1;	     	  // High speed
	E_LOW;
	// D4
	GPIOC->MODER |= GPIO_MODER_MODER9_0;   			 			  	// OUT 	PC9
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_9;  							  	// Push pull
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1;	     	  	// High speed
	D4_LOW;
	// D5
	GPIOC->MODER |= GPIO_MODER_MODER6_0;   			 			  	// OUT 	PC6
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_6;  							  	// Push pull
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;	     	  	// High speed
	D5_LOW;
	// D6
	GPIOC->MODER |= GPIO_MODER_MODER8_0;   			 			  	// OUT 	PC8
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_8;  							  	// Push pull
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8_1;	     	  	// High speed
	D6_LOW;
	// D7
	GPIOC->MODER |= GPIO_MODER_MODER7_0;   			 			   	// OUT  PC7
	GPIOC->OTYPER &= ~GPIO_OTYPER_OT_7;  							   	// Push pull
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7_1;	     	   	// High speed
	D7_LOW;

}
/******************************************************************************/
void lcd1602_Write_Data(uint8_t data){
	
	if(((data >> 3)&0x01)==1) {D7_HIGH;} else {D7_LOW;} 
  if(((data >> 2)&0x01)==1) {D6_HIGH;} else {D6_LOW;}
  if(((data >> 1)&0x01)==1) {D5_HIGH;} else {D5_LOW;}
  if((data&0x01)==1) {D4_HIGH;} else {D4_LOW;}

}
/******************************************************************************/
void lcd1602_Command(uint8_t command){
	
	RS_LOW;;
  lcd1602_Write_Data(command>>4);
  E_HIGH;
  Delay_us(DELAY_LCD);
  E_LOW;
  lcd1602_Write_Data(command);
  E_HIGH
  Delay_us(DELAY_LCD);
	E_LOW;
	
}
/******************************************************************************/
void lcd1602_Data(uint8_t data){
	
	RS_HIGH;
  lcd1602_Write_Data(data>>4);
  E_HIGH;
  Delay_us(DELAY_LCD);
  E_LOW;
  lcd1602_Write_Data(data);
  E_HIGH
  Delay_us(DELAY_LCD);
	E_LOW;

}
/******************************************************************************/
void lcd1602_Clear(void){
	
	lcd1602_Command(0x01);
	Delay_ms(4);

}
/******************************************************************************/
void lcd1602_SendChar(char cr){
	
	lcd1602_Data((uint8_t)cr);
	Delay_us(DELAY_LCD);

}
/******************************************************************************/
void lcd1602_String(char* str){
	
	uint8_t i=0;
	
	while(str[i]!=0){
		
		lcd1602_Data(str[i]);
	  Delay_us(DELAY_LCD);
		i++;
	
	}

}
/******************************************************************************/
void lcd1602_Set_Pos(uint8_t x, uint8_t y){
	
	switch(y){
		
		case 0:
			lcd1602_Command(x|0x80);
			Delay_ms(3);
			break;
    
		case 1:
			lcd1602_Command((0x40+x)|0x80);
			Delay_ms(3);
			break;

		case 2:
			lcd1602_Command((0x10+x)|0x80);
			Delay_ms(3);
			break;

    case 3:
			lcd1602_Command((0x50+x)|0x80);
			Delay_ms(3);
			break;
	
	}
}
/******************************************************************************/
void lcd1602_Init(void){
	
	lcd1602_GPIO_Init();
	
	Delay_ms(200);
	
	RS_LOW;
	lcd1602_Write_Data(0x30);
	E_HIGH;
	Delay_us(DELAY_LCD);
	E_LOW;
	Delay_ms(1);
	
	lcd1602_Write_Data(0x30);
	E_HIGH;
	Delay_us(DELAY_LCD);
	E_LOW;
	Delay_ms(1);
	
	lcd1602_Write_Data(0x30);
	E_HIGH;
	Delay_us(DELAY_LCD);
	E_LOW;
	Delay_ms(1);
	
	lcd1602_Command(0x28);
	Delay_ms(1);
	lcd1602_Command(0x28);
	Delay_ms(1);
	lcd1602_Command(0x0C);
	Delay_ms(1);
	lcd1602_Command(0x01);
	Delay_ms(2);
	lcd1602_Command(0x06);
	Delay_ms(1);
	lcd1602_Command(0x02);
	Delay_ms(2);
	
	lcd1602_Clear();
	
}
/******************************************************************************/

