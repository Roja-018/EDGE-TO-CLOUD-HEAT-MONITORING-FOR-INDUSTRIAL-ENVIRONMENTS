//uart0.h

#ifndef _UART0_H_
#define _UART0_H_

// --- Interrupt Configuration ---
// Set to 1 to enable hardware interrupt handling (RDA/THRE) for UART0 inside the driver
#define UART_INT_ENABLE 1

// --- BAUD RATE CLOCK TREE CALCULATION & DIVISOR ---
// These preprocessor directives calculate the exact fractional step value needed for the UART baud rate registers.
#define FOSC      12000000   // Fundamental Oscillator Frequency: 12 MHz external crystal input
#define CCLK      5*FOSC     // Core Clock (System Clock): PLL multiplies FOSC by 5 to achieve 60 MHz
#define PCLK      CCLK/4     // Peripheral Clock: VPB divider scales CCLK down by 4 to run peripherals at 15 MHz
#define BAUD      9600       // Target Communication Speed: 9600 Bits Per Second (Baud Rate)

#define DIVISOR   (PCLK/(16 * BAUD))


// --- Function Prototypes ---

void InitUART0(void);
void UART0_Tx(char ch);
char UART0_Rx(void);
void UART0_Str(char *);
void UART0_Int(unsigned int);

void UART0_Float(float);


#endif