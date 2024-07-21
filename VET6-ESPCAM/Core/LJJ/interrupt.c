#include "interrupt.h"
#include "string.h"
#include "usart.h"





//usart2 bluetooth
#define USART2_REC_LEN  200
uint8_t USART2_RX_BUF[USART2_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.
uint16_t USART2_RX_STA=0;//接收状态标记//bit15：接收完成标志，bit14~0：接收到的有效字节数目
uint8_t USART2_NewData;//当前串口中断接收的1个字节数据的缓存
uint8_t RxState2 = 0; 

int target=0;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{ 
	
 	if(huart ==&huart2)
   { 
 	 if(RxState2 ==0){
       USART2_RX_BUF[USART2_RX_STA]=USART2_NewData; 					
       USART2_RX_STA++; 
       RxState2 = 1;			
 	}
 	 else if(RxState2 ==1){
       USART2_RX_BUF[USART2_RX_STA++]=USART2_NewData; 
 	 	if(USART2_RX_STA >0||USART2_RX_BUF[USART2_RX_STA-1]== 0x12)
 		 {

 			target = USART2_RX_BUF[USART2_RX_STA-2]-48;			
				
 			USART2_RX_STA=0;
 			memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
 			RxState2=2;
				
 		}	
 			}
			
 	 if(USART2_RX_STA>(USART2_REC_LEN-1)){
 		memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
 		USART2_RX_STA=0;	
 	  }
 	 else if(RxState2 ==2)   //接收异常
 	 {
 		USART2_RX_STA=0;
 		memset(USART2_RX_BUF,0,sizeof(USART2_RX_BUF));
 		RxState2=0;
 		}		
     }




	 
		
		

		
		
		
		

	HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); 



}


#include "stdio.h"
#include "main.h"

#ifdef __GNUC_
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

//重映射printf的功能
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
 
  return ch;
}

		


			
	


	

