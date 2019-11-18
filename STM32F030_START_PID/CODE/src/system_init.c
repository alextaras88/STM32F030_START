#include "system_init.h"

/******************************************************************************/
void Clock_Init(void){
	
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);			  				// Enable HSI
	while(!(RCC->CR & RCC_CR_HSERDY));             		  // Wait HSI enable flag
	
	FLASH->ACR = (uint32_t)0x21;												// Prefetch buffer enable, One wait state, if 24 MHz < SYSCLK = 48 MHz
	
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;	                  // AHB/1
	RCC->CFGR |= RCC_CFGR_PPRE_DIV1;				  		      // APB1/1
	
	RCC->CFGR3 |= RCC_CFGR3_I2C1SW;											// I2C Clock SYSCLK(48MHz)
	RCC->CFGR3 |= RCC_CFGR3_USART1SW_SYSCLK;						// USART1 Clock SYSCLK
	RCC->CFGR |= RCC_CFGR_PLLSRC;									      // HSE , DIV1
	RCC->CFGR |= RCC_CFGR_PLLMUL3;									    // 3x16 = 48MHz

	RCC->CR |= RCC_CR_PLLON;                      	    // Enable PLL
	while((RCC->CR & RCC_CR_PLLRDY) == 0){}             // Wait PLL enable flag
			
	RCC->CFGR &= ~RCC_CFGR_SW;                   		    // Reset SW
	RCC->CFGR |= RCC_CFGR_SW_PLL;                 			// SYSCLK = PLL
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {}// Wait PLL-SYSCLK flag
		
}
/******************************************************************************/
void GPIO_Init(void){
	
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;								  // Clock PORT B
	//LED1
  GPIOB->MODER |= GPIO_MODER_MODER1_0;   			 			  // OUT PB_1
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_1;  							  // Push pull
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_1;	     	  // High speed

}
/******************************************************************************/

/******************************************************************************/




