/*******************************************************************************
 System Interrupts File

  File Name:
    system_int.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.

  Summary:
    This file contains source code for the interrupt vector functions in the
    system.

  Description:
    This file contains source code for the interrupt vector functions in the
    system.  It implements the system and part specific vector "stub" functions
    from which the individual "Tasks" functions are called for any modules
    executing interrupt-driven in the MPLAB Harmony system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    interrupt-driven in the system.  These handles are passed into the individual
    module "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
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

#include <xc.h>
#include <sys/attribs.h>
#include "app.h"
#include "system_definitions.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Interrupt Vector Functions
// *****************************************************************************
// *****************************************************************************

#include "cam.h"

unsigned int k = 0;

void __ISR(_EXTERNAL_2_VECTOR, IPL7AUTO) _PIXEL_WR_Handler(void){
    pixels[k] = PORTE;
    k++;
    pixels[k] = PORTE;
    k++;
    pixels[k] = PORTE;
    k++;
    pixels[k] = PORTE;
    k++;
    k--;
    k--;
    k--;
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_2);
}

void __ISR(_EXTERNAL_3_VECTOR, IPL7AUTO) _LINE_VALID_Handler(void)
{
    Nop();
    k = 0;
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_3);
}

void __ISR(_EXTERNAL_4_VECTOR, IPL7AUTO) _FRAME_VALID_Handler(void)
{
    Nop();
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_EXTERNAL_4);
}


void __ISR(_SPI1_RX_VECTOR, ipl1AUTO) _IntHandlerSPIRxInstance0(void)
{
    DRV_SPI_Tasks(sysObj.spiObjectIdx0);
}
void __ISR(_SPI1_TX_VECTOR, ipl1AUTO) _IntHandlerSPITxInstance0(void)
{
    DRV_SPI_Tasks(sysObj.spiObjectIdx0);
}
void __ISR(_SPI1_FAULT_VECTOR, ipl1AUTO) _IntHandlerSPIFaultInstance0(void)
{
    DRV_SPI_Tasks(sysObj.spiObjectIdx0);
}
 
void __ISR(_I2C5_MASTER_VECTOR, ipl1AUTO) _IntHandlerDrvI2CMasterInstance0(void)
{

    /* TODO: Add code to process interrupt here */
    /* Clear pending interrupt */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_5_MASTER);

}

void __ISR(_I2C5_BUS_VECTOR, ipl1AUTO) _IntHandlerDrvI2CErrorInstance0(void)
{

    /* TODO: Add code to process interrupt here */
    /* Clear pending interrupt */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_I2C_5_BUS);
}
 
 
 
 
 
 
  
/*******************************************************************************
 End of File
*/

