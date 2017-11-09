
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

/* Begin of <includes> initialization, DO NOT MODIFY LINES BELOW */

#include "TSK1.h"
#include "FRTOS1.h"
#include "frtos_tasks.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */

#include "AS1.h"

	uint8_t buffer[4];
	AS1_TComData string2[20] = "Recebeu! \n";
	xTaskHandle taskHandle;
	
static portTASK_FUNCTION(EnviaSerialTask, pvParameters) {

  /* Write your task initialization code here ... */
	word count;

  for(;;) {
    /* Write your task code here ... */
	  FRTOS1_ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	  AS1_SendBlock(string2, sizeof(string2),(&count));
	  
    /* You can use a task delay like
       vTaskDelay(1000/portTICK_RATE_MS);
     */
  }
  /* Destroy the task */
  vTaskDelete(EnviaSerialTask);
}

void CreateTasks(void) {
  if (FRTOS1_xTaskCreate(
     EnviaSerialTask,  /* pointer to the task */
      "EnviaSerial", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE + 0, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 1,  /* initial priority */
      &taskHandle /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
}

