/** @file           displayLCD.h
 *  @brief          This library of functions can be used with any LCD
 *  16x2 with equivalent controllers such as the Hitachi controller
 *  HD44780 LCD controller .
 *
 *  @author         Weslley Torres
 *  @since          08/Set/2014
 *  @version        2.0
 *  @description    Modification of the xlcd.h library provided with the compiler
 *  C18 by Microchip.
 *
 *  @author         Elton Junior
 *  @since          9/feb/2022
 *  @version        3.0
 *  @bug            No known bugs.
 */


#ifndef __DISPLAYLCD_H
#define __DISPLAYLCD_H

/** INCLUDES **********************************************************/
#include "pin_manager.h"

/********** LCD Connections Configuration *************/
#define LCD_RS  &MODULE_P00,0
#define LCD_RW  &MODULE_P00,6
#define LCD_EN  &MODULE_P00,1

#define LCD_D4  &MODULE_P00,2
#define LCD_D5  &MODULE_P00,3
#define LCD_D6  &MODULE_P00,4
#define LCD_D7  &MODULE_P00,5

/** D E F I N E S ************************************************************/

// Defines the LCD DATA pins connected to the Microcontroller
#define D4_PIN_LOW()    IfxPort_setPinLow(LCD_D4)
#define D4_PIN_HIGH()   IfxPort_setPinHigh(LCD_D4)

#define D5_PIN_LOW()    IfxPort_setPinLow(LCD_D5)
#define D5_PIN_HIGH()   IfxPort_setPinHigh(LCD_D5)

#define D6_PIN_LOW()    IfxPort_setPinLow(LCD_D6)
#define D6_PIN_HIGH()   IfxPort_setPinHigh(LCD_D6)

#define D7_PIN_LOW()    IfxPort_setPinLow(LCD_D7)
#define D7_PIN_HIGH()   IfxPort_setPinHigh(LCD_D7)

// Defines the LCD CONTROL pins connected to the Microcontroller
#define RS_PIN_LOW()    IfxPort_setPinLow(LCD_RS)
#define RS_PIN_HIGH()   IfxPort_setPinHigh(LCD_RS)

#define E_PIN_LOW()     IfxPort_setPinLow(LCD_EN)
#define E_PIN_HIGH()    IfxPort_setPinHigh(LCD_EN)

#define RW_PIN_LOW()    IfxPort_setPinLow(LCD_RW)
#define RW_PIN_HIGH()   IfxPort_setPinHigh(LCD_RW)

// Defines the  pins from the Microcontroller
#define LCD_D4_OUTPUT() IfxPort_setPinMode(LCD_D4, IfxPort_Mode_outputPushPullGeneral)
#define LCD_D4_INPUT()  IfxPort_setPinMode(LCD_D4, IfxPort_Mode_inputPullUp)

#define LCD_D5_OUTPUT() IfxPort_setPinMode(LCD_D5, IfxPort_Mode_outputPushPullGeneral)
#define LCD_D5_INPUT()  IfxPort_setPinMode(LCD_D5, IfxPort_Mode_inputPullUp)

#define LCD_D6_OUTPUT() IfxPort_setPinMode(LCD_D6, IfxPort_Mode_outputPushPullGeneral)
#define LCD_D6_INPUT()  IfxPort_setPinMode(LCD_D6, IfxPort_Mode_inputPullUp)

#define LCD_D7_OUTPUT() IfxPort_setPinMode(LCD_D7, IfxPort_Mode_outputPushPullGeneral)
#define LCD_D7_INPUT()  IfxPort_setPinMode(LCD_D7, IfxPort_Mode_inputPullUp)

#define LCD_RS_OUTPUT() IfxPort_setPinMode(LCD_RS, IfxPort_Mode_outputPushPullGeneral)
#define LCD_RS_INPUT()  IfxPort_setPinMode(LCD_RS, IfxPort_Mode_inputPullUp)

#define LCD_E_OUTPUT() IfxPort_setPinMode(LCD_EN, IfxPort_Mode_outputPushPullGeneral)
#define LCD_E_INPUT()  IfxPort_setPinMode(LCD_EN, IfxPort_Mode_inputPullUp)

#define LCD_RW_OUTPUT() IfxPort_setPinMode(LCD_RW, IfxPort_Mode_outputPushPullGeneral)
#define LCD_RW_INPUT()  IfxPort_setPinMode(LCD_RW, IfxPort_Mode_inputPullUp)

/*** CONFIGURATION SETTINGS  ***************************/

/******************************************************************************
* Define: LimpaDisplay()
  * Description: Removes all characters from the display and returns the position of the
  * cursor to row 1 and column 1
 *****************************************************************************/
#define LimpaDisplay()      EscreveComandoLCD(0x01)


/******************************************************************************
 * Define:      CursorHome()
* Description: Returns the cursor position for row 1 and column 1, but
  * without removing all characters from the display.
 *****************************************************************************/
#define CursorHome()    EscreveComandoLCD(0x02)


/******************************************************************************
 * Define:      LigaDisplay()
 * Description: Turns the display screen on and off the display cursor.
 *****************************************************************************/
#define LigaDisplay()       EscreveComandoLCD(0x0C)


/******************************************************************************
 * Define:      DesligaDisplay()
* Description: Turns off the display screen, but does not remove characters from
  * memory, nor turn off the backlight.
 *****************************************************************************/
#define DesligaDisplay()    EscreveComandoLCD(0x08)


/******************************************************************************
 * Define:      LigaCursor()
* Description: Makes the cursor appear on the screen, and if the screen is
  * off, will be on.
 *****************************************************************************/
#define LigaCursor()        EscreveComandoLCD(0x0E)


/******************************************************************************
 * Define:      DesligaCursor()
* Description: Makes the cursor disappear from the screen and if it is
  * off, will be on.
 *****************************************************************************/
#define DesligaCursor()     EscreveComandoLCD(0x0C)


/******************************************************************************
 * Define:      PiscaCursor()
* Description: Makes the cursor appear on the LCD and blink. if the
  * screen is off, will be on.
 *****************************************************************************/
#define PiscaCursor()       EscreveComandoLCD(0x0F)


/******************************************************************************
 * Define:      DeslocaCursorDir()
* Description: Causes the cursor to move one position on the screen to the right
 *****************************************************************************/
#define DeslocaCursorDir()      EscreveComandoLCD(0x14)


/******************************************************************************
 * Define:      DeslocaCursorEsq()
* Description: Causes the cursor to move one position on the screen to the left
 *****************************************************************************/
#define DeslocaCursorEsq()      EscreveComandoLCD(0x10)


/******************************************************************************
 * Define:      DeslocaDisplayDir()
 * Description: Causes the screen to shift one position to the right
 *****************************************************************************/
#define DeslocaDisplayDir()     EscreveComandoLCD(0x1C)


/******************************************************************************
 * Define:      DeslocaDisplayEsq()
* Description: Causes the screen to shift one position to the left
 *
 *****************************************************************************/
#define DeslocaDisplayEsq()     EscreveComandoLCD(0x18)


/**  FUNCTION PROTOTYPE   **********************************/

/******************************************************************************
* Function : void ConfiguraLCD ( void )
* Input: None ( void )
* Output: None ( void )
* Description: Configures Microcontroller ports that are connected to the
* LCD display as output . This routine is based on the LCD controller
* Hitachi HD44780. Configures the communication parameters with the display,
* such as:
* - operating mode (4 or 8 data bits)
* - cursor type
* - font size
* At the end of the configuration clears the display.
 *****************************************************************************/
extern void ConfiguraLCD(void);


/******************************************************************************
* Function : void EscreveComandoLCD ( unsigned char cmd )
* Input: cmd : command that will be sent to the LCD
* Output: None ( void )
* Description: (Write a command to the LCD)
* Writes a command to the LCD display.
 *****************************************************************************/
extern void EscreveComandoLCD(unsigned char cmd);


/******************************************************************************
* Function : void EnderecoCursor ( unsigned char address )
* Input: address : display data memory address that is
* place the cursor
* Output: None ( void )
 * Description : (Set the Display Data RAM Address)
 * This routine places the cursor at the desired address of the RAM memory of the
* LCD display. The following writing commands will start from the
* position chosen by this function
 *****************************************************************************/
extern void EnderecoCursor(unsigned char endereco);


/******************************************************************************
 * Funcao:      void PosicaoCursorLCD(unsigned char linha, unsigned char coluna)
 * Entrada:     linha: número de 1 à 4 da linha em que se deseja deixar o cursor
 *
 *              coluna: número de 1 à 16 coluna linha em que se deseja deixar o cursor
 *
 * Saída:       Nenhuma (void)
 * Descrição:   Essa rotina posiciona o cursor na tela do display, na linha
 *  e coluna desejados. Os comandos de escrita seguintes vão começar a partir
 *  da posição escolhida por esta função
 *****************************************************************************/
extern void PosicaoCursorLCD(unsigned char linha, unsigned char coluna);


/******************************************************************************
* Function : void EscreveCaractereLCD ( unsigned char data)
* Input: data: Data byte to be written to LCD RAM memory
* Output: None ( void )
* Description: (Write a Data byte to the LCD)
* This routine writes the character byte to the display from the position
* current memory of the cursor or the memory location chosen with the
* PosicaoCursorLCD () or AddressCursor () functions
 *****************************************************************************/
extern void EscreveCaractereLCD(char data);

/******************************************************************************
* Function : void EscreveInteiroLCD ( int value)
* Input: value: signed integer (from -32768 to 32767) to be written in the
* display.
*
* Output: None ( void )
* Description: This routine writes the integer number to the display starting from the position
* current memory of the cursor or the memory location chosen with the
* PosicaoCursorLCD () or AddressCursor () functions .
 *****************************************************************************/
extern void EscreveInteiroLCD(int valor);

/******************************************************************************
* Function : inline void swap(char *x, char *y)
* Input: value: two character address .
*
* Output: None ( void )
* Description: This function puts the value of x into y and y into x.
 *****************************************************************************/
extern inline void swap(char *x, char *y);

/******************************************************************************
* Function : Reverse(char *buffer, int i , int j)
* Input: value : string .
*
* Output : inverse character sequence
* Description: This function reverses the writing of the received buffer.
 *****************************************************************************/
extern char* Reverse(char *buffer, int i, int j);

/******************************************************************************
* Function : char* itoa (int value, char* buffer, int base);
 * Input: value: converts an integer to character .
*
* Output : character string
* Description: This function converts an integer to character .
 *****************************************************************************/
extern char* itoa(int value, char* buffer, int base);

/******************************************************************************
* Function : void EscreveFloatLCD ( float value, char formatting )
* Input: value: number signed float (from -9999.9999 to 9999.9999) that
* will be written on the display
*
* formatting : number of decimal places desired after the
* comma (from 0 to 4 decimal places).
*
* Output: None ( void )
* Description: This routine writes the number float on display from position
* current of the cursor to as many decimal places as are defined in the
formatting parameter .
 *****************************************************************************/
extern void EscreveFloatLCD(float valor, char formatacao);


/******************************************************************************
* Function : void EscreveFraseRamLCD (char *buffer)
* Input: *buffer: pointer to string in data memory (RAM)
* Output: None ( void )
* Description: This routine copies a null - terminated string
* from microcontroller data memory to LCD display.
* The string pointed to by *buffer is copied into the display from the position
* from current cursor memory or memory location
* chosen with the functions PosicaoCursorLCD () or EnderecoCursor ().
 *****************************************************************************/
extern void EscreveFraseRamLCD(char *buffer);


/******************************************************************************
* Function : void EscreveFraseLCD ( const char *buffer)
* Input: *buffer: pointer to string in program memory (ROM)
* Output: None ( void )
* Description: This routine copies a null - terminated string
* from microcontroller program memory to LCD display.
* The string pointed to by *buffer is copied to the display from the
* current memory location of cursor or chosen memory location
* with the PosicaoCursorLCD () or EnderecoCursor () functions .
 *****************************************************************************/
extern void EscreveFraseLCD(const char *buffer);


/******************************************************************************
 * Funcao:      void CriaCaractereLCD(unsigned char endereco, const char *buffer)
 * Entrada:     endereco: Numero de 0 à 7 que indica a posição da CGRAM que o
 *              caractere será criado.
 *
 *              *buffer: apontador para o vetor de char com tamanho 8 que
 *              guarda cada linha de desenho do caractere que será criado.
 *
 * Saída:       Nenhuma (void)
 * Descrição:   Essa rotina cria um caractere de usuário em uma das 7 posições
 *  disponiveis na CGRAM do display. O caractere criado tem tamanho 8x5 pixel
 *  (8 linhas e 5 colunas), portanto cada valor do vetor buffer representa
 *  uma linha, onde os 3 bits mais significativos de cada valor é desprezado.
 *****************************************************************************/
extern void CriaCaractereLCD(unsigned char endereco, const char *buffer);

extern void EscreveShortLongLCD(unsigned long valor);

/****************************************************** **********************************************
* Function : void PrintNUM_LCD(unsigned long  number)
* Input: value: unsigned long (from 0 to 4294967295) to be written in
* display.
*
* Output: None ( void )
* Description: This routine writes the long number to the display starting from the position
* current memory of the cursor or the memory location chosen with the
* PosicaoCursorLCD () or AddressCursor () functions .
* Ex : PrintNUM_LCD (256)
* 1
* Column -> 1234567890123456
* line 1-> 256
* line 2->
****************************************************** ******************************/
void PrintNUM_LCD(unsigned long  number);

/********************************************************************************************
* Function : void EscreveByteLCD ( unsigned char data, unsigned char row, unsigned char column)
* Input: value: integer (from 0 to 999) to be written in
* display.
*
* Output: None ( void )
* Description: This routine writes the integer number to the display starting from the position
* current memory of the cursor or the memory location chosen with the
* PosicaoCursorLCD () or AddressCursor () functions .
* Ex : WriteByteLCD (256, 1,2)
* 1
* Column -> 1234567890123456
* line 1-> 256
* line 2->
 *****************************************************************************/
extern void EscreveByteLCD(unsigned char data, unsigned char linha, unsigned char coluna);

/********************************************************************************************
* Function : void EscreveWordLCD ( unsigned char data, unsigned char row, unsigned char column)
* Input: value: integer (from 0 to 999) to be written in
* display.
*
* Output: None ( void )
* Description: This routine writes the integer number to the display starting from the position
* current memory of the cursor or the memory location chosen with the
* PosicaoCursorLCD () or AddressCursor () functions .
* Ex : WriteWordLCD (256, 1,2)
* 1
* Column -> 1234567890123456
* line 1-> 00256
* line 2->
 *****************************************************************************/
void EscreveWordLCD(unsigned int data, unsigned char linha,unsigned char coluna);

/********************************************************************************************
* Function : void EscreveLongLCD ( unsigned char data, unsigned char row, unsigned char column)
* Input: value: integer (from 0 to 999999999) to be written in
* display.
*
* Output: None ( void )
* Description: This routine writes the integer number to the display starting from the position
* current memory of the cursor or the memory location chosen with the
* PosicaoCursorLCD () or AddressCursor () functions .
* Ex : WriteLongLCD (256, 1,2)
* 1
* Column -> 1234567890123456
* line 1-> 000000256
* line 2->
 *****************************************************************************/
extern void EscreveLongLCD(unsigned long data, unsigned char linha,unsigned char coluna);

#endif
