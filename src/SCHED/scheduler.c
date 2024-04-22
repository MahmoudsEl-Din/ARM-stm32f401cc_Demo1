/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  main.c
 *          Description:  
 *          Name: Mahmoud Shams El-Din
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "scheduler.h"
#include "Runnables_List.h"
#include "MCAL/SYSTICK/STK.h"



/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	

#define SCHED_TICK_TIME_ms 1U
static void scheduler_tickcb(void);
static void scheduler(void);


/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
// variable to determine if we should call scheduler
static volatile u32 pendingTicks=0;
extern const runnable_t RunnablesList[_Runnables_NUM];
static u32 RemainTime_ms[_Runnables_NUM]={0};

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
 * Service Name: scheduler_tickcb
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): None
 * Return value: 
 * Description:
 ************************************************************************************/
static void scheduler_tickcb(void)
{
	pendingTicks++;
}

static void scheduler(void)
{
	u32 Runnable_Idx=0;
	for(Runnable_Idx = 0; Runnable_Idx < _Runnables_NUM; Runnable_Idx++)
	{
		if(RunnablesList[Runnable_Idx].cb && (RemainTime_ms[Runnable_Idx]==0))
		{
			RunnablesList[Runnable_Idx].cb();
			RemainTime_ms[Runnable_Idx]=RunnablesList[Runnable_Idx].periodicity_ms;
		}
		else
		{

		}
		RemainTime_ms[Runnable_Idx]-=SCHED_TICK_TIME_ms;
	}
	
}
/************************************************************************************
 * Service Name: scheduler_init
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): None
 * Return value: 
 * Description:
 ************************************************************************************/
void scheduler_init(void)
{
	// init vars (if needed)
	STK_Init();
	// systick configure
	STK_SetTime_ms(SCHED_TICK_TIME_ms);
	STK_RegisterCallback(scheduler_tickcb);
    for(u32 Runnable_Idx=0;Runnable_Idx<_Runnables_NUM;Runnable_Idx++)
    {
        RemainTime_ms[Runnable_Idx]=RunnablesList[Runnable_Idx].FirstDelay_ms;
    }
}
/************************************************************************************
 * Service Name: scheduler_start
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): None
 * Return value: 
 * Description:
 ************************************************************************************/
void scheduler_start(void)
{
	// start systick timer
	STK_Start(STK_Periodic);
	while(1)
	{

		if(pendingTicks)
		{
			pendingTicks--;
			scheduler();
		}
	}
}

