//rtc .c

#include<lpc214x.h>
#include"rtc_defines.h"
#include"types.h"
//#include"lcd.h"
#include"delay.h"
//#include"lcd_defines.h"
u8 week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
void RTC_Init(void)
{
        CCR=RTC_RESET;
        #ifndef CPU_LPC2148
        PREINT =PREINT_VAL;  //set rtc integer prescalar value
        PREFRAC= PREFRAC_VAL; //rtc fractional prescaler value
        CCR=RTC_ENABLE;       //enable rtc using external 32.678 khz crystal
        #else
         CCR=RTC_ENABLE|RTC_CLKSRC; //enable rtc and select internal pclk as clock resource
#endif
}
/*void getrtctimeinfo(u32 *hour,u32 *minute,u32 *second)
{
         *hour=HOUR;
         *minute=MIN;
         *second=SEC;
}
void displayrtctimeinfo(u32 hour,u32 minute,u32 second)
{
        //CmdLCD(CLR_LCD);
        CmdLCD(GOTO_LINE1_POSO);
        CharLCD((hour/10)+48);
        CharLCD((hour%10)+48);
        CharLCD(':');
        CharLCD((minute/10)+48);
        CharLCD((minute%10)+48);
        CharLCD(':');
        CharLCD((second/10)+48);
        CharLCD((second%10)+48);

}
void getrtcdateinfo(u32 *date,u32 *month,u32 *year)
{
        *date=DOM;
        *month=MONTH;
        *year=YEAR;
}
void displayrtcdateinfo(u32 date,u32 month,u32 year)
{
        //CmdLCD(CLR_LCD);
        CmdLCD(GOTO_LINE2_POSO);
        CharLCD((date/10)+48);
        CharLCD((date%10)+48);
        CharLCD('/');
        CharLCD((month / 10)+48);
        CharLCD((month%10)+48);
        CharLCD('/');
        u32LCD(year);
} */
void setrtctimeinfo(u32 hour,u32 minute,u32 second)
{
        HOUR=hour;  //set rtc hour register
        MIN=minute;  //set rtc minute register
        SEC=second; //set rtc second register
}
/*void setrtcdateinfo(u32 date,u32 month,u32 year)
{
        DOM=date;
        MONTH=month;
        YEAR=year;
}
void getrtcday(u32 *day)
{
        *day=DOW;
}
void displayrtcday(u32 day)
{
        //CmdLCD(CLR_LCD);
        CmdLCD(0X80+10);
        strLCD(week[day]);
}
void setrtcday(u32 day)
{
        DOM=date;
        MONTH=month;
        YEAR=year;
}
void getrtcday(u32 *day)
{
        *day=DOW;
}
void displayrtcday(u32 day)
{
        //CmdLCD(CLR_LCD);
        CmdLCD(0X80+10);
        strLCD(week[day]);
}
void setrtcday(u32 day)
{
        DOW=day;
}
  */
                                                                                                                                                                                                                                                                            