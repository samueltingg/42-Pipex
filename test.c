#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main()
{
	int pfd[2];
	pid_t pid;
	// char buffer[13];
 
	if (pipe(pfd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(pfd[0]); //close unused end (the reading end) of the pipe
		dup2(pfd[1], STDOUT_FILENO);
 		char *args[2] = {"ls", NULL}; 
		execve("/bin/ls", args, NULL);
		// exit(EXIT_SUCCESS);     
	}

	int pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0) // child process 2
	{
		close(pfd[1]); //close unused end (the writing end) of the pipe
		dup2(pfd[0], STDIN_FILENO);
		close(pfd[0]); //close it immediately as it will no longer be used
 		char *args[2] = {"wc", NULL}; 
		execve("/usr/bin/wc", args, NULL);
	}

	// close(pfd[0]);
	// close(pfd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}
