#ifndef __PHOTONCOMM_H__
#define __PHOTONCOMM_H__
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _WIN32
    #define SERIAL_API  __stdcall
    #include <windows.h>
#else
    #define SERIAL_API
    typedef int BOOL;
    typedef unsigned long DWORD;
	typedef long LONG;
	typedef const void* LPCVOID;
	typedef void* LPVOID;
#endif

#ifndef NULL
    #define NULL          0
#endif

#include "photondefs.h"

typedef unsigned long CAM_ADDR;
typedef int SERIAL_PORT;

#define MAX_COMM_PORTS      512


/*
 *  ===== Global variables =====
 */
extern short commRetries;
#ifdef _WIN32
    extern HANDLE g_Semaphore[MAX_COMM_PORTS];
#endif

PHOTON_RESULT SERIAL_API SetBasketBoardCommDestId(int msgDestination);
PHOTON_RESULT SERIAL_API SetBasketBoardCommSrcId(int value);
PHOTON_RESULT SERIAL_API SetComTimeout(int value);
PHOTON_RESULT SERIAL_API GetBasketBoardCommDestId(int *msgDestination);
PHOTON_RESULT SERIAL_API GetBasketBoardCommSrcId(int *value);
PHOTON_RESULT SERIAL_API GetComTimeout(int *value);
PHOTON_RESULT PhotonGetComTimeout(int *timeoutInMsec);
PHOTON_RESULT SERIAL_API SetComRetries(int value);
PHOTON_RESULT SERIAL_API GetComRetries(int *value);


PHOTON_RESULT SERIAL_API CamCallFunc(int deviceId, int func, signed short* buffer, int length);
PHOTON_RESULT SERIAL_API CamCallFuncTimeout(int deviceId, int func, signed short* buffer, int length, int timeout);
PHOTON_RESULT SERIAL_API CamGetParams(int deviceId, int func, int count, short* param);
PHOTON_RESULT SERIAL_API CamSetParams(int deviceId, int func, int count, short* param);
PHOTON_RESULT SERIAL_API CamSetParamsTimeout(SERIAL_PORT port, int func, int count, short* param, int timeout);
PHOTON_RESULT SERIAL_API CamGetParamsTimeout(SERIAL_PORT port, int func, int count, short* param, int timeout);

extern int commPort;  // 전역 변수 선언
PHOTON_RESULT SERIAL_API OpenCommPort(SERIAL_PORT uPort);
LONG SERIAL_API WriteCommPort(SERIAL_PORT uPort, LPCVOID szBuffer, LONG dwCount);
LONG SERIAL_API ReadCommPort(SERIAL_PORT uPort, LPVOID szBuffer, LONG dwCount);
LONG SERIAL_API ReadCommPortTimeout(SERIAL_PORT uPort, LPVOID szBuffer, LONG dwCount, LONG dwTimeout);
BOOL SERIAL_API FlushCommPort(SERIAL_PORT uPort);
BOOL SERIAL_API CloseCommPort(SERIAL_PORT uPort);
BOOL SERIAL_API SendCommBreak(SERIAL_PORT uPort);

PHOTON_RESULT SERIAL_API CamPostRequest(SERIAL_PORT portNum, int func, const void *buffer, int length);
PHOTON_RESULT SERIAL_API CamReadResponse(SERIAL_PORT portNum, int func, void *buffer, int maxLength);
PHOTON_RESULT SERIAL_API CamReadResponseTimeout(SERIAL_PORT portNum, int func, void *buffer, int maxLength, int timeout);


#ifdef __cplusplus
}
#endif

#endif /* __PHOTONCOMM_H__ */
