#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char

uchar code LED_SEG[]={0x3f,0x06,0x5b,
0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar code Scan_bit[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
//uchar code Scan_bit[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
uchar data Dis_buf[]={5,0,6,2,0,0,0,0};

sbit P20=P2^0;
sbit P21=P2^1;

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

void main(void)
{
	while(1) LED_Display();
}