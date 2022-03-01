/*
 * RAS.h
 *
 *  Created on: Jan 28, 2022
 *      Author: leocelente
 */

#ifndef INC_RAS_H_
#define INC_RAS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "timers.h"
#include "cmsis_os.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "zenith.h"


#define TIMEOUT_SHORT 10
#define TIMEOUT_MEDIUM 100

/* Dados do Grupo1 */
typedef struct {
	float temp1, temp2, temp3;
	float preassure1, preassure2;
	float v1, v2, v3;
	float i1, i2, i3;
	float hum, temp;
	float charge;
} grupo1_item_values_t;

typedef union {
	grupo1_item_values_t values;
	uint8_t raw[sizeof(grupo1_item_values_t)];
} grupo1_item_t;

/* Dados do Grupo2 */
typedef struct {
	float accx,accy,accz;
	float gyrox,gyroy,gyroz;
	float magx,magy,magz;
} grupo2_item_values_t;

typedef union {
	grupo2_item_values_t values;
	uint8_t raw[sizeof(grupo2_item_values_t)];
} grupo2_item_t;

/* Configuration Register */

typedef struct {
	uint16_t timer1;
	uint16_t timer2;
} config_values_t;

typedef union {
	config_values_t values;
	uint8_t raw[sizeof(config_values_t)];
} config_t;


/* CAN */

typedef enum {
	RX, TX
} CAN_Event_Type_t;

typedef enum {
	REQ_DATA_RAS = 0x0C0,
	RES_DATA_RAS_FRAG0 = 0x0C1,
	RES_DATA_RAS_FRAG1 = 0x0C2,
	RES_DATA_RAS_FRAG2 = 0x0C3,
	RES_DATA_RAS_FRAG3 = 0x0C4,
	RES_DATA_RAS_FRAG4 = 0x0C5,
	RES_DATA_RAS_FRAG5 = 0x0C6,
	RES_DATA_RAS_FRAG6 = 0x0C7,
	REQ_DATA_OBC = 0x0D0,
	RES_DATA_OBC_FRAG0 = 0x0D1,
	RES_DATA_OBC_FRAG1 = 0x0D2,
	RES_DATA_OBC_FRAG2 = 0x0D3,
	RES_DATA_OBC_FRAG3 = 0x0D4,
	REQ_SET_CFG_RAS = 0x0F0,
	RES_SET_CFG_RAS = 0x0F1,
	REQ_GET_CFG_RAS = 0x0F2,
	RES_GET_CFG_RAS = 0x0F3,
	SYNC_TIME = 0x0F4,
	REQ_HEARTBEAT = 0x0F5,
	RES_HEARTBEAT_RAS = 0x0F6,
	RES_HEARTBEAT_OBC = 0x0F7
} CAN_Messages_Ids_t;

typedef struct {
	CAN_Event_Type_t type;
	CAN_Messages_Ids_t ID;
	uint8_t data[8];
} CAN_Event_t;

#endif /* INC_RAS_H_ */
