/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:27:49 by rmeriau           #+#    #+#             */
/*   Updated: 2023/07/20 15:54:02 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_free(t_pipex data)
{
	if (data.cmds)
		free_char(data.cmds, data.n);
	if (data.pipefd)
		free_int(data.pipefd, data.n - 1);
	if (data.pids)
		free_pids(data.pids, data.n);
}

void	free_int(int **tableau, int nb_line)
{
	int	i;

	i = 0;
	if (tableau == NULL)
		return ;
	while (i < nb_line)
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}

void	free_char(char **tableau, int nb_line)
{
	int	i;

	i = 0;
	if (tableau == NULL)
		return ;
	while (i < nb_line)
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}

void	free_pids(pid_t **tableau, int nb_line)
{
	int	i;

	i = 0;
	if (tableau == NULL)
		return ;
	while (i < nb_line)
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}

int	get_nb_line(char **tableau)
{
	int	i;

	i = 0;
	while (tableau[i])
		i++;
	return (i);
}
