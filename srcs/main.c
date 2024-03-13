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

void    callexecve()
{
 char *const args[] = { "ls", NULL };
 char *const envp[] = { NULL };
 
 execve("/bin/ls", args, envp);
 perror("execve");
 exit(EXIT_FAILURE); // Make sure to exit the child process if execve fails 
}

int main()
{
	int fd[2];
	pid_t pid;
 
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
 
	pid = fork();
	if (pid == -1)
	{
		perror("fork"); 
		exit(EXIT_FAILURE);
	}
 
	if (pid == 0)
	{
		printf("I am the child. But now a new parent. My PID is :%d --- My child's PID is %d\n", getpid(), pid);
		callexecve();
	}
	else
	{
  		printf("I am the parent. My PID is :%d --- My child's PID is %d\n", getpid(), pid);
	  	waitpid(pid, NULL, 0); 
  		printf("Got back the control?\n");
	}
}