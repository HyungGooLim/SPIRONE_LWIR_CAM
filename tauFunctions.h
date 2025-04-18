#ifndef _TAUFUNCTIONS_H_
#define _TAUFUNCTIONS_H_

#define BATT_VOLTAGE_THRESH_SF   (double)100.00

#ifdef __cplusplus
extern "C" 
{
#else
    #include "photondefs.h"    
#endif

#define PIXEL_DEFAULT   8192


PHOTON_RESULT TauSetThermalThrottleButtonState(int deviceId, CAM_BUTTON_STATE functionId, short *thermVal);
PHOTON_RESULT TauGetProgramAddress(int deviceId, CAM_PROGRAM_TYPE progType, long *progAddr, long *progSizeBytes);
PHOTON_RESULT TauSetBatteryThresholds(int deviceId, double vOff, double v10, double v25, double v50, double v75, double v100);
PHOTON_RESULT TauWriteSymbols(int deviceId);
PHOTON_RESULT TauGetBatteryThresholds(int deviceId, double *vOff, double *v10, double *v25, double *v50, double *v75, double *v100);
PHOTON_RESULT TauGetFPAType(int deviceId, short* fpaType);
PHOTON_RESULT TauSetFPAType(int deviceId, short  fpaType);
PHOTON_RESULT TauReadCaptureImage(int deviceId, unsigned long address, short width, long *addrIncr, short pixBuff[]);
PHOTON_RESULT TauSetUserSymbolData(int deviceId, short symbolData[], short symbolDataSize);
PHOTON_RESULT TauGetNucAddress(int deviceId, int nuc, int type, unsigned long* addr, int *size);
PHOTON_RESULT TauReadDramNuc(int deviceId, short nucIndex, short offsetHi, short offsetLo, short dataLen, unsigned char *data);
PHOTON_RESULT TauWriteDramNuc(int deviceId, short nucIndex, short offsetHi, short offsetLo, short dataLen, unsigned char *data);
PHOTON_RESULT TauSetPixelGain(int deviceId, short row, short column, short totalColumns, short pixelValue);
PHOTON_RESULT TauWriteGainTable(int deviceId, short buffer);
PHOTON_RESULT TauSetBadPixel(int deviceId, short row, short column, short totalColumns, short badPixelFlag);
PHOTON_RESULT TauGetLensNumber(int deviceId, short *lensNumber);
PHOTON_RESULT TauSetLensNumber(int deviceId, short lensNumber);
PHOTON_RESULT TauWriteFFCOffsetForLens(int deviceId);
PHOTON_RESULT TauSetExtOffsetTempThresholds(int deviceId, short ROCZero, short ROCEighth, short ROCQuarter, 
											short ROCThreeEighth, short ROCHalf, short ROCFiveEighth, 
											short ROCThreeFourth, short ROCSevenEighth);
PHOTON_RESULT TauGetExtOffsetTempThresholds(int deviceId, short *ROCZero, short *ROCEighth, short *ROCQuarter, 
											short *ROCThreeEighth, short *ROCHalf, short *ROCFiveEighth, 
											short *ROCThreeFourth, short *ROCSevenEighth);

PHOTON_RESULT TauSetGainSwitchParams(int deviceId, TAU_GAIN_SWITCH_PARAMS gainSwitchParams);
PHOTON_RESULT TauGetGainSwitchParams(int deviceId, TAU_GAIN_SWITCH_PARAMS* gainSwitchParams);
PHOTON_RESULT TauSetBadPixelNew(int deviceId, short row, short column, short badPixelFlag);
PHOTON_RESULT TauCalculateFrameDiff(int deviceId, short diffFrame, short hotFrame, short coldFrame);
PHOTON_RESULT TauCalculateGainFrame(int deviceId, short gainFrame, short diffFrame, short average);
PHOTON_RESULT TauFindBadPixels(int deviceId, short gainFrame, short minPixelGain, short maxPixelGain);
PHOTON_RESULT TauGetBaudRate(int deviceId, short *baudRate);
PHOTON_RESULT TauSetBaudRate(int deviceId, short baudRate);
PHOTON_RESULT TauWriteGainTableNew(int deviceId, short buffer, short tableNum);
PHOTON_RESULT TauCalculateGain(int deviceId);
PHOTON_RESULT TauGetFlashStatus(int deviceId, short *status);



int expand_line(unsigned char* inp, short* out, int count);

#ifdef __cplusplus
}
#endif

#endif
