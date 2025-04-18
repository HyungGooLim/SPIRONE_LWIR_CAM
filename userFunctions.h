#ifndef _USERFUNCTIONS_H_
#define _USERFUNCTIONS_H_
#ifdef __cplusplus
extern "C" 
{
#else
#include "photondefs.h"
//#include "photonfactory.h"
#endif


PHOTON_RESULT PhotonGetAGCFilterValue(int deviceId, short* value);
PHOTON_RESULT PhotonSetAGCFilterValue(int deviceId, short value);
PHOTON_RESULT PhotonGetAGCMean(int deviceId, short* mean);
PHOTON_RESULT PhotonGetAGCROI(int deviceId, PHOTON_RECT* coordinates);
PHOTON_RESULT PhotonSetAGCROI(int deviceId, PHOTON_RECT coordinates);
PHOTON_RESULT PhotonGetAGCType(int deviceId, PHOTON_AGC_ALGORITHM* agcType);
PHOTON_RESULT PhotonSetAGCType(int deviceId, PHOTON_AGC_ALGORITHM agcType);
PHOTON_RESULT PhotonGetBrightness(int deviceId, short* brightness);
PHOTON_RESULT PhotonSetBrightness(int deviceId, short brightness);
PHOTON_RESULT PhotonGetBrightnessBias(int deviceId, short* bias);
PHOTON_RESULT PhotonSetBrightnessBias(int deviceId, short bias);
PHOTON_RESULT PhotonGetContrast(int deviceId, short* contrast);
PHOTON_RESULT PhotonSetContrast(int deviceId, short contrast);
PHOTON_RESULT PhotonGetITTMidpoint(int deviceId, short* midpoint);
PHOTON_RESULT PhotonSetITTMidpoint(int deviceId, short midpoint);
PHOTON_RESULT PhotonGetMaxAGCGain(int deviceId, short* value);
PHOTON_RESULT PhotonSetMaxAGCGain(int deviceId, short value);
PHOTON_RESULT PhotonGetPlateauValue(int deviceId, short* value);
PHOTON_RESULT PhotonSetPlateauValue(int deviceId, short value);
PHOTON_RESULT PhotonDoNoOp(int deviceId);
PHOTON_RESULT PhotonDoReset(int deviceId);
PHOTON_RESULT PhotonGetFPATemp(int deviceId, PHOTON_FPA_TEMP_MODE mode, short* temp);
PHOTON_RESULT PhotonGetRevision(int deviceId, long* swVersion, long* fwVersion);
PHOTON_RESULT PhotonGetOptions(int deviceId, PHOTON_OPTIONS* options);
PHOTON_RESULT PhotonRestoreFactoryDefaults(int deviceId);
PHOTON_RESULT PhotonGetSerialNum(int deviceId, long* serialNum);
PHOTON_RESULT PhotonSetPowerUpDefaults(int deviceId);
PHOTON_RESULT PhotonGetPartNumber(int deviceId, char* partNumber);
PHOTON_RESULT PhotonDoFFC(int deviceId);
PHOTON_RESULT PhotonGetFFCMeanValue(int deviceId, short* value);
PHOTON_RESULT PhotonSetFFCMeanValue(int deviceId, short value);
PHOTON_RESULT PhotonGetFFCMode(int deviceId, PHOTON_FFC_MODE* ffcMode);
PHOTON_RESULT PhotonSetFFCMode(int deviceId, PHOTON_FFC_MODE ffcMode);
PHOTON_RESULT PhotonGetFFCPeriod(int deviceId, short* ffcPeriod);
PHOTON_RESULT PhotonSetFFCPeriod(int deviceId, short ffcPeriod);
PHOTON_RESULT PhotonGetFFCTempDelta(int deviceId, PHOTON_TEMP* ffcTempDelta);
PHOTON_RESULT PhotonSetFFCTempDelta(int deviceId, PHOTON_TEMP ffcTempDelta);
PHOTON_RESULT PhotonGetFFCWarnTime(int deviceId, short* time);
PHOTON_RESULT PhotonSetFFCWarnTime(int deviceId, short time);
PHOTON_RESULT PhotonGetShutterPosition(int deviceId, PHOTON_SHUTTER_POSITION* position);
PHOTON_RESULT PhotonSetShutterPosition(int deviceId, PHOTON_SHUTTER_POSITION position);
PHOTON_RESULT PhotonGetIsothermMode(int deviceId, PHOTON_ISOTHERM_MODE* mode);
PHOTON_RESULT PhotonSetIsothermMode(int deviceId, PHOTON_ISOTHERM_MODE mode);
PHOTON_RESULT PhotonGetIsothermThresholds(int deviceId, PHOTON_ISOTHERM_THRESHOLD_TYPE* isoType, short* lowerThreshold, short* upperThreshold);
PHOTON_RESULT PhotonSetIsothermThresholds(int deviceId, PHOTON_ISOTHERM_THRESHOLD_TYPE isoType, short lowerThreshold, short upperThreshold);
PHOTON_RESULT PhotonGetThreeIsothermThresholds(int deviceId, PHOTON_ISOTHERM_THRESHOLD_TYPE* isoType, short* lowerThreshold, short* midThreshold, short* upperThreshold);
PHOTON_RESULT PhotonSetThreeIsothermThresholds(int deviceId, PHOTON_ISOTHERM_THRESHOLD_TYPE isoType, short lowerThreshold, short midThreshold, short upperThreshold);
PHOTON_RESULT PhotonGetGainMode(int deviceId, PHOTON_GAIN_MODE* gainMode);
PHOTON_RESULT PhotonSetGainMode(int deviceId, PHOTON_GAIN_MODE gainMode);
PHOTON_RESULT PhotonGetSpotTemp(int deviceId, PHOTON_TEMP* temp);
PHOTON_RESULT PhotonGetSpotDisplay(int deviceId, PHOTON_SPOT_DISPLAY* display);
PHOTON_RESULT PhotonSetSpotDisplay(int deviceId, PHOTON_SPOT_DISPLAY display);
PHOTON_RESULT PhotonGetSpotMeterMode(int deviceId, PHOTON_SPOT_METER_MODE* mode);
PHOTON_RESULT PhotonSetSpotMeterMode(int deviceId, PHOTON_SPOT_METER_MODE mode);
PHOTON_RESULT PhotonGetDigitalOut(int deviceId, PHOTON_DIGITAL_OUT* digitalOutput);
PHOTON_RESULT PhotonSetDigitalOut(int deviceId, PHOTON_DIGITAL_OUT digitalOutput);
PHOTON_RESULT PhotonGetSyncMode(int deviceId, PHOTON_EXT_SYNC_MODE* mode);
PHOTON_RESULT PhotonSetSyncMode(int deviceId, PHOTON_EXT_SYNC_MODE mode);
PHOTON_RESULT PhotonGetTestPattern(int deviceId, PHOTON_TEST_PATTERN* pattern);
PHOTON_RESULT PhotonSetTestPattern(int deviceId, PHOTON_TEST_PATTERN pattern);
PHOTON_RESULT PhotonGetOrientation(int deviceId, PHOTON_IMAGE_ORIENTATION* imageOrientation);
PHOTON_RESULT PhotonSetOrientation(int deviceId, PHOTON_IMAGE_ORIENTATION imageOrientation);
PHOTON_RESULT PhotonGetPanTilt(int deviceId, short* x, short* y);
PHOTON_RESULT PhotonSetPanTilt(int deviceId, short x, short y);
PHOTON_RESULT PhotonGetVideoLUT(int deviceId, PHOTON_COLOR_LUT* lut);
PHOTON_RESULT PhotonSetVideoLUT(int deviceId, PHOTON_COLOR_LUT lut);
PHOTON_RESULT PhotonGetVideoMode(int deviceId, PHOTON_VIDEO_MODE* videoMode);
PHOTON_RESULT PhotonSetVideoMode(int deviceId, PHOTON_VIDEO_MODE videoMode);
PHOTON_RESULT PhotonGetDDEGain(int deviceId, short* gain);
PHOTON_RESULT PhotonSetDDEGain(int deviceId, short gain);
PHOTON_RESULT PhotonGetDDEThreshold(int deviceId, short* threshold);
PHOTON_RESULT PhotonSetDDEThreshold(int deviceId, short threshold);
PHOTON_RESULT PhotonGetDDESpatialThreshold(int deviceId, short* threshold);
PHOTON_RESULT PhotonSetDDESpatialThreshold(int deviceId, short threshold);
PHOTON_RESULT PhotonSetParams(int deviceID, int functionId, int byteCount, short *buffer);

PHOTON_RESULT PhotonGetVideoStandard(int deviceId, PHOTON_VIDEO_STANDARD* standard);
PHOTON_RESULT PhotonSetVideoStandard(int deviceId, PHOTON_VIDEO_STANDARD standard);
PHOTON_RESULT PhotonGetVideoColor(int deviceId, PHOTON_VIDEO_COLOR* color);
PHOTON_RESULT PhotonSetVideoColor(int deviceId, PHOTON_VIDEO_COLOR color);
PHOTON_RESULT PhotonGetAnalogVideoOnOff(int deviceId, PHOTON_VIDEO_MODE *mode);
PHOTON_RESULT PhotonSetAnalogVideoOnOff(int deviceId, PHOTON_VIDEO_MODE mode);
PHOTON_RESULT PhotonSetZoomMode(int deviceId, PHOTON_VIDEO_MODE videoMode);
PHOTON_RESULT PhotonGetZoomMode(int deviceId, PHOTON_VIDEO_MODE *videoMode);
PHOTON_RESULT PhotonSetFreezeMode(int deviceId, PHOTON_VIDEO_MODE mode);
PHOTON_RESULT PhotonGetFreezeMode(int deviceId, PHOTON_VIDEO_MODE *mode);
PHOTON_RESULT PhotonGetVideoModeNew(int deviceId, PHOTON_VIDEO_MODE* videoMode);
PHOTON_RESULT PhotonSetVideoModeNew(int deviceId, PHOTON_VIDEO_MODE videoMode);
PHOTON_RESULT PhotonGetExtOffsetState(int deviceId, PHOTON_OFFSETSTATE* state);
PHOTON_RESULT PhotonSetExtOffsetState(int deviceId, PHOTON_OFFSETSTATE state);
PHOTON_RESULT PhotonCaptureFrames(int deviceID, short captureBuffer);
PHOTON_RESULT PhotonCalcSupplementalOffset(int deviceID);
PHOTON_RESULT PhotonWriteSupplementalOffset(int deviceID);
PHOTON_RESULT PhotonGetParams(int deviceID, int functionId, int byteCount, short *buffer);
PHOTON_RESULT PhotonGetFFCTempDeltas(int deviceId, PHOTON_TEMP* ffcTempDelta, PHOTON_TEMP* ffcTempDeltaLoGain);
PHOTON_RESULT PhotonSetFFCTempDeltas(int deviceId, PHOTON_TEMP ffcTempDelta, PHOTON_TEMP ffcTempDeltaLoGain);
PHOTON_RESULT PhotonGetFFCPeriods(int deviceId, short* ffcPeriod, short *ffcPeriodLowGain);
PHOTON_RESULT PhotonSetFFCPeriods(int deviceId, short ffcPeriod, short ffcPeriodLowGain);
PHOTON_RESULT PhotonGetFPAExtents(int deviceId,short *fpaColumnExtent,short *fpaRowExtent, short *fpaBlindRowExtent);
PHOTON_RESULT PhotonSetParamsWithTimeout(int deviceID, int functionId, int byteCount, short *buffer, short timeout);
PHOTON_RESULT PhotonGetParamsWithTimeout(int deviceID, int functionId, int byteCount, short *buffer, short timeout);
PHOTON_RESULT PhotonSetBasketBoardCommDestId(CAL_DESTID destinationId);
PHOTON_RESULT PhotonGetBasketBoardCommDestId(CAL_DESTID *destinationId);
PHOTON_RESULT PhotonSetBasketBoardSubSlotId(int subSlotId);
PHOTON_RESULT PhotonGetBasketBoardSubSlotId(int *subSlotId);
PHOTON_RESULT PhotonSetComTimeout(int timeoutInMsec);
PHOTON_RESULT PhotonGetComTimeout(int *timeoutInMsec);
PHOTON_RESULT PhotonSetComRetries(int NumOfRetries);
PHOTON_RESULT PhotonGetComRetries(int *NumOfRetries);


#ifdef __cplusplus
}
#endif

#endif

