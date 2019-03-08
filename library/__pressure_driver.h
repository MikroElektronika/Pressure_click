/*
    __pressure_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __pressure_driver.h
@brief    Pressure Driver
@mainpage Pressure Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   PRESSURE
@brief      Pressure Click Driver
@{

| Global Library Prefix | **PRESSURE** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Feb 2019.**      |
| Developer             | **Nenad Filipovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _PRESSURE_H_
#define _PRESSURE_H_

/** 
 * @macro T_PRESSURE_P
 * @brief Driver Abstract type 
 */
#define T_PRESSURE_P    const uint8_t*

/** @defgroup PRESSURE_COMPILE Compilation Config */              /** @{ */

   #define   __PRESSURE_DRV_SPI__                            /**<     @macro __PRESSURE_DRV_SPI__  @brief SPI driver selector */
   #define   __PRESSURE_DRV_I2C__                            /**<     @macro __PRESSURE_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __PRESSURE_DRV_UART__                           /**<     @macro __PRESSURE_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup PRESSURE_VAR Variables */                           /** @{ */


extern const uint8_t  _PRESSURE_REF_P_XLB;
extern const uint8_t  _PRESSURE_REF_P_LSB;
extern const uint8_t  _PRESSURE_REF_P_MSB;

extern const uint8_t  _PRESSURE_DEVICE_ID_REG;

extern const uint8_t  _PRESSURE_RES_CONFIG;

extern const uint8_t  _PRESSURE_CTRL_REG1;
extern const uint8_t  _PRESSURE_CTRL_REG2;
extern const uint8_t  _PRESSURE_CTRL_REG3;

extern const uint8_t  _PRESSURE_INT_CFG_REG;
extern const uint8_t  _PRESSURE_INT_SOURCE_REG;

extern const uint8_t  _PRESSURE_THS_P_LSB_REG;
extern const uint8_t  _PRESSURE_THS_P_MSB_REG;

extern const uint8_t  _PRESSURE_STATUS_REG;

extern const uint8_t  _PRESSURE_PRESS_POUT_XLB_REH;
extern const uint8_t  _PRESSURE_PRESS_OUT_LSB;
extern const uint8_t  _PRESSURE_PRESS_OUT_MSB;

extern const uint8_t  _PRESSURE_TEMP_OUT_LSB;
extern const uint8_t  _PRESSURE_TEMP_OUT_MSB;

extern const uint8_t  _PRESSURE_AMP_CTRL;

extern const uint8_t  _PRESSURE_I2C_ADDRESS_0;
extern const uint8_t  _PRESSURE_I2C_ADDRESS_1;
                                                                       /** @} */
/** @defgroup PRESSURE_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup PRESSURE_INIT Driver Initialization */              /** @{ */

#ifdef   __PRESSURE_DRV_SPI__
void pressure_spiDriverInit(T_PRESSURE_P gpioObj, T_PRESSURE_P spiObj);
#endif
#ifdef   __PRESSURE_DRV_I2C__
void pressure_i2cDriverInit(T_PRESSURE_P gpioObj, T_PRESSURE_P i2cObj, uint8_t slave);
#endif
#ifdef   __PRESSURE_DRV_UART__
void pressure_uartDriverInit(T_PRESSURE_P gpioObj, T_PRESSURE_P uartObj);
#endif


/** @defgroup PRESSURE_FUNC Driver Functions */                   /** @{ */



/**
 * @brief Generic write the byte of data function
 *
 * @param[in] regAddress                Register address
 *
 * @param[in] writeData                 Byte of data to write
 *
 * Function write the 8-bit data to the
 * target 8-bit register address of LPS331AP sensor on Pressure click board.
 */
void pressure_writeData( uint8_t regAddress, uint8_t writeData );

/**
 * @brief Generic read the byte of data function
 *
 * @param[in] regAddress                Register address
 *
 * @return 
 * 8-bit read data
 *
 * Function read the 8-bit data from the
 * target 8-bit register address of LPS331AP sensor on Pressure click board.
 */
uint8_t pressure_readData( uint8_t regAddress );

/**
 * @brief Device ID read function
 *
 * @return
 * 8-bit read ID value
 *
 * Function read the 8-bit ID value from the
 * target 8-bit _PRESSURE_DEVICE_ID_REG register of LPS331AP sensor on Pressure click board.
 */
uint8_t pressure_readID();

/**
 * @brief Set configuration function
 *
 * @param[in] configVal                 8-bit configuratio value
 *
 * Function set configuration by write 8-bit configVal data to the
 * target 8-bit _PRESSURE_RES_CONFIG register of LPS331AP sensor on Pressure click board.
 */
void pressure_setConfiguration( uint8_t configVal );

/**
 * @brief Get configuration function
 *
 * @return
 * 8-bit read configuratio value
 *
 * Function get configuration by rad 8-bit config data from the
 * target 8-bit _PRESSURE_RES_CONFIG register of LPS331AP sensor on Pressure click board.
 */
uint8_t pressure_getConfiguration();

/**
 * @brief Enable the device function
 *
 * Function enable the device by set bit7 to the
 * target 8-bit _PRESSURE_CTRL_REG1 register of LPS331AP sensor on Pressure click board.
 */
void pressure_enable();

/**
 * @brief Disable the device function
 *
 * Function disable the device by clear bit7 to the
 * target 8-bit _PRESSURE_CTRL_REG1 register of LPS331AP sensor on Pressure click board.
 */
void pressure_powerDown();

/**
 * @brief Set output data rate function
 *
 * @param[in] outDataRate
 * - 0 : Pressure : One shot; Temperature : One shot
 * - 1 : Pressure : 1 Hz    ; Temperature : 1 Hz
 * - 2 : Pressure : 7 Hz    ; Temperature : 1 Hz
 * - 3 : Pressure : 12.5 Hz ; Temperature : 1 Hz
 * - 4 : Pressure : 25 Hz   ; Temperature : 1 Hz
 * - 5 : Pressure : 7 Hz    ; Temperature : 7 Hz
 * - 6 : Pressure : 12.5 Hz ; Temperature : 12.5 Hz
 * - 7 : Pressure : 25 Hz   ; Temperature : 25 Hz
 *
 * Function set output data rate by write output data rate value to the
 * target 8-bit _PRESSURE_CTRL_REG1 register of LPS331AP sensor on Pressure click board.
 */
void pressure_setOutputDataRate( uint8_t outDataRate );

/**
 * @brief Enable interrupt function
 *
 * Function enable interrupt circuit by set bit3 to the
 * target 8-bit _PRESSURE_CTRL_REG1 register of LPS331AP sensor on Pressure click board.
 */
void pressure_enableInterruptCircuit();

/**
 * @brief Disable interrupt function
 *
 * Function disable interrupt circuit by clear bit3 to the
 * target 8-bit _PRESSURE_CTRL_REG1 register of LPS331AP sensor on Pressure click board.
 */
void pressure_disableInterrupt();

/**
 * @brief Enable block data update function
 *
 * Function enable interrupt circuit by set bit2 to the
 * target 8-bit _PRESSURE_CTRL_REG1 register of LPS331AP sensor on Pressure click board.
 */
void pressure_blockDataUpdate();

/**
 * @brief Disable block data - continuous update function
 *
 * Function disable block data - continuous update circuit by clear bit2 to the
 * target 8-bit _PRESSURE_CTRL_REG1 register of LPS331AP sensor on Pressure click board.
 */
void pressure_unblockDataUpdate();

/**
 * @brief Delta pressure enable function
 *
 * Function enable delta pressure by set bit1 to the
 * target 8-bit _PRESSURE_CTRL_REG1 register of LPS331AP sensor on Pressure click board.
 */
void pressure_enableDeltaPressure();

/**
 * @brief Delta pressure disable function
 *
 * Function disable delta pressure by clear bit1 to the
 * target 8-bit _PRESSURE_CTRL_REG1 register of LPS331AP sensor on Pressure click board.
 */
void pressure_disableDeltaPressure();

/**
 * @brief SPI serial interface mode function
 *
 * @param[in] wireInterface
 * - 3 : 3-wire interface
 * - 3 : 4-wire interface;
 *
 * Function SPI serial interface mode by write wireInterface value to the
 * target 8-bit _PRESSURE_CTRL_REG1 register of LPS331AP sensor on Pressure click board.
 */
void pressure_spiSerialInterfaceMode( uint8_t wireInterface );

/**
 * @brief Reboot memory content mode function
 *
 * @param[in] rmMode
 * - 0 : normal mode;
 * - 3 : reboot memory content;
 *
 * Function reboot memory content mode by write rmMode value to the
 * target 8-bit _PRESSURE_CTRL_REG2 register of LPS331AP sensor on Pressure click board.
 */
void pressure_rebootMemoryMode( uint8_t rmMode );

/**
 * @brief Software reset function
 *
 * Function software reset by set bit2 to the
 * target 8-bit _PRESSURE_CTRL_REG2 register of LPS331AP sensor on Pressure click board.
 */
void pressure_softReset();

/**
 * @brief Set interrupt configuration function
 *
 * @param[in] intConfigVal
 * 8-bit interrupt configuration value:
 * - [ bit2 ] : Latch Interrupt request into INT_SOURCE register ( Default value: 0 )
 *            - 0 : interrupt request not latched;
 *            - 1 : interrupt request latched;
 * - [ bit1 ] : Enable interrupt generation on differential pressure low event ( Default value: 0 )
 *            - 0 : disable interrupt request;
 *            - 1 : enable interrupt request on measured differential pressure value lower than preset threshold;
 * - [ bit0 ] : Enable interrupt generation on differential pressure high event ( Default value: 0 )
 *            - 0 : disable interrupt request;
 *            - 1 : enable interrupt request on measured differential pressure value higher than preset threshold
 *
 * Function set interrupt configuration by write intConfigVal value to the
 * target 8-bit _PRESSURE_INT_CFG_REG register of LPS331AP sensor on Pressure click board.
 */
void pressure_setInterruptConfig( uint8_t intConfigVal );

/**
 * @brief Get interrupt configuration function
 *
 * @return
 * 8-bit interrupt configuration value
 *
 * Function get interrupt configuration by read value from the
 * target 8-bit _PRESSURE_INT_CFG_REG register of LPS331AP sensor on Pressure click board.
 */
uint8_t pressure_getInterruptConfig();

/**
 * @brief Default configuration function
 *
 * @return
 * - 0 : ERROR configuration;
 * - 1 : OK; 
 *
 * Function set default configuration by write default configuration value to the
 * target 8-bit _PRESSURE_RES_CONFIG, _PRESSURE_CTRL_REG1 and _PRESSURE_CTRL_REG1 register 
 * of LPS331AP sensor on Pressure click board.
 */
uint8_t pressure_defaultCofig();

/**
 * @brief Get pressure function
 *
 * @return
 * float pressure in mbar
 *
 * Function get pressure by read pressure data form the
 * target 8-bit _PRESSURE_PRESS_OUT_MSB, _PRESSURE_PRESS_OUT_LSB and _PRESSURE_PRESS_POUT_XLB_REH register
 * of LPS331AP sensor on Pressure click board
 * and convert that data to pressure in mbar.
 */
float pressure_getPressure();

/**
 * @brief Get temperature in degrees Celsius function
 *
 * @return
 * float temperature in degrees Celsius
 *
 * Function get temperature by read temperature data form the
 * target 8-bit _PRESSURE_TEMP_OUT_MSB and _PRESSURE_TEMP_OUT_LSB register
 * of LPS331AP sensor on Pressure click board
 * and convert that data to temperature in degrees Celsius.
 */
float pressure_getTemperature();

/**
 * @brief Get interrupt state function
 *
 * @return
 * 8-bit interrupt state:
 * - 0 : interrupt not detected;
 * - 1 : interrupt is detected;
 *
 * Function get interrupt state by show state of INT pin on Pressure click board.
 */
uint8_t pressure_getInterruptState();



                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Pressure_STM.c
    @example Click_Pressure_TIVA.c
    @example Click_Pressure_CEC.c
    @example Click_Pressure_KINETIS.c
    @example Click_Pressure_MSP.c
    @example Click_Pressure_PIC.c
    @example Click_Pressure_PIC32.c
    @example Click_Pressure_DSPIC.c
    @example Click_Pressure_AVR.c
    @example Click_Pressure_FT90x.c
    @example Click_Pressure_STM.mbas
    @example Click_Pressure_TIVA.mbas
    @example Click_Pressure_CEC.mbas
    @example Click_Pressure_KINETIS.mbas
    @example Click_Pressure_MSP.mbas
    @example Click_Pressure_PIC.mbas
    @example Click_Pressure_PIC32.mbas
    @example Click_Pressure_DSPIC.mbas
    @example Click_Pressure_AVR.mbas
    @example Click_Pressure_FT90x.mbas
    @example Click_Pressure_STM.mpas
    @example Click_Pressure_TIVA.mpas
    @example Click_Pressure_CEC.mpas
    @example Click_Pressure_KINETIS.mpas
    @example Click_Pressure_MSP.mpas
    @example Click_Pressure_PIC.mpas
    @example Click_Pressure_PIC32.mpas
    @example Click_Pressure_DSPIC.mpas
    @example Click_Pressure_AVR.mpas
    @example Click_Pressure_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __pressure_driver.h

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