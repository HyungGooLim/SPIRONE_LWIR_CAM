#include "../photonComm.h"
#include <stdio.h>
#include <string.h>
#include "../userFunctions.h"

//#include "../camuser.h"

#define CONSOLE_LINE 80
#define COM_PORT 0
#define TRUE 	1
#define FALSE 	0

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
	PHOTON_RESULT	res = 0;		

	res = OpenCommPort(port);
	if (res < CAM_OK)
	{
		printf("3-1)Opening dev/ttyUSB%d failed. Error code %d\n", port, res);
		return -1;
	}

	printf("3-2) /dev/ttyUSB%d Opened\n", port);
	printf("3-3 commPort address on main.c: %d\n",&commPort);
	printf("3-4 commPort on main.c: %d\n",commPort);
	printf("PhotonGetRevision START \n");
	printf("\n");

	res = PhotonGetRevision(port, (long*)swVersion, (long*)fwVersion);
	printf("PhotonGetRevision END \n");
	if (res < CAM_OK)
	{
		printf("17)main.c//res: %d\n",res);
		printf("18)main.c//PhotonGetRevision failed. port: %d\n", port);
		
		return -1;
	}
	
	printf("SW version:\t%u.%u.%u.%u\n", swVersion[3], swVersion[2], 
	                                   swVersion[1], swVersion[0]);
	
	printf("FW version:\t%u.%u.%u.%u\n", fwVersion[3], fwVersion[2],
	                                   fwVersion[1], fwVersion[0]);
	                                   
	res = PhotonGetSerialNum(port, &serialNum);
	if (res < CAM_OK)
	{
		printf("PhotonGetSerialNum failed. Error code %d\n", port);
		return -1;
	}
	printf("Serial Number:\t%u\n", serialNum);
	
	printf("Perform a flat field correction(FFC)? (Y/N): ");
	while(1)
	{
		fgets(consoleData, CONSOLE_LINE, stdin);
	
		if(strcmp(consoleData, "y\n") == 0 ||
		   strcmp(consoleData, "Y\n") == 0)
		{
			res = PhotonDoFFC(port);
			if (res < CAM_OK)
			{
				printf("PhotonDoFFC failed. Error code %d\n", port, res);
				return -1;
			}
			break;
		}
		else if(strcmp(consoleData, "n\n") == 0 ||
		        strcmp(consoleData, "N\n") == 0)
		{
			break;
		}
	}
	if (CloseCommPort(port) != TRUE)
	{
		printf("Closing /dev/ttyUSB%d failed.", port);
		return -1;
	}
	printf("/dev/ttyUSB%d Closed\n", port);
	
    return 0;
}

