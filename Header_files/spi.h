

#ifndef SPI_H_
#define SPI_H_

#include<stdio.h>
#include<stdint.h>

void spi_init();
void SPI1_ADXL_init(void);
void SPI1_Send(uint8_t *data1, uint8_t len);
void SPI1_Receive(uint8_t *buffer, uint32_t len);
void cs_disable(void);
void cs_enable(void);


#endif /* SPI_H_ */
