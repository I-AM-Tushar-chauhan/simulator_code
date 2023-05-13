/*
 * CAN_Communication.h
 *
 *  Created on: Nov 24, 2022
 *      Author: tgopi
 */

#ifndef INC_CAN_COMMUNICATION_H_
#define INC_CAN_COMMUNICATION_H_


#include "main.h"


void JBD_BMS_Communication(FDCAN_HandleTypeDef* hf, uint8_t CellCount);

#endif /* INC_CAN_COMMUNICATION_H_ */
