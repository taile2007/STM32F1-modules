#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "delay.h"


int main(void)
 {	
	 LED_init();
	 delay_init();
 
  while(1)
	{
	    GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	    GPIO_SetBits(GPIOE,GPIO_Pin_14);
			delay_ms(300);
			GPIO_SetBits(GPIOB,GPIO_Pin_14);
			GPIO_ResetBits(GPIOE,GPIO_Pin_14);
			delay_ms(300);
	}
 }

 
 
 
 