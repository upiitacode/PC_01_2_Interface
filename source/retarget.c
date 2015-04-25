/*----------------------------------------------------------------------------
 * Name:    Retarget.c
 * Purpose: 'Retarget' layer for target-dependent low level functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the �Vision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <rt_misc.h>

//#pragma import(__use_no_semihosting_swi)

extern void send_data(unsigned char);
extern void send_command(unsigned char);
struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


int fputc(int c, FILE *f) {
  if(c=='\f'){
		send_command(0x01);
	}else if(c=='\n'){
		send_command(0xC0);
	}else{
		send_data(c);
	}
	return (c);
}


int fgetc(FILE *f) {
  return '\0';
}


int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}
