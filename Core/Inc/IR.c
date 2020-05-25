/*
 * IR.c
 *
 *  Created on: 14-May-2020
 *      Author: admiral
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdint.h>
#include "stm32g0xx_hal.h"
#include "IR.h"
#include <string.h>

/*define---------------------*/
#define UART_BUFFER_MAX_DATA_LEN 256

/* Private variables ---------------------------------------------------------*/
extern UART_HandleTypeDef huart1;

char RxData_array[UART_BUFFER_MAX_DATA_LEN];
char TxData_array[UART_BUFFER_MAX_DATA_LEN];
int  UART_index = 0;
uint8_t p_rx_buffer;
char txdata[5] = "ok\r\n";

void UART_TX (void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *uart);

/*UART Transmit function*/
void UART_TX (void)
{
	HAL_UART_Transmit(&huart1,(uint8_t*)TxData_array,strlen(TxData_array),10);
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *uart)
{
	/*prevent unused argument(s) complication warning*/
	UNUSED(uart);

	RxData_array[UART_index] = p_rx_buffer;
	if(UART_index>2){
		if((RxData_array[UART_index]=='\n')||(UART_index >=UART_BUFFER_MAX_DATA_LEN))
		{
			UART_index =0;
			memset(RxData_array,0,UART_BUFFER_MAX_DATA_LEN);
		  return;

		}
	}
	UART_index++;
}

void LED(bool enable)
{
	if(enable)
		{
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	  }else
		{
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
	  }
}
