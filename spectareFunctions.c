#include "photoncomm.h"
#include "lensdefs.h"
#include "CooledCoreControlDefs.h"
#include "spectareFunctions.h"
#include "proto.h"

/*
 *-------------------------------------------------
 *HRC Functions
 *-------------------------------------------------
 */
/*!
 *@defgroup hrc HRC Functions
 *  HRC related functions.
 *  @{
 */


/*!
  * Gets the integration time.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] intTimeMS: Integration time value (milliseconds)
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareSetIntegrationTime()
  */
PHOTON_RESULT SpectareGetIntegrationTime(int deviceId, float* intTimeMS)
{
   short param[4] = {0,0,0,0};
   unsigned int result = 0;
   unsigned int value = 0;
   result = CamGetParams(deviceId, SET_INT_TIME, 4, param);

   if( result == 8 )
   {
      value = (param[0] & 0xff) | (param[1] << 8) | (param[2] << 16) | (param[3] << 24);
      *intTimeMS = (float)value * (float)190.1244 / (float)1000000.0;
      return(CAM_OK);
   }
   else
      return(CAM_UNDEFINED_ERROR_CODE);
}


/*!
  * Sets the integration time.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] intTimeMS: Integration time value (milliseconds)
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareGetIntegrationTime()
  */
PHOTON_RESULT SpectareSetIntegrationTime(int deviceId, float intTimeMS)
{
   short value[4] = {0,0,0,0};
   float fTicks = 0;
   unsigned int uiTicks = 0;

   // Convert ms to ticks 190.2144 ns / tick
   fTicks = intTimeMS * (float)1000000.0 / (float)190.1244;
   uiTicks = (unsigned int)fTicks;

   value[0] =  uiTicks & 0xff;
   value[1] = (uiTicks >> 8) & 0xff;
   value[2] = (uiTicks >> 16) & 0xff;
   value[3] = (uiTicks >> 24) & 0xff;

   return(CamSetParams(deviceId, SET_INT_TIME, 4, value));
}

/*!
  * Gets the camera frame rate in Hz.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] frameRateHz: Frame rate Hz
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareSetFrameRate()
  */
PHOTON_RESULT SpectareGetFrameRate(int deviceId, float* frameRateHz)
{
   short param[2] = {0,0};
   unsigned int result = 0;
   unsigned int value = 0;
   result = CamGetParams(deviceId, SET_FRAME_RATE, 2, param);
   if( result == 4 )
   {
      value = (param[0] & 0xffff) | (param[1] << 16) ;
      *frameRateHz = 1 / ((float)value * (float)1.901244e-7);  /*convert to Hz*/;
      return(CAM_OK);
   }
   else
      return(CAM_UNDEFINED_ERROR_CODE);
}


/*!
  * Sets the camera frame rate in Hz.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] frameRateHz: Frame rate Hz
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareGetFrameRate()
  */
PHOTON_RESULT SpectareSetFrameRate(int deviceId, float frameRateHz)
{
   short value[2] = {0,0};
   float fTicks = 0;
   unsigned int uiTicks = 0;

   // Convert Hz to ticks 190.1244 ns / tick  1/(1.901244e-7 = 5259714.16609335
   fTicks = 1/((float)frameRateHz * (float)1.901244e-7);
   uiTicks = (unsigned int)fTicks;

   value[0] =  uiTicks & 0xffff;			/* LSW */
   value[1] = (uiTicks >> 16) & 0xffff;		/* MSW */

   return(CamSetParams(deviceId, SET_FRAME_RATE, 2, value));
}

/*!
  * Sets camera DAC voltage in millivolts
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] channel: DAC channel id
  * @param[in] valuemV: DAC input value in millivolts
  * @return >= CAM_OK if successful or an error codes in case of an error
  */
PHOTON_RESULT SpectareSetDACVoltage(int deviceId, int channel, int valuemV)
{
   short value[4] = {0,0,0,0};
   value[0] = (short)valuemV * 2; // Scale Vout by Vref/Sull Scale = 4096/2048

   if( channel > 0 )
   {
      value[0] = value[0] | 0x3000;
   }

   return(CamSetParams(deviceId, R_EXTERNAL, 1, value));
}

/*!
  * Gets the camera elapsed up time in seconds.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] timeSec: Elapsed time in seconds
  * @return >= CAM_OK if successful or an error codes in case of an error
  */
PHOTON_RESULT SpectareGetElapsedTime(int deviceId, int* timeSec)
{
   short param[4] = {0,0,0,0};
   unsigned int result = 0;
   result = CamSetParams(deviceId, SET_FRAME_RATE, 1, param);
   *timeSec = (param[0] & 0xffff) | (param[1] << 16);
   return(CAM_OK);
}

/*!
  * Commands the camera to perform a calculate gain function.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error
  */
PHOTON_RESULT SpectareCalculateGain(int deviceId)
{
   PHOTON_RESULT result;
   short param;
   result = CamSetParams(deviceId, CALC_GAIN, 0, &param);
   return(result);
}

/*!
  * Gets the camera integration mode
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] intMode: Camera integration mode.  Valid integrations modes are one of the following:\n
  \verbatim      
    VARIABLE_FRAME_RATE_ATFR   = 0,
    FIXED_VIDEO_RATE_ATFR      = 1,    NTSC/PAL frame rate
    EXTERNAL_SYNC_ATFR         = 3,
    EXTERNAL_SYNC_AIWR         = 7,
  \endverbatim
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareSetIntegrationMode()
  */
PHOTON_RESULT SpectareGetIntegrationMode(int deviceId, int *intMode)
{
   short param;
   unsigned int result = 0;
   unsigned int value = 0;
   result = CamGetParams(deviceId, SET_INTEGRATION_MODE, 1, &param);
   *intMode = param;
   return(CAM_OK);
}

/*!
  * Sets the camera integration mode
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] intMode: Camera integration mode.  Valid integrations modes are one of the following:\n
  \verbatim      
    VARIABLE_FRAME_RATE_ATFR   = 0,
    FIXED_VIDEO_RATE_ATFR      = 1,    NTSC/PAL frame rate
    EXTERNAL_SYNC_ATFR         = 3,
    EXTERNAL_SYNC_AIWR         = 7,
  \endverbatim
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareGetIntegrationMode()
  */
PHOTON_RESULT SpectareSetIntegrationMode(int deviceId, int intMode)
{
   PHOTON_RESULT result;
   if( intMode >= 0 && intMode <= 7 )
   {
      result = CamSetParams(deviceId, SET_INTEGRATION_MODE, 1, (short*)&intMode);
      return(result);
   }
   return(CAM_RANGE_ERROR);
}

/*!
  * Gets the camera calibration process status
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] status: Calibration process status.   0 = Complete otherwise BUSY.  
  * Other values imply process is active.
  * @return >= CAM_OK if successful or an error codes in case of an error

  */
PHOTON_RESULT SpectareGetCalStatus(int deviceId, short *status)
{
#if 0
   PHOTON_RESULT result = CamGetParams(deviceId, TRANSFER_FRAME, 1, status);
   return(result);
#endif
   PHOTON_RESULT result = 0;
   short value[2] = {0,0,};

   value[0] = COOLED_CORE_GET_CAL_STATUS;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 2 )
   {
      *status = value[0];
   }

   return(result);

}

/*!
  * Gets the camera correction mask which is defined by the following enum:\n
  *\verbatim
     OFFSET_CORRECTION_MASK      =   1,
     GAIN_CORRECTION_MASK        =   2,
     LAGRANGE_CORRECTION_MASK    =   4,
     PIXEL_REPLACE_MASK          =   8,
     NOISE_FILTER_MASK           =   16,
     COLUMN_CORRECTION_MASK      =   32,
     EXTFFC_OFFSET_MASK          =   64,
   \endverbatim
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] correctionMask: Camera correction mask (FFC, Gain, Bad Pixel Replace, and Noise Filter)
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareSetCorrectionMask()
  */
PHOTON_RESULT SpectareGetCorrectionMask(int deviceId, short *correctionMask)
{
   PHOTON_RESULT result = CamGetParams(deviceId, CORRECTION_MASK, 1, correctionMask);
   return(result);
}

/*!
  * Sets the camera correction mask which is defined by the following enum:\n
  *\verbatim
     OFFSET_CORRECTION_MASK      =   1,
     GAIN_CORRECTION_MASK        =   2,
     LAGRANGE_CORRECTION_MASK    =   4,
     PIXEL_REPLACE_MASK          =   8,
     NOISE_FILTER_MASK           =   16,
     COLUMN_CORRECTION_MASK      =   32,
     EXTFFC_OFFSET_MASK          =   64,
   \endverbatim
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] correctionMask: Camera correction mask (FFC, Gain, Bad Pixel Replace, and Noise Filter)
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareGetCorrectionMask()
  */
PHOTON_RESULT SpectareSetCorrectionMask(int deviceId, short correctionMask)
{
   PHOTON_RESULT result = CamSetParams(deviceId, CORRECTION_MASK, 1, &correctionMask);
   return(result);
}

/*!
  * Gets the camera cooler temperature
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] tempInKelvin: Cooler temperature in degrees Kelvin
  * @return >= CAM_OK if successful or an error codes in case of an error
  */
PHOTON_RESULT SpectareGetCoolerTemp(int deviceId, double* tempInKelvin)
{
   PHOTON_RESULT result;
   short param = 1;
   result = CamSetParams(deviceId, READ_SENSOR, 1, &param);
   // Scaling is 610 uV per LSB (0.000610 * 672.3 = 0.410103)
   // T = -672.3V + 787.8
   *tempInKelvin = 787.80000 - ((double)param * 0.410103);
   // Limit to 10K
   if( *tempInKelvin < 10.000 )
      *tempInKelvin = 10.000;
   //*tempInKelvin = (double)param;
   return(result);
}

/*!
  * Gets the camera lens version
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] buffer: Buffer to contain the version string.  Maximum 16 bytes total.
  * @return >= CAM_OK if successful or an error codes in case of an error

  */
PHOTON_RESULT SpectareGetLensRevision(int deviceId, char *buffer)
{
   PHOTON_RESULT result = 0;
   short value[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   value[0] = LENS_GET_VERSION;

   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);
   strcpy(buffer, (char *)value);

   return(result);
}

/*!
  * Gets the camera lens zoom and focus position
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] zoomPosition: Lens zoom position in counts.  Range is returned by SpectareGetLensExtents()
  * @param[out] focusPosition: Lens focus position in counts. Range is returned by SpectareGetLensExtents()
  * @param[out] movementMode: Lens focus movement mode. 1 = Manual Focus Mode, 2 = Go to position mode.
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareSetLensPosition() and SpectareGetLensExtents()
  */
PHOTON_RESULT SpectareGetLensPosition(int deviceId, short *zoomPosition, short *focusPosition, short *movementMode)
{
   PHOTON_RESULT result = 0;
   short value[4] = {0,0,0,0};
   value[0] = LENS_GET_POSITION;

   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);

   if( result >= 6 )
   {
      *zoomPosition = value[0];
      *focusPosition = value[1];
      *movementMode = value[2];
   }

   return(result);
}

/*!
  * Sets the camera lens zoom and focus position and focus movement mode
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] zoomPosition: Lens zoom position in counts.  Range is returned by SpectareGetLensExtents()
  * @param[in] focusPosition: Lens focus position in counts. Range is returned by SpectareGetLensExtents()
  * @param[in] movementMode: Lens focus movement mode. 1 = Manual Focus Mode, 2 = Go to position mode.
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareGetLensPosition() and SpectareGetLensExtents()
  */
PHOTON_RESULT SpectareSetLensPosition(int deviceId, short zoomPosition, short focusPosition, short movementMode)
{
   PHOTON_RESULT result = 0;
   short value[4] = {0,0,0,0};
   value[0] = LENS_SET_POSITION;
   value[1] = zoomPosition;
   value[2] = focusPosition;
   value[3] = movementMode;

   result = CamSetParams(deviceId, LENS_CONTROL, 4, value);

   return(result);
}

/*!
  * Gets the camera lens uptime
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] upTimeHours: Total Lens powered uptime in 1/2 hour units.
  * @return >= CAM_OK if successful or an error codes in case of an error

  */
PHOTON_RESULT SpectareGetLensUptimeHours(int deviceId, short *upTimeHours)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = LENS_GET_UPTIME;

   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);

   if( result > 0 )
   {
      *upTimeHours = value[0];
   }

   return(result);
}

/*!
  * Gets the camera lens status
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] status: Current Lens status.  Status is contained in bit-fields of 1-byte:\n
  \verbatim
    Bit 0     0 = Not Moving.                        1 = Is Moving
    Bit 1     0 = BIT not active.                    1 = BIT in process
    Bit 2     0 = Not in NUC position                1 = Is in NUC position
    Bit 3     0 = Not in Auto Focus Correct mode.    1 = Is in Auto Focus Correct mode.
    Bit 4     0 = Not in Thermal Error.              1 = Is in Thermal Error
  \endverbatim
  * @return >= CAM_OK if successful or an error codes in case of an errorCalibration process status 2 = complete

  */
PHOTON_RESULT SpectareGetLensStatus(int deviceId, short *status)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = LENS_GET_STATUS;

   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);

   if( result > 0 )
   {
      *status = value[0];
   }

   return(result);
}

/*!
  * Gets the camera lens current FOV
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] fovIndex: Current lens Field Of View index. \n
  * Range is 0 - 5.  \n
  * 0 = Not in an index FOV position.
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareSetLensFOVIndex()
  */
PHOTON_RESULT SpectareGetLensCurrentFOV(int deviceId, short *fovIndex)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = LENS_GET_CURRENT_FOV;

   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);

   if( result > 0 )
   {
      *fovIndex = value[0];
   }

   return(result);
}

/*!
  * Request the camera lens to perform it's Built-In Tests (BIT)
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error.

@sa SpectareGetLensBitStatus()
  */
PHOTON_RESULT SpectareSetLensBitRequest(int deviceId)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = LENS_SET_BIT_REQUEST;
   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);
   return(result);
}

/*!
  * Gets the camera lens BIT status
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] status: Camera lens BIT status defined by the following enum:\n
\verbatim
  OK                    =  0,
  BUSY                  =  1,
  THERMAL ERROR         =  2, 
  MOTORS SWITCHED       =  3, 
  ZOOM STUCK or NO OPTO =  4, 
  ZOOM LENS SLIP        =  5, 
  ZOOM LENS STUCK       =  6, 
  FOCUS LENS SLIP       =  7, 
  FOCUS LENS STUCK      =  8, 
  BIT ERROR             =  9, 
\endverbatim
 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareSetLensBitRequest()
  */
PHOTON_RESULT SpectareGetLensBitStatus(int deviceId, short *status)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = LENS_GET_BIT_STATUS;

   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);

   if( result > 0 )
   {
      *status = value[0];
   }

   return(result);
}

/*!
  * Sets the camera lens FOV index
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] fov: FOV index.  Range is 1 to 5.
  * @param[in] infinityFlag: Sets the focus to inifinite flag.  0 = Normal.  1 = Set to focus to infinite.
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareGetLensCurrentFOV()
  */
PHOTON_RESULT SpectareSetLensFOVIndex(int deviceId, short fov, short infinityFlag)
{
   PHOTON_RESULT result = 0;
   short value[4] = {0,0,0,0};
   value[0] = LENS_SET_FOV_INFINITY_POSITION;
   value[1] = fov;
   value[2] = infinityFlag;

   result = CamSetParams(deviceId, LENS_CONTROL, 3, value);

   return(result);
}

/*!
  * Commands the camera zoom lens to start moving inward.  Lens will continue to 
  * move until a stop command is issued or it reaches the end position.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareLensStopZoom()
  */
PHOTON_RESULT SpectareLensStartZoomIn(int deviceId)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = LENS_ZOOM_START_MOVING_IN;

   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);
   return(result);
}

/*!
  * Commands the camera zoom lens to start moving outward.  Lens will continue to 
  * move until a stop command is issued or it reaches the end position.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareLensStopZoom()
  */
PHOTON_RESULT SpectareLensStartZoomOut(int deviceId)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = LENS_ZOOM_START_MOVING_OUT;
   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);
   return(result);
}

/*!
  * Commands the camera zoom lens to stop moving.  
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareLensStartZoomIn() and SpectareLensStartZoomOut()
  */
PHOTON_RESULT SpectareLensStopZoom(int deviceId)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = LENS_ZOOM_STOP_MOVING;
   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);
   return(result);
}

/*!
  * Commands the camera focus lens to start moving inward.  Lens will continue to 
  * move until a stop command is issued or it reaches the end position.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareLensStopFocus()
  */
PHOTON_RESULT SpectareLensStartFocusIn(int deviceId)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = LENS_FOCUS_START_MOVING_IN;
   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);
   return(result);
}

/*!
  * Commands the camera focus lens to start moving outward.  Lens will continue to 
  * move until a stop command is issued or it reaches the end position.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareLensStopFocus()
  */
PHOTON_RESULT SpectareLensStartFocusOut(int deviceId)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = LENS_FOCUS_START_MOVING_OUT;
   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);
   return(result);
}

/*!
  * Commands the camera focus lens to stop moving.  
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SpectareLensStartFocusIn() and SpectareLensStartFocusOut()
  */
PHOTON_RESULT SpectareLensStopFocus(int deviceId)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = LENS_FOCUS_STOP_MOVING;
   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);
   return(result);
}

/*!
  * Gets the camera lens temperature
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] lensTemp: Lens temperature in degrees C.  Range is -127 to +128
  * @return >= CAM_OK if successful or an error codes in case of an error
  */
PHOTON_RESULT SpectareGetLensTemperature(int deviceId, short *lensTemp)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = LENS_GET_TEMPERATURE;

   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);

   if( result > 0 )
   {
      *lensTemp = value[0];
   }

   return(result);
}

/*!
  * Gets the NUC bad pixel criterion for maximum allowed pixel value 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] maxPixelLimit: Pixel value.  Range is 0 to 16383.
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareSetMaxPixelLimit()
  */
PHOTON_RESULT SpectareGetMaxPixelLimit(int deviceId, short *maxPixelLimit)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_GET_MAX_PIXEL_VALUE_LIMIT;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 2 )
   {
      *maxPixelLimit = value[0];
   }

   return(result);
}

/*!
  * Gets the NUC bad pixel criterion for minimum allowed pixel value 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] minPixelLimit: Pixel value.  Range is 0 to 16383.
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareSetMinPixelLimit()
  */
PHOTON_RESULT SpectareGetMinPixelLimit(int deviceId, short *minPixelLimit)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_GET_MIN_PIXEL_VALUE_LIMIT;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 2 )
   {
      *minPixelLimit = value[0];
   }

   return(result);
}

/*!
  * Sets the NUC bad pixel criterion for maximum allowed pixel value 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] maxPixelLimit: Pixel value.  Range is 0 to 16383.
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareGetMaxPixelLimit()
  */
PHOTON_RESULT SpectareSetMaxPixelLimit(int deviceId, short maxPixelLimit)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_SET_MAX_PIXEL_VALUE_LIMIT;
   value[1] = maxPixelLimit;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 2, value);

   return(result);
}

/*!
  * Sets the NUC bad pixel criterion for minimum allowed pixel value 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] minPixelLimit: Pixel value.  Range is 0 to 16383.
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareGetMinPixelLimit()
  */
PHOTON_RESULT SpectareSetMinPixelLimit(int deviceId, short minPixelLimit)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_SET_MIN_PIXEL_VALUE_LIMIT;
   value[1] = minPixelLimit;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 2, value);

   return(result);
}

/*!
  * Gets the NUC bad pixel criterion for maximum allowed pixel gain value 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] maxPixelGain: Pixel gain value.  Range is 0 to 200.
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareSetMaxPixelGain()
  */
PHOTON_RESULT SpectareGetMaxPixelGain(int deviceId, short *maxPixelGain)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_GET_MAX_PIXEL_GAIN_LIMIT;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 2 )
   {
      *maxPixelGain = value[0];
   }

   return(result);
}

/*!
  * Sets the NUC bad pixel criterion for maximum allowed pixel gain value 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] maxPixelGain: Pixel gain value.  Range is 0 to 200.
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareGetMaxPixelGain()
  */
PHOTON_RESULT SpectareSetMaxPixelGain(int deviceId, short maxPixelGain)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_SET_MAX_PIXEL_GAIN_LIMIT;
   value[1] = maxPixelGain;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 2, value);

   return(result);
}

/*!
  * Gets the NUC bad pixel criterion for minimum allowed pixel gain value 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] minPixelGain: Pixel gain value.  Range is 0 to 200.
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareSetMinPixelGain()
  */
PHOTON_RESULT SpectareGetMinPixelGain(int deviceId, short *minPixelGain)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_GET_MIN_PIXEL_GAIN_LIMIT;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 2 )
   {
      *minPixelGain = value[0];
   }

   return(result);
}

/*!
  * Sets the NUC bad pixel criterion for minimum allowed pixel gain value 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] minPixelGain: Pixel gain value.  Range is 0 to 200.
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareGetMinPixelGain()
  */
PHOTON_RESULT SpectareSetMinPixelGain(int deviceId, short minPixelGain)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_SET_MIN_PIXEL_GAIN_LIMIT;
   value[1] = minPixelGain;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 2, value);

   return(result);
}


/*!
  * Gets the NUC bad pixel detection results. 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] badRange: Number of pixels that exceeded the minimum and maximum pixel values.
  * @param[out] badGain: Number of pixels that exceeded the minimum and maximum pixel gain values.
  * @return >= CAM_OK if successful or an error codes in case of an error

  */
PHOTON_RESULT SpectareGetBadPixelResults(int deviceId, int *badRange,  int *badGain)
{
   PHOTON_RESULT result = 0;
   short value[4] = {0,0,0,0};
   short reverseEndienValue[4] = {0,0,0,0};
   value[0] = COOLED_CORE_GET_BAD_PIXEL_DETECTION_RESULTS;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 8 )
   {
	   reverseEndienValue[0] = value[1];
	   reverseEndienValue[1] = value[0];
	   reverseEndienValue[2] = value[3];
	   reverseEndienValue[3] = value[2];
      *badRange = *(int*)&reverseEndienValue[0];
      *badGain = *(int*)&reverseEndienValue[2];
   }

   return(result);
}


/*!
  * Gets the mean intensity of the current scene.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] sceneMeanIntensity:  Range os 0 to 16383.
  * @return >= CAM_OK if successful or an error codes in case of an error

  */
PHOTON_RESULT SpectareGetSceneMeanIntensity(int deviceId, short *sceneMeanIntensity)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_GET_SCENE_MEAN_INTENSITY;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 2 )
   {
      *sceneMeanIntensity = value[0];
   }

   return(result);
}

/*!
  * Gets the camera focus metric enable status.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] autoFocusEnable:  0 = Not enabled. 1 = Focus metric calculations enabled.
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareSetAutoFocusEnable()
  */
PHOTON_RESULT SpectareGetAutoFocusEnable(int deviceId, short *autoFocusEnable)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_GET_AUTO_FOCUS_ENABLE;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 2 )
   {
      *autoFocusEnable = value[0];
   }

   return(result);
}

/*!
  * Gets the camera focus metric Region Of Interest (ROI).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] autoFocusRoi:  A Centered region within which the focus metric is calculated.
  * Defined by the following enum:\n
  *\verbatim
     32x32          = 0,
     64x64          = 1,
     128x128        = 2,
     256x256        = 3,
  \endverbatim
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareSetAutoFocusROI()
  */
PHOTON_RESULT SpectareGetAutoFocusROI(int deviceId, short *autoFocusRoi)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_GET_AUTO_FOCUS_ROI;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 2 )
   {
      *autoFocusRoi = value[0];
   }

   return(result);
}

/*!
  * Gets the camera current focus metric result.  Larger values imply better focus.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] autoFocusMetricResult:  Metric values exceeding the specified threshold  
  * @return >= CAM_OK if successful or an error codes in case of an error

  */
PHOTON_RESULT SpectareGetAutoFocusMetricResult(int deviceId, unsigned long *autoFocusMetricResult)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0,};
   short reverseEndienValue[2] = {0,0,};
   value[0] = COOLED_CORE_GET_AUTO_FOCUS_METRIC_RESULT;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 4 )
   {
	   reverseEndienValue[0] = value[1];
	   reverseEndienValue[1] = value[0];
      *autoFocusMetricResult = *(unsigned long*)&reverseEndienValue[0];
   }
   return(result);
}

/*!
  * Gets the camera current focus metric threshold. 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] autoFocusMetricThreshold:  Specifies a threshold that focus metric values must exceed to be counted.  
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareSetAutoFocusMetricThreshold()
  */
PHOTON_RESULT SpectareGetAutoFocusMetricThreshold(int deviceId, unsigned long *autoFocusMetricThreshold)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0,};
   short reverseEndienValue[2] = {0,0,};
   value[0] = COOLED_CORE_GET_AUTO_FOCUS_METRIC_THRESHOLD;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 4 )
   {
	   reverseEndienValue[0] = value[1];
	   reverseEndienValue[1] = value[0];
      *autoFocusMetricThreshold = *(unsigned long*)&reverseEndienValue[0];
   }
   return(result);
}

/*!
  * Sets the camera focus metric enable state.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] autoFocusEnable:  0 = Not enabled. 1 = Focus metric calculations enabled.
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareGetAutoFocusEnable()
  */
PHOTON_RESULT SpectareSetAutoFocusEnable(int deviceId, short autoFocusEnable)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_SET_AUTO_FOCUS_ENABLE;
   value[1] = autoFocusEnable;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 2, value);

   return(result);
}

/*!
  * Sets the camera focus metric Region Of Interest (ROI).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] autoFocusRoi:  Region within which the focus metric is calculated.
  * Defined by the following enum:\n
  *\verbatim
     32x32          = 0,
     64x64          = 1,
     128x128        = 2,
     256x256        = 3,
  \endverbatim
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareGetAutoFocusROI()
  */
PHOTON_RESULT SpectareSetAutoFocusROI(int deviceId, short autoFocusRoi)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_SET_AUTO_FOCUS_ROI;
   value[1] = autoFocusRoi;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 2, value);

   return(result);
}

/*!
  * Sets the camera current focus metric threshold. 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] autoFocusMetricThreshold:  Specifies a threshold that focus metric values must exceed to be counted.  
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareGetAutoFocusMetricThreshold()
  */
PHOTON_RESULT SpectareSetAutoFocusMetricThreshold(int deviceId, unsigned long autoFocusMetricThreshold)
{
   PHOTON_RESULT result = 0;
   short value[4] = {0,0,0,0};

   value[0] = COOLED_CORE_SET_AUTO_FOCUS_METRIC_THRESHOLD;
   value[2] = (short)(autoFocusMetricThreshold & 0xFFFF);          /* LSB */
   value[1] = (short)((autoFocusMetricThreshold >> 16) & 0xFFFF);   /* MSB */

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 3, value);

   return(result);
}

/*!
  * Gets the camera lens focus bump amount. 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] autoFocusBumpAmount:  Specifies the amount in counts to move the focus lens
  * when the lens moves in bump mode.  
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareSetAutoFocusBumpAmount()
  */
PHOTON_RESULT SpectareGetAutoFocusBumpAmount(int deviceId, short *autoFocusBumpAmount)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0,};
   value[0] = COOLED_CORE_GET_AUTO_FOCUS_BUMP_AMOUNT;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 2 )
   {
      *autoFocusBumpAmount = value[0];
   }

   return(result);
}

/*!
  * Sets the camera lens focus bump amount. 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] autoFocusBumpAmount:  Specifies the amount in counts to move the focus lens
  * when the lens moves in bump mode.  
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareGetAutoFocusBumpAmount()
  */
PHOTON_RESULT SpectareSetAutoFocusBumpAmount(int deviceId, short autoFocusBumpAmount)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_SET_AUTO_FOCUS_BUMP_AMOUNT;
   value[1] = autoFocusBumpAmount;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 2, value);

   return(result);
}

/*!
  * Gets the camera lens motion minimum and maximum extents. 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] zoomLensMinExtent:  Specifies the range minimum for the zoom lens
  * @param[out] zoomLensMaxExtent:  Specifies the range maximum for the zoom lens
  * @param[out] focusLensMinExtent:  Specifies the range minimum for the focus lens
  * @param[out] focusLensMaxExtent:  Specifies the range maximum for the focus lens
  * @return >= CAM_OK if successful or an error codes in case of an error

  @sa SpectareGetLensPosition() and SpectareSetLensPosition()
  */
PHOTON_RESULT SpectareGetLensExtents(int deviceId,short *zoomLensMinExtent,short *zoomLensMaxExtent,short *focusLensMinExtent,short *focusLensMaxExtent)
{
   PHOTON_RESULT result = 0;
   short value[4] = {0,0,0,0,};
   value[0] = LENS_GET_LENS_EXTENTS;

   result = CamSetParams(deviceId, LENS_CONTROL, 1, value);

   if( result >= 8 )
   {
      *zoomLensMinExtent = value[0];
      *zoomLensMaxExtent = value[1];
      *focusLensMinExtent = value[2];
      *focusLensMaxExtent = value[3];
   }

   return(result);
}

/*!
  * Gets the camera FPA image maximum extents. Maximum number of rows and columns.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] fpaColumnExtent:  Specifies the total number of FPA image columns
  * @param[out] fpaRowExtent:  Specifies the total number of FPA image rows
  * @return >= CAM_OK if successful or an error codes in case of an error

  */
PHOTON_RESULT SpectareGetFPAExtents(int deviceId,short *fpaColumnExtent,short *fpaRowExtent)
{
   PHOTON_RESULT result = 0;

   short value[3] = {0,0,0};
   value[0] = DIGITAL_FPA_DIMENSIONS;

   result = CamSetParams(deviceId, DIGITAL_OUTPUT_MODE, 1, value);

   if( result >= 6 )
   {
      *fpaColumnExtent = value[0];
      *fpaRowExtent = value[1];
   }
   
   return(result);
}

/*!
  * Gets the currently active NUC table number.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] activeNuc:  Specifies the currently active NUC table number
  * @return >= CAM_OK if successful or an error codes in case of an error

  */
PHOTON_RESULT SpectareGetActiveNuc(int deviceId,short *activeNuc)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0,};

   value[0] = COOLED_CORE_GET_ACTIVE_NUC;
   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 1, value);

   if( result >= 2 )
   {
      *activeNuc = value[0];
   }

   return(result);
}

/*!
  * Selects the desired active NUC table number.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] activeNuc:  Specifies the desired active NUC table number
  * @return >= CAM_OK if successful or an error codes in case of an error

  */
PHOTON_RESULT SpectareSetActiveNuc(int deviceId,short activeNuc)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = COOLED_CORE_SET_ACTIVE_NUC;
   value[1] = activeNuc;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 2, value);

   return(result);
}


/*!
  * Sets the pixel gain value for specified pixel row and column.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] row:  Specifies the desired pixel row
  * @param[in] col:  Specifies the desired pixel column
  * @param[in] gain:  Specifies the desired pixel gain value
  * @param[in] badPixelStatus:  Specifies the desired pixel status value 0=bad 1=good
  * @return >= CAM_OK if successful or an error codes in case of an error
  */
PHOTON_RESULT SpectareSetPixelGain(int deviceId, short row, short col, short gain, short badPixelStatus)
{
   PHOTON_RESULT result = 0;
   short value[6] = {0,0,0,0,0,0};
   value[0] = COOLED_CORE_SET_PIXEL_GAIN;
   value[1] = col;
   value[2] = row;
   value[3] = gain;
   value[4] = badPixelStatus;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 5, value);

   return(result);
}

/*!
  * Gets the pixel gain value for specified pixel row and column.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] row:  Specifies the desired pixel row
  * @param[in] col:  Specifies the desired pixel column
  * @param[out] gain:  Gets the desired pixel gain value
  * @return >= CAM_OK if successful or an error codes in case of an error
  */
PHOTON_RESULT SpectareGetPixelGain(int deviceId, short row, short col, short *gain)
{
   PHOTON_RESULT result = 0;
   short value[6] = {0,0,0,0,0,0};
   value[0] = COOLED_CORE_GET_PIXEL_GAIN;
   value[1] = col;
   value[2] = row;

   result = CamSetParams(deviceId, COOLED_CORE_COMMAND, 3, value);

   if( result >= 8 )
   {
       /* data[2] is still the row and data[1] is still the col */
      *gain = value[3];
   }

   return(result);
}

/** @} */ /* end of group */
