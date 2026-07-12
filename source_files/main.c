#include<stdio.h>
#include<stdint.h>
#include"project.h"
#include"ACC.h"
#include"adc.h"
#include"I2C.h"
#include"spi.h"
#include"timer.h"
#include"usart.h"

int main()
{
    adx values;
    //char lcd_buf[17];

    printf("hello\n");
    ADC_init();
    timer_init();
    init();
    LCD_Init();
    I2C1_Init();
    LIS302DL_init();

    uint8_t id = LIS302DL_read_device_id();
    printf("%d device id",id);
    if(id==63)
        printf("LIS302DL device found \r\n");
    else
        printf("LIS302DL device is not fount\r\n");

    while(1)
    {
        headlight();
        receive();     // reads UART if data available AND calls command() internally
        LIS302DL_get_values(&values);



        uint32_t sum_sq = (int32_t)values.ax * values.ax
        	                          + (int32_t)values.ay * values.ay
        	                          + (int32_t)values.az * values.az;

        	         uint16_t magnitude = isqrt(sum_sq);
        	         printf("sum_sq=%ld\n",sum_sq);

        	         printf("Mag: %6u\r\n",
        	                magnitude);

        	         char lcd_buf[17];
        	         sprintf(lcd_buf, "Mag: %5u", magnitude);
        	         		LCD_SetCursor(4,0);       // 4th line (rows are 0,1,2,3)
        	         		LCD_Print(lcd_buf);
    }
}
