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

unsigned char pixels[IMG_WIDTH_WITH_BLANKING*IMG_HEIGHT_WITH_BLANKING + IMG_VERTICAL_BLANKING_EXTRA];
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
    MT9V034SetBinning(MT9V034_BIN_4, MT9V034_BIN_4);
}

void APP_Cam_Tasks(){

    //Consume frame
    if(frameReady && frameRequest){
        bluetoothSend(pixels, IMG_HEIGHT*IMG_WIDTH);
        frameRequest = false;
        //PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_4);
        //PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_EXTERNAL_4);
    }
}

void __ISR(_EXTERNAL_3_VECTOR, IPL7AUTO) _LINE_VALID_Handler(void){

    if(!frameReady){
        PLIB_DMA_ChannelXDestinationStartAddressSet(DMA_ID_0, DMA_CHANNEL_0, (uint32_t)&pixels[currentRow*IMG_WIDTH]);
        PLIB_DMA_ChannelXEnable(DMA_ID_0, DMA_CHANNEL_0);

        currentRow++;
        if(currentRow >= IMG_HEIGHT){

            //Frame finished here
            frameReady = true;
        }
    }

    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_3);
}

void __ISR(_EXTERNAL_4_VECTOR, IPL7AUTO) _FRAME_VALID_Handler(void){

    if(!frameRequest){
        currentRow = 0;
        frameReady = false;
    }

    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_4);
}
