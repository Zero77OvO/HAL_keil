#ifndef _ADCC_H
#define _ADCC_H

#include "main.h"

// float get_adc(ADC_HandleTypeDef *pin);
// int moveAverageFilter(int now);
float averageFilter(float in_data);
float averagelocation_y(float in_data);
#endif
