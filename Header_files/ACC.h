

#ifndef ACC_H_
#define ACC_H_
void delay();

typedef struct
{
	int16_t ax;
	int16_t ay;
	int16_t az;
}adx;

void LIS302DL_write(uint8_t address, uint8_t value);
void LIS302DL_init(void);
void LIS302DL_get_values(adx *values);
uint8_t LIS302DL_read_device_id(void);
uint16_t isqrt(uint32_t num);


#endif /* ACC_H_ */
