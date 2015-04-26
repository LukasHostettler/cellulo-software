/**
 * @file led.h
 * @brief Header for user interface LED activities
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-04-26
 */

#ifndef LED_H
#define	LED_H

#include "driver/spi/drv_spi.h"   // SYS function prototypes

#define LOW_NIBBLE_MASK 0x000F
#define LOW_BYTE_MASK 0x00FF

#define LED_XLAT_PORT_CHANNEL PORT_CHANNEL_C
#define LED_XLAT_PORT_BIT_POS PORTS_BIT_POS_14

/**
 * @brief Describes a sequence of 6 RGB leds, each with 12-bit brightness
 *
 * Since buffer elements are sent from 0 to 6, they end up reversed in the
 * shift register of the LED driver. Therefore they are in reverse order here.
 */
typedef union{
    struct{

        //Int 0
        unsigned int led5green              : 12;
        unsigned int led5blue               : 12;
        unsigned int unused                 : 8;

        //Int 1
        unsigned int led4green_high_byte    : 8;
        unsigned int led4blue               : 12;
        unsigned int led5red                : 12;

        //Int 2
        unsigned int led3green_high_nibble  : 4;
        unsigned int led3blue               : 12;
        unsigned int led4red                : 12;
        unsigned int led4green_low_nibble   : 4;

        //Int 3
        unsigned int led2blue               : 12;
        unsigned int led3red                : 12;
        unsigned int led3green_low_byte     : 8;

        //Int 4
        unsigned int led1blue_high_byte     : 8;
        unsigned int led2red                : 12;
        unsigned int led2green              : 12;

        //Int 5
        unsigned int led0blue_high_nibble   : 4;
        unsigned int led1red                : 12;
        unsigned int led1green              : 12;
        unsigned int led1blue_low_nibble    : 4;

        //Int 6
        unsigned int led0red                : 12;
        unsigned int led0green              : 12;
        unsigned int led0blue_low_byte      : 8;
    } leds;
    
    unsigned int buffer[7];
} LEDObject;

/**
 * Initializes user interface LED functionality
 */
void APP_LED_Initialize();

/**
 * Performs regular user interface LED tasks
 */
void APP_LED_Tasks();

/**
 * Starts sending current LED data to driver
 */
void sendLEDData();

/**
 * Latches current LED data in the driver
 */
void latchLEDData();

/**
 * @brief Sets the LED0 brightness, gets updated in the next cycle
 * @param red Red brightness, 0 to 4095
 * @param green Green brightness, 0 to 4095
 * @param blue Blue brightness, 0 to 4095
 */
void setLED0(unsigned short red, unsigned short green, unsigned short blue);

/**
 * @brief Sets the LED1 brightness, gets updated in the next cycle
 * @param red Red brightness, 0 to 4095
 * @param green Green brightness, 0 to 4095
 * @param blue Blue brightness, 0 to 4095
 */
void setLED1(unsigned short red, unsigned short green, unsigned short blue);

/**
 * @brief Sets the LED2 brightness, gets updated in the next cycle
 * @param red Red brightness, 0 to 4095
 * @param green Green brightness, 0 to 4095
 * @param blue Blue brightness, 0 to 4095
 */
void setLED2(unsigned short red, unsigned short green, unsigned short blue);

/**
 * @brief Sets the LED3 brightness, gets updated in the next cycle
 * @param red Red brightness, 0 to 4095
 * @param green Green brightness, 0 to 4095
 * @param blue Blue brightness, 0 to 4095
 */
void setLED3(unsigned short red, unsigned short green, unsigned short blue);

/**
 * @brief Sets the LED4 brightness, gets updated in the next cycle
 * @param red Red brightness, 0 to 4095
 * @param green Green brightness, 0 to 4095
 * @param blue Blue brightness, 0 to 4095
 */
void setLED4(unsigned short red, unsigned short green, unsigned short blue);

/**
 * @brief Sets the LED5 brightness, gets updated in the next cycle
 * @param red Red brightness, 0 to 4095
 * @param green Green brightness, 0 to 4095
 * @param blue Blue brightness, 0 to 4095
 */
void setLED5(unsigned short red, unsigned short green, unsigned short blue);

#endif	/* LED_H */

