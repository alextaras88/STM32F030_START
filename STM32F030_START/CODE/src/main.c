#include "main.h"

uint8_t str1[MFRC522_MAX_LEN];

char str[40];
uint8_t crc[2];

uint32_t value = 0;
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
//uint32_t datareg;
//void Get_Weight(void);
//void Get_Zero(void);
//void Get_coff(void);
void GetCrc(uint8_t *value, uint16_t cnt);

int main(void){
	
	Clock_Init();
	Delay_Init();
	GPIO_Init();
	I2c_Init();
	ssd1306_Init();
	//mfrc522_Init();
	ads1220_Init();
	//ads131_Init();
	//ad7730_Init();
	
//	ssd1306_SetCursor(25, 0);
//	ssd1306_WriteString("MFRC522", Font_11x18, White);
//	ssd1306_UpdateScreen();
//	
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
//		
//		mfrc522_WriteREG(0x09,0x52);
//		mfrc522_WriteREG(0x01,0x0C);
//		mfrc522_WriteREG(0x0D,0x87);
//		Delay_ms(1);
//		
//		if (mfrc522_ReadREG(0x8A) == 0x02 && mfrc522_ReadREG(0x89) == 0x44 && mfrc522_ReadREG(0x89) == 0x00){
//		
//		
//		
//	//if (!mfrc522_Request(PICC_REQALL, uid)){
//		
//		mfrc522_WriteREG(0x0A,0x80);

//		mfrc522_WriteREG(0x09, 0x93);
//		mfrc522_WriteREG(0x09, 0x20);
//		mfrc522_WriteREG(0x01, 0x0C);
//		mfrc522_WriteREG(0x0D, 0x80);
//		Delay_ms(1);
//		
//			//mfrc522_Anticoll(0x93, str);
//		uint8_t uid[10] = {mfrc522_ReadREG(0x89),mfrc522_ReadREG(0x89),mfrc522_ReadREG(0x89),mfrc522_ReadREG(0x89),mfrc522_ReadREG(0x89), };
//			
//		mfrc522_WriteREG(0x0a,0x80);
//		
//		uint8_t crc_1[]={0x93,0x70,uid[0],uid[1],uid[2],uid[3],uid[4]};	
//		GetCrc(crc_1,7);
//		
//		mfrc522_WriteREG(0x0a,0x80);
//		
//		mfrc522_WriteREG(0x09,0x93);
//    mfrc522_WriteREG(0x09,0x70);
//		
//		mfrc522_WriteREG(0x09,uid[0]);
//		mfrc522_WriteREG(0x09,uid[1]);
//		mfrc522_WriteREG(0x09,uid[2]);
//		mfrc522_WriteREG(0x09,uid[3]);
//		mfrc522_WriteREG(0x09,uid[4]);
//		
//		mfrc522_WriteREG(0x09,crc[0]);
//    mfrc522_WriteREG(0x09,crc[1]);
//		
//		mfrc522_WriteREG(0x01,0x0C);
//    mfrc522_WriteREG(0x0d,0x80);
//		
//		str[0] = mfrc522_ReadREG(0x89);
//		str[1] = mfrc522_ReadREG(0x89);
//		str[2] = mfrc522_ReadREG(0x89);
//		
//    mfrc522_WriteREG(0x0a,0x80);

//		mfrc522_WriteREG(0x09,0x95);
//		mfrc522_WriteREG(0x09,0x20);
//		mfrc522_WriteREG(0x01,0x0C);
//		mfrc522_WriteREG(0x0D,0x80);
// 
//		Delay_ms(1);

//  //Читаем UID3 UID4 UID5 UID6 BCC
//		uid[5] = mfrc522_ReadREG(0x89);
//		uid[6] = mfrc522_ReadREG(0x89);
//		uid[7] = mfrc522_ReadREG(0x89);
//		uid[8] = mfrc522_ReadREG(0x89);
//		uid[9] = mfrc522_ReadREG(0x89);
//		
//		uint8_t crc_2[]={0x95,0x70,uid[5],uid[6],uid[7],uid[8],uid[9]};
//		
//		GetCrc(crc_2,7);
// 
//  //Отправляем селект 2
//		mfrc522_WriteREG(0x09,0x95);
//		mfrc522_WriteREG(0x09,0x70);
//		//Добавляем к строке вторую часть UID
//		mfrc522_WriteREG(0x09,uid[5]);
//		mfrc522_WriteREG(0x09,uid[6]);
//		mfrc522_WriteREG(0x09,uid[7]);
//		mfrc522_WriteREG(0x09,uid[8]);
//		mfrc522_WriteREG(0x09,uid[9]);
//		//Добавляем к строке CRC
//		mfrc522_WriteREG(0x09,crc[0]);
//		mfrc522_WriteREG(0x09,crc[1]);
//		//Отправка
//		mfrc522_WriteREG(0x01,0x0C);
//		mfrc522_WriteREG(0x0d,0x80);
// 
//		Delay_ms(1);

//		//Читаем ответ
//		str[4] = (mfrc522_ReadREG(0x89));
//		str[5] = (mfrc522_ReadREG(0x89));
//		str[6] = (mfrc522_ReadREG(0x89));
//		str[7] = (mfrc522_ReadREG(0x89));
//		
//		mfrc522_WriteREG(0x09,0xE0);
//    mfrc522_WriteREG(0x09,0x20);
//		
//		//Нет смысла напрягать сопроцессор,- для 0xE0 0x20 CRC калькулировался заранее)
//    mfrc522_WriteREG(0x09,0x3b);
//    mfrc522_WriteREG(0x09,0xd6);
//   //Отправка
//    mfrc522_WriteREG(0x01,0x0c);
//    mfrc522_WriteREG(0x0d,0x80);
//		
//		str[0] = mfrc522_ReadREG(0x89);
//		str[1] = mfrc522_ReadREG(0x89);
//		str[2] = mfrc522_ReadREG(0x89);
//		str[3] = mfrc522_ReadREG(0x89);
//		str[4] = mfrc522_ReadREG(0x89);
//		str[5] = mfrc522_ReadREG(0x89);
//		str[6] = mfrc522_ReadREG(0x89);
//		str[7] = mfrc522_ReadREG(0x89);

//		
//	
//		str[0] = uid[1];
//		str[1] = uid[2];
//		str[2] = uid[3];
//		str[3] = uid[5];
//		str[4] = uid[6];
//		str[5] = uid[7];
//		str[6] = uid[8];


//		sprintf(str1, "%X" "%X" "%X" "%X" "%X" "%X" "%X",  str[0], str[1], str[2], str[3], str[4], str[5], str[6]);
//	  ssd1306_SetCursor(2, 30);
//	  ssd1306_WriteString(str1, Font_11x18, White);
//	  ssd1306_UpdateScreen();			
		
		
		
//					sprintf(str1, "%X" "%X" "%X" "%X" "%X" "%X" "%X",  uid[1], uid[2], uid[3], uid[4], uid[5], uid[6], uid[7]);
//					ssd1306_SetCursor(2, 30);
//					ssd1306_WriteString(str1, Font_11x18, White);
//					ssd1306_UpdateScreen();
//				
//			}
//	Delay_ms(500);

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
		
		Volts = ads1220_Get_V();
//		R = Volts/0.00025f;
//		temp = ((R+0.96f)-100.0f)/0.385f;
		sprintf(str, "%.4fV  ", Volts);
		ssd1306_SetCursor(0, 30);
	  ssd1306_WriteString(str, Font_11x18, White);
	  ssd1306_UpdateScreen();
		
		GPIOB->ODR ^= GPIO_ODR_1;
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
void GetCrc(uint8_t *value, uint16_t cnt){
	
  crc[0]=0;
  crc[1]=0;
  uint16_t i = 0;
	
  mfrc522_WriteREG(0x0A,0x80);
  
  while (i<cnt){
    mfrc522_WriteREG(0x09,value[i]);
    i++;
  }
  mfrc522_WriteREG(0x01,0x03);
  crc[0] = mfrc522_ReadREG(0xA2);
  crc[1] = mfrc522_ReadREG(0xA1);
  mfrc522_WriteREG(0x01,0x00);
}

