#ifndef _RASPI_H_
#define _RASPI_H_

#include <main.h>
#include "usart.h"
#include "string.h"


extern UART_HandleTypeDef huart3;//����USART2��HAL��ṹ��

#define USART3_REC_LEN  200//����USART2�������ֽ���

extern uint8_t  USART3_RX_BUF[USART3_REC_LEN];//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�ΪУ���
extern uint16_t USART3_RX_STA;//����״̬���
extern uint8_t USART3_NewData;//��ǰ�����жϽ��յ�1���ֽ����ݵĻ���




extern char pinum;		
extern char pinum2;
extern char pinum3;
extern char pinum4;
extern char pinum5;


#endif
