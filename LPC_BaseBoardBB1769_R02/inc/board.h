/**
 * @brief NXP LPC1769 XPresso board file
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __BOARD_H_
#define __BOARD_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup BOARD_NXP_LPCXPRESSO_1769 NXP LPC1769 LPCXpresso board software API functions
 * @ingroup LPCOPEN_17XX_BOARD_LPCXPRESSO_1769
 * The board support software API functions provide some simple abstracted
 * functions used across multiple LPCOpen board examples. See @ref BOARD_COMMON_API
 * for the functions defined by this board support layer.<br>
 * @{
 */

/** @defgroup BOARD_NXP_LPCXPRESSO_1769_OPTIONS BOARD: NXP LPC1769 LPCXpresso board build options
 * This board has options that configure its operation at build-time.<br>
 * @{
 */

/** Define DEBUG_ENABLE to enable IO via the DEBUGSTR, DEBUGOUT, and
    DEBUGIN macros. If not defined, DEBUG* functions will be optimized
    out of the code at build time.
 */
#define DEBUG_ENABLE

/** Define DEBUG_SEMIHOSTING along with DEBUG_ENABLE to enable IO support
    via semihosting. You may need to use a C library that supports
    semihosting with this option.
 */
#define DEBUG_SEMIHOSTING



/**
 * @}
 */

/* Board name */
#define BOARD_BB1769R02

#define USE_RMII

/**
 * Button defines
 */
#define BUTTONS_BUTTON1     0x01
#define BUTTONS_BUTTON2     0x02
#define NO_BUTTON_PRESSED   0xFF

#define BUTTONS_BUTTON1_GPIO_PORT_NUM           0
#define BUTTONS_BUTTON1_GPIO_BIT_NUM            18

#define BUTTONS_BUTTON2_GPIO_PORT_NUM           0
#define BUTTONS_BUTTON2_GPIO_BIT_NUM            1
/**
 * Leds defines
 */
#define LED0_GPIO_PORT_NUM                      0
#define LED0_GPIO_BIT_NUM                       17
#define LED1_GPIO_PORT_NUM                      0
#define LED1_GPIO_BIT_NUM                       22
#define LED2_GPIO_PORT_NUM                      2
#define LED2_GPIO_BIT_NUM                       2
#define LED3_GPIO_PORT_NUM                      2
#define LED3_GPIO_BIT_NUM                       3
#define LED4_GPIO_PORT_NUM                      2
#define LED4_GPIO_BIT_NUM                       4
#define LED5_GPIO_PORT_NUM                      0
#define LED5_GPIO_BIT_NUM                       4
#define LED6_GPIO_PORT_NUM                      2
#define LED6_GPIO_BIT_NUM                       11
#define LED7_GPIO_PORT_NUM                      2
#define LED7_GPIO_BIT_NUM                       12
/*
 * STEPPERS PORTS DEFINE
 */
#define XEN_GPIO_PORT_NUM						0
#define XEN_GPIO_BIT_NUM 						0
#define XDIR_GPIO_PORT_NUM						0
#define XDIR_GPIO_BIT_NUM						10
#define XSTEP_GPIO_PORT_NUM						0
#define XSTEP_GPIO_BIT_NUM						1
#define YEN_GPIO_PORT_NUM						0
#define YEN_GPIO_BIT_NUM 						7
#define YDIR_GPIO_PORT_NUM						0
#define YDIR_GPIO_BIT_NUM						11
#define YSTEP_GPIO_PORT_NUM						0
#define YSTEP_GPIO_BIT_NUM						9
#define ZEN_GPIO_PORT_NUM						LED4_GPIO_PORT_NUM
#define ZEN_GPIO_BIT_NUM 						LED4_GPIO_BIT_NUM
#define ZDIR_GPIO_PORT_NUM						2
#define ZDIR_GPIO_BIT_NUM						12
#define ZSTEP_GPIO_PORT_NUM						0
#define ZSTEP_GPIO_BIT_NUM						8

#define SPINDLE_GPIO_PORT_NUM	LED3_GPIO_PORT_NUM
#define SPINDLE_GPIO_BIT_NUM	LED3_GPIO_BIT_NUM
/*
 * UART PORT DEFINE
 */
#define USBBTXD_GPIO_PORT_NUM					0
#define USBBTXD_GPIO_BIT_NUM					2
#define USBBRXD_GPIO_PORT_NUM					0
#define USBBRXD_GPIO_BIT_NUM					3
/**
 * LCD defines
 */
#define LCDD7_GPIO_PORT_NUM                      2
#define LCDD7_GPIO_BIT_NUM                       8
#define LCDD6_GPIO_PORT_NUM                      2
#define LCDD6_GPIO_BIT_NUM                       7
#define LCDD5_GPIO_PORT_NUM                      2
#define LCDD5_GPIO_BIT_NUM                       6
#define LCDD4_GPIO_PORT_NUM                      2
#define LCDD4_GPIO_BIT_NUM                       5
#define LCDEN_GPIO_PORT_NUM                      2
#define LCDEN_GPIO_BIT_NUM                       1
#define LCDRS_GPIO_PORT_NUM                      2
#define LCDRS_GPIO_BIT_NUM                       0

#define RGB_GPIO_PORT_NUM						2
#define RED_GPIO_BIT_NUM                        3
#define BLUE_GPIO_BIT_NUM                       2
#define GREEN_GPIO_BIT_NUM                      4
/* On the LPC1769, the GPIO interrupts share the EINT3 vector. */
#define GPIO_IRQ_HANDLER  			EINT3_IRQHandler/* GPIO interrupt IRQ function name */
#define GPIO_INTERRUPT_NVIC_NAME    EINT3_IRQn	/* GPIO interrupt NVIC interrupt name */
/*
 * ENDSWITCHES PORTS DEFINE
 */
#define XMAX_GPIO_PORT_NUM						2
#define XMAX_GPIO_BIT_NUM						4
#define XMIN_GPIO_PORT_NUM						2
#define XMIN_GPIO_BIT_NUM						3
#define YMAX_GPIO_PORT_NUM						1
#define YMAX_GPIO_BIT_NUM						27
#define YMIN_GPIO_PORT_NUM						0
#define YMIN_GPIO_BIT_NUM						22
#define ZMAX_GPIO_PORT_NUM						1
#define ZMAX_GPIO_BIT_NUM						18
#define ZMIN_GPIO_PORT_NUM						2
#define ZMIN_GPIO_BIT_NUM						9
//#define AMAX_GPIO_PORT_NUM						0
//#define AMAX_GPIO_BIT_NUM						28
//#define AMIN_GPIO_PORT_NUM						0
//#define AMIN_GPIO_BIT_NUM						27

#define XMAX     0x01
#define XMIN     0x02
#define YMAX     0x03
#define YMIN     0x04
#define ZMAX     0x05
#define ZMIN     0x06
#define AMAX     0x07
#define AMIN     0x08
#define NO_ENDSTOP_PRESSED   0x00
/**
 * Matrix Keypad
 * Private types/enumerations/variables
 */
#define STATE				false

///Row 1 Port and Bit number
#define SW_PORT_ROW1		0
#define SW_GPIO_BIT_ROW1	27
///Row 2 Port and Bit number
#define SW_PORT_ROW2		0
#define SW_GPIO_BIT_ROW2	28
///Row 3 Port and Bit number
#define SW_PORT_ROW3		2
#define SW_GPIO_BIT_ROW3	13
///Row 4 Port and Bit number
#define SW_PORT_ROW4		2
#define SW_GPIO_BIT_ROW4	10
///Col 1 Port and Bit number
#define SW_PORT_COL1		0
#define SW_GPIO_BIT_COL1	23
///Col 2 Port and Bit number
#define SW_PORT_COL2		0
#define SW_GPIO_BIT_COL2	24
///Col 3 Port and Bit number
#define SW_PORT_COL3		0
#define SW_GPIO_BIT_COL3	25
///Col 4 Port and Bit number
#define SW_PORT_COL4		0
#define SW_GPIO_BIT_COL4	26

///Matrix Keyboard Code definitions
#define MK0 0
#define MK1 1
#define MK2 2
#define MK3 3
#define MK4 4
#define MK5 5
#define MK6 6
#define MK7 7
#define MK8 8
#define MK9 9
#define MKA 10
#define MKB 11
#define MKC 12
#define MKD 13
#define MKast 14
#define MKnum 15
#define NO_KEY 99
/**
 * LCD Defines
 */
#define LCD_20x4
#define		LCD_E_OFF				Chip_GPIO_WritePortBit(LPC_GPIO, LCDEN_GPIO_PORT_NUM, LCDEN_GPIO_BIT_NUM,false)
#define		LCD_E_ON				Chip_GPIO_WritePortBit(LPC_GPIO, LCDEN_GPIO_PORT_NUM, LCDEN_GPIO_BIT_NUM,true)
#define		LCD_RS_OFF				Chip_GPIO_WritePortBit(LPC_GPIO, LCDRS_GPIO_PORT_NUM, LCDRS_GPIO_BIT_NUM,false)
#define		LCD_RS_ON				Chip_GPIO_WritePortBit(LPC_GPIO, LCDRS_GPIO_PORT_NUM, LCDRS_GPIO_BIT_NUM,true)
#define		LCD_DATO(d4,d5,d6,d7)	Chip_GPIO_WritePortBit(LPC_GPIO, LCDD4_GPIO_PORT_NUM, LCDD4_GPIO_BIT_NUM,d4);Chip_GPIO_WritePortBit(LPC_GPIO, LCDD5_GPIO_PORT_NUM, LCDD5_GPIO_BIT_NUM,d5);Chip_GPIO_WritePortBit(LPC_GPIO, LCDD6_GPIO_PORT_NUM, LCDD6_GPIO_BIT_NUM,d6);Chip_GPIO_WritePortBit(LPC_GPIO, LCDD7_GPIO_PORT_NUM, LCDD7_GPIO_BIT_NUM,d7)
#define		LCD_CONTROL		1
#define		LCD_DATA		0
//!<  COMANDOS LCD
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

//!< flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

//!< flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

//!< flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00
#define		RENGLON0		0
#define		RENGLON1		1
#define		RENGLON2		2
#define		RENGLON3		3

void EINTInit( void );

void Board_InitLCD ( void );

void Board_Dato_LCD ( unsigned char data , unsigned char control );

void Board_Display_lcd( char *msg , char renglon , char posicion );

void Board_LED_Init(void);

void Board_TurnOff_All_LEDs(void);

void Board_Steppers_Init(void);
void Board_Spindle_Init(void);
void Board_Steppers_OFF(void);

unsigned char Board_MatrixKeyboard_4x4( void );

void Board_MatrixKeyboard_4x4_Init(void);

void Board_InitTimer(LPC_TIMER_T *pTMR,uint8_t channel, uint32_t matchVal);
void Board_TimerClose(LPC_TIMER_T *pTMR);
/**
 * @brief	Initialize pin muxing for a UART
 * @param	pUART	: Pointer to UART register block for UART pins to init
 * @return	Nothing
 */
void Board_UART_Init(LPC_USART_T *pUART,uint32_t baud);

/**
 * @brief	Returns the MAC address assigned to this board
 * @param	mcaddr : Pointer to 6-byte character array to populate with MAC address
 * @return	Nothing
 * @note    Returns the MAC address used by Ethernet
 */
void Board_ENET_GetMacADDR(uint8_t *mcaddr);


/**
 * @brief	Initialize pin muxing for SSP interface
 * @param	pSSP	: Pointer to SSP interface to initialize
 * @return	Nothing
 */
void Board_SSP_Init(LPC_SSP_T *pSSP);

/**
 * @brief	Initialize pin muxing for SPI interface
 * @param	isMaster	: true for master mode, false for slave mode
 * @return	Nothing
 */
void Board_SPI_Init(bool isMaster);

/**
 * @brief	Assert SSEL pin
 * @return	Nothing
 */
void Board_SPI_AssertSSEL(void);

/**
 * @brief	De-assert SSEL pin
 * @return	Nothing
 */
void Board_SPI_DeassertSSEL(void);

/**
 * @brief	Sets up board specific I2C interface
 * @param	id	: ID of I2C peripheral
 * @return	Nothing
 */
void Board_I2C_Init(I2C_ID_T id);

/**
 * @brief	Sets up I2C Fast Plus mode
 * @param	id	: Must always be I2C0
 * @return	Nothing
 * @note	This function must be called before calling
 *          Chip_I2C_SetClockRate() to set clock rates above
 *          normal range 100KHz to 400KHz. Only I2C0 supports
 *          this mode.
 */
STATIC INLINE void Board_I2C_EnableFastPlus(I2C_ID_T id)
{
	Chip_IOCON_SetI2CPad(LPC_IOCON, I2CPADCFG_FAST_MODE_PLUS);
}

/**
 * @brief	Disables I2C Fast plus mode and enable normal mode
 * @param	id	: Must always be I2C0
 * @return	Nothing
 */
STATIC INLINE void Board_I2C_DisableFastPlus(I2C_ID_T id)
{
	Chip_IOCON_SetI2CPad(LPC_IOCON, I2CPADCFG_STD_MODE);
}

/**
 * @brief	Initialize buttons on the board
 * @return	Nothing
 */
void Board_Buttons_Init(void);
void Board_Endstops_Init(void);

/**
 * @brief	Get button status
 * @return	status of button
 */
uint8_t Buttons_GetStatus(void);
uint8_t Endstops_GetStatus(void);


/**
 * @brief	Create Serial Stream
 * @param	Stream	: Pointer to stream
 * @return	Nothing
 */
void Serial_CreateStream(void *Stream);

/**
 * @brief	Initializes USB device mode pins per board design
 * @param	port	: USB port to be enabled 
 * @return	Nothing
 * @note	Only one of the USB port can be enabled at a given time.
 */
void Board_USBD_Init(uint32_t port);

/**
 * @}
 */

#include "board_api.h"
#include "lpc_phy.h"

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H_ */
