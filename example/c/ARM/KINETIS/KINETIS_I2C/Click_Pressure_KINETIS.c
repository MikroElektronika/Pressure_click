/*
Example for Pressure Click

    Date          : Feb 2019.
    Author        : Nenad Filipovic

Test configuration KINETIS :
    
    MCU              : MK64
    Dev. Board       : HEXIWEAR
    ARM Compiler ver : v6.1.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes GPIO, I2C and LOG structures,
     sets INT pins as input and CS pin as output.
- Application Initialization - Initialization driver enable's - I2C, set default configuration start write log.
- Application Task - (code snippet) This is a example which demonstrates the use of Pressure Click board.
     Measured pressure and temperature data from the LPS331AP sensor on Pressure click board.
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs write on usb uart changes for every 3 sec.

*/

#include "Click_Pressure_types.h"
#include "Click_Pressure_config.h"


float pressure;
float temperature;
char logText[ 50 ];
char degCel[ 4 ];

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );

    mikrobus_i2cInit( _MIKROBUS1, &_PRESSURE_I2C_CFG[0] );

    mikrobus_logInit( _LOG_USBUART, 9600 );

    mikrobus_logWrite( "----------------------------", _LOG_LINE );
    mikrobus_logWrite( "       Pressure Click       ", _LOG_LINE );
    mikrobus_logWrite( "----------------------------", _LOG_LINE );
    Delay_100ms();
}

void applicationInit()
{
    pressure_i2cDriverInit( (T_PRESSURE_P)&_MIKROBUS1_GPIO, (T_PRESSURE_P)&_MIKROBUS1_I2C, _PRESSURE_I2C_ADDRESS_1 );
    Delay_100ms();

    degCel[ 0 ] = 32;
    degCel[ 1 ] = 176;
    degCel[ 2 ] = 67;
    degCel[ 3 ] = 0;

    if ( pressure_defaultCofig() )
        mikrobus_logWrite( "       Initialization", _LOG_LINE );
    else
        mikrobus_logWrite( "          ERROR", _LOG_LINE );

    mikrobus_logWrite( "----------------------------", _LOG_LINE );
    Delay_100ms();
}

void applicationTask()
{
    pressure = pressure_getPressure();
    Delay_10ms();
    mikrobus_logWrite( " Pressure   : ", _LOG_TEXT );
    FloatToStr( pressure, logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( " mbar", _LOG_LINE );

    temperature = pressure_getTemperature();
    Delay_10ms();
    mikrobus_logWrite( " Temperature: ", _LOG_TEXT );
    FloatToStr( temperature, logText );
    mikrobus_logWrite( logText, _LOG_TEXT );
    mikrobus_logWrite( degCel, _LOG_LINE );
    mikrobus_logWrite( "----------------------------", _LOG_LINE );

    Delay_1sec();
    Delay_1sec();
    Delay_1sec();
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}