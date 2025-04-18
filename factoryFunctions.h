#ifndef _FACTORYFUNCTIONS_H_
#define _FACTORYFUNCTIONS_H_

#ifdef __cplusplus
extern "C" 
{
#ifdef _CAL
    #include "photonCalSDK.h"
#endif
#else
    #include "photondefs.h"    
    #include "photonfactory.h"    
#endif

    
#define TRUE 1
#define FALSE 0

//Splash screen related addresses

#define PHOTON_SPLASH1_ADDRESS 0x1FC0000
#define PHOTON640_SPLASH1_ADDRESS 0x1F30000

#define PHOTON_SPLASH1_START_BLOCK 62
#define PHOTON640_SPLASH1_START_BLOCK 243

#define PHOTON_BLOCK_SIZE_BYTES 0x20000
#define PHOTON640_BLOCK_SIZE_BYTES 0x10000

#define PHOTON640_NUM_SPLASH_BLOCKS 6
#define PHOTON_NUM_SPLASH_BLOCKS 1

#define SPLASH_SIZE PHOTON640_BLOCK_SIZE_BYTES * PHOTON640_NUM_SPLASH_BLOCKS
#define PALETTE_SIZE 0x400

#define PHOTON_FIRST_LUT_OFFSET 0x18000
#define PHOTON640_FIRST_LUT_OFFSET 0

#define PHOTON_PALETTE_OFFSET 0x1FC000
#define PHOTON640_PALETTE_OFFSET 0x7C00

#define PHOTON640_VIDEO_WIDTH 640
#define PHOTON640_VIDEO_NTSC_HEIGHT 480
#define PHOTON640_VIDEO_PAL_HEIGHT 512

#define PHOTON_VIDEO_WIDTH 256
#define PHOTON_VIDEO_HEIGHT 324


#define PHOTON640_SPLASH_OFFSET 0x8000
#define PHOTON_SPLASH_OFFSET 0

  


#define FLASH_OFFSET 0x1000000


#define BLOCK_TO_OFFSET(x) (x * PHOTON_BLOCK_SIZE_BYTES) + FLASH_OFFSET

#define PHOTON_FLASH_BLOCK_MIN 0
#define PHOTON640_FLASH_BLOCK_MIN 0

#define PHOTON_FLASH_BLOCK_MAX 127
#define PHOTON640_FLASH_BLOCK_MAX 255
	
#define CHECKSUM_LOCATION 0x1FE07FE


typedef int (*PROGRESSPERCENTAGE)(void* camObject, int percentage);
typedef int (*PROGRESSSTEP)(void* camObject, char* step);
typedef int (*HEXPROGRESSFUNC)(int /*port*/, long pos, long total, void* object);


typedef enum ThreadType
{
    SPLASH_SCREEN   = 0,
    UPGRADE_CAMERA  = 1
} PHOTON_THREAD;

PHOTON_RESULT PhotonDownloadFile(int deviceId, char* filepath, unsigned long offset, HEXPROGRESSFUNC progress, void* camObject);

PHOTON_RESULT PhotonEraseFlashBlock(int deviceId, short blockNumber);

PHOTON_RESULT PhotonReadMemory(int deviceId, unsigned long addr, short byteCount, unsigned char* data);

PHOTON_RESULT PhotonWriteMemory(int deviceId, unsigned long addr, short byteCount, unsigned char* data);

PHOTON_RESULT PhotonWriteBytes(int deviceId, unsigned long addr, int byteCount, unsigned char* data);

PHOTON_RESULT PhotonExecute(int deviceId, unsigned long addr);

PHOTON_RESULT PhotonGetCorrectionMask(int deviceId, short* correctionMask);

PHOTON_RESULT PhotonSetCorrectionMask(int deviceId, short correctionMask);

PHOTON_RESULT PhotonGetDigitalWindow(int deviceId, short* left, short* top, short* right, short* bottom);
PHOTON_RESULT PhotonGetDynamicDDE(int deviceId, short* value);
PHOTON_RESULT PhotonSetDynamicDDE(int deviceId, short value);
PHOTON_RESULT PhotonGetDDEState(int deviceId, short* ddeState);
PHOTON_RESULT PhotonSetDDEState(int deviceId, short ddeState);
PHOTON_RESULT PhotonGetProductId(int deviceId, short* productId);
PHOTON_RESULT PhotonGetGainSwitchParams(int deviceId, PHOTON_GAIN_SWITCH_PARAMS* gainSwitchParams);
PHOTON_RESULT PhotonSetGainSwitchParams(int deviceId, PHOTON_GAIN_SWITCH_PARAMS gainSwitchParams);
PHOTON_RESULT PhotonDownloadEncryptedFile(int deviceId, char* filename, unsigned long offset, HEXPROGRESSFUNC progress, void* camObject);
PHOTON_RESULT PhotonSetOptions(int deviceId, PHOTON_OPTIONS options);
PHOTON_RESULT PhotonLoadNucTable(int deviceId, short tableNum);
static int MyWriteBytes(int deviceId, unsigned long addr, int count, unsigned char* data);

#ifdef __cplusplus
}
#endif

#endif