#ifdef _WIN32
    #include <windows.h>
#else
    #include <stdio.h>
    #define TRUE  1
    #define FALSE 0
    #define SERIAL_API
#endif

#include "photonComm.h"

/*
 *-------------------------------------------------
 *Comm Functions
 *-------------------------------------------------
 */
/*!
 *@defgroup comm Communication Port Functions
 *  Communication Port related functions.  These 6 functions implement a device
 *  driver interface which must be customized for each application as they are
 *  operating system and/or target dependent. They support multiple ports
 *  primarily for a host communication controller.  For embedded environments
 *  (which typically have only one port the uPort parameter can be either error
 *  checked for COM1 or ignored).
 *  @{
 */

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int commPort;
struct termios my_termios;

/*!
  * Function for opening a communication port.  This function is called before
  * any of the other functions to open the communications port.
  *
  * @param[in] uPort: The index of the communication port.
  * @return CAM_OK if successful or one of the error codes defined by the enum PHOTON_RESULT.
  */

PHOTON_RESULT SERIAL_API OpenCommPort(SERIAL_PORT uPort)
{
     int res;
     char device[80];
     speed_t ispeed, ospeed;

     sprintf(device, "/dev/ttyUSB%d", uPort);

     commPort = open(device, O_NONBLOCK | O_RDWR);
     //commPort = open(device, O_RDWR | O_NOCTTY | O_SYNC);
     //commPort = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK | O_SYNC);
     
     printf("1)commPort address on serstub.c: %d\n",&commPort);
     printf("2)commPort on serstub.c: %d\n",commPort);

     if (commPort < 0)
     {
          return CAM_ERROR_CREATING_COMM;
     }	

     res = tcgetattr ( commPort, &my_termios); 

     cfsetispeed(&my_termios, B921600);
     cfsetospeed(&my_termios, B921600);
     // Serial 기존 파라미터 //
     my_termios.c_cflag &= ~CS7;
     my_termios.c_cflag |= CS8;
     // my_termios.c_iflag |= IXANY;
     // Serial 기존 파라미터 //

     // 추가한 파라미터 //
     //my_termios.c_cflag = 0;
     //my_termios.c_cflag &= ~CS7;
     //my_termios.c_cflag |= CS8;
     my_termios.c_cflag &= ~(PARENB);
     
     // my_termios.c_iflag |= IGNBRK;
     // my_termios.c_iflag &= ~(BRKINT | ICRNL | INLCR | IGNCR | IXON | IXOFF | IXANY | PARMRK | ISTRIP);
     // my_termios.c_iflag |= IGNPAR;
     my_termios.c_iflag = 0;
     my_termios.c_iflag = IGNBRK | IGNPAR;

     my_termios.c_lflag = 0;
     my_termios.c_oflag = 0;        // 출력 플래그: 원시 모드(raw mode)


     // // Serial 파라미터 수정 //
     //  my_termios.c_cflag = (my_termios.c_cflag & ~CSIZE) | CS8;
     //  my_termios.c_cflag |= (CLOCAL | CREAD);
     //  my_termios.c_cflag &= ~(PARENB | PARODD);
     //  my_termios.c_iflag &= ~CSTOPB;
     //  #ifdef CRTSCTS
     //  my_termios.c_cflag &= ~CRTSCTS;  // 하드웨어 흐름 제어 비활성화 (정의되어 있을 때만)
     //  #endif

     // // 입력 플래그: 브레이크 처리 끄기, XON/XOFF 비활성화
     //my_termios.c_iflag &= ~(IXON | IXOFF | IXANY);
     // flow control 해제, CR/NL 변환 해제, 패리티 마크 삽입 방지
     // my_termios.c_iflag |= IGNPAR;  // 패리티 오류 바이트 무시

    
     // 로컬 플래그: 캐노니컬 모드 해제, 에코 비활성화 등
     // my_termios.c_lflag &= ~ICANON; // 캐노니컬로 하면 막힘 (하지만, 기존의 문제의 원인은 아님)
     // my_termios.c_lflag = 0;
     // // // 출력 플래그: 원시 모드(raw mode)
     // my_termios.c_oflag = 0;

     // //읽기 관련 타임아웃 설정: 최소 읽기 바이트 수 0, 타임아웃 0.5초 (VTIME=5: 0.5초)
     // my_termios.c_cc[VMIN]  = 0;
     // my_termios.c_cc[VTIME] = 5;
	// // Serial 파라미터 수정 끝//

     res = tcsetattr ( commPort, TCSANOW, &my_termios); 
	
     if (res < 0)
     {
          return CAM_ERROR_CREATING_COMM;
     }
     
     return CAM_OK;
}

/*!
  * Function for reading bytes from a communication port.  Usually just a pass
  * through function for ReadCommPortTimeout(uPort, szBuffer, dwCount, CAM_NORMAL_TIMEOUT);
  *
  * @param[in] uPort: The index of the communication port.
  * @param[in] szBuffer: A pointer to a empty buffer of at least dwCount legnth in bytes.
  * @param[in] dwCount: The number of bytes to be read.
  * @return The number of bytes read from the communication port.
  */

LONG SERIAL_API ReadCommPort(SERIAL_PORT uPort, LPVOID szBuffer, LONG dwCount)
{
     return ReadCommPortTimeout( commPort, szBuffer, dwCount, CAM_NORMAL_TIMEOUT);
}

/*!
  * Function for reading bytes from a communication port.  This function is
  * synchronous and returns when either the specified number of bytes is read
  * or the timeout occurs.
  *
  * @param[in] uPort: The index of the communication port.
  * @param[in] szBuffer: A pointer to a empty buffer of at least dwCount legnth in bytes.
  * @param[in] dwCount: The number of bytes to be read.
  * @param[in] dwTimeout: The function timeout in milliseconds.
  * @return The number of bytes read from the communication port.
  */

LONG SERIAL_API ReadCommPortTimeout(SERIAL_PORT uPort, LPVOID szBuffer, LONG dwCount, LONG dwTimeout)
{
     int timecount = 0;
     char *buf = szBuffer;
     int	i = 0;
     int res;
     char	c;

     /* 
      * usleep on Cygwin, parameter is in microseconds, but there's a
      * practical limit of approx 2 milliseconds. The read itself
      * takes additional time, so that is also taken into account.
      */

     while ( (timecount < dwTimeout) && (i < dwCount) ) 
     {
          if ( (res = read(commPort, &buf[i], 1)) != -1 ) 
          {
               
               printf("read\n");
               printf("read[%d]: 0x%02X\n", i, (unsigned char)buf[i]);
               i++;
          } 
          else 
          {
               usleep(2000); //기존코드
               //usleep(100);
               printf("read usleep\n");
               timecount += 10; //기존코드
               //timecount += 1;
          }
     }
     return i;
}

/*!
  * Function for writing bytes to a communication port.  This function is 
  * usually written asynchronously in that the bytes are usually copied to a 
  * buffer and then sent out at the interrupt level (higher performance) but 
  * could also be implemented synchronously via polling (lower performance).
  * 
  * @param[in] uPort: The index of the communication port.
  * @param[in] szBuffer: A pointer to a buffer of data to be sent of at least dwCount length in bytes.
  * @param[in] dwCount: The number of bytes to be written.
  * @return The number of bytes written to the communication port.
  */
LONG SERIAL_API WriteCommPort(SERIAL_PORT uPort, LPCVOID szBuffer, LONG dwCount)
{
     int	count;

     const unsigned char *buf = (const unsigned char *)szBuffer;


     printf("6)serstub.c//commPort address: %d\n",&commPort);
     printf("7)serstub.c//commPort: %d\n",commPort);
     printf("8)serstub.c//uPort: %d\n",uPort);

     printf(">>> Writing %ld bytes:\n", dwCount);
     for (int i = 0; i < dwCount; i++) {
         printf("write[%d]: 0x%02X\n", i, buf[i]);
     }


     count = write ( commPort, szBuffer, dwCount);
     printf("9)serstub.c//write: %d\n",count);
     printf("WriteCommPort function END;\n");
     printf("\n");
     return count;
}

/*!
  * Function for flushing bytes in a communication port.  This function is
  * is called before each command/response message in the serial protocol
  * to clear out the bytes in both the transmitter and receiver buffers
  * (if they are interrupt driven).
  *
  * @param[in] uPort: The index of the communication port.
  * @return TRUE if successful FALSE otherwise.
  */
BOOL SERIAL_API FlushCommPort(SERIAL_PORT uPort)
{
     return FALSE;
}

/*!
  * Function for closing a communication port.  This function is called after
  * all the other communication functions to shut down the communication 
  * interface.  If the communication is asynchronous (interrupt driven) it 
  * should wait for the bytes to be sent/received before the port is closed.
  *
  * @param[in] uPort: The index of the communication port.
  * @return TRUE if successful FALSE otherwise.
  */
BOOL SERIAL_API CloseCommPort(SERIAL_PORT uPort)
{
     int result;
     result = close(commPort);
     if (result == 0)
     {
          return TRUE;
     }
     else
     {
          return FALSE;
     }
}

/** @} */ /* end of group */
