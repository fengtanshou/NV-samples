
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "ov2718_xc7027_2.h"

//#define TEST_COLORBAR_MODE

#define OV2718MIPI_SENSOR_ID 0x2770

#define REGISTER_ADDRESS_BYTES  2
#define REG_WRITE_BUFFER        32


static NvMediaISCSupportFunctions  *g_I2c_func = NULL;
static NvMediaISCTransactionHandle *g_transaction = NULL;

static NvMediaISCSupportFunctions  *g_I2c_func_ov = NULL;
static NvMediaISCTransactionHandle *g_transaction_ov = NULL;


static int OV2718MIPI_write_cmos_sensor(unsigned short addr, unsigned char para);
static unsigned char OV2718MIPIYUV_read_cmos_sensor(unsigned short addr);
static int XC7022_write_cmos_sensor(unsigned short addr, unsigned char para);
static unsigned char XC7022_read_cmos_sensor(unsigned short addr);



static void mDELAY(ms)
{
	usleep(ms * 1000);
}

static int OV2718MIPI_write_cmos_sensor(unsigned short addr, unsigned char para)
{
    unsigned char data[REGISTER_ADDRESS_BYTES + REG_WRITE_BUFFER];
    NvMediaStatus status;

    if((g_I2c_func_ov == NULL) || (g_transaction_ov  == NULL)) {
        return NVMEDIA_STATUS_BAD_PARAMETER;
    }

    data[0] = addr >> 8;
    data[1] = addr & (unsigned int)0xFF;
    //(void)memcpy(&data[2], &para, 1);
    data[2] = para;

    status = g_I2c_func_ov->Write(
        g_transaction_ov,
        1 + (unsigned int)REGISTER_ADDRESS_BYTES,    // dataLength
        data);                             // data

    if(status != NVMEDIA_STATUS_OK) {
        LOG_ERR("%s: sensor write failed: 0x%x, 0x%x \n", __func__, addr, para);
    }
	
    return status;
}

static unsigned char OV2718MIPIYUV_read_cmos_sensor(unsigned short addr)
{
	unsigned char registerData[REGISTER_ADDRESS_BYTES];
	unsigned char dataBuff;
	NvMediaStatus status;
	
	if((g_I2c_func_ov == NULL) || (g_transaction_ov == NULL)) {
		return NVMEDIA_STATUS_BAD_PARAMETER;
	}
	
	registerData[0] = addr >> 8;
	registerData[1] = (addr & (unsigned int)0xFF);
	status = g_I2c_func_ov->Read(
		g_transaction_ov,
		REGISTER_ADDRESS_BYTES, // regLength
		registerData,	   // regData
		1, 	   // dataLength
		&dataBuff);		   // data
	
	if(status != NVMEDIA_STATUS_OK) {
		LOG_ERR("%s: sensor read failed: 0x%x\n", __func__, addr);
	}
	
	return dataBuff;
}

static int XC7022_write_cmos_sensor(unsigned short addr, unsigned char para)
{
    unsigned char data[REGISTER_ADDRESS_BYTES + REG_WRITE_BUFFER];
    NvMediaStatus status;

    if((g_I2c_func == NULL) || (g_transaction  == NULL)) {
        return NVMEDIA_STATUS_BAD_PARAMETER;
    }

    data[0] = addr >> 8;
    data[1] = addr & (unsigned int)0xFF;
    //(void)memcpy(&data[2], &para, 1);
    data[2] = para;

    status = g_I2c_func->Write(
        g_transaction,
        1 + (unsigned int)REGISTER_ADDRESS_BYTES,    // dataLength
        data);                             // data

    if(status != NVMEDIA_STATUS_OK) {
        LOG_ERR("%s: sensor write failed: 0x%x, 0x%x \n", __func__, addr, para);
    }
	
    return status;
}

static unsigned char XC7022_read_cmos_sensor(unsigned short addr)
{
	unsigned char registerData[REGISTER_ADDRESS_BYTES];
	unsigned char dataBuff;
	NvMediaStatus status;
	
	if((g_I2c_func == NULL) || (g_transaction == NULL)) {
		return NVMEDIA_STATUS_BAD_PARAMETER;
	}
	
	registerData[0] = addr >> 8;
	registerData[1] = (addr & (unsigned int)0xFF);
	status = g_I2c_func->Read(
		g_transaction,
		REGISTER_ADDRESS_BYTES, // regLength
		registerData,	   // regData
		1, 	   // dataLength
		&dataBuff);		   // data
	
	if(status != NVMEDIA_STATUS_OK) {
		LOG_ERR("%s: sensor read failed: 0x%x\n", __func__, addr);
	}
	
	return dataBuff;
}


void SetI2cFun(NvMediaISCSupportFunctions *func, NvMediaISCTransactionHandle *transaction)
{
	g_I2c_func = func;
	g_transaction = transaction;
}

void SetI2cFunOv(NvMediaISCSupportFunctions *func, NvMediaISCTransactionHandle *transaction)
{
	g_I2c_func_ov = func;
	g_transaction_ov = transaction;
}

////////////////////////////////////////////////////////////////////////////////////////////


unsigned int XC7027_default_regs[][2] = {
// XC7027 setting	
0xfffd,0x80,
0xfffe,0x50,
0x001c,0xff,	//clock and reset
0x001d,0xff,
0x001e,0xff,
0x001f,0xff,    

0x0018,0x00,
0x0019,0x00,
0x001a,0x00,
0x001b,0x00,

0x0030,0x24,
0x0031,0xf4,
0x0032,0x73,
0x0033,0x70,

0x0020,0x01,
0x0021,0x0e,
0x0022,0x01,
0x0023,0xc7,
0x0024,0x06,
0x0025,0x05,
0x0026,0x01,
0x0027,0x06,
0x0028,0x06,
0x0029,0x00,
0x002a,0x01,
0x002b,0x06,
0x002c,0x05,
0x002d,0x00,
0x002e,0x01,

0x0050,0x03,
0x0054,0x03,
0x0058,0x03,  

0x00bc,0x19,
#ifdef TEST_COLORBAR_MODE  
	0x0090,0x3a,    
#else
	0x0090,0x38,   
#endif




0xfffe,0x26,

0x8000,0x1d,
0x8001,0x80,
0x8002,0x07,
0x8003,0x38,
0x8004,0x04,

0x8010,0x04,
0x8012,0x80,
0x8013,0x07,
0x8014,0x38,
0x8015,0x04,
0x8016,0x00,
0x8017,0x00,
0x8018,0x00,
0x8019,0x00,

0xfffe,0x30,
0x1900,0x00,
0x1901,0x00,
0x1902,0x00,
0x1903,0x00,
0x1904,0x07,
0x1905,0x80,
0x1906,0x04,
0x1907,0x38,
0x1908,0x00,

0xfffe,0x2c,

0x0000,0x00,
0x0001,0x07,
0x0002,0x80,
0x0004,0x04,
0x0005,0x38,
0x0008,0x10,
0x0044,0x08,
0x0045,0x04,
0x0048,0x0E,
0x0049,0xF0,

0xfffe,0x26,

0x2019,0x07,
0x201a,0x80,
0x201b,0x04,
0x201c,0x38,
0x201d,0x00,
0x201e,0x00,
0x201f,0x00,
0x2020,0x00,

0x2015,0x80,
0x2017,0x1E,
0x2018,0x00,
0x2023,0x03,

0x0000,0x00,
0x0009,0xc4,

0xfffe,0x30,

0x0000,0x01,
0x0001,0x00,
0x0002,0x10,
0x0003,0x20,
0x0004,0x10,
0x0050,0x20,
0x0019,0x08,
0x005e,0x7F,
0x005f,0x07,
0x0060,0x37,
0x0061,0x04,
0x0064,0x80,
0x0065,0x07,
0x0066,0x38,
0x0067,0x04,

0x0006,0x07,
0x0007,0x80,
0x0008,0x04,
0x0009,0x38,
0x000a,0x07,
0x000b,0x80,
0x000c,0x04,
0x000d,0x38,

0xfffe,0x2c,		//stitch         
0x0000,0x01,                     
0x0001,0x07,                     
0x0002,0x80,                     
0x0004,0x04,                     
0x0005,0x38,                     
                                 
0x0008,0x11,                     
0x0044,0x00,	//fifo             
0x0045,0x04,                     
                                 
0x0049,0x80,                     
0x0048,0x07,    

};


unsigned int OV2718_default_regs[][2] = {
// OV2718_setting
0x3000,0x05,
0x3001,0x64,
0x3002,0x07,
0x3003,0x01,
0x3004,0x06,
0x3005,0x56,
0x3006,0x00,
0x3007,0x07,
0x3008,0x01,
0x3009,0x00,
0x300c,0x6c,
0x300d,0xe1,
0x300e,0x80,
0x300f,0x00,
0x3012,0x00,
0x3013,0x00,
0x3014,0x84,
0x3015,0x00,
0x3017,0x00,
0x3018,0x00,
0x3019,0x00,
0x301a,0x00,
0x301b,0x01,
0x301e,0x10,
0x301f,0x5f,
0x3030,0x02,
0x3031,0x63,
0x3032,0xf0,
0x3033,0x30,
0x3034,0x34,
0x3035,0x51,
0x3036,0x02,
0x3037,0x9f,
0x3038,0x04,
0x3039,0xb7,
0x303a,0x04,
0x303b,0x07,
0x303c,0xf0,
0x303d,0x00,
0x303e,0x0b,
0x303f,0xe3,
0x3040,0xf3,
0x3041,0x29,
0x3042,0xf6,
0x3043,0x65,
0x3044,0x06,
0x3045,0x0f,
0x3046,0x55,
0x3047,0xf7,
0x3048,0x31,
0x3049,0x0f,
0x304a,0x10,
0x304b,0xc0,
0x304c,0x33,
0x304d,0x24,
0x304e,0x0b,
0x304f,0x3d,
0x3050,0x10,
0x3060,0x00,
0x3061,0x64,
0x3062,0x01,
0x3063,0x00,
0x3064,0x0b,
0x3065,0xf8,
0x3066,0x80,
0x3080,0x00,
0x3081,0x00,
0x3082,0x01,
0x3083,0xe3,
0x3084,0x05,
0x3085,0x00,
0x3086,0x10,
0x3087,0x10,
0x3089,0x00,
0x308a,0x01,
0x3093,0x00,
0x30a0,0x00,
0x30a1,0x00,
0x30a2,0x00,
0x30a3,0x00,
0x30a4,0x07,
0x30a5,0x8e, 
0x30a6,0x04,
0x30a7,0x47,
0x30a8,0x00,
0x30a9,0x00,
0x30aa,0x00,
0x30ab,0x00,
0x30ac,0x07,
0x30ad,0x90,
0x30ae,0x04,
0x30af,0x48,
0x30b0,0x04,
0x30b1,0x7e,
0x30b2,0x04,
0x30b3,0x65,
0x30b4,0x00,
0x30b5,0x00,
0x30b6,0x00,
0x30b7,0x10,
0x30b8,0x00,
0x30b9,0x02,
0x30ba,0x10,
0x30bb,0x00,
0x30bc,0x00,
0x30bd,0x03,
0x30be,0x5c,
0x30bf,0x00,
0x30c0,0x04,
0x30c1,0x00,
0x30c2,0x20,
0x30c3,0x00,
0x30c4,0x4a,
0x30c5,0x00,
0x30c7,0x00,
0x30c8,0x00,
0x30d1,0x00,
0x30d2,0x00,
0x30d3,0x80,
0x30d4,0x00,
0x30d9,0x09,
0x30da,0x64,
0x30dd,0x00,
0x30de,0x16,
0x30df,0x00,
0x30e0,0x17,
0x30e1,0x00,
0x30e2,0x18,
0x30e3,0x10,
0x30e4,0x04,
0x30e5,0x00,
0x30e6,0x00,
0x30e7,0x00,
0x30e8,0x00,
0x30e9,0x00,
0x30ea,0x00,
0x30eb,0x00,
0x30ec,0x00,
0x30ed,0x00,
0x3101,0x00,
0x3102,0x00,
0x3103,0x00,
0x3104,0x00,
0x3105,0x6c,
0x3106,0x83,
0x3107,0x72,
0x3108,0x70,
0x3109,0x6c,
0x310a,0x83,
0x310b,0x69,
0x310c,0x43,
0x310d,0x42,
0x310e,0x00,
0x3120,0x00,
0x3121,0x00,
0x3122,0x00,
0x3123,0xf0,
0x3124,0x00,
0x3125,0xa0,
0x3126,0x3f,
0x3127,0x0f,
0x3128,0x00,
0x3129,0x3a,
0x312a,0x02,
0x312b,0x0f,
0x312c,0x00,
0x312d,0x0f,
0x312e,0x1d,
0x312f,0x00,
0x3130,0x00,
0x3131,0x00,
0x3132,0x00,
0x3140,0x02,
0x3141,0x03,
0x3142,0x00,
0x3143,0x00,
0x3144,0x00,
0x3145,0x00,
0x3146,0x00,
0x3147,0x00,
0x3148,0x00,
0x3149,0x00,
0x314a,0x00,
0x314b,0x00,
0x314c,0x00,
0x314d,0x00,
0x314e,0x1c,
0x314f,0x02,
0x3150,0x02,
0x3151,0x10,
0x3152,0x10,
0x3153,0x10,
0x3154,0x80,
0x3155,0x00,
0x3156,0x03,
0x3157,0x00,
0x3158,0x0f,
0x3159,0xff,
0x315a,0x01,
0x315b,0x00,
0x315c,0x01,
0x315d,0x00,
0x315e,0x01,
0x315f,0x00,
0x3160,0x00,
0x3161,0x00,
0x3162,0x00,
0x3163,0x40,
0x3164,0x00,
0x3165,0x40,
0x3190,0x28,
0x3191,0x99,
0x3193,0x08,
0x3194,0x13,
0x3195,0x33,
0x3196,0x00,
0x3197,0x10,
0x3198,0x00,
0x3199,0x7f,
0x319a,0x80,
0x319b,0xff,
0x319c,0x80,
0x319d,0xbf,
0x319e,0xc0,
0x319f,0xff,
0x31a0,0x24,
0x31a1,0x55,
0x31a2,0x00,
0x31a3,0x00,
0x31a6,0x00,
0x31a7,0x00,
0x31b0,0x00,
0x31b1,0x00,
0x31b2,0x02,
0x31b3,0x00,
0x31b4,0x00,
0x31b5,0x01,
0x31b6,0x00,
0x31b7,0x00,
0x31b8,0x00,
0x31b9,0x00,
0x31ba,0x00,
0x31d0,0x3c,
0x31d1,0x34,
0x31d2,0x3c,
0x31d3,0x00,
0x31d4,0x2d,
0x31d5,0x00,
0x31d6,0x01,
0x31d7,0x06,
0x31d8,0x00,
0x31d9,0x64,
0x31da,0x00,
0x31db,0x28,
0x31dc,0x04,
0x31dd,0x69,
0x31de,0x0a,
0x31df,0x3c,
0x31e0,0x04,
0x31e1,0x32,
0x31e2,0x00,
0x31e3,0x01,
0x31e4,0x0d,
0x31e5,0x80,
0x31e6,0x00,
0x31e7,0x2b,
0x31e8,0x6b,
0x31e9,0xab,
0x31ea,0xeb,
0x31eb,0x3f,
0x31ec,0x0f,
0x31ed,0x20,
0x31ee,0x04,
0x31ef,0x48,
0x31f0,0x07,
0x31f1,0x90,
0x31f2,0x04,
0x31f3,0x48,
0x31f4,0x07,
0x31f5,0x90,
0x31f6,0x04,
0x31f7,0x48,
0x31f8,0x07,
0x31f9,0x90,
0x31fa,0x04,
0x31fb,0x48,
0x31fd,0xcb,
0x31fe,0x0f,
0x31ff,0x03,
0x3200,0x00,
0x3201,0xff,
0x3202,0x00,
0x3203,0xff,
0x3204,0xff,
0x3205,0xff,
0x3206,0xff,
0x3207,0xff,
0x3208,0xff,
0x3209,0xff,
0x320a,0xff,
0x320b,0x1b,
0x320c,0x1f,
0x320d,0x1e,
0x320e,0x30,
0x320f,0x2d,
0x3210,0x2c,
0x3211,0x2b,
0x3212,0x2a,
0x3213,0x24,
0x3214,0x22,
0x3215,0x00,
0x3216,0x04,
0x3217,0x2b,
0x3218,0x6b,
0x3219,0xab,
0x321a,0xeb,
0x321b,0x00,
0x3230,0x3a,
0x3231,0x00,
0x3232,0x80,
0x3233,0x00,
0x3234,0x10,
0x3235,0xaa,
0x3236,0x55,
0x3237,0x99,
0x3238,0x66,
0x3239,0x08,
0x323a,0x88,
0x323b,0x00,
0x323c,0x00,
0x323d,0x03,
0x3250,0x33,
0x3251,0x00,
0x3252,0x20,
0x3253,0x00,
0x3254,0x00,
0x3255,0x01,
0x3256,0x00,
0x3257,0x00,
0x3258,0x00,
0x3270,0x01,
0x3271,0x60,
0x3272,0xc0,
0x3273,0x00,
0x3274,0x80,
0x3275,0x40,
0x3276,0x02,
0x3277,0x08,
0x3278,0x10,
0x3279,0x04,
0x327a,0x00,
0x327b,0x03,
0x327c,0x10,
0x327d,0x60,
0x327e,0xc0,
0x327f,0x06,
0x3288,0x10,
0x3289,0x00,
0x328a,0x08,
0x328b,0x00,
0x328c,0x04,
0x328d,0x00,
0x328e,0x02,
0x328f,0x00,
0x3290,0x20,
0x3291,0x00,
0x3292,0x10,
0x3293,0x00,
0x3294,0x08,
0x3295,0x00,
0x3296,0x04,
0x3297,0x00,
0x3298,0x40,
0x3299,0x00,
0x329a,0x20,
0x329b,0x00,
0x329c,0x10,
0x329d,0x00,
0x329e,0x08,
0x329f,0x00,
0x32a0,0x7f,
0x32a1,0xff,
0x32a2,0x40,
0x32a3,0x00,
0x32a4,0x20,
0x32a5,0x00,
0x32a6,0x10,
0x32a7,0x00,
0x32a8,0x00,
0x32a9,0x00,
0x32aa,0x00,
0x32ab,0x00,
0x32ac,0x00,
0x32ad,0x00,
0x32ae,0x00,
0x32af,0x00,
0x32b0,0x00,
0x32b1,0x00,
0x32b2,0x00,
0x32b3,0x00,
0x32b4,0x00,
0x32b5,0x00,
0x32b6,0x00,
0x32b7,0x00,
0x32b8,0x00,
0x32b9,0x00,
0x32ba,0x00,
0x32bb,0x00,
0x32bc,0x00,
0x32bd,0x00,
0x32be,0x00,
0x32bf,0x00,
0x32c0,0x00,
0x32c1,0x00,
0x32c2,0x00,
0x32c3,0x00,
0x32c4,0x00,
0x32c5,0x00,
0x32c6,0x00,
0x32c7,0x00,
0x32c8,0x87,
0x32c9,0x00,
0x3330,0x03,
0x3331,0xc8,
0x3332,0x02,
0x3333,0x24,
0x3334,0x00,
0x3335,0x00,
0x3336,0x00,
0x3337,0x00,
0x3338,0x03,
0x3339,0xc8,
0x333a,0x02,
0x333b,0x24,
0x333c,0x00,
0x333d,0x00,
0x333e,0x00,
0x333f,0x00,
0x3340,0x03,
0x3341,0xc8,
0x3342,0x02,
0x3343,0x24,
0x3344,0x00,
0x3345,0x00,
0x3346,0x00,
0x3347,0x00,
0x3348,0x40,
0x3349,0x00,
0x334a,0x00,
0x334b,0x00,
0x334c,0x00,
0x334d,0x00,
0x334e,0x80,
0x3360,0x01,
0x3361,0x00,
0x3362,0x01,
0x3363,0x00,
0x3364,0x01,
0x3365,0x00,
0x3366,0x01,
0x3367,0x00,
0x3368,0x01,
0x3369,0x00,
0x336a,0x01,
0x336b,0x00,
0x336c,0x01,
0x336d,0x00,
0x336e,0x01,
0x336f,0x00,
0x3370,0x01,
0x3371,0x00,
0x3372,0x01,
0x3373,0x00,
0x3374,0x01,
0x3375,0x00,
0x3376,0x01,
0x3377,0x00,
0x3378,0x00,
0x3379,0x00,
0x337a,0x00,
0x337b,0x00,
0x337c,0x00,
0x337d,0x00,
0x337e,0x00,
0x337f,0x00,
0x3380,0x00,
0x3381,0x00,
0x3382,0x00,
0x3383,0x00,
0x3384,0x00,
0x3385,0x00,
0x3386,0x00,
0x3387,0x00,
0x3388,0x00,
0x3389,0x00,
0x338a,0x00,
0x338b,0x00,
0x338c,0x00,
0x338d,0x00,
0x338e,0x00,
0x338f,0x00,
0x3390,0x00,
0x3391,0x00,
0x3392,0x00,
0x3393,0x00,
0x3394,0x00,
0x3395,0x00,
0x3396,0x00,
0x3397,0x00,
0x3398,0x00,
0x3399,0x00,
0x339a,0x00,
0x339b,0x00,
0x33b0,0x00,
0x33b1,0x50,
0x33b2,0x01,
0x33b3,0xff,
0x33b4,0xe0,
0x33b5,0x6b,
0x33b6,0x00,
0x33b7,0x00,
0x33b8,0x00,
0x33b9,0x00,
0x33ba,0x02,
0x33bb,0x08,
0x33bc,0x01,
0x33bd,0x01,
0x33be,0x01,
0x33bf,0x01,
0x33c0,0x00,
0x33c1,0x00,
0x33c2,0x00,
0x33c3,0x00,
0x33e0,0x14,
0x33e1,0x0f,
0x33e2,0x04,
0x33e3,0x02,
0x33e4,0x01,
0x33e5,0x01,
0x33e6,0x00,
0x33e7,0x04,
0x33e8,0x0c,
0x33e9,0x00,
0x33ea,0x01,
0x33eb,0x02,
0x33ec,0x03,
0x33ed,0x02,
0x33ee,0x05,
0x33ef,0x0a,
0x33f0,0x08,
0x33f1,0x04,
0x33f2,0x04,
0x33f3,0x00,
0x33f4,0x03,
0x33f5,0x14,
0x33f6,0x0f,
0x33f7,0x02,
0x33f8,0x01,
0x33f9,0x01,
0x33fa,0x01,
0x33fb,0x00,
0x33fc,0x04,
0x33fd,0x0c,
0x33fe,0x00,
0x33ff,0x01,
0x3400,0x02,
0x3401,0x03,
0x3402,0x01,
0x3403,0x02,
0x3404,0x08,
0x3405,0x08,
0x3406,0x04,
0x3407,0x04,
0x3408,0x00,
0x3409,0x03,
0x340a,0x14,
0x340b,0x0f,
0x340c,0x04,
0x340d,0x02,
0x340e,0x01,
0x340f,0x01,
0x3410,0x00,
0x3411,0x04,
0x3412,0x0c,
0x3413,0x00,
0x3414,0x01,
0x3415,0x02,
0x3416,0x03,
0x3417,0x02,
0x3418,0x05,
0x3419,0x0a,
0x341a,0x08,
0x341b,0x04,
0x341c,0x04,
0x341d,0x00,
0x341e,0x03,
0x3440,0x00,
0x3441,0x00,
0x3442,0x00,
0x3443,0x00,
0x3444,0x02,
0x3445,0xf0,
0x3446,0x02,
0x3447,0x08,
0x3448,0x00,
0x3460,0x40,
0x3461,0x40,
0x3462,0x40,
0x3463,0x40,
0x3464,0x03,
0x3465,0x01,
0x3466,0x01,
0x3467,0x02,
0x3468,0x30,
0x3469,0x00,
0x346a,0x33,
0x346b,0xbf,
0x3480,0x40,
0x3481,0x00,
0x3482,0x00,
0x3483,0x00,
0x3484,0x07,
0x3485,0x00,
0x3486,0x00,
0x3487,0x00,
0x3488,0x00,
0x3489,0x00,
0x348a,0x00,
0x348b,0x04,
0x348c,0x00,
0x348d,0x01,
0x348f,0x01,
0x7000,0xda,
0x7001,0xcf,
0x7002,0xac,
0x7003,0xd0,
0x7004,0xac,
0x7005,0xd1,
0x7006,0x50,
0x7007,0xb6,
0x7008,0xee,
0x7009,0xac,
0x700a,0xd2,
0x700b,0xdc,
0x700c,0xdf,
0x700d,0x0f,
0x700e,0xe1,
0x700f,0x36,
0x7010,0x30,
0x7011,0xd3,
0x7012,0x2e,
0x7013,0x54,
0x7014,0x46,
0x7015,0xb4,
0x7016,0x00,
0x7017,0x1a,
0x7018,0xc1,
0x7019,0x0e,
0x701a,0xe8,
0x701b,0x00,
0x701c,0xe6,
0x701d,0xb0,
0x701e,0x6e,
0x701f,0xbd,
0x7020,0x01,
0x7021,0xd7,
0x7022,0xed,
0x7023,0xbc,
0x7024,0x22,
0x7025,0xb9,
0x7026,0x66,
0x7027,0x2c,
0x7028,0x28,
0x7029,0x19,
0x702a,0xc1,
0x702b,0x32,
0x702c,0xa1,
0x702d,0xac,
0x702e,0xd8,
0x702f,0xd6,
0x7030,0xb4,
0x7031,0x04,
0x7032,0x46,
0x7033,0xb7,
0x7034,0x00,
0x7035,0xbe,
0x7036,0x08,
0x7037,0xc3,
0x7038,0xdb,
0x7039,0xad,
0x703a,0xc3,
0x703b,0xbf,
0x703c,0x50,
0x703d,0x20,
0x703e,0xb8,
0x703f,0x02,
0x7040,0xbc,
0x7041,0x17,
0x7042,0xdb,
0x7043,0xa0,
0x7044,0xb8,
0x7045,0x00,
0x7046,0x28,
0x7047,0x54,
0x7048,0xb4,
0x7049,0xbc,
0x704a,0xbe,
0x704b,0x06,
0x704c,0xd8,
0x704d,0xd6,
0x704e,0x00,
0x704f,0xb9,
0x7050,0x64,
0x7051,0xee,
0x7052,0xe8,
0x7053,0xb4,
0x7054,0x14,
0x7055,0xab,
0x7056,0xbc,
0x7057,0x17,
0x7058,0x62,
0x7059,0x07,
0x705a,0xb9,
0x705b,0x05,
0x705c,0xad,
0x705d,0xb4,
0x705e,0x25,
0x705f,0xc3,
0x7060,0xc1,
0x7061,0x00,
0x7062,0xc0,
0x7063,0x42,
0x7064,0x50,
0x7065,0x20,
0x7066,0x04,
0x7067,0xb8,
0x7068,0x02,
0x7069,0xdb,
0x706a,0xd8,
0x706b,0xac,
0x706c,0xb7,
0x706d,0x00,
0x706e,0xbc,
0x706f,0x11,
0x7070,0xd6,
0x7071,0xc7,
0x7072,0xb8,
0x7073,0x00,
0x7074,0x28,
0x7075,0x54,
0x7076,0xb4,
0x7077,0x04,
0x7078,0x46,
0x7079,0xbe,
0x707a,0x06,
0x707b,0xc3,
0x707c,0xdb,
0x707d,0xbd,
0x707e,0x03,
0x707f,0xee,
0x7080,0xad,
0x7081,0xc3,
0x7082,0xbf,
0x7083,0x00,
0x7084,0xec,
0x7085,0x00,
0x7086,0x15,
0x7087,0xc2,
0x7088,0x47,
0x7089,0xc3,
0x708a,0xb7,
0x708b,0xc0,
0x708c,0x43,
0x708d,0x00,
0x708e,0x00,
0x708f,0x00,
0x7090,0xb9,
0x7091,0x64,
0x7092,0x29,
0x7093,0x00,
0x7094,0xb8,
0x7095,0x12,
0x7096,0xbe,
0x7097,0x01,
0x7098,0xd0,
0x7099,0xbc,
0x709a,0x01,
0x709b,0xac,
0x709c,0x37,
0x709d,0xd1,
0x709e,0xac,
0x709f,0xd2,
0x70a0,0xac,
0x70a1,0xad,
0x70a2,0x28,
0x70a3,0x00,
0x70a4,0xb8,
0x70a5,0x00,
0x70a6,0xbc,
0x70a7,0x01,
0x70a8,0xe1,
0x70a9,0x36,
0x70aa,0xd3,
0x70ab,0x30,
0x70ac,0x04,
0x70ad,0xe0,
0x70ae,0xd8,
0x70af,0xb4,
0x70b0,0xcd,
0x70b1,0x45,
0x70b2,0x00,
0x70b3,0xe8,
0x70b4,0xbe,
0x70b5,0x05,
0x70b6,0xbc,
0x70b7,0x1e,
0x70b8,0x62,
0x70b9,0x07,
0x70ba,0xb9,
0x70bb,0x05,
0x70bc,0xad,
0x70bd,0xc3,
0x70be,0xd2,
0x70bf,0x00,
0x70c0,0x15,
0x70c1,0xc2,
0x70c2,0x64,
0x70c3,0xc3,
0x70c4,0xcd,
0x70c5,0xc0,
0x70c6,0x60,
0x70c7,0x00,
0x70c8,0x46,
0x70c9,0x00,
0x70ca,0x00,
0x70cb,0x19,
0x70cc,0xc1,
0x70cd,0x7e,
0x70ce,0xa1,
0x70cf,0xb9,
0x70d0,0x64,
0x70d1,0x29,
0x70d2,0x00,
0x70d3,0xb8,
0x70d4,0x02,
0x70d5,0xbe,
0x70d6,0x02,
0x70d7,0xd0,
0x70d8,0xdc,
0x70d9,0xac,
0x70da,0xbc,
0x70db,0x01,
0x70dc,0x37,
0x70dd,0xd1,
0x70de,0xac,
0x70df,0xd2,
0x70e0,0xad,
0x70e1,0x28,
0x70e2,0x00,
0x70e3,0xb8,
0x70e4,0x00,
0x70e5,0xbc,
0x70e6,0x01,
0x70e7,0xe1,
0x70e8,0x36,
0x70e9,0x30,
0x70ea,0xe0,
0x70eb,0xd8,
0x70ec,0xb5,
0x70ed,0x06,
0x70ee,0x45,
0x70ef,0xd6,
0x70f0,0xbe,
0x70f1,0x07,
0x70f2,0x00,
0x70f3,0xe8,
0x70f4,0x62,
0x70f5,0x07,
0x70f6,0xb9,
0x70f7,0x05,
0x70f8,0xad,
0x70f9,0xc3,
0x70fa,0xd2,
0x70fb,0x46,
0x70fc,0xd5,
0x70fd,0xe3,
0x70fe,0x18,
0x70ff,0xc2,
0x7100,0xae,
0x7101,0xb9,
0x7102,0x64,
0x7103,0xd1,
0x7104,0x50,
0x7105,0xdd,
0x7106,0xac,
0x7107,0xcf,
0x7108,0xdf,
0x7109,0xb6,
0x710a,0xee,
0x710b,0xbc,
0x710c,0x13,
0x710d,0xe1,
0x710e,0x36,
0x710f,0x30,
0x7110,0xd3,
0x7111,0x2e,
0x7112,0x54,
0x7113,0xbc,
0x7114,0x32,
0x7115,0x2c,
0x7116,0x50,
0x7117,0x20,
0x7118,0x04,
0x7119,0xb8,
0x711a,0x02,
0x711b,0xbc,
0x711c,0x18,
0x711d,0xc7,
0x711e,0xb8,
0x711f,0x00,
0x7120,0x28,
0x7121,0x54,
0x7122,0xb4,
0x7123,0xbf,
0x7124,0x46,
0x7125,0xbe,
0x7126,0x04,
0x7127,0xd6,
0x7128,0xd8,
0x7129,0xab,
0x712a,0x00,
0x712b,0xe8,
0x712c,0x62,
0x712d,0x07,
0x712e,0xb9,
0x712f,0x05,
0x7130,0xad,
0x7131,0xc3,
0x7132,0xbf,
0x7133,0xb9,
0x7134,0x64,
0x7135,0x29,
0x7136,0x00,
0x7137,0xb8,
0x7138,0x02,
0x7139,0xbe,
0x713a,0x00,
0x713b,0xe6,
0x713c,0xbd,
0x713d,0x03,
0x713e,0xec,
0x713f,0xad,
0x7140,0xe2,
0x7141,0x28,
0x7142,0x00,
0x7143,0xb8,
0x7144,0x00,
0x7145,0xe0,
0x7146,0xd8,
0x7147,0xb4,
0x7148,0xcd,
0x7149,0x45,
0x714a,0xbe,
0x714b,0x03,
0x714c,0x00,
0x714d,0x30,
0x714e,0xe8,
0x714f,0xbc,
0x7150,0x1c,
0x7151,0x62,
0x7152,0x07,
0x7153,0xb9,
0x7154,0x05,
0x7155,0xad,
0x7156,0xc3,
0x7157,0xd2,
0x7158,0x46,
0x7159,0xe4,
0x715a,0xd5,
0x715b,0x00,
0x715c,0x17,
0x715d,0xc2,
0x715e,0xc6,
0x715f,0xde,
0x7160,0xcf,
0x7161,0xdf,
0x7162,0xac,
0x7163,0xd1,
0x7164,0x44,
0x7165,0xac,
0x7166,0xb9,
0x7167,0x76,
0x7168,0xb8,
0x7169,0x08,
0x716a,0xb6,
0x716b,0xfe,
0x716c,0xb4,
0x716d,0xbf,
0x716e,0xd6,
0x716f,0xd8,
0x7170,0xab,
0x7171,0xe8,
0x7172,0x00,
0x7173,0xe1,
0x7174,0x36,
0x7175,0x30,
0x7176,0xd3,
0x7177,0xbc,
0x7178,0x5e,
0x7179,0xb4,
0x717a,0x1d,
0x717b,0xaa,
0x717c,0xb8,
0x717d,0x0c,
0x717e,0x45,
0x717f,0xe6,
0x7180,0xbd,
0x7181,0x03,
0x7182,0xec,
0x7183,0xbc,
0x7184,0x7d,
0x7185,0xc3,
0x7186,0xd2,
0x7187,0x42,
0x7188,0xb8,
0x7189,0x00,
0x718a,0xe4,
0x718b,0xd5,
0x718c,0xb6,
0x718d,0x00,
0x718e,0xb9,
0x718f,0x0a,
0x7190,0xbd,
0x7191,0x03,
0x7192,0xb5,
0x7193,0x4b,
0x7194,0x40,
0x7195,0x58,
0x7196,0x76,
0x7197,0x01,
0x7198,0x6a,
0x7199,0xdd,
0x719a,0x1a,
0x719b,0xc2,
0x719c,0xd1,
0x719d,0xe8,
0x719e,0xbd,
0x719f,0x03,
0x71a0,0xe6,
0x71a1,0xec,
0x71a2,0xbc,
0x71a3,0x19,
0x71a4,0xb9,
0x71a5,0xf6,
0x71a6,0x14,
0x71a7,0xc1,
0x71a8,0xda,
0x71a9,0xd1,
0x71aa,0xac,
0x71ab,0x37,
0x71ac,0xbc,
0x71ad,0x35,
0x71ae,0x36,
0x71af,0x30,
0x71b0,0xe1,
0x71b1,0xd3,
0x71b2,0xc0,
0x71b3,0xd3,
0x71b4,0xb6,
0x71b5,0x0c,
0x71b6,0xff,
0x71b7,0xb4,
0x71b8,0xbc,
0x71b9,0xd9,
0x71ba,0x00,
0x71bb,0xe8,
0x71bc,0x56,
0x71bd,0xc0,
0x71be,0xe3,
0x71bf,0xb4,
0x71c0,0x1d,
0x71c1,0x56,
0x71c2,0xaa,
0x71c3,0xbc,
0x71c4,0x1a,
0x71c5,0x00,
0x71c6,0xb5,
0x71c7,0x48,
0x71c8,0x57,
0x71c9,0x00,
0x71ca,0x54,
0x71cb,0xe7,
0x71cc,0xc8,
0x71cd,0xb5,
0x71ce,0x13,
0x71cf,0xd9,
0x71d0,0x00,
0x71d1,0xe8,
0x71d2,0x56,
0x71d3,0x08,
0x71d4,0xb4,
0x71d5,0x44,
0x71d6,0x57,
0x71d7,0x00,
0x71d8,0x54,
0x71d9,0xe7,
0x71da,0xc8,
0x71db,0xab,
0x71dc,0x00,
0x71dd,0x66,
0x71de,0x62,
0x71df,0x06,
0x71e0,0x74,
0x71e1,0xb9,
0x71e2,0x05,
0x71e3,0xb7,
0x71e4,0x10,
0x71e5,0xbc,
0x71e6,0x26,
0x71e7,0xb7,
0x71e8,0x00,
0x71e9,0xc8,
0x7600,0x04,
0x7601,0x80,
0x7602,0x07,
0x7603,0x44,
0x7604,0x05,
0x7605,0x33,
0x7606,0x0f,
0x7607,0x00,
0x7608,0x07,
0x7609,0x40,
0x760a,0x04,
0x760b,0xe5,
0x760c,0x06,
0x760d,0x50,
0x760e,0x04,
0x760f,0xe4,
0x7610,0x00,
0x7611,0x00,
0x7612,0x06,
0x7613,0x5c,
0x7614,0x00,
0x7615,0x0f,
0x7616,0x06,
0x7617,0x1c,
0x7618,0x00,
0x7619,0x02,
0x761a,0x06,
0x761b,0xa0,
0x761c,0x00,
0x761d,0x01,
0x761e,0x06,
0x761f,0xac,
0x7620,0x00,
0x7621,0x0f,
0x7622,0x05,
0x7623,0x30,
0x7624,0x07,
0x7625,0x00,
0x7626,0x0f,
0x7627,0x00,
0x7628,0x04,
0x7629,0xe5,
0x762a,0x05,
0x762b,0x33,
0x762c,0x06,
0x762d,0x50,
0x762e,0x00,
0x762f,0x01,
0x7630,0x06,
0x7631,0x5c,
0x7632,0x04,
0x7633,0xe4,
0x7634,0x00,
0x7635,0x0e,
0x7636,0x05,
0x7637,0x30,
0x7638,0x0f,
0x7639,0x00,
0x763a,0x06,
0x763b,0x24,
0x763c,0x00,
0x763d,0x03,
0x763e,0x05,
0x763f,0x33,
0x7640,0x07,
0x7641,0x02,
0x7642,0x06,
0x7643,0x24,
0x7644,0x00,
0x7645,0x01,
0x7646,0x06,
0x7647,0x20,
0x7648,0x0f,
0x7649,0x00,
0x764a,0x06,
0x764b,0x14,
0x764c,0x00,
0x764d,0x03,
0x764e,0x05,
0x764f,0x33,
0x7650,0x07,
0x7651,0x02,
0x7652,0x06,
0x7653,0x14,
0x7654,0x00,
0x7655,0x01,
0x7656,0x06,
0x7657,0x10,
0x7658,0x0f,
0x7659,0x00,
0x765a,0x06,
0x765b,0x10,
0x765c,0x0f,
0x765d,0x00,
0x765e,0x06,
0x765f,0x20,
0x7660,0x0f,
0x7661,0x00,
0x7662,0x00,
0x7663,0x00,
0x7664,0x00,
0x7665,0x02,
0x7666,0x04,
0x7667,0xe5,
0x7668,0x04,
0x7669,0xe4,
0x766a,0x0f,
0x766b,0x00,
0x766c,0x00,
0x766d,0x00,
0x766e,0x00,
0x766f,0x02,
0x7670,0x04,
0x7671,0xe5,
0x7672,0x04,
0x7673,0xe4,
0x7674,0x0f,
0x7675,0x00,
0x7676,0x00,
0x7677,0x02,
0x7678,0x04,
0x7679,0xe4,
0x767a,0x00,
0x767b,0x02,
0x767c,0x04,
0x767d,0xc4,
0x767e,0x00,
0x767f,0x04,
0x7680,0x04,
0x7681,0xc4,
0x7682,0x05,
0x7683,0x83,
0x7684,0x07,
0x7685,0x02,
0x7686,0x0f,
0x7687,0x00,
0x7688,0x00,
0x7689,0x02,
0x768a,0x04,
0x768b,0xe4,
0x768c,0x00,
0x768d,0x02,
0x768e,0x04,
0x768f,0xc4,
0x7690,0x00,
0x7691,0x04,
0x7692,0x04,
0x7693,0xc4,
0x7694,0x05,
0x7695,0x83,
0x7696,0x07,
0x7697,0x02,
0x7698,0x03,
0x7699,0x0b,
0x769a,0x05,
0x769b,0x83,
0x769c,0x00,
0x769d,0x08,
0x769e,0x05,
0x769f,0x03,
0x76a0,0x05,
0x76a1,0x32,
0x76a2,0x00,
0x76a3,0x00,
0x76a4,0x05,
0x76a5,0x70,
0x76a6,0x00,
0x76a7,0x01,
0x76a8,0x05,
0x76a9,0x74,
0x76aa,0x03,
0x76ab,0x9a,
0x76ac,0x05,
0x76ad,0x83,
0x76ae,0x00,
0x76af,0x05,
0x76b0,0x05,
0x76b1,0x03,
0x76b2,0x05,
0x76b3,0x32,
0x76b4,0x00,
0x76b5,0x00,
0x76b6,0x05,
0x76b7,0x70,
0x76b8,0x00,
0x76b9,0x01,
0x76ba,0x05,
0x76bb,0x74,
0x76bc,0x03,
0x76bd,0x99,
0x76be,0x05,
0x76bf,0x83,
0x76c0,0x00,
0x76c1,0x03,
0x76c2,0x05,
0x76c3,0x03,
0x76c4,0x05,
0x76c5,0x32,
0x76c6,0x00,
0x76c7,0x00,
0x76c8,0x05,
0x76c9,0x70,
0x76ca,0x00,
0x76cb,0x01,
0x76cc,0x05,
0x76cd,0x74,
0x76ce,0x03,
0x76cf,0x98,
0x76d0,0x05,
0x76d1,0x83,
0x76d2,0x00,
0x76d3,0x01,
0x76d4,0x05,
0x76d5,0x03,
0x76d6,0x05,
0x76d7,0x32,
0x76d8,0x00,
0x76d9,0x00,
0x76da,0x05,
0x76db,0x70,
0x76dc,0x00,
0x76dd,0x01,
0x76de,0x05,
0x76df,0x74,
0x76e0,0x03,
0x76e1,0x97,
0x76e2,0x05,
0x76e3,0x83,
0x76e4,0x00,
0x76e5,0x01,
0x76e6,0x05,
0x76e7,0x03,
0x76e8,0x05,
0x76e9,0x32,
0x76ea,0x00,
0x76eb,0x00,
0x76ec,0x05,
0x76ed,0x70,
0x76ee,0x00,
0x76ef,0x01,
0x76f0,0x05,
0x76f1,0x74,
0x76f2,0x03,
0x76f3,0x96,
0x76f4,0x05,
0x76f5,0x83,
0x76f6,0x00,
0x76f7,0x01,
0x76f8,0x05,
0x76f9,0x03,
0x76fa,0x05,
0x76fb,0x32,
0x76fc,0x00,
0x76fd,0x00,
0x76fe,0x05,
0x76ff,0x70,
0x7700,0x00,
0x7701,0x01,
0x7702,0x05,
0x7703,0x74,
0x7704,0x03,
0x7705,0x95,
0x7706,0x05,
0x7707,0x83,
0x7708,0x00,
0x7709,0x01,
0x770a,0x05,
0x770b,0x03,
0x770c,0x05,
0x770d,0x32,
0x770e,0x00,
0x770f,0x00,
0x7710,0x05,
0x7711,0x70,
0x7712,0x00,
0x7713,0x01,
0x7714,0x05,
0x7715,0x74,
0x7716,0x03,
0x7717,0x94,
0x7718,0x05,
0x7719,0x83,
0x771a,0x00,
0x771b,0x03,
0x771c,0x05,
0x771d,0x03,
0x771e,0x05,
0x771f,0x32,
0x7720,0x00,
0x7721,0x00,
0x7722,0x05,
0x7723,0x70,
0x7724,0x00,
0x7725,0x01,
0x7726,0x05,
0x7727,0x74,
0x7728,0x03,
0x7729,0x93,
0x772a,0x05,
0x772b,0x83,
0x772c,0x00,
0x772d,0x02,
0x772e,0x05,
0x772f,0x03,
0x7730,0x05,
0x7731,0x32,
0x7732,0x00,
0x7733,0x00,
0x7734,0x05,
0x7735,0x70,
0x7736,0x00,
0x7737,0x01,
0x7738,0x05,
0x7739,0x74,
0x773a,0x03,
0x773b,0x92,
0x773c,0x05,
0x773d,0x83,
0x773e,0x00,
0x773f,0x01,
0x7740,0x05,
0x7741,0x03,
0x7742,0x05,
0x7743,0x32,
0x7744,0x00,
0x7745,0x00,
0x7746,0x05,
0x7747,0x70,
0x7748,0x00,
0x7749,0x01,
0x774a,0x05,
0x774b,0x74,
0x774c,0x03,
0x774d,0x91,
0x774e,0x05,
0x774f,0x83,
0x7750,0x00,
0x7751,0x01,
0x7752,0x05,
0x7753,0x03,
0x7754,0x05,
0x7755,0x32,
0x7756,0x00,
0x7757,0x00,
0x7758,0x05,
0x7759,0x70,
0x775a,0x00,
0x775b,0x01,
0x775c,0x05,
0x775d,0x74,
0x775e,0x03,
0x775f,0x90,
0x7760,0x05,
0x7761,0x83,
0x7762,0x00,
0x7763,0x01,
0x7764,0x05,
0x7765,0x03,
0x7766,0x05,
0x7767,0x32,
0x7768,0x00,
0x7769,0x00,
0x776a,0x05,
0x776b,0x70,
0x776c,0x00,
0x776d,0x01,
0x776e,0x05,
0x776f,0x74,
0x7770,0x02,
0x7771,0x90,
0x7772,0x05,
0x7773,0x03,
0x7774,0x07,
0x7775,0x00,
0x7776,0x0f,
0x7777,0x00,
0x7778,0x08,
0x7779,0x31,
0x777a,0x08,
0x777b,0xd1,
0x777c,0x0f,
0x777d,0x00,
0x777e,0x04,
0x777f,0xe5,
0x7780,0x06,
0x7781,0x50,
0x7782,0x04,
0x7783,0xe4,
0x7784,0x00,
0x7785,0x00,
0x7786,0x06,
0x7787,0x5c,
0x7788,0x09,
0x7789,0x14,
0x778a,0x06,
0x778b,0x1c,
0x778c,0x00,
0x778d,0x02,
0x778e,0x06,
0x778f,0xa0,
0x7790,0x00,
0x7791,0x01,
0x7792,0x06,
0x7793,0xac,
0x7794,0x00,
0x7795,0x0f,
0x7796,0x05,
0x7797,0x30,
0x7798,0x0f,
0x7799,0x00,
0x779a,0x00,
0x779b,0x00,
0x779c,0x00,
0x779d,0x02,
0x779e,0x04,
0x779f,0xe5,
0x77a0,0x04,
0x77a1,0xe4,
0x77a2,0x07,
0x77a3,0x10,
0x77a4,0x00,
0x77a5,0x00,
0x77a6,0x07,
0x77a7,0x00,
0x77a8,0x01,
0x77a9,0xbb,
0x77aa,0x07,
0x77ab,0x10,
0x77ac,0x00,
0x77ad,0x00,
0x77ae,0x07,
0x77af,0x00,
0x77b0,0x01,
0x77b1,0xaa,
0x77b2,0x07,
0x77b3,0x10,
0x77b4,0x00,
0x77b5,0x00,
0x77b6,0x07,
0x77b7,0x00,
0x77b8,0x01,
0x77b9,0x99,
0x77ba,0x07,
0x77bb,0x10,
0x77bc,0x00,
0x77bd,0x00,
0x77be,0x07,
0x77bf,0x00,
0x77c0,0x01,
0x77c1,0x88,
0x77c2,0x07,
0x77c3,0x10,
0x77c4,0x00,
0x77c5,0x00,
0x77c6,0x07,
0x77c7,0x00,
0x77c8,0x01,
0x77c9,0x77,
0x77ca,0x07,
0x77cb,0x10,
0x77cc,0x00,
0x77cd,0x00,
0x77ce,0x07,
0x77cf,0x00,
0x77d0,0x01,
0x77d1,0x66,
0x77d2,0x07,
0x77d3,0x10,
0x77d4,0x00,
0x77d5,0x00,
0x77d6,0x07,
0x77d7,0x00,
0x77d8,0x01,
0x77d9,0x55,
0x77da,0x07,
0x77db,0x10,
0x77dc,0x00,
0x77dd,0x00,
0x77de,0x07,
0x77df,0x00,
0x77e0,0x01,
0x77e1,0x44,
0x77e2,0x07,
0x77e3,0x10,
0x77e4,0x00,
0x77e5,0x00,
0x77e6,0x07,
0x77e7,0x00,
0x77e8,0x01,
0x77e9,0x33,
0x77ea,0x07,
0x77eb,0x10,
0x77ec,0x00,
0x77ed,0x00,
0x77ee,0x07,
0x77ef,0x00,
0x77f0,0x01,
0x77f1,0x22,
0x77f2,0x07,
0x77f3,0x10,
0x77f4,0x00,
0x77f5,0x00,
0x77f6,0x07,
0x77f7,0x00,
0x77f8,0x01,
0x77f9,0x11,
0x77fa,0x07,
0x77fb,0x10,
0x77fc,0x00,
0x77fd,0x00,
0x77fe,0x07,
0x77ff,0x00,
0x7800,0x01,
0x7801,0x00,
0x7802,0x01,
0x7803,0xff,
0x7804,0x07,
0x7805,0x00,
0x7806,0x02,
0x7807,0xa0,
0x7808,0x05,
0x7809,0x33,
0x780a,0x0f,
0x780b,0x00,
0x780c,0x08,
0x780d,0x36,
0x780e,0x06,
0x780f,0x50,
0x7810,0x04,
0x7811,0xe4,
0x7812,0x00,
0x7813,0x00,
0x7814,0x06,
0x7815,0x5c,
0x7816,0x09,
0x7817,0x14,
0x7818,0x06,
0x7819,0x1c,
0x781a,0x05,
0x781b,0x33,
0x781c,0x00,
0x781d,0x01,
0x781e,0x06,
0x781f,0x24,
0x7820,0x00,
0x7821,0x01,
0x7822,0x06,
0x7823,0x20,
0x7824,0x0f,
0x7825,0x00,
0x7826,0x08,
0x7827,0x36,
0x7828,0x07,
0x7829,0x10,
0x782a,0x00,
0x782b,0x00,
0x782c,0x07,
0x782d,0x00,
0x782e,0x01,
0x782f,0xbb,
0x7830,0x07,
0x7831,0x10,
0x7832,0x00,
0x7833,0x00,
0x7834,0x07,
0x7835,0x00,
0x7836,0x01,
0x7837,0xaa,
0x7838,0x07,
0x7839,0x10,
0x783a,0x00,
0x783b,0x00,
0x783c,0x07,
0x783d,0x00,
0x783e,0x01,
0x783f,0x99,
0x7840,0x07,
0x7841,0x10,
0x7842,0x00,
0x7843,0x00,
0x7844,0x07,
0x7845,0x00,
0x7846,0x01,
0x7847,0x88,
0x7848,0x07,
0x7849,0x10,
0x784a,0x00,
0x784b,0x00,
0x784c,0x07,
0x784d,0x00,
0x784e,0x01,
0x784f,0x77,
0x7850,0x07,
0x7851,0x10,
0x7852,0x00,
0x7853,0x00,
0x7854,0x07,
0x7855,0x00,
0x7856,0x01,
0x7857,0x66,
0x7858,0x07,
0x7859,0x10,
0x785a,0x00,
0x785b,0x00,
0x785c,0x07,
0x785d,0x00,
0x785e,0x01,
0x785f,0x55,
0x7860,0x07,
0x7861,0x10,
0x7862,0x00,
0x7863,0x00,
0x7864,0x07,
0x7865,0x00,
0x7866,0x01,
0x7867,0x44,
0x7868,0x07,
0x7869,0x10,
0x786a,0x00,
0x786b,0x00,
0x786c,0x07,
0x786d,0x00,
0x786e,0x01,
0x786f,0x33,
0x7870,0x07,
0x7871,0x10,
0x7872,0x00,
0x7873,0x00,
0x7874,0x07,
0x7875,0x00,
0x7876,0x01,
0x7877,0x22,
0x7878,0x07,
0x7879,0x10,
0x787a,0x00,
0x787b,0x00,
0x787c,0x07,
0x787d,0x00,
0x787e,0x01,
0x787f,0x11,
0x7880,0x07,
0x7881,0x10,
0x7882,0x00,
0x7883,0x00,
0x7884,0x07,
0x7885,0x00,
0x7886,0x01,
0x7887,0x00,
0x7888,0x01,
0x7889,0xff,
0x788a,0x02,
0x788b,0xa0,
0x788c,0x05,
0x788d,0x33,
0x788e,0x0f,
0x788f,0x00,
0x7890,0x08,
0x7891,0x3b,
0x7892,0x08,
0x7893,0x5e,
0x7894,0x0f,
0x7895,0x00,
0x7896,0x04,
0x7897,0xc0,
0x7898,0x09,
0x7899,0x14,
0x789a,0x04,
0x789b,0x99,
0x789c,0x07,
0x789d,0x14,
0x789e,0x04,
0x789f,0x80,
0x78a0,0x04,
0x78a1,0xa4,
0x78a2,0x00,
0x78a3,0x0a,
0x78a4,0x04,
0x78a5,0xa6,
0x78a6,0x00,
0x78a7,0x00,
0x78a8,0x04,
0x78a9,0xa0,
0x78aa,0x04,
0x78ab,0x80,
0x78ac,0x04,
0x78ad,0x00,
0x78ae,0x05,
0x78af,0x03,
0x78b0,0x06,
0x78b1,0x00,
0x78b2,0x0f,
0x78b3,0x00,
0x78b4,0x0f,
0x78b5,0x00,
0x78b6,0x0f,
0x78b7,0x00,
0x30a0,0x00,
0x30a1,0x00,
0x30a2,0x00,
0x30a3,0x00,
0x30a4,0x07,
0x30a5,0x8e,
0x30a6,0x04,
0x30a7,0x47,
0x30a8,0x00,
0x30a9,0x04,
0x30aa,0x00,
0x30ab,0x04,
0x30ac,0x07,
0x30ad,0x88,
0x30ae,0x04,
0x30af,0x40,
0x30b0,0x0a,
0x30b1,0x34,
0x30b2,0x04,
0x30b3,0x70,
0x30bb,0x40,
0x3196,0x00,
0x3197,0x00,
0x3195,0x29,
0x315a,0x02,
0x315b,0x00,
0x3190,0x38,
0x304b,0x00,
0x304d,0xa4,
0x3033,0x30,
0x3012,0x01,
0x315a,0x02,
0x315b,0x00,
0x30a8,0x00,
0x30a9,0x04,
0x30aa,0x00,
0x30ab,0x04,
0x30ac,0x07,
0x30ad,0x80,
0x30ae,0x04,
0x30af,0x38,
0x31A3,0x08,
0x31FE,0x01,
0x3195,0x04,
};

unsigned int bypass_on[][2] = {
0xfffd,0x80,
0xfffe,0x50,
0x004d,0x01,
};

unsigned int bypass_off[][2] = {
0xfffd,0x80,
0xfffe,0x50,
0x004d,0x00,
};



void write_reg(unsigned int reg[][2], int num)
{
	int i;

	
	for(i = 0; i < num; i++)
	{	
		XC7022_write_cmos_sensor((unsigned short)(reg[i][0]), (unsigned char)(reg[i][1]));
		//LOG_ERR("0x%x,0x%x  [0x%x]\n", XC7027_default_regs[i][0], XC7022_read_cmos_sensor(XC7027_default_regs[i][0]), XC7027_default_regs[i][1]);
		usleep(2000);
	}
}

void XC7027_i2c_bypass_on()
{	
	write_reg(bypass_on, sizeof(bypass_on) / 8);
}

void XC7027_i2c_bypass_off()
{
	write_reg(bypass_off, sizeof(bypass_off) / 8);
}

void XC7027MIPIOpen(void)
{	unsigned int isp_id;


	LOG_ERR("[XC7022MIPI_ISP] XC7027MIPIOpen begin!\n");
 	isp_id = (XC7022_read_cmos_sensor(0xfffb) << 8) | XC7022_read_cmos_sensor(0xfffc);
   	LOG_ERR("[XC7022MIPI_ISP]ISP_id[%x] \n",isp_id);

	write_reg(XC7027_default_regs, sizeof(XC7027_default_regs)/8);	
}

void OV2718MIPIOpen(void)
{	
	int i;
	unsigned short sensor_id = 0;    
	//return;

	LOG_ERR("[OV2718MIPI] OV2718MIPIOpen begin!\n");
	
	mDELAY(10);
	
	for(i=0;i<3;i++)
	{
		sensor_id = (OV2718MIPIYUV_read_cmos_sensor(0x300A) << 8) | OV2718MIPIYUV_read_cmos_sensor(0x300B);
		LOG_ERR("OV2718MIPIOpen: READ ID :%x\n", sensor_id);
		if(sensor_id != OV2718MIPI_SENSOR_ID){
			LOG_ERR("[OV2718MIPI] return FAIL\n ");
			#ifndef TEST_COLORBAR_MODE
			return;
			#endif
		}
	}

	int num = sizeof(OV2718_default_regs) / 8;
	for(i = 0; i < num; i++)
	{	
		OV2718MIPI_write_cmos_sensor((unsigned short)(OV2718_default_regs[i][0]), (unsigned char)(OV2718_default_regs[i][1]));
		//LOG_ERR("0x%x,0x%x  [0x%x]\n", OV2718_default_regs[i][0], XC7022_read_cmos_sensor(OV2718_default_regs[i][0]), OV2718_default_regs[i][1]);
		usleep(2000);
	}

}



