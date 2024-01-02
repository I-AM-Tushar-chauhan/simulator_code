/*
 * CAN_Communication.c
 *
 *  Created on: Nov 24, 2022
 *      Author: tgopi
 */

#include "GODAWARI.h"

FDCAN_TxHeaderTypeDef G_TxHeader;
uint8_t G_canTxData[8];

FDCAN_RxHeaderTypeDef G_RxHeader;
uint8_t G_canRxData[8];

FDCAN_HandleTypeDef* G_fdcan1h;

uint8_t ID_FLAG=0;
typedef enum
{
	//	JBD BMS Based Batteries
	OKAYA_69V_BATTERY		=	0,
	OKAYA_84V_BATTERY,
	GODAWARI_58V_BATTERY,

	JBD_BMS_BASED_BATTERIES_MAX,

	//	Daly BMS Based Batteries

}BatteryModelTypedef;


// JBD BMS crc
uint16_t GodawariCRC( uint8_t *buff, int len )
{
 uint16_t crc = 0xFFFF;

  for (int pos = 0; pos < len; pos++) {
    crc ^= (uint16_t)buff[pos];          // XOR byte into least sig. byte of crc

    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;
}


void GODAWARI(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	G_fdcan1h = hf;
	uint16_t crc = 0;
	//check_t = CellCount;
	G_TxHeader.IdType         = FDCAN_STANDARD_ID;
	G_TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	G_TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	G_TxHeader.FDFormat	    = FDCAN_CLASSIC_CAN;

	if(HAL_FDCAN_GetRxFifoFillLevel(G_fdcan1h, FDCAN_RX_FIFO0) > 0)
	{
		HAL_FDCAN_GetRxMessage(G_fdcan1h,FDCAN_RX_FIFO0,&G_RxHeader,G_canRxData);

		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);

		if(	(G_RxHeader.RxFrameType == FDCAN_DATA_FRAME)&&
			(G_RxHeader.IdType == FDCAN_STANDARD_ID)&&
			(G_RxHeader.FDFormat == FDCAN_CLASSIC_CAN))
		{
			if(G_RxHeader.Identifier == 0x18B )
			{
				ID_FLAG=1;
			}
		}
		if(	(G_RxHeader.RxFrameType == FDCAN_REMOTE_FRAME)&&
			(G_RxHeader.IdType == FDCAN_STANDARD_ID)&&
			(G_RxHeader.FDFormat == FDCAN_CLASSIC_CAN))
		{
			if(ID_FLAG == 1)
			{
				switch(G_RxHeader.Identifier)
				{
					case 0x100:	//	Voltage and Current
						G_TxHeader.Identifier = 0x100;
						G_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

						G_canTxData[0] = ((uint16_t)((float)CellCount*3.25*100) >> 8);
						G_canTxData[1] = ((uint16_t)((float)CellCount*3.25*100) & 0xff);
						G_canTxData[2] = 0x00;
						G_canTxData[3] = 0x64;	//	1A current
						G_canTxData[4] = 0x03;
						G_canTxData[5] = 0xE8;	//	10Ah capacity

						crc = GodawariCRC(G_canTxData,6);
						G_canTxData[6] = crc >> 8;
						G_canTxData[7] = crc & 0xff;

						if( HAL_FDCAN_GetTxFifoFreeLevel(G_fdcan1h) > 0)
							HAL_FDCAN_AddMessageToTxFifoQ(G_fdcan1h, &G_TxHeader, G_canTxData);
						HAL_Delay(1);
						ID_FLAG = 0;//we using in 0x100 because it's check in main code least i mean at the last position
						break;

					case 0x101:	//	RSoC status	-	75% for all models
						G_TxHeader.Identifier = 0x101;
						G_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

						G_canTxData[0] = 0x03;
						G_canTxData[1] = 0xE8;	//	10Ah capacity
						G_canTxData[2] = 0x00;
						G_canTxData[3] = 0x0A;	//	10 cycles
						G_canTxData[4] = 0x00;
						G_canTxData[5] = 0x4B;	//	75% SOC

						crc = GodawariCRC(G_canTxData,6);
						G_canTxData[6] = crc >> 8;
						G_canTxData[7] = crc & 0xff;

						if( HAL_FDCAN_GetTxFifoFreeLevel(G_fdcan1h) > 0)
							HAL_FDCAN_AddMessageToTxFifoQ(G_fdcan1h, &G_TxHeader, G_canTxData);
						break;

					case 0x102:	//	Protections	-	No trip for all models
						G_TxHeader.Identifier = 0x102;
						G_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

						G_canTxData[0] = 0x00;
						G_canTxData[1] = 0x00;	//	Balancing off cell  1~16
						G_canTxData[2] = 0x00;
						G_canTxData[3] = 0x00;	//	Balancing off cell 17~32
						G_canTxData[4] = 0x00;
						G_canTxData[5] = 0x00;	//	No Trip on protections

						crc = GodawariCRC(G_canTxData,6);
						G_canTxData[6] = crc >> 8;
						G_canTxData[7] = crc & 0xff;

						if( HAL_FDCAN_GetTxFifoFreeLevel(G_fdcan1h) > 0)
							HAL_FDCAN_AddMessageToTxFifoQ(G_fdcan1h, &G_TxHeader, G_canTxData);
						break;

					case 0x103:	//	Mosfet Status	-	Charge and Discharge enabled for all models
						G_TxHeader.Identifier = 0x103;
						G_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

						G_canTxData[0] = 0x00;
						G_canTxData[1] = 0x03;	//	Charge and Discharge MOS on
						G_canTxData[2] = 0x20;
						G_canTxData[3] = 0x68;	//	Date code
						G_canTxData[4] = 0x00;
						G_canTxData[5] = 0x03;	//	software version

						crc = GodawariCRC(G_canTxData,6);
						G_canTxData[6] = crc >> 8;
						G_canTxData[7] = crc & 0xff;

						if( HAL_FDCAN_GetTxFifoFreeLevel(G_fdcan1h) > 0)
							HAL_FDCAN_AddMessageToTxFifoQ(G_fdcan1h, &G_TxHeader, G_canTxData);
						break;

					case 0x104:	//	NTC				-	No of NTC based on Battery
						G_TxHeader.Identifier = 0x104;
						G_TxHeader.DataLength = FDCAN_DLC_BYTES_4;
						G_canTxData[0] = CellCount;	//No of cells
						G_canTxData[1] = 0x04;	//	No of NTC

						crc = GodawariCRC(G_canTxData,2);
						G_canTxData[2] = crc >> 8;
						G_canTxData[3] = crc & 0xff;

						if( HAL_FDCAN_GetTxFifoFreeLevel(G_fdcan1h) > 0)
							HAL_FDCAN_AddMessageToTxFifoQ(G_fdcan1h, &G_TxHeader, G_canTxData);
						break;

					case 0x105:	//	NTC 1 to 3		-	All 25deg C
						G_TxHeader.Identifier = 0x105;
						G_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

						G_canTxData[0] = 0x0B;
						G_canTxData[1] = 0xA4;	//	NTC 1 temperature 25C
						G_canTxData[2] = 0x0B;
						G_canTxData[3] = 0xA4;	//	NTC 2 temperature 25C
						G_canTxData[4] = 0x0B;
						G_canTxData[5] = 0xA4;	//	NTC 3 temperature 25C

						crc = GodawariCRC(G_canTxData,6);
						G_canTxData[6] = crc >> 8;
						G_canTxData[7] = crc & 0xff;

						if( HAL_FDCAN_GetTxFifoFreeLevel(G_fdcan1h) > 0)
							HAL_FDCAN_AddMessageToTxFifoQ(G_fdcan1h, &G_TxHeader, G_canTxData);
						break;

					case 0x106:	//	NTC 4 to 6		-	All 25deg C
						G_TxHeader.Identifier = 0x106;
						G_TxHeader.DataLength = FDCAN_DLC_BYTES_8;

						G_canTxData[0] = 0x0B;
						G_canTxData[1] = 0xA4;	//	NTC 4 temperature 25C
						G_canTxData[2] = 0x0B;
						G_canTxData[3] = 0xA4;	//	NTC 5 temperature 25C
						G_canTxData[4] = 0x0B;
						G_canTxData[5] = 0xA4;	//	NTC 6 temperature 25C

						crc = GodawariCRC(G_canTxData,6);
						G_canTxData[6] = crc >> 8;
						G_canTxData[7] = crc & 0xff;

						if( HAL_FDCAN_GetTxFifoFreeLevel(G_fdcan1h) > 0)
							HAL_FDCAN_AddMessageToTxFifoQ(G_fdcan1h, &G_TxHeader, G_canTxData);
						break;
				}
			}


			}


		}
	}
//}
