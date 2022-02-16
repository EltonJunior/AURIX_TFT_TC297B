/** @file           displayLCD.c
 *  @dependencies   See file " displayLCD.h "
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

/** INCLUDES **********************************************************/
#include "pin_manager.h"
#include "displayLCD.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/** FUNCTIONS ************************************************************/

void delay_ms(unsigned char Cnt2)
{
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, Cnt2));    /*! Wait in milliseconds            */
}

void delay_us(unsigned char Cnt2)
{
    waitTime(IfxStm_getTicksFromMicroseconds(BSP_DEFAULT_TIMER, Cnt2));    /*! Wait in microseconds            */
}

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
void ConfiguraLCD(void)
{
    /// Configure the control pins (RW,RS,E) as output.
    LCD_RW_OUTPUT();
    LCD_RS_OUTPUT();
    LCD_E_OUTPUT();

    /// Set the data pins (D4,D5,D6,D7) as output.
    LCD_D4_OUTPUT();
    LCD_D5_OUTPUT();
    LCD_D6_OUTPUT();
    LCD_D7_OUTPUT();

    /// Start of LCD display initialization routine
    /// Wait for times and send the command 0b0011XXXX 3 times as described in the datasheet
    /// from the HD44780 or SPLC780D controller

    //Select Control pins for command writing
    RW_PIN_LOW(); // write=0, read=1
    RS_PIN_LOW(); // command=0, data=1
    E_PIN_LOW(); // disable=0, enable=1

    /// select data pins with initialization command 0b0011 in Nibble -High
    ///(the most significant 4 bits of data), Nibble-Low bits are Don't care
    D7_PIN_LOW();
    D6_PIN_LOW();
    D5_PIN_HIGH();
    D4_PIN_HIGH();

    ///Step 1: Sending the initialization command 0b0011

    /// Initial delay of 15ms after powering LCD: Vdd > 4.5V
    delay_ms(15);

    ///Enables reading the command by the LCD, through the enable pin , for that,
    ///a 1ms pulse with falling edge is performed
    E_PIN_HIGH();
    delay_us(20);
    E_PIN_LOW();
    delay_us(20);

    ///Step 2: Sending the initialization command 0b0011

    /// Delay of at least 4.1ms
    delay_ms(5);

    ///Pulse on Enable pin to enable LCD reading on falling edge
    E_PIN_HIGH();
    delay_us(20);
    E_PIN_LOW();
    delay_us(20);

    ///Step 3: Sending the initialization command 0b0011

    /// Delay of at least 100us
    delay_us(50);

    ///Pulse on Enable pin to enable LCD reading on falling edge
    E_PIN_HIGH();
    delay_us(20);
    E_PIN_LOW();
    delay_us(20);

    ///Step 4: Send Configuration 0b0010 in Nibble -High
    D7_PIN_LOW();
    D6_PIN_LOW();
    D5_PIN_HIGH();
    D4_PIN_LOW();


    ///Pulse on Enable pin to enable LCD reading on falling edge
    E_PIN_HIGH();
    delay_us(20);
    E_PIN_LOW();
    delay_us(20);


    //Sending LCD Configuration commands
    EscreveComandoLCD(0x28);  // Function Set: 4bit interface, 2 lines, Font 5x7
    EscreveComandoLCD(0x04);  // Entry mode set: Increment, Shift OFF
    EscreveComandoLCD(0x0C);  // Display Control: Display ON, Cursor ON, Blink OFF
    EscreveComandoLCD(0x01);  // Clear display

}

/******************************************************************************
* Function : void EscreveComandoLCD ( unsigned char cmd )
* Input: cmd : command that will be sent to the LCD
* Output: None ( void )
* Description: (Write a command to the LCD)
* Writes a command to the LCD display.
 *****************************************************************************/
void EscreveComandoLCD(unsigned char cmd)
{
    //Select Control pins for command writing
    RW_PIN_LOW(); // write=0, read=1
    RS_PIN_LOW(); // command=0, data=1
    E_PIN_LOW(); // disable=0, enable=1

    ///Select Data pins: Nibble -High
    if(cmd&0x10){D4_PIN_HIGH();}
    else {D4_PIN_LOW();}
    if(cmd&0x20){D5_PIN_HIGH();}
    else {D5_PIN_LOW();}
    if(cmd&0x40){D6_PIN_HIGH();}
    else {D6_PIN_LOW();}
    if(cmd&0x80){D7_PIN_HIGH();}
    else {D7_PIN_LOW();}

    ///Pulse on Enable pin to enable LCD reading on falling edge
    E_PIN_HIGH();
    delay_us(20);
    E_PIN_LOW();
    delay_us(20);

    ///Select Data pins: Nibble-Low
    if(cmd&0x01){D4_PIN_HIGH();}
    else {D4_PIN_LOW();}
    if(cmd&0x02){D5_PIN_HIGH();}
    else {D5_PIN_LOW();}
    if(cmd&0x04){D6_PIN_HIGH();}
    else {D6_PIN_LOW();}
    if(cmd&0x08){D7_PIN_HIGH();}
    else {D7_PIN_LOW();}

    ///Pulse on Enable pin to enable LCD reading on falling edge
    E_PIN_HIGH();
    delay_us(20);
    E_PIN_LOW();
    delay_us(20);

    //Like the Clear Display(0x01) and Cursor Home(0b0000001x) commands,
//take longer to run, about about 1.5ms.
// A longer delay is guaranteed if they are carried out
    if (cmd==0x01 || cmd==0x02 || cmd==0x03)
    { delay_ms(2); }
}

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
void EnderecoCursor(unsigned char endereco)
{
    //Select Control pins for command writing
    RW_PIN_LOW(); // write=0, read=1
    RS_PIN_LOW(); // command=0, data=1

    ///Select Data pins: Nibble -High
    D7_PIN_HIGH();
    if(endereco&0x10){D4_PIN_HIGH();}
    else {D4_PIN_LOW();}
    if(endereco&0x20){D5_PIN_HIGH();}
    else {D5_PIN_LOW();}
    if(endereco&0x40){D6_PIN_HIGH();}
    else {D6_PIN_LOW();}

    ///Pulse on Enable pin to enable LCD reading on falling edge
    E_PIN_HIGH();
    delay_us(20);
    E_PIN_LOW();
    delay_us(20);

    ///Select Data pins: Nibble-Low
    if(endereco&0x01){D4_PIN_HIGH();}
    else {D4_PIN_LOW();}
    if(endereco&0x02){D5_PIN_HIGH();}
    else {D5_PIN_LOW();}
    if(endereco&0x04){D6_PIN_HIGH();}
    else {D6_PIN_LOW();}
    if(endereco&0x08){D7_PIN_HIGH();}
    else {D7_PIN_LOW();}

    ///Pulse on Enable pin to enable LCD reading on falling edge
    E_PIN_HIGH();
    delay_us(20);
    E_PIN_LOW();
    delay_us(20);
}

/******************************************************************************
* Function : void PosicaoCursorLCD ( unsigned char row, unsigned char column)
* Input: line: number from 1 to 4 of the line where the cursor is to be placed
*
* column: number from 1 to 16 column row where you want to leave the cursor
*
* Output: None ( void )
* Description: This routine places the cursor on the display screen, on the line
* and desired column. The following writing commands will start from
* from the position chosen by this function
 *****************************************************************************/
void PosicaoCursorLCD(unsigned char linha, unsigned char coluna)
{
    // start address of each line
    #define linha1  0x00
    #define linha2  0x40
    #define linha3  0x14
    #define linha4  0x54

    unsigned char EnderecoLCD = 0x00;

    coluna--;

    if (coluna >= 0)
    {
        //Calculate the display's RAM memory address that should be used
        //to position the cursor on the desired row and column
        switch (linha)
        {
            case 1:
                EnderecoLCD = linha1 + coluna;
                EnderecoCursor(EnderecoLCD);
            break;

            case 2:
                EnderecoLCD = linha2 + coluna;
                EnderecoCursor(EnderecoLCD);
            break;

            case 3:
                EnderecoLCD = linha3 + coluna;
                EnderecoCursor(EnderecoLCD);
            break;

            case 4:
                EnderecoLCD = linha4 + coluna;
                EnderecoCursor(EnderecoLCD);
            break;

            default:
                EnderecoLCD = linha1;
            break;
        }
    }
    else
    {
        EnderecoLCD = linha1;
    }
}

/******************************************************************************
* Function : void EscreveCaractereLCD ( unsigned char data)
* Input: data: Data byte to be written to LCD RAM memory
* Output: None ( void )
* Description: (Write a Data byte to the LCD)
* This routine writes the character byte to the display from the position
* current memory of the cursor or the memory location chosen with the
* PosicaoCursorLCD () or EnderecoCursor () functions .
 *****************************************************************************/
void EscreveCaractereLCD(char data)
{
    //Select Control pins for command writing
    RW_PIN_LOW(); // write=0, read=1
    RS_PIN_HIGH(); // command=0, data=1
    E_PIN_LOW(); // disable=0, enable=1

    ///Select Data pins: Nibble -High
    if(data&0x10){D4_PIN_HIGH();}
    else {D4_PIN_LOW();}
    if(data&0x20){D5_PIN_HIGH();}
    else {D5_PIN_LOW();}
    if(data&0x40){D6_PIN_HIGH();}
    else {D6_PIN_LOW();}
    if(data&0x80){D7_PIN_HIGH();}
    else {D7_PIN_LOW();}

    ///Pulse on Enable pin to enable LCD reading on falling edge
    E_PIN_HIGH();
    delay_us(20);
    E_PIN_LOW();
    delay_us(20);


    ///Select Data pins: Nibble-Low
    if(data&0x01){D4_PIN_HIGH();}
    else {D4_PIN_LOW();}
    if(data&0x02){D5_PIN_HIGH();}
    else {D5_PIN_LOW();}
    if(data&0x04){D6_PIN_HIGH();}
    else {D6_PIN_LOW();}
    if(data&0x08){D7_PIN_HIGH();}
    else {D7_PIN_LOW();}

    ///Pulse on Enable pin to enable LCD reading on falling edge
    E_PIN_HIGH();
    delay_us(20);
    E_PIN_LOW();
    delay_us(20);
}

/******************************************************************************
* Function : void EscreveInteiroLCD ( int value)
* Input: value: signed integer (from -32768 to 32767) to be written in the
* display.
*
* Output: None ( void )
* Description: This routine writes the integer number to the display starting from the position
* current memory of the cursor or the memory location chosen with the
* PosicaoCursorLCD () or EnderecoCursor () functions .
 *****************************************************************************/
void EscreveInteiroLCD(int valor)
{
    char texto[7] = "000000";
    (void)itoa(valor,texto, 10);
    EscreveFraseRamLCD(texto);
}

/******************************************************************************
* Function : inline void swap(char *x, char *y)
* Input: value: two character address .
*
* Output: None ( void )
* Description: This function puts the value of x into y and y into x.
 *****************************************************************************/
inline void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}

/******************************************************************************
* Function : Reverse(char *buffer, int i , int j)
* Input: value : string .
*
* Output : inverse character sequence
* Description: This function reverses the writing of the received buffer.
 *****************************************************************************/
char* Reverse(char *buffer, int i, int j)
{
    while (i < j)
        swap(&buffer[i++], &buffer[j--]);

    return buffer;
}

/******************************************************************************
* Function : char* itoa (int value, char* buffer, int base);
 * Input: value: converts an integer to character .
*
* Output : character string
* Description: This function converts an integer to character .
 *****************************************************************************/
char* itoa(int value, char* buffer, int base)
{
    int n, i;
    // invalid input
    if (base < 2 || base > 32)
        return buffer;

    // consider absolute value of number
    n = abs(value);

    i = 0;
    while (n)
    {
        int r = n % base;

        if (r >= 10)
            buffer[i++] = (char)(65 + (r - 10));
        else
            buffer[i++] = (char)(48 + r);

        n = n / base;
    }

    // if number is 0
    if (i == 0)
        buffer[i++] = '0';

    // If base is 10 and value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10)
        buffer[i++] = '-';

    buffer[i] = '\0'; // null terminate string

    /// reverse the string and return it
    return Reverse(buffer, 0, i - 1);
}

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
void EscreveFloatLCD(float valor, char formatacao)
{
    int numInt = 0;     /// save entire part
    float numFloat = 0; /// Guard fractional part
    char n;             /// command counter for

    /// Write integer part
    numInt = (int)valor;
    EscreveInteiroLCD(numInt);

    /// Write the decimal places indicated in the formatting
    if( formatacao > 0 )
    {
        EscreveCaractereLCD('.');
        /// Separate fractional part
        numFloat = (valor - numInt);
        /// If NumFloat is negative, correct the sign
        numFloat = (float)(abs(numFloat));

        /// Make sure you only write up to 5 decimal places
        if(formatacao>4)
            {formatacao=4;}

        /// Calculate decimal places
        for (n = 0; n<formatacao; n++)
        {
            numFloat *= 10;
            /// Write zeros after the comma
            if(numFloat<1)
            {
                EscreveCaractereLCD('0');
            }
        }
        /// Write fractional part
        EscreveInteiroLCD((int)numFloat);
    }
}

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
void EscreveFraseRamLCD(char *buffer)
{
    while(*buffer)      /// write data to LCD until it finds null character
    {
        EscreveCaractereLCD(*buffer); /// write character to LCD
        buffer++;       /// increment pointer
    }
}

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
void EscreveFraseLCD(const char *buffer)
{
    while(*buffer)                      /// write data to LCD until it finds null character
    {
        EscreveCaractereLCD(*buffer);   /// write character to LCD
        buffer++;                       /// increment pointer
    }
}

/****************************************************** *********************************
* Function : void CriaCaractereLCD ( unsigned char endereco , const char *buffer)
* Input: address : Number from 0 to 7 that indicates the position of the CGRAM that the
* character will be created.
*
* *buffer: pointer to the char array with size 8 that
* saves each drawing line of the character that will be created.
*
* Output: None ( void )
* Description: This routine creates a user character in one of 7 positions
* available in the CGRAM of the display. The character created has a size of 8x5 pixels
* (8 rows and 5 columns), so each buffer vector value represents
* a line, where the 3 most significant bits of each value are discarded.
 ****************************************************** ******************************/
void CriaCaractereLCD(unsigned char endereco, const char *buffer)
{
    unsigned char cmd ; // save command to be sent to LCD
    unsigned char n = 0; // for command counter

    //Depending on the address value , select the correct command
    // Make sure that the address only has values from 0 to 7
    endereco = endereco & 0x07;

    switch (endereco)
    {   case 0: cmd = 0x40;   break;
        case 1: cmd = 0x48;   break;
        case 2: cmd = 0x50;   break;
        case 3: cmd = 0x58;   break;
        case 4: cmd = 0x60;   break;
        case 5: cmd = 0x68;   break;
        case 6: cmd = 0x70;   break;
        case 7: cmd = 0x78;   break;
        default:cmd = 0x40;   break;
    }
    //Writing command in CGRAM ( custom character creation )
    EscreveComandoLCD(cmd);

    //Write each character line with the sequence of buffer values
    for(n=0; n<8; n++)
    {
        EscreveCaractereLCD(*buffer); // write character to LCD
        buffer++; // increment pointer
    }

    //Command to exit character creation mode and position cursor
    //in row 1, column 1 of the screen.
    EnderecoCursor(0x00);

}

void EscreveShortLongLCD(unsigned long valor)
{
    char texto[9] = "00000000";
    //ultoa(texto,valor, 10);
    snprintf(texto, 10, " %ld", valor);
    EscreveFraseRamLCD(texto);
}

/****************************************************** **********************************************
* Function : void PrintNUM_LCD(unsigned long  number)
* Input: value: unsigned long (from 0 to 4294967295) to be written in
* display.
*
* Output: None ( void )
* Description: This routine writes the long number to the display starting from the position
* current memory of the cursor or the memory location chosen with the
* PosicaoCursorLCD () or EnderecoCursor () functions .
* Ex : PrintNUM_LCD (256)
* 1
* Column -> 1234567890123456
* line 1-> 256
* line 2->
****************************************************** ******************************/
void PrintNUM_LCD(unsigned long  number)
{
    /********* Maximum length of Number (Decimal) = 10 **********/
    unsigned int unit=0;
    unsigned char numbers[]={'0','1','2','3','4','5','6','7','8','9'};
    unsigned char strNum[]={0,0,0,0,0,0,0,0,0,0};
    unsigned long i=0, j=0;

    while(number > 9)
    {
        unit = (unsigned int)(number % 10);
        strNum[i] = (unsigned char)(unit);
        number = number/10;
        i++;
    }
    strNum[i] = (unsigned int) number;

    for(j=i;j>-1;j--)
    {
        EscreveCaractereLCD(numbers[strNum[j]]);
    }
}

/****************************************************** **********************************************
* Function : void EscreveByteLCD ( unsigned char data, unsigned char row, unsigned char column)
* Input: value: integer (from 0 to 999) to be written in
* display.
*
* Output: None ( void )
* Description: This routine writes the integer number to the display starting from the position
* current memory of the cursor or the memory location chosen with the
* PosicaoCursorLCD () or EnderecoCursor () functions .
* Ex : WriteByteLCD (256, 1,2)
* 1
* Column -> 1234567890123456
* line 1-> 256
* line 2->
****************************************************** ******************************/
void EscreveByteLCD(unsigned char data, unsigned char linha, unsigned char coluna)
{
    unsigned char _i = 2;
    unsigned char _j = 0;
    unsigned char ASCII[3];

    ASCII[0] = 0x20;
    ASCII[1] = 0x20;
    ASCII[2] = 0x20;

    while (data>=10)
        {
            ASCII[_i] = data%10;
            data = data/10;
            ASCII[_i] = ASCII[_i]+0x30;
            --_i;
        }
    ASCII[_i] = data+0x30;
    PosicaoCursorLCD (linha,coluna);
    while(_j<3)
        {
            EscreveCaractereLCD(ASCII[_j]);
            ++_j;
        }
}

/****************************************************************************************************
* Function : void EscreveWordLCD ( unsigned char data, unsigned char row, unsigned char column)
* Input: value: integer (from 0 to 999) to be written in
* display.
*
* Output: None ( void )
* Description: This routine writes the integer number to the display starting from the position
* current memory of the cursor or the memory location chosen with the
* PosicaoCursorLCD () or EnderecoCursor () functions .
* Ex : WriteWordLCD (256, 1,2)
* 1
* Column -> 1234567890123456
* line 1-> 00256
* line 2->
************************************************************************************/
void EscreveWordLCD(unsigned int data, unsigned char linha,unsigned char coluna)
{
    char _i = 4;
    char _j = 0;
    unsigned int ASCII[5];
    ASCII[0] = 0x20;
    ASCII[1] = 0x20;
    ASCII[2] = 0x20;
    ASCII[3] = 0x20;
    ASCII[4] = 0x20;

    while (data>=10)
    {
        ASCII[_i] = (unsigned int)data%10;
        data = data/10;
        ASCII[_i] = ASCII[_i]+0x30;
        --_i;
    }
    ASCII[_i] = data+0x30;
    PosicaoCursorLCD (linha,coluna);
    while(_j<5)
    {
        EscreveCaractereLCD((char)(ASCII[_j]));
        ++_j;
    }
}

/****************************************************** **********************************************
* Function : void EscreveLongLCD ( unsigned char data, unsigned char row, unsigned char column)
* Input: value: integer (from 0 to 999999999) to be written in
* display.
*
* Output: None ( void )
* Description: This routine writes the integer number to the display starting from the position
* current memory of the cursor or the memory location chosen with the
* PosicaoCursorLCD () or EnderecoCursor () functions .
* Ex : WriteLongLCD (256, 1,2)
* 1
* Column -> 1234567890123456
* line 1-> 000000256
* line 2->
************************************************************************************/
void EscreveLongLCD(unsigned long data, unsigned char linha,unsigned char coluna)
{
    char _i = 8;
    char _j = 0;
    unsigned char ASCII[9];
    ASCII[0] = 0x20;
    ASCII[1] = 0x20;
    ASCII[2] = 0x20;
    ASCII[3] = 0x20;
    ASCII[4] = 0x20;
    ASCII[5] = 0x20;
    ASCII[6] = 0x20;
    ASCII[7] = 0x20;
    ASCII[8] = 0x20;

    while (data>=10)
        {
            ASCII[_i] = (unsigned char)data%10;
            data = data/10;
            ASCII[_i] = ASCII[_i]+0x30;
            --_i;
        }
    ASCII[_i] = (unsigned char)(data+0x30);
    PosicaoCursorLCD (linha,coluna);
    while(_j<9)
        {
            EscreveCaractereLCD(ASCII[_j]);
            ++_j;

        }
}

