/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:46:10 by sting             #+#    #+#             */
/*   Updated: 2024/03/26 10:19:27 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././includes/pipex.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

char	*get_cmd_path(char *cmd, char **env)
{
	int i;
	char *env_paths;
	char *tmp_path;
	char *path;
	char **str_arr;

	i = -1;
	while (env[++i])
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			break ;
	env_paths = env[i] + 5;
	str_arr = ft_split(env_paths, ':');
	if (str_arr == NULL)
		exit_if_error(MALLOC);
	i = -1;
	while (str_arr[++i])
	{
		tmp_path = ft_strjoin(str_arr[i], "/");
			// ! how to free "path" after strjoin?
		if (tmp_path == NULL)
			exit_if_error(MALLOC);
		path = ft_strjoin(tmp_path, cmd);
		if (path == NULL)
			exit_if_error(MALLOC);
		free(tmp_path);
		if (access(path, X_OK) != -1)
			break ;
		else
		{
			free(path);
			if (str_arr[i + 1] == NULL) // if at last str && access() show fail
				exit_if_error(INVALID_CMD);
		}
	}
	free_str_arr(str_arr);
	return (path);
}

void	callexecve(char *cmd, char **env)
{
	char	**args;
	char	*path;

	if (cmd[0] == '\0')
		exit_if_error(INVALID_CMD);
	args = ft_split(cmd, ' ');
	if (args == NULL)
		exit_if_error(MALLOC); // ! free other stuff?
	if (access(args[0], X_OK) != -1)
		path = args[0];
	else
		path = get_cmd_path(args[0], env);
	if (execve(path, args, env) == -1)
        exit_if_error(EXECVE);
}
