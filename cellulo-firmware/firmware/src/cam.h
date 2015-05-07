/**
 * @file cam.h
 * @brief Header for camera functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-04-30
 */

#ifndef CAM_H
#define	CAM_H

#include"mt9v034.h"

#define PIXEL_WR_PORT_CHANNEL PORT_CHANNEL_D
#define PIXEL_WR_PORT_BIT_POS PORTS_BIT_POS_4

#define IMG_WIDTH (752)/2
#define IMG_HEIGHT (480)/2

#define DCHCON_CHEN_MASK 0b00000000000000000000000010000000

extern unsigned char pixels[];
extern bool frameReady;
extern bool frameRequest;

/**
 * Initializes camera functionality
 */
void APP_Cam_Initialize();

/**
 * Performs regular camera tasks
 */
void APP_Cam_Tasks();

#endif	/* CAM_H */

