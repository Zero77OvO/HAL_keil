#ifndef _RASPI_H_
#define _RASPI_H_

#include <main.h>
#include "usart.h"
#include "string.h"


extern UART_HandleTypeDef huart3;//声明USART2的HAL库结构体

#define USART3_REC_LEN  200//定义USART2最大接收字节数

extern uint8_t  USART3_RX_BUF[USART3_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.末字节为校验和
extern uint16_t USART3_RX_STA;//接收状态标记
extern uint8_t USART3_NewData;//当前串口中断接收的1个字节数据的缓存




extern char pinum;		
extern char pinum2;
extern char pinum3;
extern char pinum4;
extern char pinum5;


#endif
