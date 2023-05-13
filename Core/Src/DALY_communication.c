/*
 * DALY_communication.c
 *
 *  Created on: 05-Dec-2022
 *      Author: Tushar
 */

#include "DALY_communication.h"

FDCAN_TxHeaderTypeDef DALY_TxHeader;
uint8_t DALY_canTxData[8];

FDCAN_RxHeaderTypeDef DALY_RxHeader;
uint8_t DALY_canRxData[8];

FDCAN_HandleTypeDef* DALY_fdcan1h;

//uint32_t   bmsResponse	;

void DALY_BMS_Communication(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	DALY_fdcan1h = hf;
	//uint16_t crc = 0;
	//check_t = CellCount;
	DALY_TxHeader.IdType         = FDCAN_EXTENDED_ID;
	DALY_TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	DALY_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	DALY_TxHeader.FDFormat	     = FDCAN_CLASSIC_CAN;

	if(HAL_FDCAN_GetRxFifoFillLevel(DALY_fdcan1h, FDCAN_RX_FIFO0) > 0)
	{
		HAL_FDCAN_GetRxMessage(DALY_fdcan1h,FDCAN_RX_FIFO0,&DALY_RxHeader,DALY_canTxData);

		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);

		if(	(DALY_RxHeader.IdType == FDCAN_EXTENDED_ID)&&
			(DALY_RxHeader.RxFrameType == FDCAN_DATA_FRAME)&&
			(DALY_RxHeader.FDFormat == FDCAN_CLASSIC_CAN))
		{
			//Below three lines to see what we are getting through bmsResponse variable
//			uint32_t canRxID = DALY_RxHeader.Identifier;
//			canRxID = canRxID & 0x00FF0000;
//			bmsResponse = canRxID>>16;

			switch(DALY_RxHeader.Identifier)
			{

				case 0x18900140:	//	cumulative Voltage, Gather Voltage, Current, SOC
					DALY_TxHeader.Identifier = 0x18904001;
					DALY_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					DALY_canTxData[0] = ((uint16_t)((float)CellCount*3.25*10) >> 8);
					DALY_canTxData[1] = ((uint16_t)((float)CellCount*3.25*10) & 0xff);
					DALY_canTxData[2] = ((uint16_t)((float)CellCount*3.19*10) >> 8);//0x01;
					DALY_canTxData[3] = ((uint16_t)((float)CellCount*3.19*10) & 0xff);//0xEA;
					uint16_t current_data = (uint16_t)(100+30000); //(((canRxData[4] << 8) | (canRxData[5] & 0xFF))-30000)*10;
					DALY_canTxData[4] = (uint8_t)(current_data >> 8) ;
					DALY_canTxData[5] = (uint8_t)(current_data & 0xFF);
					//DALY_canTxData[4] = 0x75;
					//DALY_canTxData[5] = 0x94;
					DALY_canTxData[6] = 0x02;//0x03;
					DALY_canTxData[7] = 0xEE;//0xDE;

					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
					break;

				case 0x18980140:	//	Protections
					DALY_TxHeader.Identifier = 0x18984001;
					DALY_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;

					DALY_canTxData[0] = 0x00;
					DALY_canTxData[1] = 0x00;	//	10Ah capacity
					DALY_canTxData[2] = 0x00;
					DALY_canTxData[3] = 0x00;	//	10 cycles
					DALY_canTxData[4] = 0x00;
					DALY_canTxData[5] = 0x00;	//	75% SOC
					DALY_canTxData[6] = 0x00;
					DALY_canTxData[7] = 0x00;

					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
					break;

				case 0x18940140:	//	No of cells, No of Temp Sens, Charger Status, Load Status
					DALY_TxHeader.Identifier = 0x18944001;
					DALY_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;

					DALY_canTxData[0] = 0x0F;
					DALY_canTxData[1] = 0x05;	//	Balancing off cell  1~16
					DALY_canTxData[2] = 0x00;
					DALY_canTxData[3] = 0x00;	//	Balancing off cell 17~32
					DALY_canTxData[4] = 0x00;
					DALY_canTxData[5] = 0x00;	//	No Trip on protections
					DALY_canTxData[6] = 0x00;
					DALY_canTxData[7] = 0x00;

					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
					break;

				case 0x18960140:	//	Frame Number, cell1temp, cell2temp, cell3temp, cell4temp, cell5temp,cell6temp,cell7temp
					DALY_TxHeader.Identifier = 0x18964001;
					DALY_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					DALY_canTxData[0] = 0x01;
					DALY_canTxData[1] = 0x3C;	//	Charge and Discharge MOS on
					DALY_canTxData[2] = 0x3D;
					DALY_canTxData[3] = 0x3E;	//	Date code
					DALY_canTxData[4] = 0x3F;
					DALY_canTxData[5] = 0x2F;	//	software version
					DALY_canTxData[6] = 0x2E;
					DALY_canTxData[7] = 0x2D;

					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
					break;

				case 0x18930140:	//	Mosfet status
					DALY_TxHeader.Identifier = 0x18934001;
					DALY_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					DALY_canTxData[0] = 0x00;
					DALY_canTxData[1] = 0x01;	//	Charge and Discharge MOS on
					DALY_canTxData[2] = 0x01;
					DALY_canTxData[3] = 0x00;	//	Date code
					DALY_canTxData[4] = 0x00;
					DALY_canTxData[5] = 0x00;	//	software version
					DALY_canTxData[6] = 0x00;
					DALY_canTxData[7] = 0x00;

					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
					break;
				case 0x18910140:	//	Mosfet status
					DALY_TxHeader.Identifier = 0x18914001;
					DALY_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					DALY_canTxData[0] = 0x0D;
					DALY_canTxData[1] = 0x20;	//	Charge and Discharge MOS on
					DALY_canTxData[2] = 0x01;
					DALY_canTxData[3] = 0x0D;	//	Date code
					DALY_canTxData[4] = 0x16;
					DALY_canTxData[5] = 0x00;	//	software version
					DALY_canTxData[6] = 0x00;
					DALY_canTxData[7] = 0x00;

					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
					break;
				case 0x18920140:	//	Mosfet status
					DALY_TxHeader.Identifier = 0x18924001;
					DALY_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					DALY_canTxData[0] = 0x43;
					DALY_canTxData[1] = 0x20;	//	Charge and Discharge MOS on
					DALY_canTxData[2] = 0x41;
					DALY_canTxData[3] = 0x0D;	//	Date code
					DALY_canTxData[4] = 0x16;
					DALY_canTxData[5] = 0x00;	//	software version
					DALY_canTxData[6] = 0x00;
					DALY_canTxData[7] = 0x00;

					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
					break;
				case 0x12104090:	//	Mosfet status
					DALY_TxHeader.Identifier = 0x12109040;
					DALY_TxHeader.DataLength = FDCAN_DLC_BYTES_1;

					DALY_canTxData[0] = 0x55;
					DALY_canTxData[1] = 0x00;	//	Charge and Discharge MOS on
					DALY_canTxData[2] = 0x00;
					DALY_canTxData[3] = 0x00;	//	Date code
					DALY_canTxData[4] = 0x00;
					DALY_canTxData[5] = 0x00;	//	software version
					DALY_canTxData[6] = 0x00;
					DALY_canTxData[7] = 0x00;

					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
					break;
				case 0x12114090:	//	Mosfet status
					DALY_TxHeader.Identifier = 0x12119040;
					DALY_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					DALY_canTxData[0] = 0x00;
					DALY_canTxData[1] = 0x00;	//	Charge and Discharge MOS on
					DALY_canTxData[2] = 0x00;
					DALY_canTxData[3] = 0x64;	//	Date code
					DALY_canTxData[4] = 0x01;
					DALY_canTxData[5] = 0x00;	//	software version
					DALY_canTxData[6] = 0x00;
					DALY_canTxData[7] = 0x00;

					if( HAL_FDCAN_GetTxFifoFreeLevel(DALY_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(DALY_fdcan1h, &DALY_TxHeader, DALY_canTxData);
					break;

			}
		}
	}
}
