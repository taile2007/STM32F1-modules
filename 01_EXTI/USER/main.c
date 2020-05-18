#include "stm32f10x.h"                  // Device header

#include "LED.h"
#include "exti.h"
#include "delay.h"


/************************************************
www.stm32vn.com
************************************************/
 
 int main(void)
 {	
	 LED_init();
	 EXTIx_Init(GPIOA, GPIO_Pin_5, Trigger_Rising);
	 EXTIx_Init(GPIOB, GPIO_Pin_5, Trigger_Falling);
	 delay_init();
	
  while(1)
	{
//	    LED0 =0;//GPIO_ResetBits(GPIOB,GPIO_Pin_5);
//	    GPIO_SetBits(GPIOE,GPIO_Pin_5);
//		delay_ms(300);
//			LED0 =1;GPIO_SetBits(GPIOB,GPIO_Pin_5);
//			GPIO_ResetBits(GPIOE,GPIO_Pin_5);
//		delay_ms(300);
		

		
	}
 }


