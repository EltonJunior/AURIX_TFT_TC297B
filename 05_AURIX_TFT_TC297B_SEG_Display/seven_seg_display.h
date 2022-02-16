/** @file       seven_seg_display.h
 *  @brief      Seven Segment Display File.
 *
 *
 *  @author     Elton Junior
 *  @since      9 de fev de 2022
 *  @version    1.0
 *  @bug        No known bugs.
 */

#ifndef SEVEN_SEG_DISPLAY_H_
#define SEVEN_SEG_DISPLAY_H_

enum{
    NUMBER_0,
    NUMBER_1,
    NUMBER_2,
    NUMBER_3,
    NUMBER_4,
    NUMBER_5,
    NUMBER_6,
    NUMBER_7,
    NUMBER_8,
    NUMBER_9
};

enum{
    DIGIT_1,
    DIGIT_2,
    DIGIT_3,
    DIGIT_4
};

#define SEG_A  &MODULE_P00,0
#define SEG_B  &MODULE_P00,1
#define SEG_C  &MODULE_P00,2
#define SEG_D  &MODULE_P00,3
#define SEG_E  &MODULE_P00,4
#define SEG_F  &MODULE_P00,5
#define SEG_G  &MODULE_P00,6

#define DISP1  &MODULE_P00,7
#define DISP2  &MODULE_P00,8
#define DISP3  &MODULE_P00,9
#define DISP4  &MODULE_P00,10

#define SEG_A_OUTPUT() IfxPort_setPinMode(SEG_A, IfxPort_Mode_outputPushPullGeneral)
#define SEG_A_INPUT()  IfxPort_setPinMode(SEG_A, IfxPort_Mode_inputPullUp)

#define SEG_B_OUTPUT() IfxPort_setPinMode(SEG_B, IfxPort_Mode_outputPushPullGeneral)
#define SEG_B_INPUT()  IfxPort_setPinMode(SEG_B, IfxPort_Mode_inputPullUp)

#define SEG_C_OUTPUT() IfxPort_setPinMode(SEG_C, IfxPort_Mode_outputPushPullGeneral)
#define SEG_C_INPUT()  IfxPort_setPinMode(SEG_C, IfxPort_Mode_inputPullUp)

#define SEG_D_OUTPUT() IfxPort_setPinMode(SEG_D, IfxPort_Mode_outputPushPullGeneral)
#define SEG_D_INPUT()  IfxPort_setPinMode(SEG_D, IfxPort_Mode_inputPullUp)

#define SEG_E_OUTPUT() IfxPort_setPinMode(SEG_E, IfxPort_Mode_outputPushPullGeneral)
#define SEG_E_INPUT()  IfxPort_setPinMode(SEG_E, IfxPort_Mode_inputPullUp)

#define SEG_F_OUTPUT() IfxPort_setPinMode(SEG_F, IfxPort_Mode_outputPushPullGeneral)
#define SEG_F_INPUT()  IfxPort_setPinMode(SEG_F, IfxPort_Mode_inputPullUp)

#define SEG_G_OUTPUT() IfxPort_setPinMode(SEG_G, IfxPort_Mode_outputPushPullGeneral)
#define SEG_G_INPUT()  IfxPort_setPinMode(SEG_G, IfxPort_Mode_inputPullUp)

#define DISP1_OUTPUT() IfxPort_setPinMode(DISP1, IfxPort_Mode_outputPushPullGeneral)
#define DISP1_INPUT()  IfxPort_setPinMode(DISP1, IfxPort_Mode_inputPullUp)

#define DISP2_OUTPUT() IfxPort_setPinMode(DISP2, IfxPort_Mode_outputPushPullGeneral)
#define DISP2_INPUT()  IfxPort_setPinMode(DISP2, IfxPort_Mode_inputPullUp)

#define DISP3_OUTPUT() IfxPort_setPinMode(DISP3, IfxPort_Mode_outputPushPullGeneral)
#define DISP3_INPUT()  IfxPort_setPinMode(DISP3, IfxPort_Mode_inputPullUp)

#define DISP4_OUTPUT() IfxPort_setPinMode(DISP4, IfxPort_Mode_outputPushPullGeneral)
#define DISP4_INPUT()  IfxPort_setPinMode(DISP4, IfxPort_Mode_inputPullUp)

#define SEG_A_ON()      IfxPort_setPinHigh(SEG_A)
#define SEG_A_OFF()     IfxPort_setPinLow(SEG_A)

#define SEG_B_ON()      IfxPort_setPinHigh(SEG_B)
#define SEG_B_OFF()     IfxPort_setPinLow(SEG_B)

#define SEG_C_ON()      IfxPort_setPinHigh(SEG_C)
#define SEG_C_OFF()     IfxPort_setPinLow(SEG_C)

#define SEG_D_ON()      IfxPort_setPinHigh(SEG_D)
#define SEG_D_OFF()     IfxPort_setPinLow(SEG_D)

#define SEG_E_ON()      IfxPort_setPinHigh(SEG_E)
#define SEG_E_OFF()     IfxPort_setPinLow(SEG_E)

#define SEG_F_ON()      IfxPort_setPinHigh(SEG_F)
#define SEG_F_OFF()     IfxPort_setPinLow(SEG_F)

#define SEG_G_ON()      IfxPort_setPinHigh(SEG_G)
#define SEG_G_OFF()     IfxPort_setPinLow(SEG_G)

#define DISP1_ON()      IfxPort_setPinLow(DISP1)
#define DISP1_OFF()     IfxPort_setPinHigh(DISP1)

#define DISP2_ON()      IfxPort_setPinLow(DISP2)
#define DISP2_OFF()     IfxPort_setPinHigh(DISP2)

#define DISP3_ON()      IfxPort_setPinLow(DISP3)
#define DISP3_OFF()     IfxPort_setPinHigh(DISP3)

#define DISP4_ON()      IfxPort_setPinLow(DISP4)
#define DISP4_OFF()     IfxPort_setPinHigh(DISP4)

void Init_Seven_Segment(void);
void Set_Seven_Segment_Value(uint8 digit, uint8 number);
void Seven_Segment_Test(void);

#endif /* SEVEN_SEG_DISPLAY_H_ */
