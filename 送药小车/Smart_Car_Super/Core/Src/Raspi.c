#include "Raspi.h"
uint8_t USART3_RX_BUF[USART3_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.
uint16_t USART3_RX_STA=0;//接收状态标记//bit15：接收完成标志，bit14~0：接收到的有效字节数目
uint8_t USART3_NewData;//当前串口中断接收的1个字节数据的缓存



