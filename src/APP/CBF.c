/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  CBF.c
 *          Description:  
 *          Name: Mahmoud Shams El-Din
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "MCAL/RCC/RCC.h"
#include "MCAL/GPIO/GPIO.h"
#include "MCAL/NVIC/NVIC.h"
#include "MCAL/NVIC/stm32f401cc.h"
#include "MCAL/USART/USART.h"
#include "HAL/LED/LED.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
u8 buffer[3]={0};
u8 buffer2[3]={'y','e','s'};
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/************************************************************************************
 * Service Name: CBF
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): None
 * Return value: 
 * Description: test call back
 ***********************************************************************************/
void CBF(void)
{
    if(buffer[0]=='y'&&buffer[1]=='e'&&buffer[2]=='s')
    {
         USART_TxBufferAsyncZeroCopy(USART_CH1,buffer,3,NULLPTR);
    }
}


/**********************************************************************************************************************
 *  END OF FILE: main.c
 *********************************************************************************************************************/