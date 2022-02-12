/** @file       pin_manager.c
 *  @brief      Pin Manager File.
 *
 *
 *  @author     Elton Junior
 *  @since      5 de fev de 2022
 *  @version    1.0
 *  @bug        No known bugs.
 */

#include "pin_manager.h"

/**
 * This function will configure the pin as output/input.
 *
 * @param .
 *
 * @return The configuration of pins.
 *
 */
void PIN_MANAGER_Initialize(void)
{
    /* Initialization of the LED used in this example */
    IfxPort_setPinModeOutput(LED_D00, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);

    /* Setup the port pin connected to the push button to input mode. This function can be used to initialize any
         * port to input mode by just specifying the port number as illustrated.
         */
        IfxPort_setPinMode(BUTTON, IfxPort_Mode_inputPullUp);

    /* Switch OFF the LED (low-level active) */
    IfxPort_setPinHigh(LED_D00);
}
