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

#define IMG_WIDTH (752/4)
#define IMG_HEIGHT (480/4)

#define IMG_WIDTH_WITH_BLANKING ((752 + 94)/4 + 1)
#define IMG_HEIGHT_WITH_BLANKING ((480 + 45)/4 + 1)
#define IMG_VERTICAL_BLANKING_EXTRA 4

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

