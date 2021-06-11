#include "rtc.h"


//�·�
u8 mon_table[12]={31,28,31,30,31,30,31,31,30,31,30,31};




/*	RTC��ʼ��
 *	����ֵ��0�ɹ� ��1ʧ��
 */
u8 RTC_Init(void)
{
	
	u8 temp=0;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��  
	
	PWR_BackupAccessCmd(ENABLE);	//ʹ�ܺ󱸼Ĵ�������
  
	//����Ƿ��һ������ʱ��
	if (BKP_ReadBackupRegister(BKP_DRx) != 0xFF00)		//��ָ���ĺ󱸼Ĵ����ж�������:��������д���ָ�����ݲ����
	{	 			
		RCC_LSEConfig(RCC_LSE_ON);	//�����ⲿ���پ���(LSE),ʹ��������پ���
		while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET&&temp<250)	//���ָ����RCC��־λ�������,�ȴ����پ������
		{
			temp++;
			delay_ms(10);
		}
		if(temp>=250)
			return 1;//��ʼ��ʱ��ʧ��,����������	
    
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); //����RTCʱ��(RTCCLK),ѡ��LSE��ΪRTCʱ��    
		RCC_RTCCLKCmd(ENABLE);	//ʹ��RTCʱ��  
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		
		RTC_WaitForSynchro();		//�ȴ�RTC�Ĵ���ͬ��  
		RTC_ITConfig(RTC_IT_SEC, ENABLE);		//ʹ��RTC���ж�		
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		
		RTC_EnterConfigMode(); // ��������	
		RTC_SetPrescaler(32767); //����RTCԤ��Ƶ ��Ƶϵ���Զ�+1
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		
		RTC_SetCounter(0); //��ʼ��Ϊ0
		RTC_ExitConfigMode(); //�˳�����ģʽ  
		BKP_WriteBackupRegister(BKP_DRx,0xFF00);//��ָ���ĺ󱸼Ĵ�����д���û���������
	}
	else//ϵͳ������ʱ
	{
		RTC_WaitForSynchro();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д�������
	}		    				     
	
	PWR_BackupAccessCmd(DISABLE); //�رպ󱸼Ĵ�������
	return 0; //ok

}		 				    

/*	�ж�����
 *	����ֵ��1���� 0ƽ��
 */

u8 Runnian(u16 year)
{
	if(year%4==0)
	{
		if(year%100==0)
		{
			if(year%400==0)return 1;
			else return 0;
		}
		else return 1;
	}
	else return 0;
}

/*	����RTCʱ��
 *	����ֵ��0�ɹ� 1ʧ��
 */
 
u8 RTC_Time_Set(u16 year,u8 month,u8 day,u8 hour,u8 min,u8 sec)
{
	u16 t;
	u32 time;
	
	if(year<1970||year>2099)
		return 1;	
	
	//������
	for(t=1970;t<year;t++)
	{
		if(Runnian(t))
			time += 31622400; //�����������
		else
			time += 31536000; //ƽ���������
	}
	//������
	if(Runnian(year))mon_table[1]=29;//����2�¶�1��
	for(t=0;t<month-1;t++)
	{
			time += mon_table[t]*86400;//ÿ���������
	}	
	mon_table[1]=28;
	//������
	time += (day-1)*86400;
	//����ʱ
	time += hour *3600;
	//�����
	time += min *60;
	//������
	time += sec;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��  
	PWR_BackupAccessCmd(ENABLE);	//ʹ��RTC�ͺ󱸼Ĵ������� 
	RTC_SetCounter(time);	//����RTC��������ֵ
	RTC_WaitForLastTask();	//�ȴ����һ�ζ�RTC�Ĵ�����д������� 
	PWR_BackupAccessCmd(DISABLE); //�ر�RTC�ͺ󱸼Ĵ�������
	return 0;
}


/* 	��ȡRTCʱ��
 *	����ֵ��ʱ��ṹ��
 */

_calendar RTC_Get(void)
{
	u16 data;
	u32 temp;
	u32 rtc_data;
	u16 temp1; 
	_calendar calendar;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	//ʹ��PWR��BKP����ʱ��  
	PWR_BackupAccessCmd(ENABLE);	//ʹ��RTC�ͺ󱸼Ĵ������� 
	
	rtc_data = RTC_GetCounter();
	//�õ�������
	temp = rtc_data/86400; 
	
	//�ж��Ƿ�ﵽ1������
	if(temp)
	{
		data=1970;
		//�������
		while(temp >= 365)
		{
			
			if(Runnian(data))
			{
				if(temp >= 366)
				{
					temp -= 366;
					data++;
				}
				else 
					break;		
			}
			else
			{
				temp -= 365;
				data++;
			}
		}
		calendar.year=data;
		temp1=temp+1;
		//�����·�
		data=0;
		if(Runnian(calendar.year))mon_table[1]=29;//����2�¶�1��
		while(temp >= 28)
		{
			temp-=mon_table[data];
			data++;
		}
		calendar.month=data+1;
		//������
		calendar.day=temp+1;	
	}
	
	//����ʱ/��/��
	temp=rtc_data%86400;
	calendar.hour=temp/3600;     	//Сʱ
	calendar.min=(temp%3600)/60; 	//����	
	calendar.sec=(temp%3600)%60; 	//����
	
	//��������
	data=0;
	data=(calendar.year-1)
	+((calendar.year-1)/4)
	-((calendar.year-1)/100)
	+((calendar.year-1)/400)
	+temp1;
	
	calendar.week=data;
	
	
	
	return calendar;
}




















