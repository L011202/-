#include "reg52.h"
//#include "lcd.h"
//#include "ADC0832.h"
#include "stdio.h"
#include "string.h"
#include "DHT11.h"

uchar rec_dat[10];   //用于显示的接收数据数组
sbit Data=P2^0;   //定义数据线

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
   DHT11_delay_ms(30);   //延时18ms以上
	//smg_show();smg_show();smg_show();smg_show();
   Data=1;
   DHT11_delay_us(30);
}

uchar DHT11_rec_byte()      //接收一个字节
{
   uchar i,dat=0;
//	EA=0;
	read_dat_flag =1;
  for(i=0;i<8;i++)    //从高到低依次接收8位数据
   {          
      while(!Data);   ////等待50us低电平过去
      DHT11_delay_us(8);     //延时60us，如果还为高则数据为1，否则为0 
      dat<<=1;           //移位使正确接收8位数据，数据为0时直接移位
      if(Data==1)    //数据为1时，使dat加1来接收数据1
         dat+=1;
      while(Data);  //等待数据线拉低    
    }  
//	 EA=1;
		read_dat_flag =0;
    return dat;
}

void DHT11_receive(void)      //接收40位的数据
{
    uchar R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise; 
    DHT11_start();
    if(Data==0)
    {
        while(Data==0);//{smg_show();}   //等待拉高     
        DHT11_delay_us(40);  //拉高后延时80us
        R_H=DHT11_rec_byte();    //接收湿度高八位  
        R_L=DHT11_rec_byte();    //接收湿度低八位  
        T_H=DHT11_rec_byte();    //接收温度高八位  
        T_L=DHT11_rec_byte();    //接收温度低八位
        revise=DHT11_rec_byte(); //接收校正位

        DHT11_delay_us(25);    //结束

        if((R_H+R_L+T_H+T_L)==revise)      //校正
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
        } 
        /*数据处理，方便显示*/
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

/*这里使用lcd1602来显示采集到的数据*/


//void main()
//{
//   uchar i;   
//   init_lcd();   //lcd1602初始化
//   while(1)
//   {   
//       DHT11_delay_ms(100);    //DHT11上电后要等待1S以越过不稳定状态在此期间不能发送任何指令
//       DHT11_receive();
//       write_com(0x80);   //从lcd1602第一行第一个位置开始显示
//       for(i=0;i<9;i++)
//       write_dat(rec_dat[i]);   //显示数据   
//	   write_com(0x80+0x40);
//	   write_dat(0x2d);
//                 write_dat(0x42);
//                 write_dat(0x3a);                
//   }
//}
