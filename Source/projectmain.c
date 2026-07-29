//main.c

#include "uart0.h"
#include "delay.h"
#include "lcd.h"
#include "esp01.h"
#include "rtc.h"

// External global variables defined in other source files (likely for UART parsing)
extern char buff[100], dummy;
extern unsigned char ch, r_flag;

// Peripheral Function Prototypes
void initadc(void);
void read_adc(u32 pin, f32 *voltage, u32 *raw_val);

// Hardware Pin Defintions (LPC2148 Port 0)
#define MQ2        10   // MQ2 Smoke Sensor digital output connected to P0.10
#define BUZZER     15   // Active Buzzer connected to P0.15

// Global System Variables
f32 temp_voltage;       // Stores converted voltage reading from the temperature sensor
u8 gas, g_flag, min;     // Status tracking flags and scheduling variables
u32 adc_val;            // Stores the raw digital conversion value from the ADC
u8 temperature;         // Computed temperature value in Celsius
#include <LPC214X.h>    // Register definition header for NXP LPC2148 Microcontroller

int main()
{

        int j = 0;              // Loop counter variable used for debounce / sensor delay tracking

        // --- Hardware Initialization Phase ---
        InitUART0();
        LCD_Init();
        initadc();
        RTC_Init();

        IODIR0 |= 1 << BUZZER;   // Set P0.15 as an OUTPUT pin to drive the Buzzer

        Write_CMD_LCD(0x80);
        Write_str_LCD("ESP01 Interface");
	  delay_ms(1000);

        esp01_connectAP();      // Send AT commands to connect the ESP01 module to an Access Point (Wi-Fi)
        setrtctimeinfo(16, 7, 0); // Manually seed the RTC with initial Time: 16:07:00 (Hours, Minutes, Seconds)
        min = MIN;              // Sync internal tracking minute variable with the active hardware RTC minute register
        delay_ms(1000);

        g_flag = 1;             // Initialize gas status flag (1 = Safe / No Smoke Detected)

        while(1)
        {
                Write_CMD_LCD(0x80);    // Move LCD cursor to Row 1, Column 1
                read_adc(1, &temp_voltage, &adc_val); // Read analog channel 1 (connected to temp sensor)
                temperature = temp_voltage * 100;     // Scale voltage value to concrete Celsius scale (e.g for LM35)

                // Display Temperature on LCD Row 1
                Write_str_LCD("TEMP: ");
                Write_int_LCD(temperature);
                Write_DAT_LCD(223);     // Character code 223 prints the degree symbol (°) on typical LCDs
                Write_DAT_LCD('C');

                Write_CMD_LCD(0xC0);
                Write_str_LCD("SMOKE: ");

                if(g_flag == 1)
                {
                        Write_CMD_LCD(0xC0 + 7); // Offset cursor past "SMOKE: " string text
                        Write_str_LCD("NDETECTED"); // Print "Not Detected" safely
                }
                if(g_flag == 0)
                {
                        Write_CMD_LCD(0xC0 + 7);
                        Write_str_LCD("DETECTED "); // Print "Detected" status
                }

                //  MQ2 Sensor Polling & Alert Trigger ---
                // Condition: Check if MQ2 pin drops Low (Active-Low logic trigger) AND rate-limiting counter 'j' resets
                if((((IOPIN0 >> MQ2) & 1) == 0) && (j == 0))
                {
                        Write_CMD_LCD(0xC0 + 7);
			  Write_str_LCD("DETECTED ");

                        IOSET0 = 1 << BUZZER;              // Turn ON the buzzer alert (Drive P0.15 High)
                        esp01_sendToThingspeak(1, 2);      // Upload "Smoke Alert Status = 1" to ThingSpeak Field 2
                        IOCLR0 = 1 << BUZZER;              // Turn OFF the buzzer alert (Drive P0.15 Low)

                        delay_ms(1000);
                        j++;                               // Force rate-limiting condition
                        g_flag = 0;                        // Toggle flag to dynamic "Detected" condition
                }

                // Rate limiting control sequence for the sensor payload upload threshold
                if(j < 30)
                        j++;                           // Increment counter up to ceiling window
                else
                        j = 0;                          // Reset lock constraint interval window once hit

                // Periodic Temperature Upload Schedule (Every 3 Minutes) ---
                if(min == MIN)
                {
                        esp01_sendToThingspeak(temperature, 1); // Upload current numeric temperature data to Field 1
                        min += 3;                               // Schedule next expected transmission timestamp
                }

                // Wrap around protection handler matching real-world 60-minute hardware time limits
                if(MIN == 59)
                        min = 0;                        // Reset targeted minute checkpoint back to baseline window

                delay_ms(1000);
        }
}
                               