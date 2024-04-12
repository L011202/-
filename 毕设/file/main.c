#include "usart.h"					//�����Զ��崮��ͷ�ļ�
//#include "stdio.h"				//ͷ�ļ�����ֱ�Ӷ�����usart.h������
//#include "stdlib.h"				//ͷ�ļ�����ֱ�Ӷ�����usart.h������
#include "string.h"					
#include "math.h"
#include "lcd.h"					//lcd�Զ���ͷ�ļ�
#include "DHT11.h"					//��ʪ�ȴ�����DHT11�Զ���ͷ�ļ�



code char  CWJAP_buff[35] = "AT+CWJAP=\"liang\",\"liangliang\"\r\n";  //����WiFi������WiFi���ƺ�����Ҫ����ΪĬ�ϵ�
code char  CWMODE_buff[15] = "AT+CWMODE=1\r\n";  //����WiFiģ��ΪSTAģʽ
code char  CIPSTART_API_buff[] = "AT+CIPSTART=1,\"TCP\",\"api.seniverse.com\",80\r\n";  //����TCP����
//code char  CIPSTART_APP_buff[] = "AT+CIPSTART=2,\"TCP\",\"192.168.43.1\",8899\r\n";  //����TCP���ӣ��˿ں�Ϊ8899,��Ϊ�ֻ����Ӳ���
//code char  CIPSTART_APP_buff[] = "AT+CIPSTART=2,\"TCP\",\"192.168.43.1\",8899\r\n";  //����TCP���ӣ��˿ں�Ϊ8899,��ҫ�ֻ����Ӳ���
code char  CIPSTART_APP_buff[] = "AT+CIPSTART=2,\"TCP\",\"192.168.137.57\",8899\r\n";  //����TCP���ӣ��˿ں�Ϊ8899,С���ֻ����Ӳ���
code char  CIPSTART_buff[] = "AT+CIPSTART=1,\"TCP\",\"api.seniverse.com\",80\r\n";  //����TCP����
code char  CIPSEND_buff[] = "AT+CIPSEND\r\n";
//AT+CIPSEND=%d,%d
code char  CIPSEND_API_buff[] = "AT+CIPSEND=1,128\r\n";
// code char  CIPSEND_API_buff[] = "AT+CIPSEND=1,128";
code char  GET_API_buff[] = "GET https://api.seniverse.com/v3/weather/daily.json?key=SWaCmu3LmzT_kS21g&location=zhengzhou&language=en&unit=c&start=0&days=1\r\n";
//zh-Hans
sbit  BEEP  =  P2^3;   //������
sbit  LED  =  P1^0;  //led
sbit  MQ2_IN  =  P2^1;  //led


extern uchar rec_dat[10];


//void delay1ms(unsigned int c)   //��� 0us
//{
//    unsigned int a,b;
//	for (; c>0; c--)
//	{
//		 for (b=199;b>0;b--)
//		 {
//		  	for(a=1;a>0;a--);
//		 }      
//	}  	
//}

 unsigned char beek_flag=0;
 unsigned char sys_cnt=0;
 idata  char  str_buff[35]="\0";
 idata char  send_len_buff[25] = "AT+CIPSEND=1,128";
 
 idata  char  date_buff[12]="\0";
 idata  char  temp_high_buff[10]="\0";	
 idata  char  temp_low_buff[10]="\0";
 idata  char  text_day[20]="\0";	 
 idata  char  text_night[20]="\0";	 
 idata  char  wind_speed[20]="\0";	 
 idata  char  wind_scale[20]="\0";	 
 idata  char  rainfall[20]="\0"; 
 
void delayms(unsigned int xms)   //��ʱ����
{
	unsigned int x;
	unsigned char y;
	for(x = xms; x > 0; x--)
		for(y = 124; y>0; y--);//11.0592MHz: 114  //12MHz: 124
}


 unsigned char resvie_usart_dat;//[15]="\0",resvie_usart_len=0,save_flag=0;
 xdata unsigned char	resvie_usart_dat_buff[500]="\0";//="[{\"date\":\"2024-04-08\",\"text_day\":\"Cloudy\",\"code_day\":\"4\",\"text_night\":\"Cloudy\",\"code_night\":\"4\",\"high\":\"26\",\"low\":\"12\",\"rainfall\":\"0.00\",\"precip\":\"0.00\",\"wind_direction\":\"E\",\"wind_direction_degree\":\"90\",\"wind_speed\":\"8.4\",\"wind_scale\":\"2\",\"humidity\":\"65\"}],\"last_update\":\"2024-04-08T08:00:00+08:00\"}]}1,CLOSED";

 unsigned short int	resvie_usart_dat_buff_len=0;
 unsigned char  resvie_usart_save_dat_flag=0;

void dat_resive_fun(void)
{
	 unsigned char i=0;
	char *str_p;
	str_p = strstr(resvie_usart_dat_buff,"date");
	memcpy(date_buff, str_p+7, 10);    for(i=0;i<10;i++){if(date_buff[i]=='"')date_buff[i]=0;  }
	
	str_p = strstr(resvie_usart_dat_buff,"high");
	memcpy(temp_high_buff, str_p+7, 3);	 for(i=0;i<3;i++){if(temp_high_buff[i]=='"')temp_high_buff[i]=0;  }
	
	str_p = strstr(resvie_usart_dat_buff,"low");
	memcpy(temp_low_buff, str_p+6, 3);		for(i=0;i<3;i++){if(temp_low_buff[i]=='"')temp_low_buff[i]=0;  }
	
	str_p = strstr(resvie_usart_dat_buff,"text_day");
	memcpy(text_day, str_p+11, 10);		for(i=0;i<10;i++){if(text_day[i]=='"')text_day[i]=0;  }	
	
	str_p = strstr(resvie_usart_dat_buff,"text_night");
	memcpy(text_night, str_p+13, 10);		for(i=0;i<10;i++){if(text_night[i]=='"')text_night[i]=0;  }		
	
	str_p = strstr(resvie_usart_dat_buff,"wind_speed");
	memcpy(wind_speed, str_p+13, 5);		for(i=0;i<5;i++){if(wind_speed[i]=='"')wind_speed[i]=0;  }
	
	str_p = strstr(resvie_usart_dat_buff,"wind_scale");
	memcpy(wind_scale, str_p+13, 5);		for(i=0;i<5;i++){if(wind_scale[i]=='"')wind_scale[i]=0;  }		
	
	str_p = strstr(resvie_usart_dat_buff,"rainfall");
	memcpy(rainfall, str_p+11, 5);		for(i=0;i<5;i++){if(wind_scale[i]=='"')wind_scale[i]=0;  }		
}


void re_tcp_conect(void)
{
	unsigned char sys_fun_cnt=0;
		resvie_usart_dat_buff_len=0; 
	Send_Str(CIPSTART_APP_buff);   //�����ֻ�app��������
	delayms(2000);
	while(strstr(resvie_usart_dat_buff,"OK")==0 && sys_fun_cnt<5){ delayms(2000);	 sys_fun_cnt++;}	
 	memset(resvie_usart_dat_buff,0,500);		
	delayms(2000);	

	
	sys_fun_cnt=0;
	memset(resvie_usart_dat_buff,0,500);
	resvie_usart_dat_buff_len=0;
	Send_Str(CWMODE_buff);           // ����Ϊstaģʽ
	delayms(2000);
	while(strstr(resvie_usart_dat_buff,"OK")==0 &&sys_fun_cnt<5){ delayms(2000);	 sys_fun_cnt++;}	
	memset(resvie_usart_dat_buff,0,500);
		delayms(3000);		
}

void send_API(void)
{
	//	send_len_buff[20] = "AT+CIPSEND=2,128";
	
	if(beek_flag)
	{
		memset(str_buff,0,35); memset(send_len_buff,0,25);
		sprintf(str_buff,"����!!!!!!!!!!!!!!!!!!!! ");//rec_dat
		sprintf(send_len_buff,"AT+CIPSEND=2,%d\r\n",(int)(strlen(str_buff)));
		Send_Str(send_len_buff);
		resvie_usart_dat_buff_len=0;	delayms(1500);	
		memset(resvie_usart_dat_buff,0,500);
		Send_Str(str_buff);  delayms(1000);		
		if(strstr(resvie_usart_dat_buff,"ERROR"))re_tcp_conect();	
	}
	
	memset(str_buff,0,35); memset(send_len_buff,0,25);
	sprintf(str_buff,"Temp,Humi:%s ",rec_dat);//rec_dat
	sprintf(send_len_buff,"AT+CIPSEND=2,%d\r\n",(int)(strlen(str_buff)));
    Send_Str(send_len_buff);
	resvie_usart_dat_buff_len=0;	delayms(1500);	
	memset(resvie_usart_dat_buff,0,500);
    Send_Str(str_buff);  delayms(1000);		
	if(strstr(resvie_usart_dat_buff,"ERROR"))re_tcp_conect();
	
	memset(str_buff,0,35); memset(send_len_buff,0,25);
	sprintf(str_buff,"date:%s",date_buff);
	sprintf(send_len_buff,"AT+CIPSEND=2,%d\r\n",(int)(strlen(str_buff)));
    Send_Str(send_len_buff);
	resvie_usart_dat_buff_len=0;	delayms(1500);	
	memset(resvie_usart_dat_buff,0,500);
    Send_Str(str_buff);  delayms(1000);
	if(strstr(resvie_usart_dat_buff,"ERROR"))re_tcp_conect();
	//	  Send_Str("\r\n");

	memset(str_buff,0,35); memset(send_len_buff,0,25);	
	sprintf(str_buff,"temp:%s~%s",temp_low_buff,temp_high_buff);//set_dis_down,csb1_dis,set:%.0fcm, 
	sprintf(send_len_buff,"AT+CIPSEND=2,%d\r\n",(int)(strlen(str_buff)));
    Send_Str(send_len_buff);	
	resvie_usart_dat_buff_len=0;	delayms(1500);	
	memset(resvie_usart_dat_buff,0,500);
    Send_Str(str_buff); delayms(1000);
	if(strstr(resvie_usart_dat_buff,"ERROR"))re_tcp_conect();
	//	  Send_Str("\r\n");

	memset(str_buff,0,35); memset(send_len_buff,0,25);	
	sprintf(str_buff,"text_day:%s",text_day);//set_dis_down,csb1_dis,set:%.0fcm, 
	sprintf(send_len_buff,"AT+CIPSEND=2,%d\r\n",(int)(strlen(str_buff)));
    Send_Str(send_len_buff);
	resvie_usart_dat_buff_len=0;	delayms(1500);		
	memset(resvie_usart_dat_buff,0,500);
    Send_Str(str_buff);delayms(1000);
	if(strstr(resvie_usart_dat_buff,"ERROR"))re_tcp_conect();
	//	  Send_Str("\r\n");

	memset(str_buff,0,35); memset(send_len_buff,0,25);
	sprintf(str_buff,"text_night:%s",text_night);//set_dis_down,csb1_dis,set:%.0fcm, 
	sprintf(send_len_buff,"AT+CIPSEND=2,%d\r\n",(int)(strlen(str_buff)));
    Send_Str(send_len_buff);
	resvie_usart_dat_buff_len=0;	delayms(1500);	
	memset(resvie_usart_dat_buff,0,500);
    Send_Str(str_buff);delayms(1000);
	if(strstr(resvie_usart_dat_buff,"ERROR"))re_tcp_conect();
	//	  Send_Str("\r\n");

	memset(str_buff,0,35); memset(send_len_buff,0,25);
	sprintf(str_buff,"wind_sped:%sm/2",wind_speed);//set_dis_down,csb1_dis,set:%.0fcm, 
	sprintf(send_len_buff,"AT+CIPSEND=2,%d\r\n",(int)(strlen(str_buff)));
    Send_Str(send_len_buff);	
	resvie_usart_dat_buff_len=0;	delayms(1500);
	memset(resvie_usart_dat_buff,0,500);	
    Send_Str(str_buff);	delayms(1000);
	if(strstr(resvie_usart_dat_buff,"ERROR"))re_tcp_conect();
	//	  Send_Str("\r\n");
	
	memset(str_buff,0,35); memset(send_len_buff,0,25);
	sprintf(str_buff,"wind_scale:%s  ",wind_scale);//set_dis_down,csb1_dis,set:%.0fcm, 
	sprintf(send_len_buff,"AT+CIPSEND=2,%d\r\n",(int)(strlen(str_buff)));
    Send_Str(send_len_buff);	
	resvie_usart_dat_buff_len=0;	delayms(1500);
	memset(resvie_usart_dat_buff,0,500);	
    Send_Str(str_buff);delayms(1000);
	if(strstr(resvie_usart_dat_buff,"ERROR"))re_tcp_conect();
	//	  Send_Str("\r\n");

	memset(str_buff,0,35); 
	memset(send_len_buff,0,25);
	sprintf(str_buff,"rainfall:%s",rainfall);//set_dis_down,csb1_dis,set:%.0fcm, 
	sprintf(send_len_buff,"AT+CIPSEND=2,%d\r\n",(int)(strlen(str_buff)+2));
    Send_Str(send_len_buff);	
	resvie_usart_dat_buff_len=0;	
	delayms(1500);	
	if(strstr(resvie_usart_dat_buff,"OK")==0)re_tcp_conect();	
	memset(resvie_usart_dat_buff,0,500);	
    Send_Str(str_buff);
	Send_Str("\r\n");	
	delayms(1000);
	if(strstr(resvie_usart_dat_buff,"ERROR"))re_tcp_conect();
}

void show_API(unsigned char chanl)
{
	//	 unsigned char i=0;
	//	char *str_p;
	LCD_display_str(0x40,"               ");
	if(chanl==0)
	{
		sprintf(str_buff,"date:%s      ",date_buff);
		LCD_display_str(0x40,str_buff);
	}
	else if(chanl==1)
	{
		sprintf(str_buff,"temp:%s~%s",temp_low_buff,temp_high_buff);//set_dis_down,csb1_dis,set:%.0fcm, 
		LCD_display_str(0x40,str_buff);
	}	
	else if(chanl==2)
	{
		sprintf(str_buff,"text_day:%s  ",text_day);//set_dis_down,csb1_dis,set:%.0fcm, 
		LCD_display_str(0x40,str_buff);
	}	
	else if(chanl==3)
	{
		sprintf(str_buff,"text_night:%s  ",text_night);//set_dis_down,csb1_dis,set:%.0fcm, 
		LCD_display_str(0x40,str_buff);
	}		
	else if(chanl==4)
	{
		sprintf(str_buff,"wind_sped:%sm/s ",wind_speed);//set_dis_down,csb1_dis,set:%.0fcm, 
		LCD_display_str(0x40,str_buff);
	}	
	else if(chanl==5)
	{
		sprintf(str_buff,"wind_scale:%s  ",wind_scale);//set_dis_down,csb1_dis,set:%.0fcm, 
		LCD_display_str(0x40,str_buff);
	}		
	else if(chanl==6)
	{
		sprintf(str_buff,"rainfall:%s  ",rainfall);//set_dis_down,csb1_dis,set:%.0fcm, 
		LCD_display_str(0x40,str_buff);
	}			
}

unsigned char resive_zero_flag=0;
void UART() interrupt 4
{	
	if(RI == 1)   //���ڽ��յ�����
	{
		RI = 0;	  sys_cnt=5;     
		resvie_usart_dat = SBUF;  //
	
		//		if(resvie_usart_dat == 'c')	{ //����ָ��õ��ֻ���������������
		//			resvie_usart_save_dat_flag=0; 
		if(resvie_usart_dat_buff_len>210 && resive_zero_flag==0) {resvie_usart_dat_buff_len=0; resive_zero_flag=1;}
		//		else resvie_usart_dat_buff_len=0;
		
		if(resvie_usart_dat_buff_len<500) resvie_usart_dat_buff[resvie_usart_dat_buff_len++]=resvie_usart_dat;
		else resvie_usart_dat_buff_len=0;
		//			set_dis_down = (float)atoi(resvie_usart_dat_buff);
		//      resvie_usart_dat_buff_len =0;			
		//		}
		//		if(resvie_usart_save_dat_flag)
		//		{
		//	  	if(resvie_usart_dat_buff_len<5)resvie_usart_dat_buff[resvie_usart_dat_buff_len++]	 = resvie_usart_dat;
		//		}	
		//if(resvie_usart_dat == ':')	{ resvie_usart_save_dat_flag=1;resvie_usart_dat_buff_len=0; }	//SET:25cm

	}	
}

void init_time0(void)
{
		TMOD = 0x01;//������ʱ��0��16λ��ʱģʽ
//		TH0 = 0x3C;  //(65536 - 50000) / 256;  //50ms
//		TL0 = 0xB0;  //(65536 - 50000) % 256;;
//		TH0 = 0xBE;  //(65536 - 50000) / 256;  //20ms
//		TL0 = 0xE0;  //(65536 - 50000) % 256;;	
		TH0 = 0;                    //��ʱ����λ����ֵ��Ϊ0 (65536-62500)/256
		TL0 = 0;                    //��ʱ����λ����ֵ��Ϊ0
		ET0=0;  // �رն�ʱ�ж�
		EA=1;   // �����ж�
		TR0=0;  // �رն�ʱ��
}


/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

//code char  CWJAP_buff[35] = "AT+CWJAP=\"CMCC-z5x5\",\"MNtH5Rr7\"\r\n";  //����WiFi ���ƺ�����
//code char  CWMODE_buff[15] = "AT+CWMODE=1\r\n";  //����WiFiģ��ΪSTAģʽ
//code char  CIPSTART_buff[] = "AT+CIPSTART=\"TCP\",\"api.seniverse.com\",80\r\n";  //����TCP����
//code char  GET_API_buff[]

unsigned char api_cnt=0;
unsigned char loop_cnt=0;



void main(void)				//������
{
//	 unsigned char i;
//	lcd12864_init();//LCD12864��ʼ��
//		sprintf((char*)str_buff,"set:%.0fcm   ",set_dis_down);
//		lcd12864_show_string(0,0,str_buff);//��1���ַ�����ʾ lie hang
	BEEP =1;
	LED =0;
	LcdInit();
	delayms(200); 
	init_time0();  //��ʱ��0��ʼ��
	init_usart_com(); //���ڳ�ʼ�� ������9600
	BEEP=1;  LED=1; 
	
	//	dat_resive_fun();
	
	resvie_usart_dat_buff_len =0;
	Send_Str("AT\r\n");             //
	delayms(2000);
	while(strstr(resvie_usart_dat_buff,"OK")==0);
	memset(resvie_usart_dat_buff,0,500);
	
	resvie_usart_dat_buff_len =0;
	Send_Str("AT+CIPMUX=1\r\n");              //������ģʽ
	delayms(2000);
	while(strstr(resvie_usart_dat_buff,"OK")==0);
	memset(resvie_usart_dat_buff,0,500);		
	delayms(1000);

	//delayms(30000);
	resvie_usart_dat_buff_len =0;
	Send_Str(CWJAP_buff);                     //����WiFi
	delayms(5000);
	while(strstr(resvie_usart_dat_buff,"OK")==0);
	memset(resvie_usart_dat_buff,0,500);
	delayms(2000);
	
	resvie_usart_dat_buff_len=0;
	Send_Str(CWMODE_buff);                // ����Ϊstaģʽ
	delayms(2000);
	while(strstr(resvie_usart_dat_buff,"OK")==0);	
	memset(resvie_usart_dat_buff,0,500); 
	delayms(1000);
	
	resvie_usart_dat_buff_len=0;
	Send_Str(CIPSTART_API_buff);    // ���ӻ�ȡ�����ķ�����
	delayms(2000);
	while(strstr(resvie_usart_dat_buff,"OK")==0);	
 	memset(resvie_usart_dat_buff,0,500); 
	delayms(1000);

	resvie_usart_dat_buff_len=0;
	Send_Str(CIPSEND_API_buff);    //��������ָ�� AT+CIPSEND = 
	delayms(2000);
	while(strstr(resvie_usart_dat_buff,"OK")==0);	
 	memset(resvie_usart_dat_buff,0,500);

	resive_zero_flag =0;
	resvie_usart_dat_buff_len=0; 
	Send_Str(GET_API_buff);        //��API���ݻ�ȡ����
	delayms(2000);
	while(strstr(resvie_usart_dat_buff,"date")==0);		
	delayms(1000);
	//	memset(resvie_usart_dat_buff,0,1000);
	//Send_Str("\r\n");  
	//Send_Str(resvie_usart_dat_buff);  

	//resvie_usart_dat_buff_len =300;
	//// ��Ϊ͸��
	if(resvie_usart_dat_buff_len>100)
	{
		dat_resive_fun();
		// CIPSEND_buff		
		memset(resvie_usart_dat_buff,0,500);
		
		resvie_usart_dat_buff_len =0; 
		Send_Str("AT+CIPMUX=1\r\n");              //����WiFi
		delayms(2000);
		while(strstr(resvie_usart_dat_buff,"OK")==0);
		memset(resvie_usart_dat_buff,0,500);		
		
		resvie_usart_dat_buff_len=0;
		Send_Str(CWMODE_buff);           // ����Ϊstaģʽ
		delayms(2000);
		while(strstr(resvie_usart_dat_buff,"OK")==0);	
		memset(resvie_usart_dat_buff,0,500);
		delayms(5000);	
	

		resvie_usart_dat_buff_len=0; 
		Send_Str(CIPSTART_APP_buff);   //�����ֻ�app��������
		delayms(2000);
		while(strstr(resvie_usart_dat_buff,"OK")==0);	
		memset(resvie_usart_dat_buff,0,500);		
		delayms(2000);		
	
		//		sprintf(str_buff,"date:%s      ",date_buff);
		//		sprintf(send_len_buff,"AT+CIPSEND=2,%d\r\n",(int)(strlen(str_buff)+2));
		//    Send_Str(send_len_buff);	delayms(2000);
		//    Send_Str(str_buff);
		//	  Send_Str("\r\n");	
		//	
		//	
		//	resvie_usart_dat_buff_len=0;
		//	Send_Str(CWMODE_buff);           // ����Ϊstaģʽ
		//	delayms(2000);
		//	while(strstr(resvie_usart_dat_buff,"OK")==0);	
		//	memset(resvie_usart_dat_buff,0,500);
		//		delayms(5000);	
		//resvie_usart_dat_buff_len=0;

		//	resvie_usart_dat_buff_len=0;
		//	Send_Str(CIPSEND_buff);       //����Ϊ͸��
		//	delayms(2000);
		//	//if(strstr(resvie_usart_dat_buff,"OK")) break;	
		//		while(strstr(resvie_usart_dat_buff,"OK")==0);	
		// 	memset(resvie_usart_dat_buff,0,500);			
		//	delayms(5000);


	}

		//	LED_READ =0;
	delayms(200);
	while(1)
	{
//		beek_flag =0;
		sys_cnt++;
		if(sys_cnt>=6)
		{
			sys_cnt =0;
			if(MQ2_IN==0) { BEEP=0; LED=0; beek_flag=1; } //����������Χ��LED�����ҷ���������
			else {  BEEP=1;  LED=1; beek_flag=0; }
			DHT11_receive();	
			LCD_display_str(0,rec_dat); 	
			
			loop_cnt++;
			if(loop_cnt>=6)
			{
				loop_cnt=0;
				show_API(api_cnt);
				api_cnt++;if(api_cnt>6) api_cnt=0;
				send_API();
			}
			
    }
				delayms(200);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

