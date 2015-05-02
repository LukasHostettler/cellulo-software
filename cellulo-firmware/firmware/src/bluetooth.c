/**
 * @file bluetooth.c
 * @brief Source for bluetooth functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-05-02
 */

#include "bluetooth.h"

char btRxQueue[BT_RX_QUEUE_SIZE];
unsigned int btRxQueueReadIndex;
unsigned int btRxQueueWriteIndex;

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
    btRxQueueReadIndex = 0;
    btRxQueueWriteIndex = 0;
    bluetoothReset();
    bluetoothForceBaud9600(false);
}

void APP_BT_Tasks(){
    while(btRxQueueReadIndex != btRxQueueWriteIndex){
        
        //TODO: PROCESS INCOMING COMMANDS HERE
        if(btRxQueue[btRxQueueReadIndex] == 'q')
            bluetoothSend("OK", 2);
        
        btRxQueueReadIndex = (btRxQueueReadIndex + 1) % BT_RX_QUEUE_SIZE;
    }
}

void bluetoothSend(char* c, unsigned int n){
    int i;
    for(i=0;i<n;i++){
        while(PLIB_USART_TransmitterBufferIsFull(USART_ID_4));
        PLIB_USART_TransmitterByteSend(USART_ID_4, c[i]);
    }
}
