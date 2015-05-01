/**
 * @file cam.c
 * @brief Source for camera functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-04-30
 */

#include"cam.h"

unsigned char pixels[IMG_WIDTH*IMG_HEIGHT];

void APP_Cam_Initialize(){

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
    Nop();
}

