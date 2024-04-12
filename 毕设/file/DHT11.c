#include "reg52.h"
//#include "lcd.h"
//#include "ADC0832.h"
#include "stdio.h"
#include "string.h"
#include "DHT11.h"

uchar rec_dat[10];   //������ʾ�Ľ�����������
sbit Data=P2^0;   //����������

bit read_dat_flag =0;

void DHT11_delay_us(uchar n)
{
    while(--n);n++;
}

void DHT11_delay_ms(uint z)
{
   uint i,j;
   for(i=z;i>0;i--)
      for(j=124;j>0;j--);
}

void DHT11_start()
{
   Data=1;
   DHT11_delay_us(2);
   Data=0;
   DHT11_delay_ms(30);   //��ʱ18ms����
	//smg_show();smg_show();smg_show();smg_show();
   Data=1;
   DHT11_delay_us(30);
}

uchar DHT11_rec_byte()      //����һ���ֽ�
{
   uchar i,dat=0;
//	EA=0;
	read_dat_flag =1;
  for(i=0;i<8;i++)    //�Ӹߵ������ν���8λ����
   {          
      while(!Data);   ////�ȴ�50us�͵�ƽ��ȥ
      DHT11_delay_us(8);     //��ʱ60us�������Ϊ��������Ϊ1������Ϊ0 
      dat<<=1;           //��λʹ��ȷ����8λ���ݣ�����Ϊ0ʱֱ����λ
      if(Data==1)    //����Ϊ1ʱ��ʹdat��1����������1
         dat+=1;
      while(Data);  //�ȴ�����������    
    }  
//	 EA=1;
		read_dat_flag =0;
    return dat;
}

void DHT11_receive(void)      //����40λ������
{
    uchar R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise; 
    DHT11_start();
    if(Data==0)
    {
        while(Data==0);//{smg_show();}   //�ȴ�����     
        DHT11_delay_us(40);  //���ߺ���ʱ80us
        R_H=DHT11_rec_byte();    //����ʪ�ȸ߰�λ  
        R_L=DHT11_rec_byte();    //����ʪ�ȵͰ�λ  
        T_H=DHT11_rec_byte();    //�����¶ȸ߰�λ  
        T_L=DHT11_rec_byte();    //�����¶ȵͰ�λ
        revise=DHT11_rec_byte(); //����У��λ

        DHT11_delay_us(25);    //����

        if((R_H+R_L+T_H+T_L)==revise)      //У��
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
        } 
        /*���ݴ���������ʾ*/
        rec_dat[0]='R';
        rec_dat[1]='H';				
        rec_dat[2]='0'+(RH/10);
        rec_dat[3]='0'+(RH%10);
        rec_dat[4]='%';
        rec_dat[5]=' ';
        rec_dat[6]='0'+(TH/10);
        rec_dat[7]='0'+(TH%10);
				rec_dat[8]='\'';
        rec_dat[9]='C';
    }
}

/*����ʹ��lcd1602����ʾ�ɼ���������*/


//void main()
//{
//   uchar i;   
//   init_lcd();   //lcd1602��ʼ��
//   while(1)
//   {   
//       DHT11_delay_ms(100);    //DHT11�ϵ��Ҫ�ȴ�1S��Խ�����ȶ�״̬�ڴ��ڼ䲻�ܷ����κ�ָ��
//       DHT11_receive();
//       write_com(0x80);   //��lcd1602��һ�е�һ��λ�ÿ�ʼ��ʾ
//       for(i=0;i<9;i++)
//       write_dat(rec_dat[i]);   //��ʾ����   
//	   write_com(0x80+0x40);
//	   write_dat(0x2d);
//                 write_dat(0x42);
//                 write_dat(0x3a);                
//   }
//}
