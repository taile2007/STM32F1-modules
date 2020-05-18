#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"


/************************************************
www.stm32vn.com
************************************************/


 
 int main(void)
 {	
	 u8 c=0;
	 char buffer[100];
	 //LED_init();
	 delay_init();
//	 pinMode(PB5,OUTPUT);
//	 pinMode(PB6,INPUT);
	 
	 USARTx_Init(USART1, Pins_PA9PA10, 115200);
		
 
  while(1)
	{
//		c=USART_Getc(USART1);
//		if(c) USART_Putc(USART1,c);
		
		if (USART_Gets(USART1, buffer, sizeof(buffer))) 	
			printf("%s\r\n",buffer);//USART_Puts(USART1,buffer);
		
		
		
//	digitalWrite( PB5, HIGH );delay_ms(300);
//	digitalWrite( PB5, LOW );delay_ms(300);
	}
 }
