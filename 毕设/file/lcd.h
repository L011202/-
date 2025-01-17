#ifndef __LCD_H_
#define __LCD_H_
/**********************************
当使用的是4位数据传输的时候定义，
使用8位取消这个定义
**********************************/
//#define LCD1602_4PINS

/**********************************
包含头文件
**********************************/
#include <reg52.h>

//---重定义关键词---//
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

/**********************************
PIN口定义
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
函数声明
**********************************/
/*在51单片机12MHZ时钟下的延时函数*/
void Lcd1602_Delay1ms(uint c);   //误差 0us
/*LCD1602写入8位命令子函数*/
void LcdWriteCom(uchar com);
/*LCD1602写入8位数据子函数*/	
void LcdWriteData(uchar dat)	;
/*LCD1602初始化子程序*/		
void LcdInit();						  

//void LCD_display_voltage(unsigned char x,float v) ;
void LCD_display_str(unsigned char x, unsigned char  str[]) ;
//void LCD_display_electr(unsigned char x,float v);
#endif
