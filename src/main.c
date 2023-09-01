/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:50:09 by rmeriau           #+#    #+#             */
/*   Updated: 2023/07/21 11:03:50 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_handler(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(0);
}

int	init_data(t_pipex *data, int argc, char *argv[])
{
	data->n = argc - 3;
	if (data->here_doc == 1)
		data->n = argc - 4;
	data->input = read_input(data, argv);
	if (data->here_doc == 1)
		data->output = open_file(argv[argc - 1], 2);
	else
		data->output = open_file(argv[argc - 1], 1);
	if (data->input == -1 || data->output == -1)
	{
		perror("bash");
		return (1);
	}
	data->cmds = fill_cmds(*data, argv);
	data->pids = fill_pids(data->n);
	data->pipefd = NULL;
	if (!data->cmds || !fill_pipefd(&data->pipefd, data->n) || !data->pids)
	{
		ft_free(*data);
		return (1);
	}
	return (0);
}

int	do_pipex(t_pipex data, int i, char **env)
{
	*data.pids[i] = fork();
	if (*data.pids[i] < 0)
	{
		perror("fork");
		return (1);
	}
	else if (*data.pids[i] == 0)
	{
		process_stdin(i, data);
		process_stdout(i, data);
		if (exec(data.cmds[i], env))
			return (1);
	}
	else
	{
		if (i != 0)
		{
			close(data.pipefd[i - 1][0]);
			close(data.pipefd[i - 1][1]);
		}
	}
	return (0);
}

int	check_args(int argc, char *argv[])
{
	int	doc;

	doc = 0;
	if (argc < 5)
		exit_handler(1);
	else if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
			exit_handler(1);
		doc = 1;
	}
	return (doc);
}

int	main(int argc, char *argv[], char **env)
{
	t_pipex	data;
	int		i;

	data.here_doc = check_args(argc, argv);
	if (init_data(&data, argc, argv))
		return (1);
	i = 0;
	while (i < data.n)
	{
		if (do_pipex(data, i, env))
		{
			ft_free(data);
			return (1);
		}
		i++;
	}
	if (waiting(data.pids, data.n))
	{
		ft_free(data);
		return (1);
	}
	close(data.input);
	ft_free(data);
	return (0);
}
