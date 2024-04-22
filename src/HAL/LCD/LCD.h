/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  LCD.h
 *          Description:  
 *          Name: Mahmoud Shams El-Din
 *********************************************************************************************************************/
#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/std_types.h"
#include "MCAL/GPIO/GPIO.h"
#include "LCD_cfg.h"


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/************************************************************************************
 * Description: Control pins
 ************************************************************************************/
#define LCD_RS 0
#define LCD_RW 1
#define LCD_E  2

/************************************************************************************
 * Description: Data pins
 ************************************************************************************/
#define LCD_DB0 3
#define LCD_DB1 4
#define LCD_DB2 5
#define LCD_DB3 6
#define LCD_DB4 7
#define LCD_DB5 8
#define LCD_DB6 9
#define LCD_DB7 10
#define LCD_PINS_NUM 11

/************************************************************************************
 * Description: 
 ************************************************************************************/
/*#define Cursor_Left_Shift  0b00010000
#define Cursor_Right_Shift 0b00010100*/

/************************************************************************************
 * Description: Callback Function Pointer for LCD
 ************************************************************************************/
typedef void (*LCD_CBF)(void);

/************************************************************************************
 * Description: LCD
 ************************************************************************************/
typedef struct
{
    void* PORT;
    u32 PIN;
} LCD_PinCgf_t;
/************************************************************************************
 * Description: LCD error types
 ************************************************************************************/
typedef enum
{
    LCD_enuOk,            /* Operation successful */
    LCD_enuNullPtr ,      /* Null Pointer */
    LCD_enuWrongPosition, /* Wrong x,y position at DDRAM */
    LCD_WrongBlockNum     /* Wrong block number at CGRAM */
} LCD_enumError_t;

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
 * Service Name: LCD_InitPins
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): None
 * Return value: 
 * Description:   Function to initialize the LCD Pins
 ************************************************************************************/
void LCD_InitPins(void);

/************************************************************************************
 * Service Name: LCD_InitPins
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  cbf - Pointer to the callback function for asynchronous initialization
 * Parameters (out): None
 * Return value: 
 * Description:   Function to request a LCD initialization process
 ************************************************************************************/
void LCD_init_asynch(LCD_CBF cbf );

/************************************************************************************
 * Service Name: LCD_enuWriteString_asynch
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  string - Pointer to the string to be written
 * 					cbf - Pointer to the callback function for asynchronous operation
 * Parameters (out): LCD_enumError_t
 * Return value: 
 * Description:  Saves user request for writing a string on LCD
 ************************************************************************************/
LCD_enumError_t LCD_enuWriteString_asynch(const char* string, LCD_CBF cbf);

/************************************************************************************
 * Service Name: LCD_enuWriteNumber_asynch
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  Copy_u8Number - The number to be written
 * Parameters (out): None
 * Return value: 
 * Description:  Saves user request for writing a number on LCD
 ************************************************************************************/
void LCD_enuWriteNumber_asynch(u16 Copy_u8Number,LCD_CBF cbf);

/************************************************************************************
 * Service Name: LCD_ClearScreen_async
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): None
 * Return value: 
 * Description:   Saves user request for LCD clear
 ************************************************************************************/
void LCD_ClearScreen_async(void);

/************************************************************************************
 * Service Name: LCD_GotoPos_XY_async
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  Copy_u8X - The X coordinate of the position (0 for first line, 1 for second line)
 * 					Copy_u8Y - The Y coordinate of the position (0 to 15)
 * 					cbf - Pointer to the callback function for asynchronous operation
 * Parameters (out): LCD_enumError_t
 * Return value: 
 * Description:  Saves user request for setting the cursor position on the LCD
 ************************************************************************************/
LCD_enumError_t LCD_GotoPos_XY_async(u8 Copy_u8X, u8 Copy_u8Y, LCD_CBF cbf);

/************************************************************************************
 * Service Name: LCD_ShiftCursor_asynch
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  Direction
 * Parameters (out): None
 * Return value: 
 * Description:  Shift the cursor position
 ************************************************************************************/
void LCD_ShiftCursor_asynch(u8 direction);

/************************************************************************************
 * Service Name: LCD_DisableCursor_asynch
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): None
 * Return value: 
 * Description:   Disable Cursor
 ************************************************************************************/
void LCD_DisableCursor_asynch(void);

/************************************************************************************
 * Service Name: LCD_EnableCursor_asynch
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  None
 * Parameters (out): None
 * Return value: 
 * Description:   Enable Cursor
 ************************************************************************************/
void LCD_EnableCursor_asynch(void);

#endif // HAL_LCD_LCD_H_
/**********************************************************************************************************************
 *  END OF FILE: LCD.h
 *********************************************************************************************************************/
