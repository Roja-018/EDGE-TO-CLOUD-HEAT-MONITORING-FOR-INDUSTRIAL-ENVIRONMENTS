//ADC.c

#include <lpc21xx.h>     // Include LPC21xx peripheral register definitions
#include "adc_defines.h" // Include user-defined ADC constants and bitmasks
#include "types.h"       // Include custom data type definitions (e.g., u32, f32)

void initadc(void)
{
    // Configure P0.22 as ADC channel 0 (or P0.28 depending on header definitions)
    PINSEL1 |= ACH0;

    // Configure the next required pin as ADC channel 1 (typically used for LM35 temperature sensor)
    PINSEL1 |= ACH1;

    // Power up the ADC operational bit (PDN) and set the ADC clock prescaler (CLK_DIV)
    ADCR = PDN_BIT | CLK_DIV;
}



void read_adc(u32 chno, f32 *eAR, u32 *adcdval)
{
    // Clear the channel selection bits [7:0] in the ADC Control Register
    ADCR &= ~(255 << 0);

    // Select the desired channel and start the conversion immediately
    ADCR |= (1 << chno) | START_CON;

    // Small delay to allow the sampling capacitor to charge properly
    delay_us(3);

    // Wait/Poll until the DONE bit in the ADC Data Register becomes 1 (Conversion complete)
    while(((ADDR >> DONBIT) & 1) == 0);

    // Clear the start bits to stop the conversion mechanism
    ADCR &= ~(START_CON);

    // Extract the 10-bit digital result from the Data Register and store it
    *adcdval = ((ADDR >> RESULT) & 1023);

    // Convert the 10-bit digital value back into its equivalent analog voltage (based on a 3.3V Vref)
    *eAR = (3.3 / 1023) * (*adcdval);
}
                                                                                                                                        