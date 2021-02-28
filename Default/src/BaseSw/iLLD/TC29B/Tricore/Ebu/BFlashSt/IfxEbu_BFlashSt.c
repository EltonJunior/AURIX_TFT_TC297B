/**
 * \file IfxEbu_BFlashSt.c
 * \brief EBU BFLASHST details
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
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxEbu_BFlashSt.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

void IfxEbu_BFlashSt_cmdBlockErase(const IfxEbu_BFlashSt *bflash, uint32 blockAddress)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress + (0x55 << 2));
    volatile uint32 *addr2 = (volatile uint32 *)(blockAddress);

    *addr1 = 0x20;
    *addr2 = 0xd0;
}


void IfxEbu_BFlashSt_cmdClearBlockProtection(const IfxEbu_BFlashSt *bflash, uint32 blockAddress)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress + (0x55 << 2));
    volatile uint32 *addr2 = (volatile uint32 *)(blockAddress);

    *addr1 = 0x60;
    *addr2 = 0xd0;
}


void IfxEbu_BFlashSt_cmdClearStatusRegister(const IfxEbu_BFlashSt *bflash)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress);

    *addr1 = 0x50;
}


void IfxEbu_BFlashSt_cmdEraseAllMainBlocks(const IfxEbu_BFlashSt *bflash)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress + (0x55 << 2));
    volatile uint32 *addr2 = (volatile uint32 *)(bflash->baseAddress + (0xaa << 2));

    *addr1 = 0x80;
    *addr2 = 0xd0;
}


void IfxEbu_BFlashSt_cmdProgramEraseResume(const IfxEbu_BFlashSt *bflash)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress);

    *addr1 = 0xd0;
}


void IfxEbu_BFlashSt_cmdProgramEraseSuspend(const IfxEbu_BFlashSt *bflash)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress);

    *addr1 = 0xb0;
}


void IfxEbu_BFlashSt_cmdProgramTuningProtection(const IfxEbu_BFlashSt *bflash)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress + (0xaa << 2));
    volatile uint32 *addr2 = (volatile uint32 *)(bflash->baseAddress + 0);
    volatile uint32 *addr3 = (volatile uint32 *)(bflash->baseAddress + 4);

    *addr1 = 0x48;
    *addr2 = bflash->passwordLower;

    IfxEbu_BFlashSt_waitForReady(bflash);

    *addr1 = 0x48;
    *addr3 = bflash->passwordUpper;

    IfxEbu_BFlashSt_waitForReady(bflash);

    IfxEbu_BFlashSt_cmdReadMemoryArray(bflash);
}


void IfxEbu_BFlashSt_cmdProgramWord(const IfxEbu_BFlashSt *bflash, uint32 address, uint32 data)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress + (0xaa << 2));
    volatile uint32 *addr2 = (volatile uint32 *)(address);

    *addr1 = 0x40;
    *addr2 = data;
}


uint32 IfxEbu_BFlashSt_cmdReadElectronicSignature(const IfxEbu_BFlashSt *bflash, uint32 signatureOffset)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress);
    volatile uint32 *addr2 = (volatile uint32 *)(bflash->baseAddress + 4 * signatureOffset);

    *addr1 = 0x90;
    __dsync();

    uint32 signature = *addr2;
    return signature;
}


void IfxEbu_BFlashSt_cmdReadMemoryArray(const IfxEbu_BFlashSt *bflash)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress);

    *addr1 = 0xff;
}


void IfxEbu_BFlashSt_cmdReadQuery(const IfxEbu_BFlashSt *bflash)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress);

    *addr1 = 0x98;
}


uint32 IfxEbu_BFlashSt_cmdReadStatus(const IfxEbu_BFlashSt *bflash)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress);

    *addr1 = 0x70;

    /* ensure that previous write operation is finished before reading */
    __dsync();

    uint32 status = *addr1;
    return status;
}


void IfxEbu_BFlashSt_cmdSetBlockProtection(const IfxEbu_BFlashSt *bflash, uint32 blockAddress)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress + (0x55 << 2));
    volatile uint32 *addr2 = (volatile uint32 *)(blockAddress);

    *addr1 = 0x60;
    *addr2 = 0x01;
}


void IfxEbu_BFlashSt_cmdSetBurstConfig(const IfxEbu_BFlashSt *bflash, IfxEbu_BFlashSt_BurstCfg burstCfg)
{
    /* The M58BW032 the address lines are connected from A2 hence we are shifting the address by 2 */
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress + (burstCfg.U << 2));

    *addr1 = 0x60;
    *addr1 = 0x03;
}


void IfxEbu_BFlashSt_cmdUnlockTuningProtection(const IfxEbu_BFlashSt *bflash)
{
    volatile uint32 *addr1 = (volatile uint32 *)(bflash->baseAddress + 0);
    volatile uint32 *addr2 = (volatile uint32 *)(bflash->baseAddress + 4);

    *addr1 = 0x78;
    *addr1 = bflash->passwordLower;

    IfxEbu_BFlashSt_waitForReady(bflash);

    *addr1 = 0x78;
    *addr2 = bflash->passwordUpper;

    IfxEbu_BFlashSt_waitForReady(bflash);

    IfxEbu_BFlashSt_cmdReadMemoryArray(bflash);
}


void IfxEbu_BFlashSt_eraseBlock(const IfxEbu_BFlashSt *bflash, uint32 blockAddress)
{
    IfxEbu_BFlashSt_cmdClearBlockProtection(bflash, blockAddress);
    IfxEbu_BFlashSt_waitForReady(bflash);

    if (bflash->hasTuningProtection != FALSE)
    {
        IfxEbu_BFlashSt_cmdUnlockTuningProtection(bflash);
        IfxEbu_BFlashSt_waitForReady(bflash);
    }

    IfxEbu_BFlashSt_cmdBlockErase(bflash, blockAddress);
    IfxEbu_BFlashSt_waitForReady(bflash);

    IfxEbu_BFlashSt_cmdReadMemoryArray(bflash);
}


void IfxEbu_BFlashSt_initMemory(IfxEbu_BFlashSt *bflash, const IfxEbu_BFlashSt_Config *config)
{
    Ifx_EBU *ebu = config->module;
    bflash->ebu                 = ebu;
    bflash->chipSelect          = config->chipSelect;
    bflash->baseAddress         = config->memoryRegionConfig.baseAddress;
    bflash->passwordLower       = config->passwordLower;
    bflash->passwordUpper       = config->passwordUpper;
    bflash->hasTuningProtection = config->hasTuningProtection;

    {
        uint16 password = IfxScuWdt_getCpuWatchdogPassword();
        IfxScuWdt_clearCpuEndinit(password);

        IfxEbu_setExternalClockRatio(ebu, config->externalClockRatio);

        IfxScuWdt_setCpuEndinit(password);
    }

    /* configuring Base and Alternate segment Address for EBU to Access External Memory */
    {
        Ifx_EBU_ADDRSEL addrsel;
        addrsel.U                          = 0;
        addrsel.B.REGENAB                  = config->memoryRegionConfig.regionEnabled;
        addrsel.B.ALTENAB                  = config->memoryRegionConfig.alternateSegmentEnabled;
        addrsel.B.WPROT                    = config->memoryRegionConfig.writeProtection;
        addrsel.B.GLOBALCS                 = config->memoryRegionConfig.combinedChipSelect;
        addrsel.B.MASK                     = config->memoryRegionConfig.addressMask;
        addrsel.B.ALTSEG                   = config->memoryRegionConfig.alternateSegment;
        addrsel.B.BASE                     = (config->memoryRegionConfig.baseAddress >> 12); /* Address bits are only 20 hence we need to shift */

        ebu->ADDRSEL[config->chipSelect].U = addrsel.U;
    }

    /* The Read Register such as BUSRCON, BUSRAP are configured for BFlashSt hence they are dependent on Clock Ratio
     * For Clock Ratio 0 it is in Asynchronous mode for the rest it is in Synchronous Mode */

    if (config->syncReadAccessParameter.externalClock == 0)
    {
        {
            Ifx_EBU_BUSRCON busrcon;
            busrcon.U                           = 0;
            busrcon.B.FETBLEN                   = config->asyncReadConfig.burstLength;
            busrcon.B.BFCMSEL                   = config->asyncReadConfig.burstFlashClockFeedback;
            busrcon.B.PORTW                     = config->asyncReadConfig.deviceInterface;
            busrcon.B.AGEN                      = config->asyncReadConfig.deviceType;
            ebu->BUS[config->chipSelect].RCON.U = busrcon.U;
        }

        {
            Ifx_EBU_BUSRAP busrap;
            busrap.U                           = 0;
            busrap.B.ADDRC                     = config->asyncReadAccessParameter.addressCycle; /* Delays are given wrt to Asynchronous mode */
            busrap.B.AHOLDC                    = config->asyncReadAccessParameter.addressHold;  /* Delays are given wrt to Asynchronous mode */
            busrap.B.CMDDELAY                  = config->asyncReadAccessParameter.commandDelay; /* Delays are given wrt to Asynchronous mode */
            busrap.B.DATAC                     = config->asyncReadAccessParameter.dataHold;
            busrap.B.WAITRDC                   = config->asyncReadAccessParameter.waitState;
            busrap.B.RDRECOVC                  = config->asyncReadAccessParameter.recoveryAccess;
            busrap.B.RDDTACS                   = config->asyncReadAccessParameter.recoveryRegion;

            ebu->BUS[config->chipSelect].RAP.U = busrap.U;
        }
    }
    else
    {
        {
            Ifx_EBU_BUSRCON busrcon;
            busrcon.U                           = 0;
            busrcon.B.FETBLEN                   = config->syncReadConfig.burstLength;
            busrcon.B.FDBKEN                    = config->syncReadConfig.burstFlashClockMode;
            busrcon.B.BFCMSEL                   = config->syncReadConfig.burstFlashClockFeedback;
            busrcon.B.ECSE                      = config->syncReadConfig.earlyChipSelect;
            busrcon.B.EBSE                      = config->syncReadConfig.earlyBurst;
            busrcon.B.PORTW                     = config->syncReadConfig.deviceInterface;
            busrcon.B.AGEN                      = config->syncReadConfig.deviceType;
            ebu->BUS[config->chipSelect].RCON.U = busrcon.U;
        }

        {
            /* Configuration of Read Parameter are dependent on Clock Ratio of BFlashSt itself */
            Ifx_EBU_BUSRAP busrap;
            busrap.U                           = 0;
            busrap.B.ADDRC                     = config->syncReadAccessParameter.addressCycle * (config->syncReadAccessParameter.externalClock + 1);
            busrap.B.AHOLDC                    = config->syncReadAccessParameter.addressHold * (config->syncReadAccessParameter.externalClock + 1);
            busrap.B.CMDDELAY                  = config->syncReadAccessParameter.commandDelay * (config->syncReadAccessParameter.externalClock + 1);
            busrap.B.EXTCLOCK                  = config->syncReadAccessParameter.externalClock;
            busrap.B.DATAC                     = config->syncReadAccessParameter.dataHold * (config->syncReadAccessParameter.externalClock + 1);
            busrap.B.WAITRDC                   = config->syncReadAccessParameter.waitState * (config->syncReadAccessParameter.externalClock + 1);
            busrap.B.RDRECOVC                  = config->syncReadAccessParameter.recoveryAccess * (config->syncReadAccessParameter.externalClock + 1);
            busrap.B.RDDTACS                   = config->syncReadAccessParameter.recoveryRegion * (config->syncReadAccessParameter.externalClock + 1);

            ebu->BUS[config->chipSelect].RAP.U = busrap.U;
        }
    }

    /* Burst Flash is written in ASync mode */
    {
        {
            Ifx_EBU_BUSWCON buswcon;
            buswcon.U                           = 0;
            buswcon.B.FETBLEN                   = config->asyncWriteConfig.burstLength;
            buswcon.B.PORTW                     = config->asyncWriteConfig.deviceInterface;
            buswcon.B.AGEN                      = config->asyncWriteConfig.deviceType;
            ebu->BUS[config->chipSelect].WCON.U = buswcon.U;
        }

        {
            Ifx_EBU_BUSWAP buswap;
            buswap.U                           = 0;
            buswap.B.ADDRC                     = config->asyncWriteAccessParameter.addressCycle;
            buswap.B.AHOLDC                    = config->asyncWriteAccessParameter.addressHold;
            buswap.B.CMDDELAY                  = config->asyncWriteAccessParameter.commandDelay;
            buswap.B.DATAC                     = config->asyncWriteAccessParameter.dataHold;
            buswap.B.WAITWRC                   = config->asyncWriteAccessParameter.waitState;
            buswap.B.WRRECOVC                  = config->asyncWriteAccessParameter.recoveryAccess;
            buswap.B.WRDTACS                   = config->asyncWriteAccessParameter.recoveryRegion;

            ebu->BUS[config->chipSelect].WAP.U = buswap.U;
        }
    }

    /* EBU Mode Configuration */
    {
        Ifx_EBU_MODCON modcon;
        modcon.U             = 0;
        modcon.B.LOCKTIMEOUT = config->moduleConfig.lockTimeout;
        modcon.B.ARBMODE     = config->moduleConfig.arbMode;
        modcon.B.ARBSYNC     = config->moduleConfig.arbSignalSynchronization;
        modcon.B.ALE         = config->moduleConfig.aleMode;
        ebu->MODCON.U        = modcon.U;
    }

    /* read back to ensure that EBU is configured before first external access */
    if (ebu->MODCON.U)
    {}

    /* configure burst mode in external device*/
    IfxEbu_BFlashSt_cmdSetBurstConfig(bflash, config->burstCfg);
}


void IfxEbu_BFlashSt_initMemoryConfig(IfxEbu_BFlashSt_Config *config, Ifx_EBU *ebu)
{
    config->module             = ebu;
    config->externalClockRatio = IfxEbu_ExternalClockRatio_3;
    config->chipSelect         = IfxEbu_ChipSelect_0;

    /* Synchronous Read Configuration */
    config->syncReadConfig.burstLength             = 3;
    config->syncReadConfig.burstFlashClockFeedback = 1;
    config->syncReadConfig.burstFlashClockMode     = 1;
    config->syncReadConfig.deviceInterface         = 3;
    config->syncReadConfig.deviceType              = IfxEbu_DeviceType_demuxedBurstType;
    config->syncReadConfig.earlyBurst              = 1;
    config->syncReadConfig.earlyChipSelect         = 1;

    /* Asynchronous Read Configuration */
    config->asyncReadConfig.burstLength             = 0;
    config->asyncReadConfig.burstFlashClockFeedback = 0;
    config->asyncReadConfig.deviceInterface         = 3;
    config->asyncReadConfig.deviceType              = IfxEbu_DeviceType_demuxedAsynchronousType;

    /* Asynchronous Write Configuration */
    config->asyncWriteConfig.burstLength     = 0;
    config->asyncWriteConfig.deviceInterface = 3;
    config->asyncWriteConfig.deviceType      = IfxEbu_DeviceType_demuxedAsynchronousType;

    /* Synchronous Read Access Parameters */
    config->syncReadAccessParameter.addressCycle   = 1;
    config->syncReadAccessParameter.addressHold    = 0;
    config->syncReadAccessParameter.commandDelay   = 1;
    config->syncReadAccessParameter.externalClock  = 3; // This is commonly used for both Sync and Async configurations as the configurations are dependent on clock ratio //
    config->syncReadAccessParameter.dataHold       = 0;
    config->syncReadAccessParameter.waitState      = 2;
    config->syncReadAccessParameter.recoveryAccess = 1;
    config->syncReadAccessParameter.recoveryRegion = 1;

    /* Asynchronous Read Access Parameters */
    config->asyncReadAccessParameter.addressCycle   = 6;
    config->asyncReadAccessParameter.addressHold    = 6;
    config->asyncReadAccessParameter.commandDelay   = 6;
    config->asyncReadAccessParameter.dataHold       = 3;
    config->asyncReadAccessParameter.waitState      = 11;
    config->asyncReadAccessParameter.recoveryAccess = 3;
    config->asyncReadAccessParameter.recoveryRegion = 3;

    /* Asynchronous Write Access Parameters */
    config->asyncWriteAccessParameter.addressCycle   = 8;
    config->asyncWriteAccessParameter.addressHold    = 8;
    config->asyncWriteAccessParameter.commandDelay   = 8;
    config->asyncWriteAccessParameter.dataHold       = 8;
    config->asyncWriteAccessParameter.waitState      = 8;
    config->asyncWriteAccessParameter.recoveryAccess = 4;
    config->asyncWriteAccessParameter.recoveryRegion = 4;

    /* Module Configuration */
    config->moduleConfig.aleMode                  = 0;
    config->moduleConfig.arbMode                  = IfxEbu_ExternalBusMode_soleMaster;
    config->moduleConfig.lockTimeout              = 0xff;
    config->moduleConfig.arbSignalSynchronization = IfxEbu_ArbitrationSignalSynchronization_asynchronous;

    /* Memory Region configuration */
    config->memoryRegionConfig.regionEnabled           = TRUE;
    config->memoryRegionConfig.alternateSegmentEnabled = TRUE;
    config->memoryRegionConfig.writeProtection         = FALSE;
    config->memoryRegionConfig.combinedChipSelect      = FALSE;
    config->memoryRegionConfig.addressMask             = 5;
    config->memoryRegionConfig.alternateSegment        = 0x8;
    config->memoryRegionConfig.baseAddress             = 0xA4000000;

    /* M58BW032 specific burst configuration */
    config->burstCfg.B.readSelect     = 0;
    config->burstCfg.B.xlat           = 1; // or 3? check with silicon!
    config->burstCfg.B.ylat           = 0;
    config->burstCfg.B.validDataReady = 1;
    config->burstCfg.B.burstType      = 1;
    config->burstCfg.B.validClockEdge = 1;
    config->burstCfg.B.wrapping       = 0;
    config->burstCfg.B.burstLength    = 2;

    /* M58BW032 specific tuning protection */
    config->passwordLower       = 0xffffffff;
    config->passwordUpper       = 0xffffffff;
    config->hasTuningProtection = FALSE;
}


void IfxEbu_BFlashSt_programWord(const void *bflash, uint32 address, uint32 data)
{
    IfxEbu_BFlashSt_cmdClearStatusRegister(bflash);

    IfxEbu_BFlashSt_cmdProgramWord(bflash, address, data);
    IfxEbu_BFlashSt_waitForReady(bflash);

    IfxEbu_BFlashSt_cmdReadMemoryArray(bflash);
}


boolean IfxEbu_BFlashSt_waitForReady(const IfxEbu_BFlashSt *bflash)
{
    /* TODO: should we add a timeout mechanism? */
    while ((IfxEbu_BFlashSt_cmdReadStatus(bflash) & 0x80) == 0x00)
    {}

    return TRUE;
}
