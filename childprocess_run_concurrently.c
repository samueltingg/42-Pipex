#include "./includes/pipex.h"

int main(void)
{
	pid_t pid;

	pid = fork(); // * FORK
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) // * CHILD
	{
		printf("child process!")
	}
	else if (pid > 0) // * PARENT 
	{
	}

}