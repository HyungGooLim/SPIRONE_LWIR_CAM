/*!
 * @file photondefs.h
 * @brief Photon Camera enumeration declarations.
 *
 */


#ifndef _PHOTONDEFS_H_
#define _PHOTONDEFS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define _SDK			/* so Result enums are correct "sign" */

#include "camuser.h"

#ifndef WIN32
typedef unsigned char       BYTE;
typedef unsigned short      WORD;

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))

/* Define to GNU C function sleep()
   */
#define Sleep(x ) sleep(x)

#endif
//#include "camfactory.h"

typedef enum GainMode PHOTON_GAIN_MODE;
typedef enum FFCMode PHOTON_FFC_MODE;
typedef enum VideoMode PHOTON_VIDEO_MODE;
typedef enum VideoColor PHOTON_VIDEO_COLOR;
typedef enum VideoStandard PHOTON_VIDEO_STANDARD;
typedef enum ImageOrientation PHOTON_IMAGE_ORIENTATION;
typedef enum AGCAlgorithm PHOTON_AGC_ALGORITHM;
typedef enum TestPattern PHOTON_TEST_PATTERN;
typedef enum DigitalOut PHOTON_DIGITAL_OUT;
typedef enum ExtSyncMode PHOTON_EXT_SYNC_MODE;
typedef enum SpotMeterMode PHOTON_SPOT_METER_MODE;
typedef enum SpotDisplay PHOTON_SPOT_DISPLAY;
typedef enum IsothermMode PHOTON_ISOTHERM_MODE;
typedef enum IsothermThresholdType PHOTON_ISOTHERM_THRESHOLD_TYPE;
typedef enum ColorLut PHOTON_COLOR_LUT;
typedef enum ProductId PHOTON_PRODUCT_ID;
typedef enum proto_command PHOTON_USER_COMMAND;
typedef enum FPATempMode PHOTON_FPA_TEMP_MODE;
typedef enum Result PHOTON_RESULT;
typedef enum ShutterPosition PHOTON_SHUTTER_POSITION;
typedef enum Options PHOTON_OPTIONS;
typedef short PHOTON_TEMP;
typedef struct GainSwitchParams PHOTON_GAIN_SWITCH_PARAMS;
typedef struct CamRect PHOTON_RECT;
typedef enum Correction PHOTON_CORRECTION;
typedef enum ExtOffsetState PHOTON_OFFSETSTATE;
typedef enum PortId PORTID;
//typedef enum CamProgramType CAM_PROGRAM_TYPE;
//typedef enum SymbolTableFunctionIds CAM_SYMBOL_TABLE_COMMANDS;
//typedef enum SymbolFunctionIds CAM_SYMBOL_COMMANDS;
typedef enum NucDataType NUC_DATA_TYPE;

#ifdef __cplusplus
}
#endif

#endif /*_PHOTONDEFS_H_*/
