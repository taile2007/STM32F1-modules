#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//STM32VN								  
//////////////////////////////////////////////////////////////////////////////////  
								    

void KEY_Init(void) //IO
{ 
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//PORTA,PORTE

//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;//KEY2-KEY0
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
// 	GPIO_Init(GPIOE, &GPIO_InitStructure);//GPIOE2,3,4

//	// WK_UP-->GPIOA.0	  
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0  
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//GPIOA.0
	
	GPIO_Set(GPIOB,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4,GPIO_Mode_IPU,GPIO_Speed_50MHz);
	GPIO_Set(GPIOA,GPIO_Pin_0,GPIO_Mode_IPD,GPIO_Speed_50MHz);

}

//mode:0,bam tha;1,bam lien tuc;--> thay doi TT
//0£¬
//1£¬KEY0
//2£¬KEY1
//3£¬KEY2
//4£¬KEY3 WK_UP
//KEY0>KEY1>KEY2>KEY3!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;
	if(mode)key_up=1;  		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||WK_UP==1))
	{
		delay_ms(10); 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(WK_UP==1)return WKUP_PRES;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0)key_up=1; 	    
 	return 0;
}
