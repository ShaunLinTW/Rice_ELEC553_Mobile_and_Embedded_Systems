#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int fd;
	int ret;
	char stringToSend[256];

	printf("Warm it up.exe\n");
	fd = open("/dev/shaun", O_RDWR);      // Capital o, not zero
	printf("Are you Shaun?");
	scanf("%[^\n]%*c", stringToSend);
	ret = write(fd, stringToSend, strlen(stringToSend));
	return 0;
}
