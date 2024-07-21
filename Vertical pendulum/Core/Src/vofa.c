#include <main.h>
#include "vofa.h"
#include "Bluetooth.h"
#include "L298N.h"
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

//extern double A;
//extern double B;

extern float kp_x;
extern float ki_x;
extern float kd_x;
extern float target_value;
extern Motor motor1;
extern float speed;


void vodka_JustFloat_send(UART_HandleTypeDef *huart)
{

	
//	Send_Data(huart, (double)A);
//	Send_Data(huart, (double)B);

	// Send_Data(huart, (float)speed[1]);
	// Send_Data(huart, (float)speed[2]);
	// Send_Data(huart, (float)spid.out);

	 Send_Data(huart, (float)kp_x);
	 Send_Data(huart, (float)ki_x);
	 Send_Data(huart, (float)kd_x);
	 Send_Data(huart, (float)target_value);
	 Send_Data(huart, (float)motor1.speed);

	// Send_Data(huart, float(speed_intg));
	Send_Tail(huart);
}

/**example**/
// while(1)
// {
// 	vodka_JustFloat_send(&huart1);
// }

#define RXSTRSIZE 256		  // �������ֽ���
uint8_t rx_string[RXSTRSIZE]; // �����ַ�������
uint8_t rx_cnt = 0;			  // �����ַ�������
uint8_t rx_buff;			  // ���ջ���
uint8_t RxBuff;
unsigned char shujv[12];
int vofa_i = 0, vofa_I = 0;
double vofa_float;





uint8_t RxState = 0; 
char num;
char num2;
char num3;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t dat;
	if (huart->Instance == huart3.Instance)
	{
		
		// �����Ǵ��ڽ����ж�ҵ�����
		if (rx_cnt++ >= RXSTRSIZE - 1) // ����ж�
		{
			rx_cnt = 0;
			memset(rx_string, 0x00, sizeof(rx_string));
		}
		else
		{
			dat = rx_buff; // ��������ת��

			shujv[vofa_I++] = dat;

			if (dat == 0x0a)
			{

				for (vofa_i = 2, vofa_float = 0; vofa_i < vofa_I - 1; vofa_i++)
					vofa_float = 10 * vofa_float + (shujv[vofa_i] - '0');
				vofa_I = 0;

				if (shujv[1] == 0x3A)
				{
					switch (shujv[0])
					{
					// case 'S':my_dat.biaozhi =  shujv[2]  ; break;
					case 'Q'://VOFA
						target_value = vofa_float; //keil
						break;
					case 'W':
						motor1.speed = vofa_float;
						break;
					case 'P':
						kp_x = vofa_float;
						break;
					case 'I':
						ki_x = vofa_float;
						break;
					case 'D':
						kd_x = vofa_float;
						break;
					}
				}
			}
			memset(rx_string, 0x00, sizeof(rx_string)); // ��ս����ַ���
			rx_cnt = 0;									// ��ռ�����
		}
	}
	
//   if(huart ==&huart3)
//  { 
//			if(RxState ==0){
//      USART1_RX_BUF[USART1_RX_STA&0X7FFF]=USART1_NewData; 					
//      USART1_RX_STA++; 
//      RxState = 1;			
//			}
//			else if(RxState ==1){
//      USART1_RX_BUF[USART1_RX_STA++]=USART1_NewData; 

//				
//      if(USART1_RX_STA>(USART1_REC_LEN-1)){
//			memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
//			USART1_RX_STA=0;
//			}
//			
//			if(USART1_RX_STA>0||USART1_RX_BUF[USART1_RX_STA-1]== 0x0A)
//			{
//				
//			num = USART1_RX_BUF[USART1_RX_STA-2];			
//			//num2 = USART1_RX_BUF[USART1_RX_STA-4];
//		//	num3 = USART1_RX_BUF[USART1_RX_STA-5];	
//				
//			USART1_RX_STA=0;
//			memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
//			RxState=0;
//				
//			}
//			
//			}
//			
//			if(USART1_RX_STA>(USART1_REC_LEN-1)){
//			memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
//			USART1_RX_STA=0;
//			
//			}
//			else if(RxState ==2)   //接收异常
//			{
//				USART1_RX_STA=0;
//			  memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
//				}
//			
//			
//			
//			
//      		
//			
//    }	
  //HAL_UART_Receive_IT(&huart1,(uint8_t *)&USART1_NewData,1);
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&rx_buff, 1);  // �ٿ��������жϣ���ȥ��ֻ�ܽ���һ��
}
