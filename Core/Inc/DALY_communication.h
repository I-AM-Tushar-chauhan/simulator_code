/*
 * CAN_Communication.h
 *
 *  Created on: DEC 5, 2022
 *      Author: tushar
 */

#ifndef INC_DALY_COMMUNICATION_H_
#define INC_DALY_COMMUNICATION_H_


#include "main.h"

typedef enum
{
	BMS_ID_Voltage_Current_RSOC     = 		0x90UL,
	BMS_ID_Protections				= 		0x98UL,
	BMS_ID_MOSFET_Status			=		0x93UL,
	BMS_ID_CELL_STRING_NTC			=		0x94UL,
	BMS_ID_NTC_TEMP					=		0x96UL,

}BMS_ID_e;


void DALY_BMS_Communication(FDCAN_HandleTypeDef* hf, uint8_t CellCount);

#endif /* INC_DALY_COMMUNICATION_H_ */
