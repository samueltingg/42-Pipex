/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:46:10 by sting             #+#    #+#             */
/*   Updated: 2024/03/19 12:35:01 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int main(int argc, char **argv, char **env)
{
	t_file file_fd;
	int fd;
	file_fd.in = open(argv[1], O_RDONLY);
	if (file_fd.in == -1)
	{
		perror("Unable to open the file");
		exit(EXIT_FAILURE);
	}
	file_fd.out = open(argv[argc - 1], O_WRONLY);
	if (file_fd.out == -1)
	{
		perror("Unable to open the file");
		exit(EXIT_FAILURE);
	}
	
		
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
	else if (pid == 0) // * child
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
	else if (pid > 0) // * parent
	{
		waitpid(pid, NULL, 0); 
		close(pfd[W_END]); //close unused end (the writing end) of the pipe
		dup2(pfd[R_END], STDIN_FILENO); // replace pfd[0] with stdin to become read end of the pipe
		close(pfd[R_END]); //close it immediately as it will no longer be used
	}
}