#include <main.h>
#include "vofa.h"
#include "Bluetooth.h"
#include "Raspi.h"



//usart1 bluetooth
uint8_t RxState = 0; 
char num;
char num2;
char num3;


//usart2 vofa




//usart3 raspi
uint8_t RxState3 = 0; 
char pinum;
char pinum2;
char pinum3;
char pinum4;
char pinum5;









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
extern float set_Speed;
extern float t;
extern float b;

void vodka_JustFloat_send(UART_HandleTypeDef *huart)
{

	Send_Data(huart, (float)set_Speed);
	Send_Data(huart, (float)t);
	Send_Data(huart, (float)b);
	// Send_Data(huart, (float)speed[1]);
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

#define RXSTRSIZE 256		  // �������ֽ���
uint8_t rx_string[RXSTRSIZE]; // �����ַ�������
uint8_t rx_cnt = 0;			  // �����ַ�������
uint8_t rx_buff;			  // ���ջ���
uint8_t RxBuff;
unsigned char shujv[12];
int vofa_i = 0, vofa_I = 0;
float vofa_float;






void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t dat;
	if (huart->Instance == huart2.Instance)
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
					case 'a':
						set_Speed = vofa_float;
						break;
//					case 'i':
//						spid.ki = vofa_float / 10.0;
//						break;
					case 't':
						 t = vofa_float;
						break;
					case 'b':
						b = vofa_float;
						break;
					}
				}
			}
			memset(rx_string, 0x00, sizeof(rx_string)); // ��ս����ַ���
			rx_cnt = 0;									// ��ռ�����
		}
	}
	
   if(huart ==&huart1)
  { 
			if(RxState ==0){
      USART1_RX_BUF[USART1_RX_STA&0X7FFF]=USART1_NewData; 					
      USART1_RX_STA++; 
      RxState = 1;			
			}
			else if(RxState ==1){
      USART1_RX_BUF[USART1_RX_STA++]=USART1_NewData; 

				
      if(USART1_RX_STA>(USART1_REC_LEN-1)){
			memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
			USART1_RX_STA=0;
			}
			
			if(USART1_RX_STA>0||USART1_RX_BUF[USART1_RX_STA-1]== 0x0A)
			{
				
			num = USART1_RX_BUF[USART1_RX_STA-2];			
			//num2 = USART1_RX_BUF[USART1_RX_STA-4];
		//	num3 = USART1_RX_BUF[USART1_RX_STA-5];	
				
			USART1_RX_STA=0;
			memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
			RxState=0;
				
			}
			
			}
			
			if(USART1_RX_STA>(USART1_REC_LEN-1)){
			memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
			USART1_RX_STA=0;
			
			}
			else if(RxState ==2)   //接收异常
			{
				USART1_RX_STA=0;
			  memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
				}
			
			
			
			
      		
			
    }
	
 	  if(huart ==&huart3)
   { 
			if(RxState3 ==0){
      USART3_RX_BUF[USART3_RX_STA&0X7FFF]=USART3_NewData; 					
      USART3_RX_STA++; 
      RxState3 = 1;			
			}
			else if(RxState3 ==1){
      USART3_RX_BUF[USART3_RX_STA++]=USART3_NewData; 

				
				
      if(USART3_RX_STA>(USART3_REC_LEN-1)){
			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
			USART3_RX_STA=0;
			}
			
			if(USART3_RX_BUF[USART3_RX_STA-1]== 0x0a&&USART3_RX_STA>16) //计数器好像是假的，明天测测阈值是多少
			{
				
			pinum = USART3_RX_BUF[USART3_RX_STA-6];			
			pinum2 = USART3_RX_BUF[USART3_RX_STA-5];
			pinum3 = USART3_RX_BUF[USART3_RX_STA-4];
      pinum4 = USART3_RX_BUF[USART3_RX_STA-3];
			pinum5 = USART3_RX_BUF[USART3_RX_STA-2];	
				
			USART3_RX_STA=0;
			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
			RxState3=0;
				
			}
		/*	else if(USART3_RX_BUF[USART3_RX_STA-1]== 0x0a&&USART3_RX_STA>15)
			{
				
				
			pinum = USART3_RX_BUF[USART3_RX_STA-5];
			pinum2 = USART3_RX_BUF[USART3_RX_STA-4];
      pinum3 = USART3_RX_BUF[USART3_RX_STA-3];
			pinum4 = USART3_RX_BUF[USART3_RX_STA-2];	
				
			USART3_RX_STA=0;
			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
			RxState3=0;
				
			}
    	else if(USART3_RX_BUF[USART3_RX_STA-1]== 0x0a&&USART3_RX_STA>14)
			{
				
				
			pinum = USART3_RX_BUF[USART3_RX_STA-4];
			pinum2 = USART3_RX_BUF[USART3_RX_STA-3];
      pinum3 = USART3_RX_BUF[USART3_RX_STA-2];
			
				
			USART3_RX_STA=0;
			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
			RxState3=0;
				
			}*/
			
			
			}
			
			if(USART3_RX_STA>(USART3_REC_LEN-1)){
			memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
			USART3_RX_STA=0;
			
			}
			else if(RxState3 ==2)   //接收异常
			{
				USART3_RX_STA=0;
			  memset(USART3_RX_BUF,0,sizeof(USART3_RX_BUF));
				}
			
			
			
			
      		
			
    }		
		
		
/*  	if(huart ==&huart3)
    { 
			
      USART3_RX_BUF[USART3_RX_STA&0X7FFF]=USART3_NewData; 					
      USART3_RX_STA++;  
			
						
      if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;
 
			//num = USART1_RX_BUF[USART1_RX_STA];
			
			HAL_UART_Receive_IT(&huart3,(uint8_t *)&USART3_NewData,1);
			
			pinum = USART3_RX_BUF[USART3_RX_STA-1];			
			pinum2 = USART3_RX_BUF[USART3_RX_STA-2];
			pinum3 = USART3_RX_BUF[USART3_RX_STA-3];
      pinum4 = USART3_RX_BUF[USART3_RX_STA-4];
			pinum5 = USART3_RX_BUF[USART3_RX_STA-5];
    }		*/
		
		
		
		
  HAL_UART_Receive_IT(&huart1,(uint8_t *)&USART1_NewData,1);
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&rx_buff, 1);  
	HAL_UART_Receive_IT(&huart3,(uint8_t *)&USART3_NewData,1);
}
