#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char

sbit P10=P1^0;
sbit P11=P1^1;
sbit P12=P1^2;
sbit P13=P1^3;
sbit P14=P1^4;
sbit P15=P1^5;
sbit P16=P1^6;
sbit P17=P1^7;

uchar i=0;

void main(void)
{
	TMOD=0x10;
	TH1=0x3c;
	TL1=0xb0;
	TR1=1;
	while(1)
	{
		while(TF1==1){
			TH1=0x3c;
			TL1=0xb0;
			TF1=0;
			i++;
			if(i==20){
				P10=0;P11=1;P12=1;P13=1;P14=1;P15=1;P16=1;P17=1;
			}else if(i==40){
				P10=1;P11=0;P12=1;P13=1;P14=1;P15=1;P16=1;P17=1;
			}else if(i==60){
				P10=1;P11=1;P12=0;P13=1;P14=1;P15=1;P16=1;P17=1;
			}else if(i==80){
				P10=1;P11=1;P12=1;P13=0;P14=1;P15=1;P16=1;P17=1;
			}else if(i==100){
				P10=1;P11=1;P12=1;P13=1;P14=0;P15=1;P16=1;P17=1;
			}else if(i==120){
				P10=1;P11=1;P12=1;P13=1;P14=1;P15=0;P16=1;P17=1;
			}else if(i==140){
				P10=1;P11=1;P12=1;P13=1;P14=1;P15=1;P16=0;P17=1;
			}else if(i==160){
				P10=1;P11=1;P12=1;P13=1;P14=1;P15=1;P16=1;P17=0;
				i=0;
			}
		}
	}
}