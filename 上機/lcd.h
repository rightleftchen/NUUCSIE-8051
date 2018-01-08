#include <reg51.h>
#define DBPORT P2
#define KBINP P0
sbit RS=P1^0;
sbit RW=P1^1;
sbit E=P1^2;
int kbin;
void delay1ms(int count)
{
	int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<122;j++);
}
void ledsileft()
{
	int i;
  char ledsileft[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe, 
		                0x7e,0xbe,0xde,0xee,0xf6,0xfa,0xfc, 
		                0x7c,0xbc,0xdc,0xec,0xf4,0xf8,
		                0x78,0xb8,0xd8,0xe8,0xf0,
		                0x70,0xb0,0xd0,0xe0, 
		                0x60,0xa0,0xc0, 
		                0x40,0x80, 
		                0x0}; 	
		for ( i=0;i<36;i++)
		{ 
			P2=ledsileft[i];
			delay1ms(100);
		}
}
void LCD_CMD(char cmd)
{
	char i;
	DBPORT=cmd;
	RS=0;RW=0;E=1;
	for(i=0;i<40;i++)
	RS=0;RW=0;E=0;
}
void Init_LCD()
{
	delay1ms(5);
	LCD_CMD(0x3f);
	LCD_CMD(0xe);
	LCD_CMD(0x1);
	delay1ms(2);
	LCD_CMD(0x80);
}

void LCD_DATA(char data1)
{
	char i;
	DBPORT=data1;
	RS=1;RW=0;E=1;
	for(i=0;i<40;i++)
	RS=1;RW=0;E=0;
}
void DISP_Str(char addr1,char *str)
{
	LCD_CMD(addr1);
	while(*str !=0 )
		LCD_DATA(*str++);
}
int kbscan() 
{ unsigned char kbp; 
  unsigned char scanln[]={0xfe,0xfd,0xfb,0xf7}; 
  unsigned char row, col,kbtemp; 
  kbp=0xff; 
  for(row=0;row < 4;row++)
     { KBINP=scanln[row];
       kbtemp=KBINP& 0xf0; 
       if(kbtemp !=0xf0)
	     { delay1ms(20); 
         for(col=0;col<4;col++)
		     { if(kbtemp==((scanln[col]&0x0f)*16))
			     { kbp=row*4+col; 
             while((KBINP&0xf0)!=0xf0); 
           } 
         } 
       }
     } 
  return kbp; 
}

