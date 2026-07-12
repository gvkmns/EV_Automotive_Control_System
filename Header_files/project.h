

#ifndef PROJECT_H_
#define PROJECT_H_

#include <stdint.h>   // <-- was missing: needed for uint32_t

typedef struct
{
	volatile uint32_t GPIO_MODER;   //0x00
	volatile uint32_t GPIO_OTYPER;  //0x04
	volatile uint32_t GPIO_OSPEEDR; //0x08
	volatile uint32_t GPIO_PUPDR;   //0x0C
	volatile uint32_t GPIO_IDR;     //0x10
	volatile uint32_t GPIO_ODR;     //0x14
	volatile uint32_t GPIO_BSRR;    //0x18
	volatile uint32_t GPIO_LCKR;    //0x1C
	volatile uint32_t GPIO_AFRL;    //0x20
	volatile uint32_t GPIO_AFRH;    //0x24
}GPIO_reg;

typedef struct
{
	volatile uint32_t RCC_CR;          //0x00
	volatile uint32_t RCC_PLLCFGR;     //0x04
	volatile uint32_t RCC_CFGR;        //0x08
	volatile uint32_t RCC_CIR;         //0x0C
	volatile uint32_t RCC_AHB1RSTR;    //0x10
	volatile uint32_t RCC_AHB2RSTR;    //0x14
	volatile uint32_t RCC_AHB3RSTR;    //0x18
	volatile uint32_t Reserved;        //0x1C
	volatile uint32_t RCC_APB1RSTR;    //0x20
	volatile uint32_t RCC_APB2RSTR;    //0x24
	volatile uint32_t Reserved2;       //0x28
	volatile uint32_t Reserved3;       //0x2C
	volatile uint32_t RCC_AHB1ENR;     //0x30
	volatile uint32_t RCC_AHB2ENR;     //0x34
	volatile uint32_t RCC_AHB3ENR;     //0x38
	volatile uint32_t Reserved5;       //0x3C
	volatile uint32_t RCC_APB1ENR;     //0x40
	volatile uint32_t RCC_APB2ENR;     //0x44
}RCC_reg;

typedef struct
{
	volatile uint32_t SPI_CR1;      //0x00
	volatile uint32_t SPI_CR2;      //0x04
	volatile uint32_t SPI_SR;       //0x08
	volatile uint32_t SPI_DR;       //0x0C
	volatile uint32_t SPI_CRCPR;    //0x10
	volatile uint32_t SPI_RXCRCR;   //0x14
	volatile uint32_t SPI_TXCRCR;   //0x18
	volatile uint32_t SPI_I2SCFGR;  //0x1C
	volatile uint32_t SPI_I2SPR;    //0x20
}SPI_reg;

typedef struct
{
	volatile uint32_t USART_SR;   //0x00
	volatile uint32_t USART_DR;   //0x04
	volatile uint32_t USART_BRR;  //0x08
	volatile uint32_t USART_CR1;  //0x0C
	volatile uint32_t USART_CR2;  //0x10
	volatile uint32_t USART_CR3;  //0x14
	volatile uint32_t USART_GTPR; //0x18
}USART_reg;

typedef struct
{
    volatile uint32_t I2C_CR1;    //0x00
    volatile uint32_t I2C_CR2;    //0x04
    volatile uint32_t I2C_OAR1;   //0x08
    volatile uint32_t I2C_OAR2;   //0x0C
    volatile uint32_t I2C_DR;     //0x10
    volatile uint32_t I2C_SR1;    //0x14
    volatile uint32_t I2C_SR2;    //0x18
    volatile uint32_t I2C_CCR;    //0x1C
    volatile uint32_t I2C_TRISE;  //0x20
} I2C_reg;

typedef struct
{
    volatile uint32_t TIM_CR1;    //0x00
    volatile uint32_t TIM_CR2;    //0x04
    volatile uint32_t TIM_SMCR;   //0x08
    volatile uint32_t TIM_DIER;   //0x0C
    volatile uint32_t TIM_SR;     //0x10
    volatile uint32_t TIM_EGR;    //0x14
    volatile uint32_t TIM_CCMR1;  //0x18
    volatile uint32_t TIM_CCMR2;  //0x1C
    volatile uint32_t TIM_CCER;   //0x20
    volatile uint32_t TIM_CNT;    //0x24
    volatile uint32_t TIM_PSC;    //0x28
    volatile uint32_t TIM_ARR;    //0x2C
    volatile uint32_t Reserved;   //0x30
    volatile uint32_t TIM_CCR1;   //0x34
    volatile uint32_t TIM_CCR2;   //0x38
    volatile uint32_t TIM_CCR3;   //0x3C
    volatile uint32_t TIM_CCR4;   //0x40
} TIM_reg;

typedef struct
{
    volatile uint32_t ADC_SR;     //0x00
    volatile uint32_t ADC_CR1;    //0x04
    volatile uint32_t ADC_CR2;    //0x08
    volatile uint32_t ADC_SMPR1;  //0x0C
    volatile uint32_t ADC_SMPR2;  //0x10
    volatile uint32_t ADC_JOFR1;  //0x14
    volatile uint32_t ADC_JOFR2;  //0x18
    volatile uint32_t ADC_JOFR3;  //0x1C
    volatile uint32_t ADC_JOFR4;  //0x20
    volatile uint32_t ADC_HTR;    //0x24
    volatile uint32_t ADC_LTR;    //0x28
    volatile uint32_t ADC_SQR1;   //0x2C
    volatile uint32_t ADC_SQR2;   //0x30
    volatile uint32_t ADC_SQR3;   //0x34
    volatile uint32_t ADC_JSQR;   //0x38
    volatile uint32_t ADC_JDR1;   //0x3C
    volatile uint32_t ADC_JDR2;   //0x40
    volatile uint32_t ADC_JDR3;   //0x44
    volatile uint32_t ADC_JDR4;   //0x48
    volatile uint32_t ADC_DR;     //0x4C
} ADC_reg;

/* ---- Peripheral base addresses (verified against DS8626 Table 10) ---- */
#define GPIOA  ((GPIO_reg *)  0x40020000)
#define GPIOB  ((GPIO_reg *)  0x40020400)
#define GPIOD  ((GPIO_reg *)  0x40020C00)
#define GPIOE  ((GPIO_reg *)  0x40021000)
#define I2C    ((I2C_reg  *)  0x40005400)
#define TIM2   ((TIM_reg  *)  0x40000000)
#define ADC1   ((ADC_reg  *)  0x40012000)
#define RCC    ((RCC_reg  *)  0x40023800)
#define USART  ((USART_reg*)  0x40004400)
#define SPI    ((SPI_reg  *)  0x40013000)

/* ---- Pin assignments ---- */
#define pinA_0 0 //TIM2_CH1
#define pinA_1 1 //TIM2_CH2
#define pinA_2 2 //USART2_TX
#define pinA_3 3 //USART2_RX
#define pinA_4 4 //ADC1_IN4
#define pinA_5 5 //SPI1_SCK
#define pinA_6 6 //SPI1_MISO
#define pinA_7 7 //SPI1_MOSI

#define pinB_0  0  //GPIO Output Left Motor Direction (IN1, IN2)
#define pinB_1  1  //GPIO Output Left Motor Direction (IN1, IN2)
#define pinB_6  6  //I2C1_SCL Serial Clock
#define pinB_7  7  //I2C1_SDA Serial Data

#define pinB_10 10 //GPIO Output Right Motor Direction (IN3,IN4)
#define pinB_11 11 //Right Motor Direction (IN3,IN4)

#define pinD_12 12 //GPIO Output Green LED (Right Turn Signal)
#define pinD_13 13 //GPIO Output Orange LED (Left Turn Signal)
#define pinD_14 14 //GPIO Output Red LED (Auto-Headlight)
#define pinE_3  3  //GPIO Output Chip Select (CS)

/* ---- External sensor / peripheral registers (not part of the MCU) ---- */
#define CTRL_REG4  0x20
#define CTRL_REG5  0x24
#define CTRL_REG6  0x25
#define OUT_X_L    0x28
#define OUT_X_H    0x29
#define OUT_Y_L    0x2A
#define OUT_Y_H    0x2B
#define OUT_Z_L    0x2C
#define OUT_Z_H    0x2D

#define LCD_BACKLIGHT  0x08   // bit 3
#define LCD_ENABLE     0x04   // bit 2
#define LCD_RW         0x02   // bit 1 read
#define LCD_RS         0x01   // bit 0
#define LCD_ADDR       0x27

#define FORWARD   'F'
#define BACKWARD  'B'
#define RIGHT     'R'
#define LEFT      'L'
#define STOP      'P'
#define START     'S'

#endif /* PROJECT_H_ */
