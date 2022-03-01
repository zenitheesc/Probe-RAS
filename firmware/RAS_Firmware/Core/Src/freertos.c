/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "RAS.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
typedef StaticTimer_t osStaticTimerDef_t;
typedef StaticSemaphore_t osStaticMutexDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Grupo1_Task */
osThreadId_t Grupo1_TaskHandle;
uint32_t Grupo1_TaskBuffer[ 256 ];
osStaticThreadDef_t Grupo1_TaskControlBlock;
const osThreadAttr_t Grupo1_Task_attributes = {
  .name = "Grupo1_Task",
  .cb_mem = &Grupo1_TaskControlBlock,
  .cb_size = sizeof(Grupo1_TaskControlBlock),
  .stack_mem = &Grupo1_TaskBuffer[0],
  .stack_size = sizeof(Grupo1_TaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Grupo2_Task */
osThreadId_t Grupo2_TaskHandle;
uint32_t Grupo2_TaskBuffer[ 256 ];
osStaticThreadDef_t Grupo2_TaskControlBlock;
const osThreadAttr_t Grupo2_Task_attributes = {
  .name = "Grupo2_Task",
  .cb_mem = &Grupo2_TaskControlBlock,
  .cb_size = sizeof(Grupo2_TaskControlBlock),
  .stack_mem = &Grupo2_TaskBuffer[0],
  .stack_size = sizeof(Grupo2_TaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for CAN_Task */
osThreadId_t CAN_TaskHandle;
uint32_t CAN_TaskBuffer[ 256 ];
osStaticThreadDef_t CAN_TaskControlBlock;
const osThreadAttr_t CAN_Task_attributes = {
  .name = "CAN_Task",
  .cb_mem = &CAN_TaskControlBlock,
  .cb_size = sizeof(CAN_TaskControlBlock),
  .stack_mem = &CAN_TaskBuffer[0],
  .stack_size = sizeof(CAN_TaskBuffer),
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for Storage_Task */
osThreadId_t Storage_TaskHandle;
uint32_t Storage_TaskBuffer[ 256 ];
osStaticThreadDef_t Storage_TaskControlBlock;
const osThreadAttr_t Storage_Task_attributes = {
  .name = "Storage_Task",
  .cb_mem = &Storage_TaskControlBlock,
  .cb_size = sizeof(Storage_TaskControlBlock),
  .stack_mem = &Storage_TaskBuffer[0],
  .stack_size = sizeof(Storage_TaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Stimulus_Task */
osThreadId_t Stimulus_TaskHandle;
uint32_t Stimulus_TaskBuffer[ 256 ];
osStaticThreadDef_t Stimulus_TaskControlBlock;
const osThreadAttr_t Stimulus_Task_attributes = {
  .name = "Stimulus_Task",
  .cb_mem = &Stimulus_TaskControlBlock,
  .cb_size = sizeof(Stimulus_TaskControlBlock),
  .stack_mem = &Stimulus_TaskBuffer[0],
  .stack_size = sizeof(Stimulus_TaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for Executer_Task */
osThreadId_t Executer_TaskHandle;
uint32_t Executer_TaskBuffer[ 256 ];
osStaticThreadDef_t Executer_TaskControlBlock;
const osThreadAttr_t Executer_Task_attributes = {
  .name = "Executer_Task",
  .cb_mem = &Executer_TaskControlBlock,
  .cb_size = sizeof(Executer_TaskControlBlock),
  .stack_mem = &Executer_TaskBuffer[0],
  .stack_size = sizeof(Executer_TaskBuffer),
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for CAN_Queue */
osMessageQueueId_t CAN_QueueHandle;
uint8_t CAN_QueueBuffer[ 16 * sizeof( CAN_Event_t ) ];
osStaticMessageQDef_t CAN_QueueControlBlock;
const osMessageQueueAttr_t CAN_Queue_attributes = {
  .name = "CAN_Queue",
  .cb_mem = &CAN_QueueControlBlock,
  .cb_size = sizeof(CAN_QueueControlBlock),
  .mq_mem = &CAN_QueueBuffer,
  .mq_size = sizeof(CAN_QueueBuffer)
};
/* Definitions for Grupo1_Queue */
osMessageQueueId_t Grupo1_QueueHandle;
uint8_t Grupo1_QueueBuffer[ 2 * sizeof( grupo1_item_t ) ];
osStaticMessageQDef_t Grupo1_QueueControlBlock;
const osMessageQueueAttr_t Grupo1_Queue_attributes = {
  .name = "Grupo1_Queue",
  .cb_mem = &Grupo1_QueueControlBlock,
  .cb_size = sizeof(Grupo1_QueueControlBlock),
  .mq_mem = &Grupo1_QueueBuffer,
  .mq_size = sizeof(Grupo1_QueueBuffer)
};
/* Definitions for Grupo2_Queue */
osMessageQueueId_t Grupo2_QueueHandle;
uint8_t Grupo2_QueueBuffer[ 12 * sizeof( grupo2_item_t ) ];
osStaticMessageQDef_t Grupo2_QueueControlBlock;
const osMessageQueueAttr_t Grupo2_Queue_attributes = {
  .name = "Grupo2_Queue",
  .cb_mem = &Grupo2_QueueControlBlock,
  .cb_size = sizeof(Grupo2_QueueControlBlock),
  .mq_mem = &Grupo2_QueueBuffer,
  .mq_size = sizeof(Grupo2_QueueBuffer)
};
/* Definitions for Grupo1_Timer */
osTimerId_t Grupo1_TimerHandle;
osStaticTimerDef_t Grupo1_TimerControlBlock;
const osTimerAttr_t Grupo1_Timer_attributes = {
  .name = "Grupo1_Timer",
  .cb_mem = &Grupo1_TimerControlBlock,
  .cb_size = sizeof(Grupo1_TimerControlBlock),
};
/* Definitions for Grupo2_Timer */
osTimerId_t Grupo2_TimerHandle;
osStaticTimerDef_t Grupo2_TimerControlBlock;
const osTimerAttr_t Grupo2_Timer_attributes = {
  .name = "Grupo2_Timer",
  .cb_mem = &Grupo2_TimerControlBlock,
  .cb_size = sizeof(Grupo2_TimerControlBlock),
};
/* Definitions for UART_Mutex */
osMutexId_t UART_MutexHandle;
osStaticMutexDef_t UART_MutexControlBlock;
const osMutexAttr_t UART_Mutex_attributes = {
  .name = "UART_Mutex",
  .cb_mem = &UART_MutexControlBlock,
  .cb_size = sizeof(UART_MutexControlBlock),
};
/* Definitions for Config_Mutex */
osMutexId_t Config_MutexHandle;
osStaticMutexDef_t Config_MutexControlBlock;
const osMutexAttr_t Config_Mutex_attributes = {
  .name = "Config_Mutex",
  .cb_mem = &Config_MutexControlBlock,
  .cb_size = sizeof(Config_MutexControlBlock),
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
extern void Grupo1_TaskFun(void *argument);
extern void Grupo2_TaskFun(void *argument);
extern void CAN_TaskFun(void *argument);
extern void Storage_TaskFun(void *argument);
extern void Stimulus_TaskFun(void *argument);
extern void Executer_TaskFun(void *argument);
extern void Grupo1_TimerFun(void *argument);
extern void Grupo2_TimerFun(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN PREPOSTSLEEP */
__weak void PreSleepProcessing(uint32_t ulExpectedIdleTime)
{
/* place for user code */
}

__weak void PostSleepProcessing(uint32_t ulExpectedIdleTime)
{
/* place for user code */
}
/* USER CODE END PREPOSTSLEEP */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of UART_Mutex */
  UART_MutexHandle = osMutexNew(&UART_Mutex_attributes);

  /* creation of Config_Mutex */
  Config_MutexHandle = osMutexNew(&Config_Mutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of Grupo1_Timer */
  Grupo1_TimerHandle = osTimerNew(Grupo1_TimerFun, osTimerPeriodic, NULL, &Grupo1_Timer_attributes);

  /* creation of Grupo2_Timer */
  Grupo2_TimerHandle = osTimerNew(Grupo2_TimerFun, osTimerPeriodic, NULL, &Grupo2_Timer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of CAN_Queue */
  CAN_QueueHandle = osMessageQueueNew (16, sizeof(CAN_Event_t), &CAN_Queue_attributes);

  /* creation of Grupo1_Queue */
  Grupo1_QueueHandle = osMessageQueueNew (2, sizeof(grupo1_item_t), &Grupo1_Queue_attributes);

  /* creation of Grupo2_Queue */
  Grupo2_QueueHandle = osMessageQueueNew (12, sizeof(grupo2_item_t), &Grupo2_Queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Grupo1_Task */
  Grupo1_TaskHandle = osThreadNew(Grupo1_TaskFun, NULL, &Grupo1_Task_attributes);

  /* creation of Grupo2_Task */
  Grupo2_TaskHandle = osThreadNew(Grupo2_TaskFun, NULL, &Grupo2_Task_attributes);

  /* creation of CAN_Task */
  CAN_TaskHandle = osThreadNew(CAN_TaskFun, NULL, &CAN_Task_attributes);

  /* creation of Storage_Task */
  Storage_TaskHandle = osThreadNew(Storage_TaskFun, NULL, &Storage_Task_attributes);

  /* creation of Stimulus_Task */
  Stimulus_TaskHandle = osThreadNew(Stimulus_TaskFun, NULL, &Stimulus_Task_attributes);

  /* creation of Executer_Task */
  Executer_TaskHandle = osThreadNew(Executer_TaskFun, NULL, &Executer_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

