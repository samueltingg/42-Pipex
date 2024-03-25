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
	int	in;
	int	out;
}		t_file;

// types of error
enum e_type {
	OPEN,
	PIPE,
	FORK,
	UNLINK,
	INVALID_CMD,
};

char	*get_cmd_path(char *cmd, char **env);
void    callexecve(char *cmd, char **env);
void exit_if_error(enum e_type type);

#endif