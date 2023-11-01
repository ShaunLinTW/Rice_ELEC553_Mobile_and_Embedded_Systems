#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

static char receive[256];

int main(){
        int fd;
        int ret;
        char stringToSend[256];
        printf("Warm it up.exe\n");
        fd = open("/dev/shaun", O_RDWR);      // Capital o, not zero
		printf("Open return value: %d\n", fd);
		if (fd < 0) return 0;
        printf("Are you Shaun?\n");
        scanf("%[^\n]%*c", stringToSend);
        ret = write(fd, stringToSend, strlen(stringToSend));
        printf("@HP, I'm going to repeat back what you said (if you hit enter)\n");
        getchar();
        ret = read(fd, receive, 256);
        printf("REPEAT OF MESSAGE: %s\n", receive);
		close(fd);
        return 0;
}