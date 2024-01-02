/*
 * AEIDTH.c
 *
 *  Created on: JUNE 6, 2023
 *      Author: TUSHAR
 */

#include <RE.h>

FDCAN_TxHeaderTypeDef RE_TxHeader;
uint8_t RE_canTxData[8];

FDCAN_RxHeaderTypeDef RE_RxHeader;
uint8_t RE_canRxData[8];

FDCAN_HandleTypeDef* RE_fdcan1h;

void RE(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	RE_fdcan1h = hf;
	//uint16_t crc = 0;
	//check_t = CellCount;
	RE_TxHeader.IdType         = FDCAN_STANDARD_ID;
	RE_TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	RE_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	RE_TxHeader.FDFormat	    = FDCAN_CLASSIC_CAN;

	for(int i=0;i<3;i++)
		{
			switch(i)
			{
			case 0:	//0x4ab
			RE_TxHeader.Identifier = 0x12E;
			RE_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

			RE_canTxData[0] = 0x18;
			RE_canTxData[1] = 0x79;
			RE_canTxData[2] = 0x7C;
			RE_canTxData[3] = 0x15;
			RE_canTxData[4] = 0xE0;
			RE_canTxData[5] = 0x2E;
			RE_canTxData[6] = 0x01;
			RE_canTxData[7] = 0x00;

			if( HAL_FDCAN_GetTxFifoFreeLevel(RE_fdcan1h) > 0)
				HAL_FDCAN_AddMessageToTxFifoQ(RE_fdcan1h, &RE_TxHeader, RE_canTxData);
			HAL_Delay(1);
			break;

		    case 1:	//0x4ac
			RE_TxHeader.Identifier = 0x151;
			RE_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

			RE_canTxData[0] = 0x05;
			RE_canTxData[1] = 0x0F;
			RE_canTxData[2] = 0x00;
			RE_canTxData[3] = 0x00;
			RE_canTxData[4] = 0x00;
			RE_canTxData[5] = 0x00;
			RE_canTxData[6] = 0x00;
			RE_canTxData[7] = 0x00;
			//09 00 00 00 c8 00 c8 00

			if( HAL_FDCAN_GetTxFifoFreeLevel(RE_fdcan1h) > 0)
				HAL_FDCAN_AddMessageToTxFifoQ(RE_fdcan1h, &RE_TxHeader, RE_canTxData);
			HAL_Delay(1);
			break;
		    case 2:	//0x1aa
			RE_TxHeader.Identifier = 0x12F;
			RE_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

			RE_canTxData[0] = 0xC4;
			RE_canTxData[1] = 0x09;
			RE_canTxData[2] = 0x00;
			RE_canTxData[3] = 0x00;
			RE_canTxData[4] = 0x00;
			RE_canTxData[5] = 0x00;
			RE_canTxData[6] = 0x00;
			RE_canTxData[7] = 0x00;

			if( HAL_FDCAN_GetTxFifoFreeLevel(RE_fdcan1h) > 0)
				HAL_FDCAN_AddMessageToTxFifoQ(RE_fdcan1h, &RE_TxHeader, RE_canTxData);
			HAL_Delay(1);
			break;
			}
		}HAL_Delay(100);


}
