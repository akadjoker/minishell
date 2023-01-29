/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:23:29 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/07 18:13:40 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_shlv_str(void)
{
	int	c;

	c = 0;
	while (g_shell.env->item[c] && c <= g_shell.env->size - 1)
	{
		if (!ft_strcmp(g_shell.env->item[c]->key, "SHLVL"))
			return (g_shell.env->item[c]->value);
		c++;
	}
	return ("");
}

void	change_shlv(void)
{
	char	*value;
	char	*nvalue;
	int		level;

	level = 0;
	value = get_shlv_str();
	if (is_integer(value) == 1)
	{
		level = ft_atoi(value);
		level += 1;
		nvalue = ft_itoa(level);
		insert_or_modify_by_key("SHLVL", nvalue);
		free (nvalue);
	}
}
