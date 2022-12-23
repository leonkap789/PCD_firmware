#include "MCP9808.h"


/*INITIALISATION*/
void MCP9808_Init(MCP9808 *dev, I2C_HandleTypeDef *i2cHandle)
{
    /*Initialise stuct and data registers*/
    dev->i2cHandle      = i2cHandle;
    dev->temp_C         = 0.0f;
    return;
}

/*DATA ACQUISITION*/
float MCP9808_Read_Temperature(MCP9808 *dev)
{
    // Initilise array
    uint8_t raw_temp[2];

    // Read temperature register
    MCP9808_Read_Registers(dev, MCP9808_TEMP, raw_temp, 2);

    // Convert raw temperature to float 
    float temp = (float)(raw_temp[0] & 0x0F)*16 + (float)(raw_temp[1])/16;

    // If the temperature is less than 0 *C
    if ((raw_temp[0] & 0x10) == 0x10)
    {
        temp = (float)256 - temp;
    }

    return temp; 
}

/*LOW_LEVEL FUNCTIONS*/
HAL_StatusTypeDef MCP9808_Read_Register(MCP9808 *dev, uint8_t reg, uint8_t *data)
{
    return HAL_I2C_Mem_Read(dev->i2cHandle, MCP9808_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}

HAL_StatusTypeDef MCP9808_Read_Registers(MCP9808 *dev, uint8_t reg, uint8_t *data, uint8_t length)
{
    return HAL_I2C_Mem_Read(dev->i2cHandle, MCP9808_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, length, HAL_MAX_DELAY);
}

HAL_StatusTypeDef MCP9808_Write_Register(MCP9808 *dev, uint8_t reg, uint8_t *data)
{
    return HAL_I2C_Mem_Write(dev->i2cHandle, MCP9808_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, data, 1, HAL_MAX_DELAY);
}