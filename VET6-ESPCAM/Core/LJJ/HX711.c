#include "HX711.h"

// 定义宏
#define HX711_NUM_BITS            24
#define HX711_TIMEOUT             1000000  // 超时计数

uint32_t fac_us;



// 初始化GPIO
void HX711_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能GPIO时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置SCK引脚为输出
    GPIO_InitStruct.Pin = HX711_SCK_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(HX711_SCK_GPIO_PORT, &GPIO_InitStruct);

    // 配置DATA引脚为输入
    GPIO_InitStruct.Pin = HX711_DATA_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(HX711_DATA_GPIO_PORT, &GPIO_InitStruct);
}

// 设置DATA引脚为输出
void HX711_Data_Out(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = HX711_DATA_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(HX711_DATA_GPIO_PORT, &GPIO_InitStruct);
}

// 设置DATA引脚为输入
void HX711_Data_In(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = HX711_DATA_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(HX711_DATA_GPIO_PORT, &GPIO_InitStruct);
}

// 读取HX711数据
uint32_t Read_HX711(void) {
    uint32_t value = 0;
    unsigned char i;

    // 设置引脚状态
    HX711_Data_Out();
    HAL_GPIO_WritePin(HX711_DATA_GPIO_PORT, HX711_DATA_GPIO_PIN, GPIO_PIN_SET);
    HAL_Delay_us(1);
    HAL_GPIO_WritePin(HX711_SCK_GPIO_PORT, HX711_SCK_GPIO_PIN, GPIO_PIN_RESET);
    HAL_Delay_us(1);
    HX711_Data_In();

    // 等待DATA引脚变为低电平
    // unsigned long timeout = HX711_TIMEOUT;
    while (HAL_GPIO_ReadPin(HX711_DATA_GPIO_PORT, HX711_DATA_GPIO_PIN) == GPIO_PIN_SET);

    // 读取24位数据
    for (i = 0; i < HX711_NUM_BITS; i++) {
        HAL_GPIO_WritePin(HX711_SCK_GPIO_PORT, HX711_SCK_GPIO_PIN, GPIO_PIN_SET);
        HAL_Delay_us(1);
        value = value << 1;
        HAL_GPIO_WritePin(HX711_SCK_GPIO_PORT, HX711_SCK_GPIO_PIN, GPIO_PIN_RESET);
        HAL_Delay_us(1);
        if (HAL_GPIO_ReadPin(HX711_DATA_GPIO_PORT, HX711_DATA_GPIO_PIN) == GPIO_PIN_SET) {
            value++;
        }
    }

    // 第25个时钟脉冲选择下一次转换的增益
    HAL_GPIO_WritePin(HX711_SCK_GPIO_PORT, HX711_SCK_GPIO_PIN, GPIO_PIN_SET);
    HAL_Delay_us(1);
    value = value ^ 0x800000;  // 符号位修正
    HAL_GPIO_WritePin(HX711_SCK_GPIO_PORT, HX711_SCK_GPIO_PIN, GPIO_PIN_RESET);
    HAL_Delay_us(1);

    return value;
}

// 最后记得空行！！！
