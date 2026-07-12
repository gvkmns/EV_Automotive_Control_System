

#ifndef I2C_H_
#define I2C_H_

void I2C1_Init(void);
uint8_t I2C1_Start(void);
uint8_t I2C1_WriteAddr(uint8_t address,uint8_t rw);
uint8_t I2C1_WriteData(uint8_t data);
void I2C1_Stop(void);
void LCD_Init(void);
void LCD_Pulse(uint8_t data);
void LCD_SendNibble(uint8_t nibble, uint8_t mode);
void LCD_SendByte(uint8_t value, uint8_t mode);
uint8_t LCD_Command(uint8_t cmd);
uint8_t LCD_Data(uint8_t data);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_Print(char *str);

#endif /* I2C_H_ */
