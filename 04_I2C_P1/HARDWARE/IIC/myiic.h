#ifndef __MYIIC_H
#define __MYIIC_H 			   
#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 


////////////////////////////////////////////////////////////////////////////////// 
//IO
//Step 1: Config
#define SDA_IN()  {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=8<<4;}	//Config PB9 as input which we can read 0/1 in this pin
#define SDA_OUT() {GPIOB->CRH&=0XFFFFFF0F;GPIOB->CRH|=3<<4;} //Config PB9 as output like setbit/resetbit to turn on/off a LED
 
// Step 2: For output: Set 1 or reset 0; For input: Check the value in that input
#define IIC_SCL    PBout(8) //SCL  We can do set/resetbit (1/0)  //This pin was declared in file.c for Output mode
#define IIC_SDA    PBout(9) //SDA	 We can do set/resetbit (1/0)
#define READ_SDA   PBin(9)  //SDA IN Check value of this Pin either 0 or 1

//IIC
void IIC_Init(void);                			 
void IIC_Start(void);				
void IIC_Stop(void);	  			
void IIC_Send_Byte(u8 txd);		
u8 IIC_Read_Byte(unsigned char ack);
u8 IIC_Wait_Ack(void); 				
void IIC_Ack(void);					
void IIC_NAck(void);	

#endif

