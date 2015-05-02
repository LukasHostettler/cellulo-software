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

#define BT_RX_QUEUE_SIZE 256

#define BT_RESET_BAR_PORT_CHANNEL PORT_CHANNEL_C
#define BT_RESET_BAR_PORT_BIT_POS PORTS_BIT_POS_12

#define BT_BAUD_9600_PORT_CHANNEL PORT_CHANNEL_C
#define BT_BAUD_9600_PORT_BIT_POS PORTS_BIT_POS_15

extern char btRxQueue[];
extern unsigned int btRxQueueWriteIndex;

/**
 * @brief Sends characters over Bluetooth
 * 
 * @param buf Characters to send
 * @param n Number of characters to send
 */
void bluetoothSend(char* buf, unsigned int n);

/**
 * @brief initializes Bluetooth communication
 */
void APP_BT_Initialize();

/**
 * @brief Performs regular Bluetooth communication tasks
 */
void APP_BT_Tasks();

#endif	/* BLUETOOTH_H */

