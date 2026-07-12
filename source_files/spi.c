/*
 * spi.c
 *
 *  Created on: Jul 6, 2026
 *      Author: shubh
 */

#include<stdio.h>
#include<stdint.h>
#include"spi.h"
#include"project.h"

void spi_init()
{
	RCC->RCC_APB2ENR |=(1<<12);//ENABLE SPI1
	RCC->RCC_AHB1ENR |=(1<<0)|(1<<4);//ENABLE GPIOA and E

	GPIOA->GPIO_MODER  &= ~(3<<(pinA_5*2));//clearing the bits
	GPIOA->GPIO_MODER  &= ~(3<<(pinA_6*2));
	GPIOA->GPIO_MODER  &= ~(3<<(pinA_7*2));
	GPIOA->GPIO_MODER  |=  (2<<(pinA_5*2))|(2<<(pinA_6*2))|(2<<(pinA_7*2));//making alternative mode
	GPIOE->GPIO_MODER  &= ~(3<<(pinE_3*2));
	GPIOE->GPIO_MODER  |=  (1<<(pinE_3*2));//making PE3 output
    GPIOE->GPIO_OTYPER &=  ~(1<<pinE_3);
    GPIOE->GPIO_OSPEEDR&=(3<<pinE_3*2);
    GPIOE->GPIO_OSPEEDR|=(1<<pinE_3*2);
	GPIOA->GPIO_AFRL   |=  (5<<pinA_5*4)|(5<<pinA_6*4)|(5<<pinA_7*4);//configure each pin for Alternate Function mode AF5 for SPI1
}

void SPI1_ADXL_init(void)
{
	RCC->RCC_APB2ENR |= (1<<12);   // enable SPI1 clock

	SPI->SPI_CR1 = 0;

	SPI->SPI_CR1 |= (1<<2);             // MSTR = 1, master mode
	SPI->SPI_CR1 |= (4<<3);             // BR[2:0] = 100 -> fPCLK/32 (ADJUST IF NEEDED)
	SPI->SPI_CR1 |= (1<<0) | (1<<1);    // CPHA = 1, CPOL = 1 (SPI mode 3, required by ADXL345)
	SPI->SPI_CR1 &= ~(1<<7);            // LSBFIRST = 0, MSB first
	SPI->SPI_CR1 |= (1<<9) | (1<<8);    // SSM = 1, SSI = 1 (software NSS management)
	SPI->SPI_CR1 |= (1<<6);             // SPE = 1, enable SPI

	cs_disable();
}

void SPI1_Send(uint8_t *data1, uint8_t len)
{
	for(volatile int i=0;i<len;i++)
	{
		while(!(SPI->SPI_SR & (1<<1)));//wait TXE
		SPI->SPI_DR=data1[i];//send byte
		while(!(SPI->SPI_SR & (1<<0)));//wait RXNE
		volatile uint8_t dump=SPI->SPI_DR;//dummy read clears RXNE
	}
	while(SPI->SPI_SR & (1<<7));//wait BSY cleared
}

void SPI1_Receive(uint8_t *buffer, uint32_t len)
{
	for(uint32_t i = 0; i < len; i++)
	{
		while(!(SPI->SPI_SR & (1<<1)));   // wait TXE
		SPI->SPI_DR = 0xFF;               // dummy write to generate clock
		while(!(SPI->SPI_SR & (1<<0)));   // wait RXNE
		buffer[i] = SPI->SPI_DR;
	}
}

void cs_disable(void)
{
	GPIOE->GPIO_BSRR |= (1<<3);    // BS3 -> PE3 high -> CS inactive
}

void cs_enable(void)
{
	GPIOE->GPIO_BSRR |= (1<<19);   // BR3 -> PE3 low -> CS active (ADXL345 is active-low)
}

