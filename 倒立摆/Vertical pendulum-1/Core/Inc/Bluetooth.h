#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include "stm32f1xx_hal.h"
#include "tim.h"
#include "gpio.h"

extern UART_HandleTypeDef huart1;//声明USART2的HAL库结构体

#define USART1_REC_LEN  200//定义USART2最大接收字节数

extern uint8_t  USART1_RX_BUF[USART1_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.末字节为校验和
extern uint16_t USART1_RX_STA;//接收状态标记
extern uint8_t USART1_NewData;//当前串口中断接收的1个字节数据的缓存


void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart);//串口中断回调函数声明



extern char num;		//百位
extern  char num2;    //十位
extern char  num3;    //个位

#endif 


