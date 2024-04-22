/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  USART.h
 *         Name: Mahmoud Shams El-Din 
 *********************************************************************************************************************/
#ifndef MCAL_USART_USART_H_
#define MCAL_USART_USART_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/std_types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/************************************************************************************
 * Description: UART 
 ************************************************************************************/
#define F_USART1  16000000
#define F_USART2  16000000
#define F_USART6  16000000
/************************************************************************************
 * Description: UART Channel Options 
 ************************************************************************************/
#define USART_CH1         (0U)
#define USART_CH2         (1U)
#define USART_CH6         (2U)

/************************************************************************************
 * Description: UART Channel Oversampling Options      
 ************************************************************************************/
#define USART_OVERSAMPLING_16                0x00000000
#define USART_OVERSAMPLING_8                 0x00008000


/************************************************************************************
 * Description:UART Channel Data Bits Options
 ************************************************************************************/
#define USART_DATA_BITS_8                    0x00000000
#define USART_DATA_BITS_9                    0x00001000

/************************************************************************************
 * Description: UART Channel Parity Bits Options  
 ************************************************************************************/
#define USART_PARITY_NONE                    0x00000000  
#define USART_PARITY_ODD                     0x00000200
#define USART_PARITY_EVEN                    0x00000000


/************************************************************************************
 * Description: UART Stop Bits Options
 ************************************************************************************/
#define USART_STOP_BITS_HALF                 0x00001000
#define USART_STOP_BITS_ONE                  0x00000000
#define USART_STOP_BITS_ONE_AND_HALF         0x00003000
#define USART_STOP_BITS_TWO                  0x00002000

/************************************************************************************
 * Description: "fnpointer" type: pointer to function that takes void and returns void
 ************************************************************************************/
typedef void (*fnpointer)(void);

/************************************************************************************
 * Description: Struct for Storing UART Post Compile Initilization Info
 ************************************************************************************/
typedef struct
{
    u8 Channel;             /**
                             * 1) USART_CH1    
                             * 2) USART_CH2   
                             * 3) USART_CH6  
                             */

    u8 OverSampling;        /**
                             * 1) USART_OVERSAMPLING_16
                             * 2) USART_OVERSAMPLING_8
                             */
    
    u8 WordLength;          /**
                             * 1) USART_DATA_BITS_8
                             * 2) USART_DATA_BITS_9
                             */
    
    u8 ParitySelect;        /**
                             * 1) USART_PARITY_NONE
                             * 2) USART_PARITY_ODD
                             * 3) USART_PARITY_EVEN
                             */

    u8 StopBits;            /**
                             * 1) USART_STOP_BITS_HALF
                             * 2) USART_STOP_BITS_ONE
                             * 3) USART_STOP_BITS_ONE_AND_HALF
                             * 4) USART_STOP_BITS_TWO
                             */

    f32 BaudRate;           /**
                             * @note Baud Rate Number Shouldn't Exceed:
                             *      1) F_UART/8 for Oversampling=8
                             *      2) F_UART/16 for Oversampling=16
                            */
}USART_PostCompileCfg_t;

/************************************************************************************
 * Description: UART Error Status Type
 ************************************************************************************/
typedef enum
{
    USART_Ok,
    USART_NullPtr,
    USART_Nok
}USART_ErrorStatus_t;

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
 * Service Name: USART_Init
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  cfg: Pointer to Struct that stores configuration for a UART channel
 * Parameters (out):  Error Status 
 * Return value: 
 * Description:  Initializes a single USART peripheral 
 ************************************************************************************/
USART_ErrorStatus_t USART_Init(USART_PostCompileCfg_t* cfg);


/************************************************************************************
 * Service Name: USART_TxBufferAsyncZeroCopy
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):   1) USART_Num:
 *                     1) USART_CH1    
 *                     2) USART_CH2   
 *                     3) USART_CH6  
 * 
 *          - 2) buffer: Pointer to a character/string to transmit asynchronously via USART
 * 
 *          - 3) len: Length of buffer
 * 
 *          - 4) cbf: Callback Function to call after transmission of buffer
 * Parameters (out): Error Status
 * Return value: 
 * Description: Takes a Buffer of Bytes to Transmit Asynchronously via a USART Peripheral
 *          - Jumps to USART ISR after every byte successfully sent
 ************************************************************************************/
USART_ErrorStatus_t USART_TxBufferAsyncZeroCopy(u8 USART_Num,char*buffer, u16 len, fnpointer cbf );

/************************************************************************************
 * Service Name: USART_RxBufferAsyncZeroCopy
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  1) USART_Num:
 *                     1) USART_CH1    
 *                     2) USART_CH2   
 *                     3) USART_CH6  
 * 
 *          - 2) buffer: Pointer to a character/string to store received buffer 
 * 
 *          - 3) len: Length of buffer to receive
 * 
 *          - 4) cbf: Callback Function to call after receiving of buffer
 * Parameters (out): None
 * Return value: 
 * Description: Error Status 
 ************************************************************************************/
USART_ErrorStatus_t USART_RxBufferAsyncZeroCopy(u8 USART_Num,u8*buffer, u16 len, fnpointer cbf);

/************************************************************************************
 * Service Name: USART_SendByte
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  1) USART_Num:
 *                     1) USART_CH1    
 *                     2) USART_CH2   
 *                     3) USART_CH6 
 * 					byte: Data to send
 * Parameters (out): None
 * Return value: 
 * Description: Error Status: Returns if Data is successfully transmitted or not
 ************************************************************************************/
USART_ErrorStatus_t USART_SendByte(u8 USART_Num,u8 byte);

/************************************************************************************
 * Service Name: USART_GetByte
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  USART_Num:
 *                     1) USART_CH1    
 *                     2) USART_CH2   
 *                     3) USART_CH6  
 * 					byte: Pointer to variable to store received data
 * Parameters (out): Error Status: Returns if Data is successfully received or not
 * Return value: 
 * Description:Received a byte over a USART Channel 
 ************************************************************************************/
USART_ErrorStatus_t USART_GetByte(u8 USART_Num,u8*byte);

//u8 USART_TxDone(void);
//u8 USART_IsRx(void);

 
#endif  /* MCAL_USART_USART_H_ */

/**********************************************************************************************************************
 *  END OF FILE: USART.h
 *********************************************************************************************************************/
