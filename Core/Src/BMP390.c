#include "BMP390.h"


/*INITIALISATION*/
void BMP390_Init(BMP390 *dev, I2C_HandleTypeDef *i2cHandle)
{
    /*Initialise stuct and data registers*/
    dev->i2cHandle      = i2cHandle;
    dev->pressure_Pa    = 0.0f;
    dev->temp_C         = 0.0f;

    __HAL_RCC_I2C1_FORCE_RESET();
    HAL_Delay(100);
    __HAL_RCC_I2C1_RELEASE_RESET();

    /*Initialise IIR filter*/
    uint8_t IIR_filter_1 = 0x02;
    uint8_t rslt = BMP390_Write_Register(dev, BMP390_CONFIG, &IIR_filter_1);
    if (rslt != HAL_OK)
    {
        while(1)
        {

        }
    }

    return;
}

/*DATA ACQUISITION*/
HAL_StatusTypeDef BMP390_Read_Pressure(BMP390 *dev)
{
    uint8_t raw_pressure[3];
    uint8_t read_pressure = 0x11;
    BMP390_Write_Register(dev, BMP390_PWR_CTRL, &read_pressure); /*Forced pressure read*/
    BMP390_Read_Registers(dev, BMP390_DATA_2, raw_pressure, 3);
}

/* HAL_StatusTypeDef BMP390_Read_Temp(BMP390 *dev)
{

}

HAL_StatusTypeDef BMP390_Read_Pressure_Temp(BMP390 *dev)
{

} */

/*LOW_LEVEL FUNCTIONS*/
HAL_StatusTypeDef BMP390_Read_Register(BMP390 *dev, uint8_t reg, uint8_t *data)
{
    return HAL_I2C_Mem_Read(dev->i2cHandle, BMP390_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, 50);
}

HAL_StatusTypeDef BMP390_Read_Registers(BMP390 *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
    return HAL_I2C_Mem_Read(dev->i2cHandle, BMP390_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, length, 50);
}

HAL_StatusTypeDef BMP390_Write_Register(BMP390 *dev, uint8_t reg, uint8_t *data)
{
    return HAL_I2C_Mem_Write(dev->i2cHandle, BMP390_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, 50);
}