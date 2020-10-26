/*==================================================================================================

  semphr_FreeRTOS_qemu.c

  Used hardware: STM32F4-Discovery evaluation board (QEMU)

  Example of using the FreeRTOS Real-Time Operating System on the STM32F4-Discovery board.

  ==================================================================================================
*/

#include "stm32f4_discovery.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"


#define BUFFER_SIZE 8

QueueHandle_t xQueue1;
uint8_t buffer[BUFFER_SIZE];


void xProdTask(void *pvParam){
  const TickType_t xPeriod = 250 / portTICK_PERIOD_MS;
  TickType_t xLastWakeTime = xTaskGetTickCount();
  uint8_t data_i = 0;

  while(1){

  xQueueSend(xQueue1,&data_i,(TickType_t) 10); 	// se a mensagem foi enviada em 10 ticks

	// data prod
  data_i++;
  data_i &= 0x0F;

  vTaskDelayUntil(&xLastWakeTime, xPeriod);
  } // while
} // xProdTask


void xConsTask(void *pvParam){
  const TickType_t xPeriod = 250 / portTICK_PERIOD_MS;
  TickType_t xLastWakeTime = xTaskGetTickCount();
  uint8_t data_o;

  while(1){

	if(xQueueReceive(xQueue1,&data_o,(TickType_t) 10 ) == pdPASS){ //conseguiu receber

		    // data consumption
		    if (data_o & 0x01) BSP_LED_On(LED3);
		    else BSP_LED_Off(LED3);

		    if (data_o & 0x02) BSP_LED_On(LED4);
		    else BSP_LED_Off(LED4);

		    if (data_o & 0x04) BSP_LED_On(LED6);
		    else BSP_LED_Off(LED6);

		    if (data_o & 0x08) BSP_LED_On(LED5);
		    else BSP_LED_Off(LED5);
	}
	vTaskDelayUntil(&xLastWakeTime, xPeriod);
  } // while
} // xConsTask


void main(void){
  __HAL_RCC_GPIOD_CLK_ENABLE();
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED6);
  BSP_LED_Init(LED5);

  xTaskCreate(xProdTask, "Producer", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);
  xTaskCreate(xConsTask, "Consumer", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

  xQueue1 = xQueueCreate(8, sizeof( BUFFER_SIZE ));


  vTaskStartScheduler();
  while(1);
} // main
