#include <math.h>
#include "photonComm.h"
#include "tauFunctions.h"
#include "factoryFunctions.h"
#include "proto.h"

#define LOSHORT(x)      ((signed short) (int) (x))
#define HISHORT(x)      ((signed short) ((unsigned long) (x) >> 16))

#define MAKE_LONG(l,h)  ((long) ((unsigned short) (l) | (long) (h) << 16))


#ifdef EMBEDDED_EXPORTS
PHOTON_RESULT PhotonReadMemory(int deviceId, unsigned long addr, short byteCount, unsigned char* data)
{
    PROTO_SHORT buffer[PROTO_BUF_SIZE];
    PHOTON_RESULT result;

    PROTO_SHORT hi = HIWORD(addr);
    PROTO_SHORT lo = LOWORD(addr);
    buffer[0] = PROTO_HTONS(hi);
    buffer[1] = PROTO_HTONS(lo);
    buffer[2] = PROTO_HTONS(byteCount);

    /* Limit count to 256 */
    if (byteCount >= 256)
    {
        byteCount = 256;
    }

    result = CamCallFunc(deviceId, READ_MEMORY, buffer, 6);
    if (result >= 0)
    {
        memcpy(data, buffer, byteCount);
    }
    else
    {
        memset(data, 0xee, byteCount);
    }
    return result;
}
#endif



/*
 *-------------------------------------------------
 *TAU Functions
 *-------------------------------------------------
 */
/*!
 *@defgroup tau TAU Functions
 *  TAU related functions.
 *  @{
 */


/*!
  * Sets the thermal throttle button in the presssed up position.
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] functionId: identifies the functions id for the button state
  * @param[out] thermVal: identifies the thermal throttle value
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa Tau()
  */
PHOTON_RESULT TauSetThermalThrottleButtonState(int deviceId, CAM_BUTTON_STATE functionId, short *thermVal)
{
   PHOTON_RESULT result = 0;
   short value[2] = {0,0};
   value[0] = (short) functionId;

	result = CamSetParams(deviceId, USER_INPUT, 1, value);
   if (result >= 0)
      *thermVal = value[0];
   return result;
}

/*!
  * Returns the flash starting block and number of blocks occupied by the various flash
  * contents
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] progType: identifies what program type for the address of interest
  * @param[out] progAddr: identifies the flash address returned from the camera for the specefied program type
  * @param[out] progSizeBytes: identifies the flash size returned from the camera
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa Tau()
  */
PHOTON_RESULT TauGetProgramAddress(int deviceId, CAM_PROGRAM_TYPE progType, long *progAddr, long *progSizeBytes)
{
   PHOTON_RESULT result = 0;
   short value[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
   short hi = 0;
   short lo = 0;

   value[0] = (short)progType;
	result = CamSetParams(deviceId, GET_PROGRAM_ADDRESS, 1, value);
   if (result >= 0)
   {
      hi = value[0];
      lo = value[1];
      *progAddr = MAKELONG(lo,hi);
      //*progAddr = (value[0] << 16) | value[1];
      hi = value[2];
      lo = value[3];
      *progSizeBytes = MAKELONG(lo,hi);
      //*progSizeBytes = (value[2] << 16) |  value[3];
   }
   return result;
}

/*!
  * Sets the battery voltage thresholds for displaying the battery symbology on the camera
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] vOff: Sets the voltage threshold in volts for the shutter and video disable states
  * @param[in] v10: Sets the voltage threshold in volts for 10% symbol
  * @param[in] v25: Sets the voltage threshold in volts for 25% symbol
  * @param[in] v50: Sets the voltage threshold in volts for 50% symbol
  * @param[in] v75: Sets the voltage threshold in volts for 75% symbol
  * @param[in] v100: Sets the voltage threshold in volts for 100% symbol
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa Tau()
  */
PHOTON_RESULT TauSetBatteryThresholds(int deviceId, double vOff, double v10, double v25, double v50, double v75, double v100)
{
   PHOTON_RESULT result = 0;
   short value[6] = {0,0,0,0,0,0};
   double dVal = 0.00;
 
   value[0] = 0;                         // vOff Symbol (symbol number)
   value[1] = SYMBOL_BATTERY_VOLTAGE_THRESHHOLDS;     // Sub Command Id
   value[2] = 159;                                    // POINT x
   value[3] = 220;                                    // POINT y
   
   // Convert Voltages to shorts
   dVal = (v100 * (-198) + 595) * BATT_VOLTAGE_THRESH_SF;
   value[4] = (short)(dVal);
   value[5] = 0x0000;
	result = CamSetParams(deviceId, SYMBOL_CONTROL, 6, value);

   value[0] = 1;                             // v10 Symbol (symbol number)
   value[5] = value[4];
   // Convert Voltages to shorts
   dVal = (v75 * (-198) + 595) * BATT_VOLTAGE_THRESH_SF;
   value[4] = (short)(dVal);
	result = CamSetParams(deviceId, SYMBOL_CONTROL, 6, value);

   value[0] = 2;                             // v25 Symbol (symbol number)
   value[5] = value[4];
   // Convert Voltages to shorts
   dVal = (v50 * (-198) + 595) * BATT_VOLTAGE_THRESH_SF;
   value[4] = (short)(dVal);
	result = CamSetParams(deviceId, SYMBOL_CONTROL, 6, value);

   value[0] = 3;                            // v50 Symbol (symbol number)
   value[5] = value[4];
   // Convert Voltages to shorts
   dVal = (v25 * (-198) + 595) * BATT_VOLTAGE_THRESH_SF;
   value[4] = (short)(dVal);
	result = CamSetParams(deviceId, SYMBOL_CONTROL, 6, value);

   value[0] = 4;                            // v75 Symbol (symbol number)
   value[5] = value[4];
   // Convert Voltages to shorts
   dVal = (v10 * (-198) + 595) * BATT_VOLTAGE_THRESH_SF;
   value[4] = (short)(dVal);
	result = CamSetParams(deviceId, SYMBOL_CONTROL, 6, value);

   value[0] = 5;                          // v100 Symbol (symbol number)
   value[5] = value[4];
   // Convert Voltages to shorts
   dVal = (vOff * (-198) + 595) * BATT_VOLTAGE_THRESH_SF;
   value[4] = (short)(dVal);
	result = CamSetParams(deviceId, SYMBOL_CONTROL, 6, value);


   return CAM_OK;
}

/*!
  * Writes the current camera symbol table to flash 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa Tau()
  */
PHOTON_RESULT TauWriteSymbols(int deviceId)
{
   PHOTON_RESULT result = CAM_OK;
   short value[2] = {0,0};
   value[0] = (short)SYMBOL_WRITE; // Sub Command Id
	result = CamSetParams(deviceId, SYMBOL_CONTROL, 1, value);
   return result;
}

/*!
  * Sets the battery voltage thresholds for displaying the battery symbology on the camera
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] vOff:  Gets the voltage threshold in volts for the shutter and video disable states
  * @param[out] v10:   Gets the voltage threshold in volts for 10% symbol
  * @param[out] v25:   Gets the voltage threshold in volts for 25% symbol
  * @param[out] v50:   Gets the voltage threshold in volts for 50% symbol
  * @param[out] v75:   Gets the voltage threshold in volts for 75% symbol
  * @param[out] v100:  Gets the voltage threshold in volts for 100% symbol
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa Tau()
  */
PHOTON_RESULT TauGetBatteryThresholds(int deviceId, double *vOff, double *v10, double *v25, double *v50, double *v75, double *v100)
{
   PHOTON_RESULT result = 0;
   short value[6] = {0,0,0,0,0,0};
   value[0] = 5;                         // vOff Symbol (symbol number)
   value[1] = SYMBOL_BATTERY_VOLTAGE_THRESHHOLDS;     // Sub Command Id
   value[2] = 159;                                    // POINT x
   value[3] = 220;                                    // POINT y
	result = CamSetParams(deviceId, SYMBOL_CONTROL, 4, value);
   if (result >= 0)
   {
      *vOff = (double)(value[0]/BATT_VOLTAGE_THRESH_SF - (double)595) / (double)(-198);
      *v10 =  (double)(value[1]/BATT_VOLTAGE_THRESH_SF - (double)595) / (double)(-198);
   }

   
   value[0] = 3;                            // vOff Symbol (symbol number)
   value[1] = SYMBOL_BATTERY_VOLTAGE_THRESHHOLDS;     // Sub Command Id
   value[2] = 159;                                    // POINT x
   value[3] = 220;                                    // POINT y
	result = CamSetParams(deviceId, SYMBOL_CONTROL, 4, value);
   if (result >= 0)
   {
      *v25 = (double)(value[0]/BATT_VOLTAGE_THRESH_SF - (double)595) / (double)(-198);
      *v50 = (double)(value[1]/BATT_VOLTAGE_THRESH_SF - (double)595) / (double)(-198);
   }


   value[0] = 1;                            // vOff Symbol (symbol number)
   value[1] = SYMBOL_BATTERY_VOLTAGE_THRESHHOLDS;     // Sub Command Id
   value[2] = 159;                                    // POINT x
   value[3] = 220;                                    // POINT y
	result = CamSetParams(deviceId, SYMBOL_CONTROL, 4, value);
   if (result >= 0)
   {
      *v75 = (double)(value[0]/BATT_VOLTAGE_THRESH_SF - (double)595) / (double)(-198);
      *v100 = (double)(value[1]/BATT_VOLTAGE_THRESH_SF - (double)595) / (double)(-198);
   }

   return result;
}

/*!
  * 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] fpaType: Current plateau value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa TauSetFPAType()
  */
PHOTON_RESULT TauGetFPAType(int deviceId, short* fpaType)
{
     PHOTON_RESULT result;
     result = CamGetParams(deviceId, FPA_PARAMS, 1, fpaType);
     return result;
}


/*!
  * 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] fpaType: Desired plateau value
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa TauGetFPAType()
  */
PHOTON_RESULT TauSetFPAType(int deviceId, short  fpaType)
{
     PHOTON_RESULT result;
     result = CamSetParams(deviceId, FPA_PARAMS, 1, (short*)&fpaType);
     return result;
}

/*!
  * 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] address: Address of captured image
  * @param[in] width: Row width of captured image
  * @param[out] addrIncr: Address increment for next row read of captured image
  * @param[in, out] pixBuff: 14 bit decompressed video data for captured image
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa TauSetFPAType() TauGetFPAType()
  */
PHOTON_RESULT TauReadCaptureImage(int deviceId, unsigned long address, short width, long *addrIncr, short pixBuff[])
{
   PHOTON_RESULT result;
   short line[320];
   short pixBuff1[160];
   short bytes = 320;
   int ii = 0;

   for (ii = 0; ii < 320; ii += 64)
   {
      //Read photon memory to get the image data from flash
      result = PhotonReadMemory(deviceId, address+ii, 64, (unsigned char*)line + ii);
   }

    bytes = expand_line((unsigned char*) line, pixBuff1, bytes);

    memcpy(pixBuff,pixBuff1,160);


    *addrIncr = bytes = (bytes + 1) & ~1;
    return result;
}

/*!
  * 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] symbolData: Symbol data to be modified for a given symbol
  * @param[in] symbolDataSize: Symbol data buffer size
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa TauGetFPAType()
*/
PHOTON_RESULT TauSetUserSymbolData(int deviceId, short symbolData[], short symbolDataSize)
{
   PHOTON_RESULT result = 0;
	result = CamSetParams(deviceId, SYMBOL_CONTROL, symbolDataSize, symbolData);
   return result;
}


/*!
  * 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] nuc: Cal table index
  * @param[in] type: Cal table type
  * @param[out] addr: Cal table flash address
  * @param[out] size: Cal table flash size
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa TauGetFPAType()
*/
PHOTON_RESULT TauGetNucAddress(int deviceId, int nuc, int type, unsigned long* addr, int *size)
{
    short buffer[8];
    PHOTON_RESULT result = 0;
    unsigned long camAddr = 0;
	int camSize = 0;
    short hi = 0;
    short lo = 0;

    buffer[0] = nuc;
    buffer[1] = type;

    result = CamSetParams(deviceId, GET_NUC_ADDRESS, 2, buffer);
    if (result >= 0)
    {
        hi = buffer[0];
        lo = buffer[1];
        camAddr = MAKELONG(lo,hi);
        if (camAddr == 0L)
            return -CAM_RANGE_ERROR;
        *addr =  camAddr;
		hi = buffer[2];
		lo = buffer[3];
		camSize = MAKELONG(lo,hi);
		*size = camSize;
    }
    return result;
}

/*!
  * 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] nucIndex: Index of nuc table  DRAM_GAIN_INDEX = 0, DRAM_LAGRANGE_INDEX = 1, DRAM_OFFSET_INDEX = 2
  * @param[in] offsetHi: Offset into Cal table (high word) 
  * @param[in] offsetLo: Offset into Cal table (low word)
  * @param[in] dataLen: Size of data (in bytes) to be read
  * @param[out] data: Nuc table data to be read
  * @return >= CAM_OK if successful or an error codes in case of an error

@sa TauWriteDramNuc()
*/
PHOTON_RESULT TauReadDramNuc(int deviceId, short nucIndex, short offsetHi, short offsetLo, short dataLen, unsigned char *data)
{
	short buffer[130];
	PHOTON_RESULT result = CAM_OK;
	buffer[0] = nucIndex;
	buffer[1] = offsetHi;
	buffer[2] = offsetLo;
    /* Limit count to 256 */
    if (dataLen>= 256)
    {
        dataLen = 256;
    }
	buffer[3] = dataLen;

	result = CamSetParams(deviceId, READ_DRAM_NUC, 4, buffer);

    if (result >= 0)
    {
        memcpy(data, buffer, dataLen);
    }
    else
    {
        memset(data, 0xee, dataLen);
    }
    return result;
}

/*!
  * 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] nucIndex: Index of nuc table  DRAM_GAIN_INDEX = 0, DRAM_LAGRANGE_INDEX = 1, DRAM_OFFSET_INDEX = 2
  * @param[in] offsetHi: Offset into Cal table (high word) 
  * @param[in] offsetLo: Offset into Cal table (low word)
  * @param[in] dataLen: Size of data (in bytes) to be written
  * @param[in] data: Nuc table data to be written
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa TauReadDramNuc()
*/
PHOTON_RESULT TauWriteDramNuc(int deviceId, short nucIndex, short offsetHi, short offsetLo, short dataLen, unsigned char *data)
{
	short buffer[160];
	PHOTON_RESULT result = CAM_OK;
	buffer[0] = nucIndex;
	buffer[1] = offsetHi;
	buffer[2] = offsetLo;
    /* Limit count to 256 */
    if (dataLen>= 256)
    {
        dataLen = 256;
    }

	memcpy(buffer + 3, data, dataLen);
	result = CamSetParamsTimeout(deviceId, WRITE_DRAM_NUC, (dataLen+6)/2, buffer, 12000);
    return result;
}

/*!
  * 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] row: Gain table row to set input value
  * @param[in] column: Gain table ciolumn to set input value
  * @param[in] totalColumns: Total number of columns for this FPA
  * @param[in] pixelValue: Value to be written to row.column coordinate in gain table
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa TauWriteDramNuc() TauReadDramNuc()
*/
PHOTON_RESULT TauSetPixelGain(int deviceId, short row, short column, short totalColumns, short pixelValue)
{
	short buffer[10];
	long offset = 0;

	PHOTON_RESULT result = CAM_OK;
	buffer[0] = (short)0;

	offset = row * totalColumns + column;

	buffer[1] = HIWORD(offset);
	buffer[2] = LOWORD(offset);

	memcpy(&buffer[3], &pixelValue, 2);
	result = CamSetParams(deviceId, WRITE_DRAM_NUC, 4, buffer);
    return result;
}

/*!
  * 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] buffer: Gain table buffer data to write to flash 0 writes current NUC data
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa TauWriteDramNuc() TauReadDramNuc()
*/
PHOTON_RESULT TauWriteGainTable(int deviceId, short buffer)
{
	int counter = 0;
	short param = 0;
	PHOTON_RESULT result = CAM_OK;
	
	if (buffer > 0)
		result = CamSetParams(deviceId, WRITE_GAIN_TABLE, 1, (short*)&buffer);
	else
		result = CamSetParams(deviceId, WRITE_GAIN_TABLE, 0, NULL);

	do
	{
		result = CamGetParams(deviceId, FLASH_STATUS, 1, &param);
		 if(result < 0)
			 break;
		 if (counter++ > 1000)
			 break;
		 Sleep(100);
	} while(param > 0);

	result = param;
	return result;
}

/*!
  * 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] row: Gain table row to set input value
  * @param[in] column: Gain table ciolumn to set input value
  * @param[in] totalColumns: Total number of columns for this FPA
  * @param[in] badPixelFlag: Flag to set or clear bad pixel 0=clear bad pixel non zero = use this pixel
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa TauSetPixelGain() TauWriteDramNuc() TauReadDramNuc()
*/
PHOTON_RESULT TauSetBadPixel(int deviceId, short row, short column, short totalColumns, short badPixelFlag)
{
	short buffer[10];
	long offset = 0;
	short data;

	PHOTON_RESULT result = CAM_OK;

	offset = row * totalColumns + column;
	buffer[0] = (short)0;
	buffer[1] = HIWORD(offset);
	buffer[2] = LOWORD(offset);
	buffer[3] = 4;

	result = CamSetParams(deviceId, READ_DRAM_NUC, 4, buffer);

    if (result >= 0)
    {
        memcpy(&data, buffer, sizeof(short));
    }
    else
    {
        memset(&data, 0xee, sizeof(short));
    }

	if (badPixelFlag)
		data &= ~0x8000;
	else
		data |= 0x8000;

	buffer[0] = (short)0;
	buffer[1] = HIWORD(offset);
	buffer[2] = LOWORD(offset);

	memcpy(&buffer[3], &data, 2);
	result = CamSetParams(deviceId, WRITE_DRAM_NUC, 4, buffer);
    return result;
}


/*!
  * 
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] row: Gain table row to set input value
  * @param[in] column: Gain table ciolumn to set input value
  * @param[in] totalColumns: Total number of columns for this FPA
  * @param[in] badPixelFlag: Flag to set or clear bad pixel 1= pixel is bad zero = use this pixel
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa TauSetPixelGain() TauWriteDramNuc() TauReadDramNuc()
*/
#define MAX_BADPIXEL_WORDS 41
PHOTON_RESULT TauSetBadPixelNew(int deviceId, short row, short column, short badPixelFlag)
{
	short buffer[MAX_BADPIXEL_WORDS];
	short dataLength = 0;
	short index = 0;
	short bitMask = 0;
	short bitLoc = 0;
	PHOTON_RESULT result = CAM_OK;
	buffer[1] = row;
	result = CamSetParams(deviceId, PIXEL_GAIN, 1, &buffer[1]);
 

	// RJT TODO: Add column range check based upon return value (contains width of row) vs FPA width from camera
    if (result >= 0)
    {
		// Locate the index of our row buffer where we want to set the bad pixel
		// We add 1 to this index because we need to reserve the first 16 bits for a row number value
		// It would have been cleaner had Mr.Lennie just send the row number to us in the above call.
		index = 1 + (column / 16);
		// Locate the bit to set/reset
		bitLoc = 15 - (column % 16);

		bitMask = pow((double)2, (double)bitLoc);
		
		// Update the pixel in the packed pixel map to the new pixel flag value
		// We have the whole row of packed pixel data in the buffer
		if (badPixelFlag)
			buffer[index] &= ~bitMask;
		else
			buffer[index] |= bitMask;
	

		// Set the row# in the first 2 bytes
		buffer[0] = row;
		// The data length needs to accomodate the row # addition
		dataLength = (result / 2) + 1;
		result = CamSetParams(deviceId, PIXEL_GAIN, dataLength, buffer);
	}

    return result;
}




/*!
  * Gets the currently selected lens number (currently 0 or 1)
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[out] lensNumber
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa TauSetLensNumber TauWriteFFCOffsetForLens
*/
PHOTON_RESULT TauGetLensNumber(int deviceId, short *lensNumber)
{
	 PHOTON_RESULT result = CamGetParams(deviceId, LENS_NUMBER, 1, lensNumber);
	 return result;
}

/*!
  * Gets the desired lens number (currently 0 or 1)
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] lensNumber
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa TauGetLensNumber TauWriteFFCOffsetForLens
*/
PHOTON_RESULT TauSetLensNumber(int deviceId, short lensNumber)
{
	 PHOTON_RESULT result = CamSetParams(deviceId, LENS_NUMBER, 1, (short*)&lensNumber);
	 return result;
}

/*!
  * Writes the FFC Offset table to flash for a given lens number. Desired lens number should be set prior to setting this command
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa SetLensNumber GetLensNumber
*/
PHOTON_RESULT TauWriteFFCOffsetForLens(int deviceId)
{
	int counter = 0;
	short param = 0;
	PHOTON_RESULT result = CamCallFuncTimeout(deviceId, WRITE_NVFFC_OFFSET_TABLE, &param, 0, CAM_LONG_TIMEOUT);
	if(result < 0)
		return (PHOTON_RESULT) result;
	do
	{
		result = CamGetParams(deviceId, FLASH_STATUS, 1, &param);
		 if(result < 0)
			 break;
		 if (counter++ > 300)
			 break;
		 Sleep(100);
	} while(param > 0);
    result = param;
	return result;
}

/*!
  * Sets temperature thresholds for supplemntal offset processing
  * @param[in] deviceId: identifies what device the calls are being sent to
  * @param[in] ROCZero:  Rate of change zero temperature threshold in counts
  * @param[in] ROCEighth:  Rate of change 1/8 temperature threshold in counts
  * @param[in] ROCQuarter:  Rate of change 1/4 temperature threshold in counts
  * @param[in] ROCThreeEighth:  Rate of change 3/8 temperature threshold in counts
  * @param[in] ROCHalf:  Rate of change 1/2 temperature threshold in counts
  * @param[in] ROCFiveEighth:  Rate of change 5/8temperature threshold in counts
  * @param[in] ROCThreeFourth:  Rate of change 3/4 temperature threshold in counts
  * @param[in] ROCSevenEighth:  Rate of change 7/8 temperature threshold in counts
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa TauGetExtOffsetTempThresholds() 
*/
PHOTON_RESULT TauSetExtOffsetTempThresholds(int deviceId, short ROCZero, short ROCEighth, short ROCQuarter, short ROCThreeEighth, short ROCHalf, short ROCFiveEighth, short ROCThreeFourth, short ROCSevenEighth)
{
	PHOTON_RESULT result = CAM_OK;
	short buffer[10];
	buffer[0] = ROCZero;
	buffer[1] = ROCEighth;
	buffer[2] = ROCQuarter;
	buffer[3] = ROCThreeEighth;
	buffer[4] = ROCHalf;
	buffer[5] = ROCFiveEighth;
	buffer[6] = ROCThreeFourth;
	buffer[7] = ROCSevenEighth;

	result = CamSetParams(deviceId, CALC_EXTOFFSET, 8, buffer);
	return result;
}


/*!
  * Sets temperature thresholds for supplemntal offset processing
  * @param[out] deviceId: identifies what device the calls are being sent to
  * @param[out] ROCZero:  Rate of change zero temperature threshold in counts
  * @param[out] ROCEighth:  Rate of change 1/8 temperature threshold in counts
  * @param[out] ROCQuarter:  Rate of change 1/4 temperature threshold in counts
  * @param[out] ROCThreeEighth:  Rate of change 3/8 temperature threshold in counts
  * @param[out] ROCHalf:  Rate of change 1/2 temperature threshold in counts
  * @param[out] ROCFiveEighth:  Rate of change 5/8temperature threshold in counts
  * @param[out] ROCThreeFourth:  Rate of change 3/4 temperature threshold in counts
  * @param[out] ROCSevenEighth:  Rate of change 7/8 temperature threshold in counts
  * @return >= CAM_OK if successful or an error codes in case of an error
@sa TauGetExtOffsetTempThresholds() 
*/
PHOTON_RESULT TauGetExtOffsetTempThresholds(int deviceId, short *ROCZero, short *ROCEighth, short *ROCQuarter, short *ROCThreeEighth, short *ROCHalf, short *ROCFiveEighth, short *ROCThreeFourth, short *ROCSevenEighth)
{
	PHOTON_RESULT result = CAM_OK;
	short buffer[10];
	buffer[0] = GET_EXTOFF_DELTA_TEMPS;

	result = CamSetParams(deviceId, CALC_EXTOFFSET, 1, buffer);

	// Set return arguments to camera return parameters only if result is not an error
	if (result >= 0)
	{
		*ROCZero = buffer[0];
		*ROCEighth = buffer[1];
		*ROCQuarter = buffer[2];
		*ROCThreeEighth = buffer[3];
		*ROCHalf = buffer[4];
		*ROCFiveEighth = buffer[5];
		*ROCThreeFourth = buffer[6];
		*ROCSevenEighth = buffer[7];
	}
	// If error code is returned from camera, set all return arguments to 0xFFFF
	else
	{
		*ROCZero = (short)0xFFFF;
		*ROCEighth = (short)0xFFFF;
		*ROCQuarter = (short)0xFFFF;
		*ROCThreeEighth = (short)0xFFFF;
		*ROCHalf = (short)0xFFFF;
		*ROCFiveEighth = (short)0xFFFF;
		*ROCThreeFourth = (short)0xFFFF;
		*ROCSevenEighth = (short)0xFFFF;
	}

	return result;
}


PHOTON_RESULT TauGetGainSwitchParams(int deviceId, TAU_GAIN_SWITCH_PARAMS* gainSwitchParams)
{
     PHOTON_RESULT result;
     short param[6];
     result = CamGetParams(deviceId, GAIN_SWITCH_PARAMS, 6, (short*)param);
     gainSwitchParams->HiLoThresh = param[0];
     gainSwitchParams->HiLoPOP = param[1];
     gainSwitchParams->LoHiThresh = param[2];
     gainSwitchParams->LoHiPOP = param[3];
	 gainSwitchParams->MedThresh = param[4];
	 gainSwitchParams->MedPOP = param[5];
     return result;
}

PHOTON_RESULT TauSetGainSwitchParams(int deviceId, TAU_GAIN_SWITCH_PARAMS gainSwitchParams)
{
     PHOTON_RESULT result;
     short param[6];
     if (((int) gainSwitchParams.HiLoThresh >= -32768 && (int) gainSwitchParams.HiLoThresh <= 32767) && 
         ((int) gainSwitchParams.HiLoPOP >= -32768 && (int) gainSwitchParams.HiLoPOP <= 32767) && 
         ((int) gainSwitchParams.LoHiThresh >= -32768 && (int) gainSwitchParams.LoHiThresh <= 32767) && 
         ((int) gainSwitchParams.LoHiPOP >= -32768 && (int) gainSwitchParams.LoHiPOP <= 32767) &&
         ((int) gainSwitchParams.MedPOP >= -32768 && (int) gainSwitchParams.MedPOP <= 32767) &&
         ((int) gainSwitchParams.MedThresh >= -32768 && (int) gainSwitchParams.MedThresh <= 32767))
     {
          param[0] = gainSwitchParams.HiLoThresh;
          param[1] = gainSwitchParams.HiLoPOP;
          param[2] = gainSwitchParams.LoHiThresh;
          param[3] = gainSwitchParams.LoHiPOP;
          param[4] = gainSwitchParams.MedThresh;
          param[5] = gainSwitchParams.MedPOP;
          result = CamSetParams(deviceId, GAIN_SWITCH_PARAMS, 6, param);
          return result;
     }
     return CAM_RANGE_ERROR;
}

PHOTON_RESULT TauCalculateFrameDiff(int deviceId, short diffFrame, short hotFrame, short coldFrame)
{
     PHOTON_RESULT result;
     short param[3];

	 param[0] = CALC_FRAME_DIFF;
	 param[1] = diffFrame;  // diff frame argument
	 param[2] = hotFrame;   // hot frame argument
	 param[3] = coldFrame;  // cold frame argument

	 //result = CamSetParams(deviceId, CALC_GAIN, 4, param);
	 result = CamCallFuncTimeout(deviceId, CALC_GAIN, param, 8, CAM_LONG_TIMEOUT);

	 return result;
}

PHOTON_RESULT TauCalculateGainFrame(int deviceId, short gainFrame, short diffFrame, short average)
{
     PHOTON_RESULT result;
     short param[3];

	 param[0] = CALC_GAIN_FRAME;
	 param[1] = gainFrame;		// gain frame argument
	 param[2] = diffFrame;		// diff frame argument
	 param[3] = average;		// average frame argument

	 //result = CamSetParams(deviceId, CALC_GAIN, 4, param);
	 result = CamCallFuncTimeout(deviceId, CALC_GAIN, param, 8, CAM_LONG_TIMEOUT);

	 return result;
}

PHOTON_RESULT TauFindBadPixels(int deviceId, short gainFrame, short minPixelGain, short maxPixelGain)
{
     PHOTON_RESULT result;
     short param[3];

	 param[0] = FIND_BAD_PIXELS;
	 param[1] = gainFrame;		// gain frame argument
	 param[2] = minPixelGain;		// diff frame argument
	 param[3] = maxPixelGain;		// average frame argument

	 //result = CamSetParams(deviceId, CALC_GAIN, 4, param);
	 result = CamCallFuncTimeout(deviceId, CALC_GAIN, param, 8, CAM_LONG_TIMEOUT);

	 return result;
}


PHOTON_RESULT TauGetBaudRate(int deviceId, short *baudRate)
{
	 PHOTON_RESULT result = CamGetParams(deviceId, BAUD_RATE, 0, baudRate);
	 return result;
}

PHOTON_RESULT TauSetBaudRate(int deviceId, short baudRate)
{
	 PHOTON_RESULT result = CamSetParams(deviceId, BAUD_RATE, 1, &baudRate);
	 return result;
}

PHOTON_RESULT TauCalculateGain(int deviceId)
{
   PHOTON_RESULT result;
   short param;
   result = CamSetParams(deviceId, CALC_GAIN, 0, &param);
   return result;
}

// To write Lens Table, buffer should be equal to -2 (CAM_LENS_GAIN enum, tableNum should be 0 or 1)
// If buffer is not equal to -2, then it represents the g_frame buffer index (see NUC_COEFF_INDEX)
PHOTON_RESULT TauWriteGainTableNew(int deviceId, short buffer, short tableNum)
{
	PHOTON_RESULT result;
	int counter = 0;
	short param = 0;
	short params[2];
	params[0] = buffer;
	params[1] = tableNum;
	
	result = CamSetParams(deviceId, WRITE_GAIN_TABLE, 2, params);

	do
	{
		result = CamGetParams(deviceId, FLASH_STATUS, 1, &param);
		 if(result < 0)
			 break;
		 if (counter++ > 1000)
			 break;
		 Sleep(100);
	} while(param > 0);

	result = (PHOTON_RESULT)param;
	return result;
}

PHOTON_RESULT TauGetFlashStatus(int deviceId, short *status)
{
   PHOTON_RESULT result;
   result = CamGetParams(deviceId, FLASH_STATUS, 1, status);
   return result;
}

/** @} */ /* end of group */


/*
 *  ===== expand_line =====
 *      Expand line of compressed data back into 14-bit pixels.
 *   _______________________________
 *  |0 0|       14-bit pixel        |
 *  |_._|_._._._._._._._._._._._._._|
 *   _______________
 *  |0 1|3-bit|3-bit|
 *  |_._|_|_|_|_|_|_|
 *   _______________
 *  |1|   7-bit     |
 *  |_|_._._._._._._|
 *
 *  Returns number of bytes read from input (variable 25% - 100%)
 */
int expand_line(unsigned char* inp, short* out, int count)
{
    int pixel = PIXEL_DEFAULT;
    int bytes = 0;

    while (count > 0)
    {
        short code = inp[bytes++];
        if (code & 0x80)
        {
            pixel = pixel + (code & 0x7F) - 64;
#if 0
            ++diff7;
#endif
        }
        else if (code & 0x40)
        {
            pixel = pixel + ((code >> 3) & 7) - 4;
            out[0] = pixel;
            ++out;
            count -= 2;
            pixel = pixel + (code & 7) - 4;
#if 0
            diff3 += 2;
#endif
        }
        else
        {
            pixel = (code << 8) | inp[bytes++];
#if 0
            ++diff14;
#endif
        }
        out[0] = pixel;
        ++out;
        count -= 2;
    }
    return bytes;
}
