/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  GPIO.c
 *          Description:  
 *          Name: Mahmoud Shams El-Din
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "GPIO.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
/************************************************************************************
 * Description: 
 ************************************************************************************/
 
#define MODER_Mask   0b11000
#define OTYPER_Mask  0b00100
#define PUPDR_Mask   0b00011
#define Clear2bits   0x00000003
#define Clear1bit    0x00000001
#define _4_BIT_MASK  0x0000000F
#define PIN_OFFSET_4 0x00000004
#define PIN_ALTERNATIVE_OFFSET 0x00000004

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
 * Service Name: GPIO_InitPin
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  AddPinCfg - Pointer to a structure containing pin configuration:
*                                - GPIO_PORT: Pointer to the GPIO port (GPIO_A/B/C)
*                                - GPIO_PIN: Pin index (GPIO_PIN0 ~ GPIO_PIN15)
*                                - GPIO_MODE: Pin mode:
*                                             - output_PP, output_PP_PU, output_PP_PD,
*                                             - output_OD, output_OD_PU, output_OD_PD,
*                                             - input_floating, input_PU, input_PD,
*                                             - AF_PP, AF_PP_PU, AF_PP_PD,
*                                             - AF_OD, AF_OD_PU, AF_OD_PD,
*                                             - analog
*                                - GPIO_SPEED: Pin speed:
*                                              - Low_speed
*                                              - Medium_speed
*											   - High_speed
*											   - VeryHigh_speed
*                                - GPIO_AF: Pin alternate function (e.g., AF0 ~ AF15)
 * Parameters (out): GPIO_ErrorStatus_t:
*								- GPIO_OK
*								- GPIO_InvalidPort
*								- GPIO_InvalidPin
*								- GPIO_Invalidspeed
*								- GPIO_Invalidmode
*								- GPIO_NULLPTR
 * Return value: 
 * Description: Initializes a GPIO pin according to the provided configuration.
 ************************************************************************************/
GPIO_ErrorStatus_t GPIO_InitPin(GPIO_PinCfg_t* AddPinCfg)
{
	GPIO_ErrorStatus_t GPIO_RetError= GPIO_OK;
	if (AddPinCfg->GPIO_PORT != GPIO_A &&
    AddPinCfg->GPIO_PORT != GPIO_B &&
    AddPinCfg->GPIO_PORT != GPIO_C) {
    GPIO_RetError= GPIO_InvalidPort;
}
  else if(AddPinCfg->GPIO_PIN > GPIO_PIN15)
  {
	 GPIO_RetError= GPIO_InvalidPin;
  }
  else if (AddPinCfg->GPIO_SPEED>VeryHigh_speed)
  {
	   GPIO_RetError= GPIO_Invalidspeed;
  }
  else if(!(AddPinCfg->GPIO_MODE == output_PP ||
  AddPinCfg->GPIO_MODE == output_PP_PU ||
  AddPinCfg->GPIO_MODE == output_PP_PD ||
  AddPinCfg->GPIO_MODE == output_OD ||
  AddPinCfg->GPIO_MODE == output_OD_PU ||
  AddPinCfg->GPIO_MODE == output_OD_PD ||
  AddPinCfg->GPIO_MODE == input_floating ||
  AddPinCfg->GPIO_MODE == input_PU ||
  AddPinCfg->GPIO_MODE == input_PD ||
  AddPinCfg->GPIO_MODE == AF_PP ||
  AddPinCfg->GPIO_MODE == AF_PP_PU ||
  AddPinCfg->GPIO_MODE == AF_PP_PD ||
  AddPinCfg->GPIO_MODE == AF_OD ||
  AddPinCfg->GPIO_MODE == AF_OD_PU ||
  AddPinCfg->GPIO_MODE == AF_OD_PD ||
  AddPinCfg->GPIO_MODE == analog)) {
	  GPIO_RetError= GPIO_Invalidmode;
  }
  else if (AddPinCfg==NULLPTR)
  {
	   GPIO_RetError= GPIO_NULLPTR;
  }

 else
 {
	u32 LocTempRegister;
	/* set the mode */
	LocTempRegister=((GPIO_t*)(AddPinCfg->GPIO_PORT))->MODER;
	LocTempRegister&=~(Clear2bits<<(AddPinCfg->GPIO_PIN*2));
	LocTempRegister|=(((AddPinCfg->GPIO_MODE&MODER_Mask)>>3)<<(AddPinCfg->GPIO_PIN*2));
	((GPIO_t*)(AddPinCfg->GPIO_PORT))->MODER=LocTempRegister;
	
	/* set the output type */
	LocTempRegister=((GPIO_t*)(AddPinCfg->GPIO_PORT))->OTYPER;
	LocTempRegister&=~(Clear1bit<<(AddPinCfg->GPIO_PIN));
	LocTempRegister|=(((AddPinCfg->GPIO_MODE&OTYPER_Mask)>>2)<<(AddPinCfg->GPIO_PIN));
	((GPIO_t*)(AddPinCfg->GPIO_PORT))->OTYPER=LocTempRegister;
	
	/* set the PUPDR */
	LocTempRegister=((GPIO_t*)(AddPinCfg->GPIO_PORT))->PUPDR;
	LocTempRegister&=~(Clear2bits<<(AddPinCfg->GPIO_PIN*2));
	LocTempRegister|=((AddPinCfg->GPIO_MODE&PUPDR_Mask)<<(AddPinCfg->GPIO_PIN*2));
	((GPIO_t*)(AddPinCfg->GPIO_PORT))->PUPDR=LocTempRegister;
	
	/* set the speed */
	LocTempRegister=((GPIO_t*)(AddPinCfg->GPIO_PORT))->OSPEEDR;
	LocTempRegister&=~(Clear2bits<<(AddPinCfg->GPIO_PIN*2));
	LocTempRegister|=(AddPinCfg->GPIO_SPEED <<(AddPinCfg->GPIO_PIN*2));
	((GPIO_t*)(AddPinCfg->GPIO_PORT))->OSPEEDR=LocTempRegister;

	/* Set the AF */
	LocTempRegister=((GPIO_t*)(AddPinCfg->GPIO_PORT))->AFR;
	LocTempRegister&= ~( ((u64)_4_BIT_MASK) << (AddPinCfg->GPIO_PIN*PIN_OFFSET_4) );
	LocTempRegister|=(((u64)AddPinCfg->GPIO_AF) << (AddPinCfg->GPIO_PIN*PIN_OFFSET_4) );
	((GPIO_t*)(AddPinCfg->GPIO_PORT))->AFR = LocTempRegister;
			/* AF */
		/*if(AddPinCfg->GPIO_PIN <= GPIO_PIN7){
			((GPIO_t*)(AddPinCfg->GPIO_PORT))->AFRL |= AddPinCfg->GPIO_AF << (PIN_ALTERNATIVE_OFFSET * (AddPinCfg->GPIO_PIN%8));
		}
		else{
			((GPIO_t*)(AddPinCfg->GPIO_PORT))->AFRH |= AddPinCfg->GPIO_AF << (PIN_ALTERNATIVE_OFFSET * (AddPinCfg->GPIO_PIN%8));
		}*/


 }
	return GPIO_RetError;
}

 /************************************************************************************
 * Service Name: GPIO_SetPinValue
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  Copy_Port - Pointer to the GPIO port (GPIO_A/B/C)                
*                  Copy_Pin  - Pin index (GPIO_PIN0 ~ GPIO_PIN15)                        
*                  Copy_Value - Value to be set for the pin (GPIO_HIGH or GPIO_LOW)
 * Parameters (out): GPIO_ErrorStatus_t:
*								- GPIO_OK
*								- GPIO_InvalidPort
*								- GPIO_InvalidPin
*								- GPIO_Invalidvalue
*								- GPIO_NULLPTR       
 * Return value: 
 * Description: Sets the value of a specific pin on a GPIO port to(GPIO_HIGH or GPIO_LOW)
 ************************************************************************************/
GPIO_ErrorStatus_t GPIO_SetPinValue(void* Copy_Port,u32 Copy_Pin,u32 Copy_Value)
{
	GPIO_ErrorStatus_t GPIO_RetError= GPIO_OK;
    if( Copy_Pin > GPIO_PIN15)
	{
		GPIO_RetError= GPIO_InvalidPin;
	}
	else if (!(Copy_Value==GPIO_LOW || Copy_Value==GPIO_HIGH))
	{
		GPIO_RetError= GPIO_Invalidvalue;
	}
	else if (Copy_Port==NULLPTR)
	{
		GPIO_RetError=GPIO_NULLPTR;
	}
	else
	{
		((GPIO_t*)Copy_Port)->BSRR =Copy_Value<<Copy_Pin;
	}
	return GPIO_RetError;
}
 /************************************************************************************
 * Service Name: GPIO_GetPinValue
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentran
 * Parameters (in):  Copy_Port - Pointer to the GPIO port (GPIO_A/B/C)               
*                  Copy_Pin  - Pin index (GPIO_PIN0 ~ GPIO_PIN15)                        
*                  Add_Value - Pointer to where the pin value will be stored
 * Parameters (out): GPIO_ErrorStatus_t:													 
*								- GPIO_OK                                                
*								- GPIO_InvalidPort
*								- GPIO_InvalidPin
*								- GPIO_NULLPTR         
 * Return value: 
 * Description: Reads the value of a specific pin on a GPIO port.
 ************************************************************************************/
GPIO_ErrorStatus_t GPIO_GetPinValue(void* Copy_Port,u32 Copy_Pin,u8* Add_Value)
{
	GPIO_ErrorStatus_t GPIO_RetError= GPIO_OK;
	if( Copy_Pin > GPIO_PIN15)
	{
		GPIO_RetError= GPIO_InvalidPin;
	}
	else if (Copy_Port==NULLPTR || Add_Value==NULLPTR )
	{
		GPIO_RetError=GPIO_NULLPTR;
	}
	else
	{
	*Add_Value = (((GPIO_t*)Copy_Port)->IDR >> Copy_Pin)&0x01;
	}
	
	return GPIO_RetError;
}

/**********************************************************************************************************************
 *  END OF FILE: GPIO.c
 *********************************************************************************************************************/
