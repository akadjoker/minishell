/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_control_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:23:29 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/07 19:06:23 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_error_control_two(char **str_var, char *command)
{
	if (str_var[4] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	command = ft_strjoin(str_var[3], str_var[4]);
	if (command == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	ft_free_split(str_var);
	return (command);
}

static char	**expand_error_control_one(char **str_var)
{
	if (str_var[1] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	str_var[2] = ft_itoa(g_shell.noerr);
	if (str_var[2] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	str_var[3] = ft_strjoin(str_var[1], str_var[2]);
	if (str_var[3] == NULL)
	{
		perror("Error: ");
		ft_free_split(str_var);
		return (NULL);
	}
	return (str_var);
}

char	*expand_error(char *command, int i)
{
	char	**str_var;
	int		j;

	str_var = (char **)ft_calloc(6, sizeof(char *));
	if (str_var == NULL)
	{
		perror("Error: ");
		free(command);
		return (NULL);
	}
	j = 0;
	while (j < 6)
		str_var[j++] = NULL;
	str_var[0] = command;
	str_var[1] = ft_substr(str_var[0], 0, i);
	str_var = expand_error_control_one(str_var);
	if (str_var == NULL)
		return (NULL);
	str_var[4] = ft_substr(str_var[0], i + 2, ft_strlen(str_var[0]) - (i + 2));
	command = expand_error_control_two(str_var, command);
	return (command);
}
