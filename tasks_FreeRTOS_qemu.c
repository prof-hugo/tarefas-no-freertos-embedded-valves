/*==================================================================================================

  tasks_FreeRTOS_qemu.c

  Used hardware: STM32F4-Discovery evaluation board (QEMU)

  Example of using the FreeRTOS Real-Time Operating System on the STM32F4-Discovery board.

  ==================================================================================================
*/

#include "stm32f4_discovery.h"
#include "FreeRTOS.h"
#include "task.h"


typedef struct parameters { // scruct de parâmetros
	int led;
	int period;
} ledstruct;


ledstruct led1,led2,led3,led4;


void vBlinkLED(ledstruct *pvParam){ // Task Geral

  int LED = pvParam-> led;
  int period = pvParam-> period;

  TickType_t xLastWakeTime;
  const TickType_t xPeriod = period / portTICK_PERIOD_MS;
  xLastWakeTime = xTaskGetTickCount();

  while(1){
    BSP_LED_Toggle(LED);
    vTaskDelayUntil(&xLastWakeTime, xPeriod);
  } // while
}




void main(void){

	// Inicialização dos LEDs

  __HAL_RCC_GPIOD_CLK_ENABLE();

  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED5);
  BSP_LED_Init(LED6);

  // Definindo os parâmetros da struct

  led1.led = LED3;
  led1.period = 330;
  led2.led = LED4;
  led2.period = 230;
  led3.led = LED5;
  led3.period = 130;
  led4.led = LED6;
  led4.period = 430;


  // Criando 4 instancias da mesma task

  xTaskCreate(vBlinkLED, "vBlinkLED3", configMINIMAL_STACK_SIZE, &led1, tskIDLE_PRIORITY, NULL);
  xTaskCreate(vBlinkLED, "vBlinkLED4", configMINIMAL_STACK_SIZE, &led2, tskIDLE_PRIORITY, NULL);
  xTaskCreate(vBlinkLED, "vBlinkLED5", configMINIMAL_STACK_SIZE, &led3, tskIDLE_PRIORITY, NULL);
  xTaskCreate(vBlinkLED, "vBlinkLED6", configMINIMAL_STACK_SIZE, &led4, tskIDLE_PRIORITY, NULL);


  vTaskStartScheduler();
  while(1);
} // main
