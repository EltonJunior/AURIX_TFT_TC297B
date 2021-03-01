/**
 * \file IfxMultican.c
 * \brief MULTICAN  basic functionality
 *
 * \version iLLD_1_0_1_8_0
 * \copyright Copyright (c) 2017 Infineon Technologies AG. All rights reserved.
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
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxMultican.h"

/******************************************************************************/
/*-----------------------Private Function Prototypes--------------------------*/
/******************************************************************************/

/** \brief Do actual long frame reading from the message object
 * \param mcan Specifies the CAN module
 * \param msgObjId Specifies the message object index. Range = [0, \ref IFXMULTICAN_NUM_MESSAGE_OBJECTS - 1]
 * \param msg This parameter is filled in by the function with the received message. Also when reading is not successful.
 * \param data Pointer to data (in words)
 * \return None
 */
IFX_STATIC void IfxMultican_MsgObj_doReadLongFrame(Ifx_CAN *mcan, IfxMultican_MsgObjId msgObjId, IfxMultican_Message *msg, uint32 *data);

/** \brief Do actual message reading from the message object
 * \param hwObj Pointer to CAN message object registers
 * \param msg This parameter is filled in by the function with the received message. Also when reading is not successful.
 * \return None
 */
IFX_STATIC void IfxMultican_MsgObj_doReadMessage(Ifx_CAN_MO *hwObj, IfxMultican_Message *msg);

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

boolean IfxMultican_MsgObj_cancelSend(Ifx_CAN_MO *hwObj)
{
    boolean         result = FALSE;
    Ifx_CAN_MO_CTR  ctr;
    Ifx_CAN_MO_STAT stat;

    stat.U = hwObj->STAT.U;

    if ((stat.B.TXRQ != 0) && (stat.B.NEWDAT != 0))
    {
        ctr.U          = 0;
        ctr.B.RESRTSEL = 1; /* take out from transmission */
        hwObj->CTR.U   = ctr.U;
        result         = TRUE;
    }

    return result;
}


void IfxMultican_MsgObj_clearStatusFlag(Ifx_CAN_MO *hwObj, IfxMultican_MsgObjStatusFlag flag)
{
    Ifx_CAN_MO_CTR ctr;
    ctr.U        = 0;
    ctr.U        = 1U << flag;

    hwObj->CTR.U = ctr.U;
}


void IfxMultican_MsgObj_deinit(Ifx_CAN *mcan, IfxMultican_MsgObjId msgObjId)
{
    Ifx_CAN_MO *hwObj = IfxMultican_MsgObj_getPointer(mcan, msgObjId);
    /* Remove the message object from any node */
    /* Append message object to the end of the list */
    IfxMultican_setListCommand(mcan, 0x2, 0, msgObjId);

    hwObj->CTR.U   = 0x0000FFFFUL; /* to be written first */

    hwObj->FCR.U   = 0x00000000UL;
    hwObj->FGPR.U  = 0x00000000UL;
    hwObj->IPR.U   = 0x00000000UL;
    hwObj->AMR.U   = 0x3FFFFFFFUL;
    hwObj->DATAL.U = 0x00000000UL;
    hwObj->DATAH.U = 0x00000000UL;
    hwObj->AR.U    = 0x00000000UL;
}


IFX_STATIC void IfxMultican_MsgObj_doReadLongFrame(Ifx_CAN *mcan, IfxMultican_MsgObjId msgObjId, IfxMultican_Message *msg, uint32 *data)
{
    Ifx_CAN_MO          *hwObj       = IfxMultican_MsgObj_getPointer(mcan, msgObjId);

    IfxMultican_MsgObjId botMsgObjId = hwObj->FGPR.B.BOT;
    Ifx_CAN_MO          *hwBotObj    = IfxMultican_MsgObj_getPointer(mcan, botMsgObjId);

    IfxMultican_MsgObjId topMsgObjId = hwObj->FGPR.B.TOP;
    Ifx_CAN_MO          *hwTopObj    = IfxMultican_MsgObj_getPointer(mcan, topMsgObjId);

    /* for standard message object and FIFO message objects*/
    IfxMultican_MsgObj_clearStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_newData);

    /* copy the length code from hardware */
    IfxMultican_DataLengthCode lengthCode = IfxMultican_MsgObj_getDataLengthCode(hwObj);

    /* read the data from the data registers */
    if (lengthCode > IfxMultican_DataLengthCode_0) /* no.of bytes 0 to 8 */
    {
        *data++ = hwObj->DATAL.U;
        *data++ = hwObj->DATAH.U;
    }

    /* read from bottom message object extended data registers */
    if (lengthCode > IfxMultican_DataLengthCode_8)
    {
        *data++ = hwBotObj->EDATA0.U;
    }

    if (lengthCode > IfxMultican_DataLengthCode_12)
    {
        *data++ = hwBotObj->EDATA1.U;
    }

    if (lengthCode > IfxMultican_DataLengthCode_16)
    {
        *data++ = hwBotObj->EDATA2.U;
    }

    if (lengthCode > IfxMultican_DataLengthCode_20)
    {
        *data++ = hwBotObj->EDATA3.U;
    }

    if (lengthCode > IfxMultican_DataLengthCode_24)
    {
        *data++ = hwBotObj->EDATA4.U;
        *data++ = hwBotObj->EDATA5.U;
    }

    if (lengthCode > IfxMultican_DataLengthCode_32)
    {
        *data++ = hwBotObj->EDATA6.U;
        /* read from top message object extended data registers */
        *data++ = hwTopObj->EDATA0.U;
        *data++ = hwTopObj->EDATA1.U;
        *data++ = hwTopObj->EDATA2.U;
    }

    if (lengthCode > IfxMultican_DataLengthCode_48)
    {
        *data++ = hwTopObj->EDATA3.U;
        *data++ = hwTopObj->EDATA4.U;
        *data++ = hwTopObj->EDATA5.U;
        *data   = hwTopObj->EDATA6.U;
    }

    msg->fastBitRate = hwObj->FCR.B.BRS;

    msg->lengthCode  = lengthCode;

    /* copy the ID from the hardware */
    msg->id = IfxMultican_MsgObj_getMessageId(hwObj);
}


IFX_STATIC void IfxMultican_MsgObj_doReadMessage(Ifx_CAN_MO *hwObj, IfxMultican_Message *msg)
{
    /* for standard message object and FIFO message objects*/
    IfxMultican_MsgObj_clearStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_newData);

    /* read the data from the data registers */
    msg->data[0] = hwObj->DATAL.U;
    msg->data[1] = hwObj->DATAH.U;

    /* copy the length code from hardware */
    msg->lengthCode = IfxMultican_MsgObj_getDataLengthCode(hwObj);

    /* copy the ID from the hardware */
    msg->id = IfxMultican_MsgObj_getMessageId(hwObj);
}


IfxMultican_MsgObjId IfxMultican_MsgObj_getPendingId(Ifx_CAN *mcan, IfxMultican_MsgObjGroup msgObjGroup)
{
    uint32               index    = mcan->MSID[msgObjGroup].U;
    IfxMultican_MsgObjId msgObjId = -1;

    if (index != 0x20U)
    {
        mcan->MSPND[msgObjGroup].U = ~(1UL << index);
        msgObjId                   = index + (msgObjGroup << 5);
    }

    return msgObjId;
}


IfxMultican_MsgObjStat IfxMultican_MsgObj_getStatus(Ifx_CAN_MO *hwObj)
{
    IfxMultican_MsgObjStat status;

    status.U = hwObj->STAT.U;

    return status;
}


boolean IfxMultican_MsgObj_getStatusFlag(Ifx_CAN_MO *hwObj, IfxMultican_MsgObjStatusFlag flag)
{
    uint32 shift = (1U << flag);

    return (hwObj->STAT.U & shift) ? TRUE : FALSE;
}


IfxMultican_Status IfxMultican_MsgObj_readLongFrame(Ifx_CAN *mcan, IfxMultican_MsgObjId msgObjId, IfxMultican_Message *msg, uint32 *data)
{
    Ifx_CAN_MO        *hwObj     = IfxMultican_MsgObj_getPointer(mcan, msgObjId);
    IfxMultican_Status status    = IfxMultican_Status_ok;

    boolean            longFrame = (hwObj->FCR.B.FDF != 0) ? TRUE : FALSE;

    if (longFrame)
    {
        /* if new data available in the message object */
        if (hwObj->STAT.B.NEWDAT != 0)
        {
            Ifx_CAN_MO_STAT stat;
            IfxMultican_MsgObj_doReadLongFrame(mcan, msgObjId, msg, data);
            stat = hwObj->STAT; /* Cache the status after reading to reduce message lost propability */

            if (stat.B.RXUPD != 0)
            {                   /* Data might be inconsistent (update while reading), declare as message lost, data will be read next time the API is called */
                status = IfxMultican_Status_messageLost;
            }
            else if (stat.B.NEWDAT != 0)
            {   /* Data might be inconsistent (update while reading), force massage lost flag, read new incoming data */
                Ifx_CAN_MO_STAT stat2;
                status = IfxMultican_Status_messageLost;
                /* perform read from the hardware */
                IfxMultican_MsgObj_doReadLongFrame(mcan, msgObjId, msg, data);

                stat2 = hwObj->STAT; /* Cache the status after reading */

                if ((stat2.B.NEWDAT == 0) && (stat2.B.RXUPD == 0))
                {
                    status |= IfxMultican_Status_newData;
                }
                else
                {   /* Return message lost at 2nd read attempt, data will be read next time the API is called*/
                }
            }
            else
            {
                status = IfxMultican_Status_newData;
            }

            if (stat.B.MSGLST != 0)
            {   /* At least on message has been lost */
                IfxMultican_MsgObj_clearStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_messageLost);
                status |= IfxMultican_Status_messageLost;
            }
        }
        else
        {
            status = IfxMultican_Status_receiveEmpty;
        }
    }
    else
    {
        /* use normal read message API */
    }

    return status;
}


IfxMultican_Status IfxMultican_MsgObj_readMessage(Ifx_CAN_MO *hwObj, IfxMultican_Message *msg)
{
    IfxMultican_Status status = IfxMultican_Status_ok;

    /* if new data available in the message object */
    if (hwObj->STAT.B.NEWDAT != 0)
    {
        Ifx_CAN_MO_STAT stat;
        IfxMultican_MsgObj_doReadMessage(hwObj, msg);
        stat = hwObj->STAT; /* Cache the status after reading to reduce message lost propability */

        if (stat.B.RXUPD != 0)
        {                   /* Data might be inconsistent (update while reading), declare as message lost, data will be read next time the API is called */
            status = IfxMultican_Status_messageLost;
        }
        else if (stat.B.NEWDAT != 0)
        {   /* Data might be inconsistent (update while reading), force massage lost flag, read new incoming data */
            Ifx_CAN_MO_STAT stat2;
            status = IfxMultican_Status_messageLost;
            /* perform read from the hardware */
            IfxMultican_MsgObj_doReadMessage(hwObj, msg);

            stat2 = hwObj->STAT; /* Cache the status after reading */

            if ((stat2.B.NEWDAT == 0) && (stat2.B.RXUPD == 0))
            {
                status |= IfxMultican_Status_newData;
            }
            else
            {   /* Return message lost at 2nd read attempt, data will be read next time the API is called*/
            }
        }
        else
        {
            status = IfxMultican_Status_newData;
        }

        if (stat.B.MSGLST != 0)
        {   /* At least on message has been lost */
            IfxMultican_MsgObj_clearStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_messageLost);
            status |= IfxMultican_Status_messageLost;
        }
    }
    else
    {
        status = IfxMultican_Status_receiveEmpty;
    }

    return status;
}


IfxMultican_Status IfxMultican_MsgObj_sendLongFrame(Ifx_CAN *mcan, IfxMultican_MsgObjId msgObjId, IfxMultican_Message *msg, uint32 *data)
{
    Ifx_CAN_MO          *hwObj  = IfxMultican_MsgObj_getPointer(mcan, msgObjId);
    IfxMultican_Status   status = IfxMultican_Status_ok;

    /* get the base address of top and bottom message objects */
    IfxMultican_MsgObjId botMsgObjId = hwObj->FGPR.B.BOT;
    Ifx_CAN_MO          *hwBotObj    = IfxMultican_MsgObj_getPointer(mcan, botMsgObjId);

    IfxMultican_MsgObjId topMsgObjId = hwObj->FGPR.B.TOP;
    Ifx_CAN_MO          *hwTopObj    = IfxMultican_MsgObj_getPointer(mcan, topMsgObjId);

    boolean              longFrame   = (hwObj->FCR.B.FDF != 0) ? TRUE : FALSE;

    /* in either of the below cases, the two conditions FDEN = 0, EDl = 1 and BRS = 0/1 will not reach */
    /* long frame CAN FD */
    /* FDEN = 1, EDL = 1 and BRS = 0/1 */
    if (longFrame)
    {
        if (hwObj->STAT.B.TXRQ)
        {                           /* previous message was not transferred, e.g. due to busy bus, BUS-OFF or others */
            status = IfxMultican_Status_notSentBusy;
        }
        else
        {
            /* MSGVAL: Set message as not valid */
            IfxMultican_MsgObj_clearStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_messageValid);

            if (msg->lengthCode > IfxMultican_DataLengthCode_0) /* no.of bytes 0 to 8 */
            {
                hwObj->DATAL.U = *data++;
                hwObj->DATAH.U = *data++;
            }

            /* load bottom message object extended data registers */
            if (msg->lengthCode > IfxMultican_DataLengthCode_8)
            {
                hwBotObj->EDATA0.U = *data++;
            }

            if (msg->lengthCode > IfxMultican_DataLengthCode_12)
            {
                hwBotObj->EDATA1.U = *data++;
            }

            if (msg->lengthCode > IfxMultican_DataLengthCode_16)
            {
                hwBotObj->EDATA2.U = *data++;
            }

            if (msg->lengthCode > IfxMultican_DataLengthCode_20)
            {
                hwBotObj->EDATA3.U = *data++;
            }

            if (msg->lengthCode > IfxMultican_DataLengthCode_24)
            {
                hwBotObj->EDATA4.U = *data++;
                hwBotObj->EDATA5.U = *data++;
            }

            if (msg->lengthCode > IfxMultican_DataLengthCode_32)
            {
                hwBotObj->EDATA6.U = *data++;
                /* load bottom message object extended data registers */
                hwTopObj->EDATA0.U = *data++;
                hwTopObj->EDATA1.U = *data++;
                hwTopObj->EDATA2.U = *data++;
            }

            if (msg->lengthCode > IfxMultican_DataLengthCode_48)
            {
                hwTopObj->EDATA3.U = *data++;
                hwTopObj->EDATA4.U = *data++;
                hwTopObj->EDATA5.U = *data++;
                hwTopObj->EDATA6.U = *data;
            }

            /* for long message */
            {
                /* set ID */
                boolean extendedFrame = IfxMultican_MsgObj_isExtendedFrame(hwObj);
                IfxMultican_MsgObj_setMessageId(hwObj, msg->id, extendedFrame);

                /* set data length code */
                IfxMultican_MsgObj_setDataLengthCode(hwObj, msg->lengthCode);

                /* set bit rate switch (fast bit rate enable/disable) */
                IfxMultican_MsgObj_setBitRateSwitch(hwObj, msg->fastBitRate);
            }

            /* --- flags configuration --- */
            {
                /* set new data flag */
                IfxMultican_MsgObj_setStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_newData);

                /* set message as valid */
                IfxMultican_MsgObj_setStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_messageValid);

                /* set RTSEL */
                IfxMultican_MsgObj_setStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_receiveTransmitSelected);

                /* set TXRQ */
                IfxMultican_MsgObj_setStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_transmitRequest);
            }
        }
    }

    /* standard frame */
    /* FDEN = 0/1, EDL = 0 and BRS = 0 (BRS = 1 also has no effect here) */
    else
    {
        /* use normal send message API */
        status = IfxMultican_Status_notInitialised;
    }

    return status;
}


IfxMultican_Status IfxMultican_MsgObj_sendMessage(Ifx_CAN_MO *hwObj, const IfxMultican_Message *msg)
{
    IfxMultican_Status status = IfxMultican_Status_ok;

    if (hwObj->STAT.B.TXRQ)
    {                           /* previous message was not transferred, e.g. due to busy bus, BUS-OFF or others */
        status = IfxMultican_Status_notSentBusy;
    }
    else
    {
        /* MSGVAL: Set message as not valid */
        IfxMultican_MsgObj_clearStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_messageValid);

        /* for standard and FIFO message object */
        hwObj->DATAL.U = msg->data[0];  /* Set the new data */
        hwObj->DATAH.U = msg->data[1];  /* Set the new data */

        /* for standard and FIFO message object */
        {
            /* set ID */
            boolean extendedFrame = IfxMultican_MsgObj_isExtendedFrame(hwObj);
            IfxMultican_MsgObj_setMessageId(hwObj, msg->id, extendedFrame);

            /* standard frame */
            /* in case of FD standard frame, FDEN = 0/1, EDL = 0 and BRS = 0 (BRS = 1 also has no effect here) */
            /* set data length code */
            IfxMultican_MsgObj_setDataLengthCode(hwObj, msg->lengthCode);
        }

        /* --- flags configuration --- */

        /* for standard and FIFO message object */
        {
            /* set new data flag */
            IfxMultican_MsgObj_setStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_newData);

            /* set message as valid, in case of FIFO mSGVAL has to be set before setting it to each slave object */
            IfxMultican_MsgObj_setStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_messageValid);

            /* set TXRQ, should not be set for FIFO base object */
            IfxMultican_MsgObj_setStatusFlag(hwObj, IfxMultican_MsgObjStatusFlag_transmitRequest);
        }
    }

    return status;
}


void IfxMultican_MsgObj_setFilter(Ifx_CAN_MO *hwObj, boolean extend, uint32 id, uint32 accMask)
{
    Ifx_CAN_MO_CTR ctr;

    ctr.U           = 0;
    ctr.B.RESMSGVAL = 1;    /* MSGVAL: Set message as not valid */
    hwObj->CTR.U    = ctr.U;

    hwObj->AMR.B.AM = accMask << ((extend != 0) ? 0 : 18);
    hwObj->AR.B.IDE = (id << ((extend != 0) ? 0 : 18)) | (extend << 29);

    ctr.U           = 0;
    ctr.B.SETMSGVAL = 1;    /* MSGVAL: Set message as valid */
    hwObj->CTR.U    = ctr.U;
}


void IfxMultican_MsgObj_setStatusFlag(Ifx_CAN_MO *hwObj, IfxMultican_MsgObjStatusFlag flag)
{
    Ifx_CAN_MO_CTR ctr;
    ctr.U        = 0;

    ctr.U        = 1U << (flag + 16);

    hwObj->CTR.U = ctr.U;
}


void IfxMultican_Node_deinit(Ifx_CAN_N *hwNode)
{
    hwNode->CR.U    = 0x00000001;
    hwNode->SR.U    = 0x00000000;
    hwNode->IPR.U   = 0x00000000;
    hwNode->PCR.U   = 0x00000000;
    hwNode->BTEVR.U = 0x00000000;
    hwNode->ECNT.U  = 0x00600000;
    hwNode->FCR.U   = 0x00000000;
}


boolean IfxMultican_Node_initRxPin(Ifx_CAN_N *hwNode, IfxMultican_Rxd_In *rxd, IfxPort_InputMode mode, IfxPort_PadDriver padDriver)
{
    IfxPort_setPinModeInput(rxd->pin.port, rxd->pin.pinIndex, mode);
    IfxPort_setPinPadDriver(rxd->pin.port, rxd->pin.pinIndex, padDriver);
    hwNode->PCR.B.RXSEL = rxd->select;

    return TRUE;
}


boolean IfxMultican_Node_initTxPin(Ifx_CAN_N *hwNode, IfxMultican_Txd_Out *txd, IfxPort_OutputMode mode, IfxPort_PadDriver padDriver)
{
    IfxPort_setPinModeOutput(txd->pin.port, txd->pin.pinIndex, mode, txd->select);
    IfxPort_setPinPadDriver(txd->pin.port, txd->pin.pinIndex, padDriver);

    return TRUE;
}


IfxMultican_Status IfxMultican_Node_recoverBusOff(Ifx_CAN_N *hwNode)
{
    IfxMultican_Status status             = IfxMultican_Status_busOff;

    boolean            busOffState        = hwNode->SR.B.BOFF;
    boolean            errorWarningStatus = hwNode->SR.B.EWRN;

    /* if the node is in bus off state, initiaite the recovery process */
    if ((busOffState != 0) && (hwNode->ECNT.B.TEC > 254))
    {
        status = IfxMultican_Status_busOff;

        /* reset error counters */
        hwNode->ECNT.B.TEC = 0x01;
        hwNode->ECNT.B.REC = 0x01;

        /* clear error warning status */
        hwNode->SR.B.EWRN = 0;

        /* clear ALERT status */
        hwNode->SR.B.ALERT = 0;

        /* disable node INIT = 1 */
        IfxMultican_Node_deactivate(hwNode);
    }

    /* during recovery process, if REC counter reaches 0x60 */
    else if ((busOffState != 0) && (errorWarningStatus != 0))
    {
        status = IfxMultican_Status_notInitialised;
    }

    /* if the recovery process is been finished or not in Bus off mode */
    else if ((busOffState == 0) && (errorWarningStatus == 0))
    {
        /* enable node INIT = 0 */
        IfxMultican_Node_activate(hwNode);

        status = IfxMultican_Status_ok;
    }

    return status;
}


void IfxMultican_Node_setBitTiming(Ifx_CAN_N *hwNode, float32 moduleFreq, uint32 baudrate, uint16 samplePoint, uint16 synchJumpWidth)
{
    sint32  maxBRP   = IFX_CAN_N_BTR_BRP_MSK + 1;
    sint32  minBRP   = 1;
    sint32  maxTSEG1 = IFX_CAN_N_BTR_TSEG1_MSK + 1;
    sint32  minTSEG1 = 3;
    sint32  maxTSEG2 = IFX_CAN_N_BTR_TSEG2_MSK + 1;
    sint32  minTSEG2 = 2;
    sint32  maxTBAUD = maxTSEG1 + maxTSEG2 + 1;
    sint32  minTBAUD = 8;

    sint32  tempBRP, tempSJW, tempTSEG1, tempTBAUD;
    sint32  bestBRP   = 0, bestSJW = 1, bestTBAUD = 8, bestTSEG1 = 3, bestTSEG2 = 2;
    float32 bestError = 10000.0;
    boolean baudrateTooLow, baudrateTooHigh, samplepointNotSuitable;

    /*
     * Bit timing & sampling
     * Tq = (BRP+1)/Fcan if DIV8 = 0
     * Tq = 8*(BRP+1)/Fcan if DIV8 = 1
     * TSync = 1.Tq
     * TSeg1 = (TSEG1+1)*Tq                >= 3Tq
     * TSeg2 = (TSEG2+1)*Tq                >= 2Tq
     * Bit Time = TSync + TSeg1 + TSeg2    >= 8Tq
     *
     * Resynchronization:
     *
     * Tsjw = (SJW + 1)*Tq
     * TSeg1 >= Tsjw + Tprop
     * TSeg2 >= Tsjw
     */

    /* search for best baudrate */
    bestError = baudrate * 0.05; /* 5% tolerance in baudrate as max error */

    for (tempBRP = 1; tempBRP <= maxBRP; tempBRP++)
    {
        float32 Fquanta = moduleFreq / tempBRP;
        tempTBAUD = Fquanta / baudrate;

        if (tempTBAUD == 0)
        {
            break; /* to avoid division by 0 */
        }

        float32 tempBaudrate = Fquanta / tempTBAUD;
        float32 error        = __absf(tempBaudrate - baudrate);

        if (tempTBAUD < minTBAUD)
        {
            break;  /* below the minimum allowed limits, break is required otherwise TSEG1 and TSEG2 may result in negitive values */
        }

        if ((tempTBAUD <= maxTBAUD) && (bestError >= error))
        {
            bestBRP   = tempBRP;
            bestTBAUD = tempTBAUD;
            bestError = error;

            if ((tempTBAUD <= 20) && (error < 0.1))
            {
                break;      /* optimal condition */
            }
        }
    }

    if ((bestBRP == 0) && (tempBRP == (maxBRP + 1)))
    {
        bestBRP         = maxBRP;
        bestTBAUD       = tempTBAUD;
        baudrateTooLow &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, baudrateTooLow);
    }

    if ((bestBRP == 0) && (tempTBAUD < minTBAUD))
    {
        bestBRP          = minBRP;
        bestTBAUD        = tempTBAUD;
        baudrateTooHigh &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, baudrateTooHigh);
    }

    /* search for best sample point */
    bestError = samplePoint * 0.15; /* 15% tolerance in sample point as max error */

    bestTSEG1 = maxTSEG1;

    for (tempTSEG1 = maxTSEG1; tempTSEG1 >= minTSEG1; tempTSEG1--)
    {
        sint32 tempSamplePoint = ((tempTSEG1 + 1) * 10000) / bestTBAUD;
        sint32 error           = __abs(tempSamplePoint - samplePoint);

        if (bestError > error)
        {
            bestTSEG1 = tempTSEG1;
            bestError = error;
        }

        if (tempSamplePoint < samplePoint)
        {
            if (tempTSEG1 == maxTSEG1)
            {
                samplepointNotSuitable &= 0; /* to avoid compiler warning */
                IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, samplepointNotSuitable);
            }
            else
            {
                /*least possible error */
            }

            break;  /* least possible error has already occured */
        }
    }

    if ((tempTSEG1 == (minTSEG1 - 1)) && (bestTSEG1 == maxTSEG1))
    {
        bestTSEG1               = minTSEG1;
        samplepointNotSuitable &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, samplepointNotSuitable);
    }

    bestTSEG2 = bestTBAUD - bestTSEG1 - 1;

    if (bestTSEG2 > maxTSEG2)
    {
        bestTSEG2               = maxTSEG2;
        samplepointNotSuitable &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, samplepointNotSuitable);
    }

    if (bestTSEG2 < minTSEG2)
    {
        bestTSEG2               = minTSEG2;
        samplepointNotSuitable &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, samplepointNotSuitable);
    }

    /* search for best SJW */
    bestError = 10000;

    for (tempSJW = 1; tempSJW <= bestTSEG2; tempSJW++)
    {
        sint32 tempSynchJumpWidth = (tempSJW * 10000) / bestTBAUD;
        sint32 error              = __abs(tempSynchJumpWidth - synchJumpWidth);

        if (bestError > error)
        {
            bestSJW   = tempSJW;
            bestError = error;
        }
    }

    {
        Ifx_CAN_N_BTR nbtr;
        nbtr.U       = 0;
        nbtr.B.BRP   = bestBRP - 1;
        nbtr.B.SJW   = bestSJW - 1;
        nbtr.B.TSEG1 = bestTSEG1 - 1;
        nbtr.B.TSEG2 = bestTSEG2 - 1;
        nbtr.B.DIV8  = 0;
        //nbtr.B.FTX = 0; /* TTCAN only */

        hwNode->BTR.U = nbtr.U;
    }
}


void IfxMultican_Node_setFastBitTiming(Ifx_CAN_N *hwNode, float32 moduleFreq, uint32 baudrate, uint16 samplePoint, uint16 synchJumpWidth)
{
    sint32  maxBRP   = IFX_CAN_N_FBTR_FBRP_MSK + 1;
    sint32  minBRP   = 1;
    sint32  maxTSEG1 = IFX_CAN_N_FBTR_FTSEG1_MSK + 1;
    sint32  minTSEG1 = 3;
    sint32  maxTSEG2 = IFX_CAN_N_FBTR_FTSEG2_MSK + 1;
    sint32  minTSEG2 = 2;
    sint32  maxTBAUD = maxTSEG1 + maxTSEG2 + 1;
    sint32  minTBAUD = 8;

    sint32  tempBRP, tempSJW, tempTSEG1, tempTBAUD;
    sint32  bestBRP   = 0, bestSJW = 1, bestTBAUD = 8, bestTSEG1 = 3, bestTSEG2 = 2;
    float32 bestError = 10000.0;
    boolean baudrateTooLow, baudrateTooHigh, samplepointNotSuitable;
    /*
     * Bit timing & sampling
     * Tq = (BRP+1)/Fcan if DIV8 = 0
     * Tq = 8*(BRP+1)/Fcan if DIV8 = 1
     * TSync = 1.Tq
     * TSeg1 = (TSEG1+1)*Tq                >= 3Tq
     * TSeg2 = (TSEG2+1)*Tq                >= 2Tq
     * Bit Time = TSync + TSeg1 + TSeg2    >= 8Tq
     *
     * Resynchronization:
     *
     * Tsjw = (SJW + 1)*Tq
     * TSeg1 >= Tsjw + Tprop
     * TSeg2 >= Tsjw
     */

    /* search for best baudrate */
    bestError = baudrate * 0.05; /* 5% tolerance in baudrate as max error */

    for (tempBRP = 1; tempBRP <= maxBRP; tempBRP++)
    {
        float32 Fquanta = moduleFreq / tempBRP;
        tempTBAUD = Fquanta / baudrate;

        if (tempTBAUD == 0)
        {
            break; /* to avoid division by 0 */
        }

        float32 tempBaudrate = Fquanta / tempTBAUD;
        float32 error        = __absf(tempBaudrate - baudrate);

        if (tempTBAUD < minTBAUD)
        {
            break;  /* below the minimum allowed limits, break is required otherwise TSEG1 and TSEG2 may result in negitive values */
        }

        if ((tempTBAUD <= maxTBAUD) && (bestError >= error))
        {
            bestBRP   = tempBRP;
            bestTBAUD = tempTBAUD;
            bestError = error;

            if ((tempTBAUD <= 20) && (error < 0.1))
            {
                break;      /* optimal condition */
            }
        }
    }

    if ((bestBRP == 0) && (tempBRP == (maxBRP + 1)))
    {
        bestBRP         = maxBRP;
        bestTBAUD       = tempTBAUD;
        baudrateTooLow &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, baudrateTooLow);
    }

    if ((bestBRP == 0) && (tempTBAUD < minTBAUD))
    {
        bestBRP          = minBRP;
        bestTBAUD        = tempTBAUD;
        baudrateTooHigh &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, baudrateTooHigh);
    }

    /* search for best sample point */
    bestError = samplePoint * 0.15; /* 15% tolerance in sample point as max error */

    bestTSEG1 = maxTSEG1;

    for (tempTSEG1 = maxTSEG1; tempTSEG1 >= minTSEG1; tempTSEG1--)
    {
        sint32 tempSamplePoint = ((tempTSEG1 + 1) * 10000) / bestTBAUD;
        sint32 error           = __abs(tempSamplePoint - samplePoint);

        if (bestError > error)
        {
            bestTSEG1 = tempTSEG1;
            bestError = error;
        }

        if (tempSamplePoint < samplePoint)
        {
            if (tempTSEG1 == maxTSEG1)
            {
                samplepointNotSuitable &= 0; /* to avoid compiler warning */
                IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, samplepointNotSuitable);
            }
            else
            {
                /*least possible error */
            }

            break;  /* least possible error has already occured */
        }
    }

    if ((tempTSEG1 == (minTSEG1 - 1)) && (bestTSEG1 == maxTSEG1))
    {
        bestTSEG1               = minTSEG1;
        samplepointNotSuitable &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, samplepointNotSuitable);
    }

    bestTSEG2 = bestTBAUD - bestTSEG1 - 1;

    if (bestTSEG2 > maxTSEG2)
    {
        bestTSEG2               = maxTSEG2;
        samplepointNotSuitable &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, samplepointNotSuitable);
    }

    if (bestTSEG2 < minTSEG2)
    {
        bestTSEG2               = minTSEG2;
        samplepointNotSuitable &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, samplepointNotSuitable);
    }

    /* search for best SJW */
    bestError = 10000;

    for (tempSJW = 1; tempSJW <= bestTSEG2; tempSJW++)
    {
        sint32 tempSynchJumpWidth = (tempSJW * 10000) / bestTBAUD;
        sint32 error              = __abs(tempSynchJumpWidth - synchJumpWidth);

        if (bestError > error)
        {
            bestSJW   = tempSJW;
            bestError = error;
        }
    }

    {
        Ifx_CAN_N_FBTR nfbtr;
        nfbtr.U        = 0;
        nfbtr.B.FBRP   = bestBRP - 1;
        nfbtr.B.FSJW   = bestSJW - 1;
        nfbtr.B.FTSEG1 = bestTSEG1 - 1;
        nfbtr.B.FTSEG2 = bestTSEG2 - 1;

        hwNode->FBTR.U = nfbtr.U;
    }
}


void IfxMultican_Node_setNominalBitTiming(Ifx_CAN_N *hwNode, float32 moduleFreq, uint32 baudrate, uint16 samplePoint, uint16 synchJumpWidth)
{
    sint32  maxBRP   = IFX_CAN_N_BTEVR_BRP_MSK + 1;
    sint32  minBRP   = 1;
    sint32  maxTSEG1 = IFX_CAN_N_BTEVR_TSEG1_MSK + 1;
    sint32  minTSEG1 = 3;
    sint32  maxTSEG2 = IFX_CAN_N_BTEVR_TSEG2_MSK + 1;
    sint32  minTSEG2 = 2;
    sint32  maxTBAUD = maxTSEG1 + maxTSEG2 + 1;
    sint32  minTBAUD = 8;

    sint32  tempBRP, tempSJW, tempTSEG1, tempTBAUD;
    sint32  bestBRP   = 0, bestSJW = 1, bestTBAUD = 8, bestTSEG1 = 3, bestTSEG2 = 2;
    float32 bestError = 10000.0;
    boolean baudrateTooLow, baudrateTooHigh, samplepointNotSuitable;
    /*
     * Bit timing & sampling
     * Tq = (BRP+1)/Fcan if DIV8 = 0
     * Tq = 8*(BRP+1)/Fcan if DIV8 = 1
     * TSync = 1.Tq
     * TSeg1 = (TSEG1+1)*Tq                >= 3Tq
     * TSeg2 = (TSEG2+1)*Tq                >= 2Tq
     * Bit Time = TSync + TSeg1 + TSeg2    >= 8Tq
     *
     * Resynchronization:
     *
     * Tsjw = (SJW + 1)*Tq
     * TSeg1 >= Tsjw + Tprop
     * TSeg2 >= Tsjw
     */

    /* search for best baudrate */
    bestError = baudrate * 0.05; /* 5% tolerance in baudrate as max error */

    for (tempBRP = 1; tempBRP <= maxBRP; tempBRP++)
    {
        float32 Fquanta = moduleFreq / tempBRP;
        tempTBAUD = Fquanta / baudrate;

        if (tempTBAUD == 0)
        {
            break; /* to avoid division by 0 */
        }

        float32 tempBaudrate = Fquanta / tempTBAUD;
        float32 error        = __absf(tempBaudrate - baudrate);

        if (tempTBAUD < minTBAUD)
        {
            break;  /* below the minimum allowed limits, break is required otherwise TSEG1 and TSEG2 may result in negitive values */
        }

        if ((tempTBAUD <= maxTBAUD) && (bestError >= error))
        {
            bestBRP   = tempBRP;
            bestTBAUD = tempTBAUD;
            bestError = error;

            if ((tempTBAUD <= 20) && (error < 0.1))
            {
                break;      /* optimal condition */
            }
        }
    }

    if ((bestBRP == 0) && (tempBRP == (maxBRP + 1)))
    {
        bestBRP         = maxBRP;
        bestTBAUD       = tempTBAUD;
        baudrateTooLow &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, baudrateTooLow);
    }

    if ((bestBRP == 0) && (tempTBAUD < minTBAUD))
    {
        bestBRP          = minBRP;
        bestTBAUD        = tempTBAUD;
        baudrateTooHigh &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, baudrateTooHigh);
    }

    /* search for best sample point */
    bestError = samplePoint * 0.15; /* 15% tolerance in sample point as max error */

    bestTSEG1 = maxTSEG1;

    for (tempTSEG1 = maxTSEG1; tempTSEG1 >= minTSEG1; tempTSEG1--)
    {
        sint32 tempSamplePoint = ((tempTSEG1 + 1) * 10000) / bestTBAUD;
        sint32 error           = __abs(tempSamplePoint - samplePoint);

        if (bestError > error)
        {
            bestTSEG1 = tempTSEG1;
            bestError = error;
        }

        if (tempSamplePoint < samplePoint)
        {
            if (tempTSEG1 == maxTSEG1)
            {
                samplepointNotSuitable &= 0;    /* to avoid compiler warning */
                IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, samplepointNotSuitable);
            }
            else
            {
                /*least possible error */
            }

            break;  /* least possible error has already occured */
        }
    }

    if ((tempTSEG1 == (minTSEG1 - 1)) && (bestTSEG1 == maxTSEG1))
    {
        bestTSEG1               = minTSEG1;
        samplepointNotSuitable &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, samplepointNotSuitable);
    }

    bestTSEG2 = bestTBAUD - bestTSEG1 - 1;

    if (bestTSEG2 > maxTSEG2)
    {
        bestTSEG2               = maxTSEG2;
        samplepointNotSuitable &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, samplepointNotSuitable);
    }

    if (bestTSEG2 < minTSEG2)
    {
        bestTSEG2               = minTSEG2;
        samplepointNotSuitable &= 0; /* to avoid compiler warning */
        IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, samplepointNotSuitable);
    }

    /* search for best SJW */
    bestError = 10000;

    for (tempSJW = 1; tempSJW <= bestTSEG2; tempSJW++)
    {
        sint32 tempSynchJumpWidth = (tempSJW * 10000) / bestTBAUD;
        sint32 error              = __abs(tempSynchJumpWidth - synchJumpWidth);

        if (bestError > error)
        {
            bestSJW   = tempSJW;
            bestError = error;
        }
    }

    {
        Ifx_CAN_N_BTEVR nbtevr;
        nbtevr.U       = 0;
        nbtevr.B.BRP   = bestBRP - 1;
        nbtevr.B.SJW   = bestSJW - 1;
        nbtevr.B.TSEG1 = bestTSEG1 - 1;
        nbtevr.B.TSEG2 = bestTSEG2 - 1;
        nbtevr.B.DIV8  = 0;
        //nbtr.B.FTX = 0; /* TTCAN only */

        hwNode->BTEVR.U = nbtevr.U;
    }
}


void IfxMultican_calcTimingFromBTR(float32 moduleFreq, uint32 btr, uint32 *baudrate, uint16 *samplePoint, uint16 *synchJumpWidth)
{
    Ifx_CAN_N_BTR nbtr      = {.U = btr};
    uint32        tempBRP   = 1U + nbtr.B.BRP;
    uint32        tempSJW   = 1U + nbtr.B.SJW;
    uint32        tempTSEG1 = 1U + nbtr.B.TSEG1;
    uint32        tempTSEG2 = 1U + nbtr.B.TSEG2;
    uint32        tempDIV8  = (nbtr.B.DIV8 != 0) ? 8U : 1U;

    uint32        tempTSEG  = 1 + tempTSEG1 + tempTSEG2;

    *baudrate       = (uint32)(moduleFreq / (float32)(tempDIV8 * tempBRP * tempTSEG));
    *samplePoint    = (uint16)(((float32)tempTSEG1) * 10000 / ((float32)(tempTSEG)));
    *synchJumpWidth = (uint16)(((float32)tempSJW) * 10000 / ((float32)(tempTSEG)));
}


void IfxMultican_deinit(Ifx_CAN *mcan)
{
    // should use kernel reset functionality!
    uint16 i;

    /* Ifx_CAN.CLC is reset last */
    uint16 numMsgObjs, numNodes, numSrcs;

    if (mcan == &MODULE_CANR)
    {
        numMsgObjs = IFXMULTICAN_R_NUM_MESSAGE_OBJECTS;
        numNodes   = IFXMULTICAN_R_NUM_NODES;
        numSrcs    = IFXMULTICAN_R_NUM_SRC;
    }
    else
    {
        numMsgObjs = IFXMULTICAN_NUM_MESSAGE_OBJECTS;
        numNodes   = IFXMULTICAN_NUM_NODES;
        numSrcs    = IFXMULTICAN_NUM_SRC;
    }

    for (i = 0; i < numMsgObjs; i++)
    {
        IfxMultican_MsgObj_deinit(mcan, i);
    }

    for (i = 0; i < numNodes; i++)
    {
        Ifx_CAN_N *hwNode = IfxMultican_Node_getPointer(mcan, IfxMultican_NodeId_0 + i);
        IfxMultican_Node_deinit(hwNode);
    }

    for (i = 0; i < numSrcs; i++)
    {
        if (mcan == &MODULE_CANR)
        {
            MODULE_SRC.CANR.CANR[0].RINT[i].U = 0x00000000;
        }
        else
        {
            MODULE_SRC.CAN.CAN[0].INT[i].U = 0x00000000;
        }
    }

    for (i = 0; i < 8; i++)
    {
        mcan->MSPND[i].U = 0x00000000;
    }

    mcan->MSIMASK.U = 0x00000000;
    mcan->MCR.U     = 0x00000000;
    {
        uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();
        IfxScuWdt_clearCpuEndinit(passwd);
        mcan->FDR.U = 0x00000000;
        IfxScuWdt_setCpuEndinit(passwd);
        IfxScuWdt_clearCpuEndinit(passwd);
        mcan->CLC.U = 0x00000001;
        IfxScuWdt_setCpuEndinit(passwd);
    }
}


volatile Ifx_SRC_SRCR *IfxMultican_getSrcPointer(Ifx_CAN *mcan, IfxMultican_SrcId srcId)
{
    volatile Ifx_SRC_SRCR *srcSFR = NULL_PTR;

    if (mcan == &MODULE_CANR)
    {
        if (srcId <= IfxMultican_SrcId_7)
        {
            srcSFR = &(MODULE_SRC.CANR.CANR[0].RINT[srcId]);
        }
        else
        {
            IFX_ASSERT(IFX_VERBOSE_LEVEL_ERROR, srcId <= IfxMultican_SrcId_7);
        }
    }
    else
    {
        srcSFR = &(MODULE_SRC.CAN.CAN[0].INT[srcId]);
    }

    return srcSFR;
}


void IfxMultican_resetModule(Ifx_CAN *can)
{
    uint16 passwd = IfxScuWdt_getCpuWatchdogPassword();

    IfxScuWdt_clearCpuEndinit(passwd);
    can->KRST0.B.RST = 1;           /* Only if both Kernel reset bits are set a reset is executed */
    can->KRST1.B.RST = 1;
    IfxScuWdt_setCpuEndinit(passwd);

    while (0 == can->KRST0.B.RSTSTAT)   /* Wait until reset is executed */

    {}

    IfxScuWdt_clearCpuEndinit(passwd);
    can->KRSTCLR.B.CLR = 1;         /* Clear Kernel reset status bit */
    IfxScuWdt_setCpuEndinit(passwd);
}


void IfxMultican_setListCommand(Ifx_CAN *mcan, uint32 cmd, uint32 arg2, uint32 arg1)
{
    Ifx_CAN_PANCTR panctr;

    panctr.B.PANAR1 = arg1;
    panctr.B.PANAR2 = arg2;
    panctr.B.PANCMD = cmd;

    /** - write to CAN_PANCTR */
    mcan->PANCTR.U = panctr.U;

    IfxMultican_waitListReady(mcan);
}


IfxMultican_Index IfxMultican_getIndex(Ifx_CAN *multican)
{
    uint32            index;
    IfxMultican_Index result;

    result = IfxMultican_Index_none;

    for (index = 0; index < IFXMULTICAN_NUM_MODULES; index++)
    {
        if (IfxMultican_cfg_indexMap[index].module == multican)
        {
            result = (IfxMultican_Index)IfxMultican_cfg_indexMap[index].index;
            break;
        }
    }

    return result;
}


Ifx_CAN *IfxMultican_getAddress(IfxMultican_Index multican)
{
    Ifx_CAN *module;

    if (multican < IFXMULTICAN_NUM_MODULES)
    {
        module = (Ifx_CAN *)IfxMultican_cfg_indexMap[multican].module;
    }
    else
    {
        module = NULL_PTR;
    }

    return module;
}
