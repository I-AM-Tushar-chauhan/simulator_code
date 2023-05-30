/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CAN_Communication.h"
#include "DALY_communication.h"
#include "STH_CAN_Simulator.h"
#include "JLN_Phenix.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
FDCAN_HandleTypeDef hfdcan1;

/* USER CODE BEGIN PV */
uint8_t CellCount = 16;//22 by gopi sir
uint8_t protocol_selection = 0;//1;//1 for godawari and 2 for daly
uint8_t fg_CellCount =0;
uint8_t fg_protocol_selection =0;//flag to set protocols

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_FDCAN1_Init(void);
static void DALY_MX_FDCAN1_Init(void);
static void STH_MX_FDCAN1_Init(void);
//static void JLN_Phenix(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FDCAN1_Init();
  /* USER CODE BEGIN 2 */

  //	LCD Initializing
  //	Select battery model
  HAL_Delay(100);
  TM1723_Initialize();
  HAL_Delay(100);
  TM1723_Clear_Screen();

  Write_7_Segment(5, 1);
  Write_7_Segment(17, 2);
  Write_7_Segment(18, 3);
  Write_7_Segment(17, 4);


  TM1723_Update_Screen();
  HAL_Delay(2000);
  //HAL_FDCAN_Start(&DALY_hfdcan1);
  HAL_FDCAN_Start(&hfdcan1);
  TM1723_Clear_Screen();

 uint8_t First_pos = CellCount/10;
 uint8_t Second_pos = CellCount%10;
  Write_7_Segment(First_pos, 1);
  Write_7_Segment(Second_pos, 2);
  Write_7_Segment(11, 4);
  TM1723_Update_Screen();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//Start the execution of protocol
if(FDCAN1->CCCR & FDCAN_CCCR_INIT_Msk) // Checking if the CCCR INIT flag is set (Bus off State)
      FDCAN1->CCCR &= ~FDCAN_CCCR_INIT;	// Resetting the flag so that bus off can be mitigated

if(protocol_selection == 0)
	  {
		  Write_7_Segment(0, 4);
		  TM1723_Update_Screen();
		  JBD_BMS_Communication(&hfdcan1, CellCount);
	  }
else if(protocol_selection == 1)
	  {
		  Write_7_Segment(1, 4);
		  TM1723_Update_Screen();
		  DALY_BMS_Communication(&hfdcan1, CellCount);
	  }
else if(protocol_selection == 2)
	  {
		  Write_7_Segment(2, 4);
		  TM1723_Update_Screen();
		  STH_BMS_Communication(&hfdcan1, CellCount);
	  }
else if(protocol_selection == 3)
	  {
		  Write_7_Segment(3, 4);
		  TM1723_Update_Screen();
		  DALY_BMS_Communication(&hfdcan1, CellCount);
	  }
else if(protocol_selection == 4)
	  {
		  Write_7_Segment(4, 4);
		  TM1723_Update_Screen();
		  JLN_BMS_Communication(&hfdcan1, CellCount);
	  }
else if(protocol_selection == 5)
	  {
		  Write_7_Segment(5, 4);
		  TM1723_Update_Screen();
		  sonalika(&hfdcan1, CellCount);
	  }
//End the execution of protocol

//Start to update cell count and manage the cell count
 if(TM1723_Read_Switches() == 1)
  {
	  HAL_Delay(1);
	  CellCount++;
	  if (CellCount<10)
	  {
		  Write_7_Segment(CellCount, 1);
		  Write_7_Segment(10, 2);
		  TM1723_Update_Screen();
	  }
	  if (CellCount>=10)
	  {
		  First_pos = CellCount/10;
		  Second_pos = CellCount%10;
		  Write_7_Segment(First_pos, 1);
		  Write_7_Segment(Second_pos, 2);
		  TM1723_Update_Screen();
	  }
	  if(CellCount > 24)
	  {
		  CellCount=1;
		  TM1723_Clear_Screen();
		  Write_7_Segment(CellCount, 1);//working fine but 5 showing of the 25 number
		  TM1723_Update_Screen();
	  }
	  while(TM1723_Read_Switches() == 1);
  }
//End to update cell count

//Start to change protocol

  if(TM1723_Read_Switches() == 2)
	{
	  protocol_selection++;
	    if(protocol_selection>5)
			  {
				  protocol_selection=0;
			  }
	    HAL_Delay(2);
	    switch(protocol_selection)
			  {
			  case 0://for JBD
				  HAL_FDCAN_Stop(&hfdcan1);
				  //FDCAN_HandleTypeDef hfdcan1;
				  MX_FDCAN1_Init();//500Kbps
				  HAL_FDCAN_Start(&hfdcan1);
				  HAL_Delay(1);
				  break;
			  case 1://for DALY
				  HAL_FDCAN_Stop(&hfdcan1);
				 // FDCAN_HandleTypeDef DALY_hfdcan1;
				  DALY_MX_FDCAN1_Init();//250Kbps
				  HAL_FDCAN_Start(&hfdcan1);
				  HAL_Delay(1);
				  break;
			  case 2://for Ruchira New
				  HAL_FDCAN_Stop(&hfdcan1);
				 // FDCAN_HandleTypeDef STH_hfdcan1;
				  STH_MX_FDCAN1_Init();//500Kbps
				  HAL_FDCAN_Start(&hfdcan1);
				  HAL_Delay(1);
				  break;
			  case 3:
			  case 4: //for Inverted Daly
				  HAL_FDCAN_Stop(&hfdcan1);
				 // FDCAN_HandleTypeDef STH_hfdcan1;
				  MX_FDCAN1_Init();//500Kbps
				  HAL_FDCAN_Start(&hfdcan1);
				  HAL_Delay(1);
				  break;
			  case 5://for sonalika
				  HAL_FDCAN_Stop(&hfdcan1);
				 // FDCAN_HandleTypeDef JLN;
				  DALY_MX_FDCAN1_Init();//250Kbps
				  HAL_FDCAN_Start(&hfdcan1);
				  HAL_Delay(1);
				  break;
			  default://By default it is a JBD
				  HAL_FDCAN_Stop(&hfdcan1);
				  //FDCAN_HandleTypeDef hfdcan1;
				  MX_FDCAN1_Init();//500Kbps
				  HAL_FDCAN_Start(&hfdcan1);
				  HAL_Delay(1);
				  break;
			  }
	  while(TM1723_Read_Switches() == 2);
//End to change protocol

	}


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 20;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief FDCAN1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_FDCAN1_Init(void)//for JBD
{

  /* USER CODE BEGIN FDCAN1_Init 0 */

  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */
  hfdcan1.Instance = FDCAN1;
  hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
  hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  hfdcan1.Init.AutoRetransmission = DISABLE;
  hfdcan1.Init.TransmitPause = DISABLE;
  hfdcan1.Init.ProtocolException = DISABLE;
  hfdcan1.Init.NominalPrescaler = 64;
  hfdcan1.Init.NominalSyncJumpWidth = 1;
  hfdcan1.Init.NominalTimeSeg1 = 2;
  hfdcan1.Init.NominalTimeSeg2 = 2;
  hfdcan1.Init.DataPrescaler = 1;
  hfdcan1.Init.DataSyncJumpWidth = 1;
  hfdcan1.Init.DataTimeSeg1 = 1;
  hfdcan1.Init.DataTimeSeg2 = 1;
  hfdcan1.Init.StdFiltersNbr = 0;
  hfdcan1.Init.ExtFiltersNbr = 0;
  hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */

  /* USER CODE END FDCAN1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void DALY_MX_FDCAN1_Init(void)
{

  /* USER CODE BEGIN FDCAN1_Init 0 */

  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */
	hfdcan1.Instance = FDCAN1;
	hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
	hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
	hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
	hfdcan1.Init.AutoRetransmission = DISABLE;
	hfdcan1.Init.TransmitPause = DISABLE;
	hfdcan1.Init.ProtocolException = DISABLE;
	hfdcan1.Init.NominalPrescaler = 64;
	hfdcan1.Init.NominalSyncJumpWidth = 1;
	hfdcan1.Init.NominalTimeSeg1 = 8;
	hfdcan1.Init.NominalTimeSeg2 = 1;
	hfdcan1.Init.DataPrescaler = 1;
	hfdcan1.Init.DataSyncJumpWidth = 1;
	hfdcan1.Init.DataTimeSeg1 = 1;
	hfdcan1.Init.DataTimeSeg2 = 1;
	hfdcan1.Init.StdFiltersNbr = 0;
	hfdcan1.Init.ExtFiltersNbr = 0;
	hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */

  /* USER CODE END FDCAN1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */

static void STH_MX_FDCAN1_Init(void)//for JBD
{

  /* USER CODE BEGIN FDCAN1_Init 0 */

  /* USER CODE END FDCAN1_Init 0 */

  /* USER CODE BEGIN FDCAN1_Init 1 */

  /* USER CODE END FDCAN1_Init 1 */
	hfdcan1.Instance = FDCAN1;
	hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
	hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
	hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
	hfdcan1.Init.AutoRetransmission = DISABLE;
	hfdcan1.Init.TransmitPause = DISABLE;
	hfdcan1.Init.ProtocolException = DISABLE;
	hfdcan1.Init.NominalPrescaler = 64;
	hfdcan1.Init.NominalSyncJumpWidth = 1;
	hfdcan1.Init.NominalTimeSeg1 = 2;
	hfdcan1.Init.NominalTimeSeg2 = 2;
	hfdcan1.Init.DataPrescaler = 1;
	hfdcan1.Init.DataSyncJumpWidth = 1;
	hfdcan1.Init.DataTimeSeg1 = 1;
	hfdcan1.Init.DataTimeSeg2 = 1;
	hfdcan1.Init.StdFiltersNbr = 0;
	hfdcan1.Init.ExtFiltersNbr = 0;
	hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;
  if (HAL_FDCAN_Init(&hfdcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN FDCAN1_Init 2 */

  /* USER CODE END FDCAN1_Init 2 */

}
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_Pin|LCD_SCK_Pin|LCD_MOSI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_Pin LCD_SCK_Pin LCD_MOSI_Pin */
  GPIO_InitStruct.Pin = LED_Pin|LCD_SCK_Pin|LCD_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_NSS_Pin */
  GPIO_InitStruct.Pin = LCD_NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_NSS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_MISO_Pin */
  GPIO_InitStruct.Pin = LCD_MISO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LCD_MISO_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
