#include "./includes/pipex.h"
 
int main()
{
	int pfd[2];
	pid_t pid;
 
	if (pipe(pfd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	// -------------
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(pfd[R_END]); //close unused end (the reading end) of the pipe
		dup2(pfd[W_END], STDOUT_FILENO);
		close(pfd[W_END]);
 		char *args[2] = {"ls", NULL}; 
		execve("/bin/ls", args, NULL);
		if (execve("/bin/ls", args, NULL) == -1) 
		{
			perror("execve");
			exit(EXIT_FAILURE);
    	}
	}

	// --------------
	int pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0) // child process 2
	{
		close(pfd[W_END]); //close unused end (the writing end) of the pipe
		dup2(pfd[R_END], STDIN_FILENO);
		close(pfd[R_END]); //close it immediately as it will no longer be used
 		char *args[2] = {"wc", NULL}; 
		if (execve("/usr/bin/wc", args, NULL) == -1) 
		{
			perror("execve");
			exit(EXIT_FAILURE);
    	}
	}

	close(pfd[1]); // ? close write end of pipe to sign end of input to 'wc' command in 2nd child process
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	printf("this msg should appear after child process finish\n");
}
