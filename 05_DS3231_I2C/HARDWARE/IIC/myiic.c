
#include "myiic.h"  

void IIC_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;			    //LED0-->PB.5 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//GPIO_Mode_Out_PP; 	 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//GPIO_Speed_50MHz;	 
  GPIO_Init(GPIOB, &GPIO_InitStructure);			     //GPIOB.5
	IIC_SCL=1;
	IIC_SDA =1;
}

void IIC_Start(void){
	SDA_OUT(); // set SDA is ouput mode
	// Set SCL and SDA to 1
	IIC_SCL=1;
	IIC_SDA =1;
	delay_us(4); // For 100kHz, we need to delay around 4us
	// After starting, set both wire to 0
	IIC_SDA =0;
	delay_us(4);
	IIC_SCL=0;	
}

void IIC_Stop(void){	
	SDA_OUT();  // set SDA is ouput mode
	// Set SCL and SDA to 0
	IIC_SCL=0;
	IIC_SDA =0;
	delay_us(4);
	// After delay, set both wire to 1
	IIC_SDA =1;
	IIC_SCL=1;
	delay_us(4);		
}

void IIC_Send_Byte(u8 txd){//11111111&10000000
	int i=0;
	SDA_OUT();
	IIC_SCL=0; // Set SCL PIN low (0)
	// Set MSB in the txd to LSB in the new one
	for(i = 0; i < 8; i++){
		IIC_SDA=(txd & 0x80) >> 7;  // & 0x80 (1000 0000) to check whether first bit is 1 or 0
		txd <<= 1;
		delay_us(2);
		IIC_SCL=1; // provide a clock for SCL
		delay_us(2);
		IIC_SCL=0;
		
	}
	
}

// Ack whenever SDA receive (read) data from Slave, Master needs to send ack to Salve for getting data or not getting data
void IIC_Ack(void){
	IIC_SCL=0; // before master receiving data
	SDA_OUT();
	IIC_SDA=0; // need to set 0
	delay_us(2);
	IIC_SCL=1; // SCL set 1
	delay_us(2);
	IIC_SCL=0; // after master receiving data
}					
void IIC_NAck(void){
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}	

u8 IIC_Read_Byte(unsigned char ack){
	int i=0;
	u8 rec=0;
	SDA_IN(); // Config in so that we can read data from this PIN (IIC_SDA)
	for(i = 0; i < 8; i++){//11111111
		IIC_SCL = 0;
		delay_us(2);
		IIC_SCL = 1;
		delay_us(2);
		rec <<= 1;  // shift left to put new bit in the prev position of old bit. Shift from right to left
		// example: 0000 0001 - <<1 -> 0|0000 001x --> <<1 --> 00|0000 01xy : x, y are new bits 
		if(READ_SDA) rec++;
	}
	if(!ack){ // if ack  = 0; Master reads correct data from Slave
		IIC_Ack();
	}
		else{ // otherwise, its wrong
		IIC_NAck();	
		}
}

// When Master write something to Slave, Master needs to wait for receving an ACK from Slave to confirm it was sent successfully or not
u8 IIC_Wait_Ack(void){
	u8 time=0;
	SDA_IN();
	IIC_SDA=1;delay_us(1); // Since SDA was setup to INPUT; how can we set it to 1
	IIC_SCL=1;delay_us(1);
	while(READ_SDA){ //need to wait this one  = 0
		time++;
		if(time > 250) {IIC_Stop(); return 1;}
	}
	IIC_SCL=0;
	return 0; 
}
// add: I2C slave address ( it should be 8bit type); reg: Need to write to which register with which data
void IIC_Cmd_Write(u8 add ,u8 reg,u8 data){
	IIC_Start();
	
	IIC_Send_Byte(add|0);
	while(IIC_Wait_Ack()); // wait ack from Slave
	IIC_Send_Byte(reg);
	while(IIC_Wait_Ack());
	IIC_Send_Byte(data);
	while(IIC_Wait_Ack());
	
	IIC_Stop(); // stop I2C
	delay_ms(2);
}

u8 IIC_Write(u8 addr,u8 reg,u8 data){
	IIC_Start();
	
	IIC_Send_Byte(addr|0);
	if(IIC_Wait_Ack()){IIC_Stop(); return 1;}
	IIC_Send_Byte(reg);
	if(IIC_Wait_Ack()){IIC_Stop(); return 1;}
	IIC_Send_Byte(data);
	if(IIC_Wait_Ack()){IIC_Stop(); return 1;}
	
	IIC_Stop();
	delay_ms(2);
	return 0;
}
// Read one byte
u8 Read_IIC(u8 addr, u8 reg){
	IIC_Start();
	
	IIC_Send_Byte(addr|0);
	while(IIC_Wait_Ack());
	IIC_Send_Byte(reg);
	while(IIC_Wait_Ack());
	
	IIC_Start();
	IIC_Send_Byte(addr|1); // add bit 1 to let Slave know we're reading
	while(IIC_Wait_Ack());
	reg = IIC_Read_Byte(1); // receive one byte, need to add 1
	IIC_Stop();
	delay_ms(2);
	
	return reg;
}

u8 IIC_ReadMulti(u8 addr,u8 reg,u8 len,u8 *buf){
	
	IIC_Start();
	IIC_Send_Byte(addr|0);
	while(IIC_Wait_Ack());
	IIC_Send_Byte(reg);
	while(IIC_Wait_Ack());
	
	IIC_Start();
	IIC_Send_Byte(addr|1);
	while(IIC_Wait_Ack());
	
	while(len){
		if(len==1) *buf= IIC_Read_Byte(1); // if len  = 1; just read only one byte -> ACK should be 1
		else *buf= IIC_Read_Byte(0);
		len--;
		buf++;
	}	
	
	IIC_Stop();
	return 0;

}

u8 IIC_WriteMulti(u8 addr,u8 reg,u8 len,u8 *buf){
	u8 i=0;
	IIC_Start();
	IIC_Send_Byte(addr|0);
	while(IIC_Wait_Ack());
	IIC_Send_Byte(reg);
	while(IIC_Wait_Ack());
	
	for(i=0;i<len;i++){
		IIC_Send_Byte(buf[i]);
		if(IIC_Wait_Ack()){IIC_Stop(); return 1;}
	}
	
	IIC_Stop();	
	return 0;
}
