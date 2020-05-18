#ifndef __SPI_H
#define __SPI_H 			   
#include "sys.h" 

//IO


#define SPI_DO 			PBout(15) // Master send data to Slave
#define SPI_DI 			PBout(14) // Master receive data from Slave
#define SPI_SCLK 		PBout(13) 
#define SPI_SS 			PBout(12) 

void SPI_Send_Byte (u8 data);
u8 SPI_Read_Byte();
u8 SPI_ReadMulti(u8 addr, u8 reg, u8 len, u8 *buf);
u8 SPI_WriteMulti(u8 addr, u8 reg, u8 len, u8 *buf);

#endif
