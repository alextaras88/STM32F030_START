#include "pwm.h"

/******************************************************************************/
void PWM_TIM3_Init(void){
	
	// GPIO INIT
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;											// Clock GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;											// Clock GPIOB
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;								      // Clock TIM3
	
	GPIOA->AFR[0] |= (1<<24);																// PA6 TIM3_CH1	AF1 
  GPIOA->AFR[0] |= (1<<28);																// PA7 TIM3_CH2	AF1
  GPIOB->AFR[0] |= (1<<4);																// PB1 TIM3_CH4	AF1	
	
	// PA6 PWM OUT CH1 **********************************************
	GPIOA->MODER |=   GPIO_MODER_MODER6_1;							   // AF OutPut Push_Pull
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_6;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;				       // Full Speed
	
	// PA7 PWM OUT CH1 **********************************************
	GPIOA->MODER |=   GPIO_MODER_MODER7_1;							   // AF OutPut Push_Pull
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_7;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7;				       // Full Speed
	
	// PA1 PWM OUT CH1 **********************************************
	GPIOB->MODER |=   GPIO_MODER_MODER1_1;							   // AF OutPut Push_Pull
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_1;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1;				       // Full Speed
	
	TIM3->PSC = 48- 1;
	TIM3->ARR = 1000;
	
	TIM3->CCR1 = 500;
	TIM3->CCR2 = 500;
	TIM3->CCR4 = 500;
	
	// CH1 **********************************************
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	TIM3->CCER |= TIM_CCER_CC1E;
	TIM3->CCER &= ~TIM_CCER_CC1P;
	
	// CH2 **********************************************
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
	TIM3->CCER |= TIM_CCER_CC2E;
	TIM3->CCER &= ~TIM_CCER_CC2P;
	
	// CH4 **********************************************
	TIM3->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
	TIM3->CCER |= TIM_CCER_CC4E;
	TIM3->CCER &= ~TIM_CCER_CC4P;
	
	TIM3->CR1 &= ~TIM_CR1_DIR;
	TIM3->CR1 |= TIM_CR1_CEN;
	
}
/******************************************************************************/
void PWM_TIM14_Init(void){
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;											// Clock GPIOA
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;								    // Clock TIM14
	
	GPIOA->AFR[0] |= (4<<16);																// PA4 TIM14_CH1	AF4
	
	// PA4 PWM OUT CH1 **********************************************
	GPIOA->MODER |=   GPIO_MODER_MODER4_1;							   // AF OutPut Push_Pull
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_4;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;				       // Full Speed
	
	TIM14->PSC = 48 - 1;
	TIM14->ARR = 1000;
	
	TIM14->CCR1 = 500;
	
	
	// CH1 **********************************************
	TIM14->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	TIM14->CCER |= TIM_CCER_CC1E;
	TIM14->CCER &= ~TIM_CCER_CC1P;
	
	TIM14->CR1 &= ~TIM_CR1_DIR;
	TIM14->CR1 |= TIM_CR1_CEN;
	
}
/******************************************************************************/
void PWM_TIM16_Init(void){
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;											// Clock GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;								    // Clock TIM16
	
	GPIOA->AFR[0] |= (5<<24);																// PA6 TIM16_CH1	AF5
	
	// PA6 PWM OUT CH1 **********************************************
	GPIOA->MODER |=   GPIO_MODER_MODER6_1;							    // AF OutPut Push_Pull
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_6;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;				        // Full Speed
	
	TIM16->PSC = 48 - 1;
	TIM16->ARR = 1000;
	
	TIM16->CCR1 = 500;
	
	// CH1 **********************************************
	TIM16->CCMR1 |=  TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	TIM16->CCER |= TIM_CCER_CC1E;
	TIM16->CCER &= ~TIM_CCER_CC1P;
	
	TIM16->BDTR &= ~TIM_BDTR_DTG;																				  // clear register
	TIM16->BDTR |= TIM_BDTR_DTG_2 | TIM_BDTR_DTG_1 | TIM_BDTR_DTG_0;			// value dead-time: = 31*Tdts = 32*41,6ns = 1.29us 

	TIM16->BDTR |= TIM_BDTR_MOE | TIM_BDTR_AOE;							
	
	TIM16->CR1 &= ~TIM_CR1_DIR;
	TIM16->CR1 &= ~TIM_CR1_CMS;
	TIM16->CR1 |= TIM_CR1_CEN;
	
}
/******************************************************************************/



