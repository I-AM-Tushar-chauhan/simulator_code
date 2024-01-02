/*
 * DALY_communication.c
 *
 *  Created on: 05-Dec-2022
 *      Author: Tushar
 */
//BS == battery smart
#include <BS.h>

FDCAN_TxHeaderTypeDef BS_TxHeader;
uint8_t BS_canTxData[8];

FDCAN_RxHeaderTypeDef BS_RxHeader;
uint8_t BS_canRxData[8];

FDCAN_HandleTypeDef* BS_fdcan1h;

//uint32_t   bmsResponse	;
uint8_t  j_BS=0;
//uint8_t  count=0;
void BS(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	BS_fdcan1h = hf;
	//uint16_t crc = 0;
	//check_t = CellCount;
	BS_TxHeader.IdType         = FDCAN_STANDARD_ID;
	BS_TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	BS_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	BS_TxHeader.FDFormat	    = FDCAN_CLASSIC_CAN;

if(HAL_FDCAN_GetRxFifoFillLevel(BS_fdcan1h, FDCAN_RX_FIFO0) > 0)
	{
		HAL_FDCAN_GetRxMessage(BS_fdcan1h,FDCAN_RX_FIFO0,&BS_RxHeader,BS_canRxData);
		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
		if(	(BS_RxHeader.RxFrameType == FDCAN_DATA_FRAME)&&
			(BS_RxHeader.IdType == FDCAN_STANDARD_ID)&&
			(BS_RxHeader.FDFormat == FDCAN_CLASSIC_CAN)&&(BS_RxHeader.Identifier == 0x1E1)&&(BS_canRxData[0] == 0x01 )&&(BS_canRxData[1] == 0x02))
		   {

				BS_TxHeader.Identifier = 0x1E3;
				BS_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				BS_canTxData[0] = 0x01;
				BS_canTxData[1] = 0x02;
				BS_canTxData[2] = 0x01;
				BS_canTxData[3] = 0x00;
				BS_canTxData[4] = 0x00;
				BS_canTxData[5] = 0x00;
				BS_canTxData[6] = 0x00;
				BS_canTxData[7] = 0x00;

				if( HAL_FDCAN_GetTxFifoFreeLevel(BS_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(BS_fdcan1h, &BS_TxHeader, BS_canTxData);
				HAL_Delay(1);
		   }
		else if((BS_RxHeader.RxFrameType == FDCAN_DATA_FRAME)&&
				(BS_RxHeader.IdType == FDCAN_STANDARD_ID)&&
				(BS_RxHeader.FDFormat == FDCAN_CLASSIC_CAN)&&(BS_RxHeader.Identifier == 0x530))
			   {

					BS_TxHeader.Identifier = 0x520;
					BS_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					BS_canTxData[0] = 0x02;
					BS_canTxData[1] = 0x47;
					BS_canTxData[2] = 0x18;
					BS_canTxData[3] = 0x02;
					BS_canTxData[4] = 0x16;
					BS_canTxData[5] = 0x6E;
					BS_canTxData[6] = 0x05;
					BS_canTxData[7] = 0xDC;

					if( HAL_FDCAN_GetTxFifoFreeLevel(BS_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(BS_fdcan1h, &BS_TxHeader, BS_canTxData);
					HAL_Delay(1);

					BS_TxHeader.Identifier = 0x521;
					BS_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					BS_canTxData[0] = 0x16;
					BS_canTxData[1] = 0xDA;
					BS_canTxData[2] = 0x08;
					BS_canTxData[3] = 0x98;
					BS_canTxData[4] = 0x13;
					BS_canTxData[5] = 0xAE;
					BS_canTxData[6] = 0x00;
					BS_canTxData[7] = 0x00;

					if( HAL_FDCAN_GetTxFifoFreeLevel(BS_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(BS_fdcan1h, &BS_TxHeader, BS_canTxData);
					HAL_Delay(1);

					BS_TxHeader.Identifier = 0x522;
					BS_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					BS_canTxData[0] = 0x00;
					BS_canTxData[1] = 0x00;
					BS_canTxData[2] = 0x00;
					BS_canTxData[3] = 0x00;
					BS_canTxData[4] = 0x00;
					BS_canTxData[5] = 0x00;
					BS_canTxData[6] = 0x00;
					BS_canTxData[7] = 0x00;

					if( HAL_FDCAN_GetTxFifoFreeLevel(BS_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(BS_fdcan1h, &BS_TxHeader, BS_canTxData);
					HAL_Delay(1);
			   }

    }
}

