/****************************************************************************

  Filename:     proto.h
  Description:  Serial Protocol definition
  Created:      15-Jan-2003

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

#ifndef __PROTO_H__
#define __PROTO_H__

typedef signed short PROTO_SHORT;
typedef signed long PROTO_LONG;

/*
 *      The serial protocol uses a binary format with crc for efficiency
 *  and reliability:
 *   _______ _______ _______ _______ ______...______ _______
 *  |       |       |       |       |               |       |
 *  |rid/st |sid/fun|length |hdr-crc|     data      |  crc  |
 *  |___|___|___|___|___|___|_______|______...______|___|___|
 */
typedef enum
{
    PROTO_RID_STATUS = 0,
    PROTO_SID_FUNC = 1,
    PROTO_LENGTH = 2,
    PROTO_HEADER_CRC = 3,
    PROTO_DATA = 4,
    PROTO_HEADER_BYTES = PROTO_DATA * 2,
    PROTO_TRAILER_BYTES = 2,
#if defined(_FLIR) || defined(_WIN32)
    PROTO_MAX_BYTES = 502,
#elif defined(_TAU) || defined(_NV3) || defined(_EASIC)
    PROTO_MAX_BYTES = 262,
#else
    PROTO_MAX_BYTES = 260,
#endif
    PROTO_RESPONSE_BYTES = 32,
    PROTO_BUF_SIZE = PROTO_HEADER_BYTES + PROTO_MAX_BYTES + PROTO_TRAILER_BYTES,
    PROTO_OVERHEAD = PROTO_HEADER_BYTES + PROTO_TRAILER_BYTES,
	PROTO_MAX_COUNT = 32767
} PROTO_INDEX;

#define PROTO_DEFAULT_ADDR  0x6E00
#define PROTO_NV3_RESPONSE  0x7000

#define PROTO_BROADCAST_ID  0x00
#define PROTO_DEFAULT_ID    0x6E
#define PROTO_ECU_ID        0x6F
#define PROTO_MASTER_ID     0x70
#define PROTO_SLAVE_ID      0x71

/* id for calibration basket board mux controller 
*/
#define PROTO_SERIALMUX_ID	0x72    // Routes message to camera
#define PROTO_BBLVDS_MUX_ID 0x73    // Routes message to LVDS Basket Board (Pleora Select for now) 

#define MIN_SUBSLOT_ID		0
#define MAX_SUBSLOT_ID		4

#ifdef _TARGET_BIG_ENDIAN
    #define PROTO_HTONS(x)  ((short) ((((x & 255) << 8) | ((x) >> 8) & 255)))
#else
    #define PROTO_HTONS(x)  ((short) (x))
#endif

#endif /* __PROTO_H__ */
