/*
 * AEIDTH.c
 *
 *  Created on: JUNE 6, 2023
 *      Author: TUSHAR
 */

#include <NE.h>

FDCAN_TxHeaderTypeDef NE_TxHeader;
uint8_t NE_canTxData[8];

FDCAN_RxHeaderTypeDef NE_RxHeader;
uint8_t NE_canRxData[8];

FDCAN_HandleTypeDef* NE_fdcan1h;

void NE(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	NE_fdcan1h = hf;
	//uint16_t crc = 0;
	//check_t = CellCount;
	NE_TxHeader.IdType         = FDCAN_EXTENDED_ID;
	NE_TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	NE_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	NE_TxHeader.FDFormat	   = FDCAN_CLASSIC_CAN;

	        switch(0)
			{
			case 0:	//0x4ab
			NE_TxHeader.Identifier = 0x18F1E5F4;
			NE_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

			NE_canTxData[0] = 0x03;//0x0348 for 840x0.1V
			NE_canTxData[1] = 0x48;
			NE_canTxData[2] = 0x02;//0x0258 for 600x0.1A
			NE_canTxData[3] = 0x58;
			NE_canTxData[4] = 0x00;
			NE_canTxData[5] = 0x64;
			NE_canTxData[6] = 0x00;
			NE_canTxData[7] = 0x00;

			if( HAL_FDCAN_GetTxFifoFreeLevel(NE_fdcan1h) > 0)
				HAL_FDCAN_AddMessageToTxFifoQ(NE_fdcan1h, &NE_TxHeader, NE_canTxData);
			HAL_Delay(1);
			break;

		}HAL_Delay(1000);


}
