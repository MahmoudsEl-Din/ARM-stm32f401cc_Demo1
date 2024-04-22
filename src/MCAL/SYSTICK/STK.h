/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  STK.h
 *         Name: Mahmoud Shams El-Din 
 *********************************************************************************************************************/
#ifndef STK_H_
#define STK_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/std_types.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/************************************************************************************
 * Description: Systick mode
 ************************************************************************************/
#define STK_OneTime  1
#define STK_Periodic 2

typedef void (*STK_cbf_t) (void);

typedef enum{
	STK_OK,
	STK_NOK
}STK_ErrorStatus_t;


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
 * Service Name: STK_Init
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): Error status (Report Error if user configured invalid clock source.) 
 * Return value: 
 * Description: Initializes the SysTick timer. (Set clock source & interrupt state)
 ************************************************************************************/
STK_ErrorStatus_t STK_Init(void);

 /************************************************************************************
 * Service Name: STK_Start
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  STK_Mode, Can be: 
 *            - STK_OneTime
 *            - STK_Periodic 
 * Parameters (out): None     
 * Return value: 
 * Description: Enables the SysTick timer.
 ************************************************************************************/
void STK_Start(u8 STK_Mode);

 /************************************************************************************
 * Service Name: STK_Stop
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentran
 * Parameters (in):  None
 * Parameters (out): None         
 * Return value: 
 * Description: Disables the SysTick timer.
 ************************************************************************************/
void STK_Stop(void);

 /************************************************************************************
 * Service Name: STK_SetTime_ms
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentran
 * Parameters (in):  CopyTime_ms: The time interval in milliseconds.
 * Parameters (out): NoError status (Report Error if the load value exceeds the register limit).ne         
 * Return value: 
 * Description: Sets the time for systick timer in milliseconds.
 ************************************************************************************/
STK_ErrorStatus_t STK_SetTime_ms(u32 CopyTime_ms);

  /************************************************************************************
 * Service Name: STK_IsExpired
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentran
 * Parameters (in):  None
 * Parameters (out): Error Status.         
 * Return value: 
 * Description: Checks if the SysTick interrupt has expired.
 ************************************************************************************/
STK_ErrorStatus_t STK_IsExpired(void);

  /************************************************************************************
 * Service Name: STK_RegisterCallback
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentran
 * Parameters (in):  cbf: Callback function pointer.
 * Parameters (out): Error status (Report error if null pointer).          
 * Return value: 
 * Description: Registers a callback function to be called upon SysTick interrupt.
 ************************************************************************************/
STK_ErrorStatus_t STK_RegisterCallback(STK_cbf_t cbf);

 
#endif  /* STK_H_ */

/**********************************************************************************************************************
 *  END OF FILE: STK.h
 *********************************************************************************************************************/
