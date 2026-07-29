//delay.c


void delay_ms(unsigned int dlyMS)
{
     // input value by 12,000.
     // while loop takes approximately 1 millisecond per unit.
     dlyMS *= 12000;

     // Loop and decrement until dlyMS reaches 0, creating the time delay.
     while(dlyMS--);
}
void delay_us(unsigned int dlyUS)
{
     // input value by 12.
     // approximately 1 microsecond per unit.
     dlyUS *= 12;

     // Loop and decrement until dlyUS reaches 0, creating the time delay.
     while(dlyUS--);
}
