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

#define IMG_WIDTH 752
#define IMG_HEIGHT 480

extern unsigned char pixels[];

/**
 * Initializes camera functionality
 */
void APP_Cam_Initialize();

/**
 * Performs regular camera tasks
 */
void APP_Cam_Tasks();

#endif	/* CAM_H */

