/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SWITCH.c
 *          Description:  
 *          Name: Mahmoud Shams El-Din
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/

#include "SWITCH.h"
#include "MCAL/GPIO/GPIO.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
extern const SWITCH_cfg_t SWITCHS[_SWITCH_NUM];
static u8 SwitchState[_SWITCH_NUM];
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
 * Service Name: SWITCH_Init
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): SWITCH_ERRORSTATUS_t :
 *         - SWITCH_OK
 *         - GPIO_ERRORStatus
 * Return value: 
 * Description: Initializes the SWITCH according to external SWITCH configuration.
 ************************************************************************************/
 SWITCH_ERRORSTATUS_t SWITCH_Init(void)
{
	SWITCH_ERRORSTATUS_t RetSwitchError=SWITCH_OK;
	GPIO_PinCfg_t Loc_SWITCH;
	u32 Idx=0;
	for(Idx=0;Idx<_SWITCH_NUM;Idx++)
	{
		Loc_SWITCH.GPIO_PORT=SWITCHS[Idx].SWITCH_Port;
		Loc_SWITCH.GPIO_PIN=SWITCHS[Idx].SWITCH_Pin;
		Loc_SWITCH.GPIO_MODE=SWITCHS[Idx].SWITCH_Mode;
		if(SWITCHS[Idx].SWITCH_Mode==SWITCH_INPUT_PU)
		{
			Loc_SWITCH.GPIO_MODE=input_PU;
		}
		else
		{
			Loc_SWITCH.GPIO_MODE=input_PD;
		}

		RetSwitchError=GPIO_InitPin(&Loc_SWITCH);
	}
	return RetSwitchError;
}
/************************************************************************************
 * Service Name: SWITCH_GetStatus
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  - Copy_SWITCH: The name of the SWITCH whose status will be set.
 *         - Copy_Status: The status of the SWITCH (SWITCH_PRESSED, SWITCH_NOT_PRESSED).
 * Parameters (out): SWITCH_ERRORSTATUS_t:
 *         - SWITCH_OK
 *         - SWITCH_InvalidSwitch
 *         - SWITCH_NULLPTR
 *         - GPIO_ERRORStatus
 * Return value: 
 * Description: Sets the status of the specified SWITCH.
 ************************************************************************************/
SWITCH_ERRORSTATUS_t SWITCH_GetStatus(u32 Copy_SWITCH, u8* Copy_Status)
{
	
	SWITCH_ERRORSTATUS_t RetSwitchError=SWITCH_OK;
	u8 Input_value;
	if(Copy_SWITCH>_SWITCH_NUM)
	{
		RetSwitchError=SWITCH_InvalidSwitch;
	}
	else if(Copy_Status==NULLPTR)
	{
		RetSwitchError=SWITCH_NULLPTR;
	}
	else
	{

		RetSwitchError=GPIO_GetPinValue(SWITCHS[Copy_SWITCH].SWITCH_Port,SWITCHS[Copy_SWITCH].SWITCH_Pin,&Input_value);
		*Copy_Status=Input_value^SWITCHS[Copy_SWITCH].SWITCH_Mode;
	}
	return RetSwitchError;
	  /* SWITCH_ERRORSTATUS_t RetSwitchError=SWITCH_OK;
	   if(Copy_SWITCH>_SWITCH_NUM)
		{
			RetSwitchError=SWITCH_InvalidSwitch;
		}
		else if(Copy_Status==NULLPTR)
		{
			RetSwitchError=SWITCH_NULLPTR;
		}
		else
		{
			*Copy_Status=SwitchState[Copy_SWITCH]^SWITCHS[Copy_SWITCH].SWITCH_Mode;;
		}
	return RetSwitchError;*/
}
/************************************************************************************
 * Service Name: SWITCH_Runnable
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): None
 * Return value: 
 * Description: Runnable task with periodicity =5 ms
 ************************************************************************************/
 void SWITCH_Runnable(void)
{
	/* handle debouncing */
	u8 Current_SWValue;
	static u8 Prev_SWValue[_SWITCH_NUM];
	static u8 Loc_counter[_SWITCH_NUM];
	for(u8 idx=0;idx<_SWITCH_NUM;idx++)
	{
		GPIO_GetPinValue(SWITCHS[idx].SWITCH_Port,SWITCHS[idx].SWITCH_Pin,&Current_SWValue);
		if(Current_SWValue==Prev_SWValue[idx])
		{
			Loc_counter[idx]++;
		}
		else
		{
			Loc_counter[idx]=0;
		}
		if(Loc_counter[idx]==5)
		{
			SwitchState[idx]=Current_SWValue;
			Loc_counter[idx]=0;
		}
		Prev_SWValue[idx]=Current_SWValue;
	}
}
