#ifndef __DHT11_H_
#define __DHT11_H_
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

void Send_Str(uchar str_dat[]);
void Send_One_Byte(uchar Byte);
void init_usart_com( void ) ;
void DHT11_delay_us(uchar n);
void DHT11_delay_ms(uint z);
void DHT11_receive(void)   ;
void smg_show(void);
#endif
