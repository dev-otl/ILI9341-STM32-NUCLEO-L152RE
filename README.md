# ILI9341-STM32-NUCLEO-L152RE
Minimal library/driver for TFT LCD Display Shield with an ILI9341 controller. Developed on STM32 Nucleo-64 development board (STM32L152RE MCU) using STM32CubeIDE.

## Device list
[STM32 Nucleo-64 development board with STM32L152RE MCU](https://www.st.com/en/evaluation-tools/nucleo-l152re.html)   
[2.4 Inch TFT LCD Touch Display Shield](https://www.az-delivery.de/en/products/2-4-tft-lcd-touch-display)  
[ILI9341 Datasheet](https://cdn-shop.adafruit.com/datasheets/ILI9341.pdf)
## Files
### `ILI9341.h`:
Header file with pin configuration and function declarations.
Needs to be included.
```C
#ifndef ILI9341_H
    #define ILI9341_H
    #include "ILI9341.h"
#endif
```

### `ILI9341.c`:
Source file with implementation of header functions.

### `AsciiLib.* and HzLib.*`:
Helper files that provide character pixel data (not mine).  
Each character is represented by [16 rows] x [8 columns] bit matrix stored as an array of 16 2-byte values. Bit 1 turns pixel to the color.     
Modify the pixel data as desired.

### Functions
|                                                        |                                                                         |
| ------------------------------------------------------ | ----------------------------------------------------------------------- |
| Basic Functions:                                       |                                                                         |
| **`LCD_Init()`**                                       | Initializes the LCD. Should be called before any other LCD functions.   |
| **`LCD_Send_Command(command)`**                        | Send LCD Command (see ILI9341 datasheet)                                |
| **`LCD_Send_Data(data)`**                              | Send LCD Data (see ILI9341 datasheet)                                   |
| Helper Functions:                                      |                                                                         |
| `PutChar(x, y, character, textColor, backgroundColor)` | writes character with specified colors at position(x,y)                 |
| `GUI_Text(x, y, line, color, background)`              | writes the line with specified colors at position (x,y) with wraparound |
| `LCD_SetPoint(x, y, color)`                            | sets pixel at position (x,y) to the specified color                     |

### Tips
+ After the LCD initialization it is recommended to follow Memory Write flowchart (ILI9341 datasheet page 114)
+ The two functions `LCD_Send_Command` and `LCD_Send_Data`  should be enough to implement your own opimized display write functions.
+ Use macros `LCD_<ILI9341_control_pin>(bit)` to set individual ILI9341 control pins to specified bit. Pins are `CSX, RESX, DCX, WRX, RDX`. 
+ To set the data pins use macro `LCD_D(x)` which sets all D<7:0> pins to the bits of x<7:0>. 
+ If you modify pin connection, modify the `LCD_<LCD_pin>` declaration in header file and the appropriate pin numbers in Set_Write_Mode*() functions in the source file.
