/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 21:50:49 by rmeriau           #+#    #+#             */
/*   Updated: 2023/07/24 10:15:58 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define PATH_HC "/tmp/here_doc.tmp"
# define NOT_ASCII -42

typedef struct s_pipex
{
	char	**cmds;
	int		**pipefd;
	int		n;
	int		here_doc;
	int		input;
	int		output;
	pid_t	**pids;
}	t_pipex;

int		init_data(t_pipex *data, int argc, char *argv[]);
int		do_pipex(t_pipex data, int i, char **env);

char	*get_path(char *cmd, char **env);
char	*my_getenv(char *name, char **env);
int		open_file(char *file, int op_mode);
int		waiting(pid_t **pids, int num_cmds);
int		read_input(t_pipex *data, char *argv[]);

int		check_args(int argc, char *argv[]);

int		read_fd(void);
int		read_term(int fd, char **argv);

int		exec(char *cmd, char **env);
void	process_stdin(int i, t_pipex data);
void	process_stdout(int i, t_pipex data);
char	*find_cmd(char **allpath, char	*s_cmd, int i);

char	**fill_cmds(t_pipex data, char *argv[]);
int		fill_pipefd(int ***pipefd, int num_cmds);
pid_t	**fill_pids(int num_cmds);

void	ft_free(t_pipex data);
void	free_int(int **tableau, int nb_line);
void	free_char(char **tableau, int nb_line);
void	free_pids(pid_t **tableau, int nb_line);
int		get_nb_line(char **tableau);

void	exit_handler(int n_exit);

char	**custom_split(char *raw_cmd);
void	new_spaces(char *str, char c);
void	no_quotes(char *str, char c);
void	redo_spaces(char **tab);

#endif