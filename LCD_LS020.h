//Library has been modified for STM32F0xx by Aleksey Sedyshev
//https://github.com/AlekseySedyshev

#ifndef LCD_LS020_h
#define LCD_LS020_h

#include "stm32f0xx.h"  

#define SPI1_DR_8bit 			*((__IO uint8_t *)&SPI1->DR)		// Limit for spi bus 8 bit

#define   HI				1
#define   LO				0

#define   CMD_()					GPIOA->BSRR 	|=1<<3			//A0->0
#define   DAT_()					GPIOA->BRR |=1<<3		//A0->1

#define   RES_ON()			GPIOA->BRR |=1<<2		//RES->0
#define   RES_OFF()			GPIOA->BSRR |=1<<2		//RES->1

#define   CS_HI()				GPIOA->BSRR |=1<<4	
#define   CS_LO()				GPIOA->BRR |=1<<4

#define LS020_WIDTH 176
#define LS020_HEIGHT 132




// Colors   16 bits	: xxxx x xxx xxx x xxxx 
// RED/ GREEN/ BLUE	:	RRRR R ggg ggg B BBBB		

// Red max value = 0xFF<<3 = 0xF8							- 5 bit color, (1f)
// Green Max value = (0xff << 1) &0x7F = 0x7E - 6 bit color, (3f)
// Blue max Value = 0xff>>3 = 0x1F 						- 5 bit color. (1f)

//===============================================================
//                    Color defines
//===============================================================
#define BLACK 0x0000       ///<   0,   0,   0
#define WHITE 0xFFFF       ///< 255, 255, 255
#define RED 0xF800         ///< 255,   0,   0
#define GREEN 0x07E0       ///<   0, 255,   0
#define BLUE 0x001F        ///<   0,   0, 255
#define YELLOW 0xFFE0      ///< 255, 255,   0
#define CYAN 0x07FF        ///<   0, 255, 255
#define MAGENTA 0xF81F     ///< 255,   0, 255

#define MAROON 0x7800      ///< 123,   0,   0
#define DARKGREEN 0x03E0   ///<   0, 125,   0
#define NAVY 0x000F        ///<   0,   0, 123
#define OLIVE 0x7BE0       ///< 123, 125,   0
#define DARKCYAN 0x03EF    ///<   0, 125, 123
#define PURPLE 0x780F      ///< 123,   0, 123

#define LIGHTGREY 0xC618   ///< 198, 195, 198
#define DARKGREY 0x7BEF    ///< 123, 125, 123

#define ORANGE 0xFD20      ///< 255, 165,   0
#define GREENYELLOW 0xAFE5 ///< 173, 255,  41
#define PINK 0xFC18        ///< 255, 130, 198

typedef enum {
true	=				1,
false	=				0
} bool;

typedef enum {
CMD	=				1,
DAT	=				0
} cmd_data_sv;

unsigned int setcolor(unsigned char cRed,unsigned char cGreen, unsigned char cBlue);
void LCD_Init(void);
void SPI_Wr(cmd_data_sv data,unsigned char value);

void setRotation(unsigned char rot);
void invertDisplay(const bool invert);

void LCD_FillScreen (unsigned int color);
void LCD_DrawLine (unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned int color);
void LCD_DrawRect (unsigned char x1,unsigned char y1,unsigned char width,unsigned char height,unsigned char size,unsigned int color);
void LCD_FillRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h,unsigned int color);
void LCD_DrawCircle (unsigned char xcenter, unsigned char ycenter, unsigned char rad, unsigned int color);
void LCD_FillCircle (unsigned char xcenter, unsigned char ycenter, unsigned char rad, unsigned int color);
void LCD_DrawTriangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char x3,unsigned char y3,unsigned int color);
void LCD_FillTriangle(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char x3,unsigned char y3,unsigned int color);
void LCD_PrintDec(long val,int x, int y,unsigned  int t_color,unsigned int b_color,unsigned char zoom_width,unsigned char zoom_height, int rot);
void LCD_PrintHex(long val,int x, int y,unsigned  int t_color,unsigned int b_color,unsigned char zoom_width,unsigned char zoom_height, int rot);
void LCD_PrintBin(unsigned char value,int x, int y,unsigned  int t_color,unsigned int b_color,unsigned char zoom_width,unsigned char zoom_height, int rot);

void Send_Symbol (unsigned char symbol,unsigned char x,unsigned char y,unsigned int t_color,unsigned int b_color,unsigned char zoom_width,unsigned char zoom_height, int rot);
void LCD_Putchar(char symbol,unsigned char x,unsigned char y,unsigned int t_color,unsigned int b_color,unsigned char zoom_width,unsigned char zoom_height, int rot);
void LCD_Puts(char *str,unsigned char x,unsigned char y,unsigned  int t_color,unsigned int b_color,unsigned char zoom_width,unsigned char zoom_height, int rot);
void Send_Symbol_Shadow (unsigned char symbol,unsigned char x,unsigned char y,unsigned int t_color,unsigned char zoom_width,unsigned char zoom_height, int rot);
void LCD_Putchar_Shadow (char symbol,unsigned char x,unsigned char y,unsigned int t_color,unsigned char zoom_width,unsigned char zoom_height, int rot);
void LCD_Puts_Shadow(char *str, unsigned char x, unsigned char y,unsigned  int t_color,unsigned char zoom_width,unsigned char zoom_height, int rot);


#endif
