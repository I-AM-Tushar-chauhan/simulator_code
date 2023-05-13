/*
 * DALY_communication.c
 *
 *  Created on: 05-Dec-2022
 *      Author: Tushar
 */

#include <STH_CAN_Simulator.h>

FDCAN_TxHeaderTypeDef STH_TxHeader;
uint8_t STH_canTxData[8];

FDCAN_RxHeaderTypeDef STH_RxHeader;
uint8_t STH_canRxData[8];

FDCAN_HandleTypeDef* STH_fdcan1h;

//uint32_t   bmsResponse	;
uint8_t  i=0;
//uint8_t  count=0;
void STH_BMS_Communication(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	STH_fdcan1h = hf;
	//uint16_t crc = 0;
	//check_t = CellCount;
	STH_TxHeader.IdType         = FDCAN_STANDARD_ID;
	STH_TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	STH_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	STH_TxHeader.FDFormat	    = FDCAN_CLASSIC_CAN;

	for( i=1;i<8;i++)
	{
		switch(i)
		{

			case 4:	//0x4ab
				STH_TxHeader.Identifier = 0x000004ab;
				STH_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				STH_canTxData[0] = 0x03;
				STH_canTxData[1] = 0x00;
				STH_canTxData[2] = 0x03;
				STH_canTxData[3] = 0x00;
				STH_canTxData[4] = 0x16;
				STH_canTxData[5] = 0x05;
				STH_canTxData[6] = 0x16;
				STH_canTxData[7] = 0x05;

				if( HAL_FDCAN_GetTxFifoFreeLevel(STH_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(STH_fdcan1h, &STH_TxHeader, STH_canTxData);
				HAL_Delay(1);
				break;

			case 7:	//0x4ac
				STH_TxHeader.Identifier = 0x000004ac;
				STH_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				STH_canTxData[0] = 0x09;
				STH_canTxData[1] = 0x00;
				STH_canTxData[2] = 0x00;
				STH_canTxData[3] = 0x00;
				STH_canTxData[4] = 0xC8;
				STH_canTxData[5] = 0x00;
				STH_canTxData[6] = 0xC8;
				STH_canTxData[7] = 0x00;
				//09 00 00 00 c8 00 c8 00

				if( HAL_FDCAN_GetTxFifoFreeLevel(STH_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(STH_fdcan1h, &STH_TxHeader, STH_canTxData);
				HAL_Delay(1);
				break;
			case 2:	//0x1aa
				STH_TxHeader.Identifier = 0x000001aa;
				STH_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				STH_canTxData[0] = 0x00;
				STH_canTxData[1] = 0x3C;
				STH_canTxData[2] = 0x00;
				STH_canTxData[3] = 0x00;
				STH_canTxData[4] = 0x00;
				STH_canTxData[5] = 0x00;
				STH_canTxData[6] = 0x00;
				STH_canTxData[7] = 0x00;

				if( HAL_FDCAN_GetTxFifoFreeLevel(STH_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(STH_fdcan1h, &STH_TxHeader, STH_canTxData);
				HAL_Delay(1);
				break;

			case 6:	//0x2aa
				STH_TxHeader.Identifier = 0x000002aa;
				STH_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				STH_canTxData[0] = 0x5E;
				STH_canTxData[1] = 0xC8;
				STH_canTxData[2] = 0x00;
				STH_canTxData[3] = 0x32;
				STH_canTxData[4] = 0x00;
				STH_canTxData[5] = 0x39;
				STH_canTxData[6] = 0x00;
				STH_canTxData[7] = 0x64;
				//5e c8 00 32 00 39 00 64

				if( HAL_FDCAN_GetTxFifoFreeLevel(STH_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(STH_fdcan1h, &STH_TxHeader, STH_canTxData);
				HAL_Delay(1);
				break;

			case 1:	//0x3aa
				STH_TxHeader.Identifier = 0x000003aa;
				STH_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				STH_canTxData[0] = 0x00;
				STH_canTxData[1] = 0x00;
				STH_canTxData[2] = 0x34;
				STH_canTxData[3] = 0x00;
				STH_canTxData[4] = 0xD2;
				STH_canTxData[5] = 0x00;
				STH_canTxData[6] = 0x64;
				STH_canTxData[7] = 0x00;

				//00 00 34 00 d2 00 64 00
				if( HAL_FDCAN_GetTxFifoFreeLevel(STH_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(STH_fdcan1h, &STH_TxHeader, STH_canTxData);
				HAL_Delay(1);
				break;

			case 3:	//0x4aa
				STH_TxHeader.Identifier = 0x000004aa;
				STH_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				STH_canTxData[0] = 0x00;
				STH_canTxData[1] = 0x3C;
				STH_canTxData[2] = 0x00;
				STH_canTxData[3] = 0x00;
				STH_canTxData[4] = 0x00;
				STH_canTxData[5] = 0x00;
				STH_canTxData[6] = 0x00;
				STH_canTxData[7] = 0x00;

				if( HAL_FDCAN_GetTxFifoFreeLevel(STH_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(STH_fdcan1h, &STH_TxHeader, STH_canTxData);
				HAL_Delay(1);
				break;

			case 5:	//0x3ab
				STH_TxHeader.Identifier = 0x000003ab;
				STH_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				STH_canTxData[0] = 0x16;
				STH_canTxData[1] = 0x16;
				STH_canTxData[2] = 0x00;
				STH_canTxData[3] = 0x00;
				STH_canTxData[4] = 0x00;
				STH_canTxData[5] = 0x00;
				STH_canTxData[6] = 0x00;
				STH_canTxData[7] = 0x00;

				if( HAL_FDCAN_GetTxFifoFreeLevel(STH_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(STH_fdcan1h, &STH_TxHeader, STH_canTxData);
				HAL_Delay(1);
				break;
		}
	}
	HAL_Delay(1000);
	//count++;

}
//	if(HAL_FDCAN_GetRxFifoFillLevel(STH_fdcan1h, FDCAN_RX_FIFO0) > 0)
//	{
//		HAL_FDCAN_GetRxMessage(STH_fdcan1h,FDCAN_RX_FIFO0,&STH_RxHeader,STH_canTxData);
//
//		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
//
//		if(	(STH_RxHeader.IdType == FDCAN_STANDARD_ID)&&
//			(STH_RxHeader.RxFrameType == FDCAN_DATA_FRAME)&&
//			(STH_RxHeader.FDFormat == FDCAN_CLASSIC_CAN))
//		{
//			switch(DALY_RxHeader.Identifier)
//			{
//
//				case 0x18900140:	//	cumulative Voltage, Gather Voltage, Current, SOC
//					DALY_TxHeader.Identifier = 0x18904001;
//					DALY_TxHeader.DataLength = FDCAN_DLC_BYTES_8;
//
//					DALY_canTxData[0] = ((uint16_t)((float)CellCount*3.25*10) >> 8);
//					DALY_canTxData[1] = ((uint16_t)((float)CellCount*3.25*10) & 0xff);
//					DALY_canTxData[2] = ((uint16_t)((float)CellCount*3.19*10) >> 8);//0x01;
//					DALY_canTxData[3] = ((uint16_t)((float)CellCount*3.19*10) & 0xff);//0xEA;
//					uint16_t current_data = (uint16_t)(100+30000); //(((canRxData[4] << 8) | (canRxData[5] & 0xFF))-30000)*10;
//					DALY_canTxData[4] = (uint8_t)(current_data >> 8) ;
//					DALY_canTxData[5] = (uint8_t)(current_data & 0xFF);
//					//DALY_canTxData[4] = 0x75;
//					//DALY_canTxData[5] = 0x94;
//					DALY_canTxData[6] = 0x02;//0x03;
//					DALY_canTxData[7] = 0xEE;//0xDE;
//
//					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
//						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
//					break;
//
//				case 0x18980140:	//	Protections
//					DALY_TxHeader.Identifier = 0x18984001;
//					DALY_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
//
//					DALY_canTxData[0] = 0x00;
//					DALY_canTxData[1] = 0x00;	//	10Ah capacity
//					DALY_canTxData[2] = 0x00;
//					DALY_canTxData[3] = 0x00;	//	10 cycles
//					DALY_canTxData[4] = 0x00;
//					DALY_canTxData[5] = 0x00;	//	75% SOC
//					DALY_canTxData[6] = 0x00;
//					DALY_canTxData[7] = 0x00;
//
//					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
//						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
//					break;
//
//				case 0x18940140:	//	No of cells, No of Temp Sens, Charger Status, Load Status
//					DALY_TxHeader.Identifier = 0x18944001;
//					DALY_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
//
//					DALY_canTxData[0] = 0x0F;
//					DALY_canTxData[1] = 0x05;	//	Balancing off cell  1~16
//					DALY_canTxData[2] = 0x00;
//					DALY_canTxData[3] = 0x00;	//	Balancing off cell 17~32
//					DALY_canTxData[4] = 0x00;
//					DALY_canTxData[5] = 0x00;	//	No Trip on protections
//					DALY_canTxData[6] = 0x00;
//					DALY_canTxData[7] = 0x00;
//
//					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
//						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
//					break;
//
//				case 0x18960140:	//	Frame Number, cell1temp, cell2temp, cell3temp, cell4temp, cell5temp,cell6temp,cell7temp
//					DALY_TxHeader.Identifier = 0x18964001;
//					DALY_TxHeader.DataLength = FDCAN_DLC_BYTES_8;
//
//					DALY_canTxData[0] = 0x01;
//					DALY_canTxData[1] = 0x3C;	//	Charge and Discharge MOS on
//					DALY_canTxData[2] = 0x3D;
//					DALY_canTxData[3] = 0x3E;	//	Date code
//					DALY_canTxData[4] = 0x3F;
//					DALY_canTxData[5] = 0x2F;	//	software version
//					DALY_canTxData[6] = 0x2E;
//					DALY_canTxData[7] = 0x2D;
//
//					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
//						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
//					break;
//
//				case 0x18930140:	//	Mosfet status
//					DALY_TxHeader.Identifier = 0x18934001;
//					DALY_TxHeader.DataLength = FDCAN_DLC_BYTES_8;
//
//					DALY_canTxData[0] = 0x00;
//					DALY_canTxData[1] = 0x01;	//	Charge and Discharge MOS on
//					DALY_canTxData[2] = 0x01;
//					DALY_canTxData[3] = 0x00;	//	Date code
//					DALY_canTxData[4] = 0x00;
//					DALY_canTxData[5] = 0x00;	//	software version
//					DALY_canTxData[6] = 0x00;
//					DALY_canTxData[7] = 0x00;
//
//					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
//						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
//					break;
//			}
//		}
//	}

