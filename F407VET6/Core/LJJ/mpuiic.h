#ifndef __MPUIIC_H
#define __MPUIIC_H

#include "head_files.h"


/*
// IO��������
//#define MPU_SDA_IN()  {GPIOB->CRH&=0XFFFF0FF;GPIOB->CRH|=((uint32_t)8<<12);}
//#define MPU_SDA_OUT() {GPIOB->CRH&=0XFFFF0FF;GPIOB->CRH|=((uint32_t)3<<12);}

 void MPU_SDA_IN(void);
 void MPU_SDA_OUT(void);

// IO��������
// #define MPU_IIC_SCL PBout(10)                             // SCL
// #define MPU_IIC_SDA PBout(11)                             // SDA
#define MPU_READ_SDA HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) // ����SDA
*/
// IIC���в�������





/* ���Ŷ��� */
#define MPU6050_IIC_SCL_GPIO_PORT            GPIOB
#define MPU6050_IIC_SCL_GPIO_PIN             GPIO_PIN_10
#define MPU6050_IIC_SCL_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)
#define MPU6050_IIC_SDA_GPIO_PORT            GPIOB
#define MPU6050_IIC_SDA_GPIO_PIN             GPIO_PIN_11
#define MPU6050_IIC_SDA_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

/* IO���� */
#define MPU6050_IIC_SCL(x)                   do{ x ?                                                                                             \
                                                    HAL_GPIO_WritePin(MPU6050_IIC_SCL_GPIO_PORT, MPU6050_IIC_SCL_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin(MPU6050_IIC_SCL_GPIO_PORT, MPU6050_IIC_SCL_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)

#define MPU6050_IIC_SDA(x)                   do{ x ?                                                                                             \
                                                    HAL_GPIO_WritePin(MPU6050_IIC_SDA_GPIO_PORT, MPU6050_IIC_SDA_GPIO_PIN, GPIO_PIN_SET) :    \
                                                    HAL_GPIO_WritePin(MPU6050_IIC_SDA_GPIO_PORT, MPU6050_IIC_SDA_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)

#define MPU6050_IIC_READ_SDA()               HAL_GPIO_ReadPin(MPU6050_IIC_SDA_GPIO_PORT, MPU6050_IIC_SDA_GPIO_PIN)

/* �������� */
//void mpu6050_iic_start(void);                /* ����IIC��ʼ�ź� */
//void mpu6050_iic_stop(void);                 /* ����IICֹͣ�ź� */
//uint8_t mpu6050_iic_wait_ack(void);          /* �ȴ�IICӦ���ź� */
//void mpu6050_iic_ack(void);                  /* ����ACKӦ���ź� */
//void mpu6050_iic_nack(void);                 /* ������ACKӦ���ź� */
//void mpu6050_iic_send_byte(uint8_t dat);     /* IIC����һ���ֽ� */
//uint8_t mpu6050_iic_read_byte(uint8_t ack);  /* IIC����һ���ֽ� */
//void mpu6050_iic_init(void);                 /* ��ʼ��IIC�ӿ� */
																								
																								
//void MPU_IIC_Delay(void);                // MPU IIC��ʱ����
void MPU_IIC_Init(void);                 // ��ʼ��IIC��IO��
void MPU_IIC_Start(void);                // ����IIC��ʼ�ź�
void MPU_IIC_Stop(void);                 // ����IICֹͣ�ź�
void MPU_IIC_Send_Byte(uint8_t txd);          // IIC����һ���ֽ�
uint8_t MPU_IIC_Read_Byte(unsigned char ack); // IIC��ȡһ���ֽ�
uint8_t MPU_IIC_Wait_Ack(void);               // IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);                  // IIC����ACK�ź�
void MPU_IIC_NAck(void);                 // IIC������ACK�ź�

void IMPU_IC_Write_One_Byte(uint8_t daddr, uint8_t addr, uint8_t data);
uint8_t MPU_IIC_Read_One_Byte(uint8_t daddr, uint8_t addr);


#endif
