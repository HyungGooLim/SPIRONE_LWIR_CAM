#ifndef __SERHOST_H__
#define __SERHOST_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_UDP_WORDS   (1536 / sizeof(short))
    
typedef unsigned long CAM_ADDR;

extern int dongleId;

int CanInit(WORD wBTR0BTR1);

int CanGetSerialNum(SERIAL_PORT port, short ident[32]);
int LinGetSerialNum(SERIAL_PORT port, short ident[32]);
int SioGetSerialNum(SERIAL_PORT port, short ident[32]);

int CanGetVersion(SERIAL_PORT port, short vers[4]);
int LinGetVersion(SERIAL_PORT port, short vers[4]);
int SioGetVersion(SERIAL_PORT port, short vers[4]);

int CanMemReadBytes(SERIAL_PORT port, CAM_ADDR addr, int count, unsigned char* data);
int LinMemReadBytes(SERIAL_PORT port, CAM_ADDR addr, int count, unsigned char* data);
int SioMemReadBytes(SERIAL_PORT port, CAM_ADDR addr, int count, unsigned char* data);

int CanMemWriteBytes(SERIAL_PORT port, CAM_ADDR addr, int count, unsigned char* data);
int LinMemWriteBytes(SERIAL_PORT port, CAM_ADDR addr, int count, unsigned char* data);
int SioMemWriteBytes(SERIAL_PORT port, CAM_ADDR addr, int count, unsigned char* data);

int CanMemEraseBlock(short block);
int LinMemEraseBlock(short block);
int SioMemEraseBlock(short block);

int CanResetCommand(SERIAL_PORT port, short reset);
int LinResetCommand(SERIAL_PORT port, short reset);
int SioResetCommand(SERIAL_PORT port, short reset);

int CanDoFFC(SERIAL_PORT port);
int LinDoFFC(SERIAL_PORT port);
int SioDoFFC(SERIAL_PORT port);

int SERIAL_API CanSendBytes(SERIAL_PORT uPort, int id, int count, BYTE* data);
int SERIAL_API CanRequestMessage(SERIAL_PORT uPort, int id, int count, BYTE* data);
int SERIAL_API LinSendBytes(SERIAL_PORT uPort, int id, int count, BYTE* data);
int SERIAL_API LinRequestMessage(SERIAL_PORT uPort, int id, int count, BYTE* data);

void ChallengeDigest(LPBYTE pSecret, LPBYTE pChallenge, LPBYTE pDigest);

int CanAuthenticate(SERIAL_PORT port, LPBYTE pSecret, long addr);
int LinAuthenticate(SERIAL_PORT port, LPBYTE pSecret, long addr);
int SioAuthenticate(SERIAL_PORT port, LPBYTE pSecret, long addr);

#ifdef _KEY_CODE_IN
int NV3LowAuth(SERIAL_PORT port, long addr, LPBYTE secret, BYTE *pDongle, int keyCode);
#endif

int CanExecute(SERIAL_PORT port, CAM_ADDR addr);
int LinExecute(SERIAL_PORT port, CAM_ADDR addr);
int SioExecute(SERIAL_PORT port, CAM_ADDR addr);

int CanChecksumBytes(SERIAL_PORT port, CAM_ADDR addr, int count, BYTE* checksum);
int LinChecksumBytes(SERIAL_PORT port, CAM_ADDR addr, int count, BYTE* checksum);
int SioChecksumBytes(SERIAL_PORT port, CAM_ADDR addr, int count, BYTE* checksum);

long CanWritePattern(SERIAL_PORT port, CAM_ADDR addr, unsigned short words);
long LinWritePattern(SERIAL_PORT port, CAM_ADDR addr, unsigned short words);
long SioWritePattern(SERIAL_PORT port, CAM_ADDR addr, unsigned short words, short protoExtend);

long CanVerifyPattern(SERIAL_PORT port, CAM_ADDR addr, unsigned short words);
long LinVerifyPattern(SERIAL_PORT port, CAM_ADDR addr, unsigned short words);
long SioVerifyPattern(SERIAL_PORT port, CAM_ADDR addr, unsigned short words, short protoExtend);

#ifdef __cplusplus
}
#endif

#endif /* __SERHOST_H__ */
