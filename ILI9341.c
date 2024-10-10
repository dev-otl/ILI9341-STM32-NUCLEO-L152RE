#ifndef ILI9341_H
#define ILI9341_H
#include "ILI9341.h"
#endif

#ifndef ASCIILIB_H
#define ASCIILIB_H
#include "AsciiLib.h"
#endif

#ifndef HAZLIB_H
#define HAZLIB_H
#include "Hzlib.h"
#endif

#include "stm32l1xx_hal.h"
// static uint8_t LCD_Code;
#define ADD_DELAY 0
#define LCD_SetCursor(x, y) LCD_Set_Window(x, 249, y, 319)
#define LCD_Send_16(A) LCD_Send_Pixel(A)

uint8_t RW_Mode;

LCD_PIN LCD_RST = {LCD_RST_PORT, LCD_RST_PIN};
LCD_PIN LCD_CS = {LCD_CS_PORT, LCD_CS_PIN};
LCD_PIN LCD_RS = {LCD_RS_PORT, LCD_RS_PIN};
LCD_PIN LCD_WR = {LCD_WR_PORT, LCD_WR_PIN};
LCD_PIN LCD_RD = {LCD_RD_PORT, LCD_RD_PIN};
LCD_PIN LCD_D0 = {LCD_D0_PORT, LCD_D0_PIN};
LCD_PIN LCD_D1 = {LCD_D1_PORT, LCD_D1_PIN};
LCD_PIN LCD_D2 = {LCD_D2_PORT, LCD_D2_PIN};
LCD_PIN LCD_D3 = {LCD_D3_PORT, LCD_D3_PIN};
LCD_PIN LCD_D4 = {LCD_D4_PORT, LCD_D4_PIN};
LCD_PIN LCD_D5 = {LCD_D5_PORT, LCD_D5_PIN};
LCD_PIN LCD_D6 = {LCD_D6_PORT, LCD_D6_PIN};
LCD_PIN LCD_D7 = {LCD_D7_PORT, LCD_D7_PIN};

LCD_PIN *LCD_D[] = {&LCD_D0, &LCD_D1, &LCD_D2, &LCD_D3, &LCD_D4, &LCD_D5,
					&LCD_D6, &LCD_D7};

static void delay(int i)
{
	while (i--)
		;
}

void LCD_Delay(int i)
{
	while (i--)
		;
}
void LCD_Set_Write_Mode_All()
{
	GPIO_InitTypeDef GPIO_Init;
	GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init.Pull = GPIO_NOPULL;
	GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	GPIO_Init.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
	HAL_GPIO_Init(GPIOA, &GPIO_Init);

	GPIO_Init.Pin = GPIO_PIN_0 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_10;
	HAL_GPIO_Init(GPIOB, &GPIO_Init);

	GPIO_Init.Pin = GPIO_PIN_1 | GPIO_PIN_7;
	HAL_GPIO_Init(GPIOC, &GPIO_Init);

	RW_Mode = WRITE_MODE;
	delay(5000);
}

void LCD_Set_Write_Mode()
{
	if (RW_Mode != WRITE_MODE)
	{
		GPIO_InitTypeDef GPIO_Init;
		GPIO_Init.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_Init.Pull = GPIO_NOPULL;
		GPIO_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

		GPIO_Init.Pin = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_8;
		HAL_GPIO_Init(GPIOA, &GPIO_Init);

		GPIO_Init.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_10;
		HAL_GPIO_Init(GPIOB, &GPIO_Init);

		GPIO_Init.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOC, &GPIO_Init);

		RW_Mode = WRITE_MODE;
		delay(5000);
	}
}

void LCD_Set_Read_Mode()
{
	if (RW_Mode != READ_MODE)
	{
		GPIO_InitTypeDef GPIO_Init;
		GPIO_Init.Mode = GPIO_MODE_INPUT;
		GPIO_Init.Pull = GPIO_NOPULL;

		GPIO_Init.Pin = GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_8;
		HAL_GPIO_Init(GPIOA, &GPIO_Init);

		GPIO_Init.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_10;
		HAL_GPIO_Init(GPIOB, &GPIO_Init);

		GPIO_Init.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOC, &GPIO_Init);

		RW_Mode = READ_MODE;
	}
}

void LCD_Pin_Set(LCD_PIN *pin)
{
	HAL_GPIO_WritePin(pin->port, pin->number, GPIO_PIN_SET);
}
void LCD_Pin_Reset(LCD_PIN *pin)
{
	HAL_GPIO_WritePin(pin->port, pin->number, GPIO_PIN_RESET);
}
#define LCD_Pin_Write(pin, value) HAL_GPIO_WritePin(pin->port, pin->number, value)

void LCD_Pin_Write_Data(uint8_t hex)
{
	/*
	 for (int i = 0; i <= 7; ++i) {
	 LCD_Pin_Write(LCD_D[i], (hex >> i) & 1);
	 }
	 */

	HAL_GPIO_WritePin(LCD_D0_PORT, LCD_D0_PIN, (hex >> 0) & 1);
	HAL_GPIO_WritePin(LCD_D1_PORT, LCD_D1_PIN, (hex >> 1) & 1);
	HAL_GPIO_WritePin(LCD_D2_PORT, LCD_D2_PIN, (hex >> 2) & 1);
	HAL_GPIO_WritePin(LCD_D3_PORT, LCD_D3_PIN, (hex >> 3) & 1);
	HAL_GPIO_WritePin(LCD_D4_PORT, LCD_D4_PIN, (hex >> 4) & 1);
	HAL_GPIO_WritePin(LCD_D5_PORT, LCD_D5_PIN, (hex >> 5) & 1);
	HAL_GPIO_WritePin(LCD_D6_PORT, LCD_D6_PIN, (hex >> 6) & 1);
	HAL_GPIO_WritePin(LCD_D7_PORT, LCD_D7_PIN, (hex >> 7) & 1);

	/*
	 * PA9,PC7,PA10,PB3,PB5,PB4,PB10,PA8
	 * 1   2   3    4   5   6   7    8
	 */
	// HAL_GPIO_WritePin(LCD_D0_PORT, LCD_D0_PIN, (hex >> 0) & 1);
	/*
	 GPIOA->ODR = ((hex & 0b00000001) << 9) | ((hex & 0b10000000) << 1);
	 GPIOB->ODR = (hex & 0b00001000) | ((hex & 0b00010000) << 1)
	 | ((hex & 0b00100000) >> 1) | ((hex & 0b00010000) << 1)
	 | ((hex & 0b01000000) << 4);
	 GPIOC->ODR = ((hex & 0b00000010) << 6);
	 */
}

void LCD_Send_Command(uint8_t command)
{
	if (RW_Mode != WRITE_MODE)
		LCD_Set_Write_Mode();
	LCD_DCX(0);
	LCD_D(command);
	LCD_WRX(0);
	// delay(100);
	LCD_WRX(1);
}

void LCD_Send_Data(uint8_t data)
{
	if (RW_Mode != WRITE_MODE)
		LCD_Set_Write_Mode();
	LCD_DCX(1);
	LCD_D(data);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);
}

void LCD_Receive_Data(uint8_t nParam)
{
	if (RW_Mode != READ_MODE)
		LCD_Set_Read_Mode();
	LCD_DCX(1);
	for (int i = 1; i <= nParam; ++i)
	{
		LCD_RDX(0);
		LCD_RDX(1);
	}
}

void LCD_Send_Read_Command(uint8_t command, uint8_t nParam)
{
	LCD_Send_Command(command);
	LCD_Receive_Data(nParam);
}

void LCD_Reset(void)
{
	LCD_RESX(0);
	LCD_RESX(1);
	LCD_RESX(0);
	LCD_RESX(1);
	delay(10000);
}

void LCD_Preset(void)
{
	LCD_CSX(0); // chip select enable
	LCD_DCX(1); // data mode
	LCD_WRX(1); // write disable
	LCD_RDX(1); // read disable
	for (int i = 0; i < 8; ++i)
	{
		LCD_D(0x01 << i); // write led
	}
	LCD_Reset();
	LCD_D(0x00);
	LCD_D(0xFF);
	LCD_D(0x00);
	LCD_D(0xFF);
	LCD_D(0x00);
	// if (ADD_DELAY)
	delay(10000);
}

void LCD_Set_Window(uint16_t SC, uint16_t EC, uint16_t SP, uint16_t EP)
{
	if (RW_Mode != WRITE_MODE)
		LCD_Set_Write_Mode();

	LCD_DCX(0);
	LCD_D(CASET);
	LCD_WRX(0);
	// delay(100);
	LCD_WRX(1);
	LCD_DCX(1);
	LCD_D(SC >> 8);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);
	LCD_D(0x00FF & SC);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);
	LCD_D(EC >> 8);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);
	LCD_D(0x00FF & EC);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);

	LCD_DCX(0);
	LCD_D(PASET);
	LCD_WRX(0);
	// delay(100);
	LCD_WRX(1);
	LCD_DCX(1);
	LCD_D(SP >> 8);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);
	LCD_D(0x00FF & SP);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);
	LCD_D(EP >> 8);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);
	LCD_D(0x00FF & EP);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);
}

void LCD_Send_Pixel(uint16_t color)
{
	uint8_t msb = color >> 8;
	uint8_t lsb = color & 0xFF;

	LCD_DCX(1);

	LCD_D(msb);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);

	LCD_D(lsb);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);
}

void LCD_Read_All()
{
	// LCD_Set_Window(0, LCD_Width - 1, 0, LCD_Height - 1);
	LCD_Send_Command(RAMRD);
	for (int i = 0; i < LCD_Width * LCD_Height; ++i)
	{
		LCD_Receive_Data(1 + 3);
	}
}

#define LCD_WR_REG LCD_Send_Command
#define LCD_WR_DATA LCD_Send_Data

void LCD_Clear_All_16(uint16_t color)
{
	// LCD_Send_Command(DISPOFF);
	LCD_Set_Window(0, LCD_Width - 1, 0, LCD_Height - 1);
	LCD_Send_Command(RAMWR);

	uint8_t msb = color >> 8;
	uint8_t lsb = color & 0xFF;

	LCD_DCX(1);

	if (msb != lsb)
		for (int i = 0; i < LCD_Width * LCD_Height; ++i)
		{
			LCD_D(msb);
			LCD_WRX(0);
			// delay(1000);
			LCD_WRX(1);

			LCD_D(lsb);
			LCD_WRX(0);
			// delay(1000);
			LCD_WRX(1);
		}
	else if (msb == lsb)
		for (int i = 0; i < LCD_Width * LCD_Height; ++i)
		{
			LCD_D(msb);
			LCD_WRX(0);
			// delay(1000);
			LCD_WRX(1);

			// LCD_D(lsb);
			LCD_WRX(0);
			// delay(1000);
			LCD_WRX(1);
		}
	else
		;
	// LCD_Send_Command(DISPON);
}

void init_test()
{

	LCD_WR_REG(0xCF); // power control B
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xD9); // 0xC1
	LCD_WR_DATA(0X30);

	//	LCD_WR_REG(0xED);
	//	LCD_WR_DATA(0x64);
	//	LCD_WR_DATA(0x03);
	//	LCD_WR_DATA(0X12);
	//	LCD_WR_DATA(0X81);

	//	LCD_WR_REG(0xE8); //Driver timing control A
	//	LCD_WR_DATA(0x85);
	//	LCD_WR_DATA(0x10);
	//	LCD_WR_DATA(0x7A);

	//	LCD_WR_REG(0xCB); //power control A
	//	LCD_WR_DATA(0x39);
	//	LCD_WR_DATA(0x2C);
	//	LCD_WR_DATA(0x00);
	//	LCD_WR_DATA(0x34);
	//	LCD_WR_DATA(0x02);

	LCD_WR_REG(0xF7);  // pump ratio control
	LCD_WR_DATA(0x20); // Display Inversion off

	//	LCD_WR_REG(0xEA); //Driver Timing Control B
	//	LCD_WR_DATA(0x00);
	//	LCD_WR_DATA(0x00);

	//	LCD_WR_REG(0xC0);    //Power control 1
	//	LCD_WR_DATA(0x1B);   //VRH[5:0]

	//	LCD_WR_REG(0xC1);    //Power control 2
	//	LCD_WR_DATA(0x12);   //SAP[2:0];BT[3:0] 0x01

	//	LCD_WR_REG(0xC5);    //VCOM control 1
	//	LCD_WR_DATA(0x08); 	 //30
	//	LCD_WR_DATA(0x26); 	 //30

	//	LCD_WR_REG(0xC7);    //VCM control2
	//	LCD_WR_DATA(0XB7);

	LCD_WR_REG(0x36); // Memory Access Control
	LCD_WR_DATA(0x08);

	LCD_WR_REG(0x3A); // color mode: pixel format set
	LCD_WR_DATA(0x55);

	//	LCD_WR_REG(0xB1); //frame rate control
	//	LCD_WR_DATA(0x00);
	//	LCD_WR_DATA(0x1A);

	LCD_WR_REG(0xB6); // Display Function Control
	LCD_WR_DATA(0x0A);
	LCD_WR_DATA(0xA2); // mirror mode

	//	LCD_WR_REG(0xF2);    // 3Gamma Function Disable
	//	LCD_WR_DATA(0x00);

	//	LCD_WR_REG(0x26);    //Gamma curve selected
	//	LCD_WR_DATA(0x01);

	//	LCD_WR_REG(0xE0);    //Set Gamma positive
	//	LCD_WR_DATA(0x0F);
	//	LCD_WR_DATA(0x1D);
	//	LCD_WR_DATA(0x1A);
	//	LCD_WR_DATA(0x0A);
	//	LCD_WR_DATA(0x0D);
	//	LCD_WR_DATA(0x07);
	//	LCD_WR_DATA(0x49);
	//	LCD_WR_DATA(0X66);
	//	LCD_WR_DATA(0x3B);
	//	LCD_WR_DATA(0x07);
	//	LCD_WR_DATA(0x11);
	//	LCD_WR_DATA(0x01);
	//	LCD_WR_DATA(0x09);
	//	LCD_WR_DATA(0x05);
	//	LCD_WR_DATA(0x04);

	//	LCD_WR_REG(0XE1);    //Set Gamma negative
	//	LCD_WR_DATA(0x00);
	//	LCD_WR_DATA(0x18);
	//	LCD_WR_DATA(0x1D);
	//	LCD_WR_DATA(0x02);
	//	LCD_WR_DATA(0x0F);
	//	LCD_WR_DATA(0x04);
	//	LCD_WR_DATA(0x36);
	//	LCD_WR_DATA(0x13);
	//	LCD_WR_DATA(0x4C);
	//	LCD_WR_DATA(0x07);
	//	LCD_WR_DATA(0x13);
	//	LCD_WR_DATA(0x0F);
	//	LCD_WR_DATA(0x2E);
	//	LCD_WR_DATA(0x2F);
	//	LCD_WR_DATA(0x05);

	//	LCD_WR_REG(0x2B);
	//	LCD_WR_DATA(0x00);
	//	LCD_WR_DATA(0x00);
	//	LCD_WR_DATA(0x01);
	//	LCD_WR_DATA(0x3f);
	//
	//	LCD_WR_REG(0x2A);
	//	LCD_WR_DATA(0x00);
	//	LCD_WR_DATA(0x00);
	//	LCD_WR_DATA(0x00);
	//	LCD_WR_DATA(0xef);

	LCD_WR_REG(0x11); // Exit Sleep
	delay(100000);

	LCD_WR_REG(0x29); // display on

	// LCD_Clear_All_16(BLUE);
	// GUI_Text(10, 10, (uint8_t*) "EOSs @ PoliTO 2022-23", WHITE, BLUE);
	// GUI_Text(10, 30, (uint8_t*) "Powered by Micrium-C OS", WHITE, BLUE);
	// GUI_Text(10, 30, (uint8_t*) "Ready", WHITE, BLUE);
}
void LCD_Init(void)
{
	/* Configure the LCD Control pins */
	__GPIOA_CLK_ENABLE();
	__GPIOB_CLK_ENABLE();
	__GPIOC_CLK_ENABLE();

	LCD_Set_Write_Mode_All();
	LCD_Preset();

	init_test();

	// registers 1521
	// booster on
	// row order
	// column order
	// sleep out mode :see flowchart
	// display on see powwer on sequence 219
}

void LCD_SetPoint(uint16_t Xpos, uint16_t Ypos, uint16_t point)
{
	if (Xpos >= MAX_X || Ypos >= MAX_Y)
	{
		return;
	}
	LCD_Set_Window(Xpos, Xpos, Ypos, Ypos);
	// LCD_WriteReg(0x0022, point);
	LCD_DCX(0);
	LCD_D(RAMWR);
	LCD_WRX(0);
	// delay(100);
	LCD_WRX(1);
	LCD_DCX(1);
	LCD_D(point >> 8);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);
	LCD_D(point & 0xFF);
	LCD_WRX(0);
	// delay(1000);
	LCD_WRX(1);
}

void PutChar(uint16_t Xpos, uint16_t Ypos, uint8_t ASCI, uint16_t charColor,
			 uint16_t bkColor)
{
	// LCD_Send_Command(DISPOFF);
	uint16_t i, j;
	uint8_t buffer[16], tmp_char;
	GetASCIICode(buffer, ASCI); /* È¡×ÖÄ£Êý¾Ý */
	for (i = 0; i < 16; i++)
	{
		tmp_char = buffer[i];
		for (j = 0; j < 8; j++)
		{
			if (((tmp_char >> (7 - j)) & 0x01) == 0x01)
			{
				LCD_SetPoint(Xpos + j, Ypos + i, charColor); /* ×Ö·ûÑÕÉ« */
			}
			else
			{
				LCD_SetPoint(Xpos + j, Ypos + i, bkColor); /* ±³¾°ÑÕÉ« */
			}
		}
	}
	// LCD_Send_Command(DISPON);
}

void GUI_Text(uint16_t Xpos, uint16_t Ypos, uint8_t *str, uint16_t Color,
			  uint16_t bkColor)
{
	// LCD_Send_Command(DISPOFF);
	uint8_t TempChar;
	do
	{
		TempChar = *str++;
		PutChar(Xpos, Ypos, TempChar, Color, bkColor);
		if (Xpos < MAX_X - 8)
		{
			Xpos += 8;
		}
		else if (Ypos < MAX_Y - 16)
		{
			Xpos = 0;
			Ypos += 16;
		}
		else
		{
			Xpos = 0;
			Ypos = 0;
		}
	} while (*str != 0);
	// LCD_Send_Command(DISPON);
}
void LCD_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
				  uint16_t color)
{
	short dx, dy; /* ¶¨ÒåX YÖáÉÏÔö¼ÓµÄ±äÁ¿Öµ */
	short temp;	  /* Æðµã ÖÕµã´óÐ¡±È½Ï ½»»»Êý¾ÝÊ±µÄÖÐ¼ä±äÁ¿ */

	if (x0 > x1) /* XÖáÉÏÆðµã´óÓÚÖÕµã ½»»»Êý¾Ý */
	{
		temp = x1;
		x1 = x0;
		x0 = temp;
	}
	if (y0 > y1) /* YÖáÉÏÆðµã´óÓÚÖÕµã ½»»»Êý¾Ý */
	{
		temp = y1;
		y1 = y0;
		y0 = temp;
	}

	dx = x1 - x0; /* XÖá·½ÏòÉÏµÄÔöÁ¿ */
	dy = y1 - y0; /* YÖá·½ÏòÉÏµÄÔöÁ¿ */

	if (dx == 0) /* XÖáÉÏÃ»ÓÐÔöÁ¿ »­´¹Ö±Ïß */
	{
		do
		{
			LCD_SetPoint(x0, y0, color); /* ÖðµãÏÔÊ¾ Ãè´¹Ö±Ïß */
			y0++;
		} while (y1 >= y0);
		return;
	}
	if (dy == 0) /* YÖáÉÏÃ»ÓÐÔöÁ¿ »­Ë®Æ½Ö±Ïß */
	{
		do
		{
			LCD_SetPoint(x0, y0, color); /* ÖðµãÏÔÊ¾ ÃèË®Æ½Ïß */
			x0++;
		} while (x1 >= x0);
		return;
	}
	/* ²¼À¼É­ººÄ·(Bresenham)Ëã·¨»­Ïß */
	if (dx > dy) /* ¿¿½üXÖá */
	{
		temp = 2 * dy - dx; /* ¼ÆËãÏÂ¸öµãµÄÎ»ÖÃ */
		while (x0 != x1)
		{
			LCD_SetPoint(x0, y0, color); /* »­Æðµã */
			x0++;						 /* XÖáÉÏ¼Ó1 */
			if (temp > 0)				 /* ÅÐ¶ÏÏÂÏÂ¸öµãµÄÎ»ÖÃ */
			{
				y0++; /* ÎªÓÒÉÏÏàÁÚµã£¬¼´£¨x0+1,y0+1£© */
				temp += 2 * dy - 2 * dx;
			}
			else
			{
				temp += 2 * dy; /* ÅÐ¶ÏÏÂÏÂ¸öµãµÄÎ»ÖÃ */
			}
		}
		LCD_SetPoint(x0, y0, color);
	}
	else
	{
		temp = 2 * dx - dy; /* ¿¿½üYÖá */
		while (y0 != y1)
		{
			LCD_SetPoint(x0, y0, color);
			y0++;
			if (temp > 0)
			{
				x0++;
				temp += 2 * dy - 2 * dx;
			}
			else
			{
				temp += 2 * dy;
			}
		}
		LCD_SetPoint(x0, y0, color);
	}
}
