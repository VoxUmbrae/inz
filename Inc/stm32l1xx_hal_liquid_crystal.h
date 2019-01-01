/*
 ===============================================================================
 LCD HD44780 driver: c file
 ===============================================================================
 * @date    28-Feb-2016
 * @author  Domen Jurkovic
 * @version v1.1
  
 */
#ifndef __LCD_H
#define __LCD_H

#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_rcc.h"
#include "stm32l1xx_hal_gpio.h"

#include "math.h"
#include "string.h"
#include "stdio.h"

#include "dwt_stm32_delay.h"

/********************************* USER SETUP DEFINES **************************************/
//#define START_X_Y_WITH_0	// uncomment if first row/column is numbered as zero
//#define GO_TO_NEW_LINE_IF_STRING_TOO_LONG	// uncomment if strings larger than screen size should break and continue on new line.
#define WINDOW_PRINT_DELAY	350	// delay between static view and window scrolling (used in LCD_PrintStringWindow();)

// If LCD_CubeMX defined, LCD driver uses CubeMX assigned pins. In this case, pins should be named:
/* LCD_RS - register select pin */
/* LCD_E - enable pin */
/* LCD_D4 - data pin 4 */
/* LCD_D5 - data pin 5 */
/* LCD_D6 - data pin 6 */
/* LCD_D7 - data pin 7 */
//#define	LCD_CubeMX

#ifdef LCD_CubeMX
	#include "mxconstants.h"
#else
	/* Register select*/
#define LCD_D7_Pin GPIO_PIN_0
#define LCD_D7_GPIO_Port GPIOB
#define LCD_D6_Pin GPIO_PIN_1
#define LCD_D6_GPIO_Port GPIOB
#define LCD_D5_Pin GPIO_PIN_2
#define LCD_D5_GPIO_Port GPIOB
#define LCD_D4_Pin GPIO_PIN_10
#define LCD_D4_GPIO_Port GPIOB
#define LCD_D3_Pin GPIO_PIN_11
#define LCD_D3_GPIO_Port GPIOB
#define LCD_D2_Pin GPIO_PIN_12
#define LCD_D2_GPIO_Port GPIOB
#define LCD_D1_Pin GPIO_PIN_13
#define LCD_D1_GPIO_Port GPIOB
#define LCD_D0_Pin GPIO_PIN_14
#define LCD_D0_GPIO_Port GPIOB
#define LCD_E_Pin GPIO_PIN_15
#define LCD_E_GPIO_Port GPIOB
#define LCD_RW_Pin GPIO_PIN_6
#define LCD_RW_GPIO_Port GPIOC
#define LCD_RS_Pin GPIO_PIN_7
#define LCD_RS_GPIO_Port GPIOC
		
	/* enable clocks to all ports. Add/delete unused */
	#define LCD_RCC_ENABLE()		do{ \
																	__GPIOB_CLK_ENABLE(); \
																	__GPIOC_CLK_ENABLE();	\
																}while(0)
#endif
																
/********************************* PRIVATE DEFINES **************************************/
/* Commands*/
#define LCD_CLEARDISPLAY        0x01
#define LCD_RETURNHOME          0x02
#define LCD_ENTRYMODESET        0x04
#define LCD_DISPLAYCONTROL      0x08
#define LCD_CURSORSHIFT         0x10
#define LCD_FUNCTIONSET         0x20
#define LCD_SETCGRAMADDR        0x40
#define LCD_SETDDRAMADDR        0x80

/* Flags for display entry mode */
#define LCD_ENTRYRIGHT          0x00
#define LCD_ENTRYLEFT           0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

/* Flags for display on/off control */
#define LCD_DISPLAYON           0x04
#define LCD_CURSORON            0x02
#define LCD_BLINKON             0x01

/* Flags for display/cursor shift */
#define LCD_DISPLAYMOVE         0x08
#define LCD_CURSORMOVE          0x00
#define LCD_MOVERIGHT           0x04
#define LCD_MOVELEFT            0x00

/* Flags for function set */
#define LCD_8BITMODE            0x10
#define LCD_4BITMODE            0x00
#define LCD_2LINE               0x08
#define LCD_1LINE               0x00
#define LCD_5x10DOTS            0x04
#define LCD_5x8DOTS             0x00

typedef struct {
	uint8_t DisplayControl;
	uint8_t DisplayFunction;
	uint8_t DisplayMode;
	uint8_t Rows;
	uint8_t Cols;
	uint8_t currentX;
	uint8_t currentY;
} _lcd_options_t;		// private LCD structure

/*
	Initializes LCD (HD44780)
	rows: height of lcd
	cols: width of lcd
*/
void LCD_Init(uint8_t rows, uint8_t cols);
void LCD_PrintString(uint8_t y, uint8_t x, char* str);
void LCD_PrintStringWindow(uint8_t y, uint8_t x, uint8_t window_size, uint16_t speed_ms, char* str);
void LCD_PrintNumber(uint8_t y, uint8_t x, int32_t number);
void LCD_PrintFloat(uint8_t y, uint8_t x, float number_f, uint8_t precision);

void LCD_DisplayOn(void);
void LCD_DisplayOff(void);
void LCD_Clear(void);
void LCD_ClearArea(uint8_t y, uint8_t x_start, uint8_t x_end);
void LCD_BlinkOn(void);
void LCD_BlinkOff(void);
void LCD_CursorOn(void);
void LCD_CursorOff(void);
void LCD_ScrollLeft(void);
void LCD_ScrollRight(void);

/**********************************************************/
/*	CUSTOM CHARACTER FUNCTIONS */
/**********************************************************/
/*
	Creates custom character at specific location 
	LCD supports up to 8 custom characters, locations: 0 - 7
	*data: Pointer to 8-bytes of data for one character
 */
void LCD_CreateChar(uint8_t location, uint8_t* data);

/**
 *  Puts custom created character on LCD
 *  location: Location on LCD where character is stored, 0 - 7
 */
void LCD_PutCustom(uint8_t y, uint8_t x, uint8_t location);


/**********************************************************/
/*	PRIVATE FUNCTIONS */
/**********************************************************/
void _lcd_init_pins(void);
void _lcd_send_command(uint8_t cmd);
void _lcd_send_command_4_bit(uint8_t cmd);
void _lcd_send_data(uint8_t data);
void _lcd_cursor_set(uint8_t row, uint8_t col);
void _lcd_enable_pulse(void);


#endif /* __LCD_H */
