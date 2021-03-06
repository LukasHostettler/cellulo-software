/**
 * @file bluetooth.h
 * @brief Header for bluetooth functionality
 * @author Ayberk �zg�r
 * @version 1.0
 * @date 2015-05-02
 */

/*
 * About the RN42 module:
 *
 * When the board is first flashed, the RN42 module must be "flashed" as well.
 * After powering up, within less than 60 seconds, connect to it with a serial
 * console over Bluetooth. Type
 *
 *      $$$
 *
 * to enter command mode. The module should respond with
 *
 *      CMD
 *
 * Then, type
 *
 *      ST,254<cr>
 *
 * to disable command mode over UART. The module should respond with
 *
 *      AOK
 *
 * Then, type
 *
 *      SU,92<cr>
 *
 * to set baud rate to 921K. The module should respond with
 *
 *      AOK
 *
 * as before. Finally, exit command mode with
 *
 *      ---<cr>
 *
 * and reboot the board.
 *
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

#define BT_RTS_BAR_PORT_CHANNEL PORT_CHANNEL_G
#define BT_RTS_BAR_PORT_BIT_POS PORTS_BIT_POS_8

#define BT_CTS_BAR_PORT_CHANNEL PORT_CHANNEL_G
#define BT_CTS_BAR_PORT_BIT_POS PORTS_BIT_POS_9

extern char btRxQueue[];                    ///< Queue for commands received over Bluetooth
extern unsigned int btRxQueueWriteIndex;    ///< Current write index for the Bluetooth command queue

/**
 * @brief List of Bluetooth commands
 */
typedef enum{
    BT_CMD_PING = 0,            ///< Ping request
    BT_CMD_FRAME_REQUEST,       ///< Request for camera frame
    BT_CMD_NUM_COMMANDS,
    BT_CMD_INVALID = -1
} BT_CMD;

/**
 * @brief Sends characters over Bluetooth
 * 
 * @param buf Characters to send
 * @param n Number of characters to send
 */
void bluetoothSend(char* buf, unsigned int n);

/**
 * @brief Sends characters over Bluetooth as pure ASCII hex
 *
 * Converts all characters to two character hex representation, e.g 255 (single
 * char) to "FF"
 *
 * @param buf Characters to send
 * @param n Number of characters to send
 */
void bluetoothSendHex(char* buf, unsigned int n);

/**
 * @brief initializes Bluetooth communication
 */
void APP_BT_Initialize();

/**
 * @brief Performs regular Bluetooth communication tasks
 */
void APP_BT_Tasks();

#endif	/* BLUETOOTH_H */

