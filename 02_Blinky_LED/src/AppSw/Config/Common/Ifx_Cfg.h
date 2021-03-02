/**
 * \file Ifx_Cfg.h
 * \brief Configuration.
 *
 * \version iLLD_Demos_1_0_1_8_0
 * \copyright Copyright (c) 2014 Infineon Technologies AG. All rights reserved.
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
 *
 * \defgroup IfxLld_Demo_ScuClockDemo_SrcDoc_IlldConfig iLLD configuration
 * \ingroup IfxLld_Demo_ScuClockDemo_SrcDoc
 */

#ifndef IFX_CFG_H
#define IFX_CFG_H

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Demo_ScuClockDemo_SrcDoc_IlldConfig
 * \{ */

/*______________________________________________________________________________
** Configuration for IfxScu_cfg.h
**____________________________________________________________________________*/
/**
 * \name Frequency configuration
 * \{
 */
#define IFX_CFG_SCU_XTAL_FREQUENCY (20000000)  /**< \copydoc IFX_CFG_SCU_XTAL_FREQUENCY */
#define IFX_CFG_SCU_PLL_FREQUENCY  (200000000) /**< \copydoc IFX_CFG_SCU_PLL_FREQUENCY */
#define IFXCPU_CSTART_CCU_INIT_HOOK()          /**< \copydoc IFXCPU_CSTART_CCU_INIT_HOOK */
/** \} */

/** \} */

#endif /* IFX_CFG_H */
