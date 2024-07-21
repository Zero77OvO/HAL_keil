#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "main.h"

#define USE_HORIZONTAL 1 // ���ú�������������ʾ 0��1Ϊ���� 2��3Ϊ����

#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif

//-----------------LCD�˿ڶ���----------------

// #define LCD_SCLK_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_12)//SCL=SCLK
// #define LCD_SCLK_Set() GPIO_SetBits(GPIOG,GPIO_Pin_12)

// #define LCD_MOSI_Clr() GPIO_ResetBits(GPIOD,GPIO_Pin_5)//SDA=MOSI
// #define LCD_MOSI_Set() GPIO_SetBits(GPIOD,GPIO_Pin_5)

// #define LCD_RES_Clr()  GPIO_ResetBits(GPIOD,GPIO_Pin_4)//RES
// #define LCD_RES_Set()  GPIO_SetBits(GPIOD,GPIO_Pin_4)

// #define LCD_DC_Clr()   GPIO_ResetBits(GPIOD,GPIO_Pin_15)//DC
// #define LCD_DC_Set()   GPIO_SetBits(GPIOD,GPIO_Pin_15)

// #define LCD_CS_Clr()   GPIO_ResetBits(GPIOD,GPIO_Pin_1)//CS
// #define LCD_CS_Set()   GPIO_SetBits(GPIOD,GPIO_Pin_1)

// #define LCD_BLK_Clr()  GPIO_ResetBits(GPIOE,GPIO_Pin_8)//BLK
// #define LCD_BLK_Set()  GPIO_SetBits(GPIOE,GPIO_Pin_8)

#define LCD_RES_Clr() HAL_GPIO_WritePin(TFT_RES_GPIO_Port, TFT_RES_Pin, GPIO_PIN_RESET) // RES
#define LCD_RES_Set() HAL_GPIO_WritePin(TFT_RES_GPIO_Port, TFT_RES_Pin, GPIO_PIN_SET)

#define LCD_DC_Clr() HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_RESET) // DC
#define LCD_DC_Set() HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET)

#define LCD_CS_Clr() HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET) // CS
#define LCD_CS_Set() HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET)

#define LCD_BLK_Clr() HAL_GPIO_WritePin(TFT_BL_GPIO_Port, TFT_BL_Pin, GPIO_PIN_RESET) // BLK
#define LCD_BLK_Set() HAL_GPIO_WritePin(TFT_BL_GPIO_Port, TFT_BL_Pin, GPIO_PIN_SET)

//void LCD_GPIO_Init(void);                             // ��ʼ��GPIO
void LCD_Writ_Bus(uint8_t dat);                            // ģ��SPIʱ��
void LCD_WR_DATA8(uint8_t dat);                            // д��һ���ֽ�
void LCD_WR_DATA(uint16_t dat);                            // д�������ֽ�
void LCD_WR_REG(uint8_t dat);                              // д��һ��ָ��
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2); // �������꺯��
void LCD_Init(void);                                  // LCD��ʼ��
#endif
