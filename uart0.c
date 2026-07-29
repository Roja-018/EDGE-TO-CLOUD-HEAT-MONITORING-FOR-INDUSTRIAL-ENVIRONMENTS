//uart0.c

#include <LPC21xx.H>                                                                                                                                                                                                                                                                                                    #include "uart0.h"                                                                                                                                                                                                                                                                                                      // --- Global Variables ---                                                                                                                                 char buff[200]="hello", dummy;  // Receive buffer array and dummy read storage variable                                                                     unsigned char i=0, ch, r_flag;  // Index counter, char cache, and general receive status flag                                                                                                                                                                                                                           void UART0_isr(void) __irq                                                                                                                                  {                                                                                                                                                             // U0IIR (Interrupt Identification Register) bit 2:1 is 0x2 (binary 010) when Receive Data Available (RDA)                                                  if((U0IIR & 0x04)) // Check if a receive interrupt is pending                                                                                               {                                                                                                                                                                         ch = U0RBR;     /* Read the Receiver Buffer Register to fetch data & automatically Clear Receive Interrupt */                                               if(i<200)   // Prevent array index boundary overflow                                                                                                                buff[i++] = ch; // Store the incoming character into the buffer and increment index                                                   }                                                                                                                                                           else                                                                                                                                                        {                                                                                                                                                               // If the interrupt wasn't triggered by reception, it's likely a Transmit Holding Register Empty (THRE) interrupt                                           dummy=U0IIR; // A acknowledge read of U0IIR or writing data to U0THR clears the transmit interrupt flag                                                                                                                                                                                                             }                                                                                                                                                            VICVectAddr = 0; /* Dummy write to the Vectored Interrupt Controller to signal completion of ISR execution */                                            }                                                                                                                                                                                                                                                                                                                       void InitUART0 (void) /* Initialize Serial Interface       */                                                                                               {                                                                                                                                                                                                                                                                                                                         PINSEL0 = 0x00000005; /* Pin Function Select 0: Configures bits [3:0] as 0101 to enable RxD0 (P0.1) and TxD0 (P0.0) */                                      U0LCR = 0x83;         /* Line Control Register: Set Bit 7 (DLAB=1) to allow baud rate updates. Set bits [1:0]=11 for 8-bit characters, 1 stop bit, no parity */
  U0DLL = DIVISOR;      /* Load the lower 8 bits (Least Significant Byte) of the calculated baud rate clock divisor factor */
        U0DLM = DIVISOR>>8;   /* Load the upper 8 bits (Most Significant Byte) of the calculated baud rate clock divisor factor */
  U0LCR = 0x03;         /* Line Control Register: Clear Bit 7 (DLAB = 0) to lock the baud rate dividers and open RBR/THR registers */

  #if UART_INT_ENABLE > 0

  VICIntSelect = 0x00000000; // Configure UART0 channel as a standard IRQ (Interrupt Request), not a high-priority FIQ
  VICVectAddr0 = (unsigned)UART0_isr; // Assign the execution memory address of our custom handler to Vector Address Slot 0
    VICVectCntl0 = 0x20 | 6; /* Vector Control Slot 0: Bit 5 enables the slot (0x20), and bits [4:0]=6 links it to hardware Peripheral ID 6 (UART0) */
  VICIntEnable = 1 << 6;   /* Enable Interrupt: Write a 1 to bit 6 to let UART0 interrupt requests bypass the mask layer to the CPU */

  U0IER = 0x03;       /* Interrupt Enable Register: Write 0x03 to enable both Receive Data (RDA) and Transmit Holding Register Empty (THRE) interrupts */

  #endif

}

void UART0_Tx(char ch)  /* Write character to Serial Port    */
{
  // Poll Line Status Register (U0LSR) bit 5 (THRE). It turns to 1 when the transmit queue pipeline becomes vacant.
  while (!(U0LSR & 0x20));
  U0THR = ch;          /* Load the character byte into the Transmit Holding Register to initiate hardware transmission shifting */
}

char UART0_Rx(void)
{
  // Poll Line Status Register (U0LSR) bit 0 (Receiver Data Ready). It transitions to 1 when a full byte arrives.
  while (!(U0LSR & 0x01));
  return (U0RBR);       /* Read and return the data byte waiting inside the Receiver Buffer Register */
}

void UART0_Str(char *s)
{
   while(*s)                 // Terminate loop once the string termination symbol ('\0') is detected
       UART0_Tx(*s++);       // Send current character, then shift the memory pointer to the next array element
}

void UART0_Int(unsigned int n)
{
  unsigned char a[10]={0,0,0,0,0,0,0,0,0,0}; // Array container to store isolated individual numeric digits
  int i=0;

  if(n==0)
  {
    UART0_Tx('0'); // Base condition fallback check: immediately send '0' if input is zero
       return;
  }
  else
  {
     // Extract individual digits backwards using modulo base-10 math
     while(n>0)
         {
           a[i++]=(n%10)+48; // Capture remainder digit and offset it into ASCII character space ('0' = 48)
           n=n/10;           // Shift structural integer place value down by one factor
         }
         --i; // Step back array pointer index to reference the last extracted active integer digit slot

         // Reorient and transmit the parsed digits forward so they display correctly on the terminal
         for(;i>=0;i--)
         {
           UART0_Tx(a[i]);
         }
   }
}

void UART0_Float(float f)
{
  int x;
  float temp;

  x=f;          // Cast float to integer, completely truncating the trailing fractional elements to capture the whole number portion
  UART0_Int(x); // Transmit the isolated whole number part
    UART0_Tx('.'); // Inject the dot decimal separator notation marker symbol

  temp=(f-x)*100;
  x=temp;       // Re-truncate target segment to discard downstream floating calculations
  UART0_Int(x); // Transmit the final fractional digits segment
}
    