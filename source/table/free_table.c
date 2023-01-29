/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:23:29 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/07 17:59:24 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tables(t_array_table *table)
{
	int				i;
	t_ht_item		*item;

	i = 0;
	if (table != NULL)
	{
		if (table->item)
		{
			while (i < table->size)
			{
				item = table->item[i];
				if (item)
					free_item(item);
				i++;
			}
			free(table->item);
		}
		free(table);
	}
}

void	free_item(t_ht_item *item)
{
	if (item->key)
		free(item->key);
	if (item->value)
		free(item->value);
	free(item);
}
