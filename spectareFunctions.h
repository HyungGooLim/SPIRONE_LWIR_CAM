#ifndef _SPECTAREFUNCTIONS_H_
#define _SPECTAREFUNCTIONS_H_
#ifdef __cplusplus
extern "C" 
{
#else
    #include "photondefs.h"    
#endif


PHOTON_RESULT SpectareGetIntegrationTime(int deviceId, float* intTimeMS);
PHOTON_RESULT SpectareSetIntegrationTime(int deviceId, float intTimeMS);
PHOTON_RESULT SpectareGetFrameRate(int deviceId, float* frameRateHz);
PHOTON_RESULT SpectareSetFrameRate(int deviceId, float frameRateHz);
PHOTON_RESULT SpectareSetDACVoltage(int deviceId, int channel, int valuemV);
PHOTON_RESULT SpectareGetElapsedTime(int deviceId, int* timeSec);
PHOTON_RESULT SpectareCalculateGain(int deviceId);
PHOTON_RESULT SpectareGetIntegrationMode(int deviceId, int *intMode);
PHOTON_RESULT SpectareSetIntegrationMode(int deviceId, int intMode);
PHOTON_RESULT SpectareCaptureFrames(int deviceId, short captureBuffer);
PHOTON_RESULT SpectareGetCalStatus(int deviceId, short *status);
PHOTON_RESULT SpectareGetCorrectionMask(int deviceId, short *correctionMask);
PHOTON_RESULT SpectareSetCorrectionMask(int deviceId, short correctionMask);
PHOTON_RESULT SpectareGetCoolerTemp(int deviceId, double* tempInKelvin);
PHOTON_RESULT SpectareGetLensRevision(int deviceId, char *buffer);
PHOTON_RESULT SpectareGetLensPosition(int deviceId, short *zoomPosition, short *focusPosition, short *movementMode);
PHOTON_RESULT SpectareSetLensPosition(int deviceId, short zoomPosition, short focusPosition, short movementMode);
PHOTON_RESULT SpectareGetLensUptimeHours(int deviceId, short *upTimeHours);
PHOTON_RESULT SpectareGetLensStatus(int deviceId, short *status);
PHOTON_RESULT SpectareGetLensCurrentFOV(int deviceId, short *fovIndex);
PHOTON_RESULT SpectareSetLensBitRequest(int deviceId);
PHOTON_RESULT SpectareGetLensBitStatus(int deviceId, short *status);
PHOTON_RESULT SpectareSetLensFOVIndex(int deviceId, short fov, short infinityFlag);
PHOTON_RESULT SpectareLensStartZoomIn(int deviceId);
PHOTON_RESULT SpectareLensStartZoomOut(int deviceId);
PHOTON_RESULT SpectareLensStopZoom(int deviceId);
PHOTON_RESULT SpectareLensStartFocusIn(int deviceId);
PHOTON_RESULT SpectareLensStartFocusOut(int deviceId);
PHOTON_RESULT SpectareLensStopFocus(int deviceId);
PHOTON_RESULT SpectareGetLensTemperature(int deviceId, short *lensTemp);
PHOTON_RESULT SpectareGetMaxPixelLimit(int deviceId, short *maxPixelLimit);
PHOTON_RESULT SpectareGetMinPixelLimit(int deviceId, short *minPixelLimit);
PHOTON_RESULT SpectareSetMaxPixelLimit(int deviceId, short maxPixelLimit);
PHOTON_RESULT SpectareSetMinPixelLimit(int deviceId, short minPixelLimit);
PHOTON_RESULT SpectareGetMaxPixelGain(int deviceId, short *maxPixelGain);
PHOTON_RESULT SpectareSetMaxPixelGain(int deviceId, short maxPixelGain);
PHOTON_RESULT SpectareGetMinPixelGain(int deviceId, short *minPixelGain);
PHOTON_RESULT SpectareSetMinPixelGain(int deviceId, short minPixelGain);
PHOTON_RESULT SpectareGetBadPixelResults(int deviceId, int *badRange,  int *badGain);
PHOTON_RESULT SpectareGetSceneMeanIntensity(int deviceId, short *meanIntensity);
PHOTON_RESULT SpectareGetAutoFocusEnable(int deviceId, short *autoFocusEnable);
PHOTON_RESULT SpectareGetAutoFocusROI(int deviceId, short *autoFocusRoi);
PHOTON_RESULT SpectareGetAutoFocusMetricResult(int deviceId, unsigned long *autoFocusMetricResult);
PHOTON_RESULT SpectareGetAutoFocusMetricThreshold(int deviceId, unsigned long *autoFocusMetricThreshold);
PHOTON_RESULT SpectareSetAutoFocusEnable(int deviceId, short autoFocusEnable);
PHOTON_RESULT SpectareSetAutoFocusROI(int deviceId, short autoFocusRoi);
PHOTON_RESULT SpectareSetAutoFocusMetricThreshold(int deviceId, unsigned long autoFocusMetricThreshold);
PHOTON_RESULT SpectareGetAutoFocusBumpAmount(int deviceId, short *autoFocusBumpAmount);
PHOTON_RESULT SpectareSetAutoFocusBumpAmount(int deviceId, short autoFocusBumpAmount);
PHOTON_RESULT SpectareGetLensExtents(int deviceId,short *zoomLensMinExtent,short *zoomLensMaxExtent,short *focusLensMinExtent,short *focusLensMaxExtent);
PHOTON_RESULT SpectareGetFPAExtents(int deviceId,short *fpaColumnExtent,short *fpaRowExtent);
PHOTON_RESULT SpectareGetActiveNuc(int deviceId,short *activeNuc);
PHOTON_RESULT SpectareSetActiveNuc(int deviceId,short activeNuc);
PHOTON_RESULT SpectareGetPixelGain(int deviceId,short row, short col, short *gain);
PHOTON_RESULT SpectareSetPixelGain(int deviceId,short row, short col, short gain, short badPixelStatus);

#ifdef __cplusplus
}
#endif

#endif
