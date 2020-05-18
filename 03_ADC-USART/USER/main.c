#include "stm32f10x.h"
#include "LED.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "adc.h"

/************************************************
www.stm32vn.com
************************************************/

extern uint16_t ADC_ConvertedValue;
 
 int main(void)
 {	
	 u8 c=0;
	 u16 adcx=0;
	 float  temp=0;
	 char buffer[100];
	 //LED_init();
	 delay_init();
	 
	 USARTx_Init(USART1, Pins_PA9PA10, 115200);
	 Adc_Init(ADC1,ADC_Channel_0);
	
  while(1)
	{
		c=USART_Getc(USART1);
		if(c) USART_Putc(USART1,c);
//		
//		if (USART_Gets(USART1, buffer, sizeof(buffer))) 	printf("%s\r\n",buffer);//USART_Puts(USART1,buffer);
//		
//	
		//adcx=Get_Adc_Average(ADC1,ADC_Channel_0,10); // for using DAC without DMA
		
		temp = (float)ADC_ConvertedValue*(3.3/4096); // we are using DMA for sampling ADC for this..............
		adcx=temp;
		//xuat LCD-UART
		printf("%f\n",temp);
//		
//		delay_ms(250);
		
//	digitalWrite( PB5, HIGH );delay_ms(300);
//	digitalWrite( PB5, LOW );delay_ms(300);
	}
 }
