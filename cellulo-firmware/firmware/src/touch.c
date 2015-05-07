/**
 * @file touch.c
 * @brief Source for touch input functionality
 * @author Ayberk Özgür
 * @version 1.0
 * @date 2015-05-03
 */

#include"touch.h"

bool keyTouching[6];

void APP_Touch_Initialize(){
    int i;
    for(i=0;i<6;i++)
        keyTouching[i] = false;

    AT42QT1070Init();

    AT42QT1070Reset();

    //Disable AKS to make multitouch possible
    AT42QT1070SetAKS(0,0);
    AT42QT1070SetAKS(1,0);
    AT42QT1070SetAKS(2,0);
    AT42QT1070SetAKS(3,0);
    AT42QT1070SetAKS(4,0);
    AT42QT1070SetAKS(5,0);

    //We don't use key 6
    AT42QT1070DisableKey(6);

    //Set 8ms sampling period
    AT42QT1070SetSamplePeriod(1);
}

unsigned char keyTest[6];
unsigned char ledTest[6];
inline void touchLedTest(){
    unsigned char change = 0;
    int i;
    for(i=0;i<6;i++){
        if(!keyTest[i] && keyTouching[i]){
            ledTest[i] = !ledTest[i];
            change = 1;
        }
        keyTest[i] = keyTouching[i];
    }

    unsigned short red = 0xFFF, green = 0xFFF*2/5, blue = 0;

    if(ledTest[0])
        setLED0(0xFFF, 0, 0);
    else
        setLED0(0x000, 0x000, 0x000);

    if(ledTest[1])
        setLED1(0, 0xFFF, 0);
    else
        setLED1(0x000, 0x000, 0x000);

    if(ledTest[2])
        setLED2(0, 0, 0xFFF);
    else
        setLED2(0x000, 0x000, 0x000);

    if(ledTest[3])
        setLED3(0xFFF, 0xFFF, 0);
    else
        setLED3(0x000, 0x000, 0x000);

    if(ledTest[4])
        setLED4(0xFFF, 0, 0xFFF);
    else
        setLED4(0x000, 0x000, 0x000);

    if(ledTest[5])
        setLED5(0, 0xFFF, 0xFFF);
    else
        setLED5(0x000, 0x000, 0x000);

    if(change)
        sendLEDData();
    change = 0;
}

void APP_Touch_Tasks(){

    //Sample key state
    while(!PLIB_PORTS_PinGet(PORTS_ID_0, TOUCH_CHANGE_BAR_PORT_CHANNEL, TOUCH_CHANGE_BAR_PORT_BIT_POS))
        AT42QT1070GetKeyStates(keyTouching);

    touchLedTest();
}
