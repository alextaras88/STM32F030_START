#include "adc.h"

/******************************************************************************/
void ADC_Init(void){
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;							// Clock GPIO A
	RCC->APB2ENR |= RCC_APB2ENR_ADCEN;							// Clock ADC
	
	GPIOA->MODER |= GPIO_MODER_MODER6;							// PA6 - Analog Input
	            
	ADC1->CFGR1 = 0x00000000;                       // Clear reg
	
	ADC1->CFGR1 = (0<26);														// AWDCH[4:0]: Analog watchdog channel selection CH0
	ADC1->CFGR1 |= ADC_CFGR1_CONT;                  // Continues mode   
	
	ADC1->SMPR = 0x07;                              // 239.5 ADC clock cycles   
	
	
  if(ADC1->CR & ADC_CR_ADEN){
		
		ADC1->CR |= ADC_CR_ADDIS;										  // Disable ADC 
    while (ADC1->CR & ADC_CR_ADEN){}
				
    }
	 
  ADC1->CR |= ADC_CR_ADCAL;                       // Calibrate ADC 
  while(ADC1->CR & ADC_CR_ADCAL) {}
    
    
  ADC1->CFGR2 = 0;															  // Reset configuration 
	ADC1->CFGR2 &= ~ADC_CFGR2_CKMODE;
  ADC1->CFGR2 = ADC_CFGR2_CKMODE_1;							  // ADC Clock PCLK/4
    
  ADC1->CR = ADC_CR_ADEN;												  // Enable device 
  while(!(ADC1->ISR & ADC_ISR_ADRDY));
			
	ADC1->IER |= ADC_IER_EOCIE;                     // Enable for EOC Interrupt     
  NVIC_EnableIRQ(ADC1_COMP_IRQn);  	

	ADC1->CR |= ADC_CR_ADSTART;                     // Start A/D conversion 
	
  ADC1->CHSELR = (1<<6);												  // Set CH6	

}
/******************************************************************************/
//void ADC1_COMP_IRQHandler(void) {

//    if (ADC1->ISR & ADC_ISR_EOC) {
//			
//           /* ADC1 EOC interrupt?  */
//        adc_data = ADC1->DR;
//			GPIOB->ODR ^= GPIO_ODR_1;

//        ADC1->ISR |= ADC_ISR_EOC;
//    }
//}
/******************************************************************************/

