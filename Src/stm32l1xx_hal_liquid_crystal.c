 /*
 ===============================================================================
 LCD HD44780 driver: c file
 ===============================================================================
 * @date    28-Feb-2016
 * @author  Domen Jurkovic
 * @version v1.1
 
	1. Set up library:
		1.1. Set up pins using HAL library or CubeMX. See pin naming in header file.
		1.2. Set up (comment/uncomment) defines in header file
	
	2. Init library:
		LCD_Init(2, 20);	// 2 rows, 20 characters
	
	3. Print characters/strings/numbers:
		LCD_PrintString(1, 1, "www.damogranlabs.com ");
		LCD_PrintStringWindow(1, 1, 10, 350, "Find us on github and www.damogranlabs.com ");
		LCD_PrintNumber(2, 1, -10);
		LCD_PrintFloat(2, 1, -326.5635, 5);
		
	3.1 Check header file for more functions. 
	
	3.2. Create & print custom characters
		uint8_t damogranlabs_logo[]={
			0x0F,
			0x13,
			0x11,
			0x11,
			0x0e,
			0x00,
			0x00		
		};
		LCD_CreateChar(0, damogranlabs_logo); 
		LCD_PutCustom(2, 10, 0);
 */

#include "stm32l1xx_hal_liquid_crystal.h"

/* Private variable */
static _lcd_options_t _lcd_options;

void LCD_Init(uint8_t rows, uint8_t cols) {
	DWT_Delay_Init ();					// Initialize microsecond delay
	HAL_Delay(50);
	#ifndef LCD_CubeMX
		_lcd_init_pins();	// Init pinout 
		HAL_Delay(50);	//At least 40ms
	#endif
	
	// Set LCD width and height 
	_lcd_options.Rows = rows;
	_lcd_options.Cols = cols;
	// Set cursor pointer to beginning for LCD 
	_lcd_options.currentX = 0;
	_lcd_options.currentY = 0;
	
	_lcd_options.DisplayFunction = LCD_4BITMODE | LCD_5x8DOTS | LCD_1LINE;
	if (rows > 1) {
		_lcd_options.DisplayFunction |= LCD_2LINE;
	}
	
	/* Try to set 4bit mode */
	_lcd_send_command_4_bit(0x03);
	HAL_Delay(6);
	
	/* Second try */
	_lcd_send_command_4_bit(0x03);
	HAL_Delay(5);
	
	/* Third goo! */
	_lcd_send_command_4_bit(0x03);
	HAL_Delay(5);	
	
	/* Set 4-bit interface */
	_lcd_send_command_4_bit(0x02);
	DWT_Delay_us (210);
	
	// Set # lines, font size, etc.
	_lcd_send_command(LCD_FUNCTIONSET | _lcd_options.DisplayFunction);

	// Turn the display on, no cursor, no blinking
	_lcd_options.DisplayControl = LCD_DISPLAYON;
	LCD_DisplayOn();

	LCD_Clear();

	// Default font & direction
	_lcd_options.DisplayMode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	_lcd_send_command(LCD_ENTRYMODESET | _lcd_options.DisplayMode);
	HAL_Delay(5);
}

/*
	Print string on lcd
	y location (row)	
	x location (col)
	*str: pointer to string to display
 */
void LCD_PrintString(uint8_t y, uint8_t x, char* str) {
	#ifndef START_X_Y_WITH_0
	x--; y--;
	#endif
	_lcd_cursor_set(y, x);
	while (*str) {
		#ifdef GO_TO_NEW_LINE_IF_STRING_TOO_LONG
			if (_lcd_options.currentX >= _lcd_options.Cols) {
				_lcd_options.currentX = 0;
				_lcd_options.currentY++;
				_lcd_cursor_set(_lcd_options.currentY, _lcd_options.currentX);
			}
			if (*str == '\n') {
				_lcd_options.currentY++;
				_lcd_cursor_set(_lcd_options.currentY, _lcd_options.currentX);
			} else if (*str == '\r') {
				_lcd_cursor_set(_lcd_options.currentY, 0);
			} else {
				_lcd_send_data(*str);
				_lcd_options.currentX++;
			}
			str++;
		#else
			if (*str == '\n') {
				_lcd_options.currentY++;
				_lcd_cursor_set(_lcd_options.currentY, _lcd_options.currentX);
			} else if (*str == '\r') {
				_lcd_cursor_set(_lcd_options.currentY, 0);
			} else {
				_lcd_send_data(*str);
				_lcd_options.currentX++;
			}
			str++;
		#endif
		
	}
}


/*
	Print string and scroll it (right to left) on LCD in specific window size. 
*/
void LCD_PrintStringWindow(uint8_t y, uint8_t x, uint8_t window_size, uint16_t speed_ms, char* str){
	#ifndef START_X_Y_WITH_0
	x--; y--;
	#endif
	
	uint8_t _window_character_number = 0;
	uint8_t string_length = strlen(str); // number of characters in passed string
	uint8_t _str_character_number = 0;	// 0 - strlen(str)
	char* _str = str;
	
	_lcd_cursor_set(y, x);
	
	
	if(string_length > window_size){	// string is larger than window size. String must be scrolled 
		
		// write character while they are inside window size
		while(_str_character_number < window_size){	
			_lcd_send_data(*_str);
			
			_lcd_options.currentX++;
			_str_character_number++;
			_str++;
		}
		HAL_Delay(WINDOW_PRINT_DELAY);
			
		_str_character_number = 0;
		_str = str++;	// increment starting character
		
		// scroll characters in window until last x characters can be shown in window
		while((string_length - _str_character_number) >= window_size){
			_window_character_number = 0;	// reset character position in window.
			_lcd_cursor_set(y, x);
						
			while(_window_character_number < window_size){				// while character number is smaller than window size
				_lcd_send_data(*_str);	// print character
				_lcd_options.currentX++;	// increment x position
				_window_character_number++;	// increment position in window
				_str++;	// increment starting character
			}
			
			_str = str++;	// increment starting character
			_str_character_number++;
			
			HAL_Delay(speed_ms);
		}
	}
	else{	// string is smaller than window size. Print it normally.
		LCD_PrintString(y, x, str);
	}
}

/*
	Print number on lcd
	y location (row)	
	x location (col)
	number = in32_t (range: -2147483647 to 2147483647)
 */
void LCD_PrintNumber(uint8_t y, uint8_t x, int32_t number){
	char buf[50];
  snprintf (buf, 100, "%d", number);
	LCD_PrintString(y, x, buf);
}

/*
	Print float on lcd
	y location (row)	
	x location (col)
	number = float (range: -2147483647 to 2147483647)
 */
void LCD_PrintFloat(uint8_t y, uint8_t x, float number_f, uint8_t precision){
	char buf[50];
  snprintf ( buf, 100, "%.*g", precision, number_f);
	LCD_PrintString(y, x, buf);
}

void LCD_Clear(void) {
	_lcd_send_command(LCD_CLEARDISPLAY);
	HAL_Delay(4);
}

void LCD_ClearArea(uint8_t y, uint8_t x_start, uint8_t x_end){
	uint8_t x = x_start;
	while(x <= x_end){
		LCD_PrintString(y, x, " ");
		x++;
	}
	
}

void LCD_DisplayOn(void) {
	_lcd_options.DisplayControl |= LCD_DISPLAYON;
	_lcd_send_command(LCD_DISPLAYCONTROL | _lcd_options.DisplayControl);
}

void LCD_DisplayOff(void) {
	_lcd_options.DisplayControl &= ~LCD_DISPLAYON;
	_lcd_send_command(LCD_DISPLAYCONTROL | _lcd_options.DisplayControl);
}

void LCD_BlinkOn(void) {
	_lcd_options.DisplayControl |= LCD_BLINKON;
	_lcd_send_command(LCD_DISPLAYCONTROL | _lcd_options.DisplayControl);
}

void LCD_BlinkOff(void) {
	_lcd_options.DisplayControl &= ~LCD_BLINKON;
	_lcd_send_command(LCD_DISPLAYCONTROL | _lcd_options.DisplayControl);
}

void LCD_CursorOn(void) {
	_lcd_options.DisplayControl |= LCD_CURSORON;
	_lcd_send_command(LCD_DISPLAYCONTROL | _lcd_options.DisplayControl);
}

void LCD_CursorOff(void) {
	_lcd_options.DisplayControl &= ~LCD_CURSORON;
	_lcd_send_command(LCD_DISPLAYCONTROL | _lcd_options.DisplayControl);
}

void LCD_ScrollLeft(void) {
	_lcd_send_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}

void LCD_ScrollRight(void) {
	_lcd_send_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

void LCD_CreateChar(uint8_t location, uint8_t *data) {
	uint8_t i;
	/* We have 8 locations available for custom characters */
	location &= 0x07;
	_lcd_send_command(LCD_SETCGRAMADDR | (location << 3));
	
	for (i = 0; i < 8; i++) {
		_lcd_send_data(data[i]);
	}
}

void LCD_PutCustom(uint8_t y, uint8_t x, uint8_t location) {
	#ifndef START_X_Y_WITH_0
	x--; y--;
	#endif
	
	_lcd_cursor_set(y, x);
	_lcd_send_data(location);
}

/* Private functions */
void _lcd_send_command(uint8_t cmd) {
	/* Command mode */
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
		
	/* High nibble */
	_lcd_send_command_4_bit(cmd >> 4);
	/* Low nibble */
	_lcd_send_command_4_bit(cmd & 0x0F);
}

void _lcd_send_data(uint8_t data) {
	/* Data mode */
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET);
	
	/* High nibble */
	_lcd_send_command_4_bit(data >> 4);
	/* Low nibble */
	_lcd_send_command_4_bit(data & 0x0F);
}

void _lcd_send_command_4_bit(uint8_t cmd) {
	/* Set output port */
	HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (GPIO_PinState) (cmd & 0x08));
	HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (GPIO_PinState) (cmd & 0x04));
	HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (GPIO_PinState) (cmd & 0x02));
	HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (GPIO_PinState) (cmd & 0x01));
	
	_lcd_enable_pulse();
}

void _lcd_cursor_set(uint8_t row, uint8_t col){
	uint8_t row_offsets[] = {0x00, 0x40, 0x14, 0x54};
		
	/* Go to beginning */
	if (row >= _lcd_options.Rows) {
		row = 0;
	}
	
	/* Set current column and row */
	_lcd_options.currentX = col;
	_lcd_options.currentY = row;
	
	/* Set location address */
	_lcd_send_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}



void _lcd_init_pins(void) {
	#ifndef LCD_CubeMX
		GPIO_InitTypeDef GPIO_InitStruct;
	
		LCD_RCC_ENABLE();
	
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_VERY_LOW;
		
		GPIO_InitStruct.Pin = LCD_RS_Pin;
		HAL_GPIO_Init(LCD_RS_GPIO_Port, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = LCD_E_Pin;
		HAL_GPIO_Init(LCD_E_GPIO_Port, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = LCD_D4_Pin;
		HAL_GPIO_Init(LCD_D4_GPIO_Port, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = LCD_D5_Pin;
		HAL_GPIO_Init(LCD_D5_GPIO_Port, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = LCD_D6_Pin;
		HAL_GPIO_Init(LCD_D6_GPIO_Port, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = LCD_D7_Pin;
		HAL_GPIO_Init(LCD_D7_GPIO_Port, &GPIO_InitStruct);
	#endif
	
	// GPIO initial state
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, GPIO_PIN_RESET);
}

void _lcd_enable_pulse(void){
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET);
	DWT_Delay_us (10);
	HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
	DWT_Delay_us (210);
}
