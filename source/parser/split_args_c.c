/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:23:29 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/07 07:39:54 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token_m	*add_token_list(t_token_m *space, t_token_m *new_token)
{
	t_token_m	*tmp;

	new_token = ft_calloc(1, sizeof(t_token_m));
	if (new_token == NULL)
	{
		perror("Error: ");
		return (NULL);
	}
	tmp = space;
	while (tmp->next_tok != NULL)
		tmp = tmp->next_tok;
	tmp->next_tok = new_token;
	return (new_token);
}

static void	put_tokens_c_ctrl(char *cmd, t_token_m *new_token, int *i, int q_id)
{
	i[0] = 0;
	i[4] = i[2] + 1;
	while (cmd[i[4]] != q_id)
	{
		if (cmd[i[4]] == ' ')
		{
			cmd[i[4]] = ALPHA;
			if (i[3] == 0)
				new_token->id[i[0]] = i[4] - 1;
			else
				new_token->id[i[0]] = i[4] - i[1] - 1;
			i[0]++;
		}
		i[4]++;
	}
}

void	put_tokens_c(char *command, t_token_m *token_list, int *i, int q_id)
{
	t_token_m	*new_token;

	new_token = NULL;
	new_token = add_token_list(token_list, new_token);
	if (new_token == NULL)
	{
		free_token_list(token_list);
		free_and_exit();
	}
	new_token->id = ft_calloc(i[4], sizeof(int));
	if (new_token->id == NULL)
	{
		perror("Error: ");
		free_token_list(token_list);
		free_and_exit();
	}
	new_token->id_size = i[4] - 1;
	new_token->split_c = i[3];
	put_tokens_c_ctrl(command, new_token, i, q_id);
}

void	free_token_list(t_token_m *lst)
{
	t_token_m	*tmp;

	tmp = NULL;
	if (lst->next_tok != NULL)
		tmp = lst->next_tok;
	free(lst);
	lst = tmp;
	if (lst == NULL)
		return ;
	while (lst->next_tok != NULL)
	{
		if (lst->id)
			free(lst->id);
		tmp = lst->next_tok;
		free(lst);
		lst = tmp;
	}
	if (lst->id)
		free(lst->id);
	free(lst);
	return ;
}

char	*expand_quote_var(char *command, int *idx, int q_id)
{
	int	i;

	i = *idx;
	while (command[++i] != q_id)
	{
		if (command[i] == '$' && command[i + 1] != S_QUOTE)
			command = expand_var(command, i--);
	}
	return (command);
}
