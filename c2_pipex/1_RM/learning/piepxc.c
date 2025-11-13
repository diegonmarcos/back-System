#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h> // For strlen

#define BUFFER_SIZE 256

void parent_process(pid_t child_pid, int pipefd) {
    		printf("Parent (PID: %d). Child PID: %d\n", getpid(), child_pid);

    char message[] = "Hello from parent!";
    ssize_t bytes_written = write(pipefd, message, strlen(message) + 1); // +1 for null terminator
																	if (bytes_written == -1) 
																		perror("Parent write");
    else 
        	printf("Parent sent: %s\n", message);
    close(pipefd); // Close the write end of the pipe in the parent
    wait(NULL);     // Wait for the child
}

void child_process(int pipefd) {
    printf("Child (PID: %d)\n", getpid());

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(pipefd, buffer, BUFFER_SIZE);
    if (bytes_read == -1) 
        perror("Child read");
    else if (bytes_read == 0) 
        printf("Child: Pipe closed by parent.\n");
	else 
        printf("Child received: %s\n", buffer);
    close(pipefd); // Close the read end of the pipe in the child
    exit(0);       // Important: exit the child process
}

int main() {
    int pipefds[2];

	// Create a pipe and initialize the parent process
	if (pipe(pipefds) == -1) 
	{
		perror("pipe");
		return 1;
	}

    pid_t pid = fork(); // Fork the process and get the PID of the child

																	if (pid < 0) 
																	{
																		perror("fork");
																		return 1;
																	} 
	else if (pid > 0) 
	{
        close(pipefds[0]); // Close the read end in the parent
        parent_process(pid, pipefds[1]);
    } 
	else 
	{
        close(pipefds[1]); // Close the write end in the child
        child_process(pipefds[0]);
    }

    return 0; // Parent continues here (but likely returns after wait())
}