/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:13:48 by sting             #+#    #+#             */
/*   Updated: 2024/03/26 10:18:57 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/pipex.h"

void	exit_if_error(enum e_type type)
{
	if (type == OPEN)
		perror("Unable to open the file");
	if (type == PIPE)
		perror("Pipe");
	if (type == FORK)
		perror("Fork");
	if (type == UNLINK)
		perror("Error deleting file");
	if (type == INVALID_CMD)
		perror("Invalid command");
	if (type == ARGC)
		ft_putstr_fd("Please input at least 4 arguments\n", STDERR_FILENO);
	if (type == MALLOC)
		perror("Malloc");
	if (type == EXECVE)
		perror("execve");
	exit(EXIT_FAILURE);
}
