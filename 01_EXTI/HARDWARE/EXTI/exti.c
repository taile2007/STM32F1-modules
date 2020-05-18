#include "exti.h"
#include "delay.h" 
#include "led.h" 
//#include "key.h"
//#include "beep.h"
//////////////////////////////////////////////////////////////////////////////////	 
uint8_t t=0;			  
////////////////////////////////////////////////////////////////////////////////// 
#define B5  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)

void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);	 
	 if(B5==0) t++;
	 EXTI_ClearITPendingBit(EXTI_Line5|EXTI_Line6|EXTI_Line7|EXTI_Line8|EXTI_Line9);  
}

//void EXTI0_IRQHandler(void)
//{
//	delay_ms(10);	
//	if(WK_UP==1)	 
//	{
//		t++;
//		BEEP=!BEEP; 
//		LED1=!LED1;
//	}		 
//	 EXTI_ClearITPendingBit(EXTI_Line0); 
//}	

//void EXTI2_IRQHandler(void)
//{
//	delay_ms(10);	
//	if(KEY2==1)	  
//	{				 
//   LED0=!LED0; 
//	}		 
//	 EXTI_ClearITPendingBit(EXTI_Line2);
//}

//void EXTI3_IRQHandler(void)
//{
//	delay_ms(10);	
//	if(KEY1==1)	 
//	{
//		LED1=!LED1;
//	}		 
//	 EXTI_ClearITPendingBit(EXTI_Line3);    
//}

//void EXTI4_IRQHandler(void)
//{
//	delay_ms(10);	
//	if(KEY0==1)	 
//	{				 
//		LED0=!LED0;	
//		LED1=!LED1;	
//	}		 
//	 EXTI_ClearITPendingBit(EXTI_Line4);  
//}
//	   
//***** From ST Lib ***********************///

//void EXTIX_Init(void)
//{
// uint32_t gpio_clock;
//	uint8_t pinsource, portsource, irqchannel;
// 	EXTI_InitTypeDef EXTI_InitStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure;

//    KEY_Init();	 //	GPIO

//  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	

//    //GPIOE.2 	//KEY2
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;	//KEY2
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//EXTI_Init

//   //GPIOE.3	   //KEY1
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
//  	EXTI_Init(&EXTI_InitStructure);	  	//EXTI_Init

//   //GPIOE.4	  //KEY0
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
//  	EXTI_Init(&EXTI_InitStructure);	  	//EXTI_Init


//   //GPIOA.0	  //  WK_UP
// 	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//  	EXTI_Init(&EXTI_InitStructure);		//EXTI_Init


//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//WK_UP
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
//  	NVIC_Init(&NVIC_InitStructure); 

//    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//KEY2
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
//  	NVIC_Init(&NVIC_InitStructure);


//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//KEY1
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					 
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
//  	NVIC_Init(&NVIC_InitStructure);  	  //NVIC

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//KEY0
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								
//  	NVIC_Init(&NVIC_InitStructure);  	  //NVIC
// 
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////



void EXTIx_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, EXTI_Trigger_t trigger) {
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	uint32_t gpio_clock;
	uint8_t pinsource, portsource, irqchannel;
	
	
	/* Enable clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	/* Get proper settings */
	if (GPIOx == GPIOA) {
		gpio_clock = RCC_APB2Periph_GPIOA;
		portsource = GPIO_PortSourceGPIOA;
	} else if (GPIOx == GPIOB) {
		gpio_clock = RCC_APB2Periph_GPIOB;
		portsource = GPIO_PortSourceGPIOB;
	} else if (GPIOx == GPIOC) {
		gpio_clock = RCC_APB2Periph_GPIOC;
		portsource = GPIO_PortSourceGPIOC;
	} else if (GPIOx == GPIOD) {
		gpio_clock = RCC_APB2Periph_GPIOD;
		portsource = GPIO_PortSourceGPIOD;
	} else if (GPIOx == GPIOE) {
		gpio_clock = RCC_APB2Periph_GPIOE;
		portsource = GPIO_PortSourceGPIOE;
	} else if (GPIOx == GPIOF) {
		gpio_clock = RCC_APB2Periph_GPIOF;
		portsource = GPIO_PortSourceGPIOF;
	} else if (GPIOx == GPIOG) {
		gpio_clock = RCC_APB2Periph_GPIOG;
		portsource = GPIO_PortSourceGPIOG;
	} 
//		else if (GPIOx == GPIOH) {
//		gpio_clock = RCC_APB2Periph_GPIOH;
//		portsource = EXTI_PortSourceGPIOH;
//	} else if (GPIOx == GPIOI) {
//		gpio_clock = RCC_AHB1Periph_GPIOI;
//		portsource = EXTI_PortSourceGPIOI;
//	} else if (GPIOx == GPIOJ) {
//		gpio_clock = RCC_AHB1Periph_GPIOJ;
//		portsource = EXTI_PortSourceGPIOJ;
//	} else if (GPIOx == GPIOK) {
//		gpio_clock = RCC_AHB1Periph_GPIOK;
//		portsource = EXTI_PortSourceGPIOK;
//	}
		else {
		;
	}
	
	switch (GPIO_Pin) {
		case GPIO_Pin_0:
			pinsource = GPIO_PinSource0;
			irqchannel = EXTI0_IRQn;
			break;
		case GPIO_Pin_1:
			pinsource = GPIO_PinSource1;
			irqchannel = EXTI1_IRQn;
			break;
		case GPIO_Pin_2:
			pinsource = GPIO_PinSource2;
			irqchannel = EXTI2_IRQn;
			break;
		case GPIO_Pin_3:
			pinsource = GPIO_PinSource3;
			irqchannel = EXTI3_IRQn;
			break;
		case GPIO_Pin_4:
			pinsource = GPIO_PinSource4;
			irqchannel = EXTI4_IRQn;
			break;
		/*
		* Interrupt line
		**/
		case GPIO_Pin_5:
			pinsource = GPIO_PinSource5;
			irqchannel = EXTI9_5_IRQn;
			break;
		case GPIO_Pin_6:
			pinsource = GPIO_PinSource6;
			irqchannel = EXTI9_5_IRQn;
			break;
		case GPIO_Pin_7:
			pinsource = GPIO_PinSource7;
			irqchannel = EXTI9_5_IRQn;
			break;
		case GPIO_Pin_8:
			pinsource = GPIO_PinSource8;
			irqchannel = EXTI9_5_IRQn;
			break;
		case GPIO_Pin_9:
			pinsource = GPIO_PinSource9;
			irqchannel = EXTI9_5_IRQn;
			break;
		case GPIO_Pin_10:
			pinsource = GPIO_PinSource10;
			irqchannel = EXTI15_10_IRQn;
			break;
		case GPIO_Pin_11:
			pinsource = GPIO_PinSource11;
			irqchannel = EXTI15_10_IRQn;
			break;
		case GPIO_Pin_12:
			pinsource = GPIO_PinSource12;
			irqchannel = EXTI15_10_IRQn;
			break;
		case GPIO_Pin_13:
			pinsource = GPIO_PinSource13;
			irqchannel = EXTI15_10_IRQn;
			break;
		case GPIO_Pin_14:
			pinsource = GPIO_PinSource14;
			irqchannel = EXTI15_10_IRQn;
			break;
		case GPIO_Pin_15:
			pinsource = GPIO_PinSource15;
			irqchannel = EXTI15_10_IRQn;
			break;
		default:
			break;
	}
	
	/*
	STEP 1: Config GPIO
	*/
	/* Enable clock for GPIO */
	RCC_APB2PeriphClockCmd(gpio_clock, ENABLE);
	
	/* Set pin as input */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	if (trigger == Trigger_Falling) {
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	} else if (trigger == Trigger_Rising) {
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	} else {
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	}
	
	/* Initialize pin */
	GPIO_Init(GPIOx, &GPIO_InitStruct);
	
	/* Connect proper GPIO */
	GPIO_EXTILineConfig(portsource, pinsource);
	
	/////////////////////////////////////////////////
	
	/* Enable EXTI */
	EXTI_InitStruct.EXTI_Line = GPIO_Pin;  // the value of GPIO_Pin_x is similar to EXTI_Line_x
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = (EXTITrigger_TypeDef)trigger;
	EXTI_Init(&EXTI_InitStruct);

	/* Add to NVIC */
	NVIC_InitStruct.NVIC_IRQChannel = irqchannel;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = EXTI_PRIORITY;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = pinsource;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	
}







