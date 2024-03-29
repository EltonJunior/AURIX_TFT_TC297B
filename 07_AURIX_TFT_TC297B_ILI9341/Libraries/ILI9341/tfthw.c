/*
 * TFTHW.c
 *
 *  Created on: 07.01.2012
 *      Author: voigtlae
 */
/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "Ifx_Types.h"
#include "IfxPort_reg.h"
#include "IfxQspi_reg.h"
#include "IfxQspi_bf.h"
//#include "font_8_12.h"
#include "tfthw.h"
#include "Configuration.h"
#include "font.h"

/******************************************************************************/
/*------------------------Inline Function Prototypes--------------------------*/
/******************************************************************************/

/******************************************************************************/
/*----------------------------------Defines-----------------------------------*/
/******************************************************************************/

/*---------------------- Graphic LCD size definitions ------------------------*/

#define WIDTH       LCD_WIDTH           /* Screen Width (in pixels)           */
#define HEIGHT      LCD_HEIGHT          /* Screen Height (in pixels)          */
#define BPP         16                  /* Bits per pixel                     */
#define BYPP        ((BPP+7)/8)         /* Bytes per pixel                    */

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

#define BGL_ON()            (P20_OUT.B.P13 = 1)
#define BGL_INIT()          (P20_OUT.B.P13 = 0, P20_IOCR12.B.PC13 = 0x10)

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/** \brief QspiCpu global data */
typedef struct
{
    struct
    {
        IfxQspi_SpiMaster         *spiMaster;            /**< \brief Pointer to spi Master handle */
        IfxQspi_SpiMaster_Channel spiMasterChannel;      /**< \brief Spi Master Channel handle */
    }drivers;
}  App_Qspi_Tft;

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/
/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/
#if TFT_DISPLAY_VAR_LOCATION == 0
    #if defined(__GNUC__)
    #pragma section
    #pragma section ".bss_cpu0" awc0
    #endif
    #if defined(__TASKING__)
    #pragma section farbss "bss_cpu0"
    #endif
    #if defined(__DCC__)
    #pragma section DATA ".data_cpu0" ".bss_cpu0" far-absolute RW
    #endif
#elif TFT_DISPLAY_VAR_LOCATION == 1
    #if defined(__GNUC__)
    #pragma section ".bss_cpu1" awc1
    #endif
    #if defined(__TASKING__)
    #pragma section farbss "bss_cpu1"
    #endif
    #if defined(__DCC__)
    #pragma section DATA ".data_cpu1" ".bss_cpu1" far-absolute RW
    #endif
#elif TFT_DISPLAY_VAR_LOCATION == 2
    #if defined(__GNUC__)
    #pragma section ".bss_cpu2" awc2
    #endif
    #if defined(__TASKING__)
    #pragma section farbss "bss_cpu2"
    #endif
    #if defined(__DCC__)
    #pragma section DATA ".data_cpu2" ".bss_cpu2" far-absolute RW
    #endif
#else
#error "Set TFT_DISPLAY_VAR_LOCATION to a valid value!"
#endif
            //!< y dimension of tft display

// the iLLD don't use cirular buffering, we need an align to 4 for DMA (32 bit access)
//uint16 Row_Buff[320*120] IFX_ALIGN(4);
volatile uint32 tft_status = 0;
volatile uint16 tft_id = 0;

volatile uint32 (*pCallbackFunction) (void) = (void *)0;

App_Qspi_Tft g_Qspi_Tft;


#if defined(__GNUC__)
#pragma section
#endif
#if defined(__TASKING__)
#pragma section farbss restore
#endif
#if defined(__DCC__)
#pragma section DATA RW
#endif


static unsigned short TextColor = COLOR_BLACK;
static unsigned short BackColor = COLOR_WHITE;
static unsigned short DriverCode;

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/
void tft_transmit_callback(void)
{
    // check that we are ready (no remaining bytes) in case that we are not using the DMA
    if (g_Qspi_Tft.drivers.spiMaster->dma.useDma == 0)
        if (g_Qspi_Tft.drivers.spiMasterChannel.base.tx.remaining) return;
    // if our pCallbackFunction is valid then we call it
    if (pCallbackFunction != (void *)0)
        pCallbackFunction();
}

static void delay_us (uint32 time)
{
    volatile sint32 test;
    uint32 i;
    test = 0;
    for (i = 0; i < time; i += 1)
    {
        test += 1;
    }
}

static void delay_ms (uint32 time)
{
    while (time--)
    {
        delay_us (1000);
        ;
    }
}

static void tft_write_data (uint8 regaddr, uint16 data)
{
    uint32 tx_data;
    /* we can use stack variables for exchange because we are waiting until the transfer is finished */

    /* wait until Spi is no longer busy (should not busy here) */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};

    tx_data = (regaddr << 22) | (data << 6);

    IfxQspi_SpiMaster_exchange(&g_Qspi_Tft.drivers.spiMasterChannel, &tx_data, 0, 1);

    /* wait until our datas are valid */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};
}

static uint32 tft_read_data (uint8 regaddr)
{
    uint32 tx_data[2];
    uint32 rx_data[2];
    uint8 cnt;

    /* wait until Spi is no longer busy (should not busy here) */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};

    /* we can use stack variables for exchange because we are waiting until the transfer is finished */

    for (cnt=0; cnt<2; cnt++)
    {
        tx_data[cnt] = 0;
        rx_data[cnt] = 0;
    }

    /* we need 16 bit for address and 26 bits for value = 42 bits total */
    /* we change the datawidth to 21 bit */
    g_Qspi_Tft.drivers.spiMasterChannel.bacon.B.DL = 20;
    g_Qspi_Tft.drivers.spiMasterChannel.dataWidth = 21;

    tx_data[0] = ((0x1 << 20) | (regaddr << 11));

    IfxQspi_SpiMaster_exchange(&g_Qspi_Tft.drivers.spiMasterChannel, &tx_data[0], &rx_data[0], 2);

    /* wait until our datas are valid */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};

    /* set back to 32 bit transfer */
    g_Qspi_Tft.drivers.spiMasterChannel.bacon.B.DL = 31;
    g_Qspi_Tft.drivers.spiMasterChannel.dataWidth = 32;

    /* ??? we need to check this with an old display */
    return rx_data[1];
}

static void tft_read_data_ili9341 (uint8 regaddr, uint16 *puiData, uint32 count)
{
    uint16 tx_data;
    /* wait until Spi is no longer busy (should not busy here) */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};
    /* we can use stack variables for exchange because we are waiting until the transfer is finished */
    /* we write first the address (10 bit) */
    /* we change the datawidth to 10 bit */
    g_Qspi_Tft.drivers.spiMasterChannel.bacon.B.DL = 9;
    g_Qspi_Tft.drivers.spiMasterChannel.dataWidth = 10;
    /* calculate the command and address value */
    tx_data = (0x3 << 8) | regaddr;
    /* send the address to ILI9341 */
    IfxQspi_SpiMaster_exchange(&g_Qspi_Tft.drivers.spiMasterChannel, &tx_data, 0, 1);
    /* our values haven 16 bit */
    /* we change the datawidth to 16 bit */
    g_Qspi_Tft.drivers.spiMasterChannel.bacon.B.DL = 15;
    g_Qspi_Tft.drivers.spiMasterChannel.dataWidth = 16;
    /* we wait until our address is send */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};
    /* send the values to ILI9341 */
    IfxQspi_SpiMaster_exchange(&g_Qspi_Tft.drivers.spiMasterChannel, 0, puiData, count);
    /* we wait until our values are send */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};
    /* we terminate the transfer by generate one SCLK without transfer */
    /* we make sure that the SCLK will be low when we switch to general output */
    IfxPort_setPinLow(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex);
    /* set the SCLK to general output */
    IfxPort_setPinMode(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex, IfxPort_Mode_outputPushPullGeneral);
    /* toggle the SCLK */
    IfxPort_togglePin(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex);
    /* toggle the SCLK */
    IfxPort_togglePin(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex);
    /* set the SCLK back to used alternate output */
    IfxPort_setPinMode(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex, IfxPort_Mode_outputPushPullAlt3);
    /* set back to 32 bit transfer */
    g_Qspi_Tft.drivers.spiMasterChannel.bacon.B.DL = 31;
    g_Qspi_Tft.drivers.spiMasterChannel.dataWidth = 32;
}

//uint32 tft_write_data_ili9341 (uint8 regaddr, uint16 *puiData, uint32 count)
static void tft_write_data_ili9341 (uint8 regaddr, uint16 *puiData, uint32 count)
{
    uint16 tx_data;
    /* wait until Spi is no longer busy (should not busy here) */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};
    /* we can use stack variables for exchange because we are waiting until the transfer is finished */
    /* we write first the address (10 bit) */
    /* we change the datawidth to 10 bit */
    g_Qspi_Tft.drivers.spiMasterChannel.bacon.B.DL = 9;
    g_Qspi_Tft.drivers.spiMasterChannel.dataWidth = 10;
    /* calculate the command and address value */
    tx_data = (0x1 << 8) | regaddr;
    /* send the address to ILI9341 */
    IfxQspi_SpiMaster_exchange(&g_Qspi_Tft.drivers.spiMasterChannel, &tx_data, 0, 1);
    /* our values haven 16 bit */
    /* we change the datawidth to 16 bit */
    g_Qspi_Tft.drivers.spiMasterChannel.bacon.B.DL = 15;
    g_Qspi_Tft.drivers.spiMasterChannel.dataWidth = 16;
    /* we wait until our address is send */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};
    /* send the values to ILI9341 */
    IfxQspi_SpiMaster_exchange(&g_Qspi_Tft.drivers.spiMasterChannel, puiData, 0, count);
    /* we wait until our values are send */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};
    /* we terminate the transfer by generate one SCLK without transfer */
    /* we make sure that the SCLK will be low when we switch to general output */
    IfxPort_setPinLow(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex);
    /* set the SCLK to general output */
    IfxPort_setPinMode(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex, IfxPort_Mode_outputPushPullGeneral);
    /* toggle the SCLK */
    IfxPort_togglePin(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex);
    /* toggle the SCLK */
    IfxPort_togglePin(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex);
    /* set the SCLK back to used alternate output */
    IfxPort_setPinMode(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex, IfxPort_Mode_outputPushPullAlt3);
    /* set back to 32 bit transfer */
    g_Qspi_Tft.drivers.spiMasterChannel.bacon.B.DL = 31;
    g_Qspi_Tft.drivers.spiMasterChannel.dataWidth = 32;
}

static uint32 tft_terminate_endless_transfer (void)
{
    // all our values was send
    uint16 tx_data;
    // first we reset the callback function to 0
    pCallbackFunction = (void *)0;
    /* wait until Spi is no longer busy (wait until receive is finished) */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};
    /* we send other 16 bit to write the last value */
    /* we change the datawidth to 16 bit */
    g_Qspi_Tft.drivers.spiMasterChannel.bacon.B.DL = 15;
    g_Qspi_Tft.drivers.spiMasterChannel.dataWidth = 16;
    /* send the value 0 to ILI9341 to write the last word */
    tx_data = 0;
    IfxQspi_SpiMaster_exchange(&g_Qspi_Tft.drivers.spiMasterChannel, &tx_data, 0, 1);
    /* we wait until our values are send */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};
    /* we terminate the transfer by generate one SCLK without transfer */
    /* we make sure that the SCLK will be low when we switch to general output */
    IfxPort_setPinLow(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex);
    /* set the SCLK to general output */
    IfxPort_setPinMode(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex, IfxPort_Mode_outputPushPullGeneral);
    /* toggle the SCLK */
    IfxPort_togglePin(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex);
    /* toggle the SCLK */
    IfxPort_togglePin(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex);
    /* set the SCLK back to used alternate output */
    IfxPort_setPinMode(TFT_USE_SCLK.pin.port, TFT_USE_SCLK.pin.pinIndex, IfxPort_Mode_outputPushPullAlt3);
    /* set back to 32 bit transfer */
    g_Qspi_Tft.drivers.spiMasterChannel.bacon.B.DL = 31;
    g_Qspi_Tft.drivers.spiMasterChannel.dataWidth = 32;
    /* we reset the tft status, no longer busy */
    tft_status = 0;
    return 0;
}

void tft_init (void)
{
    /* prepare LCD background light pin */
        BGL_INIT();

    /* disable interrupts */
    boolean interruptState = IfxCpu_disableInterrupts();
    // CS to tft
    IfxPort_setPinModeInput(TFT_USE_CHIPSELECT.pin.port, TFT_USE_CHIPSELECT.pin.pinIndex, IfxPort_Mode_inputPullUp);

    g_Qspi_Tft.drivers.spiMaster = TFT_QSPI_INIT();
    IfxQspi_SpiMaster_ChannelConfig spiMasterChannelConfig;

    {
        /* create channel config */
#if defined(__DCC__)
        // bug on DCC not all bits in mode are cleared
        memset(&spiMasterChannelConfig, 0, sizeof(spiMasterChannelConfig));
#endif
        IfxQspi_SpiMaster_initChannelConfig(&spiMasterChannelConfig,
            g_Qspi_Tft.drivers.spiMaster);

        /* set the baudrate for this channel */
        spiMasterChannelConfig.base.baudrate = 50000000;

        /* set the transfer data width */
        spiMasterChannelConfig.base.mode.dataWidth = 32;
        spiMasterChannelConfig.base.mode.csLeadDelay = SpiIf_SlsoTiming_1;
        spiMasterChannelConfig.base.mode.csTrailDelay = SpiIf_SlsoTiming_0;
        spiMasterChannelConfig.base.mode.csInactiveDelay = SpiIf_SlsoTiming_0;
        spiMasterChannelConfig.base.mode.shiftClock = SpiIf_ShiftClock_shiftTransmitDataOnTrailingEdge;

        const IfxQspi_SpiMaster_Output slsOutput = {&TFT_USE_CHIPSELECT,
                                                    IfxPort_OutputMode_pushPull,
                                                    IfxPort_PadDriver_cmosAutomotiveSpeed1};

        spiMasterChannelConfig.sls.output.pin    = slsOutput.pin;
        spiMasterChannelConfig.sls.output.mode   = slsOutput.mode;
        spiMasterChannelConfig.sls.output.driver = slsOutput.driver;

        /* initialize channel */
        IfxQspi_SpiMaster_initChannel(&g_Qspi_Tft.drivers.spiMasterChannel,
            &spiMasterChannelConfig);



    }

    /* enable interrupts again */
    IfxCpu_restoreInterrupts(interruptState);

    tft_id = 0;
    pCallbackFunction = (void *)0;

    tft_id = tft_read_data (0x0);

    if (tft_id == 0x0)
    {
        // check for ILI9341 controller
        uint16 uwData[6];
        tft_read_data_ili9341 (0xD3, &uwData[0], 5);
        if ((uwData[3] == 0x0093) && (uwData[4] == 0x0041))
        {
            tft_id = 0x9341;
        }
    }
    //tft_id = 0x9341;
    //tft_id = 0x47;

    if (tft_id == 0x9341)
    {
        // this is an ILI9341 controller
        // we will send max. 15 values + 1 value for last write
        uint16 uwData[16];
        /************* Start Initial Sequence **********/
        uwData[0] = 0x0000;
        uwData[1] = 0x0083;
        uwData[2] = 0x0030;
        uwData[3] = 0x0000;
        tft_write_data_ili9341(0xCF, &uwData[0], 4); // setting from display supplier

        uwData[0] = 0x0064;
        uwData[1] = 0x0003;
        uwData[2] = 0x0012;
        uwData[3] = 0x0081;
        uwData[4] = 0x0000;
        tft_write_data_ili9341(0xED, &uwData[0], 5); // setting from display supplier

        uwData[0] = 0x0085;
        uwData[1] = 0x0000;
        uwData[2] = 0x0078;
        uwData[3] = 0x0000;
        tft_write_data_ili9341(0xE8, &uwData[0], 4); // setting from display supplier

        uwData[0] = 0x0039;
        uwData[1] = 0x002C;
        uwData[2] = 0x0000;
        uwData[3] = 0x0034;
        uwData[4] = 0x0002;
        uwData[5] = 0x0000;
        tft_write_data_ili9341(0xCB, &uwData[0], 6); // setting from display supplier

        uwData[0] = 0x0020;
        uwData[1] = 0x0000;
        tft_write_data_ili9341(0xF7, &uwData[0], 2); // setting from display supplier

        uwData[0] = 0x0000;
        uwData[1] = 0x0000;
        uwData[2] = 0x0000;
        tft_write_data_ili9341(0xEA, &uwData[0], 3); // setting from display supplier

        uwData[0] = 0x0019;  // VRH[5:0]
        uwData[1] = 0x0000;
        tft_write_data_ili9341(0xC0, &uwData[0], 2); // Power Control 1

        uwData[0] = 0x0011;  // SAP[2:0];BT[3:0]
        uwData[1] = 0x0000;
        tft_write_data_ili9341(0xC1, &uwData[0], 2); // Power Control 2



        uwData[0] = 0x003c; // uwData[0] = 0x0031;
        uwData[1] = 0x003f; // uwData[1] = 0x003c;
        uwData[2] = 0x0000;
        tft_write_data_ili9341(0xC5, &uwData[0], 3); // VCM Control 1

        uwData[0] = 0x0090; // uwData[0] = 0x00B0;
        uwData[1] = 0x0000;
        tft_write_data_ili9341(0xC7, &uwData[0], 2); // VCM Control 2
/*
        uwData[0] = 0x0000;
        tft_write_data_ili9341(0x21, &uwData[0], 1); // display inverse
*/

/*
        uwData[0] = 0x003c;
        uwData[1] = 0x003f;
        uwData[2] = 0x0000;
        tft_write_data_ili9341(0xC5, &uwData[0], 3);

        uwData[0] = 0x0090;
        uwData[1] = 0x0000;
        tft_write_data_ili9341(0xC7, &uwData[0], 2);
*/

/*
        uwData[0] = 0x003e;
        uwData[1] = 0x0028;
        uwData[2] = 0x0000;
        tft_write_data_ili9341(0xC5, &uwData[0], 3); // adafruit

        uwData[0] = 0x0086;
        uwData[1] = 0x0000;
        tft_write_data_ili9341(0xC7, &uwData[0], 2); // adafruit
*/

        //uwData[0] = 0x0028;  // MV=1; BGR=1
        uwData[0] = 0x0028; // uwData[0] = 0x0068;
        uwData[1] = 0x0000;
        tft_write_data_ili9341(0x36, &uwData[0], 2); // Memory Access Control




        uwData[0] = 0x0055;  // 16 bit
        uwData[1] = 0x0000;
        tft_write_data_ili9341(0x3A, &uwData[0], 2); // Pixel Format Set

        uwData[0] = 0x0000;
        uwData[1] = 0x0017;
        uwData[2] = 0x0000;
        tft_write_data_ili9341(0xB1, &uwData[0], 3); // Frame Control (in Normal Mode)

        uwData[0] = 0x000A;
        uwData[1] = 0x00A2;
        uwData[2] = 0x0000;
        tft_write_data_ili9341(0xB6, &uwData[0], 3); // Display Function Control

        uwData[0] = 0x0001;
        uwData[1] = 0x0030;
        uwData[2] = 0x0000;
        tft_write_data_ili9341(0xF6, &uwData[0], 3); // Interface Control

        uwData[0] = 0x0000;  // Gamma Function Disable
        uwData[1] = 0x0000;
        tft_write_data_ili9341(0xF2, &uwData[0], 2);  // setting from display supplier

        uwData[0] = 0x0001;     //Gamma curve selected
        uwData[1] = 0x0000;
        tft_write_data_ili9341(0x26, &uwData[0], 2);  // Gamma Set

        uwData[0]  = 0x000F;
        uwData[1]  = 0x0026;
        uwData[2]  = 0x0022;
        uwData[3]  = 0x000A;
        uwData[4]  = 0x0010;
        uwData[5]  = 0x000A;
        uwData[6]  = 0x004C;
        uwData[7]  = 0x00CA;
        uwData[8]  = 0x0036;
        uwData[9]  = 0x0000;
        uwData[10] = 0x0015;
        uwData[11] = 0x0000;
        uwData[12] = 0x0010;
        uwData[13] = 0x0010;
        uwData[14] = 0x0000;
        uwData[15] = 0x0000;
        tft_write_data_ili9341(0xE0, &uwData[0], 16); // Positive Gamma Correction

        uwData[0]  = 0x0000;
        uwData[1]  = 0x0019;
        uwData[2]  = 0x001B;
        uwData[3]  = 0x0005;
        uwData[4]  = 0x000F;
        uwData[5]  = 0x0005;
        uwData[6]  = 0x0033;
        uwData[7]  = 0x0035;
        uwData[8]  = 0x0049;
        uwData[9]  = 0x000F;
        uwData[10] = 0x001F;
        uwData[11] = 0x000F;
        uwData[12] = 0x003F;
        uwData[13] = 0x003F;
        uwData[14] = 0x000F;
        uwData[15] = 0x0000;
        tft_write_data_ili9341(0xE1, &uwData[0], 16); // Negative Gamma Correction

        uwData[0] = 0x0000;
        uwData[1] = 0x0000;
        uwData[2] = ((TFT_XSIZE-1) & 0xFF00)>>8;
        uwData[3] = (TFT_XSIZE-1) & 0x00FF;
        uwData[4] = 0x0000;
        tft_write_data_ili9341(0x2A, &uwData[0], 5);  // Column Address Set

        uwData[0] = 0x0000;
        uwData[1] = 0x0000;
        uwData[2] = ((TFT_YSIZE-1) & 0xFF00)>>8;
        uwData[3] = (TFT_YSIZE-1) & 0x00FF;
        uwData[4] = 0x0000;
        tft_write_data_ili9341(0x2B, &uwData[0], 5);  // Page Address Set

        uwData[0] = 0x0000;
        tft_write_data_ili9341(0x11, &uwData[0], 1);  // Exit Sleep

        delay_ms (120);

        uwData[0] = 0x0000;
        tft_write_data_ili9341(0x29, &uwData[0], 1);  // Display on
    }
    else
    {
        if (tft_id == 0x47)
        {
            // we have a display with HX8347
            //Power on Setting
            tft_write_data (0x0019, 0x0001);    //OSC_EN='1', start Osc
            tft_write_data (0x001F, 0x0088);    // GAS=1, VOMG=00, PON=0, DK=1, XDK=0, DVDH_TRI=0, STB=0
            delay_ms (5);
            tft_write_data (0x001F, 0x0080);    // GAS=1, VOMG=00, PON=0, DK=0, XDK=0, DVDH_TRI=0, STB=0
            delay_ms (5);
            tft_write_data (0x001F, 0x0090);    // GAS=1, VOMG=00, PON=1, DK=0, XDK=0, DVDH_TRI=0, STB=0
            delay_ms (5);
            tft_write_data (0x001F, 0x00D0);    // GAS=1, VOMG=10, PON=1, DK=0, XDK=0, DDVDH_TRI=0, STB=0
            delay_ms (5);
            //262k/65k color selection
            tft_write_data (0x0017, 0x0005);    //default 0x0006 262k color
            // 0x0005 65k color
            //SET PANEL
            //tft_write_data (0x0016, 0x0028);    //MV=1, BRG=1
            tft_write_data (0x0016, 0x0020);    //MV=1, BRG=0
            tft_write_data (0x0036, 0x0000);    //SS_P, GS_P, REV_P, BGR_P
            //Display ON Setting
            tft_write_data (0x0028, 0x0038);    //GON=1, DTE=1, D=1000
            delay_ms (40);
            tft_write_data (0x0028, 0x003C);    //GON=1, DTE=1, D=1100
            //Set GRAM Area
            tft_write_data (0x0002, 0x0000);
            tft_write_data (0x0003, 0x0000);    //Column Start
            tft_write_data (0x0004, 0x0001);
            tft_write_data (0x0005, 0x003F);    //Column End
            tft_write_data (0x0006, 0x0000);
            tft_write_data (0x0007, 0x0000);    //Row Start
            tft_write_data (0x0008, 0x0000);
            tft_write_data (0x0009, 0x00EF);    //Row End

        }
        else
        {
            // we expect that this is an ILI932x
            tft_write_data (0x00, 0x0001);
            tft_write_data (0x01, 0x0100);  // set SM bit (with reg.0x60.GS=1 for rotate the display), was 0000
            tft_write_data (0x02, 0x0700);  // set 1 line inversion
            tft_write_data (0x0003, 0x1038);
            tft_write_data (0x04, 0x0000);  // Resize register
            tft_write_data (0x08, 0x0202);  // set the back porch and front porch
            tft_write_data (0x09, 0x0000);  // set non-display area refresh cycle ISC[3:0]
            tft_write_data (0x0A, 0x0000);  // FMARK function
            //Power On sequence //
            tft_write_data (0x10, 0x0080);  // SAP, BT[3:0], AP, DSTB, SLP, STB
            tft_write_data (0x11, 0x0007);  // DC1[2:0], DC0[2:0], VC[2:0]
            tft_write_data (0x12, 0x0000);  // VREG1OUT voltage
            tft_write_data (0x13, 0x0000);  // VDV[4:0] for VCOM amplitude
            tft_write_data (0x07, 0x0001);  //

            delay_ms (2000);    // Dis-sint8ge capacitor power voltage

            //         tft_write_data(0x10, 0x1790); // SAP, BT[3:0], AP, DSTB, SLP, STB
            tft_write_data (0x10, 0x1290);  // SAP, BT[3:0], AP, DSTB, SLP, STB
            tft_write_data (0x11, 0x0227);  // DC1[2:0], DC0[2:0], VC[2:0]
            delay_ms (1000);    // Delay 50ms
            tft_write_data (0x12, 0x001C);  // Internal reference voltage= Vci;
            delay_ms (1000);    // Delay 50ms
            tft_write_data (0x13, 0x1600);  // Set VDV[4:0] for VCOM amplitude
            tft_write_data (0x29, 0x0012);  // Set VCM[5:0] for VCOMH
            tft_write_data (0x2B, 0x000D);  // Set Frame Rate
            delay_ms (500);     // Delay 50ms

            tft_write_data (0x0020, 0x0000);
            tft_write_data (0x0021, 0x0000);
            // ----------- Adjust the Gamma Curve ----------//
            tft_write_data (0x0030, 0x0007);
            tft_write_data (0x0031, 0x0707);
            tft_write_data (0x0032, 0x0107);
            tft_write_data (0x0035, 0x0206);
            tft_write_data (0x0036, 0x0408);
            tft_write_data (0x0037, 0x0006);
            tft_write_data (0x0038, 0x0000);
            tft_write_data (0x0039, 0x0207);
            tft_write_data (0x003C, 0x0504);
            tft_write_data (0x003D, 0x1501);
            //------------------ Set GRAM area ---------------//
            tft_write_data (0x0050, 0x0000);    // Horizontal GRAM Start Address
            tft_write_data (0x0051, 0x00EF);    // Horizontal GRAM End Address
            tft_write_data (0x0052, 0x0000);    // Vertical GRAM Start Address
            tft_write_data (0x0053, 0x013F);    // Vertical GRAM Start Address
            tft_write_data (0x0060, 0xA700);    // Gate Scan Line was 2700 (set GS=1, with reg.0x01.MS=1 for rotate the display)
            tft_write_data (0x0061, 0x0001);    // NDL,VLE, REV
            tft_write_data (0x006A, 0x0000);    // set scrolling line
            //-------------- Partial Display Control ---------//
            tft_write_data (0x80, 0x0000);
            tft_write_data (0x81, 0x0000);
            tft_write_data (0x82, 0x0000);
            tft_write_data (0x83, 0x0000);
            tft_write_data (0x84, 0x0000);
            tft_write_data (0x85, 0x0000);
            //-------------- Panel Control -------------------//
            tft_write_data (0x90, 0x0010);
            tft_write_data (0x92, 0x0000);
            tft_write_data (0x93, 0x0003);
            tft_write_data (0x95, 0x0110);
            tft_write_data (0x97, 0x0000);
            tft_write_data (0x98, 0x0000);
            tft_write_data (0x07, 0x0173);  // 262K color and display ON   0133
            delay_ms (1000);
        }
    }

    BGL_ON();
}

void tft_display_setxy (uint32 x1,uint32 y1,uint32 x2, uint32 y2)
{
    if (tft_id == 0x9341)
    {
        uint16 uwData[5];


        uwData[0] = (uint16) (x1 >> 8);
        uwData[1] = (uint16) x1;
        uwData[2] = (uint16) (x2 >> 8);
        uwData[3] = (uint16) x2;
        uwData[4] = 0x0000;
        tft_write_data_ili9341(0x2A, &uwData[0], 5);  // Column Address Set, we change only the start (2 Parameters)

        uwData[0] = (uint16) (y1 >> 8);
        uwData[1] = (uint16) y1;
        uwData[2] = (uint16) (y2 >> 8);
        uwData[3] = (uint16) y2;
        uwData[4] = 0x0000;
        tft_write_data_ili9341(0x2B, &uwData[0], 5);  // Page Address Set, we change only the start (2 Parameters)

        uwData[0] = (uint16) (x1 >> 8);
        uwData[1] = (uint16) x1;
        uwData[2] = 0x0000;
        tft_write_data_ili9341(0x2A, &uwData[0], 3);  // Column Address Set, we change only the start (2 Parameters)

        uwData[0] = (uint16) (y1 >> 8);
        uwData[1] = (uint16) y1;
        uwData[2] = 0x0000;
        tft_write_data_ili9341(0x2B, &uwData[0], 3);  // Page Address Set, we change only the start (2 Parameters)

        //uwData[0] = 0x0000;
        //tft_write_data_ili9341(0x2C, &uwData[0], 1);  // Page Address Set, we change only the start (2 Parameters)
    }
    else
    {
        if (tft_id == 0x47)
        {
            tft_write_data (0x0002, (uint16) (x1 >> 8));
            tft_write_data (0x0003, (uint16) x1);    //Column Start
            tft_write_data (0x0006, (uint16) (y1 >> 8));
            tft_write_data (0x0007, (uint16) y1);    //Row Start
        }
        else
        {
            tft_write_data (0x0020, (uint16) y1);
            tft_write_data (0x0021, (uint16) x1);
        }
    }
}

void tft_flush_row_buff( uint32 numberOfPixel, const void * buff)
{

    if (tft_status == 0)
    {
        uint16 tx_data;

        // we write first the address (10 bit)
        // we change the datawidth to 10 bit
        g_Qspi_Tft.drivers.spiMasterChannel.bacon.B.DL = 9;
        g_Qspi_Tft.drivers.spiMasterChannel.dataWidth = 10;
        // calculate the command and address value
        if (tft_id == 0x9341)
            tx_data = (0x1 << 8) | 0x2C; // register 0x2C on ILI9341
        else
            tx_data = (0x1 << 8) | 0x22; // register 0x22 on other

        // wait until Spi is no longer busy (should not busy here)
        while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};
        // send the address to the display
        IfxQspi_SpiMaster_exchange(&g_Qspi_Tft.drivers.spiMasterChannel, &tx_data, 0, 1);
        // set back to 32 bit transfer
        g_Qspi_Tft.drivers.spiMasterChannel.bacon.B.DL = 15;
        g_Qspi_Tft.drivers.spiMasterChannel.dataWidth = 16;
    }

    tft_status = 1; // TFT Busy

    /* wait until Spi is no longer busy (should not busy here) */
    while (IfxQspi_SpiMaster_getStatus(&g_Qspi_Tft.drivers.spiMasterChannel) == SpiIf_Status_busy) {};
    /* send the values to the display */
    IfxQspi_SpiMaster_exchange(&g_Qspi_Tft.drivers.spiMasterChannel, buff, 0, numberOfPixel);
    tft_terminate_endless_transfer();
}


/************************** Local functions ***********************************/

/* write command to LCD and start an endless transfer */
static void wr_cmd_endless(unsigned int cmd)
{
    /* we need 3 free entries */
    while (QSPI0_STATUS.B.TXFIFOLEVEL > (4 - 3))
        ;
    QSPI0_BACONENTRY.U  = (CS_CPLD << IFX_QSPI_BACON_CS_OFF)
                        | (IFX_QSPI_BACON_MSB_MSK << IFX_QSPI_BACON_MSB_OFF)
                        | ((10-1) << IFX_QSPI_BACON_DL_OFF)
                        | (1 << IFX_QSPI_BACON_LEAD_OFF);
    /* start an endless transfer */
    QSPI0_DATAENTRY0.U  = (1 << 8) | cmd;
    /* configure size for endless data transfer */
    QSPI0_MIXENTRY.U    = (CS_CPLD << IFX_QSPI_BACON_CS_OFF)
                        | (IFX_QSPI_BACON_MSB_MSK << IFX_QSPI_BACON_MSB_OFF)
                        | ((16-1) << IFX_QSPI_BACON_DL_OFF)
                        | (1 << IFX_QSPI_BACON_LEAD_OFF);
}

/* write data to LCD in endless transfer mode */
static void wr_dat_endless(unsigned int c)
{
    /* we need 1 free entry */
    while (QSPI0_STATUS.B.TXFIFOLEVEL > (4 - 1))
        ;
    QSPI0_MIXENTRY.U = c;
}

/* terminate an endless data transfer to|from LCD */
static void wr_end_transfer(void)
{
    /* we need 4 free entries */
    while (QSPI0_STATUS.B.TXFIFOLEVEL > (4 - 4))
        ;
    QSPI0_BACONENTRY.U  = (CS_CPLD << IFX_QSPI_BACON_CS_OFF)
                        | (IFX_QSPI_BACON_MSB_MSK << IFX_QSPI_BACON_MSB_OFF)
                        | ((16-1) << IFX_QSPI_BACON_DL_OFF)
                        | (1 << IFX_QSPI_BACON_LEAD_OFF)
                        | (IFX_QSPI_BACON_LAST_MSK << IFX_QSPI_BACON_LAST_OFF);
    QSPI0_DATAENTRY0.U  = 0;
    /* switch to dummy chip select */
    QSPI0_BACONENTRY.U  = (CS_NONE << IFX_QSPI_BACON_CS_OFF)
                        | (IFX_QSPI_BACON_MSB_MSK << IFX_QSPI_BACON_MSB_OFF)
                        | ((9-1) << IFX_QSPI_BACON_DL_OFF)
                        | (1 << IFX_QSPI_BACON_LEAD_OFF)
                        | (IFX_QSPI_BACON_LAST_MSK << IFX_QSPI_BACON_LAST_OFF);
    QSPI0_DATAENTRY0.U  = 0;

    /* wait until all data received */
    while (QSPI0_STATUS.B.RXFIFOLEVEL != 4)
        ;

    /* ... and read and discard the data */
    (void)QSPI0_RXEXIT.U;
    (void)QSPI0_RXEXIT.U;
    (void)QSPI0_RXEXIT.U;
    (void)QSPI0_RXEXIT.U;
}

/* write LCD register <reg> with <value> */
static void wr_reg(unsigned int reg, unsigned int val)
{
    /* we need 2 free entries */
    while (QSPI0_STATUS.B.TXFIFOLEVEL > (4 - 2))
        ;
    QSPI0_BACONENTRY.U  = (CS_CPLD << IFX_QSPI_BACON_CS_OFF)
                        | (IFX_QSPI_BACON_MSB_MSK << IFX_QSPI_BACON_MSB_OFF)
                        | ((32-1) << IFX_QSPI_BACON_DL_OFF)
                        | (1 << IFX_QSPI_BACON_LEAD_OFF)
                        | (IFX_QSPI_BACON_LAST_MSK << IFX_QSPI_BACON_LAST_OFF);
    QSPI0_DATAENTRY0.U  = (reg << 22) | (val << 6);
}

/* read from LCD register <reg> */
static unsigned short rd_reg(unsigned int reg)
{
    unsigned int data;

    /* remove any old stuff from RXFIFO */
    /* read RXFIFO until empty */
    while (QSPI0_STATUS.B.RXFIFOLEVEL != 0)
    {
        (void)QSPI0_RXEXIT.U;
    }
    /* check for RXFIFO overflow and clear this error */
    data = QSPI0_STATUS.B.ERRORFLAGS & QSPI_ERROR_RXOVF;
    if (data)
    {
        QSPI0_FLAGSCLEAR.U = data;
    }

    /* we need 4 free entries */
    while (QSPI0_STATUS.B.TXFIFOLEVEL > (4 - 4))
        ;
    /* we need 16 bit for setting the register */
    QSPI0_BACONENTRY.U  = (CS_CPLD << IFX_QSPI_BACON_CS_OFF)
                        | (IFX_QSPI_BACON_MSB_MSK << IFX_QSPI_BACON_MSB_OFF)
                        | ((16-1) << IFX_QSPI_BACON_DL_OFF)
                        | (1 << IFX_QSPI_BACON_LEAD_OFF);
    /* mark as read register */
    QSPI0_DATAENTRY0.U  = ((1 << 9) | reg) << 6;
    /* we need 26 clocks for reading the data */
    QSPI0_BACONENTRY.U  = (CS_CPLD << IFX_QSPI_BACON_CS_OFF)
                        | (IFX_QSPI_BACON_MSB_MSK << IFX_QSPI_BACON_MSB_OFF)
                        | ((26-1) << IFX_QSPI_BACON_DL_OFF)
                        | (1 << IFX_QSPI_BACON_LEAD_OFF)
                        | (IFX_QSPI_BACON_LAST_MSK << IFX_QSPI_BACON_LAST_OFF);
    QSPI0_DATAENTRY0.U  = 0;

    /* wait until all data received */
    while (QSPI0_STATUS.B.RXFIFOLEVEL != 4)
        ;

    /* ... and read the data */
    (void)QSPI0_RXEXIT.U;
    (void)QSPI0_RXEXIT.U;
    data = QSPI0_RXEXIT.U;
    (void)QSPI0_RXEXIT.U;

    return (unsigned short)data;
}

/* read from LCD register <reg> in endless transfer mode */
static unsigned short rd_reg_endless(unsigned int reg)
{
    unsigned int data;

    /* we need 4 free entries */
    while (QSPI0_STATUS.B.TXFIFOLEVEL > (4 - 4))
        ;
    /* we need 16 bit for setting the register */
    QSPI0_BACONENTRY.U  = (CS_CPLD << IFX_QSPI_BACON_CS_OFF)
                        | (IFX_QSPI_BACON_MSB_MSK << IFX_QSPI_BACON_MSB_OFF)
                        | ((16-1) << IFX_QSPI_BACON_DL_OFF)
                        | (1 << IFX_QSPI_BACON_LEAD_OFF);
    /* mark as read register in endless mode */
    QSPI0_DATAENTRY0.U  = ((1 << 9) | (1 << 8) | reg) << 6;
    /* we need 10 clocks for reading the data + 16 for skipping first dummy */
    QSPI0_BACONENTRY.U  = (CS_CPLD << IFX_QSPI_BACON_CS_OFF)
                        | (IFX_QSPI_BACON_MSB_MSK << IFX_QSPI_BACON_MSB_OFF)
                        | ((26-1) << IFX_QSPI_BACON_DL_OFF)
                        | (1 << IFX_QSPI_BACON_LEAD_OFF);
    QSPI0_DATAENTRY0.U  = 0;

    /* wait until all data received */
    while (QSPI0_STATUS.B.RXFIFOLEVEL != 4)
        ;

    /* ... and read the data */
    (void)QSPI0_RXEXIT.U;
    (void)QSPI0_RXEXIT.U;
    data = QSPI0_RXEXIT.U;
    (void)QSPI0_RXEXIT.U;

    return (unsigned short)data;
}

/* read data from LCD in endless transfer mode */
static unsigned short rd_dat_endless(void)
{
    unsigned int data;

    /* we need 2 free entries */
    while (QSPI0_STATUS.B.TXFIFOLEVEL > (4 - 2))
        ;
    /* we need 16 bit for setting the register */
    QSPI0_BACONENTRY.U  = (CS_CPLD << IFX_QSPI_BACON_CS_OFF)
                        | (IFX_QSPI_BACON_MSB_MSK << IFX_QSPI_BACON_MSB_OFF)
                        | ((16-1) << IFX_QSPI_BACON_DL_OFF)
                        | (1 << IFX_QSPI_BACON_LEAD_OFF);
    /* no data */
    QSPI0_DATAENTRY0.U  = 0;

    /* wait until all data received */
    while (QSPI0_STATUS.B.RXFIFOLEVEL != (4 - 2))
        ;

    /* ... and read the data */
    data = QSPI0_RXEXIT.U;
    (void)QSPI0_RXEXIT.U;

    return (unsigned short)data;
}

/* read ID code of LCD controller */
static unsigned short get_id_code(void)
{
    /* start with reg 0 (returns ID for ILI932x) */
    unsigned short id = rd_reg(0x00);

    if (0 == id)
    {
        /* try special test for ILI9341 */
        unsigned short temp;
        /* Read ID4 register: first byte returned is ignored */
        (void)rd_reg_endless(0xD3);
        temp = rd_dat_endless();
        if (0 == temp)
        {
            temp = rd_dat_endless();
            id = (temp & 0xFF) << 8;
            temp = rd_dat_endless();
            id |= (temp & 0xFF);
        }
        /* finish endless transfer mode */
        wr_end_transfer();
    }

    return id;
}


static void glcd_set_position(unsigned int x, unsigned int y)
{
    if (tft_id == 0x9341)
    {
        wr_cmd_endless(0x2B);   /* Page Address Set: only start is set */
        wr_dat_endless(x >> 8);
        wr_dat_endless(x);
        wr_end_transfer();
        wr_cmd_endless(0x2A);   /* Column Address Set: only start is set */
        wr_dat_endless(y >> 8);
        wr_dat_endless(y);
        wr_end_transfer();
    }
    else
    {
        wr_reg(0x20, x);
        wr_reg(0x21, y);
    }
}

static void glcd_start_GRAM_write(void)
{
    if (tft_id == 0x9341)
    {
        wr_cmd_endless(0x2C);   /* Memory Write */
    }
    else
    {
        wr_cmd_endless(0x22);
    }
}

static void glcd_set_graph_window(unsigned int x0, unsigned int x1, unsigned int y0, unsigned int y1)
{
    if (tft_id == 0x9341)
    {
        wr_cmd_endless(0x2B);   /* Page Address Set */
        wr_dat_endless(x0 >> 8);
        wr_dat_endless(x0);
        wr_dat_endless(x1 >> 8);
        wr_dat_endless(x1);
        wr_end_transfer();
        wr_cmd_endless(0x2A);   /* Column Address Set */
        wr_dat_endless(y0 >> 8);
        wr_dat_endless(y0);
        wr_dat_endless(y1 >> 8);
        wr_dat_endless(y1);
        wr_end_transfer();
    }
    else
    {
        wr_reg(0x50, x0);       /* Horizontal GRAM Start Address */
        wr_reg(0x51, x1);       /* Horizontal GRAM End   Address */
        wr_reg(0x52, y0);       /* Vertical   GRAM Start Address */
        wr_reg(0x53, y1);       /* Vertical   GRAM End   Address */
    }
}

/*******************************************************************************
* Draw character on given position (line, coloum)                              *
*   Parameter:     x :        horizontal position                              *
*                  y :        vertical position                                *
*                 *c :        pointer to character definition                  *
*   Return:                                                                    *
*******************************************************************************/
static void GLCD_drawChar(unsigned int x, unsigned int y, const unsigned short *c)
{
    unsigned int index = 0;
    int  i = 0;
    unsigned int Xaddress = x;

    glcd_set_position(Xaddress, y);

    for (index = 0; index < CHAR_HEIGHT; ++index)
    {
        glcd_start_GRAM_write();    /* Prepare to write GRAM */
        for (i = 0; i < CHAR_WIDTH; ++i)
        {
            if ((c[index] & (1 << i)) == 0x00)
            {
                wr_dat_endless(BackColor);
            }
            else
            {
                wr_dat_endless(TextColor);
            }
        }
#ifdef USE_NORMAL_VDIR
        ++Xaddress;
#else
        --Xaddress;
#endif /* USE_NORMAL_VDIR */
        wr_end_transfer();
        glcd_set_position(Xaddress, y);
    }
}

/************************ Exported functions **********************************/

/*******************************************************************************
* Initialise the Graphic LCD controller                                        *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_putPixel(unsigned int x, unsigned int y)
{
    glcd_set_position(x, y);
    glcd_start_GRAM_write();
    wr_dat_endless(TextColor);
    wr_end_transfer();
}

/*******************************************************************************
* Set foreground color                                                         *
*   Parameter:    color:  color for clearing display                           *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_setTextColor(unsigned short color)
{
    TextColor = color;
}

/*******************************************************************************
* Set background color                                                         *
*   Parameter:    color:  color for clearing display                           *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_setBackColor(unsigned short color)
{
    BackColor = color;
}

/*******************************************************************************
* Clear display                                                                *
*   Parameter:    color:  color for clearing display                           *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_clear(unsigned short color)
{
    unsigned int    i;

    glcd_set_position(0, 0);
    glcd_start_GRAM_write();
    for (i = 0; i < (WIDTH*HEIGHT); ++i)
    {
        wr_dat_endless(color);
    }
    wr_end_transfer();
}

/*******************************************************************************
* Display character on given line                                              *
*   Parameter:     c :        ascii character                                  *
*                  ln:        line number                                      *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_displayChar(unsigned int ln, unsigned int col, unsigned char c)
{
    /* check for characters in our font table */
    if (isfontchar(c))
    {
        c -= 32;
        GLCD_drawChar(ln, col, &ASCII_Table[c * CHAR_HEIGHT]);
    }
}

/*******************************************************************************
* Display string on given line                                                 *
*   Parameter:     *s:        pointer to string                                *
*                  ln:        line number                                      *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_displayStringLn(unsigned int ln, const char *s)
{
    unsigned int i = 0;
    unsigned int refcolumn = 0;

    /* write the string character by character on LCD */
    while ((*s != 0) && (i < (LCD_WIDTH / CHAR_WIDTH)))
    {
        GLCD_displayChar(ln, refcolumn, *s);
        refcolumn += CHAR_WIDTH;                /* next column position */
        s++;                                    /* next character */
        i++;                                    /* count characters */
    }
}

/*******************************************************************************
* Clear given line                                                             *
*   Parameter:     ln:        line number                                      *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_clearLn(unsigned int ln)
{
    GLCD_displayStringLn(ln, "                    ");
}

/*******************************************************************************
* Display graphical bitmap image at position x horizontally and y vertically   *
* (This function is optimized for 16 bits per pixel format, it has to be       *
*  adapted for any other bits per pixel format)                                *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*                   w:        width of bitmap                                  *
*                   h:        height of bitmap                                 *
*                   bitmap:   address at which the bitmap data resides         *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_bitmap(unsigned int x, unsigned int y, unsigned int w, unsigned int h, const void *bitmap)
{
    unsigned int   i;
    unsigned int   len = w*h;
    unsigned short *bitmap_ptr = (unsigned short *)bitmap;

    /* set a graphic window for the bitmap */
    glcd_set_graph_window(y, y+h-1, x, x+w-1);

    glcd_set_position(y, x);

    glcd_start_GRAM_write();    /* Prepare to write GRAM */
    for (i = 0; i < len; ++i)
    {
        wr_dat_endless(*bitmap_ptr++);
    }
    wr_end_transfer();

    /* restore complete window */
    glcd_set_graph_window(0, (HEIGHT-1), 0, (WIDTH-1));
}

int GLCD_getLineNo(unsigned int line)
{
    switch (line)
    {
        case 0:  return LINE0;
        case 1:  return LINE1;
        case 2:  return LINE2;
        case 3:  return LINE3;
        case 4:  return LINE4;
        case 5:  return LINE5;
        case 6:  return LINE6;
        case 7:  return LINE7;
        case 8:  return LINE8;
        case 9:  return LINE9;
        default: return -1;
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
void EscreveByteLCD(unsigned char linha, unsigned char coluna, unsigned char data)
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
    while(_j<3)
        {
        GLCD_displayChar(linha,coluna,ASCII[_j]);
            ++_j;
            coluna = coluna + 14;
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
void EscreveWordLCD(unsigned char linha,unsigned char coluna, unsigned int data )
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

    while(_j<5)
    {
        GLCD_displayChar(linha,coluna,(unsigned char)ASCII[_j]);
        ++_j;
        coluna = coluna + 15;
    }
}
/******************************************************************************/
