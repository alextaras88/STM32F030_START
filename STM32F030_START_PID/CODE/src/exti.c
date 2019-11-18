#include "exti.h"

/******************************************************************************/
void GPAOA_0_EXTI(void){
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;											// Clock GPIOA
	
	GPIOA->MODER &= ~GPIO_MODER_MODER0;											// Input, Open drain, Push-UP
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_0;
	//GPIOA->BSRR |= GPIO_BSRR_BS_0;
	SYSCFG->EXTICR[0]|=SYSCFG_EXTICR1_EXTI0_PA;
	EXTI->IMR |= EXTI_IMR_MR0;
	EXTI->RTSR |= EXTI_RTSR_TR0;
	EXTI->FTSR |= EXTI_FTSR_TR0;
	
	NVIC_EnableIRQ(EXTI0_1_IRQn);
	
	__enable_irq ();
	
}
/******************************************************************************/
void GPAOA_1_EXTI(void){
	
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;											// Clock GPIOA
	
	GPIOA->MODER &= ~GPIO_MODER_MODER1;											// Input, Open drain, Push-UP
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR1_0;
	//GPIOA->BSRR |= GPIO_BSRR_BS_1;
	SYSCFG->EXTICR[0]|=SYSCFG_EXTICR1_EXTI1_PA;
	EXTI->IMR |= EXTI_IMR_MR1;
	EXTI->RTSR |= EXTI_RTSR_TR1;
	EXTI->FTSR |= EXTI_FTSR_TR1;
	
	NVIC_EnableIRQ(EXTI0_1_IRQn);
	
	__enable_irq ();
	
}
/******************************************************************************/
//void EXTI0_1_IRQHandler(void)
//{
//	
//	if(EXTI->PR & (1<<0)){
//		
//		EXTI->PR |= (1<<0);
//		GPIOB->ODR |= GPIO_ODR_1;					
//            
//  }
//  if(EXTI->PR & (1<<1)){
//		
//		EXTI->PR |= (1<<1);
//		GPIOB->ODR &=   ~GPIO_ODR_1;				
//  
//	} 
//      
//}	
/******************************************************************************/
