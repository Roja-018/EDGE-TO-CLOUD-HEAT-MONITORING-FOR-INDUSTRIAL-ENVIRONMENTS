//lpc21xx.h

/***********************************************************************/                                                                                   /*  This file is part of the uVision/ARM development tools             */                                                                                   /*  Copyright KEIL ELEKTRONIK GmbH 2002-2005                           */                                                                                   /***********************************************************************/                                                                                   /*                                                                     */                                                                                   /*  LPC21XX.H:  Header file for Philips LPC2114 / LPC2119              */                                                                                   /*                                      LPC2124 / LPC2129              */                                                                                   /*                                      LPC2194                        */                                                                                   /*                                                                     */                                                                                   /***********************************************************************/                                                                                                                                                                                                                                               #ifndef __LPC21xx_H                                                                                                                                         #define __LPC21xx_H                                                                                                                                                                                                                                                                                                     /* Vectored Interrupt Controller (VIC) */                                                                                                                   // Manages the priority, routing, and status flags of peripheral hardware interrupts                                                                        #define VICIRQStatus   (*((volatile unsigned long *) 0xFFFFF000)) // IRQ Status: Displays active interrupts configured as standard IRQ                      #define VICFIQStatus   (*((volatile unsigned long *) 0xFFFFF004)) // FIQ Status: Displays active interrupts configured as Fast IRQ (High priority)          #define VICRawIntr     (*((volatile unsigned long *) 0xFFFFF008)) // Raw Interrupt Status: Shows all active hardware interrupt requests regardless of masking                                                                                                                                                           #define VICIntSelect   (*((volatile unsigned long *) 0xFFFFF00C)) // Interrupt Select: Allocates each interrupt channel to either IRQ (0) or FIQ (1)        #define VICIntEnable   (*((volatile unsigned long *) 0xFFFFF010)) // Interrupt Enable: Set bits to allow an interrupt channel to trigger the CPU            #define VICIntEnClr    (*((volatile unsigned long *) 0xFFFFF014)) // Interrupt Enable Clear: Write a 1 to bits here to safely disable an interrupt channel  #define VICSoftInt     (*((volatile unsigned long *) 0xFFFFF018)) // Software Interrupt: Set bits to manually force an interrupt via software simulation    #define VICSoftIntClr  (*((volatile unsigned long *) 0xFFFFF01C)) // Software Interrupt Clear: Clear forced software interrupts                             #define VICProtection  (*((volatile unsigned long *) 0xFFFFF020)) // Protection Control: Limits VIC configuration adjustments to privileged User Mode       #define VICVectAddr    (*((volatile unsigned long *) 0xFFFFF030)) // Vector Address: Contains the memory address of the currently active ISR handler        #define VICDefVectAddr (*((volatile unsigned long *) 0xFFFFF034)) // Default Vector Address: Address of the fallback ISR handler for non-vectored IRQs                                                                                                                                                                  // Hardware Priority Vector Address Registers (Slots 0 to 15)                                                                                               // Hold the absolute function pointer locations for custom interrupt handling routines                                                                      #define VICVectAddr0   (*((volatile unsigned long *) 0xFFFFF100)) // Highest priority interrupt vector address slot                                         #define VICVectAddr1   (*((volatile unsigned long *) 0xFFFFF104))                                                                                           #define VICVectAddr2   (*((volatile unsigned long *) 0xFFFFF108))                                                                                           #define VICVectAddr3   (*((volatile unsigned long *) 0xFFFFF10C))                                                                                           #define VICVectAddr4   (*((volatile unsigned long *) 0xFFFFF110))                                                                                           #define VICVectAddr5   (*((volatile unsigned long *) 0xFFFFF114))                                                                                           #define VICVectAddr6   (*((volatile unsigned long *) 0xFFFFF118))                                                                                           #define VICVectAddr7   (*((volatile unsigned long *) 0xFFFFF11C))                                                                                           #define VICVectAddr8   (*((volatile unsigned long *) 0xFFFFF120))     
#define VICVectAddr9   (*((volatile unsigned long *) 0xFFFFF124))
#define VICVectAddr10  (*((volatile unsigned long *) 0xFFFFF128))
#define VICVectAddr11  (*((volatile unsigned long *) 0xFFFFF12C))
#define VICVectAddr12  (*((volatile unsigned long *) 0xFFFFF130))
#define VICVectAddr13  (*((volatile unsigned long *) 0xFFFFF134))
#define VICVectAddr14  (*((volatile unsigned long *) 0xFFFFF138))
#define VICVectAddr15  (*((volatile unsigned long *) 0xFFFFF13C)) // Lowest priority interrupt vector address slot

// Hardware Priority Control Slots (Slots 0 to 15)
// Bits [4:0] set the hardware ID source number; Bit 5 enables the vectored slot
#define VICVectCntl0   (*((volatile unsigned long *) 0xFFFFF200)) // Vector Control for slot 0 (Highest priority slot configuration)
#define VICVectCntl1   (*((volatile unsigned long *) 0xFFFFF204))
#define VICVectCntl2   (*((volatile unsigned long *) 0xFFFFF208))
#define VICVectCntl3   (*((volatile unsigned long *) 0xFFFFF20C))
#define VICVectCntl4   (*((volatile unsigned long *) 0xFFFFF210))
#define VICVectCntl5   (*((volatile unsigned long *) 0xFFFFF214))
#define VICVectCntl6   (*((volatile unsigned long *) 0xFFFFF218))
#define VICVectCntl7   (*((volatile unsigned long *) 0xFFFFF21C))
#define VICVectCntl8   (*((volatile unsigned long *) 0xFFFFF220))
#define VICVectCntl9   (*((volatile unsigned long *) 0xFFFFF224))
#define VICVectCntl10  (*((volatile unsigned long *) 0xFFFFF228))
#define VICVectCntl11  (*((volatile unsigned long *) 0xFFFFF22C))
#define VICVectCntl12  (*((volatile unsigned long *) 0xFFFFF230))
#define VICVectCntl13  (*((volatile unsigned long *) 0xFFFFF234))
#define VICVectCntl14  (*((volatile unsigned long *) 0xFFFFF238))
#define VICVectCntl15  (*((volatile unsigned long *) 0xFFFFF23C)) // Vector Control for slot 15 (Lowest priority slot configuration)

/* Pin Connect Block */
// Switches multi-functional pins between standard GPIO mode or specialized alternative functions (UART, SPI, I2C, ADC)
#define PINSEL0        (*((volatile unsigned long *) 0xE002C000)) // Pin Function Select 0: Configures pins P0.0 through P0.15 (2 bits per pin)
#define PINSEL1        (*((volatile unsigned long *) 0xE002C004)) // Pin Function Select 1: Configures pins P0.16 through P0.31 (2 bits per pin)
#define PINSEL2        (*((volatile unsigned long *) 0xE002C014)) // Pin Function Select 2: Mapped to control external bus pins (Port 1 pins / debug configurations)

/* General Purpose Input/Output (GPIO) */
// Directly changes physical pin states or samples external electrical voltage signals
#define IOPIN0         (*((volatile unsigned long *) 0xE0028000)) // Port 0 Pin Value: Directly reads input states or reflects forced outputs of Port 0
#define IOSET0         (*((volatile unsigned long *) 0xE0028004)) // Port 0 Output Set: Write a 1 to drive specific pins to High (Logic 1) level
#define IODIR0         (*((volatile unsigned long *) 0xE0028008)) // Port 0 Direction Control: Sets a pin as Input (0) or Output (1)
#define IOCLR0         (*((volatile unsigned long *) 0xE002800C)) // Port 0 Output Clear: Write a 1 to drive specific pins to Low (Logic 0) level

#define IOPIN1         (*((volatile unsigned long *) 0xE0028010)) // Port 1 Pin Value register
#define IOSET1         (*((volatile unsigned long *) 0xE0028014)) // Port 1 Output Set register
#define IODIR1         (*((volatile unsigned long *) 0xE0028018)) // Port 1 Direction Control register
#define IOCLR1         (*((volatile unsigned long *) 0xE002801C)) // Port 1 Output Clear register

// Alternative naming aliases for identical GPIO addresses (Supported for backwards compatibility)
#define IO0PIN         (*((volatile unsigned long *) 0xE0028000))
#define IO0SET         (*((volatile unsigned long *) 0xE0028004))
#define IO0DIR         (*((volatile unsigned long *) 0xE0028008))
#define IO0CLR         (*((volatile unsigned long *) 0xE002800C))
#define IO1PIN         (*((volatile unsigned long *) 0xE0028010))
#define IO1SET         (*((volatile unsigned long *) 0xE0028014))
#define IO1DIR         (*((volatile unsigned long *) 0xE0028018))
#define IO1CLR         (*((volatile unsigned long *) 0xE002801C))

/* Memory Accelerator Module (MAM) */
// Optimizes memory flash cycles to match fast ARM processor core speeds
#define MAMCR          (*((volatile unsigned char *) 0xE01FC000)) // MAM Control Register: Enables or disables acceleration functions entirely
#define MAMTIM         (*((volatile unsigned char *) 0xE01FC004)) // MAM Timing Register: Defines wait-states matching flash memory speeds
#define MEMMAP         (*((volatile unsigned char *) 0xE01FC040)) // Memory Mapping Control: Configures memory mapping choices (Bootloader vs Flash spaces)

/* Phase Locked Loop (PLL) */
// Multiplies internal crystal oscillator clock rates up to high system frequencies
#define PLLCON         (*((volatile unsigned char *) 0xE01FC080)) // PLL Control Register: Connects and enables the high-frequency PLL generator output
#define PLLCFG         (*((volatile unsigned char *) 0xE01FC084)) // PLL Configuration Register: Holds frequency divider and multiplier ratios
#define PLLSTAT        (*((volatile unsigned short*) 0xE01FC088)) // PLL Status Register: Displays working parameter flags and lock verification
#define PLLFEED        (*((volatile unsigned char *) 0xE01FC08C)) // PLL Feed Register: Must receive sequence 0xAA followed by 0x55 to apply changes

/* VPB Divider */
// Sets clock speed scalar fractions for low speed auxiliary internal peripherals
#define VPBDIV         (*((volatile unsigned char *) 0xE01FC100)) // Controls relationship between Core Clock (CCLK) and Peripheral Clock (PCLK)

/* Power Control */
// Controls system sleep profiles or toggles electricity feeds into individual hardware sections
#define PCON           (*((volatile unsigned char *) 0xE01FC0C0)) // Power Control: Shuts down CPU elements into Sleep/Power-Down configurations
#define PCONP          (*((volatile unsigned long *) 0xE01FC0C4)) // Power Control for Peripherals: Toggles operational voltage paths to specific internal components
/* External Interrupts */
// Monitors specific chip boundary pins to trigger hardware events from off-chip sources
#define EXTINT         (*((volatile unsigned char *) 0xE01FC140)) // External Interrupt Flag Register: Captures outstanding pending external interrupt triggers
#define EXTWAKE        (*((volatile unsigned char *) 0xE01FC144)) // External Wakeup Register: Defines which pins can rouse the chip from power down states
#define EXTMODE        (*((volatile unsigned char *) 0xE01FC148)) // External Interrupt Mode: Dictates Level-Sensitive (0) or Edge-Sensitive (1) activation
#define EXTPOLAR       (*((volatile unsigned char *) 0xE01FC14C)) // External Interrupt Polarity: Selects Active-Low/Falling Edge (0) vs Active-High/Rising Edge (1)

/* Timer 0 */
// High speed internal counter system used for timestamp operations or recurring software event cycles
#define T0IR           (*((volatile unsigned long *) 0xE0004000)) // Interrupt Register: Identifies which match or capture event generated an interrupt
#define T0TCR          (*((volatile unsigned long *) 0xE0004004)) // Timer Control Register: Used to start, pause, or hard-reset the internal counter block
#define T0TC           (*((volatile unsigned long *) 0xE0004008)) // Timer Counter: Raw running clock count value
#define T0PR           (*((volatile unsigned long *) 0xE000400C)) // Prescale Register: Defines cycle ticks required before incrementing the main counter
#define T0PC           (*((volatile unsigned long *) 0xE0004010)) // Prescale Counter: Tracks ticks toward the configured prescale value limit
#define T0MCR          (*((volatile unsigned long *) 0xE0004014)) // Match Control Register: Defines counter behavior (Reset, Interrupt, Stop) on match criteria
#define T0MR0          (*((volatile unsigned long *) 0xE0004018)) // Match Register 0: Target count threshold value slot 0
#define T0MR1          (*((volatile unsigned long *) 0xE000401C)) // Match Register 1: Target count threshold value slot 1
#define T0MR2          (*((volatile unsigned long *) 0xE0004020)) // Match Register 2: Target count threshold value slot 2
#define T0MR3          (*((volatile unsigned long *) 0xE0004024)) // Match Register 3: Target count threshold value slot 3
#define T0CCR          (*((volatile unsigned long *) 0xE0004028)) // Capture Control Register: Defines input pin transitions that capture timestamps
#define T0CR0          (*((volatile unsigned long *) 0xE000402C)) // Capture Register 0: Stores counter value at the moment capture pin trigger 0 occurred
#define T0CR1          (*((volatile unsigned long *) 0xE0004030)) // Capture Register 1: Stores counter value at the moment capture pin trigger 1 occurred
#define T0CR2          (*((volatile unsigned long *) 0xE0004034)) // Capture Register 2: Stores counter value at the moment capture pin trigger 2 occurred
#define T0CR3          (*((volatile unsigned long *) 0xE0004038)) // Capture Register 3: Stores counter value at the moment capture pin trigger 3 occurred
#define T0EMR          (*((volatile unsigned long *) 0xE000403C)) // External Match Register: Controls or reveals states of physical external match pins

/* Timer 1 */
// Identical layout twin to Timer 0, serving as an independent second tracking block
#define T1IR           (*((volatile unsigned long *) 0xE0008000))
#define T1TCR          (*((volatile unsigned long *) 0xE0008004))
#define T1TC           (*((volatile unsigned long *) 0xE0008008))
#define T1PR           (*((volatile unsigned long *) 0xE000800C))
#define T1PC           (*((volatile unsigned long *) 0xE0008010))
#define T1MCR          (*((volatile unsigned long *) 0xE0008014))
#define T1MR0          (*((volatile unsigned long *) 0xE0008018))
#define T1MR1          (*((volatile unsigned long *) 0xE000801C))
#define T1MR2          (*((volatile unsigned long *) 0xE0008020))
#define T1MR3          (*((volatile unsigned long *) 0xE0008024))
#define T1CCR          (*((volatile unsigned long *) 0xE0008028))
#define T1CR0          (*((volatile unsigned long *) 0xE000802C))
#define T1CR1          (*((volatile unsigned long *) 0xE0008030))
#define T1CR2          (*((volatile unsigned long *) 0xE0008034))
#define T1CR3          (*((volatile unsigned long *) 0xE0008038))
#define T1EMR          (*((volatile unsigned long *) 0xE000803C))

/* Pulse Width Modulator (PWM) */
// Alternates duty cycle square wave patterns to drive motors or handle variable power requirements
#define PWMIR          (*((volatile unsigned long *) 0xE0014000)) // PWM Interrupt Register
#define PWMTCR         (*((volatile unsigned long *) 0xE0014004)) // PWM Timer Control Register
#define PWMTC          (*((volatile unsigned long *) 0xE0014008)) // PWM Timer Counter
#define PWMPR          (*((volatile unsigned long *) 0xE001400C)) // PWM Prescale Register
#define PWMPC          (*((volatile unsigned long *) 0xE0014010)) // PWM Prescale Counter
#define PWMMCR         (*((volatile unsigned long *) 0xE0014014)) // PWM Match Control Register
#define PWMMR0         (*((volatile unsigned long *) 0xE0014018)) // PWM Match Register 0: Defines the base loop cycle period duration
#define PWMMR1         (*((volatile unsigned long *) 0xE001401C)) // PWM Match Register 1: Defines duty transition edge point for Channel 1
#define PWMMR2         (*((volatile unsigned long *) 0xE0014020)) // PWM Match Register 2: Defines duty transition edge point for Channel 2
#define PWMMR3         (*((volatile unsigned long *) 0xE0014024)) // PWM Match Register 3: Defines duty transition edge point for Channel 3
#define PWMMR4         (*((volatile unsigned long *) 0xE0014040)) // PWM Match Register 4: Defines duty transition edge point for Channel 4
#define PWMMR5         (*((volatile unsigned long *) 0xE0014044)) // PWM Match Register 5: Defines duty transition edge point for Channel 5
#define PWMMR6         (*((volatile unsigned long *) 0xE0014048)) // PWM Match Register 6: Defines duty transition edge point for Channel 6
#define PWMPCR         (*((volatile unsigned long *) 0xE001404C)) // PWM Control Register: Toggles single/double edge operations and enables outputs
#define PWMLER         (*((volatile unsigned long *) 0xE0014050)) // PWM Latch Enable Register: Locks updated match properties into place safely

/* Universal Asynchronous Receiver Transmitter 0 (UART0) */
// Mapped interface to communicate point-to-point via standard asynchronous serial protocols
#define U0RBR          (*((volatile unsigned char *) 0xE000C000)) // Receiver Buffer Register: Read arriving data bytes from this location (DLAB must be 0)
#define U0THR          (*((volatile unsigned char *) 0xE000C000)) // Transmit Holding Register: Write outbound data bytes here to send them (DLAB must be 0)
#define U0IER          (*((volatile unsigned char *) 0xE000C004)) // Interrupt Enable Register: Activates data arrival or transmit space interrupt options
#define U0IIR          (*((volatile unsigned char *) 0xE000C008)) // Interrupt Identification Register: Reveals which dynamic UART condition requires attention
#define U0FCR          (*((volatile unsigned char *) 0xE000C008)) // FIFO Control Register: Toggles and flushes internal hardware pipeline queues
#define U0LCR          (*((volatile unsigned char *) 0xE000C00C)) // Line Control Register: Sets data structure size, parity, and the Divisor Latch Bit (DLAB)
#define U0LSR          (*((volatile unsigned char *) 0xE000C014)) // Line Status Register: Flags data arrival, transmit states, and transmission frame bugs
#define U0SCR          (*((volatile unsigned char *) 0xE000C01C)) // Scratch Pad Register: Unlinked scratch storage area for program use
#define U0DLL          (*((volatile unsigned char *) 0xE000C000)) // Divisor Latch LSB: Lower byte factor for setting communication baud rates (DLAB=1)
#define U0DLM          (*((volatile unsigned char *) 0xE000C004)) // Divisor Latch MSB: Upper byte factor for setting communication baud rates (DLAB=1)

/* Universal Asynchronous Receiver Transmitter 1 (UART1) */
// Secondary independent UART interface featuring extra hardware-flow handshaking signals
#define U1RBR          (*((volatile unsigned char *) 0xE0010000))
#define U1THR          (*((volatile unsigned char *) 0xE0010000))
#define U1IER          (*((volatile unsigned char *) 0xE0010004))
#define U1IIR          (*((volatile unsigned char *) 0xE0010008))
#define U1FCR          (*((volatile unsigned char *) 0xE0010008))
#define U1LCR          (*((volatile unsigned char *) 0xE001000C))
#define U1MCR          (*((volatile unsigned char *) 0xE0010010)) // Modem Control Register: Manipulates hardware flow structures (RTS, DTR pins)
#define U1LSR          (*((volatile unsigned char *) 0xE0010014))
#define U1MSR          (*((volatile unsigned char *) 0xE0010018)) // Modem Status Register: Reflects inputs tracking flow pins (CTS, DSR, RI, DCD)
#define U1SCR          (*((volatile unsigned char *) 0xE001001C))
#define U1DLL          (*((volatile unsigned char *) 0xE0010000))
#define U1DLM          (*((volatile unsigned char *) 0xE0010004))

/* I2C Interface */
// Two-wire synchronous industrial communication bus interface
#define I2CONSET       (*((volatile unsigned char *) 0xE001C000)) // I2C Control Set Register: Sets flag control options (START, STOP, ACK, Enable)
#define I2STAT         (*((volatile unsigned char *) 0xE001C004)) // I2C Status Register: Displays internal operating states and transaction status codes
#define I2DAT          (*((volatile unsigned char *) 0xE001C008)) // I2C Data Register: Buffer holding active incoming/outbound communication bytes
#define I2ADR          (*((volatile unsigned char *) 0xE001C00C)) // I2C Address Register: Configures the address identity when operating as a Slave node
#define I2SCLH         (*((volatile unsigned short*) 0xE001C010)) // SCL Duty Cycle High: Adjusts clock pulse high-level width constraints
#define I2SCLL         (*((volatile unsigned short*) 0xE001C014)) // SCL Duty Cycle Low: Adjusts clock pulse low-level width constraints
#define I2CONCLR       (*((volatile unsigned char *) 0xE001C018)) // I2C Control Clear Register: Safely turns off specific running control flags

/* SPI0 (Serial Peripheral Interface 0) */
// Synchronous serial bus architecture designed for fast localized communication loops
#define S0SPCR         (*((volatile unsigned short*) 0xE0020000)) // SPI Control Register: Adjusts master/slave settings, clock phase, and data length
#define S0SPSR         (*((volatile unsigned char *) 0xE0020004)) // SPI Status Register: Flags completion of data transfers or data conflict errors
#define S0SPDR         (*((volatile unsigned short*) 0xE0020008)) // SPI Data Register: Location where read/write transaction values are processed
#define S0SPCCR        (*((volatile unsigned char *) 0xE002000C)) // SPI Clock Counter: Divides peripheral clock rates down to determine data step speed
#define S0SPINT        (*((volatile unsigned char *) 0xE002001C)) // SPI Interrupt Flag: Identifies data collection completion events
/* SPI1 (Serial Peripheral Interface 1) */
// Secondary independent SPI block instance
#define S1SPCR         (*((volatile unsigned short*) 0xE0030000))
#define S1SPSR         (*((volatile unsigned char *) 0xE0030004))
#define S1SPDR         (*((volatile unsigned short*) 0xE0030008))
#define S1SPCCR        (*((volatile unsigned char *) 0xE003000C))
#define S1SPINT        (*((volatile unsigned char *) 0xE003001C))

/* Real Time Clock */
// Dedicated calendar timekeeper designed to maintain dynamic human clock intervals independently
#define ILR            (*((volatile unsigned char *) 0xE0024000)) // Interrupt Location Register: Tracks which specific internal alarm flag tripped
#define CTC            (*((volatile unsigned short*) 0xE0024004)) // Clock Tick Counter: Raw clock divider component monitor
#define CCR            (*((volatile unsigned char *) 0xE0024008)) // Clock Control Register: Manages calibration, enabling, and test resets
#define CIIR           (*((volatile unsigned char *) 0xE002400C)) // Counter Increment Interrupt Register: Selects calendar updates that provoke interrupts
#define AMR            (*((volatile unsigned char *) 0xE0024010)) // Alarm Mask Register: Configures which time segments are ignored during alarm evaluation
#define CTIME0         (*((volatile unsigned long *) 0xE0024014)) // Consolidated Time 0: Packed read-only view of Seconds, Minutes, Hours, and Day of Week
#define CTIME1         (*((volatile unsigned long *) 0xE0024018)) // Consolidated Time 1: Packed read-only view of Day of Month, Month, and Year
#define CTIME2         (*((volatile unsigned long *) 0xE002401C)) // Consolidated Time 2: Packed read-only view of Day of Year values

// Discrete Time Element Registers (Writable directly when clock is paused)
#define SEC            (*((volatile unsigned char *) 0xE0024020))
#define MIN            (*((volatile unsigned char *) 0xE0024024))
#define HOUR           (*((volatile unsigned char *) 0xE0024028))
#define DOM            (*((volatile unsigned char *) 0xE002402C)) // Day of Month
#define DOW            (*((volatile unsigned char *) 0xE0024030)) // Day of Week
#define DOY            (*((volatile unsigned short*) 0xE0024034)) // Day of Year
#define MONTH          (*((volatile unsigned char *) 0xE0024038))
#define YEAR           (*((volatile unsigned short*) 0xE002403C))

// Dedicated Hardware Alarm Target Registers
#define ALSEC          (*((volatile unsigned char *) 0xE0024060))
#define ALMIN          (*((volatile unsigned char *) 0xE0024064))
#define ALHOUR         (*((volatile unsigned char *) 0xE0024068))
#define ALDOM          (*((volatile unsigned char *) 0xE002406C))
#define ALDOW          (*((volatile unsigned char *) 0xE0024070))
#define ALDOY          (*((volatile unsigned short*) 0xE0024074))
#define ALMON          (*((volatile unsigned char *) 0xE0024078))
#define ALYEAR         (*((volatile unsigned short*) 0xE002407C))

// Fractional Prescaler Settings (Matches the RTC timing precisely to standard 32.768kHz crystals)
#define PREINT         (*((volatile unsigned short*) 0xE0024080)) // Prescaler Integer Value component
#define PREFRAC        (*((volatile unsigned short*) 0xE0024084)) // Prescaler Fractional Value component

/* A/D Converter */
// Converts incoming hardware voltage lines into proportional digital values
#define ADCR           (*((volatile unsigned long *) 0xE0034000)) // ADC Control Register: Handles channel choices, clock dividers, and conversion starts
#define ADDR           (*((volatile unsigned long *) 0xE0034004)) // ADC Data Register: Stores conversion output flags alongside the 10-bit value data

/* CAN Acceptance Filter RAM */
// Storage block indexing rules for identifying incoming Control Area Network (CAN) frames
#define AFRAM          (*((volatile unsigned long *) 0xE0038000)) // Mapped memory start location for CAN identifier index tables

/* CAN Acceptance Filter */
// Routing filter mechanism sorting or discarding arriving network messages based on structural address IDs
#define AFMR           (*((volatile unsigned long *) 0xE003C000)) // Acceptance Filter Mode Register: Disables, bypasses, or configures routing paths
#define SFF_sa         (*((volatile unsigned long *) 0xE003C004)) // Standard Frame Start Address: Start offset for 11-bit identifier list
#define SFF_GRP_sa     (*((volatile unsigned long *) 0xE003C008)) // Standard Group Start Address: Start offset for 11-bit range identity groups
#define EFF_sa         (*((volatile unsigned long *) 0xE003C00C)) // Extended Frame Start Address: Start offset for 29-bit identifier list
#define EFF_GRP_sa     (*((volatile unsigned long *) 0xE003C010)) // Extended Group Start Address: Start offset for 29-bit range identity groups
#define ENDofTable     (*((volatile unsigned long *) 0xE003C014)) // End of Table Address pointer boundary value
#define LUTerrAd       (*((volatile unsigned long *) 0xE003C018)) // Look-Up Table Error Address location holder
#define LUTerr         (*((volatile unsigned long *) 0xE003C01C)) // Look-Up Table Error Status register

/* CAN Central Registers */
// Macro views tracking states across all combined network channel slots simultaneously
#define CANTxSR        (*((volatile unsigned long *) 0xE0040000)) // Central Transmit Status Register flags
#define CANRxSR        (*((volatile unsigned long *) 0xE0040004)) // Central Receive Status Register flags
#define CANMSR         (*((volatile unsigned long *) 0xE0040008)) // Central Miscellaneous Status Register flags

/* CAN Controller 1 (CAN1) */
// First independent Controller Area Network module interface
#define C1MOD          (*((volatile unsigned long *) 0xE0044000)) // Mode Control Register: Puts the controller into Reset, Operational, or Self-Test modes
#define C1CMR          (*((volatile unsigned long *) 0xE0044004)) // Command Register: Issues transmit execution or data clearing commands
#define C1GSR          (*((volatile unsigned long *) 0xE0044008)) // Global Status Register: General device working parameter summary
#define C1ICR          (*((volatile unsigned long *) 0xE004400C)) // Interrupt Capture Register: Identifies exact network condition events causing alerts
#define C1IER          (*((volatile unsigned long *) 0xE0044010)) // Interrupt Enable Register: Toggles interrupt channels
#define C1BTR          (*((volatile unsigned long *) 0xE0044014)) // Bus Timing Register: Establishes communication baud rates and sample segment details
#define C1EWL          (*((volatile unsigned long *) 0xE0044018)) // Error Warning Limit: Establishes internal connection failure monitoring trip levels
#define C1SR           (*((volatile unsigned long *) 0xE004401C)) // Status Register: Details transmission queues and data packet readiness
#define C1RFS          (*((volatile unsigned long *) 0xE0044020)) // Receive Frame Status: Structural parameters of incoming data packet
#define C1RID          (*((volatile unsigned long *) 0xE0044024)) // Receive Identifier: Identifies address value tracking arriving message
#define C1RDA          (*((volatile unsigned long *) 0xE0044028)) // Receive Data A: First 4 bytes of data payload
#define C1RDB          (*((volatile unsigned long *) 0xE004402C)) // Receive Data B: Final 4 bytes of data payload

// Transmit Buffer Set 1
#define C1TFI1         (*((volatile unsigned long *) 0xE0044030)) // Transmit Frame Info 1
#define C1TID1         (*((volatile unsigned long *) 0xE0044034)) // Transmit Identifier 1
#define C1TDA1         (*((volatile unsigned long *) 0xE0044038)) // Transmit Data A 1
#define C1TDB1         (*((volatile unsigned long *) 0xE004403C)) // Transmit Data B 1

// Transmit Buffer Set 2
#define C1TFI2         (*((volatile unsigned long *) 0xE0044040))
#define C1TID2         (*((volatile unsigned long *) 0xE0044044))
#define C1TDA2         (*((volatile unsigned long *) 0xE0044048))
#define C1TDB2         (*((volatile unsigned long *) 0xE004404C))

// Transmit Buffer Set 3
#define C1TFI3         (*((volatile unsigned long *) 0xE0044050))
#define C1TID3         (*((volatile unsigned long *) 0xE0044054))
#define C1TDA3         (*((volatile unsigned long *) 0xE0044058))
#define C1TDB3         (*((volatile unsigned long *) 0xE004405C))

/* CAN Controller 2 (CAN2) */
// Second independent Controller Area Network module interface
#define C2MOD          (*((volatile unsigned long *) 0xE0048000))
#define C2CMR          (*((volatile unsigned long *) 0xE0048004))
#define C2GSR          (*((volatile unsigned long *) 0xE0048008))
#define C2ICR          (*((volatile unsigned long *) 0xE004800C))
#define C2IER          (*((volatile unsigned long *) 0xE0048010))
#define C2BTR          (*((volatile unsigned long *) 0xE0048014))
#define C2EWL          (*((volatile unsigned long *) 0xE0048018))
#define C2SR           (*((volatile unsigned long *) 0xE004801C))
#define C2RFS          (*((volatile unsigned long *) 0xE0048020))
#define C2RID          (*((volatile unsigned long *) 0xE0048024))
#define C2RDA          (*((volatile unsigned long *) 0xE0048028))
#define C2RDB          (*((volatile unsigned long *) 0xE004802C))
#define C2TFI1         (*((volatile unsigned long *) 0xE0048030))
#define C2TID1         (*((volatile unsigned long *) 0xE0048034))
#define C2TDA1         (*((volatile unsigned long *) 0xE0048038))
#define C2TDB1         (*((volatile unsigned long *) 0xE004803C))
#define C2TFI2         (*((volatile unsigned long *) 0xE0048040))
#define C2TID2         (*((volatile unsigned long *) 0xE0048044))
#define C2TDA2         (*((volatile unsigned long *) 0xE0048048))
#define C2TDB2         (*((volatile unsigned long *) 0xE004804C))
#define C2TFI3         (*((volatile unsigned long *) 0xE0048050))
#define C2TID3         (*((volatile unsigned long *) 0xE0048054))
#define C2TDA3         (*((volatile unsigned long *) 0xE0048058))
#define C2TDB3         (*((volatile unsigned long *) 0xE004805C))

/* CAN Controller 3 (CAN3) */
// Third independent Controller Area Network module interface
#define C3MOD          (*((volatile unsigned long *) 0xE004C000))
#define C3CMR          (*((volatile unsigned long *) 0xE004C004))
#define C3GSR          (*((volatile unsigned long *) 0xE004C008))
#define C3ICR          (*((volatile unsigned long *) 0xE004C00C))
#define C3IER          (*((volatile unsigned long *) 0xE004C010))
#define C3BTR          (*((volatile unsigned long *) 0xE004C014))
#define C3EWL          (*((volatile unsigned long *) 0xE004C018))
#define C3SR           (*((volatile unsigned long *) 0xE004C01C))
#define C3RFS          (*((volatile unsigned long *) 0xE004C020))
#define C3RID          (*((volatile unsigned long *) 0xE004C024))
#define C3RDA          (*((volatile unsigned long *) 0xE004C028))
#define C3RDB          (*((volatile unsigned long *) 0xE004C02C))
#define C3TFI1         (*((volatile unsigned long *) 0xE004C030))
#define C3TID1         (*((volatile unsigned long *) 0xE004C034))
#define C3TDA1         (*((volatile unsigned long *) 0xE004C038))
#define C3TDB1         (*((volatile unsigned long *) 0xE004C03C))
#define C3TFI2         (*((volatile unsigned long *) 0xE004C040))
#define C3TID2         (*((volatile unsigned long *) 0xE004C044))
#define C3TDA2         (*((volatile unsigned long *) 0xE004C048))
#define C3TDB2         (*((volatile unsigned long *) 0xE004C04C))
#define C3TFI3         (*((volatile unsigned long *) 0xE004C050))
#define C3TID3         (*((volatile unsigned long *) 0xE004C054))
#define C3TDA3         (*((volatile unsigned long *) 0xE004C058))
#define C3TDB3         (*((volatile unsigned long *) 0xE004C05C))

/* CAN Controller 4 (CAN4) */
// Fourth independent Controller Area Network module interface
#define C4MOD          (*((volatile unsigned long *) 0xE0050000))
#define C4CMR          (*((volatile unsigned long *) 0xE0050004))
#define C4GSR          (*((volatile unsigned long *) 0xE0050008))
#define C4ICR          (*((volatile unsigned long *) 0xE005000C))
#define C4IER          (*((volatile unsigned long *) 0xE0050010))
#define C4BTR          (*((volatile unsigned long *) 0xE0050014))
#define C4EWL          (*((volatile unsigned long *) 0xE0050018))
#define C4SR           (*((volatile unsigned long *) 0xE005001C))
#define C4RFS          (*((volatile unsigned long *) 0xE0050020))
#define C4RID          (*((volatile unsigned long *) 0xE0050024))
#define C4RDA          (*((volatile unsigned long *) 0xE0050028))
#define C4RDB          (*((volatile unsigned long *) 0xE005002C))
#define C4TFI1         (*((volatile unsigned long *) 0xE0050030))
#define C4TID1         (*((volatile unsigned long *) 0xE0050034))
#define C4TDA1         (*((volatile unsigned long *) 0xE0050038))
#define C4TDB1         (*((volatile unsigned long *) 0xE005003C))
#define C4TFI2         (*((volatile unsigned long *) 0xE0050040))
#define C4TID2         (*((volatile unsigned long *) 0xE0050044))
#define C4TDA2         (*((volatile unsigned long *) 0xE0050048))
#define C4TDB2         (*((volatile unsigned long *) 0xE005004C))
#define C4TFI3         (*((volatile unsigned long *) 0xE0050050))
#define C4TID3         (*((volatile unsigned long *) 0xE0050054))
#define C4TDA3         (*((volatile unsigned long *) 0xE0050058))
#define C4TDB3         (*((volatile unsigned long *) 0xE005005C))

/* Watchdog */
// Safety monitoring loop designed to hard-reset the processor if software crashes or freezes
#define WDMOD          (*((volatile unsigned char *) 0xE0000000)) // Watchdog Mode Register: Toggles operational states and enabling parameters
#define WDTC           (*((volatile unsigned long *) 0xE0000004)) // Watchdog Timer Constant: Sets expiration time limits before a crash reset triggers
#define WDFEED         (*((volatile unsigned char *) 0xE0000008)) // Watchdog Feed Register: Must receive alternating sequence bytes 0xAA and 0x55 to reset timer count
#define WDTV           (*((volatile unsigned long *) 0xE000000C)) // Watchdog Timer Value: Displays current running value countdown status

#endif  // __LPC21xx_H