#include "main.h"

char str[20];
float Volts = 0;
float temp =0;
float R;

float E, E0, tT, Int, ti, td, p, cInt, cDif, PID;

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

int main(void){
	
	Clock_Init();
	Delay_Init();
	//GPIO_Init();
	I2c_Init();
	ssd1306_Init();
	ads1220_Init();
	
	PWM_TIM3_Init();
	
	tT = 70+1;
	p = 240;
	ti = 18;
	td = 600;

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

	while(1){

		
		Volts = ads1220_Get_V()/1000;
		R = Volts/0.00025f;
		temp = ((R+0.85f)-100.0f)/0.385f;
		
		E0 = E; 
		E = tT - temp; 
		Int = Int+(E + E0)/2; 
		cInt = Int*(1/ti); 
		cDif = td*(E-E0); 
		PID = (p*E + cInt + cDif);
		
		if(PID>=999){PID = 999;}
		if(PID<=0){PID = 0;}
		
		TIM3->CCR4 = (uint16_t)PID;
		
		sprintf(str, "%.1fC " "%u  ", temp,(uint16_t)PID );	
		ssd1306_SetCursor(0, 25);
	  ssd1306_WriteString(str, Font_11x18, White);
	  ssd1306_UpdateScreen();
			
	}

}
