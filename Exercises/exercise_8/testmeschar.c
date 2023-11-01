#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
  printf("Testing the system call open()!\n");
  open("/dev/shaun", O_RDWR);
  
  return 0;
}