// System Clock Configurations
#define FOSC      12000000          // Crystal Oscillator Frequency (12 MHz)
#define CCLK      5*FOSC            // Core Clock / Processor Clock (60 MHz via PLL)
#define PCLK      CCLK/4            // Peripheral Clock (15 MHz, determined by VPBDIV register)

// ADC Operation Settings
#define ADCLK     3000000           // Desired ADC Clock frequency (3 MHz, max allowed is 4.5 MHz for LPC21xx)

// ADC Control Register (ADCR) Bitfields
// CLK_DIV calculates the division factor (15MHz/3MHz - 1 = 4) and shifts it to bits [15:8] of ADCR
#define CLK_DIV   ((PCLK/ADCLK)-1)<<8

// Channel Selection Bitmasks for ADCR [7:0]
#define CH0       1                 // Selects ADC Channel 0 (AD0.0) -> Bit 0
#define CH1       2                 // Selects ADC Channel 1 (AD0.1) -> Bit 1
#define CH2       4                 // Selects ADC Channel 2 (AD0.2) -> Bit 2
#define CH3       8                 // Selects ADC Channel 3 (AD0.3) -> Bit 3

// ADC Operational Control Bits
#define PDN_BIT   1<<21             // Power Down bit: Sets bit 21 to bring the ADC out of power-down mode
#define START_CON 1<<24             // Start Conversion bit: Sets bit 24 to start a conversion immediately

// ADC Global Data Register (ADDR) Bit Positions
#define DONBIT    31                // Done bit: Bit 31 in ADDR flags when conversion is complete.
#define RESULT    6                 // Result offset: 10-bit conversion data is stored at bits [15:6] in ADDR.

// Pin Function Select Register 1 (PINSEL1) Bitmasks
// Used to switch GPIO pins over to their alternative ADC functionality
#define ACH0      0x00400000        // Configures P0.27 as ADC Channel 0
#define ACH1      0x01000000        // Configures P0.28 as ADC Channel 1
#define ACH2      0x04000000        // Configures P0.29 as ADC Channel 2
#define ACH3      0x10000000        // Configures P0.30 as ADC Channel 3