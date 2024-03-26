/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:46:10 by sting             #+#    #+#             */
/*   Updated: 2024/03/26 15:52:50 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/pipex.h"

void	pipe_execution(t_info info, char **env, int i)
{
	int	pfd[2];

	if (pipe(pfd) == -1) // * PIPE
		exit_if_error(PIPE);
	info.pid = fork(); // * FORK
	if (info.pid == -1)
		exit_if_error(FORK); 
	else if (info.pid == 0) // * CHILD
	{
		close(pfd[R_END]); // close unused end (the reading end) of the pipe
		if (i == (info.cmd_count - 1)) // if at last cmd
			dup2(info.fd_out, STDOUT_FILENO);
		else
			dup2(pfd[W_END], STDOUT_FILENO); //	replace pfd[1] with stdout to become write end of the pipe
		close(pfd[W_END]);
		callexecve(info.cmds[i], env);
	}
	else if (info.pid > 0) // * PARENT
	{
		close(pfd[W_END]); // close unused end (the writing end) of the pipe
		if (i != (info.cmd_count - 1)) // if not at last cmd
			dup2(pfd[R_END], STDIN_FILENO); // replace pfd[0] with stdin to become read end of the pipe
		close(pfd[R_END]); // close it immediately as it will no longer be used
		waitpid(info.pid, NULL, 0);
	}
}

void	info_setup_here_doc(int argc, char **argv, t_info *info)
{
	char	*str;
	
	info->cmd_count = argc - 4;
	info->cmds = &argv[3];
	info->fd_in = open(argv[1], O_WRONLY | O_CREAT, 0666);
	if (info->fd_in == -1)
		exit_if_error(OPEN);
	info->fd_out = open(argv[argc - 1], (O_WRONLY | O_CREAT | O_APPEND), 0666);
	if (info->fd_out == -1)
		exit_if_error(OPEN);
	while (1)
	{
		ft_printf("> ");
		str = get_next_line(STDIN_FILENO);
		if (str == NULL || ft_strncmp(str, argv[2], ft_strlen(argv[2])) == 0)
			break ;
		write(info->fd_in, str, ft_strlen(str));
	}
	// have to close and reopen as RDONLY, as file position pointer is at eof after writing
	close(info->fd_in);
	info->fd_in = open(argv[1], O_RDONLY);
	if (info->fd_in == -1)
		exit_if_error(OPEN);
}

void	info_setup_default(int argc, char **argv, t_info *info)
{
	info->cmd_count = argc - 3;
	info->cmds = &argv[2];
	info->fd_in = open(argv[1], O_RDONLY);
	if (info->fd_in == -1)
	{
		perror("Unable to open the file");
		info->fd_in = open("/dev/null", O_RDONLY);
	}
	info->fd_out = open(argv[argc - 1], (O_WRONLY | O_CREAT | O_TRUNC), 0666);
	if (info->fd_out == -1)
		exit_if_error(OPEN);
}

/*
"O_WRONLY | O_CREAT | O_TRUNC"
	- open file for writing only, create if doesn't exit,
		if exist: file starts of empty
*/
int	main(int argc, char **argv, char **env)
{
	t_info	info;
	int		i;

	if (argc < 5)
		exit_if_error(ARGC);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		info_setup_here_doc(argc, argv, &info);
	else
		info_setup_default(argc, argv, &info);
	dup2(info.fd_in, STDIN_FILENO);
	close(info.fd_in);
	i = -1;
	while (++i < info.cmd_count)
		pipe_execution(info, env, i);
	close(info.fd_out);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		if (unlink("here_doc") == -1)
			exit_if_error(UNLINK);
}
