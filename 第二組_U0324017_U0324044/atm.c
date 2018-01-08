#include <reg51.h>
#include "lcd.h" // void delay1ms(),int kbscan()
#include <stdio.h>
#include <stdlib.h>

void show_loading();
void show_welcome();
void show_accountpassword();
void show_option();
void showTheMoney(int money);
void showUser(int money);
void funSave(int money);
void funDraw(int money);
void funTranfer(int money);
char scanline[]={0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff};//left to right seven segement
unsigned char numbers[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
int account[4]={0};
int tmp1[7] = {0};
int aMoney = 5000;
int bMoney = 450;
int i;
int j;
int p;
int g;
int k;
void main()
{
	show_welcome();
	show_loading();
	//initialization 
	show_accountpassword();

  P2=numbers[0];
	
	g=0;
	
  while(1)
  {	
		kbin=kbscan();
    if(kbin!=0xff)
		{
		account[g++] = kbin;
		}
		if(g==4)		
			break;
	}
	p= account[0]*1000+account[1]*100+account[2]*10+account[3];
	showUser(p);
	
	g=0;
	
  while(1)
  {	
		kbin=kbscan();
    if(kbin!=0xff)
		{
		account[g++] = kbin;
		}
		if(g==4)
			break;
	}
	 //after enter password
	showTheMoney(aMoney);	
	showTheMoney(bMoney);
	EA=1;
	EX0=1;
	IT0=1;
	while(1){}
	
}
void key_scan() interrupt 0
{
	char s[5];
	show_option();	
	while(1)
  {	
		kbin=kbscan();
    if(kbin!=0xff)
		{
			switch(kbin){
				case 1: // draw					
					g=0;	
					while(1)
					{	
						kbin=kbscan();
						if(kbin!=0xff)
						{
							account[g++] = kbin;
						}
						if(g==4)		
							break;
					}
					p= account[0]*1000+account[1]*100+account[2]*10+account[3];
					funDraw(p); 
					showTheMoney(aMoney);
					showTheMoney(bMoney);
					break;
					
				case 2: // save
					g=0;	
					while(1)
					{	
						kbin=kbscan();
						if(kbin!=0xff)
						{
							account[g++] = kbin;
						}
						if(g==4)		
							break;
					}
					p= account[0]*1000+account[1]*100+account[2]*10+account[3];
					funSave(p);
					showTheMoney(aMoney);
					showTheMoney(bMoney);
					break;
					
				case 3: // transfer
					g=0;	
					while(1)
					{	
						kbin=kbscan();
						if(kbin!=0xff)
						{
							account[g++] = kbin;
						}
						if(g==4)		
							break;
					}
					p= account[0]*1000+account[1]*100+account[2]*10+account[3];
					funTranfer(p);
					showTheMoney(aMoney);
					showTheMoney(bMoney);
					break;
			}
		}
	}	
}
void show_loading() // LED left>>right
{	
	int round;
	for ( round=1;round<3;round++)
	{	    
		ledsileft();
  }	
	P2=0xff; 
  delay1ms(500);			
	return;
}
void show_welcome()
{
	char code *mes[2] = {	"Welcome to CSIE ATM.",	"Please login:"	};
	char k=10;
	Init_LCD();
	LCD_CMD(1);
	delay1ms(2);
	while(k!=0){
		DISP_Str(0x80,mes[0]);
		DISP_Str(0xC0,mes[1]);
		delay1ms(10);
		k--;
	}
}

void show_accountpassword()
{
	char code *mes1[2] = {"Account:","Password:"};
	char k=10;
	Init_LCD();
	LCD_CMD(1);
	delay1ms(2);
	while(k!=0){		
			DISP_Str(0x80,mes1[0]);			
			delay1ms(10);						
			DISP_Str(0xC0,mes1[1]);
			k--;
	}
}
void show_option()
{
	char code *mes1[3] = {"1.draw       ","2.save     ","3.transfer "};
	char l,k=1;
	Init_LCD();
	LCD_CMD(1);
	delay1ms(2);
	while(k!=0){
		for(l=0; l<3;l++)
		{
			DISP_Str(0x80,mes1[l]);
			delay1ms(1000);
		}
		k--;
	}	
}
void funSave(int money)
{
	aMoney = aMoney + money;	
	showTheMoney(aMoney);
}

void funDraw(int money)
{
	aMoney = aMoney - money;
	
	showTheMoney(aMoney);
}
void funTranfer(int money)
{
	aMoney = aMoney - money;
	bMoney = bMoney + money;	
	showTheMoney(aMoney);
}
void showTheMoney(int money)	//By the seven segment
{
	//left to right
	int tmp[7] = {0};

	tmp[0] = (money%100000)/10000;
	tmp[1] = (money%10000)/1000;
	tmp[2] = (money%1000)/100;
	tmp[3] = (money%100)/10;
	tmp[4] = money%10;
	
	
		for(j = 0; j < 1000; j++)  //don't touch
		{
			for (i = 0; i < 5; i++)	// don't touch
				{
					P2 = numbers[tmp[i]];
					P1 = scanline[i];
					delay1ms(1);
				}
			for (i = 5; i < 8; i++)	// don't touch
				{
					P2 = 0x00;
					P1 = scanline[i];
					delay1ms(1);
				}				
		}
		
}
void showUser(int money)	//By the seven segment
{
	//tmp1[0] = (money%100000)/10000;
	tmp1[0] = (money%10000)/1000;
	tmp1[1] = (money%1000)/100;
	tmp1[2] = (money%100)/10;
	tmp1[3] = money%10;
	
		for(j = 0; j < 500; j++)  //don't touch
		{
			for (i = 0; i < 4; i++)	// don't touch
				{
					P2 = numbers[tmp1[i]];
					P1 = scanline[i];
					delay1ms(1);
				}
				for (i = 4; i < 8; i++)	// don't touch
				{
					P2 = 0x00;
					P1 = scanline[i];
					delay1ms(1);
				}
		}
}