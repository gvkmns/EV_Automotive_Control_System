


#include<stdio.h>
#include<stdint.h>
#include"project.h"
#include"ACC.h"
#include"spi.h"

void LIS302DL_write(uint8_t address, uint8_t value)
{
	uint8_t packet[2];
	address &=~(1<<7);   // bit7=0 means write
   //address &=~(1<<6);   // bit6=0 means single register

	packet[0]=address;
	packet[1]=value;
	cs_enable();
	SPI1_Send(packet,2);
	cs_disable();
}

void LIS302DL_read(uint8_t address, uint8_t *rxdata, uint32_t len)
{
	address |=(1<<7);    // bit7=1 means read
	//if(len>1)
	//{
		//address |=(1<<6); // bit6=1 means multi-byte auto increment
	//a}
	cs_enable();
	SPI1_Send(&address,1);
	SPI1_Receive(rxdata,len);
	cs_disable();
}

void LIS302DL_init(void)
{
    spi_init();
    SPI1_ADXL_init();
    LIS302DL_write(CTRL_REG4, 0x00);
    LIS302DL_write(CTRL_REG4, 0x67);
    LIS302DL_write(CTRL_REG5, 0x00);
    LIS302DL_write(CTRL_REG6, 0x00);
    LIS302DL_write(CTRL_REG6, 0x10);

}

void LIS302DL_get_values(adx *values)
{
	uint8_t data[6];
	LIS302DL_read(OUT_X_L,data,6);

	values-> ax =((data[1]<<8)|data[0]);
	values-> ay =((data[3]<<8)|data[2]);
	values-> az =((data[5]<<8)|data[4]);

}

uint8_t LIS302DL_read_device_id(void)
{
	uint8_t id;
	LIS302DL_read(0x0F,&id,1);  // WHO_AM_I register
	return id;
}
uint16_t isqrt(uint32_t num)
{
    uint16_t res = 0;
    while ((uint32_t)(res + 1) * (res + 1) <= num)
    {
        res++;
    }
    return res;
}
