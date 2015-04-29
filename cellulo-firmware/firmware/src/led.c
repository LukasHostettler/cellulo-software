/**
 * @file led.c
 * @brief Source for user interface LED activities
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-04-26
 */

#include"led.h"

LEDObject leds;
char awaitingLatch;
DRV_HANDLE spiHandle;
DRV_SPI_BUFFER_HANDLE bufHandle;

void APP_LED_Initialize(){
    spiHandle = DRV_SPI_Open(DRV_SPI_INDEX_0, DRV_IO_INTENT_WRITE);
    if(spiHandle == DRV_HANDLE_INVALID){
        Nop(); //TODO: Throw exception
    }

    awaitingLatch = 0;

    int i;
    for(i=0;i<7;i++)
        leds.buffer[i] = 0;

    sendLEDData();
}

void APP_LED_Tasks(){
    if(awaitingLatch)
        if(DRV_SPI_BUFFER_EVENT_COMPLETE & DRV_SPI_BufferStatus(bufHandle)){
            latchLEDData();
            awaitingLatch = 0;
        }
}

void latchLEDData(){
    int i=0;
    for(;i<6400;i++)
        Nop();
    PLIB_PORTS_PinSet(PORTS_ID_0, LED_XLAT_PORT_CHANNEL, LED_XLAT_PORT_BIT_POS);
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); //Wait 30ns
    PLIB_PORTS_PinClear(PORTS_ID_0, LED_XLAT_PORT_CHANNEL, LED_XLAT_PORT_BIT_POS);
}

void sendLEDData(){
    int i;
    for(i=0;i<7;i++){
        bufHandle = DRV_SPI_BufferAddWrite(spiHandle, (void*)&leds.buffer[i], 4, NULL, NULL);
        if(bufHandle == DRV_SPI_BUFFER_HANDLE_INVALID){
            Nop(); //TODO: Throw exception
        }
    }
    awaitingLatch = 1;
}

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