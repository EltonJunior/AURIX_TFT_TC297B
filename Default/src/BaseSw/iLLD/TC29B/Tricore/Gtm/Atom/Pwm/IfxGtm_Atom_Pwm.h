/**
 * \file IfxGtm_Atom_Pwm.h
 * \brief GTM PWM details
 * \ingroup IfxLld_Gtm
 *
 * \version iLLD_1_0_1_8_0
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Gtm_Atom_Pwm_Usage How to use the GTM ATOM PWM Driver
 * \ingroup IfxLld_Gtm_Atom_Pwm
 *
 * This interface allows to generate simple PWM signal on a ATOM out put and can generate interrupts if enabled.
 * this output can also be routed to port pin if required.
 *
 * \section Preparation Preparation
 * \subsection Include Include Files
 *
 * Include following header file into your C code:
 * \code
 *     #include <Gtm/Atom/Pwm/IfxGtm_Atom_Pwm.h>
 * \endcode
 *
 * \subsection Variables Variables
 * define global variables if necessary
 *
 * \code
 * Ifx_GTM *gtm = &MODULE_GTM;
 * #define ATOM0_CH0_PRIO 20
 * \endcode
 *
 * \subsection Interrupts Interrupts
 * define Interrupts if needed
 *
 * \code
 * IFX_INTERRUPT(ATOM0Ch0_ISR, 0, ATOM0_CH0_PRIO)
 * {}
 * \endcode
 *
 * \subsection Initialization Initialization
 *
 * \code
 * // install interrupt handlers
 * IfxCpu_Irq_installInterruptHandler (ATOM0Ch0_ISR, ATOM0_CH0_PRIO);
 *
 * // enable GTM clock
 * {
 *     float32 frequency = IfxGtm_Cmu_getModuleFrequency(gtm);
 *     // Enables the GTM
 *     IfxGtm_enable(gtm);
 *     // Set the global clock frequency to the max
 *     IfxGtm_Cmu_setGclkFrequency(gtm, frequency);
 *     // Set the CMU CLK0
 *     IfxGtm_Cmu_setClkFrequency(gtm, IfxGtm_Cmu_Clk_0, frequency);
 *     // FXCLK: used by TOM and CLK0: used by ATOM
 *     IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_FXCLK | IFXGTM_CMU_CLKEN_CLK0);
 * }
 *
 * // initialise ATOM
 * IfxGtm_Atom_Pwm_Config atomConfig;	\\configuration structure
 * IfxGtm_Atom_Pwm_Driver atomHandle;	\\ handle
 *
 * IfxGtm_Atom_Pwm_initConfig(&atomConfig, gtm);
 *
 * atomConfig.tomChannel  = IfxGtm_Tom_Ch_0;
 * atomConfig.period                   = 20;
 * atomConfig.dutyCycle              = 10;
 * atomConfig.interrupt.ccu0Enabled = TRUE;
 * atomConfig.interrupt.isrPriority = ATOM0_CH0_PRIO;
 * atomConfig.pin.outputPin = &IfxGtm_ATOM0_0_TOUT0_P02_0_OUT;
 *
 * IfxGtm_Atom_Pwm_init(&atomHandle, &atomConfig);
 * \endcode
 *
 * ATOM will be now generating a PWM signal on the selected port pin while generating selected interrupt according to above configured period and duty cycle.
 *
 * \defgroup IfxLld_Gtm_Atom_Pwm ATOM PWM Interface Driver
 * \ingroup IfxLld_Gtm_Atom
 * \defgroup IfxLld_Gtm_Atom_Pwm_DataStructures ATOM PWM DataStructures
 * \ingroup IfxLld_Gtm_Atom_Pwm
 * \defgroup IfxLld_Gtm_Atom_Pwm_Pwm_Functions Pwm Functions
 * \ingroup IfxLld_Gtm_Atom_Pwm
 */

#ifndef IFXGTM_ATOM_PWM_H
#define IFXGTM_ATOM_PWM_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_PinMap/IfxGtm_PinMap.h"
#include "Gtm/Std/IfxGtm_Atom.h"
#include "Gtm/Std/IfxGtm_Cmu.h"
#include "Cpu/Std/IfxCpu.h"

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Gtm_Atom_Pwm_DataStructures
 * \{ */
/** \brief configuration structure for interrupts
 */
typedef struct
{
    boolean        ccu0Enabled;       /**< \brief Enable/Disable choice for CCU0 trigger interrupt */
    boolean        ccu1Enabled;       /**< \brief Enable/Disable choice for CCU1 trigger interrupt */
    IfxGtm_IrqMode mode;              /**< \brief IRQ mode of interrupt */
    IfxSrc_Tos     isrProvider;       /**< \brief Type of Service for Ccu0/1 interrupt */
    Ifx_Priority   isrPriority;       /**< \brief Priority for Ccu0/1 interrupt */
} IfxGtm_Atom_Pwm_Interrupt;

/** \brief configuration structure for output pin
 */
typedef struct
{
    IfxGtm_Atom_ToutMap *outputPin;        /**< \brief output pin */
    IfxPort_OutputMode   outputMode;       /**< \brief Output mode */
    IfxPort_PadDriver    padDriver;        /**< \brief Pad driver */
} IfxGtm_Atom_Pwm_pin;

/** \} */

/** \addtogroup IfxLld_Gtm_Atom_Pwm_DataStructures
 * \{ */
/** \brief Configuration structure
 */
typedef struct
{
    Ifx_GTM                  *gtm;                            /**< \brief Pointer to GTM module */
    IfxGtm_Atom               atom;                           /**< \brief Index of the ATOM object used */
    IfxGtm_Atom_Ch            atomChannel;                    /**< \brief ATOM channel used for the timer */
    IfxGtm_Atom_Mode          mode;                           /**< \brief Atom mode of operation */
    uint32                    period;                         /**< \brief Period */
    uint32                    dutyCycle;                      /**< \brief Duty Cycle */
    Ifx_ActiveState           signalLevel;                    /**< \brief Signal Level */
    boolean                   oneShotModeEnabled;             /**< \brief Enable/Disable the one shot mode */
    boolean                   synchronousUpdateEnabled;       /**< \brief Synchronous or Asynchronous update */
    boolean                   immediateStartEnabled;          /**< \brief enable immediate start after init */
    IfxGtm_Atom_Pwm_Interrupt interrupt;                      /**< \brief configuration structure for interrupt */
    IfxGtm_Atom_Pwm_pin       pin;                            /**< \brief configuration structure for output pin */
} IfxGtm_Atom_Pwm_Config;

/** \brief Driver Handle
 */
typedef struct
{
    Ifx_GTM          *gtm;               /**< \brief Pointer to GTM module */
    IfxGtm_Atom       atomIndex;         /**< \brief Index of the ATOM object used */
    IfxGtm_Atom_Ch    atomChannel;       /**< \brief ATOM channel used for the timer */
    Ifx_GTM_ATOM     *atom;              /**< \brief Pointer to the ATOM object */
    Ifx_GTM_ATOM_AGC *agc;               /**< \brief Pointer to the AGC object */
    IfxGtm_Atom_Mode  mode;              /**< \brief Atom mode of operation */
} IfxGtm_Atom_Pwm_Driver;

/** \} */

/** \addtogroup IfxLld_Gtm_Atom_Pwm_Pwm_Functions
 * \{ */

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Initialises the Timer object
 * \param driver ATOM Handle
 * \param config Configuration structure for ATOM
 * \return TRUE on success else FALSE
 */
IFX_EXTERN boolean IfxGtm_Atom_Pwm_init(IfxGtm_Atom_Pwm_Driver *driver, const IfxGtm_Atom_Pwm_Config *config);

/** \brief Initializes the configuration structure to default
 * \param config This parameter is Initialised by the function
 * \param gtm Pointer to GTM module
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Pwm_initConfig(IfxGtm_Atom_Pwm_Config *config, Ifx_GTM *gtm);

/** \brief Starts the PWM generation from the configured channel.
 * \param driver handle for the PWM device.
 * \param immediate immediate start or not.
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Pwm_start(IfxGtm_Atom_Pwm_Driver *driver, boolean immediate);

/** \brief Stops the PWM generation from the configured channel
 * \param driver handle for the PWM device
 * \param immediate immediate start or not.
 * \return None
 */
IFX_EXTERN void IfxGtm_Atom_Pwm_stop(IfxGtm_Atom_Pwm_Driver *driver, boolean immediate);

/** \} */

#endif /* IFXGTM_ATOM_PWM_H */
