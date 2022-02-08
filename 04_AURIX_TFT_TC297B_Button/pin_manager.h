/** @file       pin_manager.c
 *  @brief      Pin Manager File.
 *
 *
 *  @author     Elton Junior
 *  @since      5 de fev de 2022
 *  @version    1.0
 *  @bug        No known bugs.
 */

#ifndef PIN_MANAGER_H_
#define PIN_MANAGER_H_

/*********************************************************************************************************************/
/*-----------------------------------------------------Includes------------------------------------------------------*/
/*********************************************************************************************************************/
#include "IfxPort.h"
#include "Bsp.h"

/*********************************************************************************************************************/
/*------------------------------------------------------Macros-------------------------------------------------------*/
/*********************************************************************************************************************/
#define LED_D00    &MODULE_P00,0                                           /* P00,0 : Port, Pin definition       */
#define BUTTON     &MODULE_P00,1                                           /* P00,1 : Port, Pin definition       */

#define WAIT_TIME   500                                                     /* Wait time constant in milliseconds   */


/**
 * This function will configure the pin as output/input.
 *
 * @param .
 *
 * @return The configuration of pins.
 *
 */
void PIN_MANAGER_Initialize(void);

#endif /* PIN_MANAGER_H_ */
