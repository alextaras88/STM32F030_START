#include "main.h"

char str[20];
char str1[20];
float Volts = 0;
float temp =0;
float R;

float cof = 0;
float weight = 0;
int zero = 0;

uint8_t spi_buff[30];
int32_t adc_ch[8];

int32_t adc;
uint32_t ad7730_data;
uint8_t i=0;
char buff_rx[16];
uint8_t data = 0;
uint32_t datareg;
//void Get_Weight(void);
//void Get_Zero(void);
//void Get_coff(void);
	
int main(void){
	
	Clock_Init();
	Delay_Init();
	GPIO_Init();
	I2c_Init();
	ssd1306_Init();
	ads1220_Init();
	//ads131_Init();
	//ad7730_Init();
	
	/**************************************************/
//	for(i =0; i<16;i++)
//	{
//	buff_rx[i] = ads131_RREG(i);	
//	Delay_ms(100);
//	
//	}
//	
//	sprintf(str, "%X." "%X." "%X." "%X" , buff_rx[0], buff_rx[1], buff_rx[2], buff_rx[3]);
//	ssd1306_SetCursor(1, 0);
//	ssd1306_WriteString(str, Font_11x18, White);
//	ssd1306_UpdateScreen();
/**************************************************/
		for(i =0; i<4;i++)
	{
	buff_rx[i] = ads1220_RREG(i);	
	Delay_ms(100);
	
	}
	
	sprintf(str, "%X." "%X." "%X." "%X" , buff_rx[0], buff_rx[1], buff_rx[2], buff_rx[3]);
	ssd1306_SetCursor(1, 0);
	ssd1306_WriteString(str, Font_11x18, White);
	ssd1306_UpdateScreen();
/**************************************************/
//	ads131_Offset();
//	Delay_ms(1000);
//	Get_coff();
//	Get_Zero();
//  datareg = ad7730_Read_REG(OFFSET_REG);
//	sprintf(str, "0x%x" , datareg);
//	ssd1306_SetCursor(1, 0);
//	ssd1306_WriteString(str, Font_11x18, White);
//	ssd1306_UpdateScreen();
/**************************************************/	
//	Delay_ms(2000);
	
//	cof = ad7730_Get_Coff(5000);
//	sprintf(str, "COFF:%.4f    ", cof);
//	ssd1306_SetCursor(2, 30);
//	ssd1306_WriteString(str, Font_11x18, White);
//	ssd1306_UpdateScreen();

//	zero = ad7730_Get_Zero(30);
//	zero = 0;
//	zero = ad7730_Get_Zero(20);

	
	
	while(1){
///////////////////////////////////////////////////////////////////////////////////////////		
//			if ((GPIOA->IDR & GPIO_IDR_2) == 0){

//			Delay_ms(200);

//			if ((GPIOA->IDR & GPIO_IDR_2) == 0){

//				GPIOB->ODR |= GPIO_ODR_1;
//				zero =  ad7730_Get_Zero(20);  // get adc value
//				GPIOB->ODR &= ~GPIO_ODR_1;
//				weight = 0;

//		}

//		}
//    
//		weight = ad7730_Get_Weight(10, 167.8f, zero);   // get adc value
//		sprintf(str, "%.4fKg  ", weight/1000);
//		
//		ssd1306_SetCursor(2, 30);
//		ssd1306_WriteString(str, Font_11x18, White);
//		ssd1306_UpdateScreen();
//		
//		weight = 0;
//		GPIOB->ODR ^= GPIO_ODR_1;
///////////////////////////////////////////////////////////////////////////////////////////		
//		ad7730_data = ad7730_GetData();
//		sprintf(str, "%u", ad7730_data);
//		ssd1306_SetCursor(0, 30);
//	  ssd1306_WriteString(str, Font_11x18, White);
//	  ssd1306_UpdateScreen();
//		
//		GPIOB->ODR ^= GPIO_ODR_1;
////////////////////////////////////////////////////////////////		
//		Get_Weight();
////////////////////////////////////////////////////////////////		
//		ads131_Read_Data_Single();
//		Volts = ads131_Get_V(adc_ch[0]);
//		sprintf(str, "%i   ", adc_ch[0]);
//		sprintf(str1, "%.4fmV  ", Volts);
//		
//		ssd1306_SetCursor(0, 20);
//	  ssd1306_WriteString(str, Font_11x18, White);
//		ssd1306_SetCursor(0, 40);
//	  ssd1306_WriteString(str1, Font_11x18, White);
//	  ssd1306_UpdateScreen();
//		//Delay_ms(100);
/////////////////////////////////////////////////////////////////		
		
		Volts = ads1220_Get_V()/1000;
		R = Volts/0.00025f;
		temp = ((R+0.85f)-100.0f)/0.385f;
		sprintf(str, "%.2fC", temp);
		ssd1306_SetCursor(0, 30);
	  ssd1306_WriteString(str, Font_11x18, White);
	  ssd1306_UpdateScreen();
		
		//GPIOB->ODR ^= GPIO_ODR_1;
/////////////////////////////////////////////////////////////////		
	}

}
/******************************************************************************/
//void Get_Weight(void){

//		if ((GPIOA->IDR & GPIO_IDR_2) == 0){

//			Delay_ms(200);

//			if ((GPIOA->IDR & GPIO_IDR_2) == 0){

//				GPIOB->ODR |= GPIO_ODR_1;
//				zero =  ads1220_GetZero(20);  // get adc value
//				GPIOB->ODR &= ~GPIO_ODR_1;
//				weight = 0;

//		}

//		}
//    
//		weight = ads1220_GetWeight(10, 644.9f, zero);   // get adc value
//		sprintf(str, "%.4fKg  ", weight/1000);
//		
//		ssd1306_SetCursor(2, 30);
//		ssd1306_WriteString(str, Font_11x18, White);
//		ssd1306_UpdateScreen();
//		
//		
//		weight = 0;
//		
//}
///******************************************************************************/
//void Get_Zero(void){
//	
//	zero = ads1220_GetZero(10);
//	zero = 0;
//	zero = ads1220_GetZero(20);

//	}
///******************************************************************************/
//void Get_coff(void){

//	cof = ads1220_GetCoff(20, 500);
//  cof = ads1220_GetCoff(20, 500);
//	sprintf(str, "COFF:%.4f    ", cof);
//	ssd1306_SetCursor(2, 30);
//	ssd1306_WriteString(str, Font_11x18, White);
//	ssd1306_UpdateScreen();

//}
///******************************************************************************/
