/*
 * TM1723_LCD.h
 *
 *  Created on: Jun 27, 2022
 *      Author: lalitahuja
 */

#ifndef INC_TM1723_LCD_H_
#define INC_TM1723_LCD_H_

#include "main.h"


//	LCD Segment Bit Address mask
typedef struct {
	unsigned char s0com0 : 1;
	unsigned char s0com1 : 1;
	unsigned char s0com2 : 1;
	unsigned char s0com3 : 1;
	unsigned char s1com0 : 1;
	unsigned char s1com1 : 1;
	unsigned char s1com2 : 1;
	unsigned char s1com3 : 1;
} _com_bits;

// LCD Segment bit and byte access mask
typedef union {
	_com_bits bits;
	uint8_t bytes;
} lcd_seg_type;

//	LCD Battery Percentage enum
typedef enum
{	_enum_No_BATTERY=1,
	_enum_Charging,
	_enum_Not_Charging,
	_enum_Charging_mode_MAX
}charging_mode_enum;

//	LCD Data Display parameters enum
typedef enum{
	_enum_Err_Code	=0,
	_enum_voltage	,
	_enum_current	,
	_enum_power		,
	_enum_Batt_per  ,
	_enum_Time		,
	_enum_kWh		,
	_enum_Temp		,
	_enum_kW_power	,
	_enum_disp_param_max
} _disp_param_enum;

extern volatile uint8_t _blink;

//	LCD Segments Local RAM Copy
extern lcd_seg_type LCD_Ram[16];

//	LCD Data Transfer Pin Allocation

#define LCD_Strobe 	//_pa0
#define LCD_Clock 	//_pa2
#define LCD_Dinp 	//_pa7
#define LCD_Dout	//_pa3
#define LCD_TX_Delay 20

//	LCD Brightness Setting
//#define LCD_BIGHTNESS	25	//Brightness in percentage

//	LCD Individual segment address alias

#define TM1723_SEG00_COM0	LCD_Ram[ 0].bits.s0com0
#define TM1723_SEG00_COM1	LCD_Ram[ 0].bits.s0com1
#define TM1723_SEG00_COM2	LCD_Ram[ 0].bits.s0com2
#define TM1723_SEG00_COM3	LCD_Ram[ 0].bits.s0com3
#define TM1723_SEG01_COM0	LCD_Ram[ 0].bits.s1com0
#define TM1723_SEG01_COM1	LCD_Ram[ 0].bits.s1com1
#define TM1723_SEG01_COM2	LCD_Ram[ 0].bits.s1com2
#define TM1723_SEG01_COM3	LCD_Ram[ 0].bits.s1com3

#define TM1723_SEG02_COM0	LCD_Ram[ 1].bits.s0com0
#define TM1723_SEG02_COM1	LCD_Ram[ 1].bits.s0com1
#define TM1723_SEG02_COM2	LCD_Ram[ 1].bits.s0com2
#define TM1723_SEG02_COM3	LCD_Ram[ 1].bits.s0com3
#define TM1723_SEG03_COM0	LCD_Ram[ 1].bits.s1com0
#define TM1723_SEG03_COM1	LCD_Ram[ 1].bits.s1com1
#define TM1723_SEG03_COM2	LCD_Ram[ 1].bits.s1com2
#define TM1723_SEG03_COM3	LCD_Ram[ 1].bits.s1com3

#define TM1723_SEG04_COM0	LCD_Ram[ 2].bits.s0com0
#define TM1723_SEG04_COM1	LCD_Ram[ 2].bits.s0com1
#define TM1723_SEG04_COM2	LCD_Ram[ 2].bits.s0com2
#define TM1723_SEG04_COM3	LCD_Ram[ 2].bits.s0com3
#define TM1723_SEG05_COM0	LCD_Ram[ 2].bits.s1com0
#define TM1723_SEG05_COM1	LCD_Ram[ 2].bits.s1com1
#define TM1723_SEG05_COM2	LCD_Ram[ 2].bits.s1com2
#define TM1723_SEG05_COM3	LCD_Ram[ 2].bits.s1com3

#define TM1723_SEG06_COM0	LCD_Ram[ 3].bits.s0com0
#define TM1723_SEG06_COM1	LCD_Ram[ 3].bits.s0com1
#define TM1723_SEG06_COM2	LCD_Ram[ 3].bits.s0com2
#define TM1723_SEG06_COM3	LCD_Ram[ 3].bits.s0com3
#define TM1723_SEG07_COM0	LCD_Ram[ 3].bits.s1com0
#define TM1723_SEG07_COM1	LCD_Ram[ 3].bits.s1com1
#define TM1723_SEG07_COM2	LCD_Ram[ 3].bits.s1com2
#define TM1723_SEG07_COM3	LCD_Ram[ 3].bits.s1com3

#define TM1723_SEG08_COM0	LCD_Ram[ 4].bits.s0com0
#define TM1723_SEG08_COM1	LCD_Ram[ 4].bits.s0com1
#define TM1723_SEG08_COM2	LCD_Ram[ 4].bits.s0com2
#define TM1723_SEG08_COM3	LCD_Ram[ 4].bits.s0com3
#define TM1723_SEG09_COM0	LCD_Ram[ 4].bits.s1com0
#define TM1723_SEG09_COM1	LCD_Ram[ 4].bits.s1com1
#define TM1723_SEG09_COM2	LCD_Ram[ 4].bits.s1com2
#define TM1723_SEG09_COM3	LCD_Ram[ 4].bits.s1com3

#define TM1723_SEG10_COM0	LCD_Ram[ 5].bits.s0com0
#define TM1723_SEG10_COM1	LCD_Ram[ 5].bits.s0com1
#define TM1723_SEG10_COM2	LCD_Ram[ 5].bits.s0com2
#define TM1723_SEG10_COM3	LCD_Ram[ 5].bits.s0com3
#define TM1723_SEG11_COM0	LCD_Ram[ 5].bits.s1com0
#define TM1723_SEG11_COM1	LCD_Ram[ 5].bits.s1com1
#define TM1723_SEG11_COM2	LCD_Ram[ 5].bits.s1com2
#define TM1723_SEG11_COM3	LCD_Ram[ 5].bits.s1com3

#define TM1723_SEG12_COM0	LCD_Ram[ 6].bits.s0com0
#define TM1723_SEG12_COM1	LCD_Ram[ 6].bits.s0com1
#define TM1723_SEG12_COM2	LCD_Ram[ 6].bits.s0com2
#define TM1723_SEG12_COM3	LCD_Ram[ 6].bits.s0com3
#define TM1723_SEG13_COM0	LCD_Ram[ 6].bits.s1com0
#define TM1723_SEG13_COM1	LCD_Ram[ 6].bits.s1com1
#define TM1723_SEG13_COM2	LCD_Ram[ 6].bits.s1com2
#define TM1723_SEG13_COM3	LCD_Ram[ 6].bits.s1com3

#define TM1723_SEG14_COM0	LCD_Ram[ 7].bits.s0com0
#define TM1723_SEG14_COM1	LCD_Ram[ 7].bits.s0com1
#define TM1723_SEG14_COM2	LCD_Ram[ 7].bits.s0com2
#define TM1723_SEG14_COM3	LCD_Ram[ 7].bits.s0com3
#define TM1723_SEG15_COM0	LCD_Ram[ 7].bits.s1com0
#define TM1723_SEG15_COM1	LCD_Ram[ 7].bits.s1com1
#define TM1723_SEG15_COM2	LCD_Ram[ 7].bits.s1com2
#define TM1723_SEG15_COM3	LCD_Ram[ 7].bits.s1com3

#define TM1723_SEG16_COM0	LCD_Ram[ 8].bits.s0com0
#define TM1723_SEG16_COM1	LCD_Ram[ 8].bits.s0com1
#define TM1723_SEG16_COM2	LCD_Ram[ 8].bits.s0com2
#define TM1723_SEG16_COM3	LCD_Ram[ 8].bits.s0com3
#define TM1723_SEG17_COM0	LCD_Ram[ 8].bits.s1com0
#define TM1723_SEG17_COM1	LCD_Ram[ 8].bits.s1com1
#define TM1723_SEG17_COM2	LCD_Ram[ 8].bits.s1com2
#define TM1723_SEG17_COM3	LCD_Ram[ 8].bits.s1com3

#define TM1723_SEG18_COM0	LCD_Ram[ 9].bits.s0com0
#define TM1723_SEG18_COM1	LCD_Ram[ 9].bits.s0com1
#define TM1723_SEG18_COM2	LCD_Ram[ 9].bits.s0com2
#define TM1723_SEG18_COM3	LCD_Ram[ 9].bits.s0com3
#define TM1723_SEG19_COM0	LCD_Ram[ 9].bits.s1com0
#define TM1723_SEG19_COM1	LCD_Ram[ 9].bits.s1com1
#define TM1723_SEG19_COM2	LCD_Ram[ 9].bits.s1com2
#define TM1723_SEG19_COM3	LCD_Ram[ 9].bits.s1com3

#define TM1723_SEG20_COM0	LCD_Ram[10].bits.s0com0
#define TM1723_SEG20_COM1	LCD_Ram[10].bits.s0com1
#define TM1723_SEG20_COM2	LCD_Ram[10].bits.s0com2
#define TM1723_SEG20_COM3	LCD_Ram[10].bits.s0com3
#define TM1723_SEG21_COM0	LCD_Ram[10].bits.s1com0
#define TM1723_SEG21_COM1	LCD_Ram[10].bits.s1com1
#define TM1723_SEG21_COM2	LCD_Ram[10].bits.s1com2
#define TM1723_SEG21_COM3	LCD_Ram[10].bits.s1com3

#define TM1723_SEG22_COM0	LCD_Ram[11].bits.s0com0
#define TM1723_SEG22_COM1	LCD_Ram[11].bits.s0com1
#define TM1723_SEG22_COM2	LCD_Ram[11].bits.s0com2
#define TM1723_SEG22_COM3	LCD_Ram[11].bits.s0com3
#define TM1723_SEG23_COM0	LCD_Ram[11].bits.s1com0
#define TM1723_SEG23_COM1	LCD_Ram[11].bits.s1com1
#define TM1723_SEG23_COM2	LCD_Ram[11].bits.s1com2
#define TM1723_SEG23_COM3	LCD_Ram[11].bits.s1com3

#define TM1723_SEG24_COM0	LCD_Ram[12].bits.s0com0
#define TM1723_SEG24_COM1	LCD_Ram[12].bits.s0com1
#define TM1723_SEG24_COM2	LCD_Ram[12].bits.s0com2
#define TM1723_SEG24_COM3	LCD_Ram[12].bits.s0com3
#define TM1723_SEG25_COM0	LCD_Ram[12].bits.s1com0
#define TM1723_SEG25_COM1	LCD_Ram[12].bits.s1com1
#define TM1723_SEG25_COM2	LCD_Ram[12].bits.s1com2
#define TM1723_SEG25_COM3	LCD_Ram[12].bits.s1com3

#define TM1723_SEG26_COM0	LCD_Ram[13].bits.s0com0
#define TM1723_SEG26_COM1	LCD_Ram[13].bits.s0com1
#define TM1723_SEG26_COM2	LCD_Ram[13].bits.s0com2
#define TM1723_SEG26_COM3	LCD_Ram[13].bits.s0com3
#define TM1723_SEG27_COM0	LCD_Ram[13].bits.s1com0
#define TM1723_SEG27_COM1	LCD_Ram[13].bits.s1com1
#define TM1723_SEG27_COM2	LCD_Ram[13].bits.s1com2
#define TM1723_SEG27_COM3	LCD_Ram[13].bits.s1com3

#define TM1723_SEG28_COM0	LCD_Ram[14].bits.s0com0
#define TM1723_SEG28_COM1	LCD_Ram[14].bits.s0com1
#define TM1723_SEG28_COM2	LCD_Ram[14].bits.s0com2
#define TM1723_SEG28_COM3	LCD_Ram[14].bits.s0com3
#define TM1723_SEG29_COM0	LCD_Ram[14].bits.s1com0
#define TM1723_SEG29_COM1	LCD_Ram[14].bits.s1com1
#define TM1723_SEG29_COM2	LCD_Ram[14].bits.s1com2
#define TM1723_SEG29_COM3	LCD_Ram[14].bits.s1com3

#define TM1723_SEG30_COM0	LCD_Ram[15].bits.s0com0
#define TM1723_SEG30_COM1	LCD_Ram[15].bits.s0com1
#define TM1723_SEG30_COM2	LCD_Ram[15].bits.s0com2
#define TM1723_SEG30_COM3	LCD_Ram[15].bits.s0com3
#define TM1723_SEG31_COM0	LCD_Ram[15].bits.s1com0
#define TM1723_SEG31_COM1	LCD_Ram[15].bits.s1com1
#define TM1723_SEG31_COM2	LCD_Ram[15].bits.s1com2
#define TM1723_SEG31_COM3	LCD_Ram[15].bits.s1com3

//	LCD Battery Percentage ICON Segment Alias

#define _SYM_BATT_ICON		TM1723_SEG19_COM0
#define _SYM_BATT_25P		TM1723_SEG18_COM3
#define _SYM_BATT_50P		TM1723_SEG18_COM2
#define _SYM_BATT_75P		TM1723_SEG18_COM1
#define _SYM_BATT_100P		TM1723_SEG18_COM0

//	Assorted Symbols Segment Alias

#define _SYM_AC_PLUG		TM1723_SEG22_COM0
#define _SYM_REV_BATTERY	TM1723_SEG22_COM1
#define _SYM_ERROR_			TM1723_SEG22_COM2
#define _SYM_TEMPERATURE	TM1723_SEG22_COM3
#define _SYM_COMMUNICATION	TM1723_SEG21_COM3
#define _TXT_INPUT_			TM1723_SEG19_COM2
#define _TXT_OUTPUT			TM1723_SEG19_COM1

//	Functions	//
void TM1723_Transmit(uint8_t transmit);

//	Initialize TM1723 Display
void TM1723_Initialize(void);

//	Set Backlight color and intensity for RGB Backlight (PWM0, PWM1, PWM2)
void TM1723_Set_BL_Color(uint8_t red, uint8_t green, uint8_t blue);

//	Set Backlight intensity (PWM4)
void TM1723_Set_Backlight(uint8_t percent);

//	Read Switch Status (SW1, SW2)
uint8_t TM1723_Read_Switches(void);

	//	Push Data from LCD Ram Copy to LCD Display
void TM1723_Update_Screen();

	//	Clear all segments on LCD Display
void TM1723_Clear_Screen(void);

	//	Turn on All Segments in LCD Display
void TM1723_Test_Screen(void);

	//	Write a number on to 7 segment area(writes to Local Ram)
void Write_7_Segment(uint8_t digit, uint8_t pos);

	//	Displays upto 4 digit integer number on LCD Display (writes to Local Ram)
void Display_Integer(uint16_t temp, uint8_t z_pad);

	//	Show different parameters on LCD Display
void show_data(uint16_t num,_disp_param_enum parameter);

	//	Function to enable blinking effect (call this at regular interval)
 void lcd_blink(void);

	//	Displays Battery status in LCD Display (writes to Local Ram)
void show_batt_status(uint8_t percentage,charging_mode_enum status);

	//	Displays AC plug Segment on LCD Display (writes to Local Ram)
#define show_ac_plug_Symbol()			(_SYM_AC_PLUG = 1)
#define blink_ac_plug_Symbol()			(_SYM_AC_PLUG = _blink)
#define hide_ac_plug_Symbol()			(_SYM_AC_PLUG = 0)
//
//	//	Displays Reverse Battery Segment on LCD Display (writes to Local Ram)
#define show_batt_rev_Symbol()  		(_SYM_REV_BATTERY = 1)
#define blink_batt_rev_Symbol()  		(_SYM_REV_BATTERY = _blink)
#define hide_batt_rev_Symbol()			(_SYM_REV_BATTERY = 0)
//
//	//	Displays ERROR Segment on LCD Display (writes to Local Ram)
#define show_error_Symbol()				(_SYM_ERROR_ = 1)
#define blink_error_Symbol()			(_SYM_ERROR_ = _blink)
#define hide_error_Symbol()				(_SYM_ERROR_ = 0)
//
//	//	Displays System Temperature Segment on LCD Display (writes to Local Ram)
#define show_sys_Temp_Symbol()			(_SYM_TEMPERATURE = 1)
#define blink_sys_Temp_Symbol()			(_SYM_TEMPERATURE = _blink)
#define hide_sys_Temp_Symbol()			(_SYM_TEMPERATURE = 0)
//
//	//	Displays Communication Segment on LCD Display (writes to Local Ram)
#define show_Communication_Symbol()		(_SYM_COMMUNICATION = 1)
#define blink_Communication_Symbol()	(_SYM_COMMUNICATION = _blink)
#define hide_Communication_Symbol()		(_SYM_COMMUNICATION = 0)
//
//	//	Displays TXT INPUT Segment on LCD Display (writes to Local Ram)
#define show_TXT_INPUT_Symbol()			(_TXT_INPUT_ = 1)
#define blink_TXT_INPUT_Symbol()		(_TXT_INPUT_ = _blink)
#define hide_TXT_INPUT_Symbol()			(_TXT_INPUT_ = 0)
//
//	//	Displays TXT INPUT Segment on LCD Display (writes to Local Ram)
#define show_TXT_OUTPUT_Symbol()		(_TXT_OUTPUT = 1)
#define blink_TXT_OUTPUT_Symbol()		(_TXT_OUTPUT = _blink)
#define hide_TXT_OUTPUT_Symbol()		(_TXT_OUTPUT = 0)


#endif /* INC_TM1723_LCD_H_ */
