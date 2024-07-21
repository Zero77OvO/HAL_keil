#include "HX711.h"

// �����
#define HX711_NUM_BITS            24
#define HX711_TIMEOUT             1000000  // ��ʱ����

uint32_t fac_us;



// ��ʼ��GPIO
void HX711_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // ʹ��GPIOʱ��
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // ����SCK����Ϊ���
    GPIO_InitStruct.Pin = HX711_SCK_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(HX711_SCK_GPIO_PORT, &GPIO_InitStruct);

    // ����DATA����Ϊ����
    GPIO_InitStruct.Pin = HX711_DATA_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(HX711_DATA_GPIO_PORT, &GPIO_InitStruct);
}

// ����DATA����Ϊ���
void HX711_Data_Out(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = HX711_DATA_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(HX711_DATA_GPIO_PORT, &GPIO_InitStruct);
}

// ����DATA����Ϊ����
void HX711_Data_In(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = HX711_DATA_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(HX711_DATA_GPIO_PORT, &GPIO_InitStruct);
}

// ��ȡHX711����
uint32_t Read_HX711(void) {
    uint32_t value = 0;
    unsigned char i;

    // ��������״̬
    HX711_Data_Out();
    HAL_GPIO_WritePin(HX711_DATA_GPIO_PORT, HX711_DATA_GPIO_PIN, GPIO_PIN_SET);
    HAL_Delay_us(1);
    HAL_GPIO_WritePin(HX711_SCK_GPIO_PORT, HX711_SCK_GPIO_PIN, GPIO_PIN_RESET);
    HAL_Delay_us(1);
    HX711_Data_In();

    // �ȴ�DATA���ű�Ϊ�͵�ƽ
    // unsigned long timeout = HX711_TIMEOUT;
    while (HAL_GPIO_ReadPin(HX711_DATA_GPIO_PORT, HX711_DATA_GPIO_PIN) == GPIO_PIN_SET);

    // ��ȡ24λ����
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

    // ��25��ʱ������ѡ����һ��ת��������
    HAL_GPIO_WritePin(HX711_SCK_GPIO_PORT, HX711_SCK_GPIO_PIN, GPIO_PIN_SET);
    HAL_Delay_us(1);
    value = value ^ 0x800000;  // ����λ����
    HAL_GPIO_WritePin(HX711_SCK_GPIO_PORT, HX711_SCK_GPIO_PIN, GPIO_PIN_RESET);
    HAL_Delay_us(1);

    return value;
}

// ���ǵÿ��У�����
