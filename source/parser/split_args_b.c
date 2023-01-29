/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:23:29 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/07 07:39:47 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*treat_quotes_ctrl(char *cmd, int *i, int q_id, t_token_m *j_list)
{
	if (i[4] > 0)
		put_tokens_c(cmd, j_list, i, q_id);
	cmd = subs_quote(cmd, i[2], q_id);
	if (cmd == NULL)
	{
		free_token_list(j_list);
		free_and_exit();
	}
	return (cmd);
}

static char	*treat_quotes(char *cmd, int *idx, int q_id, t_token_m *j_list)
{
	int	i[5];

	i[0] = 0;
	i[4] = 0;
	i[3] = count_string(cmd, idx, i, q_id);
	i[2] = *idx;
	if (q_id == D_QUOTE)
	{
		cmd = expand_quote_var(cmd, idx, q_id);
		if (cmd == NULL)
		{
			free_token_list(j_list);
			free_and_exit();
		}
	}
	while (cmd[++(*idx)] != q_id)
	{
		if (cmd[*idx] == ' ')
			i[4]++;
	}
	(*idx) = (*idx) - 3;
	cmd = treat_quotes_ctrl(cmd, i, q_id, j_list);
	return (cmd);
}

static char	*check_second_quote(char *command, int *idx,
				int q_id, t_token_m *token_list)
{
	int	j;

	j = *idx;
	while (command[j++] != '\0')
	{
		if (command[j] == q_id)
		{
			command = treat_quotes(command, idx, q_id, token_list);
			break ;
		}
	}
	return (command);
}

char	*treat_command_ctrl(char *cmd, t_token_m *token_list, int i)
{
	if (cmd[i + 1] == D_QUOTE || cmd[i + 1] == S_QUOTE)
		cmd[i] = ' ';
	else if (cmd[i + 1] == '?')
	{
		cmd = expand_error(cmd, i);
		if (cmd == NULL)
		{
			free_token_list(token_list);
			free_and_exit();
		}
	}
	else if (cmd[i + 1])
	{
		cmd = expand_var(cmd, i--);
		if (cmd == NULL)
		{
			free_token_list(token_list);
			free_and_exit();
		}
	}
	return (cmd);
}

char	*treat_command(char *command, t_token_m *token_list)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '$' && command[i + 1] != '\0'
			&& command[i + 1] != ' ')
			command = treat_command_ctrl(command, token_list, i--);
		else if (command[i] == D_QUOTE)
			command = check_second_quote(command, &i, D_QUOTE, token_list);
		else if (command[i] == S_QUOTE)
			command = check_second_quote(command, &i, S_QUOTE, token_list);
		else if (command[i] == INPUT || command[i] == PIPE
			|| command[i] == OUTPUT)
		{
			command = set_space_for_redir(command, &i);
			if (command == NULL)
			{
				free_token_list(token_list);
				free_and_exit();
			}
		}
		i++;
	}
	return (command);
}
