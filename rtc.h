#include"types.h"
void RTC_Init(void);
void getrtctimeinfo(u32 *hour,u32 *minute,u32 *second);
void displayrtctimeinfo(u32 hour,u32 minute,u32 second);
void getrtcdateinfo(u32 *date,u32 *month,u32 *year);
void displayrtcdateinfo(u32 date,u32 month,u32 year);
void setrtctimeinfo(u32 hour,u32 minute,u32 second);
void setrtcdateinfo(u32 date,u32 month,u32 year);
void getrtcday(u32 *day);
void displayrtcday(u32 day);
void setrtcday(u32 day);




