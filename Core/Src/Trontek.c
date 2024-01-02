/*
 * AEIDTH.c
 *
 *  Created on: JUNE 6, 2023
 *      Author: TUSHAR
 */

#include <TRONTEK.h>

FDCAN_TxHeaderTypeDef TRONTEK_TxHeader;
uint8_t TRONTEK_canTxData[8];

FDCAN_RxHeaderTypeDef TRONTEK_RxHeader;
uint8_t TRONTEK_canRxData[8];

FDCAN_HandleTypeDef* TRONTEK_fdcan1h;

void TRONTEK(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	TRONTEK_fdcan1h = hf;
	//uint16_t crc = 0;
	//check_t = CellCount;
	TRONTEK_TxHeader.IdType         = FDCAN_STANDARD_ID;
	TRONTEK_TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	TRONTEK_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	TRONTEK_TxHeader.FDFormat	    = FDCAN_CLASSIC_CAN;

	for(int i=0; i<4; i++)
	{
		switch(i)
					{
			case 0:

				TRONTEK_TxHeader.Identifier = 0x331;
				TRONTEK_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				TRONTEK_canTxData[0] = 0x90;//((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
				TRONTEK_canTxData[1] = 0xE2;//((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
				TRONTEK_canTxData[2] = 0x00;//CURRENT HIGH
				TRONTEK_canTxData[3] = 0x00;//CURRENT LOW	25A current
				TRONTEK_canTxData[4] = 0x88;//START CHARGING AND STOP CHARGING
				TRONTEK_canTxData[5] = 0x13;//	 N/A
				TRONTEK_canTxData[6] = 0x89;//   N/A
				TRONTEK_canTxData[7] = 0x22;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(TRONTEK_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(TRONTEK_fdcan1h, &TRONTEK_TxHeader, TRONTEK_canTxData);
				 HAL_Delay(100);
			break;
			case 1:

				TRONTEK_TxHeader.Identifier = 0x333;
				TRONTEK_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				TRONTEK_canTxData[0] = 0x1C;//((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
				TRONTEK_canTxData[1] = 0x0C;//((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
				TRONTEK_canTxData[2] = 0x80;//CURRENT HIGH
				TRONTEK_canTxData[3] = 0x0C;//CURRENT LOW	25A current
				TRONTEK_canTxData[4] = 0x68;//START CHARGING AND STOP CHARGING
				TRONTEK_canTxData[5] = 0x74;//	 N/A
				TRONTEK_canTxData[6] = 0x68;//   N/A
				TRONTEK_canTxData[7] = 0x74;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(TRONTEK_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(TRONTEK_fdcan1h, &TRONTEK_TxHeader, TRONTEK_canTxData);
				 HAL_Delay(100);
			break;
           case 2:

				TRONTEK_TxHeader.Identifier = 0x334;
				TRONTEK_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				TRONTEK_canTxData[0] = 0x05;//((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
				TRONTEK_canTxData[1] = 0x00;//((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
				TRONTEK_canTxData[2] = 0x05;//CURRENT HIGH
				TRONTEK_canTxData[3] = 0x00;//CURRENT LOW	25A current
				TRONTEK_canTxData[4] = 0x00;//START CHARGING AND STOP CHARGING
				TRONTEK_canTxData[5] = 0x00;//	 N/A
				TRONTEK_canTxData[6] = 0x00;//   N/A
				TRONTEK_canTxData[7] = 0x00;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(TRONTEK_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(TRONTEK_fdcan1h, &TRONTEK_TxHeader, TRONTEK_canTxData);
				 HAL_Delay(100);
			break;
                case 3:

				TRONTEK_TxHeader.Identifier = 0x307;
				TRONTEK_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				TRONTEK_canTxData[0] = 0xC8;//((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
				TRONTEK_canTxData[1] = 0xAF;//((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
				TRONTEK_canTxData[2] = 0x00;//CURRENT HIGH
				TRONTEK_canTxData[3] = 0x00;//CURRENT LOW	25A current
				TRONTEK_canTxData[4] = 0x13;//START CHARGING AND STOP CHARGING
				TRONTEK_canTxData[5] = 0x04;//	 N/A
				TRONTEK_canTxData[6] = 0x50;//   N/A
				TRONTEK_canTxData[7] = 0x01;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(TRONTEK_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(TRONTEK_fdcan1h, &TRONTEK_TxHeader, TRONTEK_canTxData);
				 HAL_Delay(1000);
			break;

	      }
	   }

	}

