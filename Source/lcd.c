//lcd.c

#include <LPC21xx.h>

#include "delay.h"
#include "lcd.h"
#include "defines.h"
#define LCD_DAT 16   // Starting bit position for data lines (typically P0.16 to P0.23 for 8-bit mode)
#define RS 8         // Register Select line on Pin P0.8
#define RW 10        // Read/Write line on Pin P0.10
#define EN 9         // Enable line on Pin P0.9
void LCD_Init(void)
{

    // Configure LCD Data pins [P0.23:P0.16] as outputs
    WRITEBYTE(IODIR0, LCD_DAT, 0XFF);

    // Configure Control Pins (RW, RS, EN) as outputs in the IODIR0 register
    SETBIT(IODIR0, RW);
    SETBIT(IODIR0, RS);
    SETBIT(IODIR0, EN);

    // Hardware stabilization delay following power-up
    delay_ms(15);

    // Standard HD44780 initialization sequence to reset the controller state
    Write_CMD_LCD(0X30);
    delay_ms(5);
    Write_CMD_LCD(0X30);
    delay_us(100);
    Write_CMD_LCD(0X30);

    // 0x38: Configures the display for 8-bit interface, 2 display lines, and 5x7 font style
    Write_CMD_LCD(0X38);

    // 0x0C: Turns the display ON, cursor OFF, and cursor blink OFF
    Write_CMD_LCD(0X0C);

    // 0x01: Sends command to clear the entire screen display
    Write_CMD_LCD(0X01);

    // 0x06: Sets Entry Mode - Increments the cursor automatically to the right after writing a character
 Write_CMD_LCD(0X06);
}

void Write_CMD_LCD(char cmd)
{
    // Clear RS pin to 0 to specify an Instruction/Command register write
    SCLRBIT(IOCLR0, RS);

    // Push the byte out via the shared bus writer
    Write_LCD(cmd);
}

void Write_DAT_LCD(char dat)
{
    // Set RS pin to 1 to specify a Data register write
    SSETBIT(IOSET0, RS);

    // Push the byte out via the shared bus writer
    Write_LCD(dat);
}
void Write_LCD(char data)
{

    // Clear RW pin to 0 to select Write Mode
    SCLRBIT(IOCLR0, RW);

    // Load the 8-bit data character onto the mapped output port pins
    WRITEBYTE(IOPIN0, LCD_DAT, data);
    SSETBIT(IOSET0, EN);
    delay_us(1); // Keep Enable line high briefly to satisfy minimum pulse width requirement
}
void Write_LCD(char data)
{
	 // Clear RW pin to 0 to select Write Mode
    SCLRBIT(IOCLR0, RW);

    // Load the 8-bit data character onto the mapped output port pins
    WRITEBYTE(IOPIN0, LCD_DAT, data);
    SSETBIT(IOSET0, EN);
    delay_us(1); // Keep Enable line high briefly to satisfy minimum pulse width requirement

    // Bring Enable line back low to latch the data into the LCD controller internal memory
    SCLRBIT(IOCLR0, EN);

    // Execution guard delay to let the LCD controller process the incoming write internally
    delay_ms(2);
}
void Write_str_LCD(char *p)
{
    // Increment through characters until the null character '\0' is discovered
    while(*p)
        Write_DAT_LCD(*p++); // Print character and advance pointer
}
void Write_int_LCD(signed int n)
{
    char a[10], i = 0; // Temp string buffer and index tracker

    // If the integer is negative, print the minus glyph and switch variable to absolute value
    if(n < 0)
    {
        Write_DAT_LCD('-');
        n = -n;
    }

    // Deconstruct the number into individual numeric characters backwards via base-10 modulo
    do
    {
        a[i++] = n % 10 + 48; // Store individual digit converted to its ASCII character value (+48 offset)
        n = n / 10;           // Shift integer over to process next placeholder digit
    } while(n);

    // Reverse the order out of the storage array to print left-to-right correctly
    for(; i > 0; i--)
        Write_DAT_LCD(a[i-1]);
}

void Write_float_LCD(float f, char i)
{
    // Cast float to integer variable to discard trailing floating digits safely
      unsigned long int n = f;

    // Display the whole number base value first
    Write_int_LCD(n);

    // Output the standard decimal point delimiter
    Write_DAT_LCD('.');

    // Loop through the requested fractional space count precision
    for(; i > 0; i--)
    {
        f = f * 10;
        n = f;
        Write_DAT_LCD(n % 10 + 48); // Isolate the final digit step, mask to ASCII, and write to the display
    }
}