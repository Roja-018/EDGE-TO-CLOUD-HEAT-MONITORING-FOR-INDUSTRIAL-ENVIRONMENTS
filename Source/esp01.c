esp01.c

#include <string.h>  // for memset and strstr
#include "uart0.h"   // UART peripheral driver functions
#include "delay.h"   // Delay generation header
#include "lcd.h"     // LCD display control functions

// Global variables defined elsewhere (likely updated via UART ISR)
extern char buff[200];     // Global buffer array to store incoming responses from ESP-01
extern unsigned char i;    // Global index tracking the number of received characters in the buffer

void esp01_connectAP()
{

        Write_CMD_LCD(0x01);       // Clear LCD display
        Write_CMD_LCD(0x80);       // Move cursor to line 1, position 1
        Write_str_LCD("AT");       // Display "AT" on LCD
        delay_ms(1000);            // 1-second delay
        UART0_Str("AT\r\n");       // Transmit basic testing command to ESP-01 over UART

        i=0;                       // Reset the UART buffer index
        memset(buff,'\0',200);     // Clear the buffer with null characters
        while(i<4);                // Block execution until at least 4 characters are received in ISR
        delay_ms(500);             // Allow extra time for the entire message to arrive
        buff[i] = '\0';            // Explicitly null-terminate the buffer string

        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD(buff);       // Print the received ESP-01 response on the LCD
        delay_ms(2000);

        if(strstr(buff,"OK"))      // Check if the response contains the substring "OK"
        {
                Write_CMD_LCD(0xC0);   // Move cursor to line 2, position 1
                Write_str_LCD("OK");
                delay_ms(1000);
        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");// Display failure on LCD
                delay_ms(1000);
    return;                // Exit function immediately if test fails
        }

        /*Disable command echo (ATE0) --- */
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("ATE0");     // Display command name on LCD
        delay_ms(1000);
        UART0_Str("ATE0\r\n");     // Send command to turn off echoing of typed characters

        i=0; memset(buff,'\0',200);// Reset index and clear buffer
        while(i<4);                // Wait for raw confirmation characters
        delay_ms(500);
        buff[i] = '\0';            // Terminate string

        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD(buff);       // Print response
        delay_ms(2000);

        if(strstr(buff,"OK"))      // Validate success
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);
        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");
                delay_ms(1000);
                return;                // Abort if command failed
        }

        /* connection mode (Single Connection) --- */
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("AT+CIPMUX");// Display command on LCD
        delay_ms(1000);
 	    return;                // Abort if command failed
        }

        /* connection mode (Single Connection) --- */
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("AT+CIPMUX");// Display command on LCD
        delay_ms(1000);
        UART0_Str("AT+CIPMUX=0\r\n"); // Configure ESP-01 for single IP connection mode
        i=0; memset(buff,'\0',200);// Reset index and clear buffer
        while(i<4);
        delay_ms(500);
        buff[i] = '\0';

        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD(buff);       // Print response
        delay_ms(2000);

        if(strstr(buff,"OK"))      // Validate response
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);
        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");
                delay_ms(1000);
                return;                // Abort if command failed
        }

        /*Disconnect from any current Wi-Fi network */
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("AT+CWQAP"); // Display command
        delay_ms(1000);            // 1-second delay
        UART0_Str("AT+CWQAP\r\n");   // Transmit command to Quit/Disconnect from the Access Point
 	
        i=0; memset(buff,'\0',200);
        while(i<4);
        delay_ms(1500);
        buff[i] = '\0';

        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD(buff);       // Print response
        delay_ms(2000);

        if(strstr(buff,"OK"))      // Validate response
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);
        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");
                delay_ms(1000);
                return;                // Abort if disconnect fails
        }

        /* -Connect to the target Wi-Fi Access Point */
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("AT+CWJAP"); // Display command
        delay_ms(1000);

        UART0_Str("AT+CWJAP=\"Roja\",\"roja@12345\"\r\n");

        i=0; memset(buff,'\0',200);
        while(i<4);
        delay_ms(2500);
        buff[i] = '\0';
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
	   Write_str_LCD(buff);       // Print network connection response logs
        delay_ms(2000);

        if(strstr(buff,"WIFI CONNECTED")) // Verify if the module successfully authenticated and connected
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");
                delay_ms(1000);
        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");
                delay_ms(1000);
                return;                // Abort if Wi-Fi connection fails
        }
}

void esp01_sendToThingspeak(char val, int n)
{
        /*Open a TCP socket connection */
        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD("AT+CIPSTART"); // Display command
        delay_ms(1000);

        // Establish a TCP client connection targeting api.thingspeak.com on port 80
        UART0_Str("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");

        i=0; memset(buff,'\0',200);
        //while(i<5);
        delay_ms(2500);
        buff[i] = '\0';

        Write_CMD_LCD(0x01);
        Write_CMD_LCD(0x80);
        Write_str_LCD(buff);       // Display TCP connection status logs
        delay_ms(2000);
	  // Check if TCP connection is active or already running
        if(strstr(buff,"CONNECT") || strstr(buff,"ALREADY CONNECTED"))
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("OK");   // Display status
                delay_ms(1000);

                /* Prep data transmission size --- */
                Write_CMD_LCD(0x01);
                Write_CMD_LCD(0x80);
                Write_str_LCD("AT+CIPSEND"); // Display command
                delay_ms(1000);

                // Inform the ESP-01 that we plan to transmit exactly 49 bytes of raw data payload
                UART0_Str("AT+CIPSEND=49\r\n");

                i=0; memset(buff,'\0',200);

                delay_ms(500);

                /* Transmit HTTP GET Request --- */
                if(n==1)               // Target field 1 if n is equal to 1
                {
                        UART0_Str("GET /update?api_key=YO5B0XLX7CMN8E7I&field1=");
                }
                else                   // Target field 2 for any other input value
                {
                        UART0_Str("GET /update?api_key=YO5B0XLX7CMN8E7I&field2=");
                }

                UART0_Int(val);        // Transmit the integer/character data value via UART
                UART0_Str("\r\n");     // Standard HTTP carriage-return line-feed endings
        UART0_Str("\r\n");     // Blank second line required by HTTP protocols to declare end of headers

                delay_ms(5000);        // Total 10-second blocking window to ensure the remote server
                delay_ms(5000);        // receives the packet and passes back response bytes

                buff[i] = '\0';
                Write_CMD_LCD(0x01);
                Write_CMD_LCD(0x80);
		  Write_str_LCD(buff);   // Print response payload from server
                delay_ms(2000);

                if(strstr(buff,"SEND OK")) // Validate if ThingSpeak server acknowledged transmission
                {
                        Write_CMD_LCD(0x01);
                        Write_str_LCD("DATA UPDATED");
                        delay_ms(1000);
                }
                else
                {
                        Write_CMD_LCD(0x01);
                        Write_str_LCD("DATA NOT UPDATED"); // Show update failure status
                        delay_ms(1000);
                }
                Write_CMD_LCD(0x01);
        }
        else
        {
                Write_CMD_LCD(0xC0);
                Write_str_LCD("ERROR");// Show connection failure status
                delay_ms(1000);
                return;                // Exit function
        }
}
                        
