/**	
 * |----------------------------------------------------------------------
 * |  *  02, 2014
 *	- Added support for measure Vbat pin with ADC
 *	
 * Pinout
 *	CHANNEL			ADC1	ADC2	ADC3
 *	0							PA0		PA0		PA0
 *	1							PA1		PA1		PA1
 *	2							PA2		PA2		PA2
 *	3							PA3		PA3		PA3
 *	4							PA4		PA4		PF6
 *	5							PA5		PA5		PF7
 *	6							PA6		PA6		PF8
 *	7							PA7		PA7		PF9
 *	8							PB0		PB0		PF10
 *	9							PB1		PB1		PF3
 *	10						PC0		PC0		PC0
 *	11						PC1		PC1		PC1
 *	12						PC2		PC2		PC2
 *	13						PC3		PC3		PC3
 *	14						PC4		PC4		PF4
 *	15						PC5		PC5		PF5
 *
 * |----------------------------------------------------------------------
 */
#include "adc.h"
#include "delay.h"

u16 ADC_ConvertedValue=0;

/* Internal functions */
void ADC_INT_Channel_0_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_1_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_2_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_3_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_4_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_5_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_6_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_7_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_8_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_9_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_10_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_11_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_12_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_13_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_14_Init(ADC_TypeDef* ADCx);
void ADC_INT_Channel_15_Init(ADC_TypeDef* ADCx);
void ADC_INT_InitPin(uint16_t RCCx, GPIO_TypeDef* GPIOx, uint16_t PinX);

uint8_t vbatEnabled = 0;
uint8_t mult_vref = 0;
uint8_t mult_vbat = 0;

void Adc_Init(ADC_TypeDef* ADCx, uint8_t channel) {
	
	ADC_InitTypeDef ADC_InitDef;
	DMA_InitTypeDef DMA_InitStructure;/////////////////////////////
	
	if (channel == ADC_Channel_0) {
		ADC_INT_Channel_0_Init(ADCx);
	} else if (channel == ADC_Channel_1) {
		ADC_INT_Channel_1_Init(ADCx);
	} else if (channel == ADC_Channel_2) {
		ADC_INT_Channel_2_Init(ADCx);
	} else if (channel == ADC_Channel_3) {
		ADC_INT_Channel_3_Init(ADCx);
	} else if (channel == ADC_Channel_4) {
		ADC_INT_Channel_4_Init(ADCx);
	} else if (channel == ADC_Channel_5) {
		ADC_INT_Channel_5_Init(ADCx);
	} else if (channel == ADC_Channel_6) {
		ADC_INT_Channel_6_Init(ADCx);
	} else if (channel == ADC_Channel_7) {
		ADC_INT_Channel_7_Init(ADCx);
	} else if (channel == ADC_Channel_8) {
		ADC_INT_Channel_8_Init(ADCx);
	} else if (channel == ADC_Channel_9) {
		ADC_INT_Channel_9_Init(ADCx);
	} else if (channel == ADC_Channel_10) {
		ADC_INT_Channel_10_Init(ADCx);
	} else if (channel == ADC_Channel_11) {
		ADC_INT_Channel_11_Init(ADCx);
	} else if (channel == ADC_Channel_12) {
		ADC_INT_Channel_12_Init(ADCx);
	} else if (channel == ADC_Channel_13) {
		ADC_INT_Channel_13_Init(ADCx);
	} else if (channel == ADC_Channel_14) {
		ADC_INT_Channel_14_Init(ADCx);
	} else if (channel == ADC_Channel_15) {
		ADC_INT_Channel_15_Init(ADCx);
	}
	
	/* Init ADC */
	//ADC_InitADC(ADCx);	
	
	if (ADCx == ADC1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);		
	} else if (ADCx == ADC2) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	} else if (ADCx == ADC3) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
	}
	///////////////////////////////////////////////////////////////////////////////////////////
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	/* DMA channel1 configuration ----------------------------------------------*/
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = ((uint32_t)0x4001244C);
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
	
	////////////////////////////////////////////////////////////////////////////////////
		
	ADC_InitDef.ADC_Mode = ADC_Mode_Independent;
  ADC_InitDef.ADC_ScanConvMode = ENABLE;
  ADC_InitDef.ADC_ContinuousConvMode = ENABLE;
  ADC_InitDef.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitDef.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitDef.ADC_NbrOfChannel = 1;	
	/* Initialize ADC */
	ADC_Init(ADCx, &ADC_InitDef);
	
	/* Enable ADCx DMA */
  ADC_DMACmd(ADCx, ENABLE);//////////////////////////////////////////////
	
	/* Enable ADC */
	ADC_Cmd(ADCx, ENABLE);
	
	
	
	//Calib ADC
	ADC_ResetCalibration(ADCx);	 
	while(ADC_GetResetCalibrationStatus(ADCx));	
	
	ADC_StartCalibration(ADCx);
  while(ADC_GetCalibrationStatus(ADCx));	
	
	
	/* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADCx, ENABLE);//////////////////////////
}

void ADC_InitADC(ADC_TypeDef* ADCx) {
	
}

uint16_t ADC_Read(ADC_TypeDef* ADCx, uint8_t channel) {
	ADC_RegularChannelConfig(ADCx, channel, 1, ADC_SampleTime_239Cycles5);
	ADC_SoftwareStartConvCmd(ADCx,ENABLE);
	
	/* Wait till done */
	while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET);
	
	/* Return result */
	return ADC_GetConversionValue(ADCx);
}

u16 Get_Adc_Average(ADC_TypeDef* ADCx, u8 channel,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=ADC_Read( ADCx,channel);
		delay_ms(5);
	}
	return temp_val/times;
} 

void ADC_EnableVbat(void) {
//	/* Enable VBAT */
//	ADC_VBATCmd(ENABLE);
//	
//	/* Store vbat enabled */
//	vbatEnabled = 1;
}

void ADC_DisableVbat(void) {
//	/* Disable VBAT */
//	ADC_VBATCmd(DISABLE);
//	
//	/* Store vbat enabled */
//	vbatEnabled = 0;
}

uint16_t ADC_ReadVbat(ADC_TypeDef* ADCx) {
	uint32_t result;
//	/* Read battery voltage data */
//	/* Start conversion */
//	ADC_RegularChannelConfig(ADCx, ADC_Channel_Vbat, 1, ADC_SampleTime_112Cycles);
//	ADC_SoftwareStartConv(ADCx);
//	
//	/* Wait till done */
//	while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET);
//	
//	/* Get result */
//	result = ADC_GetConversionValue(ADCx);
//	
//	/* Convert to voltage */
//	result = result * ADC_VBAT_MULTI * ADC_SUPPLY_VOLTAGE / 0xFFF;
//	
//	/* Return value in mV */
	return (uint16_t) result;
}

/* Private functions */
void ADC_INT_Channel_0_Init(ADC_TypeDef* ADCx) {
	ADC_INT_InitPin(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_0);
}
void ADC_INT_Channel_1_Init(ADC_TypeDef* ADCx) {
	ADC_INT_InitPin(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_1);
}
void ADC_INT_Channel_2_Init(ADC_TypeDef* ADCx) {
	ADC_INT_InitPin(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_2);
}
void ADC_INT_Channel_3_Init(ADC_TypeDef* ADCx) {
	ADC_INT_InitPin(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_3);
}
void ADC_INT_Channel_4_Init(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_4);
	} else if (ADCx == ADC3) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOF, GPIOF, GPIO_Pin_6);
	}
}
void ADC_INT_Channel_5_Init(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_5);
	} else if (ADCx == ADC3) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOF, GPIOF, GPIO_Pin_7);
	}
}
void ADC_INT_Channel_6_Init(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_6);
	} else if (ADCx == ADC3) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOF, GPIOF, GPIO_Pin_8);
	}
}
void ADC_INT_Channel_7_Init(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_7);
	} else if (ADCx == ADC3) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOF, GPIOF, GPIO_Pin_9);
	}
}
void ADC_INT_Channel_8_Init(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_0);
	} else if (ADCx == ADC3) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOF, GPIOF, GPIO_Pin_10);
	}
}
void ADC_INT_Channel_9_Init(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_1);
	} else if (ADCx == ADC3) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOF, GPIOF, GPIO_Pin_3);
	}
}
void ADC_INT_Channel_10_Init(ADC_TypeDef* ADCx) {
	ADC_INT_InitPin(RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_0);
}
void ADC_INT_Channel_11_Init(ADC_TypeDef* ADCx) {
	ADC_INT_InitPin(RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_1);
}
void ADC_INT_Channel_12_Init(ADC_TypeDef* ADCx) {
	ADC_INT_InitPin(RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_2);
}
void ADC_INT_Channel_13_Init(ADC_TypeDef* ADCx) {
	ADC_INT_InitPin(RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_3);
}
void ADC_INT_Channel_14_Init(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_3);
	} else if (ADCx == ADC3) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOF, GPIOF, GPIO_Pin_4);
	}
}
void ADC_INT_Channel_15_Init(ADC_TypeDef* ADCx) {
	if (ADCx == ADC1 || ADCx == ADC2) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_5);
	} else if (ADCx == ADC3) {
		ADC_INT_InitPin(RCC_APB2Periph_GPIOF, GPIOF, GPIO_Pin_5);
	}
}

void ADC_INT_InitPin(uint16_t RCCx, GPIO_TypeDef* GPIOx, uint16_t PinX) {
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/* Enable GPIO clock */
	RCC_APB2PeriphClockCmd(RCCx, ENABLE);

	/* Set GPIO settings */
	GPIO_InitStruct.GPIO_Pin = PinX;
	//GPIO_InitStruct.GPIO_Speed = (GPIOSpeed_TypeDef)0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;

	/* Initialize GPIO pin */
	GPIO_Init(GPIOx, &GPIO_InitStruct);
}
