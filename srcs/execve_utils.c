/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:46:10 by sting             #+#    #+#             */
/*   Updated: 2024/03/13 09:45:18 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char *get_cmd_path(char *cmd, char **env)
{
    while
}

void    callexecve(char *cmd, char **env)
{
 char *const args[] = { "ls", NULL };
 char *const envp[] = { NULL };
 
 execve("/bin/ls", args, envp);
 perror("execve");
 exit(EXIT_FAILURE); // Make sure to exit the child process if execve fails 
}

		