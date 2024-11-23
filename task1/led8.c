#include <reg51.h>
#include <intrins.h>
#include <stdio.h>

#define uchar unsigned char
#define uint unsigned int

//uchar x=0xfe; // 1111 1110 fe
//uchar x=0x7f;
//uchar dat[8]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

// 1111 1110 fe
// 1111 1101 fd
// 1111 1011 fb
// 1111 0111 f7
// 1110 1111 ef
// 1101 1111 df
// 1011 1111 bf
// 0111 1111 7f

uchar dat[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};

void Delay1000ms(void)	//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 43;
	j = 6;
	k = 203;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main(void)
{ 
   uchar i;

   // for(i=8;i>0;i--){
   //    P1=dat[i];
   //    Delay1000ms();
   // }
    
    for(i=0;i<8;i++){
       P1=dat[i];
       Delay1000ms();
    }
}