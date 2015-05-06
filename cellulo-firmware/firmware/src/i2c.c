/**
 * @file i2c.c
 * @brief Source for I2C functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-04-26
 */

#include"i2c.h"

#include<xc.h>
#include<sys/attribs.h>
#include"system_definitions.h"

unsigned char _I2CWriteByte(unsigned char byte){
    if(DRV_I2C0_ByteWrite(byte)){
        DRV_I2C0_WaitForByteWriteToComplete();
        if(!DRV_I2C0_WriteByteAcknowledged())
            return -1;
    }
    else
        return -2;

    return 0;
}

void I2CReadBytes(unsigned char writeAddr, unsigned char registerAddr, int n, unsigned char* buffer){

    //Assert start sequence
    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_MasterStart();
    DRV_I2C0_WaitForStartComplete();

    //Send slave write address
    while (!DRV_I2C0_MasterBusIdle());
    _I2CWriteByte(writeAddr);

    //Send register address
    while (!DRV_I2C0_MasterBusIdle());
    _I2CWriteByte(registerAddr);

    //Assert restart sequence
    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_MasterRestart();
    DRV_I2C0_WaitForStartComplete();

    //Send slave read address
    while (!DRV_I2C0_MasterBusIdle());
    _I2CWriteByte(writeAddr + 1);

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

void I2CWriteBytes(unsigned char writeAddr, unsigned char registerAddr, int n, unsigned char* buffer){

    //Assert start sequence
    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_MasterStart();
    DRV_I2C0_WaitForStartComplete();

    //Send slave write address
    while (!DRV_I2C0_MasterBusIdle());
    _I2CWriteByte(writeAddr);

    //Send register address
    while (!DRV_I2C0_MasterBusIdle());
    _I2CWriteByte(registerAddr);

    //Write n bytes
    while(n > 0){
        while (!DRV_I2C0_MasterBusIdle());
        _I2CWriteByte(*buffer);
        buffer++;
        n--;
    }

    //Assert start sequence
    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_MasterStart();
    DRV_I2C0_WaitForStartComplete();

    //Send stop sequence
    while (!DRV_I2C0_MasterBusIdle());
    DRV_I2C0_MasterStop();

    //Stop sequence stops and restarts whole I2C module due to silicon bug
    //so no need to wait for stop condition end
}

void __ISR(_I2C5_MASTER_VECTOR, ipl1AUTO) _IntHandlerDrvI2CMasterInstance0(void){

    /* TODO: Add code to process interrupt here */
    /* Clear pending interrupt */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_5_MASTER);

}

void __ISR(_I2C5_BUS_VECTOR, ipl1AUTO) _IntHandlerDrvI2CErrorInstance0(void){

    /* TODO: Add code to process interrupt here */
    /* Clear pending interrupt */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_5_BUS);
}
