![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Pressure Click

---

- **CIC Prefix**  : PRESSURE
- **Author**      : Nenad Filipovic
- **Verison**     : 1.0.0
- **Date**        : Feb 2019.

---

### Software Support

We provide a library for the Pressure Click on our [LibStock](https://libstock.mikroe.com/projects/view/612/pressure-click-example) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library covers all the necessary functions to control Pressure Click board. 
Library performs the communication with the device via I2C driver by writting to registers and by reading from registers.
Library set/get configuration, for get ID, for enable/disable device,
for measuring pressure and temperature and convert that data to pressure in mbar and temperature in degrees Celsius, etc.

Key functions :

- ``` uint8_t pressure_defaultCofig() ``` - Default configuration function.
- ``` float pressure_getPressure() ``` - Get pressure function.
- ``` float pressure_getTemperature() ``` - Get temperature in degrees Celsius function.

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes GPIO, I2C and LOG structures,
     sets INT pins as input and CS pin as output.
- Application Initialization - Initialization driver enable's - I2C, set default configuration start write log.
- Application Task - (code snippet) This is a example which demonstrates the use of Pressure Click board.
     Measured pressure and temperature data from the LPS331AP sensor on Pressure click board.
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs write on usb uart changes for every 3 sec.


```.c

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

```



The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/612/pressure-click-example) page.

Other mikroE Libraries used in the example:

- I2C
- UART
- Conversion

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
