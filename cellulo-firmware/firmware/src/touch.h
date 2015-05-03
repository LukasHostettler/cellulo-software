/**
 * @file touch.h
 * @brief Header for touch input functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-05-03
 */

#ifndef TOUCH_H
#define	TOUCH_H

#include"at42qt1070.h"

#include<GenericTypeDefs.h>

#include"system_config/pic32mz1024ecg064/system_definitions.h"

#define TOUCH_CHANGE_BAR_PORT_CHANNEL PORT_CHANNEL_D
#define TOUCH_CHANGE_BAR_PORT_BIT_POS PORTS_BIT_POS_9

/**
 * Initializes touch input functionality
 */
void APP_Touch_Initialize();

/**
 * Performs regular touch input tasks
 */
void APP_Touch_Tasks();

#endif	/* TOUCH_H */

