// 74HC595.h
// Runs on TM4C123
// Use SSI0 to send a 8-bit code to the 74HC595.
// Output port expander
// If running at 80 MHz change SSI0_CPSR_R to 4
// Daniel Valvano
// July 17, 2015

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
   Program 7.4

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
// TM4C123      74HC595
//   +3.3       pin 16 Vcc powewr
//   Gnd        pin 8  ground
//   Gnd        pin 13 G*
//  +3.3        pin 10 SCLR*
// PA2 SSI0Clk  pin 11 SCK
// PA3 SSI0Fss  pin 12 RCK
// PA5 SSI0Tx   pin 14 SER

// Port         74HC595
// bit 7 (msb)  pin 7  Qh
// bit 6        pin 6  Qg
// bit 5        pin 5  Qf
// bit 4        pin 4  Qe
// bit 3        pin 3  Qd
// bit 2        pin 2  Qc
// bit 1        pin 1  Qb
// bit 0 (LSB)  pin 15 Qa

// see Figure 7.19 for complete schematic

//********Port_Init*****************
// Initialize 74HC595 serial shift register
// inputs:  none
// outputs: none
// assumes: system clock rate less than or equal to 50 MHz
void Port_OutInit(void);

//********Port_Out*****************
// Send data to 74HC595 8-bit port
// inputs:  output (0 to 255)
// outputs: none
void Port_Out(uint8_t code);
