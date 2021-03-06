//1. Poll the ADC periodicly updtaing the ADC value
// This will be concluded after avery timer interupt
//2. Poll the ADC manually in software as needed
// This will be concluded after the instruction is run
//3. Poll the ADC bassed on interupts
// This will be concluded every time the thermistor resistance changes

// PeriodicTimer0AInts.c
// Runs on LM4F120/TM4C123
// Use Timer0A in periodic mode to request interrupts at a particular
// period.
// Daniel Valvano
// September 11, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
  Program 7.5, example 7.6

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

// oscilloscope or LED connected to PF3-1 for period measurement
// When using the color wheel, the blue LED on PF2 is on for four
// consecutive interrupts then off for four consecutive interrupts.
// Blue is off for: dark, red, yellow, green
// Blue is on for: light blue, blue, purple, white
// Therefore, the frequency of the pulse measured on PF2 is 1/8 of
// the frequency of the Timer0A interrupts.

#include "..//inc//tm4c123gh6pm.h"
#include <stdint.h>
#include "PLL.h"
#include "fixed.h"
#include "Timer0A.h"
#include "ADCT0ATrigger.h"
#include "Lab2.h"
#include "ST7735.h"
#include "temperature.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

unsigned long temperature;
volatile unsigned long ADCvalue;
unsigned long offset = 0;

int j = 0;
int i = 0;

void plotInit(void){
	ST7735_SetCursor(0,0); 
	ST7735_OutString("Temp");
	ST7735_PlotClear(1000,4000);  // range from 0 to 4095
	ST7735_SetCursor(0,1); 
	ST7735_OutString("N=");
	ST7735_SetCursor(0,2); 
	ST7735_OutString("T="); 
	ST7735_sDecOut2(0000);
	ST7735_SetCursor(7,2); 
  ST7735_OutString("C");
}

int N = 1;
void plotPoint(void){
	ST7735_PlotPoint(temperature);  // Measured temperature
	if((j&(N-1))==0){          // fs sampling, fs/N samples plotted per second
		ST7735_PlotNextErase();  // overwrites N points on same line
	}
	j++;                       // counts the number of samples
}

// if desired interrupt frequency is f, Timer0A_Init parameter is busfrequency/f
#define F16HZ (50000000/16)
#define F20HZ (50000000/20)
#define F30HZ (50000000/30)
#define F20KHZ (50000000/20000)
//debug code
int main(void){
	PLL_Init(Bus80MHz);	// bus clock at 50 MHz
  Output_Init();
	SYSCTL_RCGCGPIO_R |= 0x20;       // activate port F
	//ADC0_InitTimer0ATriggerSeq3(2, F30HZ); // ADC channel 0, 1000 Hz sampling
	ADC0_InitTimer0ATriggerSeq3PD3(F30HZ);
  //ADC0_InitSWTriggerSeq3_Ch9();
	while((SYSCTL_PRGPIO_R&0x0020) == 0){};// ready?
  GPIO_PORTF_DIR_R |= 0x02;        // make PF1 output (PF1 built-in LEDs)
  GPIO_PORTF_AFSEL_R &= ~0x02;     // disable alt funct on PF1
  GPIO_PORTF_DEN_R |= 0x02;        // enable digital I/O on PF1
                                   // configure PF1 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;          // disable analog functionality on PF
  EnableInterrupts();

	plotInit();
		
	while(1){
		GPIO_PORTF_DATA_R ^= 0x02;           // toggle LED
		//ADCvalue = ADC0_InSeq3();
		temperature = adcToTemp(ADCvalue + offset);
		plotPoint();
		ST7735_SetCursor(1,2);
		ST7735_sDecOut2(temperature);
		ST7735_SetCursor(2,1);
		ST7735_OutUDec(ADCvalue + offset);
	}
}
