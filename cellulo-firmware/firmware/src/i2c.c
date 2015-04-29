/**
 * @file i2c.c
 * @brief Source for I2C functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-04-26
 */

#include"i2c.h"

#include <xc.h>

void _I2CWriteByte(unsigned char byte){
    if(DRV_I2C0_ByteWrite(byte)){
        DRV_I2C0_WaitForByteWriteToComplete();
        if(!DRV_I2C0_WriteByteAcknowledged()){
            Nop();
        }
    }
    else{
        Nop();
    }
}

void I2CReadBytes(unsigned char slaveAddr, unsigned char registerAddr, int n, unsigned char* buffer){

    //Assert start sequence
    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_MasterStart();
    DRV_I2C0_WaitForStartComplete();

    //Send slave write address
    while (!DRV_I2C0_MasterBusIdle());
    _I2CWriteByte((slaveAddr << 1) + 0);

    //Send register address
    while (!DRV_I2C0_MasterBusIdle());
    _I2CWriteByte(registerAddr);

    //Assert restart sequence
    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_MasterRestart();
    DRV_I2C0_WaitForStartComplete();

    //Send slave read address
    while (!DRV_I2C0_MasterBusIdle());
    _I2CWriteByte((slaveAddr << 1) + 1);

    //Read n - 1 bytes with ACK in the end
    while(n > 1){

        //Set up byte read
        while (!DRV_I2C0_MasterBusIdle());
        DRV_I2C0_SetUpByteRead();
        while(!DRV_I2C0_WaitForReadByteAvailable());
        *buffer = DRV_I2C0_ByteRead();
        buffer++;

        //Assert ACK
        DRV_I2C0_MasterACKSend();
        while (!DRV_I2C0_WaitForACKOrNACKComplete());

        n--;
    }

    //Read last byte with NACK in the end
    {

        //Set up byte read
        while (!DRV_I2C0_MasterBusIdle());
        DRV_I2C0_SetUpByteRead();
        while(!DRV_I2C0_WaitForReadByteAvailable());
        *buffer = DRV_I2C0_ByteRead();

        //Assert NACK
        DRV_I2C0_MasterNACKSend();
        while (!DRV_I2C0_WaitForACKOrNACKComplete());
    }

    //Send stop sequence
    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_MasterStop();

    //Stop sequence stops and restarts whole I2C module due to silicon bug
    //so no need to wait for stop condition end
}