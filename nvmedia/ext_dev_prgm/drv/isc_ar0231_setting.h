/*
 * Copyright (c) 2016-2017, NVIDIA CORPORATION.  All rights reserved. All
 * information contained herein is proprietary and confidential to NVIDIA
 * Corporation.  Any use, reproduction, or disclosure without the written
 * permission of NVIDIA Corporation is prohibited.
 */
#ifndef _AR0231_SETTING_H_
#define _AR0231_SETTING_H_

#define AR0231_VER_6             6u
#define AR0231_VER_4             4u
#define AR0231_VER_3_OR_OLDER    3u

/* Fine Integration time for 3-exp HDR */
#define AR0231_FINE_INTEG_TIME_V6(hts) ((hts) - 278u)
#define AR0231_FINE_INTEG_TIME_V4(hts) ((hts) - 276u)

#define AR0231_FINE_INTEG_TIME_V3_T1 0x352
#define AR0231_FINE_INTEG_TIME_V3_T2 0x5BB
#define AR0231_FINE_INTEG_TIME_V3_T3 0x1E8

#define AR0231_ACTIVE_H  1920u

#define AR0231_HTS       2162u
#define AR0231_VTS_30FPS 1354u
#define AR0231_VTS_36FPS 1130u

#define AR0231_VTS_30FPS_EXTSYNC 1344u
#define AR0231_VTS_36FPS_EXTSYNC 1120u

#define AR0231_PCLK   88000000  //Hz

typedef struct {
    unsigned int hts;
    unsigned int vts;
    const unsigned char *settings;
} TimingSettingAR0231;

static const NvU8 ar0231_raw12_default[] = { //v6
    //Disable Streaming
    'w', 4, 0x30, 0x1A, 0x10, 0x58, // RESET_REGISTER
    'd',    0x27, 0x01,             // Delay 1ms
    // Sensor gain
    'w', 8, 0x33, 0x62, 0x00, 0x00, 0x00, 0x60, 0x77, 0x77,
    'w', 10, 0x30, 0x56, 0x00, 0x80, 0x00, 0xE9, 0x00, 0xA7, 0x00, 0x80, //GBRG 1.0,1.82,1.3,1.0
    // Design recomannended settings
    'w', 4, 0x31, 0x38, 0x00, 0x0B,
    'w', 6, 0x31, 0x8E, 0x02, 0x00, 0x50, 0x00, // DLO_CONTROL0/1
    //'w', 4, 0x31, 0x94, 0x50, 0x80, // DLO_CONTROL3,reduce ghost color?
    'w', 10, 0x32, 0x90, 0x0F, 0xC0, 0x0F, 0xC0, 0x0F, 0xC0, 0x0F, 0xC0, // T3 barrier
    'w', 4, 0x33, 0x72, 0xF5, 0x4F, // DBLC_FS0_CONTROL
    'w', 4, 0x33, 0x7A, 0x0D, 0x70,
    'w', 4, 0x33, 0x7E, 0x1F, 0xFD,
    'w', 4, 0x33, 0x82, 0x00, 0xC0,
    'w', 4, 0x3C, 0x04, 0x0E, 0x80, // RNC_BIAS
    'w', 6, 0x3F, 0x90, 0x06, 0xE1, 0x06, 0xE1, // TEMPVSENS0/1_TMG_CTRL
    'w', 12, 0x35, 0x06, 0x44, 0x44, 0x44, 0x44, 0x44, 0x65, 0x05, 0x5F,
                         0xFF, 0x10, // DAC_LD_6_7, 8_9, 10_11
    'w', 4, 0x35, 0x18, 0x1F, 0xFE, // DAC_LD_24_25
    'w', 8, 0x35, 0x20, 0xC6, 0x88, 0x88, 0xC0, 0xC0, 0xC6,
    'w', 12, 0x35, 0x28, 0xDD, 0xDD, 0x08, 0x9F, 0xC6, 0xC6, 0x00, 0x11,
                         0x44, 0x00,
    'w', 10, 0x35, 0x36, 0xFF, 0x06, 0xFF, 0xFF, 0x90, 0x00, 0x3F, 0x00,
    'w', 12, 0x35, 0x40, 0xC6, 0x37, 0x46, 0x4B, 0x4B, 0x5A, 0x5A, 0x5A,
                         0x64, 0x00,
    'w', 4, 0x35, 0x56, 0x10, 0x1F,
    'w', 4, 0x35, 0x66, 0x33, 0x28,
    //Sequencer
    'w', 4, 0x25, 0x12, 0x80, 0x00,
    'w', 4, 0x25, 0x10, 0x09, 0x05,
    'w', 4, 0x25, 0x10, 0x33, 0x50,
    'w', 4, 0x25, 0x10, 0x20, 0x04,
    'w', 4, 0x25, 0x10, 0x14, 0x60,
    'w', 4, 0x25, 0x10, 0x15, 0x78,
    'w', 4, 0x25, 0x10, 0x13, 0x60,
    'w', 4, 0x25, 0x10, 0x7b, 0x24,
    'w', 4, 0x25, 0x10, 0xff, 0x24,
    'w', 4, 0x25, 0x10, 0xff, 0x24,
    'w', 4, 0x25, 0x10, 0xea, 0x24,
    'w', 4, 0x25, 0x10, 0x10, 0x22,
    'w', 4, 0x25, 0x10, 0x24, 0x10,
    'w', 4, 0x25, 0x10, 0x15, 0x5a,
    'w', 4, 0x25, 0x10, 0x13, 0x42,
    'w', 4, 0x25, 0x10, 0x14, 0x00,
    'w', 4, 0x25, 0x10, 0x24, 0xff,
    'w', 4, 0x25, 0x10, 0x24, 0xff,
    'w', 4, 0x25, 0x10, 0x24, 0xea,
    'w', 4, 0x25, 0x10, 0x23, 0x24,
    'w', 4, 0x25, 0x10, 0x64, 0x7a,
    'w', 4, 0x25, 0x10, 0x24, 0x04,
    'w', 4, 0x25, 0x10, 0x05, 0x2c,
    'w', 4, 0x25, 0x10, 0x40, 0x0a,
    'w', 4, 0x25, 0x10, 0xff, 0x0a,
    'w', 4, 0x25, 0x10, 0xff, 0x0a,
    'w', 4, 0x25, 0x10, 0x18, 0x08,
    'w', 4, 0x25, 0x10, 0x38, 0x51,
    'w', 4, 0x25, 0x10, 0x14, 0x40,
    'w', 4, 0x25, 0x10, 0x00, 0x04,
    'w', 4, 0x25, 0x10, 0x08, 0x01,
    'w', 4, 0x25, 0x10, 0x04, 0x08,
    'w', 4, 0x25, 0x10, 0x11, 0x80,
    'w', 4, 0x25, 0x10, 0x15, 0xdc,
    'w', 4, 0x25, 0x10, 0x13, 0x4c,
    'w', 4, 0x25, 0x10, 0x10, 0x02,
    'w', 4, 0x25, 0x10, 0x10, 0x16,
    'w', 4, 0x25, 0x10, 0x11, 0x81,
    'w', 4, 0x25, 0x10, 0x11, 0x89,
    'w', 4, 0x25, 0x10, 0x10, 0x56,
    'w', 4, 0x25, 0x10, 0x12, 0x10,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x0d, 0x08,
    'w', 4, 0x25, 0x10, 0x09, 0x13,
    'w', 4, 0x25, 0x10, 0x13, 0xc8,
    'w', 4, 0x25, 0x10, 0x09, 0x2b,
    'w', 4, 0x25, 0x10, 0x15, 0x88,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x13, 0x88,
    'w', 4, 0x25, 0x10, 0x09, 0x09,
    'w', 4, 0x25, 0x10, 0x11, 0xd9,
    'w', 4, 0x25, 0x10, 0x09, 0x1d,
    'w', 4, 0x25, 0x10, 0x14, 0x41,
    'w', 4, 0x25, 0x10, 0x09, 0x03,
    'w', 4, 0x25, 0x10, 0x12, 0x14,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x10, 0xd6,
    'w', 4, 0x25, 0x10, 0x12, 0x10,
    'w', 4, 0x25, 0x10, 0x12, 0x12,
    'w', 4, 0x25, 0x10, 0x12, 0x10,
    'w', 4, 0x25, 0x10, 0x11, 0xdd,
    'w', 4, 0x25, 0x10, 0x11, 0xd9,
    'w', 4, 0x25, 0x10, 0x10, 0x56,
    'w', 4, 0x25, 0x10, 0x09, 0x05,
    'w', 4, 0x25, 0x10, 0x11, 0xdb,
    'w', 4, 0x25, 0x10, 0x09, 0x2b,
    'w', 4, 0x25, 0x10, 0x11, 0x9b,
    'w', 4, 0x25, 0x10, 0x11, 0xbb,
    'w', 4, 0x25, 0x10, 0x12, 0x1a,
    'w', 4, 0x25, 0x10, 0x12, 0x10,
    'w', 4, 0x25, 0x10, 0x14, 0x60,
    'w', 4, 0x25, 0x10, 0x12, 0x50,
    'w', 4, 0x25, 0x10, 0x10, 0x76,
    'w', 4, 0x25, 0x10, 0x10, 0xe6,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x15, 0xab,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x13, 0xa8,
    'w', 4, 0x25, 0x10, 0x12, 0x40,
    'w', 4, 0x25, 0x10, 0x12, 0x60,
    'w', 4, 0x25, 0x10, 0x09, 0x23,
    'w', 4, 0x25, 0x10, 0x15, 0x8d,
    'w', 4, 0x25, 0x10, 0x13, 0x8d,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x0b, 0x09,
    'w', 4, 0x25, 0x10, 0x01, 0x08,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x14, 0x40,
    'w', 4, 0x25, 0x10, 0x09, 0x1d,
    'w', 4, 0x25, 0x10, 0x15, 0x88,
    'w', 4, 0x25, 0x10, 0x13, 0x88,
    'w', 4, 0x25, 0x10, 0x09, 0x2d,
    'w', 4, 0x25, 0x10, 0x10, 0x66,
    'w', 4, 0x25, 0x10, 0x09, 0x05,
    'w', 4, 0x25, 0x10, 0x0c, 0x08,
    'w', 4, 0x25, 0x10, 0x09, 0x0b,
    'w', 4, 0x25, 0x10, 0x14, 0x41,
    'w', 4, 0x25, 0x10, 0x09, 0x0d,
    'w', 4, 0x25, 0x10, 0x10, 0xe6,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x12, 0x62,
    'w', 4, 0x25, 0x10, 0x12, 0x60,
    'w', 4, 0x25, 0x10, 0x11, 0xbf,
    'w', 4, 0x25, 0x10, 0x11, 0xbb,
    'w', 4, 0x25, 0x10, 0x10, 0x66,
    'w', 4, 0x25, 0x10, 0x11, 0xfb,
    'w', 4, 0x25, 0x10, 0x09, 0x35,
    'w', 4, 0x25, 0x10, 0x11, 0xbb,
    'w', 4, 0x25, 0x10, 0x12, 0x63,
    'w', 4, 0x25, 0x10, 0x12, 0x60,
    'w', 4, 0x25, 0x10, 0x14, 0x00,
    'w', 4, 0x25, 0x10, 0x15, 0x10,
    'w', 4, 0x25, 0x10, 0x11, 0xb8,
    'w', 4, 0x25, 0x10, 0x12, 0xa0,
    'w', 4, 0x25, 0x10, 0x12, 0x00,
    'w', 4, 0x25, 0x10, 0x10, 0x26,
    'w', 4, 0x25, 0x10, 0x10, 0x00,
    'w', 4, 0x25, 0x10, 0x13, 0x42,
    'w', 4, 0x25, 0x10, 0x11, 0x00,
    'w', 4, 0x25, 0x10, 0x7a, 0x06,
    'w', 4, 0x25, 0x10, 0x09, 0x13,
    'w', 4, 0x25, 0x10, 0x05, 0x07,
    'w', 4, 0x25, 0x10, 0x08, 0x41,
    'w', 4, 0x25, 0x10, 0x37, 0x50,
    'w', 4, 0x25, 0x10, 0x2c, 0x2c,
    'w', 4, 0x25, 0x10, 0xfe, 0x05,
    'w', 4, 0x25, 0x10, 0xfe, 0x13,
    // FINE INTEGRATION TIME MINS
    'w', 4, 0x10, 0x08, 0x03, 0x61,
    'w', 8, 0x10, 0x0C, 0x05, 0x89, 0x07, 0xB1, 0x01, 0x39,
    // FINE_CORRECTION
    'w', 10, 0x32, 0x30, 0x03, 0x04, 0x05, 0x2c, 0x07, 0x54, 0x00, 0xdc,
    // PLL 27MHz In -88MHz out
                // VT_PIX_CLK_DIV, VT_SYS_CLK_DIV, PRE_PLL_CLK_DIV, PLL_MULTIPLIER
    'w', 10, 0x30, 0x2A, 0x00, 0x06, 0x00, 0x01, 0x00, 0x09, 0x00, 0xB0,
    'w', 6, 0x30, 0x36, 0x00, 0x08, 0x00, 0x01, // OP_WORD_CLK_DIV, OP_SYS_CLK_DIV
    'w', 4, 0x30, 0xB0, 0x0B, 0x02, // DIGITAL_TEST
    // Readout Mode Configuration
    'w', 8, 0x30, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, // READ_MODE, EXTRA_DELAY, DARK_CONTROL
    'w', 4, 0x30, 0x64, 0x19, 0x02, // SMIA_TEST, enable top embedded data
    'w', 4, 0x31, 0x80, 0x00, 0x80,
    'w', 4, 0x33, 0xE4, 0x00, 0x00, // 0X00, 0x80
    // Timing
    'w', 4, 0x30, 0x32, 0x00, 0x00, // SCALING_MODE
    'w', 8, 0x34, 0x00, 0x00, 0x10, 0x0F, 0x10, 0x09, 0x70,
    // 3 exp Timing
    'w', 4, 0x30, 0x82, 0x00, 0x00 + (((NVMEDIA_ISC_EXPOSURE_MODE_MAX - 1) << 2) & 0xF), // OPERATION_MODE_CTRL
    'w', 4, 0x30, 0xBA, 0x11, 0xE2, // DIGITAL_CTRL
    // Exposure ratio and time
    'w', 4, 0x32, 0x38, 0x87, 0x77, // EXPOSURE_RATIO, use reg
    'w', 4, 0x30, 0x12, 0x03, 0x00, // COARSE_INTEGRATION_TIME_
    'w', 4, 0x32, 0x12, 0x00, 0x30, // COARSE_INTEGRATION_TIME_2
    'w', 4, 0x32, 0x16, 0x00, 0x03, // COARSE_INTEGRATION_TIME_3
    'w', 6, 0x32, 0xEA, 0x3C, 0x0E, 0x72, 0xA1,
    // GPIO control  // ENABLE GPIO3 to trigger fsync
    'w', 6, 0x34, 0x0A, 0x00, 0x77, 0x00, 0x80,
    'w', 4, 0x30, 0xCE, 0x01, 0x20, // enable synchronization
    // Parallel HDR 12 bit Output
    'w', 4, 0x31, 0xD0, 0x00, 0x01, // COMPANDING
    'w', 6, 0x31, 0xAC, 0x14, 0x0C, 0x00, 0x01, // DATA_FORMAT_BITS, SERIAL_FORMAT
    'e'
};

static const NvU8 ar0231_raw12_default_v3[] = {  //v3 or before
    // Disable Streaming
    'w', 4, 0x30, 0x1A, 0x10, 0x58, // RESET_REGISTER
    'd',    0x27, 0x01,             // Delay 1ms
    // Sensor gain
    'w', 4, 0x30, 0xFE, 0x00, 0x20, // NOISE_PEDESTAL
    'w', 8, 0x33, 0x62, 0x00, 0x00, 0x00, 0x60, 0x77, 0x77, // DC_GAIN, DCG_TRIM, ANALOG_GAIN
    'w', 10, 0x30, 0x56, 0x00, 0x80, 0x00, 0xE9, 0x00, 0xA7, 0x00, 0x80, //GBRG gain
    'w', 4, 0x31, 0x8E, 0x02, 0x00, // DLO_CONTROL0
    // Design recomannended settings
    'w', 4, 0x32, 0xE2, 0x20, 0x00, // SHUT_DCG_BOOST
    'w', 4, 0x33, 0x70, 0x02, 0x31, // DBLC_CONTROl
    'w', 4, 0x33, 0x86, 0x00, 0x00, // DBLC_PEDESTAL
    'w', 6, 0x35, 0x00, 0x01, 0x00, 0x08, 0x08,
    'w', 10, 0x35, 0x06, 0x33, 0x44, 0x44, 0x33, 0x33, 0x88, 0x0A, 0x5F,// DAC_LD_6_7, 8_9, 10_11
    'w', 4, 0x35, 0x10, 0x00, 0x00,
    'w', 4, 0x35, 0x14, 0x01, 0x06,
    'w', 4, 0x35, 0x18, 0x1F, 0xFE,
    'w', 20, 0x35, 0x20, 0xC6, 0x88, 0x88, 0xC6, 0xC6, 0xC6, 0x00, 0x00,
             0x99, 0x99, 0x08, 0x1F, 0xC6, 0xC6, 0x00, 0x11, 0x44, 0x00,
    'w', 12, 0x35, 0x34, 0x00, 0x00, 0xFF, 0x06, 0xFF, 0xFF, 0x00, 0x00,
             0x3F, 0x00,
    'w', 12, 0x35, 0x40, 0xC6, 0x44, 0x54, 0x5B, 0x64, 0x46, 0x54, 0x5B,
             0x62, 0x30,
    'w', 4, 0x35, 0x50, 0x0D, 0x28,
    'w', 4, 0x35, 0x56, 0x10, 0x1F,
    'w', 8, 0x35, 0x5A, 0x0D, 0x0C, 0x01, 0x40, 0x10, 0x01,
    'w', 6, 0x35, 0x66, 0x33, 0x28, 0x00, 0x00,
    'w', 6, 0x3C, 0x02, 0x00, 0x00, 0x0F, 0x00, // READOUT_UNBIAS, RNC_BIAS
    'w', 6, 0x3F, 0x90, 0x06, 0xE1, 0x06, 0xE1, // TEMPVSENS0/1_TMG_CTRL
    // Sequencer
    'w', 4, 0x25, 0x12, 0x80, 0x00, // SEQ_CTRL_PORT
    'w', 4, 0x25, 0x10, 0x09, 0x05, // SEQ_DATA_PORT
    'w', 4, 0x25, 0x10, 0x33, 0x50,
    'w', 4, 0x25, 0x10, 0x20, 0x04,
    'w', 4, 0x25, 0x10, 0x14, 0x60,
    'w', 4, 0x25, 0x10, 0x15, 0x78,
    'w', 4, 0x25, 0x10, 0x13, 0x60,
    'w', 4, 0x25, 0x10, 0x7B, 0x24,
    'w', 4, 0x25, 0x10, 0xFF, 0x24,
    'w', 4, 0x25, 0x10, 0xFF, 0x24,
    'w', 4, 0x25, 0x10, 0xEA, 0x24,
    'w', 4, 0x25, 0x10, 0x10, 0x22,
    'w', 4, 0x25, 0x10, 0x24, 0x10,
    'w', 4, 0x25, 0x10, 0x15, 0x5A,
    'w', 4, 0x25, 0x10, 0x13, 0x42,
    'w', 4, 0x25, 0x10, 0x14, 0x00,
    'w', 4, 0x25, 0x10, 0x24, 0xFF,
    'w', 4, 0x25, 0x10, 0x24, 0xFF,
    'w', 4, 0x25, 0x10, 0x24, 0xEA,
    'w', 4, 0x25, 0x10, 0x23, 0x24,
    'w', 4, 0x25, 0x10, 0x64, 0x7A,
    'w', 4, 0x25, 0x10, 0x24, 0x04,
    'w', 4, 0x25, 0x10, 0x05, 0x2C,
    'w', 4, 0x25, 0x10, 0x40, 0x0A,
    'w', 4, 0x25, 0x10, 0xFF, 0x0A,
    'w', 4, 0x25, 0x10, 0xFF, 0x0A,
    'w', 4, 0x25, 0x10, 0x05, 0x38,
    'w', 4, 0x25, 0x10, 0x51, 0x14,
    'w', 4, 0x25, 0x10, 0x40, 0x15,
    'w', 4, 0x25, 0x10, 0x5C, 0x13,
    'w', 4, 0x25, 0x10, 0x4C, 0x00,
    'w', 4, 0x25, 0x10, 0x04, 0x08,
    'w', 4, 0x25, 0x10, 0x01, 0x04,
    'w', 4, 0x25, 0x10, 0x08, 0x11,
    'w', 4, 0x25, 0x10, 0x80, 0x10,
    'w', 4, 0x25, 0x10, 0x02, 0x10,
    'w', 4, 0x25, 0x10, 0x16, 0x11,
    'w', 4, 0x25, 0x10, 0x81, 0x11,
    'w', 4, 0x25, 0x10, 0x89, 0x10,
    'w', 4, 0x25, 0x10, 0x56, 0x12,
    'w', 4, 0x25, 0x10, 0x10, 0x09,
    'w', 4, 0x25, 0x10, 0x01, 0x11,
    'w', 4, 0x25, 0x10, 0x89, 0x0D,
    'w', 4, 0x25, 0x10, 0x09, 0x07,
    'w', 4, 0x25, 0x10, 0x14, 0x40,
    'w', 4, 0x25, 0x10, 0x09, 0x02,
    'w', 4, 0x25, 0x10, 0x13, 0x4C,
    'w', 4, 0x25, 0x10, 0x15, 0xCC,
    'w', 4, 0x25, 0x10, 0x13, 0xCC,
    'w', 4, 0x25, 0x10, 0x09, 0x1E,
    'w', 4, 0x25, 0x10, 0x13, 0xCC,
    'w', 4, 0x25, 0x10, 0x15, 0xCC,
    'w', 4, 0x25, 0x10, 0x15, 0x88,
    'w', 4, 0x25, 0x10, 0x13, 0x88,
    'w', 4, 0x25, 0x10, 0x14, 0x00,
    'w', 4, 0x25, 0x10, 0x09, 0x1E,
    'w', 4, 0x25, 0x10, 0x11, 0x99,
    'w', 4, 0x25, 0x10, 0x11, 0xD9,
    'w', 4, 0x25, 0x10, 0x09, 0x2F,
    'w', 4, 0x25, 0x10, 0x12, 0x14,
    'w', 4, 0x25, 0x10, 0x10, 0xD6,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x12, 0x10,
    'w', 4, 0x25, 0x10, 0x12, 0x12,
    'w', 4, 0x25, 0x10, 0x12, 0x10,
    'w', 4, 0x25, 0x10, 0x11, 0xDD,
    'w', 4, 0x25, 0x10, 0x11, 0xD9,
    'w', 4, 0x25, 0x10, 0x09, 0x03,
    'w', 4, 0x25, 0x10, 0x14, 0x01,
    'w', 4, 0x25, 0x10, 0x09, 0x08,
    'w', 4, 0x25, 0x10, 0x10, 0x56,
    'w', 4, 0x25, 0x10, 0x09, 0x04,
    'w', 4, 0x25, 0x10, 0x11, 0xDB,
    'w', 4, 0x25, 0x10, 0x09, 0x03,
    'w', 4, 0x25, 0x10, 0x11, 0xFB,
    'w', 4, 0x25, 0x10, 0x11, 0xBB,
    'w', 4, 0x25, 0x10, 0x12, 0x1A,
    'w', 4, 0x25, 0x10, 0x12, 0x10,
    'w', 4, 0x25, 0x10, 0x10, 0x56,
    'w', 4, 0x25, 0x10, 0x12, 0x50,
    'w', 4, 0x25, 0x10, 0x10, 0x76,
    'w', 4, 0x25, 0x10, 0x10, 0xE6,
    'w', 4, 0x25, 0x10, 0x14, 0x21,
    'w', 4, 0x25, 0x10, 0x09, 0x02,
    'w', 4, 0x25, 0x10, 0x15, 0xAB,
    'w', 4, 0x25, 0x10, 0x13, 0xAB,
    'w', 4, 0x25, 0x10, 0x12, 0x40,
    'w', 4, 0x25, 0x10, 0x12, 0x60,
    'w', 4, 0x25, 0x10, 0x09, 0x1C,
    'w', 4, 0x25, 0x10, 0x14, 0x20,
    'w', 4, 0x25, 0x10, 0x09, 0x06,
    'w', 4, 0x25, 0x10, 0x15, 0x08,
    'w', 4, 0x25, 0x10, 0x09, 0x03,
    'w', 4, 0x25, 0x10, 0x0B, 0x13,
    'w', 4, 0x25, 0x10, 0x88, 0x14,
    'w', 4, 0x25, 0x10, 0x20, 0x14,
    'w', 4, 0x25, 0x10, 0x60, 0x09,
    'w', 4, 0x25, 0x10, 0x02, 0x15,
    'w', 4, 0x25, 0x10, 0x0D, 0x13,
    'w', 4, 0x25, 0x10, 0x0D, 0x10,
    'w', 4, 0x25, 0x10, 0x66, 0x09,
    'w', 4, 0x25, 0x10, 0x1C, 0x15,
    'w', 4, 0x25, 0x10, 0x08, 0x13,
    'w', 4, 0x25, 0x10, 0x08, 0x14,
    'w', 4, 0x25, 0x10, 0x00, 0x15,
    'w', 4, 0x25, 0x10, 0x88, 0x13,
    'w', 4, 0x25, 0x10, 0x88, 0x09,
    'w', 4, 0x25, 0x10, 0x36, 0x0C,
    'w', 4, 0x25, 0x10, 0x14, 0x00,
    'w', 4, 0x25, 0x10, 0x11, 0xBB,
    'w', 4, 0x25, 0x10, 0x10, 0x66,
    'w', 4, 0x25, 0x10, 0x09, 0x1F,
    'w', 4, 0x25, 0x10, 0x10, 0xE6,
    'w', 4, 0x25, 0x10, 0x11, 0xFB,
    'w', 4, 0x25, 0x10, 0x12, 0x62,
    'w', 4, 0x25, 0x10, 0x12, 0x60,
    'w', 4, 0x25, 0x10, 0x11, 0xFF,
    'w', 4, 0x25, 0x10, 0x11, 0xFB,
    'w', 4, 0x25, 0x10, 0x14, 0x01,
    'w', 4, 0x25, 0x10, 0x09, 0x02,
    'w', 4, 0x25, 0x10, 0x10, 0x66,
    'w', 4, 0x25, 0x10, 0x09, 0x1A,
    'w', 4, 0x25, 0x10, 0x11, 0xBB,
    'w', 4, 0x25, 0x10, 0x12, 0x63,
    'w', 4, 0x25, 0x10, 0x12, 0x60,
    'w', 4, 0x25, 0x10, 0x14, 0x00,
    'w', 4, 0x25, 0x10, 0x15, 0x5A,
    'w', 4, 0x25, 0x10, 0x11, 0xB8,
    'w', 4, 0x25, 0x10, 0x12, 0xA0,
    'w', 4, 0x25, 0x10, 0x12, 0x00,
    'w', 4, 0x25, 0x10, 0x10, 0x26,
    'w', 4, 0x25, 0x10, 0x10, 0x00,
    'w', 4, 0x25, 0x10, 0x13, 0x42,
    'w', 4, 0x25, 0x10, 0x11, 0x80,
    'w', 4, 0x25, 0x10, 0x7A, 0x06,
    'w', 4, 0x25, 0x10, 0x05, 0x11,
    'w', 4, 0x25, 0x10, 0x00, 0x07,
    'w', 4, 0x25, 0x10, 0x41, 0x37,
    'w', 4, 0x25, 0x10, 0x50, 0x2C,
    'w', 4, 0x25, 0x10, 0x2C, 0xFE,
    'w', 4, 0x25, 0x10, 0xF7, 0xFE,
    'w', 4, 0x25, 0x10, 0x07, 0x2C,
    // Sensor Setup
    'w', 10, 0x32, 0xD0, 0x3A, 0x02, 0x35, 0x08, 0x37, 0x02, 0x3C, 0x04,
    'w', 4, 0x32, 0xDC, 0x37, 0x0A,
    // PLL 27MHz In -88MHz out
                // VT_PIX_CLK_DIV, VT_SYS_CLK_DIV, PRE_PLL_CLK_DIV, PLL_MULTIPLIER
    'w', 10, 0x30, 0x2A, 0x00, 0x06, 0x00, 0x01, 0x00, 0x09, 0x00, 0xB0,
    'w', 6, 0x30, 0x36, 0x00, 0x08, 0x00, 0x01, // OP_WORD_CLK_DIV, OP_SYS_CLK_DIV
    'w', 4, 0x30, 0xB0, 0x0B, 0x02, // DIGITAL_TEST
    // Readout Mode Configuration
    'w', 4, 0x30, 0xA2, 0x00, 0x01, // X_ODD_INC_
    'w', 4, 0x30, 0xA6, 0x00, 0x01, // Y_ODD_INC_
    'w', 8, 0x30, 0x40, 0x00, 0x00,  0x00, 0x00, 0x04, 0x00, // READ_MODE, EXTRA_DELAY, DARK_CONTROL
    'w', 4, 0x30, 0x64, 0x19, 0x02, // SMIA_TEST, enable top embedded data
    'w', 4, 0x31, 0x80, 0x00, 0x80,
    'w', 4, 0x33, 0xE4, 0x00, 0x00, // 0X00, 0x80
    // Timing
    'w', 4, 0x30, 0x32, 0x00, 0x00, // SCALING_MODE
    'w', 8, 0x34, 0x00, 0x00, 0x10, 0x0F, 0x10, 0x09, 0x70,
    // 3 or 4 exp Timing
    'w', 4, 0x30, 0x82, 0x00, 0x80 + (((NVMEDIA_ISC_EXPOSURE_MODE_MAX - 1) << 2) & 0xF), // OPERATION_MODE_CTRL
    'w', 4, 0x30, 0xBA, 0x10, 0x22, // DIGITAL_CTRL
    // Exposure
    'w', 4, 0x32, 0x38, 0x87, 0x77, // EXPOSURE_RATIO, use reg
    'w', 4, 0x10, 0x08, 0x03, 0x52, // FINE_INTEGRATIONx_TIME_MIN
    'w', 8, 0x10, 0x0C, 0x05, 0x66, 0x07, 0x7A, 0x01, 0x3E, // FINE_INTEGRATIONx_TIME_MIN2/3
    'w', 4, 0x30, 0x12, 0x03, 0x8C, // COARSE_INTEGRATION_TIME_
    'w', 4, 0x32, 0x12, 0x00, 0x3E, // COARSE_INTEGRATION_TIME_2
    'w', 4, 0x32, 0x16, 0x00, 0x05, // COARSE_INTEGRATION_TIME_3
    'w', 6, 0x32, 0xEA, 0x3C, 0x0E, 0x72, 0xA0,
    // GPIO control  // ENABLE GPIO3 to trigger fsync
    'w', 6, 0x34, 0x0A, 0x00, 0x77, 0x00, 0x80,
    'w', 4, 0x30, 0xCE, 0x01, 0x20, // enable synchronization
    // Parallel HDR 12 bit Output
    'w', 4, 0x31, 0xD0, 0x00, 0x01, // COMPANDING
    'w', 6, 0x31, 0xAC, 0x14, 0x0C, 0x00, 0x01, // DATA_FORMAT_BITS, SERIAL_FORMAT
    'e'
};

static const NvU8 ar0231_raw12_default_v4[] = { //v4
    //Disable Streaming
    'w', 4, 0x30, 0x1A, 0x10, 0x58, // RESET_REGISTER
    'd',    0x27, 0x01,             // Delay 1ms
    // Sensor gain
    'w', 4, 0x30, 0xFE, 0x00, 0x20, // NOISE_PEDESTAL
    'w', 8, 0x33, 0x62, 0x00, 0x00, 0x00, 0x60, 0x77, 0x77, // DC_GAIN, DCG_TRIM, ANALOG_GAIN
    'w', 10, 0x30, 0x56, 0x00, 0x80, 0x00, 0xE9, 0x00, 0xA7, 0x00, 0x80, //GBRG 1.0,1.82,1.3,1.0
    // Design recomannended settings
    'w', 6, 0x31, 0x8E, 0x02, 0x00, 0x50, 0x00, // DLO_CONTROL0/1
    'w', 10, 0x32, 0x90, 0x0F, 0xC0, 0x0F, 0xC0, 0x0F, 0xC0, 0x0F, 0xC0, // T3 barrier
    'w', 4, 0x32, 0xE2, 0x38, 0x03, // SHUT_DCG_BOOST
    'w', 6, 0x33, 0x70, 0x02, 0x31, 0x70, 0x0F, // DBLC_CONTROL, DBLC_FS0_CONTROL
    'w', 4, 0x33, 0x86, 0x00, 0x00, // DBLC_PEDESTAL
    'w', 4, 0x3C, 0x04, 0x0E, 0x80, // RNC_BIAS
    'w', 6, 0x3F, 0x90, 0x06, 0xE1, 0x06, 0xE1, // TEMPVSENS0/1_TMG_CTRL
    'w', 4, 0x35, 0x02, 0x08, 0x08, // DAC_LD_2_3, tbd:verify 3500
    'w', 12, 0x35, 0x06, 0x44, 0x44, 0x44, 0x44, 0x44, 0x65, 0x05, 0x5F,
                         0xFF, 0x10, // DAC_LD_6_7, 8_9, 10_11
    'w', 8, 0x32, 0x30, 0x03, 0x17, 0x05, 0x52, 0x07, 0x8D, //FINE_CORRECTION T1, T2, T3
    'w', 4, 0x35, 0x10, 0x00, 0x00,
    'w', 4, 0x35, 0x14, 0x01, 0x06,
    'w', 4, 0x35, 0x18, 0x1F, 0xFE, // DAC_LD_24_25
    'w', 8, 0x35, 0x20, 0xC6, 0x88, 0x88, 0xC0, 0xC0, 0xC6, //tdb:verify 3526
    'w', 12, 0x35, 0x28, 0x99, 0x99, 0x08, 0x9F, 0xC6, 0xC6, 0x00, 0x11,
                         0x44, 0x00,
    'w', 10, 0x35, 0x36, 0xFF, 0x06, 0xFF, 0xFF, 0x90, 0x00, 0x3F, 0x00,
    'w', 12, 0x35, 0x40, 0xC6, 0x37, 0x46, 0x4B, 0x4B, 0x5A, 0x5A, 0x5A,
                         0x64, 0x00,
    'w', 4, 0x35, 0x50, 0x0E, 0x28,
    'w', 4, 0x35, 0x56, 0x10, 0x1F,
    'w', 4, 0x35, 0x66, 0x33, 0x28,
    //Sequencer
    'w', 4, 0x25, 0x12, 0x80, 0x00,
    'w', 4, 0x25, 0x10, 0x09, 0x05,
    'w', 4, 0x25, 0x10, 0x33, 0x50,
    'w', 4, 0x25, 0x10, 0x20, 0x04,
    'w', 4, 0x25, 0x10, 0x14, 0x60,
    'w', 4, 0x25, 0x10, 0x15, 0x78,
    'w', 4, 0x25, 0x10, 0x13, 0x60,
    'w', 4, 0x25, 0x10, 0x7b, 0x24,
    'w', 4, 0x25, 0x10, 0xff, 0x24,
    'w', 4, 0x25, 0x10, 0xff, 0x24,
    'w', 4, 0x25, 0x10, 0xea, 0x24,
    'w', 4, 0x25, 0x10, 0x10, 0x22,
    'w', 4, 0x25, 0x10, 0x24, 0x10,
    'w', 4, 0x25, 0x10, 0x15, 0x5a,
    'w', 4, 0x25, 0x10, 0x13, 0x42,
    'w', 4, 0x25, 0x10, 0x14, 0x00,
    'w', 4, 0x25, 0x10, 0x24, 0xff,
    'w', 4, 0x25, 0x10, 0x24, 0xff,
    'w', 4, 0x25, 0x10, 0x24, 0xea,
    'w', 4, 0x25, 0x10, 0x23, 0x24,
    'w', 4, 0x25, 0x10, 0x64, 0x7a,
    'w', 4, 0x25, 0x10, 0x24, 0x04,
    'w', 4, 0x25, 0x10, 0x05, 0x2c,
    'w', 4, 0x25, 0x10, 0x40, 0x0a,
    'w', 4, 0x25, 0x10, 0xff, 0x0a,
    'w', 4, 0x25, 0x10, 0xff, 0x0a,
    'w', 4, 0x25, 0x10, 0x04, 0x08,
    'w', 4, 0x25, 0x10, 0x38, 0x51,
    'w', 4, 0x25, 0x10, 0x14, 0x40,
    'w', 4, 0x25, 0x10, 0x00, 0x04,
    'w', 4, 0x25, 0x10, 0x08, 0x01,
    'w', 4, 0x25, 0x10, 0x04, 0x08,
    'w', 4, 0x25, 0x10, 0x11, 0x80,
    'w', 4, 0x25, 0x10, 0x15, 0xdc,
    'w', 4, 0x25, 0x10, 0x13, 0x4c,
    'w', 4, 0x25, 0x10, 0x10, 0x02,
    'w', 4, 0x25, 0x10, 0x10, 0x16,
    'w', 4, 0x25, 0x10, 0x11, 0x81,
    'w', 4, 0x25, 0x10, 0x11, 0x89,
    'w', 4, 0x25, 0x10, 0x10, 0x56,
    'w', 4, 0x25, 0x10, 0x12, 0x10,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x0d, 0x08,
    'w', 4, 0x25, 0x10, 0x09, 0x13,
    'w', 4, 0x25, 0x10, 0x13, 0xc8,
    'w', 4, 0x25, 0x10, 0x09, 0x2b,
    'w', 4, 0x25, 0x10, 0x15, 0x88,
    'w', 4, 0x25, 0x10, 0x13, 0x88,
    'w', 4, 0x25, 0x10, 0x09, 0x0b,
    'w', 4, 0x25, 0x10, 0x11, 0xd9,
    'w', 4, 0x25, 0x10, 0x09, 0x1d,
    'w', 4, 0x25, 0x10, 0x14, 0x41,
    'w', 4, 0x25, 0x10, 0x09, 0x03,
    'w', 4, 0x25, 0x10, 0x12, 0x14,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x10, 0xd6,
    'w', 4, 0x25, 0x10, 0x12, 0x10,
    'w', 4, 0x25, 0x10, 0x12, 0x12,
    'w', 4, 0x25, 0x10, 0x12, 0x10,
    'w', 4, 0x25, 0x10, 0x11, 0xdd,
    'w', 4, 0x25, 0x10, 0x11, 0xd9,
    'w', 4, 0x25, 0x10, 0x10, 0x56,
    'w', 4, 0x25, 0x10, 0x09, 0x0b,
    'w', 4, 0x25, 0x10, 0x11, 0xdb,
    'w', 4, 0x25, 0x10, 0x09, 0x15,
    'w', 4, 0x25, 0x10, 0x11, 0x9b,
    'w', 4, 0x25, 0x10, 0x09, 0x0f,
    'w', 4, 0x25, 0x10, 0x11, 0xbb,
    'w', 4, 0x25, 0x10, 0x12, 0x1a,
    'w', 4, 0x25, 0x10, 0x12, 0x10,
    'w', 4, 0x25, 0x10, 0x14, 0x60,
    'w', 4, 0x25, 0x10, 0x12, 0x50,
    'w', 4, 0x25, 0x10, 0x10, 0x76,
    'w', 4, 0x25, 0x10, 0x10, 0xe6,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x15, 0xab,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x13, 0xa8,
    'w', 4, 0x25, 0x10, 0x12, 0x40,
    'w', 4, 0x25, 0x10, 0x12, 0x60,
    'w', 4, 0x25, 0x10, 0x09, 0x23,
    'w', 4, 0x25, 0x10, 0x15, 0x8d,
    'w', 4, 0x25, 0x10, 0x13, 0x8d,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x0b, 0x09,
    'w', 4, 0x25, 0x10, 0x01, 0x08,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x14, 0x40,
    'w', 4, 0x25, 0x10, 0x09, 0x1d,
    'w', 4, 0x25, 0x10, 0x15, 0x88,
    'w', 4, 0x25, 0x10, 0x13, 0x88,
    'w', 4, 0x25, 0x10, 0x09, 0x2d,
    'w', 4, 0x25, 0x10, 0x10, 0x66,
    'w', 4, 0x25, 0x10, 0x09, 0x05,
    'w', 4, 0x25, 0x10, 0x0c, 0x08,
    'w', 4, 0x25, 0x10, 0x09, 0x0b,
    'w', 4, 0x25, 0x10, 0x14, 0x41,
    'w', 4, 0x25, 0x10, 0x09, 0x0d,
    'w', 4, 0x25, 0x10, 0x10, 0xe6,
    'w', 4, 0x25, 0x10, 0x09, 0x01,
    'w', 4, 0x25, 0x10, 0x12, 0x62,
    'w', 4, 0x25, 0x10, 0x12, 0x60,
    'w', 4, 0x25, 0x10, 0x11, 0xbf,
    'w', 4, 0x25, 0x10, 0x11, 0xbb,
    'w', 4, 0x25, 0x10, 0x10, 0x66,
    'w', 4, 0x25, 0x10, 0x11, 0xfb,
    'w', 4, 0x25, 0x10, 0x09, 0x35,
    'w', 4, 0x25, 0x10, 0x11, 0xbb,
    'w', 4, 0x25, 0x10, 0x12, 0x63,
    'w', 4, 0x25, 0x10, 0x12, 0x60,
    'w', 4, 0x25, 0x10, 0x14, 0x00,
    'w', 4, 0x25, 0x10, 0x15, 0x10,
    'w', 4, 0x25, 0x10, 0x11, 0xb8,
    'w', 4, 0x25, 0x10, 0x12, 0xa0,
    'w', 4, 0x25, 0x10, 0x12, 0x00,
    'w', 4, 0x25, 0x10, 0x10, 0x26,
    'w', 4, 0x25, 0x10, 0x10, 0x00,
    'w', 4, 0x25, 0x10, 0x13, 0x42,
    'w', 4, 0x25, 0x10, 0x11, 0x00,
    'w', 4, 0x25, 0x10, 0x7a, 0x06,
    'w', 4, 0x25, 0x10, 0x09, 0x26,
    'w', 4, 0x25, 0x10, 0x05, 0x07,
    'w', 4, 0x25, 0x10, 0x08, 0x41,
    'w', 4, 0x25, 0x10, 0x37, 0x50,
    'w', 4, 0x25, 0x10, 0x2c, 0x2c,
    'w', 4, 0x25, 0x10, 0xfe, 0x02,
    'w', 4, 0x25, 0x10, 0xfe, 0x14,
    // Sensor Setup
    'w', 10, 0x32, 0xD0, 0x3A, 0x02, 0x35, 0x08, 0x37, 0x02, 0x3C, 0x04,
    'w', 4, 0x32, 0xDC, 0x37, 0x0A,
    // PLL 27MHz In -88MHz out
                // VT_PIX_CLK_DIV, VT_SYS_CLK_DIV, PRE_PLL_CLK_DIV, PLL_MULTIPLIER
    'w', 10, 0x30, 0x2A, 0x00, 0x06, 0x00, 0x01, 0x00, 0x09, 0x00, 0xB0,
    'w', 6, 0x30, 0x36, 0x00, 0x08, 0x00, 0x01, // OP_WORD_CLK_DIV, OP_SYS_CLK_DIV
    'w', 4, 0x30, 0xB0, 0x0B, 0x02, // DIGITAL_TEST
    // Readout Mode Configuration
    'w', 8, 0x30, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, // EXTRA_DELAY, DARK_CONTROL
    'w', 4, 0x30, 0x64, 0x19, 0x02, // SMIA_TEST, enable top embedded data
    'w', 4, 0x31, 0x80, 0x00, 0x80,
    'w', 4, 0x33, 0xE4, 0x00, 0x00, // 0X00, 0x80
    // Timing
    'w', 8, 0x34, 0x00, 0x00, 0x10, 0x0F, 0x10, 0x09, 0x70,
    // 3 or 4 exp Timing
    'w', 4, 0x30, 0x82, 0x00, 0x00 + (((NVMEDIA_ISC_EXPOSURE_MODE_MAX - 1) << 2) & 0xF), // OPERATION_MODE_CTRL
    'w', 4, 0x30, 0xBA, 0x11, 0xE2, // DIGITAL_CTRL
    // Exposure ratio and time
    'w', 4, 0x32, 0x38, 0x87, 0x77, // EXPOSURE_RATIO, use reg
    'w', 4, 0x30, 0x12, 0x03, 0x00, // COARSE_INTEGRATION_TIME_
    'w', 4, 0x32, 0x12, 0x00, 0x30, // COARSE_INTEGRATION_TIME_2
    'w', 4, 0x32, 0x16, 0x00, 0x03, // COARSE_INTEGRATION_TIME_3
    'w', 6, 0x32, 0xEA, 0x3C, 0x0E, 0x72, 0xA1,
    // GPIO control  // ENABLE GPIO3 to trigger fsync
    'w', 6, 0x34, 0x0A, 0x00, 0x77, 0x00, 0x80,
    'w', 4, 0x30, 0xCE, 0x01, 0x20, // enable synchronization
    // Parallel HDR 12 bit Output
    'w', 4, 0x31, 0xD0, 0x00, 0x01, // COMPANDING
    'w', 6, 0x31, 0xAC, 0x14, 0x0C, 0x00, 0x01, // DATA_FORMAT_BITS, SERIAL_FORMAT
    'e'
};

/* Config set 0 */
static const NvU8 ar0231_raw12_comp_1920x1008_36fps[] = {
    'w', 4, 0x33, 0xE0, 0x00, 0x00, // TEST_ASIL_ROWS
             // Y_ADDR_START_, X_ADDR_START_, Y_ADDR_END_, X_ADDR_END_;
    'w', 14, 0x30, 0x02, 0x00, 0x00, 0x00, 0x04, 0x03, 0xEF, 0x07, 0x83,
                        (AR0231_VTS_36FPS >> 8) & 0xFF,
                         AR0231_VTS_36FPS & 0xFF,
                        (AR0231_HTS >> 8) & 0xFF,
                         AR0231_HTS & 0xFF,
    'e'
};

static const NvU8 ar0231_raw12_comp_1920x1208_30fps[] = {
    'w', 4, 0x33, 0xE0, 0x00, 0x80, // TEST_ASIL_ROWS
             // Y_ADDR_START_, X_ADDR_START_, Y_ADDR_END_, X_ADDR_END_;
    'w', 14, 0x30, 0x02, 0x00, 0x00, 0x00, 0x04, 0x04, 0xB7, 0x07, 0x83,
                        (AR0231_VTS_30FPS >> 8) & 0xFF,
                         AR0231_VTS_30FPS & 0xFF,
                        (AR0231_HTS >> 8) & 0xFF,
                         AR0231_HTS & 0xFF,
    'e'
};

/* Config set 1 */
static const unsigned char ar0231_raw12_comp_1920x1008_36fps_extsync[] = {
    'w', 4, 0x33, 0xE0, 0x00, 0x00, // TEST_ASIL_ROWS
             // Y_ADDR_START_, X_ADDR_START_, Y_ADDR_END_, X_ADDR_END_;
    'w', 14, 0x30, 0x02, 0x00, 0x00, 0x00, 0x04, 0x03, 0xEF, 0x07, 0x83,
                        (AR0231_VTS_36FPS_EXTSYNC >> 8) & 0xFF,
                         AR0231_VTS_36FPS_EXTSYNC & 0xFF,
                        (AR0231_HTS >> 8) & 0xFF,
                         AR0231_HTS & 0xFF,
    'w', 4, 0x30, 0xDC, 0x9C, 0x41, // TODO: find the proper triggering delay
    'e'
};

static const unsigned char ar0231_raw12_comp_1920x1208_30fps_extsync[] = {
    'w', 4, 0x33, 0xE0, 0x00, 0x80, // TEST_ASIL_ROWS
             // Y_ADDR_START_, X_ADDR_START_, Y_ADDR_END_, X_ADDR_END_;
    'w', 14, 0x30, 0x02, 0x00, 0x00, 0x00, 0x04, 0x04, 0xB7, 0x07, 0x83,
                        (AR0231_VTS_30FPS_EXTSYNC >> 8) & 0xFF,
                         AR0231_VTS_30FPS_EXTSYNC & 0xFF,
                        (AR0231_HTS >> 8) & 0xFF,
                         AR0231_HTS & 0xFF,
    'w', 4, 0x30, 0xDC, 0x9C, 0x41, // TODO: find the proper triggering delay
    'e'
};

static const unsigned char ar0231_enable_streaming[] = {
    4, 0x30, 0x1A, 0x19, 0xDC, // RESET_REGISTER
};

static const
TimingSettingAR0231 ar0231_timing[ISC_CONFIG_AR0231_NUM_CONFIG_SET][ISC_CONFIG_AR0231_NUM_RESOLUTION] = {
    { /* Config set 0 */
    {
        /* Index 0: 30fps, 1920x1208 */
        AR0231_HTS,
        AR0231_VTS_30FPS,
        ar0231_raw12_comp_1920x1208_30fps
    },
    {   /* Index 1: 36fps, 1920X1008 */
        AR0231_HTS,
        AR0231_VTS_36FPS,
        ar0231_raw12_comp_1920x1008_36fps
    },
    },
    { /* Config set 1 */
    {
        /* Index 0: 30fps, 1920x1208 */
        AR0231_HTS,
        AR0231_VTS_30FPS_EXTSYNC,
        ar0231_raw12_comp_1920x1208_30fps_extsync
    },
    {   /* Index 1: 36fps, 1920X1008 */
        AR0231_HTS,
        AR0231_VTS_36FPS_EXTSYNC,
        ar0231_raw12_comp_1920x1008_36fps_extsync
    },
    }
};

#endif /* _AR0231_SETTING_H_ */
