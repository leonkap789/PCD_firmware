#ifndef MCP9808_I2C_DRIVER_H
#define MCP9808_I2C_DRIVER_H

//INCLUDES
#include "stm32f405xx.h" //Need for I2C HAL calls
#include "i2c.h"

//DEFINES
#define MCP9808_I2C_ADDR (0x18 << 1) //Left shift for I2C

//REGISTERS
#define MCP9808_TEMP            0x05


//SENSOR STRUCT
typedef struct
{
    //I2C Handle
    I2C_HandleTypeDef *i2cHandle;

    //Temperature data in C
    float temp_C;
} MCP9808;

//INITIALISATION
void MCP9808_Init(MCP9808 *dev, I2C_HandleTypeDef *i2cHandle);

//DATA ACQUISITION
HAL_StatusTypeDef MCP9808_Read_Temp(MCP9808 *dev);

//LOW-LEVEL FUNCTIONS
HAL_StatusTypeDef MCP9808_Read_Register(MCP9808 *dev, uint8_t reg, uint8_t *data);
HAL_StatusTypeDef MCP9808_Read_Registers(MCP9808 *dev, uint8_t reg, uint8_t *data, uint8_t length);
HAL_StatusTypeDef MCP9808_Write_Register(MCP9808 *dev, uint8_t reg, uint8_t *data);


#endif