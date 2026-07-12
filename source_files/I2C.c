
#include<stdio.h>
#include<stdint.h>
#include"project.h"
#include"I2C.h"
#include"timer.h"

#define APB1_CLK_MHZ 16

void I2C1_Init(void)
{
	RCC->RCC_AHB1ENR |=(1<<1);// Enable GPIOB port
	RCC->RCC_APB1ENR |=(1<<21);//Enable I2C1 register

	GPIOB->GPIO_MODER &=~(3<<(pinB_6 *2));
	GPIOB->GPIO_MODER &=~(3<<(pinB_7 *2));
	GPIOB->GPIO_MODER |=(2<<(pinB_6 *2));// AF mode
	GPIOB->GPIO_MODER |=(2<<(pinB_7 *2));

	GPIOB->GPIO_AFRL &=~(0xF<<(pinB_6 *4));
	GPIOB->GPIO_AFRL &=~(0xF<<(pinB_7 *4));
	GPIOB->GPIO_AFRL |=(4<<(pinB_6 *4));//AF4 = I2C1
	GPIOB->GPIO_AFRL |=(4<<(pinB_7 *4));

	GPIOB->GPIO_OTYPER |=(1<<pinB_6)|(1<<pinB_7);//open-drain

	GPIOB->GPIO_OSPEEDR |=(3<<(pinB_6*2));//high speed  <-- ADDED
	GPIOB->GPIO_OSPEEDR |=(3<<(pinB_7*2));//high speed  <-- ADDED

	GPIOB->GPIO_PUPDR &=~(3<<(pinB_6 *2));
	GPIOB->GPIO_PUPDR &=~(3<<(pinB_7 *2));
	GPIOB->GPIO_PUPDR |=(1<<(pinB_6 *2));//pull-up
	GPIOB->GPIO_PUPDR |=(1<<(pinB_7 *2));

	I2C->I2C_CR1 |=(1<<15);//software reset
	I2C->I2C_CR1 &=~(1<<15);

	I2C->I2C_CR2   = APB1_CLK_MHZ;                 // FREQ field = APB1 clock in MHz
	I2C->I2C_CCR   = APB1_CLK_MHZ*5;                // 100kHz std mode: CCR = Fpclk1/(2*100000)
	I2C->I2C_TRISE = APB1_CLK_MHZ+1;                // TRISE = (Fpclk1_MHz * 1000ns / 1000)+1

	I2C->I2C_CR1 |=(1<<0);//PE enable (must be last)
}

/* Returns 1 on success (ACK received), 0 on failure (NACK / timeout) */
uint8_t I2C1_Start(void)
{
	uint32_t timeout = 100000;
	while((I2C->I2C_SR2 & (1<<1)) && --timeout); // wait while BUS BUSY   <-- ADDED
	if(timeout==0)
		return 0;

	I2C->I2C_CR1 |=(1<<8);//generate start bit
	timeout = 100000;
	while(!(I2C->I2C_SR1 & (1<<0)) && --timeout); // wait for SB
	return
			(timeout!=0);
}

/* Returns 1 on success (ACK received), 0 on NACK/failure */
uint8_t I2C1_WriteAddr(uint8_t address,uint8_t rw)
{
	volatile uint32_t temp;
	uint32_t timeout = 100000;

	I2C->I2C_DR =(address<<1)|rw ;

	while(timeout--)
	{
		if(I2C->I2C_SR1 & (1<<1))          // ADDR set -> ACK received
		{
			temp = I2C->I2C_SR1;           // clear ADDR
			temp = I2C->I2C_SR2;
			(void)temp;
			return 1;
		}
		if(I2C->I2C_SR1 & (1<<4))          // AF set -> NACK received  <-- ADDED
		{
			I2C->I2C_SR1 &= ~(1<<4);       // clear AF
			I2C->I2C_CR1 |= (1<<9);        // send STOP
			return 0;
		}
	}
	I2C->I2C_CR1 |= (1<<9);                // timeout safety stop     <-- ADDED
	return 0;
}

uint8_t I2C1_WriteData(uint8_t data)
{
	uint32_t timeout = 100000;
	while(!(I2C->I2C_SR1 & (1<<7)) && --timeout); // wait TXE
	if(timeout==0) return 0;

	I2C->I2C_DR = data;

	timeout = 100000;
	while(!(I2C->I2C_SR1 & (1<<2)) && --timeout); // wait BTF
	return
	(timeout!=0);
}

void I2C1_Stop(void)
{
	I2C->I2C_CR1 |=(1<<9);
}

void LCD_Pulse(uint8_t data)
{
	data |=(1<<2);
	I2C1_WriteData(data);
	delay();
	data &= ~(1<<2);
	I2C1_WriteData(data);
	delay();
}

void LCD_SendNibble(uint8_t nibble, uint8_t mode)
{
	uint8_t data=0;
	data 	= (nibble & 0xF0);
	data |= LCD_BACKLIGHT;
	if(mode)
		data |= LCD_RS;
	else
		data &= ~LCD_RS;

	LCD_Pulse(data);
}

void LCD_SendByte(uint8_t value, uint8_t mode)
{
	LCD_SendNibble(value & 0xF0, mode);
	LCD_SendNibble((value << 4) & 0xF0, mode);
}

uint8_t LCD_Command(uint8_t cmd)
{
	if(!I2C1_Start()) return 0;
	if(!I2C1_WriteAddr(LCD_ADDR , 0)){ return 0; }
	LCD_SendByte(cmd,0);
	I2C1_Stop();
	return 1;
}

uint8_t LCD_Data(uint8_t data)
{
	if(!I2C1_Start()) return 0;
	if(!I2C1_WriteAddr(LCD_ADDR, 0)){ return 0; }
	LCD_SendByte(data,1);
	I2C1_Stop();
	return 1;
}

void LCD_Init(void)
{
	delay();
	if(!I2C1_Start())
	{ printf("LCD: I2C start failed\r\n");
	return;
	}
	if(!I2C1_WriteAddr(LCD_ADDR, 0))
	{
		printf("LCD: NACK - check address/wiring\r\n");
		return;
	}

	LCD_SendNibble(0x30,0);
	delay();
	LCD_SendNibble(0x30,0);
	delay();
	LCD_SendNibble(0x30,0);
	delay();
	LCD_SendNibble(0x20,0);//4-bit mode
	delay();
	I2C1_Stop();

	LCD_Command(0x28);//4-bit,2line
	delay();
	LCD_Command(0x0C);//Display on
	delay();
	LCD_Command(0x06);//Entry mode
	delay();
	LCD_Command(0x01);//Clear
	delay();

	printf("LCD init done\r\n");
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
	uint8_t value;
	if(row==0)      value = 0x80+col;
	else if(row==1) value = 0xC0+col;
	else if(row==2) value = 0x94+col;
	else            value = 0xD4+col;
	LCD_Command(value);
}

void LCD_Print(char *str)
{
	volatile uint32_t i=0;
	while(str[i] != '\0')
	{
		LCD_Data(str[i]);
		i++;
	}
}

void delay()
{
	for(volatile int i=0;i<50000;i++){}
}
