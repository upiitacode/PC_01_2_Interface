////////////////////////////////////
#ifndef _LCD_LIB_H_
#define _LCD_LIB_H_
	#include "ARM_delay.h"
	#include "TM4C123.h"
	#define LCD_CTL_PORT GPIOE_BASE
	#define PIN_RS	0
	#define PIN_RW  1
	#define PIN_E		2
	#define STATE_LOW  0
	#define STATE_HIGH  1
	#define RS_INSTRUCTION 0
	#define RS_DATA 1
	#define RW_WRITE 0
	#define RW_READ 1
	
	void configureGPIO(void);
	void outputPin(unsigned char pin_name,unsigned char pin_val);
	void send_command(unsigned char);
	void send_data(unsigned char data);
	void outputNibble(int data);
	void lcd_init(void);

#endif
