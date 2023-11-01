#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>

#define syscall_num 452

int main(int argc, char *argv[])
{
        int reset_flag = 0;      // 0 = increment, 1 = reset
        int increment_value = 1; // Default increment value is 1
        int initial_value = 0;   // Default initial value is 0

        // Check if there are at least 2 command-line arguments provided
        if (argc >= 2)
        {
                // Convert the first command-line argument (reset flag) from string to integer
                // atoi() function converts a string to an integer in C
                reset_flag = atoi(argv[1]);
        }
        
        // Check if increment_value is provided and positive
        if (argc >= 3)
        {
                increment_value = atoi(argv[2]);

                // Check if increment_value is positive
                if (increment_value < 0) {
                        printf("Invalid increment value. Please use a positive integer.\n");
                        return EINVAL; // Return EINVAL if invalid increment value is provided
                }
        }

        // Check if initial_value is provided and positive
        if (argc >= 4)
        {
                initial_value = atoi(argv[3]);

                // Check if initial_value is positive
                if (initial_value < 0) {
                        printf("Invalid initial value. Please use a positive integer.\n");
                        return EINVAL; // Return EINVAL if invalid initial value is provided
                }
        }

        printf("Calling counter syscall...\n");

        // Call the custom syscall (hl116) with provided arguments
        int result = syscall(syscall_num, reset_flag, increment_value, initial_value);

        // Check if syscall returns an error
        if (result < 0)
        {
                perror("Error calling custom syscall");
                return errno;
        }

        printf("Custom syscall returned: %d\n", result);

        // Return 0 to indicate successful execution
        return 0;
}
