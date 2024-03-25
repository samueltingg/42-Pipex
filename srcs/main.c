/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:46:10 by sting             #+#    #+#             */
/*   Updated: 2024/03/25 14:13:41 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/pipex.h"





/*
"O_WRONLY | O_CREAT | O_TRUNC"
	- open file for writing only, create if doesn't exit, if exist: file starts of empty

*/
int main(int argc, char **argv, char **env)
{
	// * parse "infile" & "outfile"
	t_file file_fd;
	int cmd_count;

	int i;
	int j;
	int pfd[2];
	pid_t pid;
	
	if (argc < 5)
	{
		ft_putstr_fd("Please input at least 4 arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	

	
	// ? here_doc =======
	
	i = -1;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		cmd_count = argc - 4;
		j = 3;
		file_fd.in = open(argv[1], O_WRONLY | O_CREAT, 0666);
		printf("here?\n");
		file_fd.out = open(argv[argc - 1], (O_WRONLY | O_CREAT | O_APPEND), 0666);
		while(1)
		{
			ft_printf("> ");
			char *str = get_next_line(STDIN_FILENO); // ! need to check if NULL?
			if (ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0)
				break;
			write(file_fd.in, str, ft_strlen(str));
		}
		close(file_fd.in); // ! have to close and reopne as readonly
		file_fd.in = open(argv[1], O_RDONLY);
	}
	else 
	{
		cmd_count = argc - 3;
		j = 2;
		
		file_fd.in = open(argv[1], O_RDONLY); 
		file_fd.out = open(argv[argc - 1], (O_WRONLY | O_CREAT | O_TRUNC), 0666);
	}
	
	if (file_fd.in == -1)
	{
		perror("Unable to open the file");
		exit(EXIT_FAILURE);
	}
	if (file_fd.out == -1)
	{
		perror("Unable to open the file");
		exit(EXIT_FAILURE);
	}
	
	// ? ==========


	dup2(file_fd.in, STDIN_FILENO);
	close(file_fd.in); // ! where to close ?
	while (++i < cmd_count)
	{
		if (pipe(pfd) == -1) // * PIPE
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork(); // * FORK
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0) // * CHILD
		{
			close(pfd[R_END]); 	// lose unused end (the reading end) of the pipe
			if (i == (cmd_count - 1)) // if at last cmd
			{
				dup2(file_fd.out, STDOUT_FILENO);
				close(file_fd.out);
			}
			else
				dup2(pfd[W_END], STDOUT_FILENO); //	replace pfd[1] with stdout to become write end of the pipe
			close(pfd[W_END]);
			callexecve(argv[j], env);
		}
		else if (pid > 0) // * PARENT 
		{
			close(pfd[W_END]); // lose unused end (the writing end) of the pipe
			if (i != (cmd_count - 1)) // if not at last cmd 
				dup2(pfd[R_END], STDIN_FILENO); // replace pfd[0] with stdin to become read end of the pipe
			close(pfd[R_END]); 	// lose it immediately as it will no longer be used
			waitpid(pid, NULL, 0);
		}
		j++;
	}
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (unlink("here_doc") == -1)
		{
			perror("Error deleting file");
			exit(EXIT_FAILURE);
		}
	}
}
 