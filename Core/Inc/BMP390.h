#ifndef BMP390_I2C_DRIVER_H
#define BMP390_I2C_DRIVER_H

/*INCLUDES*/
#include "stm32f405xx.h" /*Need for I2C HAL calls*/
#include "i2c.h"

/*DEFINES*/
#define BMP390_I2C_ADDR (0x76 << 1) /*Left shift for I2C*/

/*REGISTERS*/
#define BMP390_CMD              0x7E
#define BMP390_CONFIG           0x1F
#define BMP390_ODR              0x1D
#define BMP390_OSR              0x1C
#define BMP390_PWR_CTRL         0x1B
#define BMP390_IF_CONF          0x1A
#define BMP390_INT              0x19
#define BMP390_FIFO_CONFIG_2    0x18
#define BMP390_FIFO_CONFIG_1    0x17
#define BMP390_FIFO_WTM_1       0x16
#define BMP390_FIFO_WTM_0       0x15
#define BMP390_FIFO_DATA        0x14
#define BMP390_FIFO_LENGTH_1    0x13
#define BMP390_FIFO_LENGTH_0    0x12
#define BMP390_INT_STATUS       0x11
#define BMP390_EVENT            0x10
#define BMP390_SENSORTIME_2     0x0E
#define BMP390_SENSORTIME_1     0x0D
#define BMP390_SENSORTIME_0     0x0C
#define BMP390_DATA_5           0x09
#define BMP390_DATA_4           0x08
#define BMP390_DATA_3           0x07
#define BMP390_DATA_2           0x06
#define BMP390_DATA_1           0x05
#define BMP390_DATA_0           0x04
#define BMP390_STATUS           0x03
#define BMP390_ERR_REG          0x02
#define BMP390_REV_ID           0x01
#define BMP390_CHIP_ID          0x00

/*SENSOR STRUCT*/
typedef struct
{
    /*I2C Handle*/
    I2C_HandleTypeDef *i2cHandle;

    /*Pressure data in Pa*/
    float pressure_Pa;

    /*Temperature data in C*/
    float temp_C;
} BMP390;

/*INITIALISATION*/
void BMP390_Init(BMP390 *dev, I2C_HandleTypeDef *i2cHandle);

/*DATA ACQUISITION*/
HAL_StatusTypeDef BMP390_Read_Pressure(BMP390 *dev);
/* HAL_StatusTypeDef BMP390_Read_Temp(BMP390 *dev);
HAL_StatusTypeDef BMP390_Read_Pressure_Temp(BMP390 *dev); */

/*LOW-LEVEL FUNCTIONS*/
HAL_StatusTypeDef BMP390_Read_Register(BMP390 *dev, uint8_t reg, uint8_t *data);
HAL_StatusTypeDef BMP390_Read_Registers(BMP390 *dev, uint8_t reg, uint8_t *data, uint8_t length);
HAL_StatusTypeDef BMP390_Write_Register(BMP390 *dev, uint8_t reg, uint8_t *data);


#endif