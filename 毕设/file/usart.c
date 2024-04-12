#include "reg52.h"
//#include "lcd.h"
//#include "ADC0832.h"
#include "stdio.h"
#include "string.h"
#include "usart.h"

void init_usart_com( void ) 
{ 
     SCON=0x50; //���ڹ�����ʽ1��8λUART�������ʿɱ�  
//     TH2=0xFF;           
//     TL2=0xFD;    //������:115200 ����=11.0592MHz 
//     RCAP2H=0xFF;   
//     RCAP2L=0xFD; //16λ�Զ���װ��ֵ
	  
    	TH2=0xFF;           
     TL2=0xDC;    //������:9600 ����=11.0592MHz 
     RCAP2H=0xFF;   
     RCAP2L=0xDC; //16λ�Զ���װ��ֵ
	
	
//	
//    	TH2=0xFF;           
//     TL2=0xD9;    //������:9600 ����=12MHz 
//     RCAP2H=0xFF;   
//     RCAP2L=0xD9; //16λ�Զ���װ��ֵ	
	
/*****************/
     TCLK=1;   
     RCLK=1;   
     C_T2=0;   
     EXEN2=0; //�����ʷ�����������ʽ
/*****************/
     TR2=1 ; //��ʱ��2��ʼ
}




void Send_One_Byte(uchar Byte)  //�򴮿�д��һ���ֽ�����
{
	ES = 0;  //�ش����ж�
	SBUF = Byte; 
	while(!TI);		//TI == 1 ����ѭ��
	TI = 0;
	ES = 1;  //�򿪴����ж�
}

void Send_Str(uchar str_dat[])  //�򴮿�д���ַ���
{
	idata unsigned char i;
	idata unsigned int len;
	len = strlen(str_dat);
  for(i=0;i<len;i++)
	{
		Send_One_Byte(str_dat[i]);
	}
//	Send_One_Byte(0XFF);
//	Send_One_Byte(0XFF);
//	Send_One_Byte(0XFF);  //������������
}

//void Send_EStr(uchar str[]) 
//{
//	
//}

