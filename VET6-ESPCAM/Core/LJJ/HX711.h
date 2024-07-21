#ifndef __HX711_H
#define __HX711_H

#include "stm32f4xx_hal.h"

// 定义GPIO引脚和时钟
#define HX711_DATA_GPIO_PORT      GPIOA
#define HX711_DATA_GPIO_PIN       GPIO_PIN_7

#define HX711_SCK_GPIO_PORT       GPIOA
#define HX711_SCK_GPIO_PIN        GPIO_PIN_6

void HX711_GPIO_Init(void);
uint32_t Read_HX711(void);

#endif

// 最后记得空行！！！
