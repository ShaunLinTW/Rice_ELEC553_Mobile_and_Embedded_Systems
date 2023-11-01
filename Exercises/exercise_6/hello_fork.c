// Header files
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

// Use fork to create child process
// Child will wait for character input, then print "Hello world!" and return
// Parent will wait for child process to complete, then print "Hello world!"
// and return
int main()
{

    // The return value of fork will be 0 for the (newly created) child process
    // and for the parent process it will be the pid of the child process
    int pid = fork();
    printf("%i\n", pid);

    // Child process: Wait on character input
    if(pid==0){
        getchar();
    }
    // Parent process: Wait for child process to complete
    else {
        waitpid(pid, 0, 0);
    }

    // Both processes print "Hello world!" before returning
    printf("Hello world!\n");
    return 0;
}
