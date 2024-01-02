/*
 * CAN_Communication.c
 *
 *  Created on: MAR 3, 2023
 *      Author: TUSHAR
 */

#include <Sonalika.h>

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

			//switch(S_RxHeader.Identifier)
			switch(1)
			{
			//case 0x18FF50E5:
			case 1:

				S_TxHeader.Identifier = 0x1F10FA02;
				S_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				S_canTxData[0] = 0x30; //Cell 1 High Byte
				S_canTxData[1] = 0x00; //Cell 1 Low Byte
				S_canTxData[2] = 0x28; //Cell 2 High Byte
				S_canTxData[3] = 0x75; //Cell 2 Low Byte
				S_canTxData[4] = 0x80; //Cell 3 High Byte
				S_canTxData[5] = 0x14; //Cell 3 Low Byte
				S_canTxData[6] = 0x03; //Cell 4 High Byte
				S_canTxData[7] = 0x00; //Cell 4 Low Byte

				if( HAL_FDCAN_GetTxFifoFreeLevel(S_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(S_fdcan1h, &S_TxHeader, S_canTxData);
				 HAL_Delay(1);

				S_TxHeader.Identifier = 0x1F11FA02;
				S_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				S_canTxData[0] = 0xA0; //Cell 1 High Byte
				S_canTxData[1] = 0x9F; //Cell 1 Low Byte
				S_canTxData[2] = 0xB6; //Cell 2 High Byte
				S_canTxData[3] = 0x0E; //Cell 2 Low Byte
				S_canTxData[4] = 0x9F; //Cell 3 High Byte
				S_canTxData[5] = 0x0E; //Cell 3 Low Byte
				S_canTxData[6] = 0x00; //Cell 4 High Byte
				S_canTxData[7] = 0x00; //Cell 4 Low Byte

				if( HAL_FDCAN_GetTxFifoFreeLevel(S_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(S_fdcan1h, &S_TxHeader, S_canTxData);
				 HAL_Delay(1);

				 HAL_Delay(998);

			break;

			}
		//}
	}
//}
