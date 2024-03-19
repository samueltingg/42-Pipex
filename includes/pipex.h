#ifndef PIPEX_H
#define PIPEX_H

# define R_END 0
# define W_END 1

#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
# include <fcntl.h>
# include "./libft/libft.h"

typedef struct t_file
{
	int *in;
	int *out;
}			t_file;

#endif