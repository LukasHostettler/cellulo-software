/**
 * @file bluetooth.c
 * @brief Source for bluetooth functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-05-02
 */

#include "bluetooth.h"

void resetBluetooth(){
    int k;
    PLIB_PORTS_PinClear(PORTS_ID_0, BT_RESET_BAR_PORT_CHANNEL, BT_RESET_BAR_PORT_BIT_POS);
    for(k=0;k<1000000;k++);
    PLIB_PORTS_PinSet(PORTS_ID_0, BT_RESET_BAR_PORT_CHANNEL, BT_RESET_BAR_PORT_BIT_POS);
    for(k=0;k<1000000;k++);
}

void forceBluetoothBaud9600(BOOL enable){
    if(enable)
        PLIB_PORTS_PinSet(PORTS_ID_0, BT_BAUD_9600_PORT_CHANNEL, BT_BAUD_9600_PORT_BIT_POS);
    else
        PLIB_PORTS_PinClear(PORTS_ID_0, BT_BAUD_9600_PORT_CHANNEL, BT_BAUD_9600_PORT_BIT_POS);
}
