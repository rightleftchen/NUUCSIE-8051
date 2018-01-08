#include <reg51.h>
void delay10ms(int count)
{
	int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<1940;j++);
}

void main()
{
	
	P2=0xFE;
  delay10ms(100);
	P2=0xFD;
	delay10ms(100);
	P2=0xFB;
	delay10ms(100);
	P2=0xF7;
	delay10ms(100);
  P2=0xEF;
	delay10ms(100);
	P2=0xDF;
	delay10ms(100);
	P2=0xBF;
	delay10ms(100);
	P2=0x7F;
	delay10ms(100);
}
