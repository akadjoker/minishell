/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:23:29 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/13 18:39:52 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**swap_spaces(char **splitted,
			t_token_m *lst, t_token_m *tmp)
{
	while (lst->next_tok != NULL)
	{
		while (lst->id_size >= 0)
		{
			splitted[lst->split_c][lst->id[lst->id_size]] = ' ';
			lst->id_size--;
		}
		free(lst->id);
		tmp = lst->next_tok;
		free(lst);
		lst = tmp;
	}
	while (lst->id_size >= 0)
	{
		splitted[lst->split_c][lst->id[lst->id_size]] = ' ';
		lst->id_size--;
	}
	free(lst->id);
	free(lst);
	return (splitted);
}

static char	**unchange_tok_c(char **splitted, t_token_m *lst)
{
	t_token_m	*tmp;

	tmp = NULL;
	if (lst->next_tok != NULL)
		tmp = lst->next_tok;
	free(lst);
	lst = tmp;
	if (lst == NULL)
		return (splitted);
	return (swap_spaces(splitted, lst, tmp));
}

static void	split_command_control(char **split, t_token_m *j_list, char *cmd)
{
	if (split == NULL)
	{
		perror("Error: ");
		free(cmd);
		free_token_list(j_list);
		free_and_exit();
	}
}

/*
the begining :D 
*/
char	**split_command(char *command)
{
	t_token_m	*token_list;
	char		**splitted;

	command = ft_strdup(command);
	if (command == NULL)
	{
		perror("Error: ");
		free_and_exit();
	}
	token_list = ft_calloc(1, sizeof(t_token_m));
	if (token_list == NULL)
	{
		perror("Error: ");
		free(command);
		free_and_exit();
	}
	command = treat_command(command, token_list);
	splitted = ft_split(command, ' ');
	split_command_control(splitted, token_list, command);
	free(command);
	splitted = unchange_tok_c(splitted, token_list);
	return (splitted);
}
