#include "interrupt.h"
#include "usart.h"
#include "adcc.h"
#include "adc.h"
#include "tim.h"
#include "pid.h"

int time_1s = 0;
int flag_stop = 0;
extern int flag_init;
extern float out;
int time_500ms = 0;
int flag_500ms = 0;
int test_flag = 0;
int flag_500ms2 = 0;
int time_500ms2 = 0;
int num_counter = 2;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {





        
        num_counter = __HAL_TIM_GET_COUNTER(&htim2);

            if (++time_1s == 100)
            {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                time_1s = 0;
            }

    // if (flag_stop == 0 && flag_init == 0)
    // {
    //     out = vertical_PID_value((get_adc(&hadc1) * 1000), 1860);
    //     if (out < 400 && out > 0)
    //         out = 400;
    //     if (out > -400 && out < 0)
    //         out = -400;
    //     if (out > 0)
    //     {
    //         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    //         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
    //         __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, out);
    //     }
    //     if (out < 0)
    //     {
    //         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    //         HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
    //         __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, -out);
    //     }
    // }
    }
}

char rxdatas[30];
uint8_t rxdata;
unsigned char rx_pointer;
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    rxdatas[rx_pointer++] = rxdata - 48;
    HAL_UART_Receive_IT(&huart3, &rxdata, 1);
}
