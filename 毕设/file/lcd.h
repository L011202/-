#ifndef __LCD_H_
#define __LCD_H_
/**********************************
��ʹ�õ���4λ���ݴ����ʱ���壬
ʹ��8λȡ���������
**********************************/
//#define LCD1602_4PINS

/**********************************
����ͷ�ļ�
**********************************/
#include <reg52.h>

//---�ض���ؼ���---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

/**********************************
PIN�ڶ���
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P3^4;   //P3^4;2.7 
sbit LCD1602_RW=P3^6;  //3.6 2.5
sbit LCD1602_RS=P3^5;   //3.5 2.6

//#define LCD1602_DATAPINS P0
//sbit LCD1602_E=P1^7;   //P3^4;2.7 
//sbit LCD1602_RW=P1^6;  //3.6 2.5
//sbit LCD1602_RS=P1^5;   //3.5 2.6

/**********************************
��������
**********************************/
/*��51��Ƭ��12MHZʱ���µ���ʱ����*/
void Lcd1602_Delay1ms(uint c);   //��� 0us
/*LCD1602д��8λ�����Ӻ���*/
void LcdWriteCom(uchar com);
/*LCD1602д��8λ�����Ӻ���*/	
void LcdWriteData(uchar dat)	;
/*LCD1602��ʼ���ӳ���*/		
void LcdInit();						  

//void LCD_display_voltage(unsigned char x,float v) ;
void LCD_display_str(unsigned char x, unsigned char  str[]) ;
//void LCD_display_electr(unsigned char x,float v);
#endif
