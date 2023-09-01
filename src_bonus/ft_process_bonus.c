/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:54:15 by rmeriau           #+#    #+#             */
/*   Updated: 2023/07/24 10:18:08 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	process_stdin(int i, t_pipex data)
{
	if (i != 0)
	{
		close(data.input);
		dup2(data.pipefd[i - 1][0], STDIN_FILENO);
		close(data.pipefd[i - 1][0]);
		close(data.pipefd[i - 1][1]);
	}
	else
	{
		dup2(data.input, STDIN_FILENO);
		close(data.input);
	}
}

void	process_stdout(int i, t_pipex data)
{
	if (i != data.n - 1)
	{
		dup2(data.pipefd[i][1], STDOUT_FILENO);
		close(data.pipefd[i][0]);
		close(data.pipefd[i][1]);
	}
	else
	{
		dup2(data.output, STDOUT_FILENO);
		close(data.output);
	}
}

int	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = custom_split(cmd);
	if (!s_cmd)
		return (1);
	path = get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		free_char(s_cmd, get_nb_line(s_cmd));
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Command not found\n", 2);
		return (1);
	}
	free_char(s_cmd, get_nb_line(s_cmd));
	return (0);
}
