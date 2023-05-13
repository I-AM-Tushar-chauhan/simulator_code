/*
 * CAN_Communication.c
 *
 *  Created on: Nov 24, 2022
 *      Author: tgopi
 */

#include "CAN_Communication.h"

FDCAN_TxHeaderTypeDef TxHeader;
uint8_t canTxData[8];

FDCAN_RxHeaderTypeDef RxHeader;
uint8_t canRxData[8];

FDCAN_HandleTypeDef* fdcan1h;

typedef enum
{
	//	JBD BMS Based Batteries
	OKAYA_69V_BATTERY		=	0,
	OKAYA_84V_BATTERY,
	GODAWARI_58V_BATTERY,

	JBD_BMS_BASED_BATTERIES_MAX,

	//	Daly BMS Based Batteries

}BatteryModelTypedef;

//uint8_t check_t;
//list of voltages for each battery
float JBD_voltages[JBD_BMS_BASED_BATTERIES_MAX] = {
		65.0,	//	OKAYA 69V battery
		78.0,	//	OKAYA 84B battery
		50.0	//	Godawari 58V battery
};

// JBD BMS crc
uint16_t getCRCJBD( uint8_t *buff, int len )
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


void JBD_BMS_Communication(FDCAN_HandleTypeDef* hf, uint8_t CellCount)
{
	fdcan1h = hf;
	uint16_t crc = 0;
	//check_t = CellCount;
	TxHeader.IdType         = FDCAN_STANDARD_ID;
	TxHeader.TxFrameType    = FDCAN_DATA_FRAME;
	TxHeader.DataLength     = FDCAN_DLC_BYTES_8;
	TxHeader.FDFormat	    = FDCAN_CLASSIC_CAN;

	if(HAL_FDCAN_GetRxFifoFillLevel(fdcan1h, FDCAN_RX_FIFO0) > 0)
	{
		HAL_FDCAN_GetRxMessage(fdcan1h,FDCAN_RX_FIFO0,&RxHeader,canRxData);

		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);

		if(	(RxHeader.RxFrameType == FDCAN_REMOTE_FRAME)&&
			(RxHeader.IdType == FDCAN_STANDARD_ID)&&
			(RxHeader.FDFormat == FDCAN_CLASSIC_CAN))
		{

			switch(RxHeader.Identifier)
			{
				case 0x100:	//	Voltage and Current
					TxHeader.Identifier = 0x100;
					TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					canTxData[0] = ((uint16_t)((float)CellCount*3.25*100) >> 8);
					canTxData[1] = ((uint16_t)((float)CellCount*3.25*100) & 0xff);
					canTxData[2] = 0x00;
					canTxData[3] = 0x64;	//	1A current
					canTxData[4] = 0x03;
					canTxData[5] = 0xE8;	//	10Ah capacity

					crc = getCRCJBD(canTxData,6);
					canTxData[6] = crc >> 8;
					canTxData[7] = crc & 0xff;

					if( HAL_FDCAN_GetTxFifoFreeLevel(fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(fdcan1h, &TxHeader, canTxData);
					break;

				case 0x101:	//	RSoC status	-	75% for all models
					TxHeader.Identifier = 0x101;
					TxHeader.DataLength     = FDCAN_DLC_BYTES_8;

					canTxData[0] = 0x03;
					canTxData[1] = 0xE8;	//	10Ah capacity
					canTxData[2] = 0x00;
					canTxData[3] = 0x0A;	//	10 cycles
					canTxData[4] = 0x00;
					canTxData[5] = 0x4B;	//	75% SOC

					crc = getCRCJBD(canTxData,6);
					canTxData[6] = crc >> 8;
					canTxData[7] = crc & 0xff;

					if( HAL_FDCAN_GetTxFifoFreeLevel(fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(fdcan1h, &TxHeader, canTxData);
					break;

				case 0x102:	//	Protections	-	No trip for all models
					TxHeader.Identifier = 0x102;
					TxHeader.DataLength     = FDCAN_DLC_BYTES_8;

					canTxData[0] = 0x00;
					canTxData[1] = 0x00;	//	Balancing off cell  1~16
					canTxData[2] = 0x00;
					canTxData[3] = 0x00;	//	Balancing off cell 17~32
					canTxData[4] = 0x00;
					canTxData[5] = 0x00;	//	No Trip on protections

					crc = getCRCJBD(canTxData,6);
					canTxData[6] = crc >> 8;
					canTxData[7] = crc & 0xff;

					if( HAL_FDCAN_GetTxFifoFreeLevel(fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(fdcan1h, &TxHeader, canTxData);
					break;

				case 0x103:	//	Mosfet Status	-	Charge and Discharge enabled for all models
					TxHeader.Identifier = 0x103;
					TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					canTxData[0] = 0x00;
					canTxData[1] = 0x03;	//	Charge and Discharge MOS on
					canTxData[2] = 0x20;
					canTxData[3] = 0x68;	//	Date code
					canTxData[4] = 0x00;
					canTxData[5] = 0x03;	//	software version

					crc = getCRCJBD(canTxData,6);
					canTxData[6] = crc >> 8;
					canTxData[7] = crc & 0xff;

					if( HAL_FDCAN_GetTxFifoFreeLevel(fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(fdcan1h, &TxHeader, canTxData);
					break;

				case 0x104:	//	NTC				-	No of NTC based on Battery
					TxHeader.Identifier = 0x104;
					TxHeader.DataLength = FDCAN_DLC_BYTES_4;
					canTxData[0] = CellCount;	//No of cells
					canTxData[1] = 0x04;	//	No of NTC

					crc = getCRCJBD(canTxData,2);
					canTxData[2] = crc >> 8;
					canTxData[3] = crc & 0xff;

					if( HAL_FDCAN_GetTxFifoFreeLevel(fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(fdcan1h, &TxHeader, canTxData);
					break;

				case 0x105:	//	NTC 1 to 3		-	All 25deg C
					TxHeader.Identifier = 0x105;
					TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					canTxData[0] = 0x0B;
					canTxData[1] = 0xA4;	//	NTC 1 temperature 25C
					canTxData[2] = 0x0B;
					canTxData[3] = 0xA4;	//	NTC 2 temperature 25C
					canTxData[4] = 0x0B;
					canTxData[5] = 0xA4;	//	NTC 3 temperature 25C

					crc = getCRCJBD(canTxData,6);
					canTxData[6] = crc >> 8;
					canTxData[7] = crc & 0xff;

					if( HAL_FDCAN_GetTxFifoFreeLevel(fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(fdcan1h, &TxHeader, canTxData);
					break;

				case 0x106:	//	NTC 4 to 6		-	All 25deg C
					TxHeader.Identifier = 0x106;
					TxHeader.DataLength = FDCAN_DLC_BYTES_8;

					canTxData[0] = 0x0B;
					canTxData[1] = 0xA4;	//	NTC 4 temperature 25C
					canTxData[2] = 0x0B;
					canTxData[3] = 0xA4;	//	NTC 5 temperature 25C
					canTxData[4] = 0x0B;
					canTxData[5] = 0xA4;	//	NTC 6 temperature 25C

					crc = getCRCJBD(canTxData,6);
					canTxData[6] = crc >> 8;
					canTxData[7] = crc & 0xff;

					if( HAL_FDCAN_GetTxFifoFreeLevel(fdcan1h) > 0)
						HAL_FDCAN_AddMessageToTxFifoQ(fdcan1h, &TxHeader, canTxData);
					break;
			}
		}
	}
}
