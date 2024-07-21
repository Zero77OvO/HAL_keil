#ifndef _INTERRUPT_H
#define _INTERRUPT_H






extern uint8_t USART1_NewData_1;



//k210
#define USART1_REC_LEN  200
extern uint8_t  USART1_RX_BUF[USART1_REC_LEN];
extern uint16_t USART1_RX_STA;
extern uint8_t USART1_NewData;
extern uint8_t RxState1; 

extern float x1;
extern float y1;

extern float x2;
extern float y2;

extern float x3;
extern float y3;

extern float x4;
extern float y4;


extern float x_red;
extern float y_red;

extern float x_green;
extern float y_green;

extern float horizon_pid;
extern float vertical_pid;
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
#define USART3_REC_LEN  200//����USART2�������ֽ���
extern uint8_t  USART3_RX_BUF[USART3_REC_LEN];//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�ΪУ���
extern uint16_t USART3_RX_STA;//����״̬���
extern uint8_t USART3_NewData;//��ǰ�����жϽ��յ�1���ֽ����ݵĻ���
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


//其他变量
extern int point_step;		//记录边
extern int move_step_total;	//每条边细分的步数
extern int move_step_now; 	//记录激光走的点

extern int x;
extern int y;


extern int mode;

#define MAX_POINTS 10 
extern int x_history[MAX_POINTS];
extern int y_history[MAX_POINTS];
extern int num_points;  // 当前历史坐标数
#endif
