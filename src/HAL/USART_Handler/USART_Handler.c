/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  USART Handler.c
 *          Description:  
 *          Name: Farah Mohey
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "USART_Handler.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
/************************************************************************************
 * Description: extern USART_PostCompileCfg_t USART1_cfg
 ************************************************************************************/
USART_PostCompileCfg_t USART1_cfg={USART_CH1,USART_OVERSAMPLING_16,USART_DATA_BITS_8,USART_PARITY_NONE,USART_STOP_BITS_ONE,9600};

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
 * Service Name: USARTHandler_Init
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  
 * Parameters (out): 
 * Return value: 
 * Description:   
 ************************************************************************************/
void USARTHandler_Init(u8 UART_chanel){
    switch (UART_chanel)
    {
    case USART_CH1:
        /* code */
        RCC_enuEnableDisablePeripheral(RCC_APB2, USART1EN, Periph_enuON);
        RCC_enuEnableDisablePeripheral(RCC_AHB1,GPIOBEN,Periph_enuON);
        NVIC_EnableInterrupt(USART1_IRQn);
        GPIO_PinCfg_t GpioTX={USART1_TxPORT,USART1_TxPIN,AF_PP,High_speed,AF7}; 
        GPIO_PinCfg_t GpioRX={USART1_RxPORT,USART1_RxPIN,AF_PP,High_speed,AF7};
        GPIO_InitPin(&GpioTX);
        GPIO_InitPin(&GpioRX);  
        USART_Init(&USART1_cfg);
        break; 
    default:
        break;
    }

}
/************************************************************************************
 * Service Name: USARTHandler_SendUSART
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  
		   
 * Parameters (out): 
 * Return value: 
 * Description: 
 ************************************************************************************/
void USARTHandler_SendUSART(u8 USART_Num, u8* buffer, u16 len, fnpointer cbf){
    USART_TxBufferAsyncZeroCopy(USART_Num, buffer, len, cbf);
}
/************************************************************************************
 * Service Name: USARTHandler_ReceiveUSART
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  
 * Parameters (out): 
 * Return value: 
 * Description:  
 ************************************************************************************/
void USARTHandler_ReceiveUSART(u8 USART_Num,u8* buffer, u16 len, fnpointer cbf){
    USART_RxBufferAsyncZeroCopy(USART_Num, buffer, len, cbf);
}