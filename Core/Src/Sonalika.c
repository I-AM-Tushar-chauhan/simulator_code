/*
 * CAN_Communication.c
 *
 *  Created on: MAR 3, 2023
 *      Author: TUSHAR
 */

#include "Sonalika.h"

FDCAN_TxHeaderTypeDef S_TxHeader;
uint8_t S_canTxData[8];

FDCAN_RxHeaderTypeDef S_RxHeader;
uint8_t S_canRxData[8];

FDCAN_HandleTypeDef* S_fdcan1h;

void sonalika(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	S_fdcan1h = hf;
	//uint16_t crc = 0;
	//check_t = CellCount;
	S_TxHeader.IdType         = FDCAN_EXTENDED_ID;
	S_TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	S_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	S_TxHeader.FDFormat	    = FDCAN_CLASSIC_CAN;

	if(HAL_FDCAN_GetRxFifoFillLevel(S_fdcan1h, FDCAN_RX_FIFO0) > 0)
	{
		HAL_FDCAN_GetRxMessage(S_fdcan1h,FDCAN_RX_FIFO0,&S_RxHeader,S_canRxData);

		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);

		if(	(S_RxHeader.RxFrameType == FDCAN_DATA_FRAME)&&
			(S_RxHeader.IdType == FDCAN_EXTENDED_ID)&&
			(S_RxHeader.FDFormat == FDCAN_CLASSIC_CAN))
		{

			switch(S_RxHeader.Identifier)
			{
			case 0x18FF50E5:
				S_TxHeader.Identifier = 0x1806E5F4;
				S_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				S_canTxData[0] = ((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
				S_canTxData[1] = ((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
				S_canTxData[2] = 0x00;//CURRENT HIGH
				S_canTxData[3] = 0xFA;//CURRENT LOW	25A current
				S_canTxData[4] = 0x00;//START CHARGING AND STOP CHARGING
				S_canTxData[5] = 0x00;//	 N/A
				S_canTxData[6] = 0x00;//   N/A
				S_canTxData[7] = 0x00;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(S_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(S_fdcan1h, &S_TxHeader, S_canTxData);

				 HAL_Delay(2);

				S_TxHeader.Identifier = 0x18FFE5F4;
				S_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				S_canTxData[0] = ((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
				S_canTxData[1] = ((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
				S_canTxData[2] = 0x00;//CURRENT HIGH
				S_canTxData[3] = 0xFA;//CURRENT LOW	25A current
				S_canTxData[4] = 0x00;//START CHARGING AND STOP CHARGING
				S_canTxData[5] = 0x00;//	 N/A
				S_canTxData[6] = 0x00;//   N/A
				S_canTxData[7] = 0x00;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(S_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(S_fdcan1h, &S_TxHeader, S_canTxData);

				 HAL_Delay(2);
			S_TxHeader.Identifier = 0x18FF03FF;
			S_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

			S_canTxData[0] = 0x0C; //Cell 1 High Byte
			S_canTxData[1] = 0xE4; //Cell 1 Low Byte
			S_canTxData[2] = 0x0C; //Cell 2 High Byte
			S_canTxData[3] = 0xF3; //Cell 2 Low Byte
			S_canTxData[4] = 0x0C; //Cell 3 High Byte
			S_canTxData[5] = 0xF4; //Cell 3 Low Byte
			S_canTxData[6] = 0x0C; //Cell 4 High Byte
			S_canTxData[7] = 0xF5; //Cell 4 Low Byte

			if( HAL_FDCAN_GetTxFifoFreeLevel(S_fdcan1h) > 0)
				HAL_FDCAN_AddMessageToTxFifoQ(S_fdcan1h, &S_TxHeader, S_canTxData);

			 HAL_Delay(2);

				S_TxHeader.Identifier = 0x18FF01FF;
				S_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				S_canTxData[0] = 0x01; //Cell 1 High Byte
				S_canTxData[1] = 0xF4; //Cell 1 Low Byte
				S_canTxData[2] = 0x00; //Cell 2 High Byte
				S_canTxData[3] = 0x96; //Cell 2 Low Byte
				S_canTxData[4] = 0x58; //Cell 3 High Byte
				S_canTxData[5] = 0x41; //Cell 3 Low Byte
				S_canTxData[6] = 0x01; //Cell 4 High Byte
				S_canTxData[7] = 0x00; //Cell 4 Low Byte

				if( HAL_FDCAN_GetTxFifoFreeLevel(S_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(S_fdcan1h, &S_TxHeader, S_canTxData);
				 HAL_Delay(2);

			break;

			}
		}
	}
}
