/*
 * seven_seg_display.c
 *
 *  Created on: 9 de fev de 2022
 *      Author: uidq5744
 */

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "Bsp.h"
#include "seven_seg_display.h"


void Init_Seven_Segment(void){

    SEG_A_OUTPUT();SEG_B_OUTPUT();SEG_C_OUTPUT();SEG_D_OUTPUT();
    SEG_E_OUTPUT();SEG_F_OUTPUT();SEG_G_OUTPUT();

    DISP1_OUTPUT();DISP2_OUTPUT();DISP3_OUTPUT();DISP4_OUTPUT();

}

void Set_Seven_Segment_Value(uint8 digit, uint8 number)
{

    switch(number)
    {
        case NUMBER_0:
            SEG_A_ON();SEG_B_ON();SEG_C_ON();SEG_D_ON();SEG_E_ON();SEG_F_ON();SEG_G_OFF();
            break;
        case NUMBER_1:
            SEG_A_OFF();SEG_B_ON();SEG_C_ON();SEG_D_OFF();SEG_E_OFF();SEG_F_OFF();SEG_G_OFF();
            break;
        case NUMBER_2:
            SEG_A_ON();SEG_B_ON();SEG_C_OFF();SEG_D_ON();SEG_E_ON();SEG_F_OFF();SEG_G_ON();
            break;
        case NUMBER_3:
            SEG_A_ON();SEG_B_ON();SEG_C_ON();SEG_D_ON();SEG_E_OFF();SEG_F_OFF();SEG_G_ON();
            break;
        case NUMBER_4:
            SEG_A_OFF();SEG_B_ON();SEG_C_ON();SEG_D_OFF();SEG_E_OFF();SEG_F_ON();SEG_G_ON();
            break;
        case NUMBER_5:
            SEG_A_ON();SEG_B_OFF();SEG_C_ON();SEG_D_ON();SEG_E_OFF();SEG_F_ON();SEG_G_ON();
            break;
        case NUMBER_6:
            SEG_A_ON();SEG_B_OFF();SEG_C_ON();SEG_D_ON();SEG_E_ON();SEG_F_ON();SEG_G_ON();
            break;
        case NUMBER_7:
            SEG_A_ON();SEG_B_ON();SEG_C_ON();SEG_D_OFF();SEG_E_OFF();SEG_F_OFF();SEG_G_OFF();
            break;
        case NUMBER_8:
            SEG_A_ON();SEG_B_ON();SEG_C_ON();SEG_D_ON();SEG_E_ON();SEG_F_ON();SEG_G_ON();
            break;
        case NUMBER_9:
            SEG_A_ON();SEG_B_ON();SEG_C_ON();SEG_D_ON();SEG_E_OFF();SEG_F_ON();SEG_G_ON();
            break;
        default:
            SEG_A_ON();SEG_B_ON();SEG_C_ON();SEG_D_ON();SEG_E_ON();SEG_F_ON();SEG_G_OFF();
            break;
    }

    (digit == DIGIT_1) ? DISP1_ON() : DISP1_OFF();
    (digit == DIGIT_2) ? DISP2_ON() : DISP2_OFF();
    (digit == DIGIT_3) ? DISP3_ON() : DISP3_OFF();
    (digit == DIGIT_4) ? DISP4_ON() : DISP4_OFF();

}

void Seven_Segment_Test(void){

    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));    /*! Wait 1000 milliseconds            */
    Set_Seven_Segment_Value(DIGIT_1, NUMBER_1);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));    /*! Wait 1000 milliseconds            */
    Set_Seven_Segment_Value(DIGIT_1, NUMBER_2);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));    /*! Wait 1000 milliseconds            */
    Set_Seven_Segment_Value(DIGIT_1, NUMBER_3);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));    /*! Wait 1000 milliseconds           */
    Set_Seven_Segment_Value(DIGIT_1, NUMBER_4);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));    /*! Wait 1000 milliseconds            */
    Set_Seven_Segment_Value(DIGIT_1, NUMBER_5);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));    /*! Wait 1000 milliseconds            */
    Set_Seven_Segment_Value(DIGIT_1, NUMBER_6);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));    /*! Wait 1000 milliseconds            */
    Set_Seven_Segment_Value(DIGIT_1, NUMBER_7);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));    /*! Wait 1000 milliseconds            */
    Set_Seven_Segment_Value(DIGIT_1, NUMBER_8);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));    /*! Wait 1000 milliseconds            */
    Set_Seven_Segment_Value(DIGIT_1, NUMBER_9);
    waitTime(IfxStm_getTicksFromMilliseconds(BSP_DEFAULT_TIMER, 1000));    /*! Wait 1000 milliseconds            */
}
