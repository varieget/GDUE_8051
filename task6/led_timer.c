#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

uchar code LED_SEG[]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
0x77,0x7c,0x39,0x5e,0x79,0x71,
0x00,
0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,
0x40
};
uchar code Scan_bit[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
//uchar code Scan_bit[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
uchar data Dis_buf[]={0,0,16,0,0,16,0,0};

sbit P20=P2^0;
sbit P21=P2^1;

uchar cnt=0;

uchar hour=23;
uchar min=57;
uchar second=50;

void Delay1ms(void)	//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void LED_Display(void)
{
	uchar i;
	for(i=0;i<8;i++){
		P20=1;
		P0=LED_SEG[Dis_buf[i]];
		P20=0;
		P0=0xff;
		P21=1;
		P0=Scan_bit[i];
		P21=0;
		Delay1ms();
	}
}

void Timer0_Init(void)
{
	TMOD = 0x01;
	TL0 = 0xB0;
	TH0 = 0x3C;
	TF0 = 0;
	TR0 = 1;
}

void main(void)
{
	Timer0_Init();
	Dis_buf[7]=second%10;
	Dis_buf[6]=second/10%10;
	Dis_buf[4]=min%10;
	Dis_buf[3]=min/10%10;
	Dis_buf[1]=hour%10;
	Dis_buf[0]=hour/10%10;
	while(1)
	{
		LED_Display();
		if(TF0==1){
			TF0 = 0;
			TL0 = 0xB0;
			TH0 = 0x3C;
			cnt++;
			if(cnt==20){
				cnt=0;
				second++;
				if(second==60) {
					second=0;
					min++;
				}
				if(min==60) {
					min=0;
					hour++;
				}
				if(hour==24) {
					second=0;
					min=0;
					hour=0;
				}
				Dis_buf[7]=second%10;
				Dis_buf[6]=second/10%10;
				Dis_buf[5]=Dis_buf[5]==27?16:27;
				Dis_buf[4]=min%10;
				Dis_buf[3]=min/10%10;
				Dis_buf[2]=Dis_buf[2]==27?16:27;
				Dis_buf[1]=hour%10;
				Dis_buf[0]=hour/10%10;
			}
		}
	}
}