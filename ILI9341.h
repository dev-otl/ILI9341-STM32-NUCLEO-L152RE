#ifndef SOURCE_ST_STM32L152RE_NUCLEO_BLINKY_CUSTOMLIBRARY_ILI9341_H_
#define SOURCE_ST_STM32L152RE_NUCLEO_BLINKY_CUSTOMLIBRARY_ILI9341_H_

#include  "stm32l152xe.h"

//#include <math.h>
#define PIN_LCD_RST	//A4 => PC1
#define PIN_LCD_CS 	//A3 => PB0
#define PIN_LCD_RS 	//A2 => PA4
#define PIN_LCD_WR 	//A1 => PA1
#define PIN_LCD_RD 	//A0 => PA0
#define PIN_LCD_D0 	//D8 => PA9
#define PIN_LCD_D1	//D9 => PC7
#define PIN_LCD_D2 	//D2 => PA10
#define PIN_LCD_D3 	//D3 => PB3
#define PIN_LCD_D4	//D4 => PB5
#define PIN_LCD_D5	//D5 => PB4
#define PIN_LCD_D6	//D6 => PB10/PE8
#define PIN_LCD_D7	//D7 => PA8

#define LCD_RST_PORT GPIOC
#define LCD_RST_PIN GPIO_PIN_1
#define LCD_CS_PORT GPIOB
#define LCD_CS_PIN GPIO_PIN_0
#define LCD_RS_PORT GPIOA
#define LCD_RS_PIN GPIO_PIN_4
#define LCD_WR_PORT GPIOA
#define LCD_WR_PIN GPIO_PIN_1
#define LCD_RD_PORT GPIOA
#define LCD_RD_PIN GPIO_PIN_0

#define LCD_D0_PORT GPIOA
#define LCD_D0_PIN GPIO_PIN_9
#define LCD_D1_PORT GPIOC
#define LCD_D1_PIN GPIO_PIN_7
#define LCD_D2_PORT GPIOA
#define LCD_D2_PIN GPIO_PIN_10
#define LCD_D3_PORT GPIOB
#define LCD_D3_PIN GPIO_PIN_3
#define LCD_D4_PORT GPIOB
#define LCD_D4_PIN GPIO_PIN_5
#define LCD_D5_PORT GPIOB
#define LCD_D5_PIN GPIO_PIN_4
#define LCD_D6_PORT GPIOB
#define LCD_D6_PIN GPIO_PIN_10
#define LCD_D7_PORT GPIOA
#define LCD_D7_PIN GPIO_PIN_8

/**********************************************
 * Commands
 */
#define CASET 	0x2A
#define PASET 	0x2B
#define RAMWR 	0x2C
#define RAMRD 	0x2E
#define DISPOFF 0x28
#define DISPON 	0x29
#define WRDISBV 0x51
#define RDDISBV 0x52
#define WRCTRLD 0x53
#define RDCTRLD 0x54
#define RDDSDR 	0x0F

/************************************************/

/*************************************************
 * Colors
 */
#define WHITE       0xFFFF
#define BLACK      	0x0000
#define BLUE       	0x001F
#define BRED        0XF81F
#define GRED 		0XFFE0
#define GBLUE		0X07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 		0XBC40
#define BRRED 		0XFC07
#define GRAY  		0X8430
/*************************************************/
/*********************************/
#define Default_Delay 10000000
#define delayTime 100//Default_Delay/10000
#define LCD_Width 240 //240
#define LCD_Height 320 //320

#define MAX_FREQENCY 30000000 //3*10^6
#define MIN_PERIOD (10*10**-9) //33.333 nS
#define S *(1/MIN_PERIOD)
#define uS *(S/(10**6))
#define mS *(S/(10**3))
#define nS *(S/(10**9))

#define READ_MODE 0
#define WRITE_MODE 1

#define DELAY_EACH_PIN_SET 0



#if DELAY_EACH_PIN_SET == 1

#define LCD_CSX(x) {(x)? LCD_Pin_Set(&LCD_CS) : LCD_Pin_Reset(&LCD_CS); delay(delayTime);}
#define LCD_RESX(x) {(x)? LCD_Pin_Set(&LCD_RST) : LCD_Pin_Reset(&LCD_RST); delay(delayTime);}
#define LCD_DCX(x) {(x)? LCD_Pin_Set(&LCD_RS) : LCD_Pin_Reset(&LCD_RS); delay(delayTime);}
#define LCD_WRX(x) {(x)? LCD_Pin_Set(&LCD_WR) : LCD_Pin_Reset(&LCD_WR); delay(delayTime);}
#define LCD_RDX(x) {(x)? LCD_Pin_Set(&LCD_RD) : LCD_Pin_Reset(&LCD_RD); delay(delayTime);}
#define LCD_D(x) {LCD_Pin_Write_Data(x); delay(delayTime);}

#elif DELAY_EACH_PIN_SET == 0

#define LCD_CSX(x) {(x)? LCD_Pin_Set(&LCD_CS) : LCD_Pin_Reset(&LCD_CS);}
#define LCD_RESX(x) {(x)? LCD_Pin_Set(&LCD_RST) : LCD_Pin_Reset(&LCD_RST);}
#define LCD_DCX(x) {(x)? LCD_Pin_Set(&LCD_RS) : LCD_Pin_Reset(&LCD_RS);}
#define LCD_WRX(x) {(x)? LCD_Pin_Set(&LCD_WR) : LCD_Pin_Reset(&LCD_WR);}
#define LCD_RDX(x) {(x)? LCD_Pin_Set(&LCD_RD) : LCD_Pin_Reset(&LCD_RD);}
#define LCD_D(x) {LCD_Pin_Write_Data(x);}

#elif DELAY_EACH_PIN_SET == 2

#define LCD_CSX(x) {(x)? LCD_Pin_Set(&LCD_CS) : LCD_Pin_Reset(&LCD_CS); delay(355 uS);}
#define LCD_RESX(x) {(x)? LCD_Pin_Set(&LCD_RST) : LCD_Pin_Reset(&LCD_RST); delay(10 mS);}
#define LCD_DCX(x) {(x)? LCD_Pin_Set(&LCD_RS) : LCD_Pin_Reset(&LCD_RS); delay(0);}
#define LCD_WRX(x) {(x)? LCD_Pin_Set(&LCD_WR) : LCD_Pin_Reset(&LCD_WR); delay(15 nS);}
#define LCD_RDX(x) {(x)? LCD_Pin_Set(&LCD_RD) : LCD_Pin_Reset(&LCD_RD); delay(450 nS);}
#define LCD_D(x) {LCD_Pin_Write_Data(x); delay(10 nS);}

#endif

/************************************/

typedef struct LCD_PIN_s {
	GPIO_TypeDef *port;
	uint16_t number;
} LCD_PIN;

#define DISP_ORIENTATION  0  /* angle 0 90 */
#if  ( DISP_ORIENTATION == 90 ) || ( DISP_ORIENTATION == 270 )
	#define  MAX_X  320
	#define  MAX_Y  240
#elif  ( DISP_ORIENTATION == 0 ) || ( DISP_ORIENTATION == 180 )
#define  MAX_X  240
#define  MAX_Y  320
#endif

#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

#define RGB565CONVERT(red, green, blue)\
(uint16_t)( (( red   >> 3 ) << 11 ) | \
(( green >> 2 ) << 5  ) | \
( blue  >> 3 ))

void LCD_Set(LCD_PIN*);
void LCD_Init();
void LCD_Send_Command(uint8_t);
#define LCD_Clear(x) LCD_Clear_All_16(x)
void LCD_Clear_All_16(uint16_t color);
void LCD_Set_Window(uint16_t SC, uint16_t EC, uint16_t SP, uint16_t EP);

void LCD_Initialization(void);
//void LCD_Clear(uint16_t Color);
uint16_t LCD_GetPoint(uint16_t Xpos, uint16_t Ypos);
void LCD_SetPoint(uint16_t Xpos, uint16_t Ypos, uint16_t point);
void LCD_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
		uint16_t color);
void PutChar(uint16_t Xpos, uint16_t Ypos, uint8_t ASCI, uint16_t charColor,
		uint16_t bkColor);
void GUI_Text(uint16_t Xpos, uint16_t Ypos, uint8_t *str, uint16_t Color,
		uint16_t bkColor);

void LCD_Pin_Set(LCD_PIN *pin);
void LCD_Pin_Reset(LCD_PIN *pin);
void LCD_Send_Command(uint8_t command);
void LCD_Send_Data(uint8_t data);
void LCD_Pin_Write_Data(uint8_t hex);

#endif /* SOURCE_ST_STM32L152RE_NUCLEO_BLINKY_CUSTOMLIBRARY_ILI9341_H_ */
