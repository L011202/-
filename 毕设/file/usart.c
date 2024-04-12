#include "reg52.h"
//#include "lcd.h"
//#include "ADC0832.h"
#include "stdio.h"
#include "string.h"
#include "usart.h"

void init_usart_com( void ) 
{ 
     SCON=0x50; //串口工作方式1，8位UART，波特率可变  
//     TH2=0xFF;           
//     TL2=0xFD;    //波特率:115200 晶振=11.0592MHz 
//     RCAP2H=0xFF;   
//     RCAP2L=0xFD; //16位自动再装入值
	  
    	TH2=0xFF;           
     TL2=0xDC;    //波特率:9600 晶振=11.0592MHz 
     RCAP2H=0xFF;   
     RCAP2L=0xDC; //16位自动再装入值
	
	
//	
//    	TH2=0xFF;           
//     TL2=0xD9;    //波特率:9600 晶振=12MHz 
//     RCAP2H=0xFF;   
//     RCAP2L=0xD9; //16位自动再装入值	
	
/*****************/
     TCLK=1;   
     RCLK=1;   
     C_T2=0;   
     EXEN2=0; //波特率发生器工作方式
/*****************/
     TR2=1 ; //定时器2开始
}




void Send_One_Byte(uchar Byte)  //向串口写入一个字节数据
{
	ES = 0;  //关串口中断
	SBUF = Byte; 
	while(!TI);		//TI == 1 跳出循环
	TI = 0;
	ES = 1;  //打开串口中断
}

void Send_Str(uchar str_dat[])  //向串口写入字符串
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
//	Send_One_Byte(0XFF);  //三个结束符号
}

//void Send_EStr(uchar str[]) 
//{
//	
//}

