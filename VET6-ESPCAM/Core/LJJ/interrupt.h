#ifndef _INTERRUPT_H
#define _INTERRUPT_H

#include "main.h"
#include "usart.h"
#include "string.h"


//k210
#define USART1_REC_LEN  200
extern uint8_t  USART1_RX_BUF[USART1_REC_LEN];
extern uint16_t USART1_RX_STA;
extern uint8_t USART1_NewData;
extern uint8_t RxState1; 




//usart2 bluetooth
#define USART2_REC_LEN  200
extern uint8_t  USART2_RX_BUF[USART2_REC_LEN];
extern uint16_t USART2_RX_STA;
extern uint8_t USART2_NewData;
extern uint8_t RxState2; 

extern char num;
extern char num2;
extern char num3;




//usart3 openmv
#define USART3_REC_LEN  200//定义USART2最大接收字节数
extern uint8_t  USART3_RX_BUF[USART3_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.末字节为校验和
extern uint16_t USART3_RX_STA;//接收状态标记
extern uint8_t USART3_NewData;//当前串口中断接收的1个字节数据的缓存
extern uint8_t RxState3; 


extern char pinum;		
extern char pinum2;
extern char pinum3;
extern char pinum4;
extern char pinum5;

//usart6 vofa
#define RXSTRSIZE 256		  // ???????????
extern uint8_t rx_string[RXSTRSIZE]; // ?????????????
extern uint8_t rx_cnt;			  // ?????????????
extern uint8_t rx_buff;			  // ???????
extern uint8_t RxBuff;
extern unsigned char shujv[12];
extern int vofa_i, vofa_I;
extern float vofa_float;



#endif
