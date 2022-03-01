/*
 * RAS.c
 *
 *  Created on: Jan 28, 2022
 *      Author: leocelente
 */
#include "RAS.h"

/* -- Generated Handles -- */

/* Task Handles */
extern osThreadId_t Grupo1_TaskHandle;
extern osThreadId_t Grupo2_TaskHandle;
extern osThreadId_t CAN_TaskHandle;
extern osThreadId_t Storage_TaskHandle;
extern osThreadId_t Stimulus_TaskHandle;
extern osThreadId_t Executer_TaskHandle;

/* Queues Handles */
extern osMessageQueueId_t CAN_QueueHandle;
extern osMessageQueueId_t Grupo1_QueueHandle;
extern osMessageQueueId_t Grupo2_QueueHandle;

/* Timers Handles */
extern osTimerId_t Grupo1_TimerHandle;
extern osTimerId_t Grupo2_TimerHandle;

/* Mutexes Handles */
extern osMutexId_t UART_MutexHandle;
extern osMutexId_t Config_MutexHandle;

static config_t config = { .values = { .timer1 = 1000, .timer2 = 100 } };

/* -- Function Implementations -- */

/* Fetch Grupo1 sensors data */
void Grupo1_TaskFun(void *argument) {
	osTimerStart(Grupo1_TimerHandle, 1000);

	while (true) {
		osThreadFlagsWait(0x00000001U, osFlagsWaitAny, osWaitForever);
		debug("[Grupo1] Fetch Barometer 1  (MPX5700)")
		debug("[Grupo1] Fetch Barometer 2  (MS5607)")
		debug("[Grupo1] Fetch Thermistor 1 (MAX6682)")
		debug("[Grupo1] Fetch Thermistor 2 (MAX6682)")
		debug("[Grupo1] Fetch Thermistor 3 (MAX6682)")
		debug("[Grupo1] Fetch Humidity     (HDC1080)")
		grupo1_item_t data = { .values = { 0 } };
		osMessageQueuePut(Grupo1_QueueHandle, &data, 0, 100);
	}
}

/* Fetch Grupo2 sensors data */
void Grupo2_TaskFun(void *argument) {
	osTimerStart(Grupo2_TimerHandle, 100);
	while (true) {
		osThreadFlagsWait(0x00000001U, osFlagsWaitAny, osWaitForever);
		debug("[Grupo2] Fetch IMU Data")
		debug("[Grupo2] Fetch Magnetometer Data")
		grupo2_item_t data = { .values = { 0 } };
		osMessageQueuePut(Grupo2_QueueHandle, &data, 0, 100);
	}
}

/* Handle CAN events (Rx & Tx) */
void CAN_TaskFun(void *argument) {
	CAN_Event_t event = { 0 };
	while (true) {
		osMessageQueueGet(CAN_QueueHandle, &event, 0, osWaitForever);
		switch (event.type) {
		case RX:
			switch (event.ID) {
			case SYNC_TIME:
				debug("[CAN] Sync Time!")

				break;
			case REQ_DATA_RAS:
				debug("[CAN] Data Requested!")
				osThreadFlagsSet(Executer_TaskHandle, 0x00000001U);
				break;
			case REQ_HEARTBEAT:
				debug("[CAN] Heartbeat Requested!")
				osThreadFlagsSet(Executer_TaskHandle, 0x00000002U);
				break;
			default:
				break;
			}
			break;
		case TX:
			debug("[CAN] Sending message")
			debug(" \tID: %.2X", event.ID)
			debug(" \t %.2X %.2X %.2X %.2X %.2X %.2X %.2X %.2X", event.data[0],
					event.data[1], event.data[2], event.data[3], event.data[4],
					event.data[5], event.data[6], event.data[7])
			break;
		default:
			break;
		}
	}
}

/* Handle Storage devices (flash & sdcard) */
void Storage_TaskFun(void *argument) {
	grupo1_item_t grupo1_data = { .values = { 0 } };
	grupo2_item_t grupo2_data[10] = { 0 };
	while (true) {
		osDelay(1000);
		/* Block on Slowest Group */
		osMessageQueueGet(Grupo1_QueueHandle, &grupo1_data, 0, osWaitForever);

		/* flush buffer */
		size_t grupo2_buffered_count = osMessageQueueGetCount(
				Grupo2_QueueHandle);
		for (int i = 0; i < grupo2_buffered_count; ++i) {
			osMessageQueueGet(Grupo2_QueueHandle, &grupo2_data[i], 0, 10);
		}

		debug("[Storage] Saving Grupo1 Data to SDCard")
		debug("[Storage] Saving Grupo1 Data to Flash")

		debug("[Storage] Saving Grupo2 Data to SDCard")
		for (int i = 0; i < grupo2_buffered_count; ++i) {
			(void) 0;
		}

		debug("[Storage] Saving Grupo2 Data to Flash")
		for (int i = 0; i < grupo2_buffered_count; ++i) {
			(void) 0;
		}
	}
}

/* Creates stimulus to test mock implementation */
void Stimulus_TaskFun(void *argument) {
	osDelay(1000);
	CAN_Event_t request = { .type = RX, .ID = REQ_DATA_RAS };
	CAN_Event_t time_sync = { .type = RX, .ID = SYNC_TIME };
	while (true) {
		/* Fake receiving a CDH Request */
		osMessageQueuePut(CAN_QueueHandle, &request, 0, 100);
		osDelay(1000);
		osMessageQueuePut(CAN_QueueHandle, &time_sync, 0, 100);
		osDelay(2000);
	}

}

void Executer_TaskFun(void *argument) {
	while (true) {
		/* Wait for command */
		uint32_t cmd = osThreadFlagsWait(0x000000FF, osFlagsWaitAny,
		osWaitForever);

		switch (cmd) {
		case 1:
			debug("[Exec] Creating Packet")
			grupo1_item_t current_data;
			xQueuePeek(CAN_QueueHandle, &current_data, osWaitForever);
			CAN_Event_t data_response[7];
			uint8_t bytes2send = sizeof(current_data.raw);
			for (int i = 0, j = 0; bytes2send > 0; i += 8, ++j) {
				uint8_t send = (bytes2send >= 8) ? 8 : bytes2send % 8;
				debug("[Exec] \tfrag: %d, offset: %d, size: %d", j, i, send)
				memcpy(&data_response[j].data, &current_data.raw[i], send);
				bytes2send -= send;
				data_response[j].type = TX;
				data_response[j].ID = RES_DATA_RAS_FRAG0 + j;
				osMessageQueuePut(CAN_QueueHandle, &data_response[j], 0,
				TIMEOUT_MEDIUM);
			}

			break;
		case 2:
			debug("[Exec] Responding to Heartbeat")
			CAN_Event_t heartbeat_response = { .type = TX, .ID =
					RES_HEARTBEAT_RAS, .data = { 0 } };
			osMessageQueuePut(CAN_QueueHandle, &heartbeat_response, 0,
			TIMEOUT_SHORT);

		default:
			break;
		}
	}
}

/* Called on Grupo1 Timer callback */
void Grupo1_TimerFun(void *argument) {
	osThreadFlagsSet(Grupo1_TaskHandle, 0x00000001U);
	if (osMutexAcquire(Config_MutexHandle, 0)) {
		xTimerChangePeriod(Grupo1_TaskHandle, config.values.timer1, 0);
		osMutexRelease(Config_MutexHandle);
	}

}

/* Called on Grupo2 Timer callback */
void Grupo2_TimerFun(void *argument) {
	osThreadFlagsSet(Grupo2_TaskHandle, 0x00000001U);
	if (osMutexAcquire(Config_MutexHandle, 0)) {
		xTimerChangePeriod(Grupo2_TaskHandle, config.values.timer2, 0);
		osMutexRelease(Config_MutexHandle);
	}
}
