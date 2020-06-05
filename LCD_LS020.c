//Library has been modified for STM32F0xx by Aleksey Sedyshev
//https://github.com/AlekseySedyshev

#include "stm32f0xx.h"  
#include "LCD_LS020.h"  
#include "main.h" 

uint8_t _orientation = 0;
uint8_t _width  = LS020_WIDTH;
uint8_t _height = LS020_HEIGHT;

unsigned char const font_5x8[][5]  = 	{	//font_5x8
0x00, 0x00, 0x00, 0x00, 0x00,// (space)  32
0x00, 0x00, 0x5F, 0x00, 0x00,// !        33
0x00, 0x07, 0x00, 0x07, 0x00,// "        34
0x14, 0x7F, 0x14, 0x7F, 0x14,// #        35
0x24, 0x2A, 0x7F, 0x2A, 0x12,// $        36
0x23, 0x13, 0x08, 0x64, 0x62,// %        37
0x36, 0x49, 0x55, 0x22, 0x50,// &        38
0x00, 0x05, 0x03, 0x00, 0x00,// '        39
0x00, 0x1C, 0x22, 0x41, 0x00,// (        40
0x00, 0x41, 0x22, 0x1C, 0x00,// )        41
0x08, 0x2A, 0x1C, 0x2A, 0x08,// *        42
0x08, 0x08, 0x3E, 0x08, 0x08,// +        43
0x00, 0x50, 0x30, 0x00, 0x00,// ,        44
0x08, 0x08, 0x08, 0x08, 0x08,// -        45
0x00, 0x30, 0x30, 0x00, 0x00,// .        46
0x20, 0x10, 0x08, 0x04, 0x02,// /        47
0x3E, 0x51, 0x49, 0x45, 0x3E,// 0        48
0x00, 0x42, 0x7F, 0x40, 0x00,// 1        49
0x42, 0x61, 0x51, 0x49, 0x46,// 2        50
0x21, 0x41, 0x45, 0x4B, 0x31,// 3        51
0x18, 0x14, 0x12, 0x7F, 0x10,// 4        52
0x27, 0x45, 0x45, 0x45, 0x39,// 5        53
0x3C, 0x4A, 0x49, 0x49, 0x30,// 6        54
0x01, 0x71, 0x09, 0x05, 0x03,// 7        55
0x36, 0x49, 0x49, 0x49, 0x36,// 8        56
0x06, 0x49, 0x49, 0x29, 0x1E,// 9        57
0x00, 0x36, 0x36, 0x00, 0x00,// :        58
0x00, 0x56, 0x36, 0x00, 0x00,// ;        59
0x00, 0x08, 0x14, 0x22, 0x41,// <        60
0x14, 0x14, 0x14, 0x14, 0x14,// =        61
0x41, 0x22, 0x14, 0x08, 0x00,// >        62
0x02, 0x01, 0x51, 0x09, 0x06,// ?        63
0x32, 0x49, 0x79, 0x41, 0x3E,// @        64
0x7E, 0x11, 0x11, 0x11, 0x7E,// A        65
0x7F, 0x49, 0x49, 0x49, 0x36,// B        66
0x3E, 0x41, 0x41, 0x41, 0x22,// C        67
0x7F, 0x41, 0x41, 0x22, 0x1C,// D        68
0x7F, 0x49, 0x49, 0x49, 0x41,// E        69
0x7F, 0x09, 0x09, 0x01, 0x01,// F        70
0x3E, 0x41, 0x41, 0x51, 0x32,// G        71
0x7F, 0x08, 0x08, 0x08, 0x7F,// H        72
0x00, 0x41, 0x7F, 0x41, 0x00,// I        73
0x20, 0x40, 0x41, 0x3F, 0x01,// J        74
0x7F, 0x08, 0x14, 0x22, 0x41,// K        75
0x7F, 0x40, 0x40, 0x40, 0x40,// L        76
0x7F, 0x02, 0x04, 0x02, 0x7F,// M        77
0x7F, 0x04, 0x08, 0x10, 0x7F,// N        78
0x3E, 0x41, 0x41, 0x41, 0x3E,// O        79
0x7F, 0x09, 0x09, 0x09, 0x06,// P        80
0x3E, 0x41, 0x51, 0x21, 0x5E,// Q        81
0x7F, 0x09, 0x19, 0x29, 0x46,// R        82
0x46, 0x49, 0x49, 0x49, 0x31,// S        83
0x01, 0x01, 0x7F, 0x01, 0x01,// T        84
0x3F, 0x40, 0x40, 0x40, 0x3F,// U        85
0x1F, 0x20, 0x40, 0x20, 0x1F,// V        86
0x7F, 0x20, 0x18, 0x20, 0x7F,// W        87
0x63, 0x14, 0x08, 0x14, 0x63,// X        88
0x03, 0x04, 0x78, 0x04, 0x03,// Y        89
0x61, 0x51, 0x49, 0x45, 0x43,// Z        90
0x00, 0x00, 0x7F, 0x41, 0x41,// [        91
0x02, 0x04, 0x08, 0x10, 0x20,// "\"      92
0x41, 0x41, 0x7F, 0x00, 0x00,// ]        93
0x04, 0x02, 0x01, 0x02, 0x04,// ^        94
0x40, 0x40, 0x40, 0x40, 0x40,// _        95
0x00, 0x01, 0x02, 0x04, 0x00,// `        96
0x20, 0x54, 0x54, 0x54, 0x78,// a        97
0x7F, 0x48, 0x44, 0x44, 0x38,// b        98
0x38, 0x44, 0x44, 0x44, 0x20,// c        99
0x38, 0x44, 0x44, 0x48, 0x7F,// d        100
0x38, 0x54, 0x54, 0x54, 0x18,// e        101
0x08, 0x7E, 0x09, 0x01, 0x02,// f        102
0x08, 0x14, 0x54, 0x54, 0x3C,// g        103
0x7F, 0x08, 0x04, 0x04, 0x78,// h        104
0x00, 0x44, 0x7D, 0x40, 0x00,// i        105
0x20, 0x40, 0x44, 0x3D, 0x00,// j        106
0x00, 0x7F, 0x10, 0x28, 0x44,// k        107
0x00, 0x41, 0x7F, 0x40, 0x00,// l        108
0x7C, 0x04, 0x18, 0x04, 0x78,// m        109
0x7C, 0x08, 0x04, 0x04, 0x78,// n        110
0x38, 0x44, 0x44, 0x44, 0x38,// o        111
0x7C, 0x14, 0x14, 0x14, 0x08,// p        112
0x08, 0x14, 0x14, 0x18, 0x7C,// q        113
0x7C, 0x08, 0x04, 0x04, 0x08,// r        114
0x48, 0x54, 0x54, 0x54, 0x20,// s        115
0x04, 0x3F, 0x44, 0x40, 0x20,// t        116
0x3C, 0x40, 0x40, 0x20, 0x7C,// u        117
0x1C, 0x20, 0x40, 0x20, 0x1C,// v        118
0x3C, 0x40, 0x30, 0x40, 0x3C,// w        119
0x44, 0x28, 0x10, 0x28, 0x44,// x        120
0x0C, 0x50, 0x50, 0x50, 0x3C,// y        121
0x44, 0x64, 0x54, 0x4C, 0x44,// z        122
0x00, 0x08, 0x36, 0x41, 0x00,// {        123
0x00, 0x00, 0x7F, 0x00, 0x00,// |        124
0x00, 0x41, 0x36, 0x08, 0x00,// }        125
0x00, 0x00, 0x00, 0x00, 0x00,// (space)  126
0x00, 0x00, 0x00, 0x00, 0x00,// (space)  127
0x7E, 0x11, 0x11, 0x11, 0x7E,// A        192
0x7F, 0x45, 0x45, 0x45, 0x39,// Б        193
0x7F, 0x49, 0x49, 0x49, 0x36,// B        194
0x7F, 0x01, 0x01, 0x01, 0x03,// Г        195
0xC0, 0x7E, 0x41, 0x7F, 0xC0,// Д        196
0x7F, 0x49, 0x49, 0x49, 0x41,// E        197
119,8,127,8,119,             // Ж        198
34,73,73,73,54,              // З        199
127,32,16,8,127,             // И        200
127,32,19,8,127,             // Й        201
0x7F, 0x08, 0x14, 0x22, 0x41,// K        202
64,62,1,1,127,               // Л        203
0x7F, 0x02, 0x04, 0x02, 0x7F,// M        204
0x7F, 0x08, 0x08, 0x08, 0x7F,// H        205
0x3E, 0x41, 0x41, 0x41, 0x3E,// O        206
127,1,1,1,127,               // П        207
0x7F, 0x09, 0x09, 0x09, 0x06,// P        208
0x3E, 0x41, 0x41, 0x41, 0x22,// C        209
0x01, 0x01, 0x7F, 0x01, 0x01,// T        210
39,72,72,72,63,              // У        211
30,33,127,33,30,             // Ф        212
0x63, 0x14, 0x08, 0x14, 0x63,// X        213
127,64,64,127,192,           // Ц        214
15,16,16,16,127,             // Ч        215
127,64,124,64,127,           // Ш        216
127,64,124,64,255,           // Щ        217
1,127,72,72,48,              // Ъ        218
127,72,48,0,127,             // Ы        219
127,72,72,72,48,             // Ь        220
34,73,73,73,62,              // Э        221
127,8,62,65,62,              // Ю        222
118,9,9,9,127,               // Я        223
0x20, 0x54, 0x54, 0x54, 0x78,// a        224
124, 84, 84, 84, 36,         // б        225
124, 84, 84, 84, 40,         // в        226
124, 4, 4, 4, 12,            // г        227
192, 120, 68, 124, 192,      // д        228
0x38, 0x54, 0x54, 0x54, 0x18,// e        229
108, 16, 124, 16, 108,       // ж        230
40, 68, 84, 84, 40,          // з        231
124, 32, 16, 8, 124,         // и        232
124, 33, 18, 8, 124,         // й        233
124, 16, 16, 40, 68,         // к        234
64, 56, 4, 4, 124,           // л        235
124, 8, 16, 8, 124,          // м        236
124, 16, 16, 16, 124,        // н        237
0x38, 0x44, 0x44, 0x44, 0x38,// o        238
124, 4, 4, 4, 124,           // п        239
0x7C, 0x14, 0x14, 0x14, 0x08,// p        240
0x38, 0x44, 0x44, 0x44, 0x20,// c        241
4, 4, 124, 4, 4,             // т        242
0x0C, 0x50, 0x50, 0x50, 0x3C,// y        243
24, 36, 124, 36, 24,         // ф        244
0x44, 0x28, 0x10, 0x28, 0x44,// x        245
124, 64, 64, 124, 192,       // ц        246
12, 16, 16, 16, 124,         // ч        247
124, 64, 120, 64, 124,       // ш        248
124, 64, 120, 64, 252,       // щ        249
124, 84, 80, 80, 32,         // ъ        250
124,80,32,0,124,             // ы        251
124, 80, 80, 80, 32,         // ь        252
40, 68, 84, 84, 56,          // э        253
124, 16, 56, 68, 56,         // ю        254
72, 52, 20, 20, 124          // я        255
};

unsigned char init_array_0[] = 				{	//init_array_0 
        0xEF, 0x00, 0xEE, 0x04, 0x1B, 0x04, 0xFE, 0xFE,
        0xFE, 0xFE, 0xEF, 0x90, 0x4A, 0x04, 0x7F, 0x3F,
        0xEE, 0x04, 0x43, 0x06
    };
 
unsigned char init_array_1[] = 				{	//init_array_1
        0xEF, 0x90, 0x09, 0x83, 0x08, 0x00, 0x0B, 0xAF,
        0x0A, 0x00, 0x05, 0x00, 0x06, 0x00, 0x07, 0x00,
        0xEF, 0x00, 0xEE, 0x0C, 0xEF, 0x90, 0x00, 0x80,
        0xEF, 0xB0, 0x49, 0x02, 0xEF, 0x00, 0x7F, 0x01,
        0xE1, 0x81, 0xE2, 0x02, 0xE2, 0x76, 0xE1, 0x83,
        0x80, 0x01, 0xEF, 0x90, 0x00, 0x00
    };
//------------------------------LCD ------------------------------
  
void SPI_Wr(cmd_data_sv data,unsigned char value)																				{
if (data==CMD) 	{CMD_();}
	else 					{DAT_();}
CS_LO();
while (!(SPI1->SR & SPI_SR_TXE)){};	 
SPI1_DR_8bit = value;
while (SPI1->SR & SPI_SR_BSY){};
while (!(SPI1->SR & SPI_SR_RXNE)){}; 
SPI1_DR_8bit;	
CS_HI();
}

void SPI_WrReg(cmd_data_sv data,unsigned char reg,unsigned char value)									{
if (data==CMD) 	{CMD_();}
	else 					{DAT_();}
CS_LO();
while (!(SPI1->SR & SPI_SR_TXE)){};	 
SPI1_DR_8bit = reg;
while (SPI1->SR & SPI_SR_BSY){};
while (!(SPI1->SR & SPI_SR_RXNE)){}; 
SPI1_DR_8bit;		
while (!(SPI1->SR & SPI_SR_TXE)){};	 
SPI1_DR_8bit = value;
while (SPI1->SR & SPI_SR_BSY){};
while (!(SPI1->SR & SPI_SR_RXNE)){}; 
SPI1_DR_8bit;	
CS_HI();
}



void SPI_Wr16(cmd_data_sv data,uint16_t value)																					{
if (data==CMD) 	{CMD_();}
	else 					{DAT_();}
CS_LO();
while (!(SPI1->SR & SPI_SR_TXE)){};	 
SPI1_DR_8bit = value>>8;
while (SPI1->SR & SPI_SR_BSY){};
while (!(SPI1->SR & SPI_SR_RXNE)){}; 
SPI1_DR_8bit;		
while (!(SPI1->SR & SPI_SR_TXE)){};	 
SPI1_DR_8bit = (value & 0xff);
while (SPI1->SR & SPI_SR_BSY){};
while (!(SPI1->SR & SPI_SR_RXNE)){}; 
SPI1_DR_8bit;	
CS_HI();
}




void SPI_Write_Buf(cmd_data_sv data, unsigned char *pBuf, unsigned char bytes)					{
 if (data==CMD) 	{CMD_();}
	else 					{DAT_();} 
CS_LO();
for(uint8_t i = 0; i < bytes; i ++ )
 {
  while (!(SPI1->SR & SPI_SR_TXE)){};	
	SPI1_DR_8bit = pBuf[i]; 
	while (SPI1->SR & SPI_SR_BSY){};
	while (!(SPI1->SR & SPI_SR_RXNE)){};
	SPI1_DR_8bit;	
 }
CS_HI();
}

unsigned int setcolor(unsigned char cRed,unsigned char cGreen, unsigned char cBlue) {
// RED/ GREEN/ BLUE	:	RRRR R ggg ggg B BBBB	
	return (uint16_t)( ((uint16_t)(cRed>>3))<<11 | ((uint16_t)(cGreen>>2))<<5 | ((uint16_t)(cBlue>>3)&0x1F));
} 

void setRotation(unsigned char rot) 																										{

    uint8_t val01, val05;
    switch(rot) {

        case 1:
            _orientation = 1;
            _width  = LS020_HEIGHT;
            _height = LS020_WIDTH;
            val01 = 0x00; 
            val05 = 0x00;
        break;
        case 2:
            _orientation = 2;
            _width  = LS020_WIDTH;
            _height = LS020_HEIGHT;
            val01 = 0x80;               //x0->x1, y1->y0
            val05 = 0x04;               //0x04=rotate, 0x00=normal
        break;
        case 3:
            _orientation = 3;
            _width  = LS020_HEIGHT;
            _height = LS020_WIDTH;
            val01 = 0xC0;               //x1->x0, y1->y0
            val05 = 0x00;               //0x04=rotate, 0x00=normal
        break;
        default:
            _orientation = 0;
            _width  = LS020_WIDTH;
            _height = LS020_HEIGHT;
            val01 = 0x40;               //x1->x0, y0->y1
            val05 = 0x04;               //0x04=rotate, 0x00=normal
        break;
    }

    SPI_WrReg(CMD,0xEF, 0x90);
    SPI_WrReg(CMD,0x01, val01);
    SPI_WrReg(CMD,0x05, val05);

    //setAddrWindow(0, 0, _width-1, _height-1);
}



void SetArea(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1) 		{

    SPI_WrReg(CMD,0xEF, 0x90);

    switch(_orientation) {

        case 0:
            SPI_WrReg(CMD,0x08, y0);                        //set y0
            SPI_WrReg(CMD,0x09, y1);                        //set y1
            SPI_WrReg(CMD,0x0A, (LS020_WIDTH-1) - x0);      //set x0
            SPI_WrReg(CMD,0x0B, (LS020_WIDTH-1) - x1);      //set x1
            SPI_WrReg(CMD,0x06, y0);                        //set y cursor pos
            SPI_WrReg(CMD,0x07, (LS020_WIDTH-1) - x0);      //set x cursor pos
        break;
        case 1:
            SPI_WrReg(CMD,0x08, x0);                        //set y0
            SPI_WrReg(CMD,0x09, x1);                        //set y1
            SPI_WrReg(CMD,0x0A, y0);                        //set x0
            SPI_WrReg(CMD,0x0B, y1);                        //set x1
            SPI_WrReg(CMD,0x06, x0);                        //set y cursor pos
            SPI_WrReg(CMD,0x07, y0);                        //set x cursor pos
        break;
        case 2:
             SPI_WrReg(CMD,0x08, (LS020_HEIGHT-1) - y0);    //set y0
            SPI_WrReg(CMD,0x09, (LS020_HEIGHT-1) - y1);     //set y1
            SPI_WrReg(CMD,0x0A, x0);                        //set x0
            SPI_WrReg(CMD,0x0B, x1);                        //set x1
            SPI_WrReg(CMD,0x06, (LS020_HEIGHT-1) - y0);     //set y cursor pos
            SPI_WrReg(CMD,0x07, x0);                        //set x cursor pos
        break;
        case 3:
            SPI_WrReg(CMD,0x08, (LS020_HEIGHT-1) - x0);     // set x0
            SPI_WrReg(CMD,0x09, (LS020_HEIGHT-1) - x1);     //set x1
            SPI_WrReg(CMD,0x0A, (LS020_WIDTH-1) - y0);      //set y0
            SPI_WrReg(CMD,0x0B, (LS020_WIDTH-1) - y1);      //set y1
            SPI_WrReg(CMD,0x06, (LS020_HEIGHT-1) - x0);     //set x cursor pos
            SPI_WrReg(CMD,0x07, (LS020_WIDTH-1) - y0);      //set y cursor pos
        break;
    }
}


void LCD_Init(void) 																																		{// INIT LCD
CS_HI();
RES_ON();
delay_ms(100);
RES_OFF();
delay_ms(100);	

for (uint8_t i = 0; i < sizeof(init_array_0); i++ ) {SPI_Wr(CMD, init_array_0[i]); }
delay_ms(7);
for (uint8_t i = 0; i < sizeof(init_array_1); i++ ) { SPI_Wr(CMD, init_array_1[i]); }
setRotation(_orientation);	
}


void invertDisplay(const bool invert) 																									{

    SPI_WrReg(CMD,0xEF, 0xB0);
    SPI_WrReg(CMD,0x49, (invert) ? 0x03:0x02);
    SPI_WrReg(CMD,0xEF, 0x90);
}
void Put_Pixel (int16_t x, int16_t y, uint16_t color) 																	{

    if ((x >= 0 && x < _width) 
    && (y >= 0 && y < _height)) {

        SetArea(x, y, x, y);
        SPI_Wr16(DAT, color);
    }
}
void LCD_FillScreen (unsigned int color)																								{//заливаем цветом 
 SetArea(0, 0, _width-1, _height-1);
    for(uint32_t size = LS020_WIDTH*LS020_HEIGHT; size!=0; size--) {

      SPI_Wr16(DAT, color);
    }               
} 


void LCD_DrawLine (unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned int color)																												{//НАРИСОВАТЬ ЛИНИЮ 
 short  x, y, d, dx, dy, i, i1, i2, kx, ky;
 signed char flag;

 dx = x2 - x1;
 dy = y2 - y1;
 if (dx == 0 && dy == 0) Put_Pixel(x1, y1, color);  //Точка
 else      //Линия
 {
  kx = 1;
  ky = 1;
  if( dx < 0 )
  { 
   dx = -dx; 
   kx = -1; 
  }
  else
  if(dx == 0) kx = 0;
  if(dy < 0)
  { 
   dy = -dy; 
   ky = -1; 
  }
  if(dx < dy)
  { 
   flag = 0; 
   d = dx; 
   dx = dy; 
   dy = d; 
  }
  else flag = 1;
  i1 = dy + dy; 
  d = i1 - dx; 
  i2 = d - dx;
  x = x1; 
  y = y1;

  for(i=0; i < dx; i++)
  {
   Put_Pixel(x, y, color);
   if(flag) x += kx;
   else y += ky;
   if( d < 0 ) d += i1;
   else
   {
    d += i2;
    if(flag) y += ky;
    else x += kx;
   }
  }
  Put_Pixel(x, y, color);
 }
} 



void LCD_DrawRect (unsigned char x1,unsigned char y1,unsigned char width,unsigned char height,unsigned char size,unsigned int color)															{//НАРИСОВАТЬ РАМКУ     
 unsigned int i;
 char x2=x1+(width-1), y2=y1+(height-1); //Конечные размеры рамки по осям х и у
 for( i=1; i<=size; i++)   // size - толщина рамки
 {
  LCD_DrawLine(x1, y1, x1, y2, color);
  LCD_DrawLine(x2, y1, x2, y2, color);
  LCD_DrawLine(x1, y1, x2, y1, color);
  LCD_DrawLine(x1, y2, x2, y2, color);
  x1++; // Увеличиваю толщину рамки, если это задано
  y1++;
  x2--;
  y2--;
 }
}
void LCD_FillRect(unsigned char x, unsigned char  y, unsigned char  w, unsigned char  h, unsigned int  color) 																										{
    
    for (uint8_t row = 0; row < h; row++) {

        SetArea(x, y+row, x+w-1, y+row);

        for (int8_t size = w; size!=0; size--) {

            SPI_Wr16(DAT, color);
        }
    }
}
void LCD_DrawCircle (unsigned char xcenter, unsigned char ycenter, unsigned char rad,unsigned int color)																													{//НАРИСОВАТЬ ОКРУЖНОСТЬ
 signed int tswitch, x1=0, y1; 
 unsigned char d;

 d = ycenter - xcenter;
 y1 = rad;
 tswitch = 3 - 2 * rad;
 while (x1 <= y1) 
 {
  Put_Pixel(xcenter + x1, ycenter + y1, color); 
  Put_Pixel(xcenter + x1, ycenter - y1, color);
  Put_Pixel(xcenter - x1, ycenter + y1, color);   
  Put_Pixel(xcenter - x1, ycenter - y1, color);
  Put_Pixel(ycenter + y1 - d, ycenter + x1, color); 
  Put_Pixel(ycenter + y1 - d, ycenter - x1, color);
  Put_Pixel(ycenter - y1 - d, ycenter + x1, color);
  Put_Pixel(ycenter - y1 - d, ycenter - x1, color);

  if (tswitch < 0) tswitch += (4 * x1 + 6);
  else 
  {
   tswitch += (4 * (x1 - y1) + 10);
   y1--;
  }
  x1++;
 }
}    
void LCD_FillCircle (unsigned char xcenter, unsigned char ycenter, unsigned char rad,unsigned int color)																													{// ЗАПОЛНИТЬ КРУГ ЦВЕТОМ COLOR
 signed int x1=0, y1, tswitch; 
 y1 = rad;
 tswitch = 1 - rad;

 do
 {
  LCD_DrawLine(xcenter-x1, ycenter+y1, xcenter+x1, ycenter+y1, color);
  LCD_DrawLine(xcenter-x1, ycenter-y1, xcenter+x1, ycenter-y1, color);
  LCD_DrawLine(xcenter-y1, ycenter+x1, xcenter+y1, ycenter+x1, color);
  LCD_DrawLine(xcenter-y1, ycenter-x1, xcenter+y1, ycenter-x1, color);

  if(tswitch < 0)
  tswitch+= 3 + 2*x1++;
  else
  tswitch+= 5 + 2*(x1++ - y1--);
 } while(x1 <= y1);
}

void LCD_DrawTriangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char x3, unsigned char y3,unsigned int color)							{//НАРИСОВАТЬ ТРЕУГОЛЬНИК
 LCD_DrawLine(x1, y1, x2, y2, color);
 LCD_DrawLine(x3, y3, x1, y1, color);
 LCD_DrawLine(x3, y3, x2, y2, color);  
}


void LCD_FillTriangleA(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char x3, unsigned char y3,unsigned int color)							{
 signed long x, y, addx, dx, dy;
 signed long P;
 int i;
 long a1,a2,b1,b2;
 if(y1>y2)  {b1=y2; b2=y1; a1=x2; a2=x1;}
 else       {b1=y1; b2=y2; a1=x1; a2=x2;}
 dx = a2 -a1;
 dy = b2 - b1;
 if(dx<0)dx=-dx;
 if(dy<0)dy=-dy;
 x = a1;
 y = b1;
   
 if(a1 > a2)    addx = -1;
 else           addx = 1;
   
 if(dx >= dy)
 {
  P = 2*dy - dx;
  for(i=0; i<=dx; ++i)
  {
   LCD_DrawLine((int)x, (int)y, x3, y3, color);
   if(P < 0)
   {
    P += 2*dy;
    x += addx;
   }
   else
   {
    P += 2*dy - 2*dx;
    x += addx;
    y ++;
   }
  }
 }
 else
 {
  P = 2*dx - dy;
  for(i=0; i<=dy; ++i)
  {
   LCD_DrawLine((int)x, (int)y, x3, y3, color);
   if(P < 0)
   {
    P += 2*dx;
    y ++;
   }
   else
   {
    P += 2*dx - 2*dy;
    x += addx;
    y ++;
   }
  }
 }
}
void LCD_FillTriangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char x3, unsigned char y3,unsigned int color)							{//ЗАПОЛНИТЬ ТРЕУГОЛЬНИК ЦВЕТОМ COLOR
 LCD_FillTriangleA(x1, y1, x2, y2, x3, y3, color);
 LCD_FillTriangleA(x3, y3, x1, y1, x2, y2, color);
 LCD_FillTriangleA(x3, y3, x2, y2, x1, y1, color);
}    






void Send_Symbol (unsigned char symbol, unsigned char x, unsigned char y,unsigned int t_color,unsigned int b_color, unsigned char zoom_width, unsigned char zoom_height, int rot) {//Функция прорисовки символа на дисплее
 unsigned char temp_symbol, a, b, zw, zh, mask; 
 char m, n;
 m=x; 
 n=y;
 if (symbol>127) symbol-=64;    //Убираем отсутствующую часть таблицы ASCII
 for ( a = 0; a < 5; a++) //Перебираю 5 байт, составляющих символ
 {  
  temp_symbol = font_5x8[symbol-32][a];
  zw = 0; 
  while(zw != zoom_width) //Вывод байта выполняется zw раз 
  {    
   switch(rot)
   {
    case 0: case 180: n=y; break;
    case 90: case 270: m=x; break;
   } 
   mask=0x01;     
   for ( b = 0; b < 8; b++ ) //Цикл перебирания 8 бит байта
   {         
    zh = 0; //в zoom_height раз увеличится высота символа
    while(zh != zoom_height) //Вывод пикселя выполняется z раз
    {
     switch(rot)
     {
      case 0: case 180:  
      if (temp_symbol&mask) 
      {
       Put_Pixel (m+zw, n+zh, t_color);
      }
      else
      {
       Put_Pixel (m+zw, n+zh, b_color);
      }
      break; 
      case 90: case 270: 
      if (temp_symbol&mask) 
      {
       Put_Pixel (m+zh, n+zw, t_color);
      }
      else
      {
       Put_Pixel (m+zh, n+zw, b_color);
      }
      break; //Получить адрес начального пикселя по оси y для вывода очередного байта            
     }            
     zh++;
    }
    mask<<=1; //Смещаю содержимое mask на 1 бит влево;
    switch(rot)
    {
     case 0: case 180: n=n+zoom_height; break;
     case 90: case 270: m=m+zoom_height; break;
    }          
   }
   zw++;   
  }
  switch(rot)
  {
   case 0: case 180: m=m+zoom_width; break;
   case 90: case 270: n=n+zoom_width; break;
  }           
 }
} 


void LCD_Putchar(char symbol, unsigned char x, unsigned char y,unsigned int t_color,unsigned int b_color, unsigned char zoom_width, unsigned char zoom_height,  int rot)					{//Функция вывода одного символа ASCII-кода 
    unsigned char m;
    if(zoom_width == 0)   zoom_width = 1;
    if(zoom_height == 0)  zoom_height = 1;
    switch (rot)
    {
        case 0:  //Начальный адрес осей Х и У - левый верхний угол дисплея   
        Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rot);
        break;
        //================================
        case 90:
        m=y+3; y=x; x=m;
        SPI_Wr(CMD, 0x36); 
        SPI_Wr(DAT, 0x08); //Начальный адрес осей Х и У - правый верхний угол дисплея 
        Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rot);
        SPI_Wr(CMD, 0x36); 
        SPI_Wr(DAT, 0x48);
        break;
        //================================
        case 180:
        x+=3; y+=2;       
        SPI_Wr(CMD, 0x36); 
        SPI_Wr(DAT, 0x88); //Начальный адрес осей Х и У - правый нижний угол дисплея 
        Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rot);
        SPI_Wr(CMD, 0x36); 
        SPI_Wr(DAT, 0x48);
        break;
        //================================
        case 270:
        m=y; y=x+2; x=m;
        SPI_Wr(CMD, 0x36); 
        SPI_Wr(DAT, 0xC8); //Начальный адрес осей Х и У - левый нижний угол дисплея  
        Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rot);
        SPI_Wr(CMD, 0x36); 
        SPI_Wr(DAT, 0x48);
        break;
        //================================
        default:
        SPI_Wr(CMD, 0x36); 
        SPI_Wr(DAT, 0x48); //Начальный адрес осей Х и У - левый верхний угол дисплея  
        Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height, rot);
        SPI_Wr(CMD, 0x36); 
        SPI_Wr(DAT, 0x48);
        //=================================    
    };  
}

void LCD_Puts(char *str, unsigned char x, unsigned char y, unsigned int t_color,unsigned int b_color, unsigned char zoom_width, unsigned char zoom_height, int rot)																		{//Функция вывода строки
 unsigned char i=0;
              
 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
   
 while (str[i]) //x и y - адрес пикселя начальной позиции; с увеличением переменной i адрес вывода очередного символа смещается на i*6 (чем организуются столбцы дисплея)  
 {      
  LCD_Putchar(str[i], x+(i*6*zoom_width), y, t_color, b_color, zoom_width, zoom_height, rot);
  i++;
 }  
}
void Send_Symbol_Shadow (unsigned char symbol, unsigned char x, unsigned char y,unsigned int t_color, unsigned char zoom_width, unsigned char zoom_height, int rot) 			{//
 unsigned char temp_symbol, a, b, zw, zh, mask; 
 char m, n;
 m=x; 
 n=y;
 if (symbol>127) symbol-=64;    //Убираем отсутствующую часть таблицы ASCII
 for ( a = 0; a < 5; a++) //Перебираю 5 байт, составляющих символ
 {  
  temp_symbol = font_5x8[symbol-32][a];
  zw = 0; 
  while(zw != zoom_width) //Вывод байта выполняется zw раз 
  {    
   switch(rot)
   {
    case 0: case 180: n=y; break;
    case 90: case 270: m=x; break;
   } 
   mask=0x01;     
   for ( b = 0; b < 8; b++ ) //Цикл перебирания 8 бит байта
   {         
    zh = 0; //в zoom_height раз увеличится высота символа
    while(zh != zoom_height) //Вывод пикселя выполняется z раз
    {
     switch(rot)
     {
      case 0: case 180:  
      if (temp_symbol&mask) 
      {
       Put_Pixel (m+zw, n+zh, t_color);
      }
      break; 
      case 90: case 270: 
      if (temp_symbol&mask) 
      {
       Put_Pixel (m+zh, n+zw, t_color);
      }
      break; //Получить адрес начального пикселя по оси y для вывода очередного байта            
     }            
     zh++;
    }
    mask<<=1; //Смещаю содержимое mask на 1 бит влево;
    switch(rot)
    {
     case 0: case 180: n=n+zoom_height; break;
     case 90: case 270: m=m+zoom_height; break;
    }          
   }
   zw++;   
  }
  switch(rot)
  {
   case 0: case 180: m=m+zoom_width; break;
   case 90: case 270: n=n+zoom_width; break;
  }           
 }
} 


void LCD_Putchar_Shadow (char symbol, unsigned char x, unsigned char y,unsigned int t_color, unsigned char zoom_width, unsigned char zoom_height, int rot)								{//Функция вывода одного символа ASCII-кода без цвета фона
 unsigned char m;
 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
 switch (rot)
 {
  case 0:  //Начальный адрес осей Х и У - левый верхний угол дисплея   
  Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height, rot);
  break;
  //================================
  case 90:  
  m=y+3; y=x; x=m;
  SPI_Wr(CMD, 0x36); 
  SPI_Wr(DAT, 0x08); //Начальный адрес осей Х и У - правый верхний угол дисплея 
  Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height, rot);
  SPI_Wr(CMD, 0x36); 
  SPI_Wr(DAT, 0x48);
  break;
  //================================
  case 180:
  x+=3; y+=2;          
  SPI_Wr(CMD, 0x36); 
  SPI_Wr(DAT, 0x88); //Начальный адрес осей Х и У - правый нижний угол дисплея 
  Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height, rot);
  SPI_Wr(CMD, 0x36); 
  SPI_Wr(DAT, 0x48);
  break;
  //================================
  case 270:
  m=y; y=x+2; x=m;
  SPI_Wr(CMD, 0x36); 
  SPI_Wr(DAT, 0xC8); //Начальный адрес осей Х и У - левый нижний угол дисплея  
  Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height, rot);
  SPI_Wr(CMD, 0x36); 
  SPI_Wr(DAT, 0x48);
  break;
  //================================
  default:
  SPI_Wr(CMD, 0x36); 
  SPI_Wr(DAT, 0x48); //Начальный адрес осей Х и У - левый верхний угол дисплея  
  Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height, rot);
  SPI_Wr(CMD, 0x36); 
  SPI_Wr(DAT, 0x48);
  //=================================    
 };  
}

void LCD_Puts_Shadow(char *str, unsigned char x, unsigned char y, unsigned int t_color, unsigned char zoom_width, unsigned char zoom_height, int rot)												{//Функция вывода строки, без цвета фона 

 unsigned char i=0;
                    
 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
   
 while (str[i]) //x и y - адрес пикселя начальной позиции; с увеличением переменной i адрес вывода очередного символа смещается на i*6 (чем организуются столбцы дисплея)  
 {      
  LCD_Putchar_Shadow(str[i], x+(i*6*zoom_width), y, t_color, zoom_width, zoom_height, rot);
  i++;
 }  
}



void LCD_PrintDec(long val,int x, int y,unsigned  int t_color,unsigned int b_color, unsigned char zoom_width, unsigned char zoom_height, int rot) 							{// Print Dec

 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
	
	char i=1,d=0;
	unsigned char text[10];
//-------Added for support valur <0----------------
	uint8_t minus_flag=0;
	uint32_t value;
	if (val>=0) {value=val;}
		else {value=val*(-1);minus_flag=1;}

//-------------------------------------------------	
do 
  { 
    if (value >=10)  {
				d = value % 10; 																				
				text[i] = d + '0'; 																			
				value /= 10; 																						
			}
		else 
			{	text[i] = value + '0';
				value=0;
			}
 		i++;
  }
	while(value); 

//-------Added for support valur <0----------------
	if(minus_flag) {text[i]='-';}
		else {i--;}		
	d=i;
for (d=i;d>0;d--){	
	
		LCD_Putchar(text[d], x+((i-d)*6*zoom_width), y, t_color, b_color, zoom_width, zoom_height, rot);
		
	}

}
			
void LCD_PrintHex(long val,int x, int y,unsigned  int t_color,unsigned int b_color, unsigned char zoom_width, unsigned char zoom_height, int rot) 							{// Print Hex
	
	char i=1,d=0;
	unsigned char text[10];
//-------------Added for support valur <0
	uint8_t minus_flag=0;
	uint32_t value;
	if (val>=0) {value=val;}
		else {value=val*(-1);minus_flag=1;}
//---------------------------------------		
	do 
  { 
    if (value >=0x10)  {
				d = value % 0x10; 																				
				if(d<0x0A) text[i] = d + '0'; 																			
				else 			 text[i] = d + 0x37;
				value /= 0x10; 																						
			}
		else 
			{	
				if(value < 0x0A)	text[i] = value + '0';			//0..9
				else 							text[i] = value + 0x37;			//A...F
				value=0;
			}
 		i++;
  }
	while(value); 
//-------Added for support valur <0----------------
	if(minus_flag) {text[i]='-';}
	else {i--;}		
//---------------------------------------		
d=i;
	do
	{	LCD_Putchar(text[i], x+((d-i)*6*zoom_width), y, t_color, b_color, zoom_width, zoom_height, rot);
		i--;
	}
	while(i);
}

void LCD_PrintBin(unsigned char value,int x, int y,unsigned  int t_color,unsigned int b_color, unsigned char zoom_width, unsigned char zoom_height, int rot) 		{// Print Bin
	
	unsigned char i=1,d=0;
	unsigned char text[9];
	do 
  { 
    if (value >=2)  {
				d = value % 2; 																				
				text[i] = d + '0'; 																			
				value /= 0x2; 																						
			}
		else 
			{	
				text[i] = value + '0';			//0..9
				value=0;
			}
 		i++;
  }
	while(i<9); 
	i--;
d=i;	
	do
	{	LCD_Putchar(text[i], x+((d-i)*6*zoom_width), y, t_color, b_color, zoom_width, zoom_height, rot);
		i--;
	}
	while(i);
}	

//------------------------------

