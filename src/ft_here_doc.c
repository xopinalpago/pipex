/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 11:16:49 by rmeriau           #+#    #+#             */
/*   Updated: 2023/07/24 10:13:27 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	read_fd(void)
{
	int	i;
	int	fd;

	i = 10000;
	if (access(PATH_HC, F_OK) == 0)
		unlink(PATH_HC);
	while (access(PATH_HC, F_OK) != 0 && i)
	{
		fd = open_file(PATH_HC, 3);
		if (fd > 0)
			return (fd);
		i--;
	}
	return (-1);
}

int	read_term(int fd, char **argv)
{
	char	*line;

	ft_putstr_fd("> ", 1);
	line = get_next_line(0, 0);
	while (1)
	{
		if (!line)
		{
			get_next_line(-1, 0);
			return (-1);
		}
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			get_next_line(-1, 0);
			free(line);
			break ;
		}
		ft_putstr_fd("> ", 1);
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0, 0);
	}
	return (0);
}

int	read_input(t_pipex *data, char *argv[])
{
	int	ret;
	int	fd;

	if (data->here_doc == 1)
	{
		fd = read_fd();
		if (fd < 0)
			return (-1);
		ret = read_term(fd, argv);
		close(fd);
		if (ret == -1)
			return (-1);
		fd = open_file(PATH_HC, 0);
		data->input = fd;
	}
	else
		data->input = open_file(argv[1], 0);
	return (data->input);
}
