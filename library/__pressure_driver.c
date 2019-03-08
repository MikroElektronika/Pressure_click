/*
    __pressure_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__pressure_driver.h"
#include "__pressure_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __PRESSURE_DRV_I2C__
static uint8_t _slaveAddress;
#endif

static uint8_t pressureInterfaceSelect;

const uint8_t _PRESSURE_I2C_SELECT                                  = 0;
const uint8_t _PRESSURE_SPI_SELECT                                  = 1;

const uint8_t _PRESSURE_REF_P_XLB                                   = 0x08;                 //  Reference pressure  (LSB)
const uint8_t _PRESSURE_REF_P_LSB                                   = 0x09;                 //  Reference pressure  (middle)
const uint8_t _PRESSURE_REF_P_MSB                                   = 0x0A;                 //  Reference pressure  (MSB)

const uint8_t _PRESSURE_DEVICE_ID_REG                               = 0x0F;                 //  Device identification

const uint8_t _PRESSURE_RES_CONFIG                                  = 0x10;                 //  Pressure resolution
const uint8_t _PRESSURE_DEFAULT_CONFIG                              = 0xFA;                 //  Pressure resolution default value

const uint8_t _PRESSURE_CTRL_REG1                                   = 0x20;                 //  Control register 1
const uint8_t _PRESSURE_CTRL_REG2                                   = 0x21;                 //  Control register 2
const uint8_t _PRESSURE_CTRL_REG3                                   = 0x22;                 //  Control register 3

const uint8_t _PRESSURE_INT_CFG_REG                                 = 0x23;                 //  Interrupt configuration
const uint8_t _PRESSURE_INT_SOURCE_REG                              = 0x24;                 //  Interrupt source

const uint8_t _PRESSURE_THS_P_LSB_REG                               = 0x25;                 //  Treshold pressure (LSB)
const uint8_t _PRESSURE_THS_P_MSB_REG                               = 0x26;                 //  Treshold pressure (MSB)

const uint8_t _PRESSURE_STATUS_REG                                  = 0x27;                 //  Status register

const uint8_t _PRESSURE_PRESS_POUT_XLB_REH                          = 0x28;                 //  Pressure data (LSB)
const uint8_t _PRESSURE_PRESS_OUT_LSB                               = 0x29;                 //  Pressure data (middle)
const uint8_t _PRESSURE_PRESS_OUT_MSB                               = 0x2A;                 //  Pressure data (MSB)

const uint8_t _PRESSURE_TEMP_OUT_LSB                                = 0x2B;                 //  Temperature data (LSB)
const uint8_t _PRESSURE_TEMP_OUT_MSB                                = 0x2C;                 //  Temperature data (MSB)

const uint8_t _PRESSURE_AMP_CTRL                                    = 0x30;                 //  Analog front ned control

const uint8_t _PRESSURE_I2C_ADDRESS_0                               = 0x5C;
const uint8_t _PRESSURE_I2C_ADDRESS_1                               = 0x5D;                 //  Slave address

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __PRESSURE_DRV_SPI__

void pressure_spiDriverInit(T_PRESSURE_P gpioObj, T_PRESSURE_P spiObj)
{
    pressureInterfaceSelect = _PRESSURE_SPI_SELECT;
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    hal_gpio_csSet( 0 );
}

#endif
#ifdef   __PRESSURE_DRV_I2C__

void pressure_i2cDriverInit(T_PRESSURE_P gpioObj, T_PRESSURE_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    pressureInterfaceSelect = _PRESSURE_I2C_SELECT;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __PRESSURE_DRV_UART__

void pressure_uartDriverInit(T_PRESSURE_P gpioObj, T_PRESSURE_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif



/* ----------------------------------------------------------- IMPLEMENTATION */



/* Generic write the byte of data function */
void pressure_writeData( uint8_t regAddress, uint8_t writeData )
{
    uint8_t wBuffer[ 2 ];

    wBuffer[ 0 ] = regAddress;
    wBuffer[ 1 ] = writeData;

    if ( pressureInterfaceSelect == _PRESSURE_SPI_SELECT )
    {
        wBuffer[ 0 ] &= 0x3F;

        hal_gpio_csSet( 0 );
        hal_spiWrite( wBuffer, 2 );
        hal_gpio_csSet( 1 );
    }
    else
    {
        hal_i2cStart();
        hal_i2cWrite( _slaveAddress, wBuffer, 2, END_MODE_STOP );
    }
}

/* Generic read the byte of data function*/
uint8_t pressure_readData( uint8_t regAddress )
{
    uint8_t wBuffer[ 1 ];
    uint8_t rBuffer[ 1 ];

    wBuffer[ 0 ] = regAddress;

    if ( pressureInterfaceSelect == _PRESSURE_SPI_SELECT )
    {
        wBuffer[ 0 ] &= 0xBF;

        hal_gpio_csSet( 0 );
        hal_spiWrite( wBuffer, 1 );
        hal_spiRead( rBuffer, 1 );
        hal_gpio_csSet( 1 );
    }
    else
    {
        hal_i2cStart();
        hal_i2cWrite( _slaveAddress, wBuffer, 1, END_MODE_RESTART );
        hal_i2cRead( _slaveAddress, rBuffer, 1, END_MODE_STOP );
    }

    return rBuffer[ 0 ];
}

/* Device ID read function */
uint8_t pressure_readID()
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_DEVICE_ID_REG );

    return temp;
}

/* Set configuration function*/
void pressure_setConfiguration( uint8_t configVal )
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_RES_CONFIG );

    temp |= configVal;

    pressure_writeData( _PRESSURE_RES_CONFIG, temp );
}

/* Get configuration function*/
uint8_t pressure_getConfiguration()
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_RES_CONFIG );

    return temp;
}

/* Enable the device function*/
void pressure_enable()
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_CTRL_REG1 );

    temp |= 0x80;

    pressure_writeData( _PRESSURE_CTRL_REG1, temp );
}

/* Disable the device function*/
void pressure_powerDown()
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_CTRL_REG1 );

    temp &= 0x7F;

    pressure_writeData( _PRESSURE_CTRL_REG1, temp );
}

/* Set output data rate function*/
void pressure_setOutputDataRate( uint8_t outDataRate )
{
    uint8_t temp;

    outDataRate %= 8;
    outDataRate <<= 4;

    temp = pressure_readData( _PRESSURE_CTRL_REG1 );

    temp &= 0x8F;
    temp |= outDataRate;

    pressure_writeData( _PRESSURE_CTRL_REG1, temp );
}

/* Enable interrupt circuit function*/
void pressure_enableInterruptCircuit()
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_CTRL_REG1 );

    temp |= 0x08;

    pressure_writeData( _PRESSURE_CTRL_REG1, temp );
}

/* Disable interrupt function*/
void pressure_disableInterrupt()
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_CTRL_REG1 );

    temp &= 0xF7;

    pressure_writeData( _PRESSURE_CTRL_REG1, temp );
}

/* Enable block data update function*/
void pressure_blockDataUpdate()
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_CTRL_REG1 );

    temp |= 0x04;

    pressure_writeData( _PRESSURE_CTRL_REG1, temp );
}

/* Disable block data - continuous update function*/
void pressure_unblockDataUpdate()
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_CTRL_REG1 );

    temp &= 0xFB;

    pressure_writeData( _PRESSURE_CTRL_REG1, temp );
}

/* Delta pressure enable function */
void pressure_enableDeltaPressure()
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_CTRL_REG1 );

    temp |= 0x02;

    pressure_writeData( _PRESSURE_CTRL_REG1, temp );
}

/* Delta pressure disable function*/
void pressure_disableDeltaPressure()
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_CTRL_REG1 );

    temp &= 0xFD;

    pressure_writeData( _PRESSURE_CTRL_REG1, temp );
}

/* SPI serial interface mode function*/
void pressure_spiSerialInterfaceMode( uint8_t wireInterface )
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_CTRL_REG1 );

     if ( wireInterface == 4 )
     {
         temp &= 0xEF;
     }

     if ( wireInterface == 3 )
     {
         temp |= 0x01;
     }

    pressure_writeData( _PRESSURE_CTRL_REG1, temp );
}

/* Reboot memory content mode function*/
void pressure_rebootMemoryMode( uint8_t rmMode )
{
    uint8_t temp;

    rmMode %= 2;
    rmMode <<= 7;

    temp = pressure_readData( _PRESSURE_CTRL_REG2 );

    temp |= rmMode;

    pressure_writeData( _PRESSURE_CTRL_REG2, temp );
}

/*  Software reset function*/
void pressure_softReset()
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_CTRL_REG2 );

    temp |= 0x04;

    pressure_writeData( _PRESSURE_CTRL_REG2, temp );
}

/* Set interrupt configuration function*/
void pressure_setInterruptConfig( uint8_t intConfigVal )
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_INT_CFG_REG );

    temp |= intConfigVal;

    pressure_writeData( _PRESSURE_CTRL_REG2, temp );
}

/* Get interrupt configuration function*/
uint8_t pressure_getInterruptConfig()
{
    uint8_t temp;

    temp = pressure_readData( _PRESSURE_INT_CFG_REG );

    return temp;
}

/* Default configuration function */
uint8_t pressure_defaultCofig()
{
    uint8_t temp;
    uint8_t err;

    err = 1;

    pressure_writeData( _PRESSURE_RES_CONFIG, 0x78 );
    temp = pressure_readData( _PRESSURE_RES_CONFIG );

    if ( temp != 0x78 )
    {
        err = 0;
    }

    pressure_writeData( _PRESSURE_CTRL_REG1, 0x74 );
    temp = pressure_readData( _PRESSURE_CTRL_REG1 );

    if ( temp != 0x74 )
    {
        err = 0;
    }

    pressure_writeData( _PRESSURE_CTRL_REG1, 0xF4 );
    temp = pressure_readData( _PRESSURE_CTRL_REG1 );

    if ( temp != 0xF4 )
    {
        err = 0;
    }

    temp = pressure_readData( _PRESSURE_DEVICE_ID_REG );

    if ( temp != 0xBB )
    {
        err = 0;
    }

    return err;
}

/* Get pressure function */
float pressure_getPressure()
{
    uint32_t presVal;
    float pressure;
    uint8_t buffer[ 3 ];

    buffer[ 0 ] = pressure_readData( _PRESSURE_PRESS_OUT_MSB );
    buffer[ 1 ] =  pressure_readData( _PRESSURE_PRESS_OUT_LSB );
    buffer[ 2 ] = pressure_readData( _PRESSURE_PRESS_POUT_XLB_REH );

    presVal = buffer[ 0 ];
    presVal <<= 8;
    presVal |= buffer[ 1 ];
    presVal <<= 8;
    presVal |= buffer[ 2 ];

    presVal &= 0x00FFFFFF;

    pressure = ( float ) presVal;
    pressure /= 4096.0;

    return pressure;
}

/* Get temperature in degrees Celsius function */
float pressure_getTemperature()
{
    uint8_t buffer[ 2 ];
    int16_t tempVal;
    float temperature;

    buffer[ 0 ] = pressure_readData( _PRESSURE_TEMP_OUT_MSB );
    buffer[ 1 ] = pressure_readData( _PRESSURE_TEMP_OUT_LSB );

    tempVal = buffer[ 0 ];
    tempVal <<= 8;
    tempVal |= buffer[ 1 ];

    temperature = ( float ) tempVal;
    temperature /= 480.0;
    temperature += 42.5;

    return temperature;
}

/* Get interrupt state function*/
uint8_t pressure_getInterruptState()
{
    return hal_gpio_intGet();
}



/* -------------------------------------------------------------------------- */
/*
  __pressure_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */