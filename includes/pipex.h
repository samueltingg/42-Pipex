/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:13:25 by sting             #+#    #+#             */
/*   Updated: 2024/03/26 11:13:26 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define R_END 0
# define W_END 1

# include ".././libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct t_file
{
	int		in;
	int		out;
}			t_file;

typedef struct s_info
{
	int		fd_in;
	int		fd_out;
	char	**cmds;
	int		cmd_count;
	pid_t	pid;

}			t_info;

// types of error
enum		e_type
{
	OPEN,
	PIPE,
	FORK,
	UNLINK,
	INVALID_CMD,
	ARGC,
	MALLOC,
	EXECVE,
};

char		*get_cmd_path(char *cmd, char **env);
void		callexecve(char *cmd, char **env);
void		exit_if_error(enum e_type type);

#endif