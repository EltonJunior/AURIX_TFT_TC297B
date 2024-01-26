/*
 * tfthw.h
 *
 *  Created on: 06.02.2015
 *      Author: dienst
 */
#ifndef TFTHW_H
#define TFTHW_H

/* definition of used chip selects */
#define CS_CPLD             8
#define CS_TOUCH            9
#define CS_NONE             15

/* error flag bits in STATUS and FLAGSCLEAR */
#define QSPI_ERROR_PE       (1 << 0)    /* Parity Error */
#define QSPI_ERROR_UCE      (1 << 1)    /* unexpected Configuration Error */
#define QSPI_ERROR_BRE      (1 << 2)    /* Baud Rate Error */
#define QSPI_ERROR_TXOVF    (1 << 3)    /* TXFIFO Overflow */
#define QSPI_ERROR_TXUNF    (1 << 4)    /* TXFIFO Underflow */
#define QSPI_ERROR_RXOVF    (1 << 5)    /* RXFIFO Overflow */
#define QSPI_ERROR_RXUNF    (1 << 6)    /* RXFIFO Underflow */
#define QSPI_ERROR_EXPECT   (1 << 7)    /* Expect Timeout error */
#define QSPI_ERROR_SE       (1 << 8)    /* SLSI misplaced inactivation */

/* Colour conversion macros: RGB888 ==> RGB565 */
/* GLCD RGB color definitions (RGB565 format) */
#define COL_R_WIDTH         (5)
#define COL_R_POS           (11)
#define COL_G_WIDTH         (6)
#define COL_G_POS           (5)
#define COL_B_WIDTH         (5)
#define COL_B_POS           (0)

#define COL_PART(x, w, p)   ((((x) * (1 << (w))) >> 8) << (p))

#define COL_RGB565(r, g, b) ( COL_PART((r), COL_R_WIDTH, COL_R_POS)\
                            | COL_PART((g), COL_G_WIDTH, COL_G_POS)\
                            | COL_PART((b), COL_B_WIDTH, COL_B_POS))

#define COLOR_BLACK         COL_RGB565(  0,   0,   0)
#define COLOR_NAVY          COL_RGB565(  0,   0, 127)
#define COLOR_DARKGREEN     COL_RGB565(  0, 127,   0)
#define COLOR_DARKCYAN      COL_RGB565(  0, 127, 127)
#define COLOR_MAROON        COL_RGB565(127,   0,   0)
#define COLOR_PURPLE        COL_RGB565(127,   0, 127)
#define COLOR_OLIVE         COL_RGB565(127, 127,   0)
#define COLOR_LIGHTGREY     COL_RGB565(192, 192, 192)
#define COLOR_DARKGREY      COL_RGB565(127, 127, 127)
#define COLOR_BLUE          COL_RGB565(  0,   0, 255)
#define COLOR_GREEN         COL_RGB565(  0, 255,   0)
#define COLOR_CYAN          COL_RGB565(  0, 255, 255)
#define COLOR_RED           COL_RGB565(255,   0,   0)
#define COLOR_MAGENTA       COL_RGB565(255,   0, 255)
#define COLOR_YELLOW        COL_RGB565(255, 255,   0)
#define COLOR_WHITE         COL_RGB565(255, 255, 255)

/* dimensions of LCD and used font */
#define LCD_WIDTH       320
#define LCD_HEIGHT      240
#define CHAR_HEIGHT     24
#define CHAR_WIDTH      16
#define MAX_LINES       (LCD_HEIGHT / CHAR_HEIGHT)

/* "non-normal" vertical direction: top to bottom */
#define LINENO(n)       (((MAX_LINES - (n)) * CHAR_HEIGHT) - 1)

#define LINE0           LINENO(0)
#define LINE1           LINENO(1)
#define LINE2           LINENO(2)
#define LINE3           LINENO(3)
#define LINE4           LINENO(4)
#define LINE5           LINENO(5)
#define LINE6           LINENO(6)
#define LINE7           LINENO(7)
#define LINE8           LINENO(8)
#define LINE9           LINENO(9)

#define TFT_XSIZE 320             //!< x dimension of tft display
#define TFT_YSIZE 240             //!< y dimension of tft display


extern uint16 Row_Buff[];
extern volatile uint32 tft_status;

//specific entries tfthw.c
void tft_drvinit (void);
void tft_init (void);
// flush the actual row buff and callback pFunc if finished
void tft_flush_row_buff(uint32 numberOfPixel, const void * buff);
// set the pixel datapointer to x,y location
void tft_display_setxy (uint32 x1,uint32 y1,uint32 x2, uint32 y2);

// Initialise the Graphic LCD controller
void GLCD_putPixel(unsigned int x, unsigned int y);

// Set foreground color
void GLCD_setTextColor(unsigned short color);

// Set background color
void GLCD_setBackColor(unsigned short color);

// Clear display
void GLCD_clear(unsigned short color);

// Display character on given line
void GLCD_displayChar(unsigned int ln, unsigned int col, unsigned char c);

// Display string on given line
void GLCD_displayStringLn(unsigned int ln, const char *s);

// Clear given line
void GLCD_clearLn(unsigned int ln);

// Display graphical bitmap image at position x horizontally and y vertically
void GLCD_bitmap(unsigned int x, unsigned int y, unsigned int w, unsigned int h, const void *bitmap);

int GLCD_getLineNo(unsigned int line);

void EscreveByteLCD(unsigned char linha, unsigned char coluna, unsigned char data);

void EscreveWordLCD(unsigned char linha,unsigned char coluna, unsigned int data );

#endif /* TFTHW_H */
