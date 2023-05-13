/*
 * CAN_Communication.c
 *
 *  Created on: MAR 3, 2023
 *      Author: TUSHAR
 */

#include "JLN_Phenix.h"

FDCAN_TxHeaderTypeDef JLN_TxHeader;
uint8_t JLN_canTxData[8];

FDCAN_RxHeaderTypeDef JLN_RxHeader;
uint8_t JLN_canRxData[8];

FDCAN_HandleTypeDef* JLN_fdcan1h;

void JLN_BMS_Communication(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	JLN_fdcan1h = hf;
	uint16_t crc = 0;
	//check_t = CellCount;
	JLN_TxHeader.IdType         = FDCAN_EXTENDED_ID;
	JLN_TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	JLN_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	JLN_TxHeader.FDFormat	    = FDCAN_CLASSIC_CAN;

	if(HAL_FDCAN_GetRxFifoFillLevel(JLN_fdcan1h, FDCAN_RX_FIFO0) > 0)
	{
		HAL_FDCAN_GetRxMessage(JLN_fdcan1h,FDCAN_RX_FIFO0,&JLN_RxHeader,JLN_canRxData);

		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);

		if(	(JLN_RxHeader.RxFrameType == FDCAN_DATA_FRAME)&&
			(JLN_RxHeader.IdType == FDCAN_EXTENDED_ID)&&
			(JLN_RxHeader.FDFormat == FDCAN_CLASSIC_CAN))
		{

			switch(JLN_RxHeader.Identifier)
			{
				case 0x18FF50E5:	//	Voltage and Current

					JLN_TxHeader.Identifier = 0x1806E5F4;
					JLN_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					JLN_canTxData[0] = ((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
					JLN_canTxData[1] = ((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
					JLN_canTxData[2] = 0x00;//CURRENT HIGH
					JLN_canTxData[3] = 0x3C;//CURRENT LOW	1A current
					JLN_canTxData[4] = 0x00;//START CHARGING AND STOP CHARGING
					JLN_canTxData[5] = 0x00;//	 N/A
					JLN_canTxData[6] = 0x00;//   N/A
     				JLN_canTxData[7] = 0x00;//   N/A

					if( HAL_FDCAN_GetTxFifoFreeLevel(JLN_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(JLN_fdcan1h, &JLN_TxHeader, JLN_canTxData);

					 HAL_Delay(2);

					JLN_TxHeader.Identifier = 0x18FFE5F4;
					JLN_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					JLN_canTxData[0] = ((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
					JLN_canTxData[1] = ((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
					JLN_canTxData[2] = 0x00;//CURRENT HIGH
					JLN_canTxData[3] = 0x0A;//CURRENT LOW	1A current
					JLN_canTxData[4] = 0x00;//START CHARGING AND STOP CHARGING
					JLN_canTxData[5] = 0x00;//	 N/A
					JLN_canTxData[6] = 0x00;//   N/A
					JLN_canTxData[7] = 0x00;//   N/A

					if( HAL_FDCAN_GetTxFifoFreeLevel(JLN_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(JLN_fdcan1h, &JLN_TxHeader, JLN_canTxData);
					break;

			}
		}
	}
}
