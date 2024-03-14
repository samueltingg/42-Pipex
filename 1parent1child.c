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
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) // child process
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
	else if (pid > 0) // parent process
	{
		waitpid(pid, NULL, 0);
		// close(pfd[W_END]); //close unused end (the writing end) of the pipe
		dup2(pfd[R_END], STDIN_FILENO); // replace pfd[0] with stdin to become read end of the pipe
		close(pfd[R_END]); //close it immediately as it will no longer be used
 		char *args[2] = {"wc", NULL};
		if (execve("/usr/bin/wc", args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
    	}
	}

	printf("this msg should appear after child process finish\n");
}
