#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

int main(void) {
    const char *portName = "/dev/ttyUSB0";
    int fd = open(portName, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        perror("Error opening serial port");
        return EXIT_FAILURE;
    }
    else{
        printf("Open %s Successfully\n", portName);
    }

    // 시리얼 포트 설정
    struct termios tty;
    memset(&tty, 0, sizeof tty);
    if (tcgetattr(fd, &tty) != 0) {
        perror("Error from tcgetattr");
        close(fd);
        return EXIT_FAILURE;
    }
    
    // 송수신 속도 설정 (예: 921600)
    cfsetospeed(&tty, B921600);
    cfsetispeed(&tty, B921600);
    
    // 제어 플래그: 8N1, 로컬 모드, 수신 활성화, 하드웨어 흐름 제어 해제
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;  // 8비트 데이터
    tty.c_cflag |= (CLOCAL | CREAD);             // 모뎀 제어 무시, 수신 활성화
    tty.c_cflag &= ~(PARENB | PARODD);           // 패리티 없음
    tty.c_cflag &= ~CSTOPB;                      // 1 stop bit (2 stop bit 사용하려면 cstopb)
#ifdef CRTSCTS
    tty.c_cflag &= ~CRTSCTS;  // 하드웨어 흐름 제어 비활성화 (정의되어 있을 때만)
#endif

    // 입력 플래그: 브레이크 처리 끄기, XON/XOFF 비활성화
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~IGNBRK;
    
    // 로컬 플래그: 캐노니컬 모드 해제, 에코 비활성화 등
    tty.c_lflag = 0;
    
    // 출력 플래그: 원시 모드(raw mode)
    tty.c_oflag = 0;
    
    // 읽기 관련 타임아웃 설정: 최소 읽기 바이트 수 0, 타임아웃 0.5초 (VTIME=5: 0.5초)
    tty.c_cc[VMIN]  = 0;
    tty.c_cc[VTIME] = 5;
    
    // 설정 적용
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("Error from tcsetattr");
        close(fd);
        return EXIT_FAILURE;
    }
    
    // 송신할 데이터 패킷 (10바이트)
    unsigned char packet1[10] = { 0x6E, 0x00, 0x00, 0x05, 0x00, 0x00, 0x34, 0x4B, 0x00, 0x00 };
    unsigned char packet2[10] = { 0x6E, 0x00, 0x00, 0x04, 0x00, 0x00, 0x03, 0x7B, 0x00, 0x00 };

    for (int k = 1; k <= 2; k++) {
        unsigned char *current_packet;
        if (k == 1) {
            current_packet = packet1;
        } else { // k == 2
            current_packet = packet2;
        }
        
        // 송신할 데이터 패킷 출력 (16진수)
        printf("Sending packet %d: ", k);
        for (int i = 0; i < sizeof(packet1); i++) {
            printf("0x%02X ", current_packet[i]);
        }
        printf("\n");
        
        // 패킷 송신
        int bytes_written = write(fd, current_packet, sizeof(packet1));
        if (bytes_written < 0) {
            perror("Error writing to serial port");
            close(fd);
            return EXIT_FAILURE;
        } else {
            printf("Sent %d bytes successfully.\n", bytes_written);
        }
        
        // 수신: 최대 256바이트 읽기
        unsigned char buf[256];
        memset(buf, 0, sizeof(buf));
        int n = read(fd, buf, sizeof(buf));
        if (n < 0) {
            perror("Error reading from serial port");
            close(fd);
            return EXIT_FAILURE;
        } else if (n == 0) {
            printf("No data received.\n");
        } else {
            printf("Received %d byte(s):\n", n);
            for (int i = 0; i < n; i++) {
                printf("0x%02X ", buf[i]);
            }
            printf("\n");
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}
