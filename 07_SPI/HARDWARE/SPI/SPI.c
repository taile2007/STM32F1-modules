#include "SPI.h"
#include "delay.h"

void SPI_Send_Byte (u8 data)
{
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		SPI_DO = (data & 0x80) >> 7;
		data <<= 1;
		
		SPI_SCLK = 1;
		SPI_SCLK = 0;
	}
}

u8 SPI_Read_Byte()
{
	int i = 0;
	u8 rec = 0;
	
	for (i = 0; i <8; i++)
	{
		SPI_SCLK = 1;
		rec <<= 1;
		if (SPI_DI) rec ++;
		
		SPI_SCLK = 0;
	}
	return 0;
}


u8 SPI_WriteMulti(u8 addr, u8 reg, u8 len, u8 *buf)
{
	uint8_t i = 0;
	SPI_SS = 0;
	SPI_Send_Byte(addr);
	SPI_SS = 1;
	SPI_SS = 0;
	SPI_Send_Byte(reg);
	SPI_SS = 1;
	for (i = 0; i < len; i++)
	{
		SPI_SS = 0;
		SPI_Send_Byte(buf[i]);
		SPI_SS = 1;
	}
	
	return 0;
}

u8 SPI_ReadMulti(u8 addr, u8 reg, u8 len, u8 *buf)
{
	uint8_t i = 0;
	SPI_SS = 0;
	SPI_Send_Byte(addr);
	SPI_SS = 1;
	SPI_SS = 0;
	SPI_Send_Byte(reg);
	SPI_SS = 1;
	
	while(len)
	{
		SPI_SS = 0;
		*buf = SPI_Read_Byte();
		len --;
		buf++;
		SPI_SS = 1;
	}
	
	return 0;
}

