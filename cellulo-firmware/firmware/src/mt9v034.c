/**
 * @file mt9v034.c
 * @brief Source for MT9V034 image sensor functionality
 * @author Ayberk �zg�r
 * @version 1.0
 * @date 2015-04-30
 */

#include "mt9v034.h"

void MT9V034Reset(){
    int i;

    //Reset sequence
    PLIB_PORTS_PinClear(PORTS_ID_0, IMG_RESET_BAR_PORT_CHANNEL, IMG_RESET_BAR_PORT_BIT_POS);
    for(i=0;i<1000000;i++) Nop();
    PLIB_PORTS_PinSet(PORTS_ID_0, IMG_RESET_BAR_PORT_CHANNEL, IMG_RESET_BAR_PORT_BIT_POS);
    for(i=0;i<1000000;i++) Nop();

    //Clear bit 9 of CHIP CONTROL register
    MT9V034Register reg;
    I2CReadBytes(MT9V034_I2C_SLAVE_WRITE_ADDR, MT9V034_REG_ADDR_CHIP_CONTROL, 2, (unsigned char*)&reg);
    reg.highByte = reg.highByte & 0b11111101;
    I2CWriteBytes(MT9V034_I2C_SLAVE_WRITE_ADDR, MT9V034_REG_ADDR_CHIP_CONTROL, 2, (unsigned char*)&reg);
    for(i=0;i<1000000;i++) Nop();
}

void MT9V034Standby(BOOL enable){
    int i;
    if(enable){
        PLIB_PORTS_PinSet(PORTS_ID_0, IMG_STANDBY_PORT_CHANNEL, IMG_STANDBY_PORT_BIT_POS);
        //TODO: Disable clock here after current frame is finished
    }
    else{
        //TODO: Enable clock here
        for(i=0;i<1000;i++) Nop(); //Wait at least 10 SYSCLK cycles
        PLIB_PORTS_PinClear(PORTS_ID_0, IMG_STANDBY_PORT_CHANNEL, IMG_STANDBY_PORT_BIT_POS);
        for(i=0;i<1000;i++) Nop(); //Wait at least 10 SYSCLK cycles
    }
}

void MT9V034OutputEnable(BOOL enable){
    if(enable)
        PLIB_PORTS_PinSet(PORTS_ID_0, IMG_OE_PORT_CHANNEL, IMG_OE_PORT_BIT_POS);
    else
        PLIB_PORTS_PinClear(PORTS_ID_0, IMG_OE_PORT_CHANNEL, IMG_OE_PORT_BIT_POS);
}