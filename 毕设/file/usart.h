#ifndef __USART_H_
#define __USART_H_
/**********************************
��ʹ�õ���4λ���ݴ����ʱ���壬
ʹ��8λȡ���������
**********************************/
//#define LCD1602_4PINS

/**********************************
����ͷ�ļ�
**********************************/
#include <reg52.h>
#include <stdio.h>
#include "stdlib.h"


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
#endif
