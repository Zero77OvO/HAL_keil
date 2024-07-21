#ifndef __HUIDU_H__
#define __HUIDU_H__
 
#include "stm32f4xx_hal.h"	//链接HAL库，还是一样，你的是那个芯片就改哪个，后面教你在哪找
#include <main.h>

#define   L4                 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_14)
#define   L3                 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_13)
#define   L2                 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12)
#define   L1                 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11)
#define   R1                 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_10)
#define   R2                 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9)
#define   R3                 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8)
#define   R4                 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7)





#endif
