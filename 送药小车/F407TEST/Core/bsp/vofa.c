/*
 * @Author: yyl
 * @Date: 2024-04-23 20:42:29
 * @LastEditors: yyl
 * @FilePath: \MDK-ARMc:\Users\vanilla\Desktop\F407TEST\Core\bsp\vofa.c
 * @LastEditTime: 2024-04-28 11:03:30
 * @Descripttion:   
 * code bless us
 */
#include <main.h>
#include "vofa.h"
#include "pid.h"
#include "motor.h"

extern MOTOR motor;
void Float_to_Byte(float f, unsigned char byte[])
{
	FloatLongType fl;
	fl.fdata = f;
	byte[0] = (unsigned char)fl.ldata;
	byte[1] = (unsigned char)(fl.ldata >> 8);
	byte[2] = (unsigned char)(fl.ldata >> 16);
	byte[3] = (unsigned char)(fl.ldata >> 24);
}

void Send_Data(UART_HandleTypeDef *huart, float f)
{
	unsigned char byte[4] = {0};

	Float_to_Byte(f, byte);
	HAL_UART_Transmit(huart, (uint8_t *)&byte[0], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
	HAL_UART_Transmit(huart, (uint8_t *)&byte[1], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
	HAL_UART_Transmit(huart, (uint8_t *)&byte[2], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
	HAL_UART_Transmit(huart, (uint8_t *)&byte[3], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
}

void Send_Tail(UART_HandleTypeDef *huart)
{
	unsigned char byte[4] = {0x00, 0x00, 0x80, 0x7f};

	HAL_UART_Transmit(huart, (uint8_t *)&byte[0], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
	HAL_UART_Transmit(huart, (uint8_t *)&byte[1], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
	HAL_UART_Transmit(huart, (uint8_t *)&byte[2], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
	HAL_UART_Transmit(huart, (uint8_t *)&byte[3], 1, 0xffff);
	while (HAL_UART_GetState(huart) == HAL_UART_STATE_BUSY_TX)
		;
}

// Add Send_Date
extern int speed_reality;
extern int speed_out;
void vodka_JustFloat_send(UART_HandleTypeDef *huart)
{

	Send_Data(huart, (float)speed_reality);
	Send_Data(huart, (float)speed_out);
	// Send_Data(huart, (float)speed[2]);
	// Send_Data(huart, (float)spid.out);

	// Send_Data(huart, (float)spid.kp);
	// Send_Data(huart, (float)spid.ki);
	// Send_Data(huart, (float)spid.kd);

	// Send_Data(huart, float(speed_intg));
	Send_Tail(huart);
}

/**example**/
// while(1)
// {
// 	vodka_JustFloat_send(&huart1);
// }

#define RXSTRSIZE 256		  // 最大接收字节数
uint8_t rx_string[RXSTRSIZE]; // 接收字符串数组
uint8_t rx_cnt = 0;			  // 接收字符串计数
uint8_t rx_buff;			  // 接收缓存
uint8_t RxBuff;
unsigned char shujv[12];
int vofa_i = 0, vofa_I = 0;
float vofa_float;
/*

*/
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
// 	uint8_t dat;
// 	if (huart->Instance == huart2.Instance)
// 	{

// 		// 以下是串口接收中断业务代码
// 		if (rx_cnt++ >= RXSTRSIZE - 1) // 溢出判断
// 		{
// 			rx_cnt = 0;
// 			memset(rx_string, 0x00, sizeof(rx_string));
// 		}
// 		else
// 		{
// 			dat = rx_buff; // 接收数据转存

// 			shujv[vofa_I++] = dat;

// 			if (dat == 0x0a)
// 			{

// 				for (vofa_i = 2, vofa_float = 0; vofa_i < vofa_I - 1; vofa_i++)
// 					vofa_float = 10 * vofa_float + (shujv[vofa_i] - '0');
// 				vofa_I = 0;

// 				if (shujv[1] == 0x3A)
// 				{
// 					switch (shujv[0])
// 					{
// 					// case 'S':my_dat.biaozhi =  shujv[2]  ; break;
// 					case 'p':
// 						// ZL_KP = vofa_float / 10.0;
// 						break;
// //					case 'i':
// //						spid.ki = vofa_float / 10.0;
// //						break;
// 					case 'd':
// 						 a = vofa_float / 10.0;
// 						break;
// //					case 'v':
// //						spid.target = vofa_float;
// //						break;
// 					}
// 				}
// 			}
// 			memset(rx_string, 0x00, sizeof(rx_string)); // 清空接收字符串
// 			rx_cnt = 0;									// 清空计数器
// 		}
// 	}

// 	HAL_UART_Receive_IT(&huart2, (uint8_t *)&rx_buff, 1);  // 再开启接收中断，若去掉只能接收一次
// }
