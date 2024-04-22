/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  SWITCH_cfg.c
 *          Description:  
 *          Name: Mahmoud Shams El-Din
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "MCAL/GPIO/GPIO.h"
#include "SWITCH.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/************************************************************************************
 * Description: SWITCHS user configuration
 ************************************************************************************/
const SWITCH_cfg_t SWITCHS[_SWITCH_NUM]={
	[SWITCH_OK_MODE]={.SWITCH_Port=GPIO_A, .SWITCH_Pin=GPIO_PIN3,  .SWITCH_Mode=SWITCH_INPUT_PU},
	[SWITCH_UP]={.SWITCH_Port=GPIO_A, .SWITCH_Pin=GPIO_PIN4,  .SWITCH_Mode=SWITCH_INPUT_PU},
	[SWITCH_EDIT]={.SWITCH_Port=GPIO_A, .SWITCH_Pin=GPIO_PIN5,  .SWITCH_Mode=SWITCH_INPUT_PU},
	[SWITCH_RIGHT_START_STOP_STOPWATCH]={.SWITCH_Port=GPIO_A, .SWITCH_Pin=GPIO_PIN6,  .SWITCH_Mode=SWITCH_INPUT_PU},
	[SWITCH_LEFT_RESET_STOPWATCH]={.SWITCH_Port=GPIO_A, .SWITCH_Pin=GPIO_PIN7,  .SWITCH_Mode=SWITCH_INPUT_PU},
	[SWITCH_DOWN_PAUSE_CONTINUE_STOPWATCH]={.SWITCH_Port=GPIO_A, .SWITCH_Pin=GPIO_PIN8,  .SWITCH_Mode=SWITCH_INPUT_PU},
};

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


/**********************************************************************************************************************
 *  END OF FILE: SWITCH_cfg.c
 *********************************************************************************************************************/