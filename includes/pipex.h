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

char	*get_cmd_path(char *cmd, char **env);
void    callexecve(char *cmd, char **env);

#endif