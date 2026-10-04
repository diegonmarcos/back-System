#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() 
{
    int pipefds[2];
    char buffer[256] = ""; // Initialize buffer to empty string
    
	// Create a pipe starting the parent process
	pipe(pipefds); // writes to pipefds[1] and reads from pipefds[0] and add those FDs to the pipefds array
    	printf("Parent PID: %d\n", getpid()); // PID is the process ID
    read(pipefds[0], buffer, 3); // read 3 bytes from the pipefds[0] and store them in the buffer
		printf("Got from pipe: %s\n", buffer); // print the buffer
	write(pipefds[1], "msg", 3); // write 3 bytes to the pipe
	read(pipefds[0], buffer, 3); // read 3 bytes from the pipefds[0] and store them in the buffer
		printf("Got from pipe: %s\n", buffer); // print the buffer
    
	if (fork() > 0) {
        return 0; // here the parent process is closed with the return 0
    }
	// here starts the child process
		printf("Child PID: %d\n", getpid());
    read(pipefds[0], buffer, 3); // read 3 bytes from the pipefds[0] and store them in the buffer
    	printf("Got from pipe: %s\n", buffer); 
    return 0;
}

