/*
 * AEIDTH.c
 *
 *  Created on: JUNE 6, 2023
 *      Author: TUSHAR
 */

#include <AEIDTH.h>

FDCAN_TxHeaderTypeDef AEIDTH_TxHeader;
uint8_t AEIDTH_canTxData[8];

FDCAN_RxHeaderTypeDef AEIDTH_RxHeader;
uint8_t AEIDTH_canRxData[8];

FDCAN_HandleTypeDef* AEIDTH_fdcan1h;

void AEIDTH(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	AEIDTH_fdcan1h = hf;
	//uint16_t crc = 0;
	//check_t = CellCount;
	AEIDTH_TxHeader.IdType         = FDCAN_EXTENDED_ID;
	AEIDTH_TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	AEIDTH_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	AEIDTH_TxHeader.FDFormat	    = FDCAN_CLASSIC_CAN;

	if(HAL_FDCAN_GetRxFifoFillLevel(AEIDTH_fdcan1h, FDCAN_RX_FIFO0) > 0)
	{
		HAL_FDCAN_GetRxMessage(AEIDTH_fdcan1h,FDCAN_RX_FIFO0,&AEIDTH_RxHeader,AEIDTH_canRxData);

		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);

		if(	(AEIDTH_RxHeader.RxFrameType == FDCAN_DATA_FRAME)&&
			(AEIDTH_RxHeader.IdType == FDCAN_EXTENDED_ID)&&
			(AEIDTH_RxHeader.FDFormat == FDCAN_CLASSIC_CAN))
		{

			switch(AEIDTH_RxHeader.Identifier)
			{
			case 0x10FD151A:

				AEIDTH_TxHeader.Identifier = 0x18FF005B;
				AEIDTH_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				AEIDTH_canTxData[0] = 0x01;//((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
				AEIDTH_canTxData[1] = 0xD0;//((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
				AEIDTH_canTxData[2] = 0x23;//Voltage low      (21C0 for 86.4V)
				AEIDTH_canTxData[3] = 0x28;//Voltage high byte (20A0 for 83.5V)(2328 for 90V)
				AEIDTH_canTxData[4] = 0x0F;//START CHARGING AND STOP CHARGING
				AEIDTH_canTxData[5] = 0x00;//	 N/A
				AEIDTH_canTxData[6] = 0x00;//   N/A
				AEIDTH_canTxData[7] = 0x00;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(AEIDTH_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(AEIDTH_fdcan1h, &AEIDTH_TxHeader, AEIDTH_canTxData);

				 HAL_Delay(50);

				 AEIDTH_TxHeader.Identifier = 0x18963257;
				AEIDTH_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				AEIDTH_canTxData[0] = 0x15;//((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
				AEIDTH_canTxData[1] = 0xFE;//((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
				AEIDTH_canTxData[2] = 0x00;//CURRENT HIGH
				AEIDTH_canTxData[3] = 0x00;//CURRENT LOW	25A current
				AEIDTH_canTxData[4] = 0x1E;//START CHARGING AND STOP CHARGING
				AEIDTH_canTxData[5] = 0x23;//	 N/A
				AEIDTH_canTxData[6] = 0x64;//   N/A
				AEIDTH_canTxData[7] = 0xC2;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(AEIDTH_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(AEIDTH_fdcan1h, &AEIDTH_TxHeader, AEIDTH_canTxData);

				 HAL_Delay(50);

				AEIDTH_TxHeader.Identifier = 0x18963258;
				AEIDTH_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				AEIDTH_canTxData[0] = 0x01;//((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
				AEIDTH_canTxData[1] = 0xFF;//((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
				AEIDTH_canTxData[2] = 0x00;//CURRENT HIGH
				AEIDTH_canTxData[3] = 0x00;//CURRENT LOW	25A current
				AEIDTH_canTxData[4] = 0x63;//START CHARGING AND STOP CHARGING
				AEIDTH_canTxData[5] = 0x64;//	 N/A
				AEIDTH_canTxData[6] = 0x00;//   N/A
				AEIDTH_canTxData[7] = 0x27;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(AEIDTH_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(AEIDTH_fdcan1h, &AEIDTH_TxHeader, AEIDTH_canTxData);

				 HAL_Delay(50);

				AEIDTH_TxHeader.Identifier = 0x18963259;
				AEIDTH_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				AEIDTH_canTxData[0] = 0x0D;//((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
				AEIDTH_canTxData[1] = 0xC4;//((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
				AEIDTH_canTxData[2] = 0x0D;//CURRENT HIGH
				AEIDTH_canTxData[3] = 0xBA;//CURRENT LOW	25A current
				AEIDTH_canTxData[4] = 0x1E;//START CHARGING AND STOP CHARGING
				AEIDTH_canTxData[5] = 0x1D;//	 N/A
				AEIDTH_canTxData[6] = 0x0D;//   N/A
				AEIDTH_canTxData[7] = 0xBF;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(AEIDTH_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(AEIDTH_fdcan1h, &AEIDTH_TxHeader, AEIDTH_canTxData);

				 HAL_Delay(50);

				AEIDTH_TxHeader.Identifier = 0x18963263;
				AEIDTH_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

				AEIDTH_canTxData[0] = 0x00;//((uint16_t)((float)CellCount*3.25*10) >> 8);//VOLTAGE HIGH
				AEIDTH_canTxData[1] = 0x04;//((uint16_t)((float)CellCount*3.25*10) & 0xff);//VOLTAGE LOW
				AEIDTH_canTxData[2] = 0x00;//CURRENT HIGH
				AEIDTH_canTxData[3] = 0x00;//CURRENT LOW	25A current
				AEIDTH_canTxData[4] = 0x00;//START CHARGING AND STOP CHARGING
				AEIDTH_canTxData[5] = 0x00;//	 N/A
				AEIDTH_canTxData[6] = 0x00;//   N/A
				AEIDTH_canTxData[7] = 0x00;//   N/A

				if( HAL_FDCAN_GetTxFifoFreeLevel(AEIDTH_fdcan1h) > 0)
					HAL_FDCAN_AddMessageToTxFifoQ(AEIDTH_fdcan1h, &AEIDTH_TxHeader, AEIDTH_canTxData);
				 HAL_Delay(50);


			break;

			}
		}
	}
}
