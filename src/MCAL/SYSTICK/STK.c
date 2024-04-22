/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  STK.c
 *          Description:  
 *          Name: Mahmoud Shams El-Din
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "STK.h"
#include "STK_cfg.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
/************************************************************************************
 * Description: 
 ************************************************************************************/
#define Enable_Mask 0x00000001
#define Max_ReloadValue 0x00ffffff

/************************************************************************************
 * Description: SYSTICK Base Address
 ************************************************************************************/
#define STK_BASEADDRESS (0xE000E010UL)
/************************************************************************************
 * Description: the base address as pointer to the SYSTICK registers
 ************************************************************************************/
#define STK ((void* )STK_BASEADDRESS)

/************************************************************************************
 * Description: Static Pointer systickcbf_t type, Points to APP_cbf
 ************************************************************************************/
static STK_cbf_t APP_cbf=NULLPTR;

static u8 STK_global_Mode=STK_OneTime;

/************************************************************************************
 * Description: SYSTICK Registers definitions
 ************************************************************************************/
typedef struct
{
	volatile u32 CTRL;
    volatile u32 LOAD;
    volatile u32 VAL;
    volatile u32 CALIB;
 }STK_RegisterOffset_t;

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
 * Service Name: STK_Init
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): Error status (Report Error if user configured invalid clock source.) 
 * Return value: 
 * Description: Initializes the SysTick timer. (Set clock source & interrupt state)
 ************************************************************************************/
 STK_ErrorStatus_t  STK_Init(void)
 {
	 STK_ErrorStatus_t STK_RetErrorStatus = STK_OK;
	 if(!((STK_CLKSOURCE==AHB_div_8)||(STK_CLKSOURCE==Proc_clk_AHB)))
	 {
		 STK_RetErrorStatus = STK_NOK;
	 }
	 else
	 {
		 /* Set Clock Source */
		 ((STK_RegisterOffset_t*)(STK))->CTRL|=STK_CLKSOURCE;
		 /* Set Interrupt mode */
		 ((STK_RegisterOffset_t*)(STK))->CTRL|=STK_TICKINT;
	 }

	 return STK_RetErrorStatus;
 }
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
 void STK_Start(u8 STK_Mode)
 {
	 /* Set The timer mode */
	 STK_global_Mode=STK_Mode;

	 /* clear the current timer value */
	 ((STK_RegisterOffset_t*)(STK))->VAL = 1U;

    /* enable counter*/
    ((STK_RegisterOffset_t*)(STK))->CTRL|=Enable_Mask;
 }

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
 void STK_Stop(void)
 {
    /* disable counter*/
	((STK_RegisterOffset_t*)(STK))->CTRL&=~(Enable_Mask);

 }
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
 STK_ErrorStatus_t STK_SetTime_ms(u32 CopyTime_ms)
 {
     STK_ErrorStatus_t STK_RetErrorStatus = STK_OK;

     /* Determine the STK clock source frequency based on the selected clock source */
     u32 STK_CLKSRC_FREQ = (STK_CLKSOURCE == Proc_clk_AHB) ? STK_AHB_FREQ : (STK_AHB_FREQ / 8);

    /* Set reload value in STK_LOAD Register */
    u32 Reload_Value = ((CopyTime_ms * STK_CLKSRC_FREQ) / 1000) - 1;

    if(Reload_Value>Max_ReloadValue)
    {
    	STK_RetErrorStatus=STK_NOK;
    }
    else
    {
    	((STK_RegisterOffset_t*)STK)->LOAD=Reload_Value;
    }
     return STK_RetErrorStatus;
 }


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
 STK_ErrorStatus_t STK_RegisterCallback(STK_cbf_t cbf)
 {
     STK_ErrorStatus_t STK_RetErrorStatus = STK_OK;
     if(cbf)
     {
    	 APP_cbf=cbf;
     }
     else
     {
    	 STK_RetErrorStatus=STK_NOK;
     }

     return STK_RetErrorStatus;
 }

/************************************************************************************
 * Service Name: SysTick_Handler
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentran
 * Parameters (in):  None
 * Parameters (out): None        
 * Return value: 
 * Description: Handler
 ************************************************************************************/
 void SysTick_Handler(void)
 {
	 if(APP_cbf)
	 {
		 APP_cbf();
		 if(STK_global_Mode==STK_OneTime)
		 {

			 STK_Stop();
		 }
		 else
		 {
			/* do nothing*/
		 }
	 }
	 else
	 {
		 /*do nothing*/
	 }
 }
