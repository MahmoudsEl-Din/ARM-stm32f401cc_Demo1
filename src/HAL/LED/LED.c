/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  LED.c
 *          Description:  
 *          Name: Mahmoud Shams El-Din
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "LED.h"
#include "MCAL/GPIO/GPIO.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
/************************************************************************************
 * Description: LED
 ************************************************************************************/
extern const LED_cfg_t LEDS[_LED_NUM];
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/************************************************************************************
 * Service Name: LED_Init
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  void
 * Parameters (out): LED_ERRORSTATUS_t :
 *         - LED_OK
 *         - GPIO_ERRORStatus
 * Return value: 
 * Description:   Initializes the LED according to external LED configuration.
 ************************************************************************************/
LED_ERRORSTATUS_t LED_Init(void)
{
	LED_ERRORSTATUS_t RetLedError=LED_OK;
	GPIO_PinCfg_t Loc_LED;
	u32 Idx=0;
	for(Idx=0;Idx<_LED_NUM;Idx++)
	{
		Loc_LED.GPIO_PORT=LEDS[Idx].LED_Port;
		Loc_LED.GPIO_PIN=LEDS[Idx].LED_Pin;
		Loc_LED.GPIO_MODE=LEDS[Idx].LED_Mode;
		Loc_LED.GPIO_SPEED=LEDS[Idx].LED_Speed;
		RetLedError=GPIO_InitPin(&Loc_LED);
	}
	return RetLedError;
}
/************************************************************************************
 * Service Name: LED_SetStatus
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  Copy_LED: The name of the LED whose status will be set.
 *         - Copy_Status: The status to set for the LED (LED_STATE_ON or LED_STATE_OFF).
 * Parameters (out):  LED_ERRORSTATUS_t:
 *         - LED_OK
 *         - LED_InvalidLed
 *         - LED_InvalidStatus
 * Return value: 
 * Description:   
 ************************************************************************************/
LED_ERRORSTATUS_t LED_SetStatus(u32 Copy_LED, u32 Copy_Status)
{
	LED_ERRORSTATUS_t RetLedError=LED_OK;
	if(Copy_LED>_LED_NUM)
	{
		RetLedError=LED_InvalidLed;
	}
	else if(Copy_Status !=LED_STATE_ON && Copy_Status!=LED_STATE_OFF)
	{
		RetLedError=LED_InvalidStatus;
	}
	else
	{
		RetLedError=GPIO_SetPinValue(LEDS[Copy_LED].LED_Port,LEDS[Copy_LED].LED_Pin,LEDS[Copy_LED].LED_Conn^Copy_Status);
	}
	return RetLedError;
}
/**********************************************************************************************************************
 *  END OF FILE: led.c
 *********************************************************************************************************************/
