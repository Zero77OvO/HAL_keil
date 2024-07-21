#include "matrix_keyboard.h" 

uint8_t Key_Scan(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	//前4个端口输出低电平
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_RESET);
	
	//前4个端口推挽输出
	GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	//后4个端口上拉输入
	GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	HAL_Delay(10);
	
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_4)==GPIO_PIN_RESET)//读取第1行
	{
		//后4个端口输出低电平
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);
		//后4个端口推挽输出
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		//前4个端口上拉输入
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0)==GPIO_PIN_RESET)return 1;
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)==GPIO_PIN_RESET)return 5;
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)==GPIO_PIN_RESET)return 9;
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3)==GPIO_PIN_RESET)return 13;
	}
	
  if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_5)==GPIO_PIN_RESET)//读取第2行
	{
		//后4个端口输出低电平
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);
		//后4个端口推挽输出
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		//前4个端口上拉输入
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0)==GPIO_PIN_RESET)return 2;
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)==GPIO_PIN_RESET)return 6;
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)==GPIO_PIN_RESET)return 10;
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3)==GPIO_PIN_RESET)return 14;
	}	

	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_6)==GPIO_PIN_RESET)//读取第3行
	{
		//后4个端口输出低电平
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);
		//后4个端口推挽输出
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		//前4个端口上拉输入
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0)==GPIO_PIN_RESET)return 3;
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)==GPIO_PIN_RESET)return 7;
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)==GPIO_PIN_RESET)return 11;
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3)==GPIO_PIN_RESET)return 15;
	}
	if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7)==GPIO_PIN_RESET)//读取第4行
	{
		//后4个端口输出低电平
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);
		//后4个端口推挽输出
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		//前4个端口上拉输入
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Pin =  GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0)==GPIO_PIN_RESET)return 4;
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)==GPIO_PIN_RESET)return 8;
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)==GPIO_PIN_RESET)return 12;
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3)==GPIO_PIN_RESET)return 16;
	}
	return 0;
}
