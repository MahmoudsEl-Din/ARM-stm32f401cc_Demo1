/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  LED.h
 * 			Description:
 *          Name: Mahmoud Shams El-Din
 *********************************************************************************************************************/
#ifndef HAL_LED_LED_H_
#define HAL_LED_LED_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/std_types.h"
#include "LED_cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/************************************************************************************
 * Description: LED Defines
 ************************************************************************************/
#define LED_STATE_ON  0x00000001
#define LED_STATE_OFF 0X00010000
#define LED_CONN_FWD  0x00000000
#define LED_CONN_REV  0x00010001


/************************************************************************************
 * Description: Led configurations
 ************************************************************************************/
typedef struct{
	void* LED_Port;
	u32 LED_Pin;
	u8  LED_Conn;
	u32 LED_Mode;
	u32 LED_Speed;
	}LED_cfg_t;
	
/************************************************************************************
 * Description: Error Status
 ************************************************************************************/
typedef enum
{
	LED_OK,
	LED_InvalidLed,
	LED_InvalidStatus
	}LED_ERRORSTATUS_t;

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
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
LED_ERRORSTATUS_t LED_Init(void);
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
LED_ERRORSTATUS_t LED_SetStatus(u32 Copy_LED, u32 Copy_Status);

#endif // HAL_LED_LED_H_
/**********************************************************************************************************************
 *  END OF FILE: LED.h
 *********************************************************************************************************************/
