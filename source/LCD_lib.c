#include "LCD_lib.h" 
void configureGPIO(){
		SYSCTL->RCGCGPIO|=0x3F;
		//Control Signals E0 E1 E2	
		GPIOE->DEN|=0x7;//Digital functions
	  GPIOE->ODR|=0x7;//Open Drain output type // llegue a 5 volts (ver data)// con resistencias de 10K a vcc 5 volts (no mas)
		GPIOE->DIR|=0x7;//Pins as Output
		//Data Singnals   A4 A5 A6 A7
		GPIOA->DEN|=0xF0;//Digital functions
	  GPIOA->ODR|=0xF0;//Open Drain output type
		GPIOA->DIR|=0xF0;//Pins as Output
}

void lcd_sendChar(char c){
  if(c=='\f'){
		send_command(0x01);
	}else if(c=='\n'){
		send_command(0xC0);
	}else{
		send_data(c);
	}
}

void lcd_init(){
	SystemCoreClockUpdate();
	SystemCoreClockUpdate();
	configureGPIO();
	outputPin(PIN_RW,RW_WRITE);
	outputNibble(0xF);
	outputPin(PIN_RW,RW_WRITE);
	outputPin(PIN_E,STATE_LOW);
	outputPin(PIN_RS,RS_INSTRUCTION);
	delay_ms(30);
	outputNibble(0x2);
	delay_us(1);
	outputPin(PIN_E,STATE_HIGH);
	delay_us(1);
	outputPin(PIN_E,STATE_LOW);
  delay_ms(1);	
	send_command(0x2C);
	send_command(0x0C);
	send_command(0x01);
	delay_ms(1);
}

void outputNibble(int data){
		int *PORTA_H=(int*)GPIOA_BASE;
	  PORTA_H[0xF0]=data<<4;
}

void send_data(unsigned char data){
	outputPin(PIN_RW,RW_WRITE);
	outputPin(PIN_E,STATE_LOW);
	outputPin(PIN_RS,RS_DATA);
	outputNibble(data>>4);
	delay_us(1);
	outputPin(PIN_E,STATE_HIGH);
	delay_us(1);
	outputPin(PIN_E,STATE_LOW);
  delay_us(1);
  outputNibble(data&0xF);
	delay_us(1);
	outputPin(PIN_E,STATE_HIGH);
	delay_us(1);
	outputPin(PIN_E,STATE_LOW);
  delay_us(40);
}

void send_command(unsigned char command){
	outputPin(PIN_RW,RW_WRITE);
	outputPin(PIN_E,STATE_LOW);
	outputPin(PIN_RS,RS_INSTRUCTION);
	outputNibble(command>>4);
	delay_us(1);
	outputPin(PIN_E,STATE_HIGH);
	delay_us(1);
	outputPin(PIN_E,STATE_LOW);
  delay_us(1);
  outputNibble(command&0xF);
	delay_us(1);
	outputPin(PIN_E,STATE_HIGH);
	delay_us(1);
	outputPin(PIN_E,STATE_LOW);
  delay_us(1600);
}

void outputPin(unsigned char pin_name,unsigned char pin_val){
	int* LCD_CTL=(int *)LCD_CTL_PORT;
	LCD_CTL[0x1<<pin_name]=pin_val<<pin_name;
}
