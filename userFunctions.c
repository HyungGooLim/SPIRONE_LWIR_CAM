#include "photonComm.h"
#include "userFunctions.h"
#include "proto.h"


void ShortSwapLong(long* value)
{
     long temp;
     temp = *value;
     *value = (temp >> 16) & 0x0000FFFF;
     *value += temp << 16;
}


/*
 *-------------------------------------------------
 *AGC Functions
 *-------------------------------------------------
 */
/*!
 *@defgroup agc AGC Functions
 *  AGC related functions.
 *  @{
 */


/*!
  * Gets the automatic gain correction (AGC) filter value.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] value: Current AGC filter value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetAGCFilterValue()
  */
PHOTON_RESULT PhotonGetAGCFilterValue(int deviceId, short* value)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, AGC_FILTER, 1, value);
     return result;
}


/*!
  * Sets the automatic gain correction (AGC) filter value.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] value: Desired AGC filter value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetAGCFilterValue()
  */
PHOTON_RESULT PhotonSetAGCFilterValue(int deviceId, short value)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) value >= -32768 && (int) value <= 32767)
     {
          result = CamSetParams(deviceId, AGC_FILTER, 1, &value);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the mean array value in the ROI.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] mean: Current mean array value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetAGCROI(), SetAGCROI()
  */
PHOTON_RESULT PhotonGetAGCMean(int deviceId, short* mean)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, READ_ARRAY_AVERAGE, 1, mean);
     return result;
}


/*!
  * Gets the region of interest for automatic gain correction (AGC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] coordinates: A structure with a left, top, right and bottom value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetAGCType(), SetAGCType(), SetAGCROI(), GetAGCMean()
  */
PHOTON_RESULT PhotonGetAGCROI(int deviceId, PHOTON_RECT* coordinates)
{
     PHOTON_RESULT result = CAM_OK;
     short param[4];
     result = CamGetParams(deviceId, AGC_ROI, 4, (short*)param);
     coordinates->left = param[0];
     coordinates->top = param[1];
     coordinates->right = param[2];
     coordinates->bottom = param[3];
     return result;
}


/*!
  * Sets the region of interest for automatic gain correction (AGC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] coordinates: A structure with a left, top, right and bottom value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetAGCType(), SetAGCType(), GetAGCROI(), GetAGCMean()
  */
PHOTON_RESULT PhotonSetAGCROI(int deviceId, PHOTON_RECT coordinates)
{
     PHOTON_RESULT result = CAM_OK;
     short param[4];
     if (((int) coordinates.left >= -32768 && (int) coordinates.left <= 32767) && 
         ((int) coordinates.top >= -32768 && (int) coordinates.top <= 32767) && 
         ((int) coordinates.right >= -32768 && (int) coordinates.right <= 32767) && 
         ((int) coordinates.bottom >= -32768 && (int) coordinates.bottom <= 32767))
     {
          param[0] = coordinates.left;
          param[1] = coordinates.top;
          param[2] = coordinates.right;
          param[3] = coordinates.bottom;
          result = CamSetParams(deviceId, AGC_ROI, 4, param);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the automatic gain correction (AGC) algorithm.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] agcType: An enum corresponding to the automatic gain correction (AGC) algorithms of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetAGCType()
  */
PHOTON_RESULT PhotonGetAGCType(int deviceId, PHOTON_AGC_ALGORITHM* agcType)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, AGC_TYPE, 1, &param);
     *agcType = param;
     return result;
}


/*!
  * Sets the automatic gain correction (AGC) algorithm.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] agcType: An enum corresponding to the automatic gain correction (AGC) algorithms of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetAGCType()
  */
PHOTON_RESULT PhotonSetAGCType(int deviceId, PHOTON_AGC_ALGORITHM agcType)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) agcType >= 0 && (int) agcType <= 32767)
     {
          result = CamSetParams(deviceId, AGC_TYPE, 1, (short*)&agcType);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the brightness.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] brightness: Current brightness value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetBrightness(), GetAGCType(), SetAGCType()
  */
PHOTON_RESULT PhotonGetBrightness(int deviceId, short* brightness)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, BRIGHTNESS, 1, brightness);
     return result;
}


/*!
  * Sets the brightness.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] brightness: Desired brightness value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetBrightness(), GetAGCType(), SetAGCType()
  */
PHOTON_RESULT PhotonSetBrightness(int deviceId, short brightness)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) brightness >= -32768 && (int) brightness <= 32767)
     {
          result = CamSetParams(deviceId, BRIGHTNESS, 1, &brightness);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the brightness bias.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] bias: Current brightness bias value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetBrightnessBias(), GetAGCType(), SetAGCType()
  */
PHOTON_RESULT PhotonGetBrightnessBias(int deviceId, short* bias)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, BRIGHTNESS_BIAS, 1, bias);
     return result;
}


/*!
  * Sets the brightness bias.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] bias: Desired brightness bias value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetBrightnessBias(), GetAGCType(), SetAGCType()
  */
PHOTON_RESULT PhotonSetBrightnessBias(int deviceId, short bias)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) bias >= -32768 && (int) bias <= 32767)
     {
          result = CamSetParams(deviceId, BRIGHTNESS_BIAS, 1, &bias);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the contrast.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] contrast: Current contrast value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetContrast(), GetAGCType(), SetAGCType()
  */
PHOTON_RESULT PhotonGetContrast(int deviceId, short* contrast)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, CONTRAST, 1, contrast);
     return result;
}


/*!
  * Sets the contrast.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] contrast: Desired contrast value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetContrast(), GetAGCType(), SetAGCType()
  */
PHOTON_RESULT PhotonSetContrast(int deviceId, short contrast)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) contrast >= -32768 && (int) contrast <= 32767)
     {
          result = CamSetParams(deviceId, CONTRAST, 1, &contrast);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the intensity transform table (ITT) midpoint offset.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] midpoint: Current ITT midpoint offset
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetAGCType(), SetAGCType(), SetITTMidpoint()
  */
PHOTON_RESULT PhotonGetITTMidpoint(int deviceId, short* midpoint)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, ITT_MIDPOINT, 1, midpoint);
     return result;
}


/*!
  * Sets the intensity transform table (ITT) midpoint offset.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] midpoint: Desired ITT midpoint offset
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetAGCType(), SetAGCType(), GetITTMidpoint()
  */
PHOTON_RESULT PhotonSetITTMidpoint(int deviceId, short midpoint)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) midpoint >= -32768 && (int) midpoint <= 32767)
     {
          result = CamSetParams(deviceId, ITT_MIDPOINT, 1, &midpoint);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the max AGC gain.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] value: Current max AGC gain value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetAGCType(), SetAGCType(), SetMaxAGCGain()
  */
PHOTON_RESULT PhotonGetMaxAGCGain(int deviceId, short* value)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, MAX_AGC_GAIN, 1, value);
     return result;
}


/*!
  * Sets the max AGC gain.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] value: Desired max AGC gain value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetAGCType(), SetAGCType(), GetMaxAGCGain()
  */
PHOTON_RESULT PhotonSetMaxAGCGain(int deviceId, short value)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) value >= -32768 && (int) value <= 32767)
     {
          result = CamSetParams(deviceId, MAX_AGC_GAIN, 1, &value);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the plateau level.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] value: Current plateau value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetAGCType(), SetAGCType(), SetPlateauValue()
  */
PHOTON_RESULT PhotonGetPlateauValue(int deviceId, short* value)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, PLATEAU_LEVEL, 1, value);
     return result;
}


/*!
  * Sets the plateau level.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] value: Desired plateau value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetAGCType(), SetAGCType(), GetPlateauValue()
  */
PHOTON_RESULT PhotonSetPlateauValue(int deviceId, short value)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) value >= -32768 && (int) value <= 32767)
     {
          result = CamSetParams(deviceId, PLATEAU_LEVEL, 1, &value);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/** @} */ /* end of group */


/*
 *-------------------------------------------------
 *Camera System Functions
 *-------------------------------------------------
 */
/*!
 *@defgroup system Camera System Functions
 *  Camera System related functions.
 *  @{
 */


/*!
  * Performs no operation.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error
  */
PHOTON_RESULT PhotonDoNoOp(int deviceId)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamSetParams(deviceId, NO_OP, 0, &param);
     return result;
}


/*!
  * Resets the camera.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error
  */
PHOTON_RESULT PhotonDoReset(int deviceId)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamSetParams(deviceId, CAMERA_RESET, 0, &param);
     return result;
}


/*!
  * Gets the FPA temperature.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] mode: An enum corresponding to the focal plane array (FPA) temp modes of the camera which are raw counts and tenths of degrees celsius
  * @param[out] temp: Current FPA temperature
  * @return >= CAM_OK if successful or an error codes in case of an error
  */
PHOTON_RESULT PhotonGetFPATemp(int deviceId, PHOTON_FPA_TEMP_MODE mode, short* temp)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     if ((int) mode >= 0 && (int) mode <= 32767)
     {
          param = mode;
          result = CamSetParams(deviceId, READ_SENSOR, 1, &param);
          *temp = param;
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the software and firmware verions.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] swVersion: Software version number
  * @param[out] fwVersion: Firmware version number
  * @return >= CAM_OK if successful or an error codes in case of an error
  */
PHOTON_RESULT PhotonGetRevision(int deviceId, long* swVersion, long* fwVersion)
{
    printf("4)userFunctions.c//deviceID address: %d\n", &commPort);
    printf("5)userFunctions.c//deviceID: %d\n", commPort);
    
     PHOTON_RESULT result = CAM_OK;
     short param[4];
     result = CamGetParams(deviceId, GET_REVISION, 4, param);
     *swVersion = (param[0] << 16) + param[1];
     *fwVersion = (param[2] << 16) + param[3];
     return result;
}


/*!
  * Gets the options which are installed on the camera.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] options: An enum corresponding to all the of the optional features on the camera
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonSetOptions()
  */
PHOTON_RESULT PhotonGetOptions(int deviceId, PHOTON_OPTIONS* options)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamSetParams(deviceId, GET_CAMERA_OPTIONS, 1, &param);
     *options = param;
     return result;
}


/*!
  * Resets the defaults settings of the camera.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa SetPowerUpDefaults()
  */
PHOTON_RESULT PhotonRestoreFactoryDefaults(int deviceId)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamSetParams(deviceId, RESET_FACTORY_DEFAULTS, 0, NULL);
     if(result < 0)
          return (PHOTON_RESULT) result;
     do
     {
          result = CamGetParams(deviceId, FLASH_STATUS, 1, &param);
          if(result < 0)
               break;
     } while(param > 0);
     result = param;
     return result;
}


/*!
  * Gets the serial number of the camera.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] serialNum: Camera serial number 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetPartNumber()
  */
PHOTON_RESULT PhotonGetSerialNum(int deviceId, long* serialNum)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, SERIAL_NUMBER, 2, (short*)serialNum);
     ShortSwapLong(serialNum);
     return result;
}


/*!
  * Sets the default settings of the camera.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa RestoreFactoryDefaults()
  */
PHOTON_RESULT PhotonSetPowerUpDefaults(int deviceId)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamSetParams(deviceId, SET_DEFAULTS, 0, NULL);
     if(result < 0)
          return (PHOTON_RESULT) result;
     do
     {
          result = CamGetParams(deviceId, FLASH_STATUS, 1, &param);
          if(result < 0)
               break;
     } while(param > 0);
     result = param;
     return result;
}


/*!
  * Gets the camera part number.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] partNumber: A string representing the part number of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetPartNumberNum()
  */
PHOTON_RESULT PhotonGetPartNumber(int deviceId, char* partNumber)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, CAMERA_PART, -16, (short*)partNumber);
     return result;
}


/** @} */ /* end of group */


/*
 *-------------------------------------------------
 *FFC & Flag Functions
 *-------------------------------------------------
 */
/*!
 *@defgroup ffc FFC & Flag Functions
 *  FFC and Flag related functions.
 *  @{
 */


/*!
  * Command the camera to perform a flat field correction (FFC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMode(), SetFFCMode()
  */
PHOTON_RESULT PhotonDoFFC(int deviceId)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamSetParams(deviceId, DO_FFC, 0, &param);
     return result;
}


/*!
  * Gets the mean average for the frame during the flat field correction (FFC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] value: Current frame mean average during a FFC 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetFFCMeanValue()
  */
PHOTON_RESULT PhotonGetFFCMeanValue(int deviceId, short* value)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, FFC_MEAN_VALUE, 1, value);
     return result;
}


/*!
  * Sets the mean average for the frame during the flat field correction (FFC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] value: Desired frame mean average during a FFC 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMeanValue()
  */
PHOTON_RESULT PhotonSetFFCMeanValue(int deviceId, short value)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) value >= -32768 && (int) value <= 32767)
     {
          result = CamSetParams(deviceId, FFC_MEAN_VALUE, 1, &value);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the flat field correction (FFC) mode.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] ffcMode: An enum corresponding to the flat field correction (FFC) modes of the camera which are manual and auto
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetFFCMode(), GetFFCPeriod(), SetFFCPeriod() SetFFCPeriods() GetFFCPeriods()
  */
PHOTON_RESULT PhotonGetFFCMode(int deviceId, PHOTON_FFC_MODE* ffcMode)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, FFC_MODE_SELECT, 1, &param);
     *ffcMode = param;
     return result;
}


/*!
  * Sets the flat field correction (FFC) mode.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] ffcMode: An enum corresponding to the flat field correction (FFC) modes of the camera which are manual and auto
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMode(), GetFFCPeriod(), SetFFCPeriod() SetFFCPeriods() GetFFCPeriods()
  */
PHOTON_RESULT PhotonSetFFCMode(int deviceId, PHOTON_FFC_MODE ffcMode)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) ffcMode >= 0 && (int) ffcMode <= 32767)
     {
          result = CamSetParams(deviceId, FFC_MODE_SELECT, 1, (short*)&ffcMode);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the period between automatic flat field corrections (FFC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] ffcPeriod: Current FFC period in frames
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMode(), SetFFCMode(), SetFFCPeriod() SetFFCPeriods() GetFFCPeriods()
  */
PHOTON_RESULT PhotonGetFFCPeriod(int deviceId, short* ffcPeriod)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, FFC_PERIOD, 1, ffcPeriod);
     return result;
}


/*!
  * Sets the period between automatic flat field corrections (FFC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] ffcPeriod: Desired FFC period in frames
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMode(), SetFFCMode(), GetFFCPeriod() SetFFCPeriods() GetFFCPeriods()
  */
PHOTON_RESULT PhotonSetFFCPeriod(int deviceId, short ffcPeriod)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) ffcPeriod >= -32768 && (int) ffcPeriod <= 32767)
     {
          result = CamSetParams(deviceId, FFC_PERIOD, 1, &ffcPeriod);
          return result;
     }
     return CAM_RANGE_ERROR;
}

/*!
  * Gets the periods (high and low gain) between automatic flat field corrections (FFC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] ffcPeriod: Current FFC period in frames
  * @param[out] ffcPeriodLowGain: Current FFC period in frames
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMode(), SetFFCMode(), SetFFCPeriod() PhotonSetFFCPeriods()
  */
PHOTON_RESULT PhotonGetFFCPeriods(int deviceId, short* ffcPeriod, short *ffcPeriodLowGain)
{
     PHOTON_RESULT result = CAM_OK;
     short params[2];
     result = CamGetParams(deviceId, FFC_PERIOD, 2, params);
     if (result >= 0)
     {
        *ffcPeriod = params[0];
        *ffcPeriodLowGain = params[1];
     }
     return result;
}


/*!
  * Sets the period (high and low gain) between automatic flat field corrections (FFC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] ffcPeriod: Desired FFC period in frames
  * @param[in] ffcPeriodLowGain: Desired FFC period in frames
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMode(), SetFFCMode(), GetFFCPeriod() GetFFCPeriods()
  */
PHOTON_RESULT PhotonSetFFCPeriods(int deviceId, short ffcPeriod, short ffcPeriodLowGain)
{
     PHOTON_RESULT result = CAM_OK;
     short params[2];
     params[0] = ffcPeriod;
     params[1] = ffcPeriodLowGain;
     if ((int) ffcPeriod >= -32768 && (int) ffcPeriod <= 32767)
     {
         if ((int) ffcPeriodLowGain >= -32768 && (int) ffcPeriodLowGain <= 32767)
         {
            result = CamSetParams(deviceId, FFC_PERIOD, 2, params);
            return result;
         }
          
     }
     return CAM_RANGE_ERROR;
}



/*!
  * Gets the temperature change needed to have the camera perform a flat field correction (FFC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] ffcTempDelta: A type used to represent 10ths of degrees celsius
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMode(), SetFFCMode(), SetFFCTempDelta()
  */
PHOTON_RESULT PhotonGetFFCTempDelta(int deviceId, PHOTON_TEMP* ffcTempDelta)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, FFC_TEMP_DELTA, 1, &param);
     *ffcTempDelta = param;
     return result;
}


/*!
  * Sets the temperature change needed to have the camera perform a flat field correction (FFC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] ffcTempDelta: A type used to represent 10ths of degrees celsius
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMode(), SetFFCMode(), GetFFCTempDelta()
  */
PHOTON_RESULT PhotonSetFFCTempDelta(int deviceId, PHOTON_TEMP ffcTempDelta)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) ffcTempDelta >= -32768 && (int) ffcTempDelta <= 32767)
     {
          result = CamSetParams(deviceId, FFC_TEMP_DELTA, 1, (short*)&ffcTempDelta);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the flat field correction (FFC) warn time.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] time: Current FFC warn time in frames
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMode(), SetFFCMode(), SetFFCWarnTime()
  */
PHOTON_RESULT PhotonGetFFCWarnTime(int deviceId, short* time)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, FFC_WARN_TIME, 1, time);
     return result;
}


/*!
  * Sets the flat field correction (FFC) warn time.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] time: Desired FFC warn time in frames
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMode(), SetFFCMode(), GetFFCWarnTime()
  */
PHOTON_RESULT PhotonSetFFCWarnTime(int deviceId, short time)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) time >= -32768 && (int) time <= 32767)
     {
          result = CamSetParams(deviceId, FFC_WARN_TIME, 1, &time);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the shutter position of the camera.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] position: An enum corresponding to the shutter positions of the camera which are open and closed
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetShutterPosition()
  */
PHOTON_RESULT PhotonGetShutterPosition(int deviceId, PHOTON_SHUTTER_POSITION* position)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, SHUTTER_POSITION, 1, &param);
     *position = param;
     return result;
}


/*!
  * Sets the shutter position of the camera.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] position: An enum corresponding to the shutter positions of the camera which are open and closed
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetShutterPosition()
  */
PHOTON_RESULT PhotonSetShutterPosition(int deviceId, PHOTON_SHUTTER_POSITION position)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) position >= 0 && (int) position <= 32767)
     {
          result = CamSetParams(deviceId, SHUTTER_POSITION, 1, (short*)&position);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/** @} */ /* end of group */


/*
 *-------------------------------------------------
 *Isotherm Functions
 *-------------------------------------------------
 */
/*!
 *@defgroup isotherm Isotherm Functions
 *  Isotherm related functions.
 *  @{
 */


/*!
  * Gets the isotherm mode.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] mode: An enum corresponding to the isotherm modes of the camera which are off and on
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetIsothermMode(), GetIsothermThresholds(), SetIsothermThresholds()
  */
PHOTON_RESULT PhotonGetIsothermMode(int deviceId, PHOTON_ISOTHERM_MODE* mode)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, ISOTHERM, 1, &param);
     *mode = param;
     return result;
}


/*!
  * Sets the isortherm mode.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] mode: An enum corresponding to the isotherm modes of the camera which are off and on
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetIsothermMode(), GetIsothermThresholds(), SetIsothermThresholds()
  */
PHOTON_RESULT PhotonSetIsothermMode(int deviceId, PHOTON_ISOTHERM_MODE mode)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) mode >= 0 && (int) mode <= 32767)
     {
          result = CamSetParams(deviceId, ISOTHERM, 1, (short*)&mode);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the isotherm thresholds.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] isoType: An enum corresponding to the isotherm types of the camera which are percentage and celsius
  * @param[out] lowerThreshold: Current lower isotherm threshold value
  * @param[out] upperThreshold: Current upper isotherm threshold value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetIsothermMode(), SetIsothermMode(), SetIsothermThresholds()
  */
PHOTON_RESULT PhotonGetIsothermThresholds(int deviceId, PHOTON_ISOTHERM_THRESHOLD_TYPE* isoType, short* lowerThreshold, short* upperThreshold)
{
     PHOTON_RESULT result = CAM_OK;
     short param[2];
     result = CamGetParams(deviceId, ISOTHERM_THRESHOLDS, 2, param);
     if (param[0] >> 12 != 00 && param[1] >> 12 != 0)
          *isoType = ISOTHERM_CELSIUS;
     else
          *isoType = ISOTHERM_PERCENTAGE;
     if (*isoType == ISOTHERM_CELSIUS)
     {
          param[0] = param[0] & 0x7FFF;
          param[1] = param[1] & 0x7FFF;
     }
     *lowerThreshold = param[0];
     *upperThreshold = param[1];
     return result;
}


/*!
  * Sets the isotherm thresholds.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] isoType: An enum corresponding to the isotherm types of the camera which are percentage and celsius
  * @param[in] lowerThreshold: Desired lower isotherm threshold value
  * @param[in] upperThreshold: Desired upper isotherm threshold value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetIsothermMode(), SetIsothermMode(), GetIsothermThresholds()
  */
PHOTON_RESULT PhotonSetIsothermThresholds(int deviceId, PHOTON_ISOTHERM_THRESHOLD_TYPE isoType, short lowerThreshold, short upperThreshold)
{
     PHOTON_RESULT result = CAM_OK;
     short param[2];
     if ((int) isoType >= 0 && (int) isoType <= 1)
     {
          if (((int) lowerThreshold >= -40 && (int) lowerThreshold <= 32767) &&
              ((int) upperThreshold >= -40 && (int) upperThreshold <= 32767))
          {
               param[0] = lowerThreshold;
               param[1] = upperThreshold;
               if (isoType == ISOTHERM_CELSIUS)
               {
                    param[0] = param[0] | 0x8000;
                    param[1] = param[1] | 0x8000;
               }
               result = CamSetParams(deviceId, ISOTHERM_THRESHOLDS, 2, param);
               return result;
          }
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets three isotherm thresholds.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] isoType: An enum corresponding to the isotherm types of the camera which are percentage and celsius
  * @param[out] lowerThreshold: Current lower isotherm threshold value
  * @param[out] midThreshold: Current mid isotherm threshold value
  * @param[out] upperThreshold: Current upper isotherm threshold value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetIsothermMode(), SetIsothermMode(), SetThreeIsothermThresholds()
  */
PHOTON_RESULT PhotonGetThreeIsothermThresholds(int deviceId, PHOTON_ISOTHERM_THRESHOLD_TYPE* isoType, short* lowerThreshold, short* midThreshold, short* upperThreshold)
{
     PHOTON_RESULT result = CAM_OK;
     short param[3];
     result = CamGetParams(deviceId, ISOTHERM_THRESHOLDS, 3, param);
     if (param[0] >> 12 != 00 )
          *isoType = ISOTHERM_CELSIUS;
     else
          *isoType = ISOTHERM_PERCENTAGE;
     if (*isoType == ISOTHERM_CELSIUS)
     {
         if ((param[0] & 0x4000) == 0) // Need to sign extend if negative value
         {
			param[0] = param[0] & 0x7FFF;
         }
     }
     *lowerThreshold = param[0];
     *midThreshold = param[1];
     *upperThreshold = param[2];
     return result;
}


/*!
  * Sets three isotherm thresholds.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] isoType: An enum corresponding to the isotherm types of the camera which are percentage and celsius
  * @param[in] lowerThreshold: Desired lower isotherm threshold value
  * @param[in] midThreshold: Desired upper isotherm threshold value
  * @param[in] upperThreshold: Desired upper isotherm threshold value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetIsothermMode(), SetIsothermMode(), GetThreeIsothermThresholds()
  */
PHOTON_RESULT PhotonSetThreeIsothermThresholds(int deviceId, PHOTON_ISOTHERM_THRESHOLD_TYPE isoType, short lowerThreshold, short midThreshold, short upperThreshold)
{
     PHOTON_RESULT result = CAM_OK;
     short param[3];
     if ((int) isoType >= 0 && (int) isoType <= 1)
     {
          if (((int) lowerThreshold >= -40 && (int) lowerThreshold <= 32767) &&
			  ((int) midThreshold >= -40 && (int) midThreshold <= 32767) &&
              ((int) upperThreshold >= -40 && (int) upperThreshold <= 32767))
          {
               param[0] = lowerThreshold;
               param[1] = midThreshold;
               param[2] = upperThreshold;
               if (isoType == ISOTHERM_CELSIUS)
               {
                    param[0] = param[0] | 0x8000;
               }
               result = CamSetParams(deviceId, ISOTHERM_THRESHOLDS, 3, param);
               return result;
          }
     }
     return CAM_RANGE_ERROR;
}


/** @} */ /* end of group */


/*
 *-------------------------------------------------
 *NUC Functions
 *-------------------------------------------------
 */
/*!
 *@defgroup nuc NUC Functions
 *  NUC related functions.
 *  @{
 */


/*!
  * Gets the gain mode of the camera.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] gainMode: An enum corresponding to the gain modes of the camera which are auto, low, high and manual
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetGainMode()
  */
PHOTON_RESULT PhotonGetGainMode(int deviceId, PHOTON_GAIN_MODE* gainMode)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, GAIN_MODE, 1, &param);
     *gainMode = param;
     return result;
}


/*!
  * Sets the gain mode of the camera.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] gainMode: An enum corresponding to the gain modes of the camera which are auto, low, high and manual
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetGainMode()
  */
PHOTON_RESULT PhotonSetGainMode(int deviceId, PHOTON_GAIN_MODE gainMode)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) gainMode >= 0 && (int) gainMode <= 32767)
     {
          result = CamSetParams(deviceId, GAIN_MODE, 1, (short*)&gainMode);
          return result;
     }
     return CAM_RANGE_ERROR;
}

/*!
  * Gets the External Offset State - On/Off.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] state: value of 1 indicates on and  state value of 0 indicates off
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetExtOffsetSetate()
  */

PHOTON_RESULT PhotonGetExtOffsetState(int deviceId, PHOTON_OFFSETSTATE* state)
{
     PHOTON_RESULT result = CAM_OK;
	 short correctionMask;
     result = CamGetParams(deviceId, CORRECTION_MASK, 1, &correctionMask);
	 if(correctionMask & EXTFFC_OFFSET_MASK)
	 {
		 *state = 1;
	 }
	 else
	 {
		 *state = 0;
	 }
     return result;
}

/*!
  * Sets the External Offset State - On/Off.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] state: value of 1 indicates on and  state value of 0 indicates off
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetExtOffsetSetate()
  */
PHOTON_RESULT PhotonSetExtOffsetState(int deviceId, PHOTON_OFFSETSTATE state)
{
	PHOTON_RESULT result = CAM_OK;
	short correctionMask;
	
	result = CamGetParams(deviceId, CORRECTION_MASK, 1, &correctionMask);
	if(state == 1)
	{
		correctionMask = correctionMask | EXTFFC_OFFSET_MASK;
	}
	else
	{
		correctionMask = correctionMask & ~EXTFFC_OFFSET_MASK;
	}
		
    result = CamSetParams(deviceId, CORRECTION_MASK, 1, &correctionMask);
      
	return result;
}

/*!
  * Sets the camera Dynamic Data Enhancement state (spatial threshold)
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] ddeState: value between 0 and 64 inclusive to indicate spatial 
  * threshold index.
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetExtOffsetState()
  */
PHOTON_RESULT PhotonSetDDEState(int deviceId, short ddeState)
{
    int result = 0;
    short spatialThreshold = 0;
    result = CamGetParams(deviceId, SPATIAL_THRESHOLD, 1, &spatialThreshold);
	//Mask out the DDE mode value
    spatialThreshold &= 0x00FF;
	 ddeState = (ddeState << 8) & 0xFF00;
    // Preserve the spatial threshold value (OR it back in)
    spatialThreshold = ddeState | spatialThreshold;
    result = CamSetParams(deviceId, SPATIAL_THRESHOLD, 1, &spatialThreshold);
    return result;
}


/*!
  * Computes additional offset cprrection following original gain and offset correctionState 
  * @param[in] deviceID: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetExtOffsetState()
  */
PHOTON_RESULT PhotonCalcSupplementalOffset(int deviceID)
{
	short param;
    PHOTON_RESULT result = CamCallFuncTimeout(deviceID, CALC_EXTOFFSET, &param, 0, CAM_LONG_TIMEOUT);
	return result;
}


PHOTON_RESULT PhotonWriteSupplementalOffset(int deviceID)
{
	short param;
    PHOTON_RESULT result = CamCallFuncTimeout(deviceID, WRITE_EXT_OFFSET_TABLE, &param, 0, CAM_LONG_TIMEOUT);
	//PHOTON_RESULT result = CamSetParams(deviceID, WRITE_EXT_OFFSET_TABLE, 0, &param);
	if(result < 0)
         return (PHOTON_RESULT) result;
    do
    {
         result = CamGetParams(deviceID, FLASH_STATUS, 1, &param);
         if(result < 0)
		     break;
    } while(param > 0);
    result = param;
    return result;	
}


/** @} */ /* end of group */


/*
 *-------------------------------------------------
 *Spot Meter Functions
 *-------------------------------------------------
 */
/*!
 *@defgroup spot Spot Meter Functions
 *  Spot Meter related functions.
 *  @{
 */


/*!
  * Gets the temperature reading of the spot meter.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] temp: A type used to represent 10ths of degrees celsius
  * @return >= CAM_OK if successful or an error codes in case of an error
  */
PHOTON_RESULT PhotonGetSpotTemp(int deviceId, PHOTON_TEMP* temp)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, GET_SPOT_METER, 1, &param);
     *temp = param;
     return result;
}


/*!
  * Gets the spot meter display mode.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] display: An enum corresponding to the spot display modes of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetSpotDisplay()
  */
PHOTON_RESULT PhotonGetSpotDisplay(int deviceId, PHOTON_SPOT_DISPLAY* display)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, SPOT_DISPLAY, 1, &param);
     *display = param;
     return result;
}


/*!
  * Sets the spot meter display mode.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] display: An enum corresponding to the spot display modes of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetSpotDisplay()
  */
PHOTON_RESULT PhotonSetSpotDisplay(int deviceId, PHOTON_SPOT_DISPLAY display)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) display >= 0 && (int) display <= 32767)
     {
          result = CamSetParams(deviceId, SPOT_DISPLAY, 1, (short*)&display);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the spot meter mode.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] mode: An enum corresponding to the spot meter modes of the camera which are off, fahrenheit and celsius
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetMeterMode()
  */
PHOTON_RESULT PhotonGetSpotMeterMode(int deviceId, PHOTON_SPOT_METER_MODE* mode)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, SPOT_METER_MODE, 1, &param);
     *mode = param;
     return result;
}


/*!
  * Sets the spot meter mode.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] mode: An enum corresponding to the spot meter modes of the camera which are off, fahrenheit and celsius
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetMeterMode()
  */
PHOTON_RESULT PhotonSetSpotMeterMode(int deviceId, PHOTON_SPOT_METER_MODE mode)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) mode >= 0 && (int) mode <= 32767)
     {
          result = CamSetParams(deviceId, SPOT_METER_MODE, 1, (short*)&mode);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/** @} */ /* end of group */


/*
 *-------------------------------------------------
 *Video Control Functions
 *-------------------------------------------------
 */
/*!
 *@defgroup video Video Control Functions
 *  Video Control related functions.
 *  @{
 */


/*!
  * Gets the digital output mode.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] digitalOutput: An enum corresponding to the digitital output types of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetDigitalOut()
  */
PHOTON_RESULT PhotonGetDigitalOut(int deviceId, PHOTON_DIGITAL_OUT* digitalOutput)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, DIGITAL_OUTPUT_MODE, 1, &param);
     *digitalOutput = param;
     return result;
}


/*!
  * Sets the digital output mode.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] digitalOutput: An enum corresponding to the digitital output types of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetDigitalOut()
  */
PHOTON_RESULT PhotonSetDigitalOut(int deviceId, PHOTON_DIGITAL_OUT digitalOutput)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) digitalOutput >= 0 && (int) digitalOutput <= 32767)
     {
          result = CamSetParams(deviceId, DIGITAL_OUTPUT_MODE, 1, (short*)&digitalOutput);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the external syncronization mode.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] mode: An enum corresponding to the external syncronization types of the camera which are disabled, master and slave
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetSyncMode()
  */
PHOTON_RESULT PhotonGetSyncMode(int deviceId, PHOTON_EXT_SYNC_MODE* mode)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, EXTERNAL_SYNC, 1, &param);
     *mode = param;
     return result;
}


/*!
  * Sets the external syncronization mode.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] mode: An enum corresponding to the external syncronization types of the camera which are disabled, master and slave
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetSyncMode()
  */
PHOTON_RESULT PhotonSetSyncMode(int deviceId, PHOTON_EXT_SYNC_MODE mode)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) mode >= 0 && (int) mode <= 32767)
     {
          result = CamSetParams(deviceId, EXTERNAL_SYNC, 1, (short*)&mode);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the test pattern.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] pattern: An enum corresponding to the test patterns of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetTestPattern()
  */
PHOTON_RESULT PhotonGetTestPattern(int deviceId, PHOTON_TEST_PATTERN* pattern)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, TEST_PATTERN, 1, &param);
     *pattern = param;
     return result;
}


/*!
  * Sets the test pattern.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] pattern: An enum corresponding to the test patterns of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetTestPattern()
  */
PHOTON_RESULT PhotonSetTestPattern(int deviceId, PHOTON_TEST_PATTERN pattern)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) pattern >= 0 && (int) pattern <= 32767)
     {
          result = CamSetParams(deviceId, TEST_PATTERN, 1, (short*)&pattern);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the image orientation.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] imageOrientation: 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetOrientation()
  */
PHOTON_RESULT PhotonGetOrientation(int deviceId, PHOTON_IMAGE_ORIENTATION* imageOrientation)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, VIDEO_ORIENTATION, 1, &param);
     *imageOrientation = param;
     return result;
}


/*!
  * Sets the image orientation.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] imageOrientation: 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetOrientation()
  */
PHOTON_RESULT PhotonSetOrientation(int deviceId, PHOTON_IMAGE_ORIENTATION imageOrientation)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) imageOrientation >= 0 && (int) imageOrientation <= 32767)
     {
          result = CamSetParams(deviceId, VIDEO_ORIENTATION, 1, (short*)&imageOrientation);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the pan and tilt location.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] x: Current x-axis coordinate for center of the video output
  * @param[out] y: Current y-axis coordinate for center of the video output
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetPanTilt(), GetVideoMode(), SetVideoMode()
  */
PHOTON_RESULT PhotonGetPanTilt(int deviceId, short* x, short* y)
{
     PHOTON_RESULT result = CAM_OK;
     short param[2];
     result = CamGetParams(deviceId, VIDEO_ARRAY_OFFSET, 2, param);
     *y = param[0];
     *x = param[1];
     return result;
}


/*!
  * Sets the pan and tilt location.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] x: Desired x-axis coordinate for center of the video output
  * @param[in] y: Desired y-axis coordinate for center of the video output
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetPanTilt(), GetVideoMode(), SetVideoMode()
  */
PHOTON_RESULT PhotonSetPanTilt(int deviceId, short x, short y)
{
     PHOTON_RESULT result = CAM_OK;
     short param[2];
     if (((int) x >= -32768 && (int) x <= 32767) &&
         ((int) y >= -32768 && (int) y <= 32767))
     {
          param[0] = y;
          param[1] = x;
          result = CamSetParams(deviceId, VIDEO_ARRAY_OFFSET, 2, param);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the video color lut.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] lut: An enum corresponding to the color look up tables (LUT) of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetVideoLUT()
  */
PHOTON_RESULT PhotonGetVideoLUT(int deviceId, PHOTON_COLOR_LUT* lut)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, VIDEO_LUT, 1, &param);
     *lut = param;
     return result;
}


/*!
  * Sets the video color lut.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] lut: An enum corresponding to the color look up tables (LUT) of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetVideoLUT()
  */
PHOTON_RESULT PhotonSetVideoLUT(int deviceId, PHOTON_COLOR_LUT lut)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) lut >= 0 && (int) lut <= 32767)
     {
          result = CamSetParams(deviceId, VIDEO_LUT, 1, (short*)&lut);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the video mode (real time, frozen, disabled, etc.)
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] videoMode: An enum corresponding to the video modes of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetVideoModeNew() SetVideoModeNew()
  */
PHOTON_RESULT PhotonGetVideoMode(int deviceId, PHOTON_VIDEO_MODE* videoMode)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, VIDEO_MODE, 1, &param);
     *videoMode = param;
     return result;
}


/*!
  * Sets the video mode (real time, frozen, disabled, etc.)
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] videoMode: An enum corresponding to the video modes of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetVideoModeNew() SetVideoModeNew()
  */
PHOTON_RESULT PhotonSetVideoMode(int deviceId, PHOTON_VIDEO_MODE videoMode)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) videoMode >= 0 && (int) videoMode <= 32767)
     {
          result = CamSetParams(deviceId, VIDEO_MODE, 1, (short*)&videoMode);
          return result;
     }
     return CAM_RANGE_ERROR;
}

/*!
  * Gets the video mode (real time, frozen, disabled, etc.)
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] videoMode: An enum corresponding to the video modes of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetVideoModeNew() SetVideoModeNew()
  */
PHOTON_RESULT PhotonGetVideoModeNew(int deviceId, PHOTON_VIDEO_MODE* videoMode)
{
     PHOTON_RESULT result = CAM_OK;
     short param;
     result = CamGetParams(deviceId, VIDEO_MODE, 1, &param);
     *videoMode = param;
     return result;
}

/*!
  * Sets the video mode (real time, frozen, disabled, etc.). Different from original SetVideoMode in 
  * that it takes into account 2x adn 4x zoom special cases.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] videoMode: An enum corresponding to the video modes of the camera
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetVideoModeNew() SetVideoMode()
  */
PHOTON_RESULT PhotonSetVideoModeNew(int deviceId, PHOTON_VIDEO_MODE videoMode)
{
   PHOTON_RESULT result = CAM_OK;
   short currentMode = 0;

   if ((int) videoMode >= 0 && (int) videoMode <= 32767)
   {
      result = CamGetParams(deviceId,VIDEO_MODE,1,&currentMode);   
         
      if ( (videoMode & VIDEO_REAL_TIME) == VIDEO_REAL_TIME )
      {
         currentMode = currentMode & ~VIDEO_FROZEN;
      }

      if ( (videoMode & VIDEO_FROZEN) == VIDEO_FROZEN)
      {
         currentMode = currentMode & ~VIDEO_REAL_TIME;
      }

      if ( (videoMode & VIDEO_DISABLED) == VIDEO_DISABLED)
      {
         currentMode = currentMode & ~VIDEO_REAL_TIME;
         currentMode = currentMode & ~VIDEO_FROZEN;
      }
      
      // 2x zoom
      if( (videoMode & VIDEO_ZOOM) == VIDEO_ZOOM )
      {
         //Clear previous zoom state (4x and 8x)
         currentMode &= ~(VIDEO_4XZOOM | VIDEO_8XZOOM);
         result = CamSetParams(deviceId, VIDEO_MODE, 1, &currentMode);
      }
      //4X zoom
      else if((videoMode & VIDEO_4XZOOM) == VIDEO_4XZOOM )
      {
         //Clear previous zoom state (2x and 8x)
         currentMode &= ~(VIDEO_ZOOM | VIDEO_8XZOOM);
         result = CamSetParams(deviceId, VIDEO_MODE, 1, &currentMode);
      }
      //8X zoom
      else if((videoMode & VIDEO_8XZOOM) == VIDEO_8XZOOM )
      {
         //Clear previous zoom state (2x and 4x)
         currentMode &= ~(VIDEO_ZOOM | VIDEO_4XZOOM);
         result = CamSetParams(deviceId, VIDEO_MODE, 1, &currentMode);
      }
      //No Zoom
      else 
      {
         //Clear previous zoom states (2x and 4x)
         currentMode &= ~(VIDEO_ZOOM | VIDEO_4XZOOM | VIDEO_8XZOOM);
         result = CamSetParams(deviceId, VIDEO_MODE, 1, &currentMode);
      }
	   currentMode |= videoMode;
      result = CamSetParams(deviceId, VIDEO_MODE, 1, (short*)&currentMode);
      return result;
   }

   return CAM_RANGE_ERROR;
}

/*!
  * Gets if the video is color or monochrome
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] color: PHOTON_VIDEO_COLOR enum 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetVideoColor()
  */

PHOTON_RESULT PhotonGetVideoColor(int deviceId, PHOTON_VIDEO_COLOR* color)
{
     PHOTON_RESULT result = CAM_OK;
	 short param;
	 result = CamGetParams(deviceId,VIDEO_COLOR_MODE,1,(short *)&param);	 	 
	 *color = param;
     return result;     
}

/*!
  * Sets if the video is color or monochrome
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] color: PHOTON_VIDEO_COLOR enum 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetVideoColor()
  */

PHOTON_RESULT PhotonSetVideoColor(int deviceId, PHOTON_VIDEO_COLOR color)
{
     PHOTON_RESULT result = CAM_OK;
	 if((int) color >= 0 && (int) color <= 32767)
	 {
		  result = CamSetParams(deviceId, VIDEO_COLOR_MODE, 1, (short*)&color);
          return result;
     }
     return CAM_RANGE_ERROR;	 
}

/*!
  * Gets if the video state is on or off
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] mode: PHOTON_VIDEO_MODE enum 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetAnalogVideoOnOff()
  */

PHOTON_RESULT PhotonGetAnalogVideoOnOff(int deviceId, PHOTON_VIDEO_MODE *mode)
{
	 PHOTON_RESULT result = CAM_OK;
	 short currentMode = 0;    
	 result = CamGetParams(deviceId,VIDEO_MODE,1,&currentMode);   
	 if(currentMode & VIDEO_DISABLED)
	 {
		 *mode = VIDEO_DISABLED;
	 }
	 else
	 {
		 *mode = VIDEO_ENABLED;
	 }
	 return result;    
}

/*!
  * Sets if the video state is on or off
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] mode: PHOTON_VIDEO_MODE enum 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetAnalogVideoOnOff()
  */

PHOTON_RESULT PhotonSetAnalogVideoOnOff(int deviceId, PHOTON_VIDEO_MODE mode)
{
	 PHOTON_RESULT result = CAM_OK;
	 short currentMode = 0;
     result = CamGetParams(deviceId,VIDEO_MODE,1,&currentMode);   
	 if(mode == VIDEO_DISABLED)
	 {
		 currentMode = currentMode | VIDEO_DISABLED;
	 }
	 else
	 {
		 currentMode = currentMode & ~VIDEO_DISABLED;
	 }
	 result = CamSetParams(deviceId, VIDEO_MODE, 1, (short*)&currentMode);
     return result;     
}

/*!
  * Get the Zoom Mode
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] videoMode: PHOTON_VIDEO_MODE enum 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetZoomMode()
  */

PHOTON_RESULT PhotonGetZoomMode(int deviceId, PHOTON_VIDEO_MODE *videoMode)
{
	 PHOTON_RESULT result = CAM_OK;
	 short currentMode = 0;    
	 result = CamGetParams(deviceId,VIDEO_MODE,1,&currentMode);   
	 if(currentMode & VIDEO_8XZOOM)
	 {
		 *videoMode = VIDEO_8XZOOM;
	 }
	 else if(currentMode & VIDEO_4XZOOM)
	 {
		 *videoMode = VIDEO_4XZOOM;
	 }
	 else if(currentMode & VIDEO_ZOOM)
	 {
		 *videoMode = VIDEO_ZOOM;
	 }
	 else if ((currentMode & VIDEO_ZOOM) == 0 && (currentMode & VIDEO_4XZOOM) == 0 && (currentMode & VIDEO_8XZOOM) == 0)
	 {
		 *videoMode = VIDEO_UNZOOM;
	 }
	 return result;    
}


/*!
  * Set the Zoom Mode
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] videoMode: PHOTON_VIDEO_MODE enum 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetZoomMode()
  */

PHOTON_RESULT PhotonSetZoomMode(int deviceId, PHOTON_VIDEO_MODE videoMode)
{
   PHOTON_RESULT result = CAM_OK;
   short currentMode = 0;

   if ((int) videoMode >= 0 && (int) videoMode <= 32767)
   {
      result = CamGetParams(deviceId,VIDEO_MODE,1,&currentMode);   
         
      // 2x zoom
      if(videoMode == VIDEO_ZOOM)
      {
         //Clear previous zoom state (4x and 8x)
         currentMode &= ~(VIDEO_4XZOOM | VIDEO_8XZOOM);
         result = CamSetParams(deviceId, VIDEO_MODE, 1, &currentMode);
      }
      //4X zoom
      else if(videoMode == VIDEO_4XZOOM)
      {
         //Clear previous zoom state (2x and 8x)
         currentMode &= ~(VIDEO_ZOOM | VIDEO_8XZOOM);
         result = CamSetParams(deviceId, VIDEO_MODE, 1, &currentMode);
      }
      //8X zoom
      else if(videoMode == VIDEO_8XZOOM)
      {
         //Clear previous zoom state (2x and 4x)
         currentMode &= ~(VIDEO_ZOOM | VIDEO_4XZOOM);
         result = CamSetParams(deviceId, VIDEO_MODE, 1, &currentMode);
      }
      //No Zoom
      else 
      {
         //Clear previous zoom states (2x and 4x and 8x)
         currentMode &= ~(VIDEO_ZOOM | VIDEO_4XZOOM | VIDEO_8XZOOM);
      }
	  currentMode |= videoMode;
      result = CamSetParams(deviceId, VIDEO_MODE, 1, (short*)&currentMode);
      return result;
   }

   return CAM_RANGE_ERROR;
}


/*!
  * Get the Freeze Mode
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] mode: PHOTON_VIDEO_MODE enum 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetFreezeMode()
  */

PHOTON_RESULT PhotonGetFreezeMode(int deviceId, PHOTON_VIDEO_MODE *mode)
{
	 PHOTON_RESULT result = CAM_OK;
	 short currentMode = 0;    
	 result = CamGetParams(deviceId,VIDEO_MODE,1,&currentMode);   
	 if(currentMode & VIDEO_FROZEN)
	 {
		 *mode = VIDEO_FROZEN;
	 }
	 else
	 {
		 *mode = VIDEO_REAL_TIME;
	 }
	 return result;    
}


/*!
  * Set the Freeze Mode
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] mode: PHOTON_VIDEO_MODE enum 
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFreezeMode()
  */
PHOTON_RESULT PhotonSetFreezeMode(int deviceId, PHOTON_VIDEO_MODE mode)
{
	 PHOTON_RESULT result = CAM_OK;
	 short currentMode = 0;
     result = CamGetParams(deviceId,VIDEO_MODE,1,&currentMode);   
	 if(mode == VIDEO_FROZEN)
	 {
		 currentMode = currentMode | VIDEO_FROZEN;
	 }
	 else
	 {
		 currentMode = currentMode & ~VIDEO_FROZEN;
	 }
	 result = CamSetParams(deviceId, VIDEO_MODE, 1, (short*)&currentMode);
     return result;     
}

/*!
  * Capture video frames
  * @param[in] deviceID: identifies what device the calls are being sent to
  * @param[in] captureBuffer: the buffer index of where the captured data will be saved For example 0,1
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa PhotonCaptureFrames()
  */

PHOTON_RESULT PhotonCaptureFrames(int deviceID, short captureBuffer)

{
   PROTO_SHORT buffer[PROTO_BUF_SIZE];
   PHOTON_RESULT result = CAM_OK;
   buffer[0] = PROTO_HTONS(captureBuffer);
   result = CamCallFuncTimeout(deviceID, TRANSFER_FRAME, buffer, 2, CAM_LONG_TIMEOUT);
   return result;
}

/** @} */ /* end of group */


/*
 *-------------------------------------------------
 *Video Filter Functions
 *-------------------------------------------------
 */
/*!
 *@defgroup filter Video Filter Functions
 *  Video Filter related functions.
 *  @{
 */


/*!
  * Gets the DDE filter gain.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] gain: Current DDE filter gain value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetDDEGain()
  */
PHOTON_RESULT PhotonGetDDEGain(int deviceId, short* gain)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, DDE_GAIN, 1, gain);
     return result;
}


/*!
  * Sets the DDE filter gain.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] gain: Desired DDE filter gain value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetDDEGain()
  */
PHOTON_RESULT PhotonSetDDEGain(int deviceId, short gain)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) gain >= -32768 && (int) gain <= 32767)
     {
          result = CamSetParams(deviceId, DDE_GAIN, 1, &gain);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the DDE filter threshold.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] threshold: Current DDE filter threshold value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetDDEThreshold()
  */
PHOTON_RESULT PhotonGetDDEThreshold(int deviceId, short* threshold)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, DDE_THRESHOLD, 1, threshold);
     return result;
}


/*!
  * Sets the DDE filter threshold.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] threshold: Desired DDE filter threshold value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetDDEThreshold()
  */
PHOTON_RESULT PhotonSetDDEThreshold(int deviceId, short threshold)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) threshold >= -32768 && (int) threshold <= 32767)
     {
          result = CamSetParams(deviceId, DDE_THRESHOLD, 1, &threshold);
          return result;
     }
     return CAM_RANGE_ERROR;
}


/*!
  * Gets the DDE filter spatial threshold.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] threshold: Current DDE filter spatial threshold value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetDDESpatialThreshold()
  */
PHOTON_RESULT PhotonGetDDESpatialThreshold(int deviceId, short* threshold)
{
     PHOTON_RESULT result = CAM_OK;
     result = CamGetParams(deviceId, SPATIAL_THRESHOLD, 1, threshold);
     return result;
}


/*!
  * Sets the DDE filter spatial threshold.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] threshold: Desired DDE filter spatial threshold value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetDDESpatialThreshold()
  */
PHOTON_RESULT PhotonSetDDESpatialThreshold(int deviceId, short threshold)
{
     PHOTON_RESULT result = CAM_OK;
     if ((int) threshold >= -32768 && (int) threshold <= 32767)
     {
          result = CamSetParams(deviceId, SPATIAL_THRESHOLD, 1, &threshold);
          return result;
     }
     return CAM_RANGE_ERROR;
}

/*!
  * Gets the DDE'ness factor of the Auto DDE filter. 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] value: DDE'ness factor for Auto DDE
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetDynamicDDE()
  */
PHOTON_RESULT PhotonGetDynamicDDE(int deviceId, short* value)
{
    int result = 0;

    result = CamGetParams(deviceId, SPATIAL_THRESHOLD, 1, value);
	//Mask out the DDE Mode
    *value &= 0x00FF;
    return result;
}

/*!
  * Sets the DDE'ness factor of the Auto DDE filter. 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] value: DDE'ness factor for Auto DDE
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetDynamicDDE()
  */
PHOTON_RESULT PhotonSetDynamicDDE(int deviceId, short value)
{
   short currentSpatialThreshold = 0;
	int result;
	short ddeMode;

	result = CamGetParams(deviceId, SPATIAL_THRESHOLD, 1, &currentSpatialThreshold);
	ddeMode = currentSpatialThreshold & 0xFF00; 
	value &= 0x00FF;
	//OR back the DDE mode that was originally set
	value |= ddeMode;
   return CamSetParams(deviceId, SPATIAL_THRESHOLD, 1, &value);
}

/*!
 * Gets the DDE mode - Auto or Manual.
 * @param[in] deviceId: identifies what device the calls are being sent to
 * @param[out] ddeState: Current DDE State, Auto if greater than 0 or Manual if equal to 0 
 * @return >= CAM_OK if successful or an error codes in case of an error

@sa SetDDEState()
 */
PHOTON_RESULT PhotonGetDDEState(int deviceId, short* ddeState)
{
    int result = 0;

    result = CamGetParams(deviceId, SPATIAL_THRESHOLD, 1, ddeState);
	//Mask out the Spatial Threshold
    *ddeState &= 0xFF00;
    return result;
}


/*!
  * Gets the temperature changes (High and Low Gain) needed to have the camera perform a flat field correction (FFC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] ffcTempDelta: A type used to represent 10ths of degrees celsius
  * @param[out] ffcTempDeltaLoGain: A type used to represent 10ths of degrees celsius
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMode(), SetFFCMode(), SetFFCTempDelta() PhotonGetFFCTempDeltas()
  */
PHOTON_RESULT PhotonGetFFCTempDeltas(int deviceId, PHOTON_TEMP* ffcTempDelta, PHOTON_TEMP* ffcTempDeltaLoGain)
{
     PHOTON_RESULT result = CAM_OK;
     short params[2];
     result = CamGetParams(deviceId, FFC_TEMP_DELTA, 2, (short*)params);
     *ffcTempDelta = params[0];
     *ffcTempDeltaLoGain = params[1];
     return result;
}


/*!
  * Sets the temperature change needed to have the camera perform a flat field correction (FFC).
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] ffcTempDelta: Flat field correction temperature differencce
  * @param[in] ffcTempDeltaLoGain: Low gain FFC temperature difference
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa GetFFCMode(), SetFFCMode(), GetFFCTempDelta()
  */
PHOTON_RESULT PhotonSetFFCTempDeltas(int deviceId, PHOTON_TEMP ffcTempDelta, PHOTON_TEMP ffcTempDeltaLoGain )
{
     PHOTON_RESULT result = CAM_OK;
     short params[2];
     params[0] = ffcTempDelta;
     params[1] = ffcTempDeltaLoGain;
     if ((int) ffcTempDelta >= -32768 && (int) ffcTempDelta <= 32767)
     {
         if ((int) ffcTempDeltaLoGain >= -32768 && (int) ffcTempDeltaLoGain <= 32767)
         {
            result = CamSetParams(deviceId, FFC_TEMP_DELTA, 2, params);
            return result;
         }
     }
     return CAM_RANGE_ERROR;
}


/*!
 * Sends a generic message to the camera.
 * @param[in] deviceID: identifies the device to send the messsage to
 * @param[in] functionId: identifies function the camera should perform
 * @param[in] byteCount: identifies the byte count of the camera message
 * @param[in] buffer: Data to send to the camera
 * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonGetParams()
 */
PHOTON_RESULT PhotonSetParams(int deviceID, int functionId, int byteCount, short *buffer)
{
	PHOTON_RESULT result = CamSetParams(deviceID, functionId, byteCount, buffer);
	return result;	
}


/*!
 * Gets generic data from the camera.
 * @param[in] deviceID: identifies the device to send the messsage to
 * @param[in] functionId: identifies function the camera should perform
 * @param[in] byteCount: identifies the byte count of the camera message
 * @param[out] buffer: Data to send and receive from the camera
 * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonSetParams()
 */
PHOTON_RESULT PhotonGetParams(int deviceID, int functionId, int byteCount, short *buffer)
{
	PHOTON_RESULT result = CamGetParams(deviceID, functionId, byteCount, buffer);
	return result;
}

/*!
  * Gets the camera FPA image maximum extents. Maximum number of rows and columns.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] fpaColumnExtent:  Specifies the total number of FPA image columns
  * @param[out] fpaRowExtent:  Specifies the total number of FPA image rows
  * @param[out] fpaBlindRowExtent:  Specifies the total number of FPA blind rows
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonGetParams()
  */
PHOTON_RESULT PhotonGetFPAExtents(int deviceId,short *fpaColumnExtent,short *fpaRowExtent, short *fpaBlindRowExtent)
{
   PHOTON_RESULT result = 0;

   short value[3] = {0,0,0};
   value[0] = DIGITAL_FPA_DIMENSIONS;

   result = CamSetParams(deviceId, DIGITAL_OUTPUT_MODE, 1, value);

   if( result >= 6 )
   {
      *fpaColumnExtent = value[0];
      *fpaRowExtent = value[1];
	  *fpaBlindRowExtent = value[2];
   }
   
   return(result);
}

/*!
 * Sends a generic message to the camera. Allows user to pass in timout argument
 * @param[in] deviceID: identifies the device to send the messsage to
 * @param[in] functionId: identifies function the camera should perform
 * @param[in] byteCount: identifies the byte count of the camera message
 * @param[in] buffer: Data to send to the camera
 * @param[in] timeout: Timout in msecs to wait for response
 * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonGetParamsTimeout() PhotonGetParams()
 */
PHOTON_RESULT PhotonSetParamsWithTimeout(int deviceID, int functionId, int byteCount, short *buffer, short timeout)
{
	PHOTON_RESULT result = CamSetParamsTimeout(deviceID, functionId, byteCount, buffer, timeout);
	return result;	
}

/*!
 * Gets generic data from the camera. Allows user to pass in timout argument
 * @param[in] deviceID: identifies the device to send the messsage to
 * @param[in] functionId: identifies function the camera should perform
 * @param[in] byteCount: identifies the byte count of the camera message
 * @param[out] buffer: Data to send and receive from the camera
 * @param[in] timeout: Timout in msecs to wait for response
 * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonSetParamsTimeout() PhotonSetParams()
 */
PHOTON_RESULT PhotonGetParamsWithTimeout(int deviceID, int functionId, int byteCount, short *buffer, short timeout)
{
	PHOTON_RESULT result = CamGetParamsTimeout(deviceID, functionId, byteCount, buffer, timeout);
	return result;
}
/** @} */ /* end of group */


/*!
 * Set the Communications destination id (Normally defaulted to 6E) to the cal station basket board. 
 * @param[in] destinationId: identifies the device messsages are intended for (Camera or Basket Board)
 * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonGetParamsTimeout() PhotonGetParams()
 */
PHOTON_RESULT PhotonSetBasketBoardCommDestId(CAL_DESTID destinationId)
{
	
    PHOTON_RESULT result = CAM_OK;
	int destId = 0;
	
	switch (destinationId)
	{
		case CAMERA_DEST:
			destId = PROTO_SERIALMUX_ID;
			break;
		case BASKETBOARD_DEST:
			destId = PROTO_BBLVDS_MUX_ID;
			break;
		case DEFAULT_DEST:
			destId = PROTO_DEFAULT_ID;
			break;
		default:
			destId = PROTO_DEFAULT_ID;
			break;
	}
	
	result = SetBasketBoardCommDestId(destId);
	return result;
}

/*!
 * Get the Communications destination id (Normally defaulted to 6E) to the cal station basket board. 
 * @param[out] destinationId: identifies the device messsages are intended for (Camera or Basket Board)
 * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonGetParamsTimeout() PhotonGetParams()
 */
PHOTON_RESULT PhotonGetBasketBoardCommDestId(CAL_DESTID *destinationId)
{
	
    PHOTON_RESULT result = CAM_OK;
	int destId = 0;
	
	result = GetBasketBoardCommDestId(&destId);

	switch (destId)
	{
		case CAMERA_DEST:
			*destinationId = PROTO_SERIALMUX_ID;
			break;
		case BASKETBOARD_DEST:
			destId = PROTO_BBLVDS_MUX_ID;
			break;
		case DEFAULT_DEST:
			*destinationId  = PROTO_DEFAULT_ID;
			break;
		default:
			*destinationId  = PROTO_DEFAULT_ID;
			break;
	}
	
	return result;
}


/*!
 * Set the Communications source id (Normally defaulted to 0) to the cal station basket board. 
 * @param[in] subSlotId: Index of subslot that host will communicate with
 * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonGetParamsTimeout() PhotonGetParams()
 */
PHOTON_RESULT PhotonSetBasketBoardSubSlotId(int subSlotId)
{
    PHOTON_RESULT result = SetBasketBoardCommSrcId(subSlotId);
	return result;
}

/*!
 * Get the Communications source id (Normally defaulted to 0) to the cal station basket board. 
 * @param[out] subSlotId: Index of subslot that host will communicate with
 * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonGetParamsTimeout() PhotonGetParams()
 */
PHOTON_RESULT PhotonGetBasketBoardSubSlotId(int *subSlotId)
{
    PHOTON_RESULT result = GetBasketBoardCommSrcId(subSlotId);
	return result;
}


/*!
 * Set the communications global timeout in msecs. Currently defaults to 500 msec. 
 * @param[in] timeoutInMsec: Communication timeout in milliseconds
 * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonGetComTimeout PhotonGetParamsTimeout() PhotonGetParams()
 */
PHOTON_RESULT PhotonSetComTimeout(int timeoutInMsec)
{
    PHOTON_RESULT result = SetComTimeout(timeoutInMsec);
	return result;
}

/*!
 * Get the communications global timeout value in msecs. Currently defaults to 500 msec. 
 * @param[out] timeoutInMsec: Communication timeout in milliseconds
 * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonSetComTimeout PhotonGetParamsTimeout() PhotonGetParams()
 */
PHOTON_RESULT PhotonGetComTimeout(int *timeoutInMsec)
{
    PHOTON_RESULT result = GetComTimeout(timeoutInMsec);
	return result;
}

/*!
 * Set the communications global number of retries. Currently defaults to 3. 
 * @param[in] NumOfRetries: Communication number of retries
 * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonGetNumOfRetries PhotonGetParamsTimeout() PhotonGetParams()
 */
PHOTON_RESULT PhotonSetComRetries(int NumOfRetries)
{
    PHOTON_RESULT result = SetComRetries(NumOfRetries);
	return result;
}

/*!
 * Gets the communications global number of retries. Currently defaults to 3. 
 * @param[in] NumOfRetries: Communication number of retries
 * @return >= CAM_OK if successful or an error codes in case of an error
@sa PhotonSetNumOfRetries PhotonSetParamsTimeout() PhotonSetParams()
 */
PHOTON_RESULT PhotonGetComRetries(int *NumOfRetries)
{
    PHOTON_RESULT result = GetComRetries(NumOfRetries);
	return result;
}
