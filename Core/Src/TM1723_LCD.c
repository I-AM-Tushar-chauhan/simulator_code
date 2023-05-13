/*
 * TM1723_LCD.c
 *
 *  Created on: Jun 27, 2022
 *      Author: lalitahuja
 */

#include "main.h"

#define LCD_BIGHTNESS 00
#define	c_PhaseErrCodes  7

//extern  SPI_HandleTypeDef hspi3;

//	Bit flag to enable blinking effect on segment

volatile uint8_t _blink = 0;

//	LCD Segments Local RAM Copy
lcd_seg_type LCD_Ram[16];

//	LCD 7 Segment Font table
const uint8_t LCD_7seg_font[] = {
	0b10101111,		//	0
	0b10100000,		//	1
	0b11001011,		//	2
	0b11101001,		//	3
	0b11100100,		//	4
	0b01101101,		//	5
	0b01101111,		//	6
	0b10101000,		//	7
	0b11101111,		//	8
	0b11101101,		//	9
	0b00000000,		//	10	- white space
	0b01001111,		//	11  - 'E'
	0b11001110,		//	12  - 'P'
	0b01000000,		//	13  - '-'
	0b11100011,     //  14  - 'd'
	0b01100011,     //  15  - 'o'
	0b01100010,     //  16  - 'n'
	0b01000111,     //  17  - 't'
	0b01000010,     //  18  - 'r'

};

//	Functions	//

//	Start LCD Communication (de-assert Strobe Pin)
static void TM1723_StartComm(void)
{
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin, GPIO_PIN_RESET);
	for(int i = 0 ; i < 500 ;i++);  //Delay 20 us
}

//	Start LCD Communication (assert Strobe Pin)
static void TM1723_StopComm(void)
{
	HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_Pin, GPIO_PIN_SET);
	for(int i = 0 ; i < 500 ;i++); //Delay 20 us
}

//	Transmit one byte to LCD Display
 void TM1723_Transmit(uint8_t transmit)
{
	uint8_t i=0;
	while(i<8)
	{
		//SCK PB3
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

		// MOSI PB5
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, !(transmit & (1 << i)));

		for(int i = 0 ; i < 500 ;i++);

		//SCK PB3
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
		for(int i = 0 ; i < 500 ;i++);
		i++;
	}
	// MOSI PB5
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
}

//	Receive one byte from LCD Display
static uint8_t TM1723_Receive(void)
{
	uint8_t receive=0x00;
	uint8_t i=0;
	while(i<8)
	{
		//SCK PB3
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
		for(int i = 0 ; i < 500 ;i++);
		//SCK PB3
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
		//MISO PB4
		receive |= (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)<<i);
		for(int i = 0 ; i < 500 ;i++);
		i++;
	}
	return(receive);

}

//	Initialize TM1723 Display
void TM1723_Initialize(void)
{
	uint8_t i=0;

	//	turn off all backlight
	TM1723_StartComm();
	TM1723_Transmit(0x41);	//	write to PWM command
	TM1723_StopComm();
	TM1723_StartComm();
	TM1723_Transmit(0xC0);	//	PWM0 address
	TM1723_Transmit(0x3F);	//	PWM0 data
	TM1723_Transmit(0x3F);	//	PWM1 data
	TM1723_Transmit(0x3F);	//	PWM2 data
#ifdef LCD_BIGHTNESS
	TM1723_Transmit(LCD_BIGHTNESS);	//	PWM3 data
#else
	TM1723_Transmit(0x3F);	//	PWM3 data
#endif
	TM1723_StopComm();

	//	clear the screen
	while(i<16)
	{
		LCD_Ram[i].bytes=0;
		i++;
	}
	TM1723_Update_Screen();

	// setup display
	TM1723_StartComm();
	TM1723_Transmit(0x13);	//	PWM3 active, SW0/1 active
	TM1723_StopComm();
	TM1723_StartComm();
	TM1723_Transmit(0x97);	//	display on, 1/3bias, VLCD = 5.0V
	TM1723_StopComm();

}

//	Read Switch Status (SW1, SW2)
uint8_t TM1723_Read_Switches(void)
{
	uint8_t x = 0x00;
    TM1723_StartComm();
	TM1723_Transmit(0x43);
	x = TM1723_Receive();
	TM1723_StopComm();
	return(x);
}

//	Push Data from LCD Ram Copy to LCD Display
void TM1723_Update_Screen()
{
	uint8_t i=0;
	TM1723_StartComm();
	TM1723_Transmit(0x40);	//	write Display command
	TM1723_StopComm();
	TM1723_StartComm();
	TM1723_Transmit(0xC0);	//	0x00 address
	while(i<16)
	{
		TM1723_Transmit(LCD_Ram[i].bytes);	//	data
		i++;
	}
	TM1723_StopComm();
}

//	Clear all segments on LCD Display
void TM1723_Clear_Screen(void)
{
	uint8_t i=0;
	while(i<16)
	{
		LCD_Ram[i].bytes=0;
		i++;
	}
	TM1723_Update_Screen();
}

//	Turn on All Segments in LCD Display
void TM1723_Test_Screen(void)
{
	uint8_t i=0;
	TM1723_StartComm();
	TM1723_Transmit(0x40);	//	write Display command
	TM1723_StopComm();
	TM1723_StartComm();
	TM1723_Transmit(0xC0);	//	0x00 address
	while(i<16)
	{
		TM1723_Transmit(0xff);	//	data
    	//_clrwdt();
		LCD_Ram[i].bytes=0xff;
		i++;
	}
	TM1723_StopComm();
}

//	Write a number on to 7 segment area(writes to Local Ram)
void Write_7_Segment(uint8_t digit, uint8_t pos)
{
	pos++;
	LCD_Ram[pos].bytes &= 0b00010000;
	LCD_Ram[pos].bytes |= LCD_7seg_font[digit];
}

//	Displays upto 4 digit integer number on LCD Display (writes to Local Ram)
void Display_Integer(uint16_t num, uint8_t z_pad)
{
	uint16_t temp = num;

	temp=temp%10000; // Stripping last 4 digits
	Write_7_Segment((temp/1000), 1); //sending 1st digit for display
	temp=temp%1000; // Stripping last 3 digits
	Write_7_Segment((temp/100), 2);  // sending 2nd digit for display
	temp=temp%100; // Stripping last 2 digits
	Write_7_Segment((temp/10), 3); // sending 3rd digit for display
	Write_7_Segment((temp%10), 4); // sending 4th digit for display

	if(z_pad > 0)
	{
		if((num < 1000))
			Write_7_Segment(10, 1); //padding 1st digit with white space
	}
	if(z_pad > 1)
	{
		if((num < 100))
			Write_7_Segment(10, 2); //padding 2nd digit with white space
	}
	if(z_pad > 2)
	{
		if((num < 10))
			Write_7_Segment(10, 3); //padding 3rd digit with white space
	}
}

//	Show different parameters on LCD Display
void show_data(uint16_t num,_disp_param_enum parameter)
{
	LCD_Ram[10].bytes &= 0b10000000;
	TM1723_SEG19_COM3=0;// A
	TM1723_SEG07_COM0=0;// Clock symbol
	TM1723_SEG11_COM0=0;// 3rd decimal
	TM1723_SEG09_COM0=0;// 2nd decimal
	TM1723_SEG05_COM0=0;// 1st decimal

	switch(parameter)
	{

		case _enum_Err_Code:
			Display_Integer(num,2);
			Write_7_Segment(13,2);
			if(num < c_PhaseErrCodes)
				Write_7_Segment(12,1);
			else
				Write_7_Segment(11,1);
			break;

		case _enum_voltage:
			TM1723_SEG20_COM3=1;// V
			TM1723_SEG11_COM0=1;// 3rd decimal
			Display_Integer(num,2);
			break;

		case _enum_current:
			TM1723_SEG19_COM3=1;// A
			TM1723_SEG11_COM0=1;// 3rd decimal
			Display_Integer(num,2);
			break;

		case _enum_power:
			TM1723_SEG21_COM1=1;// W
			Display_Integer(num,3);
			break;

		default:
			break;
	}
}

//	Function to enable blinking effect (call this at regular interval)
void lcd_blink(void)
{
	_blink = !_blink;
}

//	Displays Battery status in LCD Display (writes to Local Ram)
void show_batt_status(uint8_t percentage,charging_mode_enum status)
{
	uint8_t i=0;
	if(status == _enum_Charging)
		i=_blink;

	_SYM_BATT_ICON = _blink;
	LCD_Ram[ 9].bytes &= 0b11100000;

	if(status != _enum_No_BATTERY)
	{
		_SYM_BATT_ICON = 1;
		if(percentage>0)
		{
			_SYM_BATT_25P = i;
		}
		if(percentage>25)
		{
			_SYM_BATT_25P = 1;
			_SYM_BATT_50P = i;
		}
		if(percentage>50)
		{
			_SYM_BATT_50P = 1;
			_SYM_BATT_75P = i;
		}
		if(percentage>75)
		{
			_SYM_BATT_75P = 1;
			_SYM_BATT_100P = i;
		}
		if(percentage>99)
			_SYM_BATT_100P = 1;
	}
}

