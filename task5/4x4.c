#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int

#define KEY P3

uchar code LED_SEG[]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
0x77,0x7c,0x39,0x5e,0x79,0x71,
0x00,
0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,
0x40
};
uchar code Scan_bit[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uchar data Dis_buf[]={16,16,16,16,16,16,16,16};

sbit P20=P2^0;
sbit P21=P2^1;

uchar key_volume;

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

void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}

uchar keyscan(void)
{
	KEY=0x0f;
	_nop_();
	if(KEY!=0x0f)
	{
		Delay10ms();
		if(KEY!=0x0f)
		{
			KEY=0xef;
			_nop_();
			switch(KEY&0x0f){
			   case 0x0e: key_volume=0; break;
			   case 0x0d: key_volume=1; break;
			   case 0x0b: key_volume=2; break;
			   case 0x07: key_volume=3; break;
			   default: break;
			}

			KEY=0xdf;
			_nop_();
			switch(KEY&0x0f){
			   case 0x0e: key_volume=4; break;
			   case 0x0d: key_volume=5; break;
			   case 0x0b: key_volume=6; break;
			   case 0x07: key_volume=7; break;
			   default: break;
			}

			KEY=0xbf;
			_nop_();
			switch(KEY&0x0f){
			   case 0x0e: key_volume=8; break;
			   case 0x0d: key_volume=9; break;
			   case 0x0b: key_volume=10; break;
			   case 0x07: key_volume=11; break;
			   default: break;
			}

			KEY=0x7f;
			_nop_();
			switch(KEY&0x0f){
			   case 0x0e: key_volume=12; break;
			   case 0x0d: key_volume=13; break;
			   case 0x0b: key_volume=14; break;
			   case 0x07: key_volume=15; break;
			   default: break;
			}
		}
		else
		{
			key_volume=16;
		}
	}
	else
	{
		key_volume=16;
	}
	KEY=0xff;
	return 16;
}


void main(void)
{
	key_volume=16;
	KEY=0xff;
	while(1)
	{
		keyscan();
		if(key_volume!=16) Dis_buf[7]=key_volume;
		LED_Display();
	}
}