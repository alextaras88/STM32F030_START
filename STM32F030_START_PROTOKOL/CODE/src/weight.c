#include "weight.h"

/******************************************************************************/
int32_t ads1220_GetZero(uint8_t time){
	
	int32_t zero = 0;
	uint8_t i;
	
	for(i = 0; i<time; i++){
		
		zero += ads1220_GetData();
		Delay_ms(5);
		
	}
	zero/=(int32_t)time;
	
	return zero;

}
/******************************************************************************/
float ads1220_GetWeight(uint32_t time, float coff, int32_t zero){
	
	float weight = 0;
	uint32_t i;
	
	for( i = 0; i<time; i++){
		
		weight += (float)ads1220_GetData();
	}
	
	weight /= time;
	weight -= (float)zero;
	weight /= coff;
	
	return (float)weight;
	
}
/******************************************************************************/
float ads1220_GetCoff(uint8_t time, uint16_t weight){
	
	int32_t zero = 0;
	int32_t weight1 = 0;
	
	zero = ads1220_GetZero(time);
	GPIOB->ODR |= GPIO_ODR_1;
	Delay_ms(5000);
	
  weight1 = ads1220_GetZero(time); 
	GPIOB->ODR &= ~GPIO_ODR_1;
	
	return (float)(weight1 - zero)/weight;

}
/******************************************************************************/

/******************************************************************************/

/******************************************************************************/

/******************************************************************************/

