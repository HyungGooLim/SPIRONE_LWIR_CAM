/****************************************************************************

  Filename:     serhost.c
  Description:  Serial Input/Output Host functions
  Created:      20-Mar-2003

  Copyright (c) 2003, Indigo Systems Corporation
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

  Neither the name of the Indigo Systems Corporation nor the names of its
  contributors may be used to endorse or promote products derived from this
  software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.

****************************************************************************/

#ifdef _WIN32
    #include <windows.h>
#else
    #include <stdio.h>
    #include <string.h>
#endif

#include "crc16.h"
#include "photondefs.h"
#include "photonComm.h"

#ifndef _NO_LOG
    #include "msglog.h"
#endif

#include "proto.h"

#define COMM_RETRIES    1
//#define BYTE    unsigned char
#define PROTO_BUF_WORDS     (PROTO_BUF_SIZE / sizeof(PROTO_SHORT))

/*
 *  ===== Global variables =====
 */
short commRetries = COMM_RETRIES;
BYTE commDstId = 0x6E;
BYTE commSrcId = 0x00;
BYTE commTry = 0x00;
int comTimeout = CAM_NORMAL_TIMEOUT;


/*
 *  Sets the destination id for messages to the remote basket board for calibration of 1cc 
 *  Returns CAM_OK or CAM_RANGE_ERROR
 */
PHOTON_RESULT SERIAL_API SetBasketBoardCommDestId(int msgDestination)
{
	if ( (msgDestination >= PROTO_BROADCAST_ID) && (msgDestination <= PROTO_BBLVDS_MUX_ID) )
	{
		commDstId = msgDestination;
		return CAM_OK;
	}
	else
	{
		return CAM_COMM_RANGE_ERROR;
	}
}

/*
 *  Sets the commSrcId (currently sub slot index) for messages to the remote basket board for calibration of 1cc 
 *  Returns CAM_OK or CAM_RANGE_ERROR
 */
PHOTON_RESULT SERIAL_API SetBasketBoardCommSrcId(int value)
{
	if ( (value >= MIN_SUBSLOT_ID) && (value <= MAX_SUBSLOT_ID) )
	{
		commSrcId = value;
		return CAM_OK;
	}
	else
	{
		return CAM_COMM_RANGE_ERROR;
	}
}

/*
 *  Sets the default communication timeout for serial messages not sent with timeout defined
 *  Returns CAM_OK 
 */
PHOTON_RESULT SERIAL_API SetComTimeout(int value)
{
	comTimeout = value;
	return CAM_OK;
}


/*
 *  Sets the communication nmber of retries for serial messages 
 *  Returns CAM_OK 
 */
PHOTON_RESULT SERIAL_API SetComRetries(int value)
{
	commRetries = value;
	return CAM_OK;
}


/*
 *  Gets the destination id for messages to the remote basket board for calibration of 1cc 
 *  Returns CAM_OK or CAM_RANGE_ERROR
 */
PHOTON_RESULT SERIAL_API GetBasketBoardCommDestId(int *msgDestination)
{
	*msgDestination = commDstId;
	if ( (commDstId >= PROTO_BROADCAST_ID) && (commDstId <= PROTO_BBLVDS_MUX_ID) )
		return CAM_OK;
	else
		return CAM_COMM_RANGE_ERROR;
}

/*
 *  Gets the commSrcId (currently sub slot index) for messages to the remote basket board for calibration of 1cc 
 *  Returns CAM_OK or CAM_RANGE_ERROR
 */
PHOTON_RESULT SERIAL_API GetBasketBoardCommSrcId(int *value)
{
	*value = commSrcId;
	if ( (commSrcId >= MIN_SUBSLOT_ID) && (commSrcId <= MAX_SUBSLOT_ID) )
		return CAM_OK;
	else
		return CAM_COMM_RANGE_ERROR;
}

/*
 *  Gets the default communication timeout for serial messages not sent with timeout defined
 *  Returns CAM_OK 
 */
PHOTON_RESULT SERIAL_API GetComTimeout(int *value)
{
	*value = comTimeout;
	return CAM_OK;
}

/*
 *  Gets the communication number of retries for serial messages 
 *  Returns CAM_OK 
 */
PHOTON_RESULT SERIAL_API GetComRetries(int *value)
{
	*value = commRetries;
	return CAM_OK;
}


/*
 *  Read a serial packet (header or data) from the camera.  Returns negative
 *  for CAM_COMM_TIMEOUT_ERROR or 16-bit unsigned CRC.
 */
PHOTON_RESULT CamReadPacketTimeout(SERIAL_PORT portNum, void* rxbuf, int count, CRC16 crc, int timeout)
{
    /* Attempt to read bytes */
    printf("\nReadCommPortTimeout function START\n");
    printf("ReadCommPortTimeout_count값:%d\n",count);
    int result = ReadCommPortTimeout(portNum, rxbuf, count, timeout);
	printf("serhost.c//ReadCommPortTimeout_수신 바이트: %d\n",result);
    printf("ReadCommPortTimeout function END\n");
    printf("\n");
    printf("result(%d)>=count(%d)\n",result,count);
    if (result >= count)
	//if(result >= CAM_OK)
    {
        printf("\nUpdateCRC16Bytes function START (Read한 값 CRC계산)\n");
		crc = UpdateCRC16Bytes(count, rxbuf, crc);
		printf("serhost.c//UpdateCRC16Bytes_crc값: %d\n",crc);
        printf("UpdateCRC16Bytes function END\n");
        printf("\n");
        return crc;
	}
	return CAM_COMM_TIMEOUT_ERROR;
}

/*
 *  Post a serial I/O Request function to the remote camera.  Returns negative (< 0)
 *  for error else CAM_OK if success.
 */
PHOTON_RESULT SERIAL_API CamPostRequest(SERIAL_PORT portNum, int func, const void* buffer, int length)
{
    int count;
    CRC16 crc;
    PROTO_SHORT txbuf[PROTO_BUF_WORDS];
    /* Support protocol extensions for NV2 1.5 Honda */
    short dstAddr = (commDstId << 8) | (commSrcId ? commTry : 0);
    short srcAddr = (commSrcId << 8) | func;

    /*  Construct the header for the message */
    txbuf[PROTO_RID_STATUS] = PROTO_HTONS(dstAddr);                 /*  Address/Process code */
    txbuf[PROTO_SID_FUNC] = PROTO_HTONS(srcAddr);                   /*  Function/Sub-function */
    txbuf[PROTO_LENGTH] = PROTO_HTONS(length);                      /*  Message length */
    crc = CalcCRC16Words(PROTO_HEADER_CRC, txbuf);                  
    printf("header_CRC:%d\n",crc);
    txbuf[PROTO_HEADER_CRC] = PROTO_HTONS(crc);                     /*  Header CRC */
    /*  Header is now complete */

    /*  Now we need to copy the parameter data to the txdata array */
    memcpy(txbuf + PROTO_DATA, buffer, length);

    /* Calculate the body CRC */
    count = length + PROTO_HEADER_BYTES;
    printf("length + PROTO_HEADER_BYTES:%d\n",count);
    crc = UpdateCRC16Bytes(count, (char*) txbuf, 0);

    ((BYTE*) txbuf)[count] = crc >> 8;
    ((BYTE*) txbuf)[count + 1] = crc;

#ifndef _NO_LOG
    LogMessage((short) func, TRUE, count, (BYTE*) txbuf);
#endif
    /* Send message to target */
    count = length + (PROTO_HEADER_BYTES + PROTO_TRAILER_BYTES);
    printf("serhost.c//count: %d\n",count);
    printf("\n");
    printf("WriteCommPort function START;\n");
    return WriteCommPort(portNum, txbuf, count);
}


/*
 *  Read a serial I/O response from the remote camera.  Returns negative (< 0)
 *  for error else byte count if success.
 */
PHOTON_RESULT SERIAL_API CamReadResponse(SERIAL_PORT portNum, int func, void* buffer, int maxLength)
{
    return CamReadResponseTimeout(portNum, func, buffer, maxLength, comTimeout);
}

PHOTON_RESULT SERIAL_API CamReadResponseTimeout(SERIAL_PORT portNum, int func, void* buffer, int maxLength, int timeout)
{
    PHOTON_RESULT result;
    PROTO_SHORT rxbuf[PROTO_BUF_WORDS];

    /* Try to read packet header */
    printf("\nCamReadPacketTimeout function START\n");
	result = CamReadPacketTimeout(portNum, rxbuf, PROTO_HEADER_BYTES, 0U, timeout);
    printf("serhost.c//CamReadPacketTimeout_crc값:%d\n",result);
    printf("CamReadPacketTimeout function END\n");
    printf("\n");
    
    if (result >= CAM_OK)
    {
		CRC16 crc1 = result; //자료형 크기 2바이트
		/*
		 * Get lengh of packet from header: note if header is corrupted
		 * timeout will resync to recover from error
		 */
		/*  This is the indicated length of the packet */
		int rxByteLength = PROTO_HTONS(rxbuf[PROTO_LENGTH]);
        printf("rxbytelength: %d\n",rxByteLength);
		/*  Check for reasonableness */
        printf("maxLength:%d\n",maxLength);
		if (rxByteLength >= 0 && rxByteLength <= maxLength)
		{
			/* Read data portion of the packet */
            printf("serhost.c//rxByteLength + sizeof(CRC16):%d\n",rxByteLength + sizeof(CRC16));
            printf("\nCamReadPacketTimeout function START \n");
			result = CamReadPacketTimeout(portNum, rxbuf + PROTO_DATA, rxByteLength + sizeof(CRC16), 0U, timeout);
            printf("serhost.c//CamReadPacketTimeout_result:%d\n",result);
            printf("\nCamReadPacketTimeout function END \n");
            printf("\n");
			if (result >= CAM_OK)
			{
                printf("11)serhost.c//CamReadPacketTimeout_(result %d >=CAM_OK %d ):\n",result,CAM_OK);
#ifndef _NO_LOG
				LogMessage((short) func, FALSE, rxByteLength + PROTO_OVERHEAD, (BYTE*) rxbuf);
#endif
                
                printf("12)serhost.c//Check the crc1 value: %d\n",crc1);

                /*  Check the crc value */
				if (crc1 == 0 && result == 0)
                //if (1)
                {
                    printf("13-1)serhost.c//crc1 == 0 && result == 0 성립\n");
                    
                    //if (func < 0 || (PROTO_HTONS(rxbuf[PROTO_SID_FUNC]) & 0xFF) == func)
                    if (1)
                    {
                        /* copy received message to buffer and return result code */
                        memcpy(buffer, rxbuf + PROTO_DATA, rxByteLength );
                        printf("rxbuf[PROTO_RID_STATUS]:%d\n",rxbuf[PROTO_RID_STATUS]);
                        result = -((rxbuf[PROTO_RID_STATUS] >> 8) & 255);
                        printf("14-1)result: %d\n",result);
                        if (result == CAM_OK)
                        {
                            result = rxByteLength;
                        }
                    }
                    else
                    {
                        result = CAM_COMM_ECHO_ERROR;
                    }
                }
                else
                {
                    printf("13-2)serhost.c//crc1 == 0 && result == 0 미성립\n");
                    printf("14-2)serhost.c//crc1 값:  %d\n",crc1);
                    printf("CRC = 0x%02X\n", crc1);  // 16진수, 올바른 표현
                    printf("15-2)serhost.c//result 값:  %d\n",result);
                    printf("CRC = 0x%02X\n", result);  // 16진수, 올바른 표현
                    result = CAM_COMM_CHECKSUM_ERROR; 
                }
            }
            else
            {
                result = CAM_COMM_TIMEOUT_ERROR;
            }
        }  /* (rxByteLength >= 0 && rxByteLength < PROTO_MAX_BYTES) */
        else 
        {
            result = CAM_COMM_COUNT_ERROR;
            printf("serhost.c//CAM_COMM_COUNT_ERROR: %d\n", result);
        }
    }  /* (rxCount >= PROTO_HEADER_BYTES) */
    else
    {
        result = CAM_COMM_TIMEOUT_ERROR;
    }
#ifndef _NO_LOG
    if (result < 0)
    {
        LogMessage((short) result, FALSE, 0, (BYTE*) rxbuf);
    }
#endif
    return result;
}


/*
 *  Call a serial I/O function on the remote camera.  Returns negative (< 0)
 *  for error else byte count if success.
 */
PHOTON_RESULT SERIAL_API CamCallFunc(SERIAL_PORT portNum, int func, signed short* buffer, int length)
{
    return CamCallFuncTimeout(portNum, func, buffer, length, comTimeout);
}

PHOTON_RESULT SERIAL_API CamCallFuncTimeout(SERIAL_PORT portNum, int func, signed short* buffer, int length, int timeout)
{
    PROTO_SHORT rxbuf[PROTO_BUF_WORDS];
    PHOTON_RESULT result = CAM_RANGE_ERROR;
	DWORD semRet = 0;

    if (portNum >= 0 && portNum < MAX_COMM_PORTS)
    {
#ifdef _WIN32
        /*
         * Critical section (only one thread allowed to 
         * send/recieve commands at once.
         */
        semRet = WaitForSingleObject(g_Semaphore[portNum], INFINITE);
#endif
        /* Retry command for reliability */
        for (commTry = 0; commTry < commRetries; ++commTry)
        {
            /* Clear out recieve FIFO */
            FlushCommPort(portNum);

            /* Send request to camera */
            printf("\nCamPostRequest function start;\n");
            result = CamPostRequest(portNum, func, buffer, length);
            printf("CamPostRequest function END\n");
            printf("\n");
            
            
            
            if (result >= 0)
            {
                printf("CamReadResponseTimeout function START\n");
                result = CamReadResponseTimeout(portNum, func, rxbuf, PROTO_BUF_SIZE, timeout);
                printf("serhost.c//CamReadResponseTimeout_result: %d\n",result);
                printf("CamReadResponseTimeout function END\n");
                printf("\n");
                
                if (result >= 0)
                {
                    /* Copy response back to caller */
                    memcpy(buffer, rxbuf, result);
                    if (commDstId == PROTO_BROADCAST_ID)
                    {
                        /* Read (and ignore) slave response */
                        result = CamReadResponseTimeout(portNum, func, rxbuf, PROTO_BUF_SIZE, timeout);
                    }
                    break;
                }
            }
#ifdef _DEBUG
            else
            {
                TCHAR szTrace[80];
                wsprintf(szTrace, "retry %d\n", commTry);
                OutputDebugString(szTrace);
            }
#endif

        }  /* End of for loop */
#ifdef _WIN32
        ReleaseSemaphore(g_Semaphore[portNum], 1, NULL);
#endif
    }
    return result;
}

#define ABS(x)      ((x) >= 0 ? (x) : -(x))

PHOTON_RESULT SERIAL_API CamSetParams(SERIAL_PORT port, int func, int count, short* param)
{
    PROTO_SHORT buffer[PROTO_BUF_WORDS];
    PHOTON_RESULT result;
    int i;


	


    for (i = 0; i < ABS(count); ++i)
    {
        buffer[i] = (count > 0) ? PROTO_HTONS(param[i]) : param[i];
    }
    result = CamCallFunc(port, func, buffer, ABS(count) * 2);
    if (result > 0 && param != NULL)
    {
        for(i = 0; i < result >> 1; ++i)
        {
            param[i] = PROTO_HTONS(buffer[i]);
        }
    }
    printf("CamSetParams_result:%d",result);
    return result;
}

PHOTON_RESULT SERIAL_API CamGetParams(SERIAL_PORT port, int func, int count, short* param)
{
    PROTO_SHORT buffer[PROTO_BUF_WORDS];
    int i, result;
    result = CamCallFunc(port, func, buffer, 0);
    if (result > 0)
    {
        for (i = 0; i < ABS(count); ++i)
        {
            param[i] = (count > 0) ? PROTO_HTONS(buffer[i]) : buffer[i];
        }
    }
    return result;
}

PHOTON_RESULT SERIAL_API CamSetParamsTimeout(SERIAL_PORT port, int func, int count, short* param, int timeout)
{
    PROTO_SHORT buffer[PROTO_BUF_WORDS];
    PHOTON_RESULT result;
    int i;

    for (i = 0; i < ABS(count); ++i)
    {
        buffer[i] = (count > 0) ? PROTO_HTONS(param[i]) : param[i];
    }
    result = CamCallFuncTimeout(port, func, buffer, ABS(count) * 2, timeout);
    if (result > 0 && param != NULL)
    {
        for(i = 0; i < result >> 1; ++i)
        {
            param[i] = PROTO_HTONS(buffer[i]);
        }
    }

    return result;
}

PHOTON_RESULT SERIAL_API CamGetParamsTimeout(SERIAL_PORT port, int func, int count, short* param, int timeout)
{
    PROTO_SHORT buffer[PROTO_BUF_WORDS];
    int i, result;
    result = CamCallFuncTimeout(port, func, buffer, 0, timeout);
    if (result > 0)
    {
        for (i = 0; i < ABS(count); ++i)
        {
            param[i] = (count > 0) ? PROTO_HTONS(buffer[i]) : buffer[i];
        }
    }
    return result;
}
