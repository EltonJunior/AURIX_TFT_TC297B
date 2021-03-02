/**
 * \file IfxEbu.h
 * \brief EBU  basic functionality
 * \ingroup IfxLld_Ebu
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
 * \defgroup IfxLld_Ebu_Std_Enum Enumerations
 * \ingroup IfxLld_Ebu_Std
 * \defgroup IfxLld_Ebu_Std_Operative Operative Functions
 * \ingroup IfxLld_Ebu_Std
 * \defgroup IfxLld_Ebu_Std_Support Support Functions
 * \ingroup IfxLld_Ebu_Std
 */

#ifndef IFXEBU_H
#define IFXEBU_H 1

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "_Impl/IfxEbu_cfg.h"
#include "IfxEbu_reg.h"
#include "Scu/Std/IfxScuWdt.h"

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/** \addtogroup IfxLld_Ebu_Std_Enum
 * \{ */
typedef enum
{
    IfxEbu_ChipSelect_0,     /**< \brief Chip Select Line 0  */
    IfxEbu_ChipSelect_1,     /**< \brief Chip Select Line 1  */
    IfxEbu_ChipSelect_2      /**< \brief Chip Select Line 2  */
} IfxEbu_ChipSelect;

typedef enum
{
    IfxEbu_ExternalClockRatio_1,  /**< \brief f_ebu:f_sri = 1:1; */
    IfxEbu_ExternalClockRatio_2,  /**< \brief f_ebu:f_sri = 2:1 */
    IfxEbu_ExternalClockRatio_3,  /**< \brief f_ebu:f_sri = 3:1 */
    IfxEbu_ExternalClockRatio_4,  /**< \brief f_ebu:f_sri = 4:1 */
    IfxEbu_ExternalClockRatio_6,  /**< \brief f_ebu:f_sri = 6:1 */
    IfxEbu_ExternalClockRatio_8   /**< \brief f_ebu:f_sri = 8:1 */
} IfxEbu_ExternalClockRatio;

/** \} */

typedef enum
{
    IfxEbu_AlternateSegmentCompare_disabled = 0,  /**< \brief Alternate Segment is never Compared with SRI Bus */
    IfxEbu_AlternateSegmentCompare_enabled  = 1   /**< \brief Alternate Segment Address is always compared */
} IfxEbu_AlternateSegmentCompare;

typedef enum
{
    IfxEbu_ArbitrationSignalSynchronization_synchronous  = 0, /**< \brief Arbitration Signals are Synchronous */
    IfxEbu_ArbitrationSignalSynchronization_asynchronous = 1  /**< \brief Arbitration inputs are Asynchronous */
} IfxEbu_ArbitrationSignalSynchronization;

typedef enum
{
    IfxEbu_ByteControl_byteControlFollowingChipSelect    = 0,
    IfxEbu_ByteControl_bytecontrolFollowingControlSignal = 1,
    IfxEbu_ByteControl_byteControlFollowingWriteEnable   = 2,
    IfxEbu_ByteControl_sdramAccessDQM                    = 3
} IfxEbu_ByteControl;

typedef enum
{
    IfxEbu_ByteControlEnable_byteControlOff   = 0,  /**< \brief Byte control off. Pins available for address or
                                                     * GPIO as set by Ports logic */
    IfxEbu_ByteControlEnable_byteControl8Bit  = 1,  /**< \brief 8 bit byte control. Byte control 0 only. A(22:20)
                                                     * available for address or GPIO as set by Ports
                                                     * logic */
    IfxEbu_ByteControlEnable_byteControl16Bit = 2,  /**< \brief 16 bit byte control. BC(1:0) available. A(21:20)
                                                     * available for address or GPIO as set by Ports
                                                     * logic */
    IfxEbu_ByteControlEnable_byteControl32Bit = 3   /**< \brief 32 bit byte control. BC(3:0) available */
} IfxEbu_ByteControlEnable;

typedef enum
{
    IfxEbu_CASLatency_Latency2 = 2,  /**< \brief CAS Latency 2 between Read Command and availability of Data */
    IfxEbu_CASLatency_Latency3 = 3   /**< \brief CAS Latency 3 between Read Access and availability of Data */
} IfxEbu_CASLatency;

typedef enum
{
    IfxEbu_ClockDivideRatio_0 = 0,      /**< \brief EBU Clock divide Ratio  */
    IfxEbu_ClockDivideRatio_1,          /**< \brief EBU Clock divide Ratio  */
    IfxEbu_ClockDivideRatio_2,          /**< \brief EBU Clock divide Ratio  */
    IfxEbu_ClockDivideRatio_3           /**< \brief EBU Clock divide Ratio  */
} IfxEbu_ClockDivideRatio;

typedef enum
{
    IfxEbu_ClockSource_asynchronous = 0,  /**< \brief EBU input clock is in Asynchronous mode; */
    IfxEbu_ClockSource_synchronous  = 1   /**< \brief EBU Input Clock Source is from PLL; */
} IfxEbu_ClockSource;

typedef enum
{
    IfxEbu_ColumnAddressWidth_1 = 1,  /**< \brief Asri[8:0] for 16bit 512bytes and Asri[9:0] for 32bit 1024bytes */
    IfxEbu_ColumnAddressWidth_2 = 2,  /**< \brief Asri[9:0] for 16bit 1024 bytes and Asri[10:0] for 32bit 2048 bytes */
    IfxEbu_ColumnAddressWidth_3 = 3   /**< \brief Asri[10:0] for 16bit 1024 bytes and Asri[11:0] for 32bit 4096 bytes */
} IfxEbu_ColumnAddressWidth;

typedef enum
{
    IfxEbu_DelayOnPowerDownExit_0,     /**< \brief Number of Nops after SDRAM controller exits power down  */
    IfxEbu_DelayOnPowerDownExit_1,     /**< \brief Number of Nops after SDRAM controller exits power down  */
    IfxEbu_DelayOnPowerDownExit_2,     /**< \brief Number of Nops after SDRAM controller exits power down  */
    IfxEbu_DelayOnPowerDownExit_3,     /**< \brief Number of Nops after SDRAM controller exits power down  */
    IfxEbu_DelayOnPowerDownExit_4,     /**< \brief Number of Nops after SDRAM controller exits power down  */
    IfxEbu_DelayOnPowerDownExit_5,     /**< \brief Number of Nops after SDRAM controller exits power down  */
    IfxEbu_DelayOnPowerDownExit_6,     /**< \brief Number of Nops after SDRAM controller exits power down  */
    IfxEbu_DelayOnPowerDownExit_7      /**< \brief Number of Nops after SDRAM controller exits power down  */
} IfxEbu_DelayOnPowerDownExit;

typedef enum
{
    IfxEbu_DeviceType_muxedAsynchronousType   = 0,  /**< \brief External Device is a Muxed Asynchronous Type Device */
    IfxEbu_DeviceType_muxedBurstType          = 1,  /**< \brief External Device is a Muxed Burst Type */
    IfxEbu_DeviceType_nandFlash               = 2,  /**< \brief External Device is a Nand Flash device */
    IfxEbu_DeviceType_muxedCellularRam        = 3,  /**< \brief External Device is a Muxed Cellular Ram Device */
    IfxEbu_DeviceType_demuxedAsynchronousType = 4,  /**< \brief External Device is a Demuxed Asynchronous Type device */
    IfxEbu_DeviceType_demuxedBurstType        = 5,  /**< \brief External device is a Demuxed Burst Type device */
    IfxEbu_DeviceType_demuxedPageMode         = 6,  /**< \brief External device is a Demuxed Page Mode Device */
    IfxEbu_DeviceType_demuxedCellularRam      = 7,  /**< \brief External device is a Demuxed Cellular Ram Device */
    IfxEbu_DeviceType_sdram                   = 8   /**< \brief External Device is a SDRAM Device */
} IfxEbu_DeviceType;

typedef enum
{
    IfxEbu_ExtendedData_0,     /**< \brief Data is output every 2*str(x)  Clock Cycle(s)  */
    IfxEbu_ExtendedData_1,     /**< \brief Data is output every 2*str(x)  Clock Cycle(s)  */
    IfxEbu_ExtendedData_2,     /**< \brief Data is output every 2*str(x)  Clock Cycle(s)  */
    IfxEbu_ExtendedData_3      /**< \brief Data is output every 2*str(x)  Clock Cycle(s)  */
} IfxEbu_ExtendedData;

typedef enum
{
    IfxEbu_ExtendedOperationBankSelect_0,     /**< \brief Value written to Bank Select Pins of Mobile SDRAM  */
    IfxEbu_ExtendedOperationBankSelect_1,     /**< \brief Value written to Bank Select Pins of Mobile SDRAM  */
    IfxEbu_ExtendedOperationBankSelect_2,     /**< \brief Value written to Bank Select Pins of Mobile SDRAM  */
    IfxEbu_ExtendedOperationBankSelect_3      /**< \brief Value written to Bank Select Pins of Mobile SDRAM  */
} IfxEbu_ExtendedOperationBankSelect;

typedef enum
{
    IfxEbu_ExtendedRefresh_0,
    IfxEbu_ExtendedRefresh_1,
    IfxEbu_ExtendedRefresh_2,
    IfxEbu_ExtendedRefresh_3
} IfxEbu_ExtendedRefresh;

typedef enum
{
    IfxEbu_ExternalBusMode_noBus       = 0,  /**< \brief EBU is in NoBus Mode */
    IfxEbu_ExternalBusMode_arbiter     = 1,  /**< \brief EBU is in Arbiter mode; */
    IfxEbu_ExternalBusMode_participant = 2,  /**< \brief EBU is in Participant Mode; */
    IfxEbu_ExternalBusMode_soleMaster  = 3   /**< \brief EBU is in Sole Master Mode */
} IfxEbu_ExternalBusMode;

typedef enum
{
    IfxEbu_ExternalDeviceInterface_8bitMultiplexed      = 0,  /**< \brief External Device is an 8 Bit Device */
    IfxEbu_ExternalDeviceInterface_16bitMultiplexed     = 1,  /**< \brief External evice is an 16 bit Multiplexed */
    IfxEbu_ExternalDeviceInterface_twin16bitMultiplexed = 2,  /**< \brief Two External 16 bit Multiplexed Devices are used */
    IfxEbu_ExternalDeviceInterface_32bitMultiplexed     = 3   /**< \brief External device is an 32 bit Multiplexed device */
} IfxEbu_ExternalDeviceInterface;

typedef enum
{
    IfxEbu_ExternalMemoryWriteProtect_disabled = 0,  /**< \brief External memory is writable */
    IfxEbu_ExternalMemoryWriteProtect_enabled  = 1   /**< \brief External Memory is write protected */
} IfxEbu_ExternalMemoryWriteProtect;

typedef enum
{
    IfxEbu_MaskForBankTag_1 = 1,  /**< \brief Asri[21 to 20] */
    IfxEbu_MaskForBankTag_2 = 2,  /**< \brief Asri[22 to 21] */
    IfxEbu_MaskForBankTag_3 = 3,  /**< \brief Asri[23 to 22] */
    IfxEbu_MaskForBankTag_4 = 4,  /**< \brief Asri[24 to 23] */
    IfxEbu_MaskForBankTag_5 = 5,  /**< \brief Asri[25 to 24] */
    IfxEbu_MaskForBankTag_6 = 6   /**< \brief Asri[26 to 25] */
} IfxEbu_MaskForBankTag;

typedef enum
{
    IfxEbu_MemoryRegionMask_0,     /**< \brief Mask1  */
    IfxEbu_MemoryRegionMask_1,     /**< \brief Mask2  */
    IfxEbu_MemoryRegionMask_2,     /**< \brief Mask3  */
    IfxEbu_MemoryRegionMask_3,     /**< \brief Mask4  */
    IfxEbu_MemoryRegionMask_4,     /**< \brief Mask5  */
    IfxEbu_MemoryRegionMask_5,     /**< \brief Mask6  */
    IfxEbu_MemoryRegionMask_6,     /**< \brief Mask7  */
    IfxEbu_MemoryRegionMask_7,     /**< \brief Mask8  */
    IfxEbu_MemoryRegionMask_8,     /**< \brief Mask9  */
    IfxEbu_MemoryRegionMask_9,     /**< \brief Mask10  */
    IfxEbu_MemoryRegionMask_10,    /**< \brief Mask11  */
    IfxEbu_MemoryRegionMask_11,    /**< \brief Mask12  */
    IfxEbu_MemoryRegionMask_12,    /**< \brief Mask13  */
    IfxEbu_MemoryRegionMask_13,    /**< \brief Mask14  */
    IfxEbu_MemoryRegionMask_14,    /**< \brief Mask15  */
    IfxEbu_MemoryRegionMask_15     /**< \brief Mask16  */
} IfxEbu_MemoryRegionMask;

typedef enum
{
    IfxEbu_ModeRegisterSetupTime_0,     /**< \brief Number of Nop Cycles after a Mode Register Set Command (Crsc + 1) Nop cycles  */
    IfxEbu_ModeRegisterSetupTime_1,     /**< \brief Number of Nop Cycles after a Mode Register Set Command (Crsc + 1) Nop cycles  */
    IfxEbu_ModeRegisterSetupTime_2,     /**< \brief Number of Nop Cycles after a Mode Register Set Command (Crsc + 1) Nop cycles  */
    IfxEbu_ModeRegisterSetupTime_3      /**< \brief Number of Nop Cycles after a Mode Register Set Command (Crsc + 1) Nop cycles  */
} IfxEbu_ModeRegisterSetupTime;

typedef enum
{
    IfxEbu_PowerSaveMode_0,     /**< \brief Power Save mode used for clock gate mode  */
    IfxEbu_PowerSaveMode_1,     /**< \brief Power Save mode used for clock gate mode  */
    IfxEbu_PowerSaveMode_2,     /**< \brief Power Save mode used for clock gate mode  */
    IfxEbu_PowerSaveMode_3      /**< \brief Power Save mode used for clock gate mode  */
} IfxEbu_PowerSaveMode;

typedef enum
{
    IfxEbu_RefreshCommands_0,
    IfxEbu_RefreshCommands_1,
    IfxEbu_RefreshCommands_2,
    IfxEbu_RefreshCommands_3,
    IfxEbu_RefreshCommands_4,
    IfxEbu_RefreshCommands_5,
    IfxEbu_RefreshCommands_6,
    IfxEbu_RefreshCommands_7
} IfxEbu_RefreshCommands;

typedef enum
{
    IfxEbu_RowPrechargeTime_0,     /**< \brief Number of Nops inserted after Precharge command (Crp + 1) Nop Cycles  */
    IfxEbu_RowPrechargeTime_1,     /**< \brief Number of Nops inserted after Precharge command (Crp + 1) Nop Cycles  */
    IfxEbu_RowPrechargeTime_2,     /**< \brief Number of Nops inserted after Precharge command (Crp + 1) Nop Cycles  */
    IfxEbu_RowPrechargeTime_3      /**< \brief Number of Nops inserted after Precharge command (Crp + 1) Nop Cycles  */
} IfxEbu_RowPrechargeTime;

typedef enum
{
    IfxEbu_RowToColumnDelay_0,     /**< \brief Number of Nops between Row Address and Column Address (Crcd(value) + 1 Nop Cycle)  */
    IfxEbu_RowToColumnDelay_1,     /**< \brief Number of Nops between Row Address and Column Address (Crcd(value) + 1 Nop Cycle)  */
    IfxEbu_RowToColumnDelay_2,     /**< \brief Number of Nops between Row Address and Column Address (Crcd(value) + 1 Nop Cycle)  */
    IfxEbu_RowToColumnDelay_3      /**< \brief Number of Nops between Row Address and Column Address (Crcd(value) + 1 Nop Cycle)  */
} IfxEbu_RowToColumnDelay;

typedef enum
{
    IfxEbu_SDRAMBurstLength_1  = 0, /**< \brief Burst Length 1 */
    IfxEbu_SDRAMBurstLength_2  = 1, /**< \brief Burst Length 2 */
    IfxEbu_SDRAMBurstLength_4  = 2, /**< \brief Burst Length 4 */
    IfxEbu_SDRAMBurstLength_8  = 3, /**< \brief Burst Length 8 */
    IfxEbu_SDRAMBurstLength_16 = 4  /**< \brief Burst Length 16 */
} IfxEbu_SDRAMBurstLength;

typedef enum
{
    IfxEbu_SynchronousBurstBuffer_bufferLength = 0,  /**< \brief EBU Buffer length = IfxEbu_SynchronousBurstLength; */
    IfxEbu_SynchronousBurstBuffer_continuous   = 1   /**< \brief EBU External Data is Transferred in Single Burst; */
} IfxEbu_SynchronousBurstBuffer;

typedef enum
{
    IfxEbu_SynchronousBurstLength_1 = 0,  /**< \brief EBU Burst Length is 1; */
    IfxEbu_SynchronousBurstLength_2 = 1,  /**< \brief EBU Burst length is 2 */
    IfxEbu_SynchronousBurstLength_4 = 2,  /**< \brief EBU Burst Length is 4 */
    IfxEbu_SynchronousBurstLength_8 = 3   /**< \brief EBU Burst Length is 8 */
} IfxEbu_SynchronousBurstLength;

typedef enum
{
    IfxEbu_WaitControl_off          = 0,  /**< \brief External Wait is off */
    IfxEbu_WaitControl_asynchronous = 1,  /**< \brief Asynchronous input for wait (Asynchronous Device) & Wait for Page load (Synchronous Device) */
    IfxEbu_WaitControl_synchronous  = 2   /**< \brief Synchronous input for wait (Asynchronous Device) & wait for Page load (with Data) (Synchronous Device) */
} IfxEbu_WaitControl;

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

typedef struct
{
    boolean                 regionEnabled;
    boolean                 alternateSegmentEnabled;
    boolean                 writeProtection;
    boolean                 combinedChipSelect;
    IfxEbu_MemoryRegionMask addressMask;
    uint8                   alternateSegment;
    uint32                  baseAddress;
} IfxEbu_MemoryRegionConfig;

typedef struct
{
    boolean                                 aleMode;                        /**< \brief when '0' output is ADV, when '1' output is ALE */
    IfxEbu_ExternalBusMode                  arbMode;                        /**< \brief Arbitration mode of External Bus */
    IfxEbu_ArbitrationSignalSynchronization arbSignalSynchronization;       /**< \brief Arbitration signal Synchronization mode */
    boolean                                 sdramTri;                       /**< \brief when '0' SDRAM control Signals are driven by EBU, when '1' SDRAM control signals are tristated */
    uint8                                   lockTimeout;                    /**< \brief Value for preloaded for arbitration lock */
    boolean                                 clockComb;                      /**< \brief Both BFlash and SDRAM share the same clock out */
} IfxEbu_ModuleConfig;

typedef struct
{
    uint8               addressCycle;         /**< \brief BUSRAP.ADDRC Number of Clock Phase for Address */
    uint8               addressHold;          /**< \brief BUSRAP.AHOLDC Number of Cycles for Address Hold Phase */
    uint8               commandDelay;         /**< \brief BUSRAP.CMDDELAY Number of Command Delay Phase Clock Cycles */
    IfxEbu_ExtendedData extendedData;         /**< \brief BUSRAP.EXTDATA Determines the Clock Cycles after which the data is put out */
    uint8               externalClock;        /**< \brief BUSRAP.EXTCLOCK Determines the Clock Ratio between EBU_CLC and BFCLK or SDCLK */
    uint8               dataHold;             /**< \brief BUSRAP.DATAC Data Hold Cycles for Read */
    uint8               waitState;            /**< \brief BUSRAP.WAITRDC Number of Wait States for Read */
    uint8               recoveryAccess;       /**< \brief BUSRAP.RDRECOVC Recovery cycles at end of Read Access */
    uint8               recoveryRegion;       /**< \brief BUSRAP.RDDTACS Recovery cycles between different regions */
} IfxEbu_ReadAccessParameter;

typedef struct
{
    IfxEbu_DeviceType              deviceType;                    /**< \brief BUSRCON.AGEN Device selection for Read */
    IfxEbu_WaitControl             waitControl;                   /**< \brief BUSRCON.WAIT, External Wait Control */
    IfxEbu_ExternalDeviceInterface deviceInterface;               /**< \brief BUSRCON.PORTW Selects the device Addressing mode (16bit, 32bit, 2*16bit) */
    uint8                          byteControl;                   /**< \brief BUSRCON.BCGEN selects the timing mode of byte control */
    boolean                        polarityWait;                  /**< \brief BUSRCON.WAITINV if '1' the polarity is reversed */
    boolean                        earlyBurst;                    /**< \brief BUSRCON.EBSE if '1' ADV is not delayed */
    boolean                        earlyChipSelect;               /**< \brief BUSRCON.ECSE if '1' CS is not delayed */
    boolean                        burstFlashClockMode;           /**< \brief BUSRCON.BFCMSEL if '1' Clock is disabled between Access */
    boolean                        burstFlashClockFeedback;       /**< \brief BUSRCON.FDBKEN if '1' Feedback clock is used for resynchronizing the contol and data coming in */
    boolean                        synchronousBurstBuffer;        /**< \brief BUSRCON.FBBMSEL The data is either continuous or depends on FETLBEN */
    IfxEbu_SynchronousBurstLength  burstLength;                   /**< \brief BUSRCON.FETBLEN Defines maximum number of Burst Data */
} IfxEbu_ReadConfig;

typedef struct
{
    uint8                        rowToPrechargeDelay;                /**< \brief Number of clock cycles between Row Activate command and a Precharge command */
    uint8                        initializationRefreshCommand;       /**< \brief Number of Refresh cycles issued during Initialization */
    IfxEbu_ModeRegisterSetupTime modeRegSetupTime;                   /**< \brief Number of NOP commands after a mode register set command */
    IfxEbu_RowPrechargeTime      rowPrechargeTime;                   /**< \brief Number of NOP commands inserted after Precharge */
    IfxEbu_ColumnAddressWidth    columnAddressWidth;                 /**< \brief Number of Address bits from 0 used for Column Addressing */
    IfxEbu_RowToColumnDelay      rowToColumnDelay;                   /**< \brief Number of NOP commands between Row address and Column address */
    uint8                        refreshCycleTime;                   /**< \brief Number of NOP cycles following Refresh cycle */
    IfxEbu_MaskForBankTag        maskForBankTag;                     /**< \brief SRI address bits used to determine Bank Address */
    boolean                      disableClockOutput;                 /**< \brief if '0' Clock is enabled */
    IfxEbu_PowerSaveMode         powerSaveMode;                      /**< \brief Power save mode used for Gated Clock mode */
    boolean                      clockModeSelect;                    /**< \brief if '0' clock is running continuously, if '1' clock is disabled between access */
} IfxEbu_SDRAMControlConfig;

typedef struct
{
    IfxEbu_ExtendedOperationBankSelect extendedBankSelect;          /**< \brief Value to be written to bank select pins of a mobile SDRAM */
    uint16                             extendedOperationMode;       /**< \brief Value to be written to the extended mode register of a mobile SDRAM device */
    boolean                            coldStart;                   /**< \brief If '1' is written the SDRAM device register will be updated */
    IfxEbu_CASLatency                  casLatency;                  /**< \brief Number of Clock cycles between the availability of data an Read Access */
    IfxEbu_SDRAMBurstLength            burstLength;                 /**< \brief Number of location that can be accessed in a single command */
    uint8                              opmode;
} IfxEbu_SDRAMModConfig;

typedef struct
{
    IfxEbu_DelayOnPowerDownExit delayOnPowerDownExit;       /**< \brief Number of Nops after SDRAM Controller exits Power down before an active command is active */
    boolean                     autoRefresh;                /**< \brief If '1' Auto Refresh will be enabled before Self Refresh Exit */
    uint8                       selfRefreshExitDelay;       /**< \brief Number of Nops inserted after Self Refresh Command */
    IfxEbu_ExtendedRefresh      extendedRefresh;            /**< \brief Used to Increase the Range of RefreshC field from 6 bits to 8 bits */
    boolean                     automaticSelfRefresh;       /**< \brief If '1' Automatic Self Refresh command will be issued for Entry and Exit */
    boolean                     selfRefreshEntry;           /**< \brief If '1' Self Refresh Entry command is issued */
    boolean                     selfRefreshExit;            /**< \brief If '1' Self Refresh Exit commands are issued */
    IfxEbu_RefreshCommands      refreshCommands;            /**< \brief The Number of additional Refresh commands issued to SDRAM each time a refresh is due */
    uint8                       refreshPeriod;              /**< \brief Number of clock Cycles between Refresh */
} IfxEbu_SDRAMRefreshConfig;

typedef struct
{
    uint8               addressCycle;         /**< \brief BUSWAP.ADDRC Number of Clock Phase for Address */
    uint8               addressHold;          /**< \brief BUSWAP.AHOLDC Number of Cycles for Address Hold Phase */
    uint8               commandDelay;         /**< \brief BUSWAP.CMDDELAY Number of Command Delay Phase Clock Cycles */
    IfxEbu_ExtendedData extendedData;         /**< \brief BUSWAP.EXTDATA Determines the Clock Cycles after which the data is put out */
    uint8               externalClock;        /**< \brief BUSWAP.EXTCLOCK Determines the Clock Ratio between EBU_CLC and BFCLK or SDCLK */
    uint8               dataHold;             /**< \brief BUSWAP.DATAC Data Hold Cycles for WRITE */
    uint8               waitState;            /**< \brief BUSRAP.WAITWRC Number of Wait States for Write */
    uint8               recoveryAccess;       /**< \brief BUSWAP.WRRECOVC Recovery cycles at end of Write Access */
    uint8               recoveryRegion;       /**< \brief BUSWAP.WRDTACS Recovery cycles between different regions */
} IfxEbu_WriteAccessParameter;

typedef struct
{
    IfxEbu_DeviceType              deviceType;                   /**< \brief BUSWCON.AGEN Device selection for Read */
    IfxEbu_WaitControl             waitControl;                  /**< \brief BUSWCON.WAIT, External Wait Control */
    IfxEbu_ExternalDeviceInterface deviceInterface;              /**< \brief BUSWCON.PORTW Selects the device Addressing mode (16bit, 32bit, 2*16bit) */
    uint8                          byteControl;                  /**< \brief BUSWCON.BCGEN selects the timing mode of byte control */
    boolean                        polarityWait;                 /**< \brief BUSWCON.WAITINV if '1' the polarity is reversed */
    boolean                        earlyBurst;                   /**< \brief BUSWCON.EBSE if '1' ADV is not delayed */
    boolean                        earlyChipSelect;              /**< \brief BUSWCON.ECSE if '1' CS is not delayed */
    boolean                        synchronousBurstBuffer;       /**< \brief BUSWCON.FBBMSEL The data is either continuous or depends on FETLBEN */
    IfxEbu_SynchronousBurstLength  burstLength;                  /**< \brief BUSWCON.FETBLEN Defines maximum number of Burst Data */
} IfxEbu_WriteConfig;

/** \addtogroup IfxLld_Ebu_Std_Operative
 * \{ */

/******************************************************************************/
/*-------------------------Inline Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Returns the memory segment for a particular chip select
 * \param ebu pointer to the base of EBU registers
 * \param chipSelect Chip Select
 * \return memory segment
 */
IFX_INLINE uint16 IfxEbu_getMemorySegment(Ifx_EBU *ebu, IfxEbu_ChipSelect chipSelect);

/******************************************************************************/
/*-------------------------Global Function Prototypes-------------------------*/
/******************************************************************************/

/** \brief Configures the EBU Clock Divider
 * \param ebu pointer to the base of EBU registers
 * \param ratio external clock ratio
 * \return None
 */
IFX_EXTERN void IfxEbu_setExternalClockRatio(Ifx_EBU *ebu, IfxEbu_ExternalClockRatio ratio);

/** \brief configures the byte control enable in the USERCON register
 * \param ebu pointer to the base of EBU registers
 * \param byteControlEnable Enable byte control
 * \return None
 */
IFX_EXTERN void IfxEbu_setByteControlEnable(Ifx_EBU *ebu, IfxEbu_ByteControlEnable byteControlEnable);

/** \brief Disables the module
 * \param ebu pointer to the base of EBU registers
 * \return None
 */
IFX_EXTERN void IfxEbu_disableModule(Ifx_EBU *ebu);

/** \} */

/******************************************************************************/
/*---------------------Inline Function Implementations------------------------*/
/******************************************************************************/

IFX_INLINE uint16 IfxEbu_getMemorySegment(Ifx_EBU *ebu, IfxEbu_ChipSelect chipSelect)
{
    return ebu->ADDRSEL[chipSelect].B.ALTSEG;
}


#endif /* IFXEBU_H */