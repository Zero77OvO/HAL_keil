#include "adcc.h"
//#include "adc.h"



#define N 3


int time =0;
int value_buf[N];
int sum = 0;
int curNum = 0;


float data[100];
float averageFilter(float in_data)
{
	float sum = 0;
	for(int i=0; i<3; i++)
	{
		data[i]=data[i+1];
		sum = sum + data[i];
	}
	data[3] = in_data;
	sum = sum + data[3];
	
	return(sum/4);
 
}

float averagelocation_y(float in_data)
{
	float sum = 0;
	for(int i=0; i<3; i++)
	{
		data[i]=data[i+1];
		sum = sum + data[i];
	}
	data[3] = in_data;
	sum = sum/3;
	if(data[3]-sum>20||data[3]-sum<-20){


       return(data[2]); 
    }
    else{

        return(data[3]); 
    }


	
 
}


//float get_adc(ADC_HandleTypeDef *pin)
//{   
//    HAL_ADC_Start(pin);
//    int adc;
//    adc = HAL_ADC_GetValue(pin);
//	  
//	return adc* 3.6 / 4096 ;
//	
//    
//}

// float get_adc(ADC_HandleTypeDef *pin)
// {   
//     HAL_ADC_Start(pin);
//     int adc;
//     adc = HAL_ADC_GetValue(pin);

// 		return adc* 3.6 / 4095 ;
	
	
    
// }

int moveAverageFilter(int now)
{
    if (curNum < N)
    {
        value_buf[curNum] = now;
        sum += value_buf[curNum];
        curNum++;
        return sum / curNum;
    }
    else
    {
        sum -= sum / N;
        sum += now;
        return sum / N;
    }
}
