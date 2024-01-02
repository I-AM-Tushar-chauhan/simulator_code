/*
 * CAN_Communication.c
 *
 *  Created on: MAR 3, 2023
 *      Author: TUSHAR
 */

#include "Pixel.h"

FDCAN_TxHeaderTypeDef Pixel_TxHeader;
uint8_t Pixel_canTxData[8];

FDCAN_RxHeaderTypeDef Pixel_RxHeader;
uint8_t Pixel_canRxData[8];

FDCAN_HandleTypeDef* Pixel_fdcan1h;

void Pixel(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	Pixel_fdcan1h = hf;
	//uint16_t crc = 0;
	//check_t = CellCount;
	Pixel_TxHeader.IdType         = FDCAN_EXTENDED_ID;
	Pixel_TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	Pixel_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	Pixel_TxHeader.FDFormat	      = FDCAN_CLASSIC_CAN;

	if(HAL_FDCAN_GetRxFifoFillLevel(Pixel_fdcan1h, FDCAN_RX_FIFO0) > 0)
	{
		HAL_FDCAN_GetRxMessage(Pixel_fdcan1h,FDCAN_RX_FIFO0,&Pixel_RxHeader,Pixel_canRxData);

		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);

		if(	(Pixel_RxHeader.RxFrameType == FDCAN_DATA_FRAME)&&
			(Pixel_RxHeader.IdType == FDCAN_EXTENDED_ID)&&
			(Pixel_RxHeader.FDFormat == FDCAN_CLASSIC_CAN))
		{

			switch(Pixel_RxHeader.Identifier)
			{
				case 0x18FF50E5:	//	Voltage and Current

					Pixel_TxHeader.Identifier = 0x18FFE5F4;
					Pixel_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					Pixel_canTxData[0] = ((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
					Pixel_canTxData[1] = ((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
					Pixel_canTxData[2] = 0x00;//CURRENT HIGH
					Pixel_canTxData[3] = 0xFA;//CURRENT LOW	25A current
					Pixel_canTxData[4] = 0x00;//START CHARGING AND STOP CHARGING
					Pixel_canTxData[5] = 0x00;//	 N/A
					Pixel_canTxData[6] = 0x00;//   N/A
					Pixel_canTxData[7] = 0x00;//   N/A

					if( HAL_FDCAN_GetTxFifoFreeLevel(Pixel_fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(Pixel_fdcan1h, &Pixel_TxHeader,Pixel_canTxData);

			}
		}
	}
}
