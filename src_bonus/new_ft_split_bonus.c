/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_ft_split_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmeriau <rmeriau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:21:05 by lpaulo-m          #+#    #+#             */
/*   Updated: 2023/07/24 10:18:12 by rmeriau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	new_spaces(char *str, char c)
{
	str = ft_strchr(str, c);
	while (str != NULL && *str != '\0')
	{
		str++;
		while (*str != c && *str != '\0')
		{
			if (*str == ' ')
				*str = NOT_ASCII;
			str++;
		}
		if (*str == c)
			str++;
	}
}

void	no_quotes(char *str, char c)
{
	str = ft_strchr(str, c);
	while (str != NULL)
	{
		ft_strcpy(str, str + 1);
		str = ft_strchr(str, c);
	}
}

void	redo_spaces(char **tab)
{
	char	*token;

	while (*tab != NULL)
	{
		token = *tab;
		while (*token != '\0')
		{
			if (*token == NOT_ASCII)
				*token = ' ';
			token++;
		}
		tab++;
	}
}

char	**custom_split(char *raw_cmd)
{
	char	*free_me;
	char	**tokens;
	char	sep;

	sep = 0;
	if (ft_strchr(raw_cmd, '\'') == NULL && ft_strchr(raw_cmd, '"') == NULL)
		return (ft_split(raw_cmd, " "));
	else if (ft_strchr(raw_cmd, '\'') != NULL)
		sep = '\'';
	else if (ft_strchr(raw_cmd, '"') != NULL)
		sep = '"';
	free_me = ft_strdup(raw_cmd);
	new_spaces(free_me, sep);
	no_quotes(free_me, sep);
	tokens = ft_split(free_me, " ");
	redo_spaces(tokens);
	free(free_me);
	return (tokens);
}
