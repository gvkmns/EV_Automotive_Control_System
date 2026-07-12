/*
 * timer.c
 *
 *  Created on: Jul 6, 2026
 *      Author: shubh
 */

#include<stdio.h>
#include<stdint.h>
#include"project.h"
#include"timer.h"
#include"I2C.h"     // for LCD_Command / LCD_SetCursor / LCD_Print

volatile uint8_t start = 0;   // 0 = standby, 1 = active

void timer_init(void)
{
	RCC->RCC_AHB1ENR |=(1<<0); // GPIOA
	RCC->RCC_AHB1ENR |=(1<<1);//GPIOB
	RCC->RCC_APB1ENR |=(1<<0);// TIM2 CLOCK

	GPIOA->GPIO_MODER |=(2<<(pinA_0*2));//AF MODE
	GPIOA->GPIO_MODER |=(2<<(pinA_1*2));

	GPIOB->GPIO_MODER &=~(3<<(pinB_0*2));//PB0,PB1 OUTPUT
	GPIOB->GPIO_MODER &=~(3<<(pinB_1*2));//PB0,PB1 OUTPUT
	GPIOB->GPIO_MODER &=~(3<<(pinB_10*2));//PB10,PB11 OUTPUT
	GPIOB->GPIO_MODER &=~(3<<(pinB_11*2));

	GPIOB->GPIO_MODER |=(1<<(pinB_0*2));//PB0,PB1 OUTPUT
	GPIOB->GPIO_MODER |=(1<<(pinB_1*2));//PB0,PB1 OUTPUT
	GPIOB->GPIO_MODER |=(1<<(pinB_10*2));//PB10,PB11 OUTPUT
	GPIOB->GPIO_MODER |=(1<<(pinB_11*2));

	GPIOA->GPIO_AFRL &=~(0x0F<<(pinA_0*4));//celar AF1 PA0,PA1
	GPIOA->GPIO_AFRL &=~(0x0F<<(pinA_1*4));
	GPIOA->GPIO_AFRL |=(1<<(pinA_0*4));//AF1 PA0,PA1
	GPIOA->GPIO_AFRL |=(1<<(pinA_1*4));

	TIM2->TIM_PSC =15;//PRESCALER
	TIM2->TIM_ARR=999;//AUTO RELOAD REG

	TIM2->TIM_CCMR1 &= ~(7 << 4);   // Clear OC1M bits
	TIM2->TIM_CCMR1 |= (6 << 4);   // OC1M = PWM mode 1
	TIM2->TIM_CCMR1 |= (1 << 3);   // OC1PE preload enable

	TIM2->TIM_CCMR1 &= ~(7 << 12);
	TIM2->TIM_CCMR1 |= (6 << 12);  // OC2M = PWM mode 1
	TIM2->TIM_CCMR1 |= (1 << 11);  // OC2PE preload enable

	TIM2->TIM_CCER |= (1 << 0);    // CC1E enable CH1 output
	TIM2->TIM_CCER |= (1 << 4);    // CC2E enable CH2 output

	TIM2->TIM_CR1 |=((1<<0)|(1<<7));//AUTO PRELOAD,COUNTER ENABLE
	TIM2->TIM_CCR1 =250;
	TIM2->TIM_CCR2 =250;
}

void command(volatile char direction)
{
	if (direction == 'S')   // START
	{
		start = 1;
		LCD_Command(0x01);        // clear display
		LCD_SetCursor(0,0);
		LCD_Print(" Systen On ");
		LCD_SetCursor(1,0);
		LCD_Print("Standby mode ");
		return;
	}

	if (!start)   // ignore movement commands until 'S' received
		return;

	if (direction == 'F')
	{
		TIM2->TIM_CCR1 = 250;
		TIM2->TIM_CCR2 = 250;

		// Left motor forward
		GPIOB->GPIO_ODR |=  (1<<pinB_0);
		GPIOB->GPIO_ODR &= ~(1 << pinB_1);
		// Right motor forward
		GPIOB->GPIO_ODR |=  (1 << pinB_10);
		GPIOB->GPIO_ODR &= ~(1 <<pinB_11);

		LCD_SetCursor(1,0);
		LCD_Print("Moving Forward");
		delay();
	}
	else if (direction == 'B')
	{
	    TIM2->TIM_CCR1 = 250;
		TIM2->TIM_CCR2 = 250;
		// Left motor backward
		GPIOB->GPIO_ODR &= ~(1 << pinB_0);
		GPIOB->GPIO_ODR |=  (1 << pinB_1);
		// Right motor backward
		GPIOB->GPIO_ODR &= ~(1 << pinB_10);
		GPIOB->GPIO_ODR |=  (1 << pinB_11);



		LCD_SetCursor(1,0);
		LCD_Print("Backward    ");
		delay();
	}

	else if (direction == 'L')
	{
		TIM2->TIM_CCR1 = 250;
		TIM2->TIM_CCR2 = 250;

		// Left motor backward
		GPIOB->GPIO_ODR &= ~(1 << pinB_0);
		GPIOB->GPIO_ODR |=  (1 << pinB_1);
		// Right motor forward
		GPIOB->GPIO_ODR |=  (1 << pinB_10);
		GPIOB->GPIO_ODR &= ~(1 << pinB_11);

		LCD_SetCursor(1,0);
		LCD_Print("Left        ");
		delay();
	}

	else if (direction == 'R')
	{
		TIM2->TIM_CCR1 = 250;
		TIM2->TIM_CCR2 = 250;

		// Left motor forward
		GPIOB->GPIO_ODR|=  (1 << pinB_0);
		GPIOB->GPIO_ODR &= ~(1 << pinB_1);
		// Right motor backward
		GPIOB->GPIO_ODR &= ~(1 << pinB_10);
		GPIOB->GPIO_ODR |=  (1 << pinB_11);

		LCD_SetCursor(1,0);
		LCD_Print("Right       ");
		delay();

	}
	else if (direction == 'P')
	{
		// All motors off
		GPIOB->GPIO_ODR &= ~((1 << pinB_0) | (1 << pinB_1) | (1 <<pinB_10) | (1 << pinB_11));

		LCD_SetCursor(1,0);
		LCD_Print("Standby Mode____");
	}
}
