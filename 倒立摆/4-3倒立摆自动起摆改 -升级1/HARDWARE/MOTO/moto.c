#include "moto.h"
#include "stm32f10x.h"

/**************************************************************************
函数功能：电机的正反转
入口参数：mode   mode=0时为正转  mode=1时反转
返回  值：无
**************************************************************************/


void moto(int mode)
{
	if(mode==1)    //反转
	{
	 GPIO_SetBits(GPIOB, GPIO_Pin_12);	 // 高电平      PB7 --- AIN2      1   
	 GPIO_ResetBits(GPIOB, GPIO_Pin_13);	 // 低电平}   PB8 --- AIN1      0
		
	}
	 if(mode==0)   //正传
	{
	 GPIO_SetBits(GPIOB, GPIO_Pin_13);	 // 高电平       PB8 --- AIN1     1
	 GPIO_ResetBits(GPIOB, GPIO_Pin_12);	 // 低电平}    PB7 --- AIN2     0
		
	 }
	if(mode==2)   //停止
	{

		GPIO_ResetBits(GPIOB, GPIO_Pin_12);	 // 低电平}    PB7 --- AIN2     0
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
	 }
 
}

/*

———————————————————
AIN1  |   0     |   1     |    0   |
———————————————————
AIN2  |   0     |   0     |    1   |
———————————————————
      |  停止   |  正转    |  反转  |
———————————————————

*/
