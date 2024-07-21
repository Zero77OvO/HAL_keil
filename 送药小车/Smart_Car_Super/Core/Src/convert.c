#include "convert.h"
#include "usart.h"
#include "tim.h"
#include "OLED.h"
#include "Bluetooth.h"
#include "vofa.h"
#include "Raspi.h"
int value;
int flag;
int last;
 
 
void TargetTracking()
{
	flag = USART3_RX_STA - last;
				
	last = USART3_RX_STA;
	
	
  value = (pinum3-48) * 100 + (pinum2-48) * 10 + (pinum-48) * 1;
	
	//OLED_ShowStr(10,2,"Object Center",2);
	OLED_Showdecimal(0,0,value,3,1,16);
	
	if(flag == 2)
	{
		value = (pinum2-48) * 10 + (pinum-48) * 1;
		OLED_Showdecimal(0,2,value,3,1,16);
	}


	
}
