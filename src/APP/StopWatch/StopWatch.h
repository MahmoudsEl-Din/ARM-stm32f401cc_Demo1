
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  STOPWATCH.h
 *         Name: Farah Mohey
 *********************************************************************************************************************/
#ifndef STOPWATCH_H_
#define STOPWATCH_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "LIB/std_types.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/************************************************************************************
 * Description: 
 ************************************************************************************/
typedef struct {
    u8 millisec;
    u8 sec;
    u8 min;
    u8 hour;
}StopWatch_value_t;

typedef enum{
    StopWatch_OK,
    StopWatch_TimeExceeded
}StopWatch_ErrorState_t;


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
 * Service Name: StopWatch_Reset
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): StopWatch_ErrorState_t
 * Return value: 
 * Description: to reset stop watch and start from 00:00:00
 ************************************************************************************/
StopWatch_ErrorState_t StopWatch_Reset(void);

/************************************************************************************
 * Service Name: StopWatch_Count
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  StopWatch_values : to stopwatch struct that have time values
 * Parameters (out): StopWatch_ErrorState_t
 * Return value: 
 * Description: to count every 100msec
 ************************************************************************************/
StopWatch_ErrorState_t StopWatch_Count(StopWatch_value_t* StopWatch_values);

/************************************************************************************
 * Service Name: StopWatch_Display
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): None
 * Return value: 
 * Description: 
 ************************************************************************************/
void StopWatch_Display(void);

#endif  /* STOPWATCH_H_*/

/**********************************************************************************************************************
 *  END OF FILE: STOPWATCH.h
 *********************************************************************************************************************/