/**
 * @file led.c
 * @brief Source for user interface LED activities
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-04-26
 */

#include"led.h"

LEDObject leds;

void setLED0(unsigned short red, unsigned short green, unsigned short blue){
    leds.leds.led0red = red;
    leds.leds.led0green = green;
    leds.leds.led0blue_high_nibble = blue >> 8;
    leds.leds.led0blue_low_byte = blue & LOW_BYTE_MASK;
}

void setLED1(unsigned short red, unsigned short green, unsigned short blue){
    leds.leds.led1red = red;
    leds.leds.led1green = green;
    leds.leds.led1blue_low_nibble = blue & LOW_NIBBLE_MASK;
    leds.leds.led1blue_high_byte = blue >> 4;
}

void setLED2(unsigned short red, unsigned short green, unsigned short blue){
    leds.leds.led2red = red;
    leds.leds.led2green = green;
    leds.leds.led2blue = blue;
}

void setLED3(unsigned short red, unsigned short green, unsigned short blue){
    leds.leds.led3red = red;
    leds.leds.led3green_low_byte = green & LOW_BYTE_MASK;
    leds.leds.led3green_high_nibble = green >> 8;
    leds.leds.led3blue = blue;
}

void setLED4(unsigned short red, unsigned short green, unsigned short blue){
    leds.leds.led4red = red;
    leds.leds.led4green_high_byte = green >> 4;
    leds.leds.led4green_low_nibble = green & LOW_NIBBLE_MASK;
    leds.leds.led4blue = blue;
}

void setLED5(unsigned short red, unsigned short green, unsigned short blue){
    leds.leds.led5red = red;
    leds.leds.led5green = green;
    leds.leds.led5blue = blue;
}