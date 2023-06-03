/*
 * CAN_Communication.c
 *
 *  Created on: MAR 3, 2023
 *      Author: TUSHAR
 */

#include <EXIDE.h>

FDCAN_TxHeaderTypeDef E_TxHeader;
uint8_t E_canTxData[8];

FDCAN_RxHeaderTypeDef E_RxHeader;
uint8_t E_canRxData[8];

FDCAN_HandleTypeDef* E_fdcan1h;

void EXIDE(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	E_fdcan1h = hf;
	//uint16_t crc = 0;
	//check_t = CellCount;
	E_TxHeader.IdType         = FDCAN_EXTENDED_ID;
	E_TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	E_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	E_TxHeader.FDFormat	    = FDCAN_CLASSIC_CAN;

	if(HAL_FDCAN_GetRxFifoFillLevel(E_fdcan1h, FDCAN_RX_FIFO0) > 0)
	{
		HAL_FDCAN_GetRxMessage(E_fdcan1h,FDCAN_RX_FIFO0,&E_RxHeader,E_canRxData);

		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);

		if(	(E_RxHeader.RxFrameType == FDCAN_DATA_FRAME)&&
			(E_RxHeader.IdType == FDCAN_EXTENDED_ID)&&
			(E_RxHeader.FDFormat == FDCAN_CLASSIC_CAN))
		{

			switch(E_RxHeader.Identifier)
			{
			case 0x10FD151A:

				E_TxHeader.Identifier = 0x18FF01D0;
				E_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				E_canTxData[0] = ((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
				E_canTxData[1] = ((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
				E_canTxData[2] = 0xD0;//CURRENT HIGH
				E_canTxData[3] = 0xFC;//CURRENT LOW	25A current
				E_canTxData[4] = 0x0C;//START CHARGING AND STOP CHARGING
				E_canTxData[5] = 0xFC;//	 N/A
				E_canTxData[6] = 0x0D;//   N/A
				E_canTxData[7] = 0x17;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(E_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(E_fdcan1h, &E_TxHeader, E_canTxData);

				 HAL_Delay(2);

				E_TxHeader.Identifier = 0x18FF005B;
				E_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				E_canTxData[0] = 0x01;//
				E_canTxData[1] = 0x90;//
				E_canTxData[2] = 0x04;//CURRENT HIGH
				E_canTxData[3] = 0xA0;//CURRENT LOW	25A current
				E_canTxData[4] = 0x0F;//START CHARGING AND STOP CHARGING
				E_canTxData[5] = 0x00;//	 N/A
				E_canTxData[6] = 0x00;//   N/A
				E_canTxData[7] = 0x00;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(E_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(E_fdcan1h, &E_TxHeader, E_canTxData);

				 HAL_Delay(2);


				E_TxHeader.Identifier = 0x18FF02D0;
				E_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				E_canTxData[0] = 0x42; //Battery Voltage High Byte
				E_canTxData[1] = 0x17; //Battery Voltage Low Byte
				E_canTxData[2] = 0x96; //Battery Current High Byte
				E_canTxData[3] = 0x4D; //Battery Current Low Byte
				E_canTxData[4] = 0x00; //Battery SoC
				E_canTxData[5] = 0x00; //Battery Temperature
				E_canTxData[6] = 0x00; //Charging Status
				E_canTxData[7] = 0x00; //Reserved

				if( HAL_FDCAN_GetTxFifoFreeLevel(E_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(E_fdcan1h, &E_TxHeader, E_canTxData);
				 HAL_Delay(2);

				E_TxHeader.Identifier = 0x18FF03D0;
				E_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				E_canTxData[0] = 0x01;
				E_canTxData[1] = 0x38;
				E_canTxData[2] = 0x01;
				E_canTxData[3] = 0x40;  // No of cell strings
				E_canTxData[4] = 0x01;
				E_canTxData[5] = 0x3D;
				E_canTxData[6] = 0x00;
				E_canTxData[7] = 0x00;

				if( HAL_FDCAN_GetTxFifoFreeLevel(E_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(E_fdcan1h, &E_TxHeader, E_canTxData);
				 HAL_Delay(2);

				E_TxHeader.Identifier = 0x18FF05D0;
				E_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				E_canTxData[0] = 0x11; //Cell 1 High Byte
				E_canTxData[1] = 0x5A; //Cell 1 Low Byte
				E_canTxData[2] = 0x27; //Cell 2 High Byte
				E_canTxData[3] = 0x0F; //Cell 2 Low Byte
				E_canTxData[4] = 0x40; //Cell 3 High Byte
				E_canTxData[5] = 0x44; //Cell 3 Low Byte
				E_canTxData[6] = 0x82; //Cell 4 High Byte
				E_canTxData[7] = 0x55; //Cell 4 Low Byte

				if( HAL_FDCAN_GetTxFifoFreeLevel(E_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(E_fdcan1h, &E_TxHeader, E_canTxData);

				 HAL_Delay(2);

				E_TxHeader.Identifier = 0x18FF10D0;
				E_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				E_canTxData[0] = 0x9C; //Cell 1 High Byte
				E_canTxData[1] = 0x00; //Cell 1 Low Byte
				E_canTxData[2] = 0xA0; //Cell 2 High Byte
				E_canTxData[3] = 0x00; //Cell 2 Low Byte
				E_canTxData[4] = 0xA4; //Cell 3 High Byte
				E_canTxData[5] = 0x00; //Cell 3 Low Byte
				E_canTxData[6] = 0xA8; //Cell 4 High Byte
				E_canTxData[7] = 0x00; //Cell 4 Low Byte

				if( HAL_FDCAN_GetTxFifoFreeLevel(E_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(E_fdcan1h, &E_TxHeader, E_canTxData);

//				 HAL_Delay(2);

//				S_TxHeader.Identifier = 0x18FF05FF;
//				S_TxHeader.DataLength = FDCAN_DLC_BYTES_8;
//
//				S_canTxData[0] = 0x0C; //Cell 1 High Byte
//				S_canTxData[1] = 0xE5; //Cell 1 Low Byte
//				S_canTxData[2] = 0x0C; //Cell 2 High Byte
//				S_canTxData[3] = 0xF6; //Cell 2 Low Byte
//				S_canTxData[4] = 0x0C; //Cell 3 High Byte
//				S_canTxData[5] = 0xF5; //Cell 3 Low Byte
//				S_canTxData[6] = 0x0C; //Cell 4 High Byte
//				S_canTxData[7] = 0xF1; //Cell 4 Low Byte
//
//				if( HAL_FDCAN_GetTxFifoFreeLevel(S_fdcan1h) > 0)
//					HAL_FDCAN_AddMessageToTxFifoQ(S_fdcan1h, &S_TxHeader, S_canTxData);
//				 HAL_Delay(2);
//
//				S_TxHeader.Identifier = 0x18FF06FF;
//				S_TxHeader.DataLength = FDCAN_DLC_BYTES_8;
//
//				S_canTxData[0] = 0x0C; //Cell 1 High Byte
//				S_canTxData[1] = 0xE5; //Cell 1 Low Byte
//				S_canTxData[2] = 0x0C; //Cell 2 High Byte
//				S_canTxData[3] = 0xF6; //Cell 2 Low Byte
//				S_canTxData[4] = 0x0C; //Cell 3 High Byte
//				S_canTxData[5] = 0xF5; //Cell 3 Low Byte
//				S_canTxData[6] = 0x0C; //Cell 4 High Byte
//				S_canTxData[7] = 0xF1; //Cell 4 Low Byte
//
//				if( HAL_FDCAN_GetTxFifoFreeLevel(S_fdcan1h) > 0)
//					HAL_FDCAN_AddMessageToTxFifoQ(S_fdcan1h, &S_TxHeader, S_canTxData);
//				 HAL_Delay(2);
//
//				S_TxHeader.Identifier = 0x18FF07FF;
//				S_TxHeader.DataLength = FDCAN_DLC_BYTES_8;
//
//				S_canTxData[0] = 0x0C; //Cell 1 High Byte
//				S_canTxData[1] = 0xE5; //Cell 1 Low Byte
//				S_canTxData[2] = 0x0C; //Cell 2 High Byte
//				S_canTxData[3] = 0xF6; //Cell 2 Low Byte
//				S_canTxData[4] = 0x0C; //Cell 3 High Byte
//				S_canTxData[5] = 0xF5; //Cell 3 Low Byte
//				S_canTxData[6] = 0x0C; //Cell 4 High Byte
//				S_canTxData[7] = 0xF1; //Cell 4 Low Byte
//
//				if( HAL_FDCAN_GetTxFifoFreeLevel(S_fdcan1h) > 0)
//					HAL_FDCAN_AddMessageToTxFifoQ(S_fdcan1h, &S_TxHeader, S_canTxData);
//				 HAL_Delay(2);
//
//				S_TxHeader.Identifier = 0x18FF08FF;
//				S_TxHeader.DataLength = FDCAN_DLC_BYTES_8;
//
//				S_canTxData[0] = 0x0C; //Cell 1 High Byte
//				S_canTxData[1] = 0xE5; //Cell 1 Low Byte
//				S_canTxData[2] = 0x0C; //Cell 2 High Byte
//				S_canTxData[3] = 0xF6; //Cell 2 Low Byte
//				S_canTxData[4] = 0x0C; //Cell 3 High Byte
//				S_canTxData[5] = 0xF5; //Cell 3 Low Byte
//				S_canTxData[6] = 0x0C; //Cell 4 High Byte
//				S_canTxData[7] = 0xF1; //Cell 4 Low Byte
//
//				if( HAL_FDCAN_GetTxFifoFreeLevel(S_fdcan1h) > 0)
//					HAL_FDCAN_AddMessageToTxFifoQ(S_fdcan1h, &S_TxHeader, S_canTxData);
//				 HAL_Delay(2);
//
//				S_TxHeader.Identifier = 0x18FF09FF;
//				S_TxHeader.DataLength = FDCAN_DLC_BYTES_8;
//
//				S_canTxData[0] = 0x0C; //Cell 1 High Byte
//				S_canTxData[1] = 0xE5; //Cell 1 Low Byte
//				S_canTxData[2] = 0x0C; //Cell 2 High Byte
//				S_canTxData[3] = 0xF6; //Cell 2 Low Byte
//				S_canTxData[4] = 0x0C; //Cell 3 High Byte
//				S_canTxData[5] = 0xF5; //Cell 3 Low Byte
//				S_canTxData[6] = 0x00; //Cell 4 High Byte
//				S_canTxData[7] = 0x00; //Cell 4 Low Byte
//
//				if( HAL_FDCAN_GetTxFifoFreeLevel(S_fdcan1h) > 0)
//					HAL_FDCAN_AddMessageToTxFifoQ(S_fdcan1h, &S_TxHeader, S_canTxData);
//				 HAL_Delay(2);



			break;

			}
		}
	}
}
