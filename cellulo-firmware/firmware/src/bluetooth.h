/**
 * @file bluetooth.h
 * @brief Header for bluetooth functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-05-02
 */

#ifndef BLUETOOTH_H
#define	BLUETOOTH_H

#include<GenericTypeDefs.h>

#include"system_config/pic32mz1024ecg064/system_definitions.h"

#define BT_RESET_BAR_PORT_CHANNEL PORT_CHANNEL_C
#define BT_RESET_BAR_PORT_BIT_POS PORTS_BIT_POS_12

#define BT_BAUD_9600_PORT_CHANNEL PORT_CHANNEL_C
#define BT_BAUD_9600_PORT_BIT_POS PORTS_BIT_POS_15

/**
 * @brief Asserts a reset sequence
 */
void resetBluetooth();

/**
 * @brief Forces 9600 baud rate or releases it
 *
 * @param enable Whether to force 9600 baud rate
 */
void forceBluetoothBaud9600(BOOL enable);

#endif	/* BLUETOOTH_H */

