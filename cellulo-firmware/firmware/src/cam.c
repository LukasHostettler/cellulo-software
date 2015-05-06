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
unsigned int currentRow = 0;
unsigned int currentPixel = 0;

void APP_Cam_Initialize(){
    frameReady = false;
    frameRequest = false;
    currentRow = 0;
    currentPixel = 0;

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
    if(frameReady){
        bluetoothSend(pixels, IMG_HEIGHT*IMG_WIDTH);
        frameReady = false;
    }
}

void __ISR(_EXTERNAL_2_VECTOR, IPL7AUTO) _PIXEL_WR_Handler(void){
    pixels[currentPixel] = PORTE;
    currentPixel++;
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_2);
}

void __ISR(_EXTERNAL_3_VECTOR, IPL7AUTO) _LINE_VALID_Handler(void){
    currentRow++;
    if(currentRow >= 120){

        //Frame finished here

        PLIB_INT_SourceDisable(INT_ID_0, INT_SOURCE_EXTERNAL_2);
        if(frameRequest){
            frameReady = true;
            frameRequest = false;
        }
    }
    else
        currentPixel = currentRow*IMG_WIDTH;
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_3);
}

void __ISR(_EXTERNAL_4_VECTOR, IPL7AUTO) _FRAME_VALID_Handler(void){
    currentRow = 0;
    currentPixel = 0;

    if(frameRequest){
        PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_EXTERNAL_2);
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_2);
    }

    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_4);
}
