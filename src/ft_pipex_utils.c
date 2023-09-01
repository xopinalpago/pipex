/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:49:55 by rmeriau           #+#    #+#             */
/*   Updated: 2023/07/24 10:13:12 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*find_cmd(char **allpath, char	*cmd, int i)
{
	char	*path_part;
	char	*exec;

	path_part = ft_strjoin(allpath[i], "/");
	exec = ft_strjoin(path_part, cmd);
	free(path_part);
	if (access(exec, F_OK | X_OK) == 0)
	{
		free_char(allpath, get_nb_line(allpath));
		return (exec);
	}
	free(exec);
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ":");
	if (!allpath)
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	while (allpath[++i])
	{
		exec = find_cmd(allpath, cmd, i);
		if (exec)
			return (exec);
	}
	free_char(allpath, get_nb_line(allpath));
	return (cmd);
}

int	open_file(char *file, int op_mode)
{
	int	fd;

	if (op_mode == 0)
		fd = open(file, O_RDONLY, 0777);
	if (op_mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (op_mode == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (op_mode == 3)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	waiting(pid_t **pids, int num_cmds)
{
	int	status;
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		if (waitpid(*pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			return (1);
		}
		i++;
	}
	return (0);
}
