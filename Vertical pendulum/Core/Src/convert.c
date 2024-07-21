#include "convert.h"
#include "usart.h"
#include "tim.h"
#include "OLED.h"
 #include "Bluetooth.h"

int value;
int flag;
int last;
 
 
void TargetTracking()
{
	flag = USART1_RX_STA - last;
				
	last = USART1_RX_STA;
	
	
	if(flag == 2)
	{
	value = (num2-48) * 10 + (num-48) * 1;
	//OLED_Showdecimal(0,4,num,3,1,16);
	
	}
	else{
	value = (num3-48) * 100 + (num2-48) * 10 + (num-48) * 1;
	OLED_Showdecimal(0,0,num,3,1,16);
	OLED_Showdecimal(0,2,num2,3,1,16);
	OLED_Showdecimal(0,4,num3,3,1,16);
	OLED_Showdecimal(0,6,USART1_RX_STA,3,1,16);
	}
	
}
