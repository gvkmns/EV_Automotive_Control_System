/*
 */

#include<stdio.h>
#include<stdint.h>
#include"project.h"
#include"usart.h"
#include"timer.h"
void init(void)
{
	RCC->RCC_APB1ENR |=(1<<17);//ENABLE CLOCK
	RCC->RCC_AHB1ENR  |=(1<<0);//GPIOA ENABLE

	GPIOA->GPIO_MODER |=(2<<(pinA_2*2))|(2<<(pinA_3*2));//PA2,PA3 ALTERNATE MODE
	GPIOA->GPIO_AFRL  |=((7<<8)|(7<<12));//UART TX,RX

	USART->USART_BRR=0x0683;//9600
	USART->USART_CR1 |=((1<<3)|(1<<2));//ENABLE TX,RX
	USART->USART_CR1 |=(1<<13);// ENABLE UART
    USART->USART_CR1 |=(1<<5);//RXNE enable
    USART->USART_CR1 |=(1<<7);//txe enable
    //NVIC_ISER1 |=(1<<6);
    //receive();
}
    void receive()
    {
    	volatile char data;
    	if(USART->USART_SR &(1<<5))//CHECKING RECEIVE FLAG
    	{
    		data=USART->USART_DR;
    		printf("%c",data);
    		command(data);
    		delay();
    	}
    }
