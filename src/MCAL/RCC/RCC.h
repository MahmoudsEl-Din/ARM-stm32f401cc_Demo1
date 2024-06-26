/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  RCC.h
 *         Name: Mahmoud Shams El-Din 
 *********************************************************************************************************************/
#ifndef MCAL_RCC_RCC_H_
#define MCAL_RCC_RCC_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "LIB/std_types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


/************************************************************************************
 * Description: Clock Sources
 ************************************************************************************/
#define RCC_HSI   0
#define RCC_HSE   1
#define RCC_PLL   2

/************************************************************************************
 * Description: RCC_AHB1ENR PINS    
 ************************************************************************************/
#define GPIOAEN  0x00000001  // Bit mask for GPIOAEN
#define GPIOBEN  0x00000002  // Bit mask for GPIOBEN
#define GPIOCEN  0x00000004  // Bit mask for GPIOCEN
#define GPIODEN  0x00000008  // Bit mask for GPIODEN
#define GPIOEEN  0x00000010  // Bit mask for GPIOEEN
#define GPIOHEN  0x00000080  // Bit mask for GPIOHEN
#define CRCEN    0x00001000  // Bit mask for CRCEN
#define DMA1EN   0x00200000  // Bit mask for DMA1EN
#define DMA2EN   0x00400000  // Bit mask for DMA2EN

/************************************************************************************
 * Description:RCC_AHB2ENR PINS
 ************************************************************************************/
#define OTGFSEN   0x00000080  // Bit mask for OTGFSEN

/************************************************************************************
 * Description: RCC_APB1ENR PINS
 ************************************************************************************/
#define TIM2EN    0x00000001  // Bit mask for TIM2EN
#define TIM3EN    0x00000002  // Bit mask for TIM3EN
#define TIM4EN    0x00000004  // Bit mask for TIM4EN
#define TIM5EN    0x00000008  // Bit mask for TIM5EN
#define WWDGEN    0x00000800  // Bit mask for WWDGEN
#define SPI2EN    0x00004000  // Bit mask for SPI2EN
#define SPI3EN    0x00008000  // Bit mask for SPI3EN
#define USART2EN  0x00020000  // Bit mask for USART2EN
#define I2C1EN    0x00200000  // Bit mask for I2C1EN
#define I2C2EN    0x00400000  // Bit mask for I2C2EN
#define I2C3EN    0x00800000  // Bit mask for I2C3EN
#define PWREN     0x10000000  // Bit mask for PWREN


/************************************************************************************
 * Description: RCC_APB2ENR PINS
 ************************************************************************************/
#define TIM1EN    0x00000001  // Bit mask for TIM1EN
#define USART1EN  0x00000010  // Bit mask for USART1EN
#define USART6EN  0x00000020  // Bit mask for USART6EN
#define ADC1EN    0x00000100  // Bit mask for ADC1EN
#define SDIOEN    0x00000800  // Bit mask for SDIOEN
#define SPI1EN    0x00001000  // Bit mask for SPI1EN
#define SPI4EN    0x00002000  // Bit mask for SPI4EN
#define SYSCFGEN  0x00004000  // Bit mask for SYSCFGEN
#define TIM9EN    0x00010000  // Bit mask for TIM9EN
#define TIM10EN   0x00020000  // Bit mask for TIM10EN
#define TIM11EN   0x00040000  // Bit mask for TIM11EN

/************************************************************************************
 * Description:  Peripheral Buses
 ************************************************************************************/
#define RCC_AHB1 0
#define RCC_AHB2 1
#define RCC_APB1 2
#define RCC_APB2 3

/************************************************************************************
 * Description: AHB prescalar values
 ************************************************************************************/
#define AHB_NO_PRES  0x00000000 //0x0xxxxxxx
#define AHB_PRES_2   0x00000080
#define AHB_PRES_4   0x00000090
#define AHB_PRES_8   0x000000a0
#define AHB_PRES_16  0x000000b0
#define AHB_PRES_64  0x000000c0
#define AHB_PRES_128 0x000000d0
#define AHB_PRES_256 0x000000e0
#define AHB_PRES_512 0x000000f0

/************************************************************************************
 * Description: APB1 prescalar values
 ************************************************************************************/
#define APB1_NO_PRES 0x00000000 //0x0xxxxxxx
#define APB1_PRES_2  0x00001000
#define APB1_PRES_4  0x00001400
#define APB1_PRES_8  0x00001800
#define APB1_PRES_16 0x00001c00

/************************************************************************************
 * Description: APB2 prescalar values
 ************************************************************************************/
#define APB2_NO_PRES 0x00000000 //0x0xxxxxxx
#define APB2_PRES_2  0x00008000
#define APB2_PRES_4  0x0000a000
#define APB2_PRES_8  0x0000c000
#define APB2_PRES_16 0x0000e000

/************************************************************************************
 * Description: Peripheral state
 ************************************************************************************/
typedef enum
{
	Periph_enuOFF,
	Periph_enuON
}RCC_enuPeriphStatus_t;


/************************************************************************************
 * Description: RCC Error Status
 ************************************************************************************/
typedef enum
{
	RCC_enuOK,
	RCC_enuINVALID_CLKSRC,
	RCC_enuINVALID_CLKSTATE,
	RCC_enuINVALID_CLKCTRL,
	RCC_enuNOTRDY,
	RCC_enuCLKOFF,
	RCC_enuSWS_NOTMATCH,
	RCC_enuINVALID_M,
	RCC_enuINVALID_N,
	RCC_enuINVALID_P,
	RCC_enuINVALID_Q,
	RCC_enuINVALID_PLLSRC,
	RCC_enuINVALID_AHBPRES,
	RCC_enuINVALID_APB1PRES,
	RCC_enuINVALID_APB2PRES
}RCC_enuErrorStatus_t;

/************************************************************************************
 * Description: Clock Status
 ************************************************************************************/
typedef enum{
	CLK_OFF,
	CLK_ON
}RCC_enuClkStatus_t;

/************************************************************************************
 * Description: PLL Struct Configuration
 ************************************************************************************/
typedef struct
{
	u32 RCC_enuPLLClockSource;
	u32 RCC_enuPLL_M;
	u32 RCC_enuPLL_N;
	u32 RCC_enuPLL_P;
	u32 RCC_enuPLL_Q;
}RCC_strPLLConfig_t;

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
 * Service Name: RCC_enuControlClock
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  Copy_u8ClockSource: RCC_HSE/RCC_HSI/RCC_PLL
           Copy_enuClockState: CLK_ON/CLK_OFF
 * Parameters (out):  RCC_enuErrorStatus_t: report error at the following cases:
          -Controlling the sys_clk
		  -Choosing wrong clock
	      -Choosing wrong clock state 
 * Return value: 
 * Description:  Function to control the clock state ON/OFF 
 ************************************************************************************/
RCC_enuErrorStatus_t RCC_enuControlClock(u8 Copy_u8ClockSource, RCC_enuClkStatus_t Copy_enuClockState );


/************************************************************************************
 * Service Name: RCC_enuSelectClock
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):   Copy_u8ClockSource: RCC_HSE/RCC_HSI/RCC_PLL
 * Parameters (out): RCC_enuErrorStatus_t: report error at the following cases:
		  -Choosing wrong clock
	      -Choosing wrong clock state  
		  -Clock not ready
		  -Clock not enabled
		  -Wrong SWS 
 * Return value: 
 * Description: Function to select the system clock 
 ************************************************************************************/
RCC_enuErrorStatus_t RCC_enuSelectClock(u8 Copy_u8ClockSource);


/************************************************************************************
 * Service Name: RCC_enuConfigPLL
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  ADD_strPLLConfig: pointer to struct contains
           PLL configuration parameters( CLK_SRC/M/N/P/Q)
 * Parameters (out): RCC_enuErrorStatus_t
 * Return value: 
 * Description: Function to configure PLL clock source  
 ************************************************************************************/
RCC_enuErrorStatus_t RCC_enuConfigPLL(RCC_strPLLConfig_t* ADD_strPLLConfig);

/************************************************************************************
 * Service Name: RCC_enuEnableDisablePeripheral
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  Copy_u32PeripheralBus: RCC_AHB1/RCC_AHB2/RCC_APB1/RCC_APB2
           Copy_u32Peripheral: Peripheral pin (ex:GPIOBEN)
		   Copy_enuPeriphState: Periph_enuOFF/Periph_enuON
 * Parameters (out): RCC_enuErrorStatus_t
 * Return value: 
 * Description: Function to Control(Enable/Disable) peripheral  
 ************************************************************************************/
RCC_enuErrorStatus_t RCC_enuEnableDisablePeripheral(u32 Copy_u32PeripheralBus, u32 Copy_u32Peripheral, RCC_enuPeriphStatus_t Copy_enuPeriphState );

/************************************************************************************
 * Service Name: RCC_enuConfigPrescalar_AHB
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  Copy_u32APB2Prescaler:choose one of the following options :
		  -AHB_NO_PRES
		  -AHB_PRES_2
		  -AHB_PRES_4   
		  -AHB_PRES_8   
		  -AHB_PRES_16  
		  -AHB_PRES_64  
		  -AHB_PRES_128 
		  -AHB_PRES_256 
		  -AHB_PRES_512 
 * Parameters (out): RCC_enuErrorStatus_t
 * Return value: 
 * Description: Function to configure the prescalars of AHB  
 ************************************************************************************/
RCC_enuErrorStatus_t RCC_enuConfigPrescalar_AHB(u32 Copy_u32AHBPrescaler);
/************************************************************************************
 * Service Name: RCC_enuConfigPrescalar_APB1
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  Copy_u32APB2Prescaler:choose one of the following options :
		  -APB1_NO_PRES 
		  -APB1_PRES_2  
		  -APB1_PRES_4 
		  -APB1_PRES_8 
		  -APB1_PRES_16
 * Parameters (out): RCC_enuErrorStatus_t
 * Return value: 
 * Description: Function to configure the prescalars of APB1 
 ************************************************************************************/
RCC_enuErrorStatus_t RCC_enuConfigPrescalar_APB1(u32 Copy_u32APB1Prescaler);

/************************************************************************************
 * Service Name: RCC_enuConfigPrescalar_APB2
 * Service ID[hex]: 0x10
 * Sync/Async: Synchronous
 * Reentrancy: Non reentrant
 * Parameters (in):  Copy_u32APB2Prescaler:choose one of the following options :
		  -APB2_NO_PRES 
		  -APB2_PRES_2  
		  -APB2_PRES_4 
		  -APB2_PRES_8 
		  -APB2_PRES_16
 * Parameters (out): RCC_enuErrorStatus_t
 * Return value: 
 * Description: Function to configure the prescalars of APB2
 ************************************************************************************/
RCC_enuErrorStatus_t RCC_enuConfigPrescalar_APB2(u32 Copy_u32APB2Prescaler);

 
#endif  /* USART_H_ */

/**********************************************************************************************************************
 *  END OF FILE: USART.h
 *********************************************************************************************************************/
