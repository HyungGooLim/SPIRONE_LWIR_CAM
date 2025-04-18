/****************************************************************************

  Filename:     HexFile.h
  Description:  Hex File Parsing functions for Motorola S-Record and Intel Hex
  Created:      10-Dec-2002

  Copyright (c) 2002-2003, Indigo Systems Corporation
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

#include <stdio.h>
#include <memory.h>
#include <string.h>


#ifndef __HEXFILE_H__
#define __HEXFILE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define HEX_FILE_BYTES   256
#define HEX_LINE_BUF     (HEX_FILE_BYTES*2+20)

typedef unsigned char HEX_BYTE;
typedef unsigned long HEX_ADDR;

typedef struct
{
    HEX_ADDR addr;
    HEX_BYTE buffer[HEX_FILE_BYTES];
    HEX_ADDR base;
    int length;
    int type;
} HEX_RECORD;

typedef enum
{
    HEX_END_ERROR = -7,
    HEX_CHECKSUM_ERROR = -6,
    HEX_DATA_ERROR = -5,
    HEX_ADDR_ERROR = -4,
    HEX_LENGTH_ERROR = -3,
    HEX_FORMAT_ERROR = -2,
    HEX_ERROR = -1,
    HEX_DONE = 0,
    HEX_DATA = 1,
    HEX_OTHER = 2,
    HEX_ABORT = 3,
} HEX_RESULT_CODE;

typedef int (*HEXWRITEFUNC)(int /*port*/, HEX_ADDR /*addr*/, int /*length*/, HEX_BYTE* /*buffer*/);
typedef int (*HEXPROGRESSFUNC)(int /*port*/, long pos, long total, void* object);

/* Parsing functions */
int ParseHexDigit(const char ch);
long ParseHexLong(const char* line);
long ParseHexWord(const char* line);
int ParseHexByte(const char * line);
int ParseMotorolaSRecord(const char * line, HEX_RECORD* record);
int ParseIntelHex(const char * line, HEX_RECORD* record);
int ParseHexLine(const char * line, HEX_RECORD* record);
int LoadBinaryFile(int port, const char* filename, long offset, HEXWRITEFUNC func, HEXPROGRESSFUNC progress, void* object);
int LoadTextFile(int port, const char* filename, long offset, HEXWRITEFUNC func, HEXPROGRESSFUNC progress, void* object, long bufsize);
int LoadHexFile(int port, const char* filename, long offset, HEXWRITEFUNC func, HEXPROGRESSFUNC progress, void* object);

/* Write functions */
int WriteIntelHex(FILE* fout, void* buf, unsigned int offset, int count);
int WriteIntelEnd(FILE* fout);

#ifdef __cplusplus
}
#endif

#endif /* __HEXFILE_H__ */
