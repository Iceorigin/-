#ifndef _rtc_H
#define _rtc_H

#include "system.h"

/*�û�����*/
#define BKP_DRx BKP_DR1






//ʱ��ṹ��
typedef struct 
{
	u16 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 min;
	u8 sec;	
	u8 week;		 
}_calendar;					 

extern _calendar calendar;	//�����ṹ��

u8 RTC_Init(void); //RTC��ʼ��
u8 RTC_Time_Set(u16 year,u8 mon,u8 day,u8 hour,u8 min,u8 sec); //����RTCʱ��
u8 Runnian(u16 year); //�ж�����
_calendar RTC_Get(void); //��ȡRTCʱ��


#endif








