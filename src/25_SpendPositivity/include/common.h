#ifndef COMMON_H
#define COMMON_H


#include "libc/stdint.h"

// Define common integer types for easier reference
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

// Hardware communication functions
void outb(u16int port, u8int value);  // Send a byte to a port
u8int inb(u16int port);               // Receive a byte from a port
u16int inw(u16int port);              // Receive a word from a port


#endif
