#include "./includes/pipex.h"


/*
! Testing ls | wc | wc
	- create 2 pipes
*/

int main()
{
	int pfd[2];
	pid_t pid;

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
		close(pfd[R_END]); //close unused end (the reading end) of the pipe
		dup2(pfd[W_END], STDOUT_FILENO); // replace pfd[1] with stdout to become write end of the pipe
		close(pfd[W_END]);
 		char *args[2] = {"ls", NULL};
		if (execve("/bin/ls", args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
    	}
	}
	else
	{
		close(pfd[W_END]); //close unused end (the writing end) of the pipe
		dup2(pfd[R_END], STDIN_FILENO); // replace pfd[0] with stdin to become read end of the pipe
		close(pfd[R_END]); //close it immediately as it will no longer be used
	}

	int pfd2[2];

	if (pipe(pfd2) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	int pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0) // child process 2
	{
		close(pfd2[R_END]);
		dup2(pfd2[W_END], STDOUT_FILENO);
		close(pfd2[W_END]);
 		char *args[2] = {"wc", NULL};
		if (execve("/usr/bin/wc", args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
    	}
	}
	else 
	{
		close(pfd2[W_END]); //close unused end (the writing end) of the pipe
		dup2(pfd2[R_END], STDIN_FILENO); // replace pfd[0] with stdin to become read end of the pipe
		close(pfd2[R_END]); //close it immediately as it will no longer be used
	}


	int pid3 = fork();
	if (pid3 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid3 == 0) // child process 3
	{
 		char *args[2] = {"wc", NULL};
		if (execve("/usr/bin/wc", args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
    	}
	}

	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	waitpid(pid3, NULL, 0);
	// printf("this msg should appear after child process finish\n");
}



