#include "adcc.h"
#include "adc.h"

float get_adc(ADC_HandleTypeDef *pin)
{
    HAL_ADC_Start(pin);
    int adc;
    adc = HAL_ADC_GetValue(pin);
    return adc * 3.3 / 4096;
}
