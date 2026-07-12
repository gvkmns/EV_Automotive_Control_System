


#include<stdio.h>
#include<stdint.h>
#include"project.h"
#include"adc.h"

void ADC_init()
{
	RCC->RCC_AHB1ENR |=(1<<0)|(1<<3);      // enable GPIOA and GPIOD clock
	RCC->RCC_APB2ENR |=(1<<8);              // enable ADC1 clock

	GPIOA->GPIO_MODER &=~(3<<(pinA_4*2));  // clear PA4 bits
	GPIOA->GPIO_MODER |=(3<<(pinA_4*2));   // PA4 analog mode

	GPIOD->GPIO_MODER &=~(3<<(pinD_14*2)); // clear PD14 bits
	GPIOD->GPIO_MODER |=(1<<(pinD_14*2));  // PD14 output mode

	ADC1->ADC_CR1 &=~(3<<24);              // 12-bit resolution
	ADC1->ADC_SQR3=4;                      // channel 4
	ADC1->ADC_CR2 |=(1<<0);               // ADC ON
}

void headlight()
{
	//while(1)
	//{
		ADC1->ADC_CR2 |=(1<<30);           // start conversion
		while(!(ADC1->ADC_SR & (1<<1)));   // wait EOC

		uint32_t adc_value=ADC1->ADC_DR;
		printf("adc = %lu\n",adc_value);

		if(adc_value>1000)
		{
			GPIOD->GPIO_ODR |=(1<<pinD_14);  // bright → LED ON
		}
		else
		{
			GPIOD->GPIO_ODR &=~(1<<pinD_14); // dark → LED OFF
		//}
	}
}

