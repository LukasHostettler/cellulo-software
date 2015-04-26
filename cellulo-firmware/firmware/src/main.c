/*******************************************************************************
  MPLAB Harmony Project Main Source File

  Company:
    Microchip Technology Inc.
  
  File Name:
    main.c

  Summary:
    This file contains the "main" function for an MPLAB Harmony project.

  Description:
    This file contains the "main" function for an MPLAB Harmony project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state 
    machines of all MPLAB Harmony modules in the system and it calls the 
    "SYS_Tasks" function from within a system-wide "super" loop to maintain 
    their correct operation. These two functions are implemented in 
    configuration-specific files (usually "system_init.c" and "system_tasks.c")
    in a configuration-specific folder under the "src/system_config" folder 
    within this project's top-level folder.  An MPLAB Harmony project may have
    more than one configuration, each contained within it's own folder under
    the "system_config" folder.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

//Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "system/common/sys_module.h"
#include "driver/spi/drv_spi.h"   // SYS function prototypes

#include "led.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

DRV_SPI_BUFFER_HANDLE bufHandle;
DRV_HANDLE spiHandle;

unsigned char complete = 1;

/*void APP_MyBufferEventHandler( DRV_SPI_BUFFER_EVENT event,
                               DRV_SPI_BUFFER_HANDLE bufferHandle,
                               uintptr_t context )
{
    int i;
    switch(event)
    {
        case DRV_SPI_BUFFER_EVENT_COMPLETE:
            
            for(i=0;i<10;i++)
                Nop();
            PORTCbits.RC14 = 1;
            for(i=0;i<10;i++)
                Nop();
            PORTCbits.RC14 = 0;
            complete = 1;
            break;

        case DRV_SPI_BUFFER_EVENT_ERROR:
        default:

            Nop();
            break;
    }
}*/


int main ( void )
{
    /* Initialize all MPLAB Harmony modules, including application(s). */
    SYS_Initialize ( NULL );

    spiHandle = DRV_SPI_Open(DRV_SPI_INDEX_0, DRV_IO_INTENT_WRITE);
    if(spiHandle == DRV_HANDLE_INVALID){
        Nop();
    }

    setLED0(500,0,0);
    setLED1(500,0,0);
    setLED2(500,0,0);
    setLED3(500,0,0);
    setLED4(500,0,0);
    setLED5(500,0,0);
    //leds.leds.led5green = 0xFFF;
    //leds.leds.led5red = 0xFFF;
    //leds.leds.led5green = 0xFFF;


    bufHandle = DRV_SPI_BufferAddWrite(spiHandle, (void*)&leds.buffer, 4*7, NULL, NULL);//(DRV_SPI_BUFFER_EVENT_HANDLER)APP_MyBufferEventHandler, NULL);
    if(bufHandle == DRV_SPI_BUFFER_HANDLE_INVALID){
        Nop();
    }

    while ( true )
    {

        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );

        int i;
        for(i=0;i<10000000;i++)
            Nop();
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

