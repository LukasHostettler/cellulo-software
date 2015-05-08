/**
 * @file cam.c
 * @brief Source for camera functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-04-30
 */

#include"cam.h"

#include <xc.h>
#include <sys/attribs.h>
#include "system_definitions.h"

unsigned char pixels[IMG_WIDTH*IMG_HEIGHT];
bool frameReady;
bool frameRequest;
bool disableLineValid;
unsigned int currentRow = 0;

void APP_Cam_Initialize(){
    frameReady = false;
    frameRequest = false;
    disableLineValid = false;
    currentRow = 0;

    //Initialize pixel memory
    int i;
    for(i=0;i<IMG_WIDTH*IMG_HEIGHT;i++)
        pixels[i] = 0;

    //Initialize image sensor
    MT9V034Reset();
    MT9V034OutputEnable(TRUE);
    MT9V034SetBinning(MT9V034_BIN_2, MT9V034_BIN_2);
}

void APP_Cam_Tasks(){

    //Consume frame
    if(frameReady && frameRequest){
        bluetoothSendHex(pixels, IMG_HEIGHT*IMG_WIDTH);
        frameRequest = false;
    }
}

void __ISR(_EXTERNAL_3_VECTOR, IPL7AUTO) _LineStartHandler(void){
    if(!frameReady)
        DCH0CONSET = DCHCON_CHEN_MASK;
    
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_3);
}

void __ISR(_DMA0_VECTOR, ipl7AUTO) _LineFinishedHandler(void){
    currentRow++;
    if(currentRow >= IMG_HEIGHT)
        frameReady = true;
    else
        DCH0DSA = ConvertToPhysicalAddress(&pixels[currentRow*IMG_WIDTH]);


    DCH0INTCLR = 0x000000ff;
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_DMA_0);
}

void __ISR(_EXTERNAL_4_VECTOR, IPL7AUTO) _FrameStartHandler(void){
    if(!frameRequest){
        currentRow = 0;
        DCH0DSA = ConvertToPhysicalAddress(pixels);
        frameReady = false;
    }

    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_4);
}
