/**
 * @file bluetooth.c
 * @brief Source for bluetooth functionality
 * @author Ayberk �zg�r
 * @version 1.0
 * @date 2015-05-02
 */

#include"bluetooth.h"

#include<xc.h>
#include<sys/attribs.h>
#include<string.h>

#include"system_definitions.h"
#include"cam.h"

char btRxQueue[BT_RX_QUEUE_SIZE];
char btRxCmd[BT_RX_QUEUE_SIZE];
unsigned int btRxQueueWriteIndex;
unsigned int btRxQueueReadIndex;
unsigned int btRxCmdIndex;
const char* btCmdStrings[] = {
    "PING_",
    "FRAME"
};

void bluetoothReset(){
    int k;
    PLIB_PORTS_PinClear(PORTS_ID_0, BT_RESET_BAR_PORT_CHANNEL, BT_RESET_BAR_PORT_BIT_POS);
    for(k=0;k<1000000;k++);
    PLIB_PORTS_PinSet(PORTS_ID_0, BT_RESET_BAR_PORT_CHANNEL, BT_RESET_BAR_PORT_BIT_POS);
    for(k=0;k<1000000;k++);
}

void bluetoothForceBaud9600(BOOL enable){
    if(enable)
        PLIB_PORTS_PinSet(PORTS_ID_0, BT_BAUD_9600_PORT_CHANNEL, BT_BAUD_9600_PORT_BIT_POS);
    else
        PLIB_PORTS_PinClear(PORTS_ID_0, BT_BAUD_9600_PORT_CHANNEL, BT_BAUD_9600_PORT_BIT_POS);
}

void APP_BT_Initialize(){
    btRxQueueWriteIndex = 0;
    btRxQueueReadIndex = 0;
    btRxCmdIndex = 0;
    bluetoothReset();
    bluetoothForceBaud9600(false);
    PLIB_PORTS_PinClear(PORTS_ID_0, BT_CTS_BAR_PORT_CHANNEL, BT_CTS_BAR_PORT_BIT_POS);
}

inline BT_CMD getCommand(){
    int c;
    for(c=0;c<BT_CMD_NUM_COMMANDS;c++)
        if(!strncmp(btCmdStrings[c], btRxCmd, 5))
            return (BT_CMD)c;
    return BT_CMD_INVALID;
}

void APP_BT_Tasks(){
    while(btRxQueueReadIndex != btRxQueueWriteIndex){
        btRxCmd[btRxCmdIndex] = btRxQueue[btRxQueueReadIndex];

        //Command has ended
        if(btRxCmd[btRxCmdIndex] == '\n'){
            btRxCmdIndex = 0;
            switch(getCommand()){
                case BT_CMD_PING:
                    bluetoothSend("PONG\n", 5);
                    break;

                case BT_CMD_FRAME_REQUEST:
                    frameRequest = true;
                    break;

                default:
                    break;
            }
        }

        //Command continues
        else
            btRxCmdIndex = (btRxCmdIndex + 1) % BT_RX_QUEUE_SIZE;
        
        btRxQueueReadIndex = (btRxQueueReadIndex + 1) % BT_RX_QUEUE_SIZE;
    }
}

void bluetoothSend(char* c, unsigned int n){
    int k;
    for(k=0;k<n;k++){

        //Wait until transmitter buffer is available
        while(PLIB_USART_TransmitterBufferIsFull(USART_ID_4));

        //Wait until Bluetooth module is available
        while(PLIB_PORTS_PinGet(PORTS_ID_0, BT_RTS_BAR_PORT_CHANNEL, BT_RTS_BAR_PORT_BIT_POS));

        //Send byte
        PLIB_USART_TransmitterByteSend(USART_ID_4, c[k]);
    }
}

void bluetoothSendHex(char* c, unsigned int n){
    int k;
    char high, low;
    for(k=0;k<n;k++){

        //Wait until transmitter buffer is available
        while(PLIB_USART_TransmitterBufferIsFull(USART_ID_4));

        //Wait until Bluetooth module is available
        while(PLIB_PORTS_PinGet(PORTS_ID_0, BT_RTS_BAR_PORT_CHANNEL, BT_RTS_BAR_PORT_BIT_POS));

        //Send high byte
        high = ((unsigned char)c[k])/16 + 48; //0, 1, 2, 3, 4, 5, 6, 7, 8 or 9
        if(high > 57) //A, B, C, D, E or F
            high += 7;
        PLIB_USART_TransmitterByteSend(USART_ID_4, high);

        //Wait until transmitter buffer is available
        while(PLIB_USART_TransmitterBufferIsFull(USART_ID_4));

        //Wait until Bluetooth module is available
        while(PLIB_PORTS_PinGet(PORTS_ID_0, BT_RTS_BAR_PORT_CHANNEL, BT_RTS_BAR_PORT_BIT_POS));

        //Send low byte
        low = ((unsigned char)c[k])%16 + 48; //0, 1, 2, 3, 4, 5, 6, 7, 8 or 9
        if(low > 57) //A, B, C, D, E or F
            low += 7;
        PLIB_USART_TransmitterByteSend(USART_ID_4, low);

        //Wait until transmitter buffer is available
        while(PLIB_USART_TransmitterBufferIsFull(USART_ID_4));

        //Wait until Bluetooth module is available
        while(PLIB_PORTS_PinGet(PORTS_ID_0, BT_RTS_BAR_PORT_CHANNEL, BT_RTS_BAR_PORT_BIT_POS));

        PLIB_USART_TransmitterByteSend(USART_ID_4, '\n');
    }
}

void __ISR(_UART3_RX_VECTOR, ipl1AUTO) _BT_RX_Handler(void){
    btRxQueue[btRxQueueWriteIndex] = U3RXREG;
    btRxQueueWriteIndex = (btRxQueueWriteIndex + 1) % BT_RX_QUEUE_SIZE;
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_3_RECEIVE);
}
