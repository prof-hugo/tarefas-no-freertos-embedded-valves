/*==================================================================================================

  tasks_FreeRTOS_qemu.c

  Used hardware: STM32F4-Discovery evaluation board (QEMU)

  Example of using the FreeRTOS Real-Time Operating System on the STM32F4-Discovery board.

  ==================================================================================================
*/

#include "stm32f4_discovery.h"
#include "FreeRTOS.h"
#include "task.h"


void vBlinkLED3(void *pvParam){ // LED 3
  TickType_t xLastWakeTime;
  const TickType_t xPeriod = 530 / portTICK_PERIOD_MS; // 530 ms
  xLastWakeTime = xTaskGetTickCount();

  while(1){
    BSP_LED_Toggle(LED3);
    vTaskDelayUntil(&xLastWakeTime, xPeriod);
  } // while
} // vBlinkLED3


void vBlinkLED4(void *pvParam){ // LED 4
  TickType_t xLastWakeTime;
  const TickType_t xDelay = 430 / portTICK_PERIOD_MS;
  xLastWakeTime = xTaskGetTickCount();

  while(1){
    BSP_LED_Toggle(LED4);
    vTaskDelayUntil(&xLastWakeTime, xDelay); // Delay -> período total
  } // while
} // vBlinkLED4


void vBlinkLED5(void *pvParam){ // LED 5
  TickType_t xLastWakeTime;
  const TickType_t xPeriod = 330 / portTICK_PERIOD_MS;
  xLastWakeTime = xTaskGetTickCount();

  while(1){
    BSP_LED_Toggle(LED5);
    vTaskDelayUntil(&xLastWakeTime, xPeriod);
  } // while
} // vBlinkLED5

void vBlinkLED6(void *pvParam){ // LED 6
  TickType_t xLastWakeTime;
  const TickType_t xPeriod = 230 / portTICK_PERIOD_MS;
  xLastWakeTime = xTaskGetTickCount();

  while(1){
    BSP_LED_Toggle(LED6);
    vTaskDelayUntil(&xLastWakeTime, xPeriod);
  } // while
} // vBlinkLED6




void main(void){
  __HAL_RCC_GPIOD_CLK_ENABLE();
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED5);
  BSP_LED_Init(LED6);

  xTaskCreate(vBlinkLED3, "vBlinkLED3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
  xTaskCreate(vBlinkLED4, "vBlinkLED4", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
  xTaskCreate(vBlinkLED5, "vBlinkLED5", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
  xTaskCreate(vBlinkLED6, "vBlinkLED6", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);


  vTaskStartScheduler();
  while(1);
} // main
