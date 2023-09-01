/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_elems.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:26:00 by rmeriau           #+#    #+#             */
/*   Updated: 2023/07/21 11:00:40 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**fill_cmds(t_pipex data, char *argv[])
{
	char	**cmds;
	int		i;
	int		doc;

	doc = 2;
	if (data.here_doc == 1)
		doc = 3;
	cmds = (char **)malloc(data.n * sizeof(char *));
	if (!cmds)
		return (NULL);
	i = 0;
	while (i < data.n)
	{
		cmds[i] = (char *)malloc((ft_strlen(argv[i + doc]) + 1) * sizeof(char));
		if (!cmds[i])
			return (NULL);
		ft_strcpy(cmds[i], argv[i + doc]);
		i++;
	}
	return (cmds);
}

int	fill_pipefd(int ***pipefd, int num_cmds)
{
	int	i;

	*pipefd = (int **)malloc((num_cmds - 1) * sizeof(int *));
	if (!(*pipefd))
		return (0);
	i = 0;
	while (i < num_cmds - 1)
	{
		(*pipefd)[i] = (int *)malloc(2 * sizeof(int));
		if (!(*pipefd)[i])
			return (0);
		if (pipe((*pipefd)[i]) == -1)
		{
			perror("pipe");
			return (0);
		}
		i++;
	}
	return (1);
}

pid_t	**fill_pids(int num_cmds)
{
	pid_t	**pids;
	int		i;

	pids = (pid_t **)malloc(num_cmds * sizeof(pid_t *));
	if (!pids)
		return (NULL);
	i = 0;
	while (i < num_cmds)
	{
		pids[i] = (pid_t *)malloc(sizeof(pid_t));
		if (!pids[i])
			return (NULL);
		i++;
	}
	return (pids);
}
