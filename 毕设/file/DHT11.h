#ifndef __DHT11_H_
#define __DHT11_H_
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

void Send_Str(uchar str_dat[]);
void Send_One_Byte(uchar Byte);
void init_usart_com( void ) ;
void DHT11_delay_us(uchar n);
void DHT11_delay_ms(uint z);
void DHT11_receive(void)   ;
void smg_show(void);
#endif
