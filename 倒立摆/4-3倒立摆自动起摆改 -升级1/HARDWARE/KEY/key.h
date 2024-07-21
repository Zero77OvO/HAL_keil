#ifndef __KEY_H
#define __KEY_H

#define KEY5 PAin(5)   
#define KEY2 PAin(2)
#define KEY7 PAin(7)
#define KEY11 PAin(11)
#define KEY12 PAin(12)
#define KEY14 PCin(14)


#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)//读取按键0
//#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1
//#define KEY2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//读取按键2 
//#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP) 

 

#define KEY0_PRES 	1	//KEY0按下
//#define KEY1_PRES	2	//KEY1按下
//#define KEY2_PRES	3	//KEY2按下
//#define WKUP_PRES   4	//KEY_UP按下(即WK_UP/KEY_UP)

void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数		
	
#endif
