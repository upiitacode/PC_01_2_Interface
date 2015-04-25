#include "ARM_delay.h"

extern void SystemCoreClockUpdate (void);
extern int SystemCoreClock;

void delay_raw(unsigned int delay_time){
	unsigned int i;
	unsigned int b=0;
	for(i=0;i<=delay_time;i++){
		b++;
	}
}

void delay_ms(unsigned int ms){
	
	delay_raw(((SystemCoreClock/1000)*ms)/6);
	
}

void delay_us(unsigned int ms){
	delay_raw(((SystemCoreClock/1000000)*ms)/6);
}

void configure_delay(void){
		SystemCoreClockUpdate();
	 //SystemCoreClock=40000000;
}
