#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define COM_PORT "/dev/ttyUSB0"  // 사용할 장치 파일 (필요에 따라 변경)

int main(void)
{
    int fd;
    char buffer[32];
    int number = 123;  // 임의로 전송할 숫자
    int len, count;

    // 통신 포트 열기 (읽기/쓰기, 논블로킹 모드)
    fd = open(COM_PORT, O_RDWR | O_NONBLOCK);
    if (fd < 0) {
        perror("Failed to open port");
        return EXIT_FAILURE;
    }
    printf("Opened %s (fd: %d)\n", COM_PORT, fd);

    // 숫자를 문자열로 변환 (예: "42")
    len = snprintf(buffer, sizeof(buffer), "%d", number);
    if(len < 0) {
        perror("snprintf error");
        close(fd);
        return EXIT_FAILURE;
    }

    // 통신 포트에 데이터 전송
    count = write(fd, buffer, len);
    if (count < 0) {
        perror("Write failed");
        close(fd);
        return EXIT_FAILURE;
    }
    printf("Wrote %d bytes: %s\n", count, buffer);

    // 포트 닫기
    close(fd);
    return EXIT_SUCCESS;
}