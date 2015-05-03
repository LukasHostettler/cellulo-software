/**
 * @file at42qt1070.c
 * @brief Source for AT42QT1070 touch sensor functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-05-03
 */

#include"at42qt1070.h"

#include"util.h"

unsigned char keyStateBuf[2];
unsigned char* keyState;

void AT42QT1070Init(){
    keyState = &keyStateBuf[1];
}

void AT42QT1070Reset(){

    //For now, HW reset doesn't work. We will SW reset instead.

    //Reset sequence
    //PLIB_PORTS_PinClear(PORTS_ID_0, TOUCH_RESET_BAR_PORT_CHANNEL, TOUCH_RESET_BAR_PORT_BIT_POS);
    //for(i=0;i<1000000;i++) Nop();
    //PLIB_PORTS_PinSet(PORTS_ID_0, TOUCH_RESET_BAR_PORT_CHANNEL, TOUCH_RESET_BAR_PORT_BIT_POS);
    //for(i=0;i<1000000;i++) Nop();
    unsigned char c = 0xFF;
    I2CWriteBytes(AT42QT1070_I2C_SLAVE_WRITE_ADDR, AT42QT1070_REG_ADDR_RESET_BAR, 1, (unsigned char*)&c);
    delayTenNanos(50000000); //Delay 500 ms
}

void AT42QT1070SetAKS(unsigned char key, unsigned char group){
    if(group > 3 ||key > 6)
        return;

    unsigned char regAddr = AT42QT1070_REG_ADDR_AVE_AKS_KEY_0 + key;
    unsigned char regVal;
    I2CReadBytes(AT42QT1070_I2C_SLAVE_WRITE_ADDR, regAddr, 1, &regVal);
    regVal = (regVal & 0b11111100) + group;
    I2CWriteBytes(AT42QT1070_I2C_SLAVE_WRITE_ADDR, regAddr, 1, &regVal);
}

void AT42QT1070SetAVE(unsigned char key, unsigned char ave){
    if(key > 6 || (ave != 0 && ave != 1 && ave != 2 && ave != 4 && ave != 8 && ave != 16 && ave != 32))
        return;

    unsigned char regAddr = AT42QT1070_REG_ADDR_AVE_AKS_KEY_0 + key;
    unsigned char regVal;
    I2CReadBytes(AT42QT1070_I2C_SLAVE_WRITE_ADDR, regAddr, 1, &regVal);
    regVal = (regVal & 0b00000011) + (ave << 2);
    I2CWriteBytes(AT42QT1070_I2C_SLAVE_WRITE_ADDR, regAddr, 1, &regVal);
}

void AT42QT1070DisableKey(unsigned char key){
    AT42QT1070SetAVE(key, 0);
}

void AT42QT1070SetSamplePeriod(unsigned char eightMillis){
    I2CWriteBytes(AT42QT1070_I2C_SLAVE_WRITE_ADDR, AT42QT1070_REG_ADDR_LP, 1, &eightMillis);
}

void AT42QT1070GetKeyStates(bool* keys){
    I2CReadBytes(AT42QT1070_I2C_SLAVE_WRITE_ADDR, AT42QT1070_REG_ADDR_DETECTION_STATUS, 2, keyStateBuf);
    keys[0] = (*keyState & 0b00000001) >> 0;
    keys[1] = (*keyState & 0b00000010) >> 1;
    keys[2] = (*keyState & 0b00000100) >> 2;
    keys[3] = (*keyState & 0b00001000) >> 3;
    keys[4] = (*keyState & 0b00010000) >> 4;
    keys[5] = (*keyState & 0b00100000) >> 5;
}