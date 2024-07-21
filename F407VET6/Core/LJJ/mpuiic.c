#include "mpuiic.h"





/**
 ****************************************************************************************************
 * @file        mpu6050_iic.c
 * @version     V1.0
 * @date        2022-06-21

 *
 ****************************************************************************************************
 */



/**
 * @brief       IIC�ӿ���ʱ���������ڿ���IIC��д�ٶ�
 * @param       ��
 * @retval      ��
 */
static inline void mpu6050_iic_delay(void)
{
    delaynus_tim(2);
}

/**
 * @brief       ����IIC��ʼ�ź�
 * @param       ��
 * @retval      ��
 */
void MPU_IIC_Start(void)
{
    MPU6050_IIC_SDA(1);
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SDA(0);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(0);
    mpu6050_iic_delay();
}

/**
 * @brief       ����IICֹͣ�ź�
 * @param       ��
 * @retval      ��
 */
void MPU_IIC_Stop(void)
{
    MPU6050_IIC_SDA(0);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SDA(1);
    mpu6050_iic_delay();
}

/**
 * @brief       �ȴ�IICӦ���ź�
 * @param       ��
 * @retval      0: Ӧ���źŽ��ճɹ�
 *              1: Ӧ���źŽ���ʧ��
 */
uint8_t MPU_IIC_Wait_Ack(void)
{
    uint8_t waittime = 0;
    uint8_t rack = 0;
    
    MPU6050_IIC_SDA(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    
    while (MPU6050_IIC_READ_SDA())
    {
        waittime++;
        
        if (waittime > 250)
        {
            MPU_IIC_Stop();
            rack = 1;
            break;
        }
    }
    
    MPU6050_IIC_SCL(0);
    mpu6050_iic_delay();
    
    return rack;
}

/**
 * @brief       ����ACKӦ���ź�
 * @param       ��
 * @retval      ��
 */
void MPU_IIC_Ack(void)
{
    MPU6050_IIC_SDA(0);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(0);
    mpu6050_iic_delay();
    MPU6050_IIC_SDA(1);
    mpu6050_iic_delay();
}

/**
 * @brief       ������ACKӦ���ź�
 * @param       ��
 * @retval      ��
 */
void MPU_IIC_NAck(void)
{
    MPU6050_IIC_SDA(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(0);
    mpu6050_iic_delay();
}

/**
 * @brief       IIC����һ���ֽ�
 * @param       dat: Ҫ���͵�����
 * @retval      ��
 */
void MPU_IIC_Send_Byte(uint8_t dat)
{
    uint8_t t;
    
    for (t=0; t<8; t++)
    {
        MPU6050_IIC_SDA((dat & 0x80) >> 7);
        mpu6050_iic_delay();
        MPU6050_IIC_SCL(1);
        mpu6050_iic_delay();
        MPU6050_IIC_SCL(0);
        dat <<= 1;
    }
    MPU6050_IIC_SDA(1);
}

/**
 * @brief       IIC����һ���ֽ�
 * @param       ack: ack=1ʱ������ack; ack=0ʱ������nack
 * @retval      ���յ�������
 */
uint8_t MPU_IIC_Read_Byte(uint8_t ack)
{
    uint8_t i;
    uint8_t dat = 0;
    
    for (i = 0; i < 8; i++ )
    {
        dat <<= 1;
        MPU6050_IIC_SCL(1);
        mpu6050_iic_delay();
        
        if (MPU6050_IIC_READ_SDA())
        {
            dat++;
        }
        
        MPU6050_IIC_SCL(0);
        mpu6050_iic_delay();
    }
    
    if (ack == 0)
    {
        MPU_IIC_NAck();
    }
    else
    {
        MPU_IIC_Ack();
    }

    return dat;
}

/**
 * @brief       ��ʼ��IIC�ӿ�
 * @param       ��
 * @retval      ��
 */
void MPU_IIC_Init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* ʹ��SCL��SDA����GPIO��ʱ�� */
    MPU6050_IIC_SCL_GPIO_CLK_ENABLE();
    MPU6050_IIC_SDA_GPIO_CLK_ENABLE();
    
    /* ��ʼ��SCL���� */
    gpio_init_struct.Pin    = MPU6050_IIC_SCL_GPIO_PIN;  /* SCL���� */
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;          /* ������� */
    gpio_init_struct.Pull   = GPIO_PULLUP;                  /* ���� */
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;         /* ���� */
    HAL_GPIO_Init(MPU6050_IIC_SCL_GPIO_PORT, &gpio_init_struct);
    
    /* ��ʼ��SDA���� */
    gpio_init_struct.Pin    = MPU6050_IIC_SDA_GPIO_PIN;  /* SDA���� */
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_OD;          /* ��©��� */
    HAL_GPIO_Init(MPU6050_IIC_SDA_GPIO_PORT, &gpio_init_struct);
    
    MPU_IIC_Stop();
}


/*
 * @description: MPU IIC ��ʱ2us����
 * 	72Ϊ������Ƶ��2Ϊʱ�� 4Ϊָ����������
 * @return 
 
 
 // 6 clk 7 sda

 void MPU_SDA_IN(void)
{
    
    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC->APB2ENR|=1<<4;//��ʹ������IO portcʱ��
    __HAL_RCC_GPIOB_CLK_ENABLE();
 
    GPIO_InitStructure.Pin = GPIO_PIN_11;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStructure.Pull= GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
   // __HAL_RCC_I2C2_CLK_ENABLE();
}
 
void MPU_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC->APB2ENR|=1<<4;//��ʹ������IO portcʱ��
    __HAL_RCC_GPIOB_CLK_ENABLE();
 
    GPIO_InitStructure.Pin = GPIO_PIN_11;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);
   //	__HAL_RCC_I2C2_CLK_ENABLE();
} 

void MPU_IIC_Delay(void)
{  //delay_us(2);
	delaynus_tim(2);
	uint32_t Delay = 2 * 168/2;
	do
	{
		__NOP();
	} while (Delay--);
	
}

// ��ʼ��IIC
void MPU_IIC_Init(void)
{
	;
}
// ����IIC��ʼ�ź�
void MPU_IIC_Start(void)
{
	MPU_SDA_OUT(); // sda�����
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	MPU_IIC_Delay();
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET); // START:when CLK is high,DATA change form high to low
	MPU_IIC_Delay();
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET); // ǯסI2C���ߣ�׼�����ͻ��������
}
// ����IICֹͣ�ź�
void MPU_IIC_Stop(void)
{
	MPU_SDA_OUT(); // sda�����
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET); // STOP:when CLK is high DATA change form low to high
	MPU_IIC_Delay();
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET); // ����I2C���߽����ź�
	MPU_IIC_Delay();
	MPU_IIC_Delay();
}
// �ȴ�Ӧ���źŵ���
// ����ֵ��1������Ӧ��ʧ��
//         0������Ӧ��ɹ�
uint8_t MPU_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime = 0;
	MPU_SDA_IN(); // SDA����Ϊ����
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	MPU_IIC_Delay();
	while (MPU_READ_SDA)
	{
		ucErrTime++;
		if (ucErrTime > 250)
		{
			MPU_IIC_Stop();
			return 1;
		}
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET); // ʱ�����0
	return 0;
}
// ����ACKӦ��
void MPU_IIC_Ack(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	MPU_SDA_OUT();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
}
// ������ACKӦ��
void MPU_IIC_NAck(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	MPU_SDA_OUT();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	MPU_IIC_Delay();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
}
// IIC����һ���ֽ�
// ���شӻ�����Ӧ��
// 1����Ӧ��
// 0����Ӧ��
void MPU_IIC_Send_Byte(uint8_t txd)
{
	uint8_t t;
	MPU_SDA_OUT();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET); // ����ʱ�ӿ�ʼ���ݴ���
	for (t = 0; t < 8; t++)
	{
		if ((txd & 0x80) >> 7)
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
		txd <<= 1;
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
		MPU_IIC_Delay();
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
		MPU_IIC_Delay();
	}
}
// ��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t MPU_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	MPU_SDA_IN(); // SDA����Ϊ����
	for (i = 0; i < 8; i++)
	{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
		MPU_IIC_Delay();
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
		receive <<= 1;
		if (MPU_READ_SDA)
			receive++;
		MPU_IIC_Delay();
	}
	if (!ack)
		MPU_IIC_NAck(); // ����nACK
	else
		MPU_IIC_Ack(); // ����ACK
	return receive;
}
*/

