/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_to_str_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:13:12 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/06 14:03:28 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**array_to_str_arr(t_array_table *n_env)
{
	int		i;
	int		j;
	char	**ret;
	char	*str_start;

	j = 0;
	i = 0;
	while (n_env->item[j])
		j++;
	ret = (char **)malloc((j + 1) * sizeof(char *));
	while (n_env->item[i])
	{
		str_start = ft_strjoin(n_env->item[i]->key, "=");
		ret[i] = ft_strjoin(str_start, n_env->item[i]->value);
		free(str_start);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
