#include "../photonComm.h"
#include "../tauFunctions.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../userFunctions.h"
#include "../raw2jpg.h"

#include "../camuser.h"

#define CONSOLE_LINE 80
#define COM_PORT 0
#define TRUE    1
#define FALSE    0
#define RAW2JPG_H

int commPort;  // 전역 변수 정의 - open 디스크립터

int main(int argc, char* argv[])
{
   int Product = PRODUCT_TAU2;
   printf("CAM_PRODUCT_ID: %d\n",Product);

   SERIAL_PORT port = COM_PORT;
   unsigned char swVersion[4]; 
   unsigned char fwVersion[4];
   char consoleData[CONSOLE_LINE];
   long serialNum;
   PHOTON_RESULT res = 0;      

   res = OpenCommPort(port);
   if (res < CAM_OK)
   {
      printf("3-1)Opening dev/ttyUSB%d failed. Error code %d\n", port, res);
      return -1;
   }

   printf("3-2) /dev/ttyUSB%d Opened\n", port);
   printf("3-3 commPort address on main.c: %d\n",&commPort);
   printf("3-4 commPort on main.c: %d\n",commPort);

   //코드 추가

   // Digital outbut 세팅 코드 //
   res = PhotonSetDigitalOut(port, DIGITAL_14BIT_UNFILTERED);
   //res = PhotonSetDigitalOut(port, DIGITAL_FPA_DIMENSIONS);
   
   if (res >= CAM_OK) {
        printf("Digital output set to 14-bit unfiltered mode successfully.\n");
    } else {
        printf("Failed to set digital output mode. Error: %d\n", res);
    }

   // // 카메라 FPA센서 온도 추출 코드 //
   // printf("PhotonGetFPATemp START \n");
   // printf("\n");

   // short PhotonFPATemp;
   // float Celsius;
   // CAM_FPA_TEMP_MODE mode;
   // mode = FPA_TENTHS_DEG_C;  // 섭씨 0.1도 단위로 FPA 온도를 읽겠다
   // res = PhotonGetFPATemp(port, mode, &PhotonFPATemp);
   // if (res < CAM_OK)
   // {
   //    printf("PhotonGetFPATemp res: %d\n",res);
   //    printf("main.c//PhotonGetFPATemp failed. port: %d\n", port);
   //    return -1;
   // }
   // Celsius = PhotonFPATemp * 0.1;
   // printf("PhotonGetFPATemp res: %d\n",res);
   // printf("PhotonFPATemp value: %.1f celsius\n", Celsius);
   // 온도 추출 끝 //

   // // 카메라 보드레이트 추출 코드//
   // printf("TauGetBaudRate START \n");
   // printf("\n");
   // short baudRate;
   // res = TauGetBaudRate(port, &baudRate);
   //  if (res < CAM_OK)
   //   {
   //    printf("TauGetBaudRate res: %d\n",res);
   //    printf("main.c//TauGetBaudRate failed. port: %d\n", port);
   //    return -1;
   // }
   // printf("TauGetBaudRate res: %d\n",res);
   // printf("TauGetBaudRate value: %d flag\n", baudRate);
   // // Baudrate 함수 끝
   
   
   // // 코드 추가 끝
   // printf("PhotonGetRevision START \n");
   // printf("\n");

   // res = PhotonGetRevision(port, (long*)swVersion, (long*)fwVersion);
   // printf("PhotonGetRevision END \n");
   // if (res < CAM_OK)
   // {
   //    printf("17)main.c//res: %d\n",res);
   //    printf("18)main.c//PhotonGetRevision failed. port: %d\n", port);
      
   //    return -1;
   // }
   
   // printf("SW version:\t%u.%u.%u.%u\n", swVersion[3], swVersion[2], 
   //                                    swVersion[1], swVersion[0]);
   
   // printf("FW version:\t%u.%u.%u.%u\n", fwVersion[3], fwVersion[2],
   //                                    fwVersion[1], fwVersion[0]);
                                      
   // res = PhotonGetSerialNum(port, &serialNum);
   // if (res < CAM_OK)
   // {
   //    printf("PhotonGetSerialNum failed. Error code %d\n", port);
   //    return -1;
   // }
   // printf("Serial Number:\t%u\n", serialNum);
   


   // 캡쳐 코드 추가 //
   printf("PhotonCaptureFrames START \n");
   printf("\n");
   short captureBuffer = 0x0800;
   res = PhotonCaptureFrames(port, captureBuffer);
   printf("PhotonCaptureFrames END \n");
   printf("result:\t%d\n", res);
   usleep(1500000); // Memory에 저장되는 시간 마진

   // Snapshot 정보 요청
   unsigned long addr = 0;
   int size = 0;
   int nuc = 0x0000;
   int type = 0x0013;

   res = TauGetNucAddress(port, nuc, type, &addr, &size);
   if (res >= 0) {
      printf("Snapshot memory address: 0x%08lX\n", addr);
      printf("Size in bytes: %d\n", size);
   } else {
      printf("Error: %d\n", res);
      return -1;
   }

   // 주소값 직접 불러오기 //
   // unsigned long gui_addr = 0x01D85b2a;
   // unsigned char gui_buf[64];
   // PhotonReadMemory(port, gui_addr, 64, gui_buf);
   // for (int i = 0; i < 64; i++) {
   //    printf("%02X ", gui_buf[i]);
   // }
   // 주소값 직접 불러오기 끝//

   // 이미지 저장용 버퍼
   short imageBuffer[512][640];
   short segmentBuffer[640];

   const int totalWidth = 640;
   const int totalHeight = 512;
   const int segmentWidth = 640;  // TauReadCaptureImage 단위
   int segmentsPerRow = totalWidth / segmentWidth;

   long next_addr = addr;
   long addrIncr = 0;

   // 전체 세로 행 루프
   for (int row = 0; row < totalHeight; row++) {
      // 중간버퍼(segmentBuffer)에 픽셀 1열씩 저장
      res = TauReadCaptureImage(port, next_addr, segmentWidth, &addrIncr, segmentBuffer);
      if (res >= 0) {
	      printf("Captured full image (640x512 pixels) successfully.\n");
      }
      else {
         printf("Error: %d\n", res);
         break;
      }
      // 이미지 버퍼에 복사
      memcpy(&imageBuffer[row][0], segmentBuffer, 640*2);
      next_addr += addrIncr;
   }

   // RAW 파일로 방출 //
   const char* raw_path = "LWIR.raw";
   FILE* raw_fp = fopen(raw_path, "wb");
   if (raw_fp == NULL) {
       perror("Failed to open raw file for writing");
   } else {
       size_t written = fwrite(imageBuffer, sizeof(short), totalWidth * totalHeight, raw_fp);
       if (written != totalWidth * totalHeight) {
           fprintf(stderr, "Warning: Only %zu pixels written out of %d\n", written, totalWidth * totalHeight);
       } else {
           printf("Image data successfully written to %s\n", raw_path);
       }
       fclose(raw_fp);
   }

   // jpg형식 압축 코드 //
   convertRawToJpg((short*)imageBuffer, totalWidth, totalHeight, "LWIR.jpg");
   

	// txt 파일로 방출 //
	const char* path = "image.txt";
	FILE* fp = fopen(path, "w");
	printf("%d\n",fp);
	if (fp == NULL) {
		perror("Failed to open file for writing");
	} else {
		for (int row = totalHeight-1; row >= 0 ; row--) {
			for (int col = 0; col < totalWidth; col++) {
				fprintf(fp, "%d ", imageBuffer[row][col]);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
		printf("Image data successfully written %s\n", path);
	}
	
   // Digital outbut확인 코드 //
   PHOTON_DIGITAL_OUT digitalOutMode;
   res = PhotonGetDigitalOut(port, &digitalOutMode);
   if (res >= CAM_OK) {
        printf("Digital Output Mode: %d\n", digitalOutMode);
    } else {
        printf("Error getting digital output mode: %d\n", res);
    }

   // // FFC 수행 코드 //
   // printf("Perform a flat field correction(FFC)? (Y/N): ");
   // while(1)
   // {
   //    fgets(consoleData, CONSOLE_LINE, stdin);
   
   //    if(strcmp(consoleData, "y\n") == 0 ||
   //       strcmp(consoleData, "Y\n") == 0)
   //    {
   //       res = PhotonDoFFC(port);
   //       if (res < CAM_OK)
   //       {
   //          printf("PhotonDoFFC failed. Error code %d\n", port, res);
   //          return -1;
   //       }
   //       break;
   //    }
   //    else if(strcmp(consoleData, "n\n") == 0 ||
   //            strcmp(consoleData, "N\n") == 0)
   //    {
   //       break;
   //    }
   // }
   if (CloseCommPort(port) != TRUE)
   {
      printf("Closing /dev/ttyUSB%d failed.", port);
      return -1;
   }
   printf("/dev/ttyUSB%d Closed\n", port);
   
   return 0;
}