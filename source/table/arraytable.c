/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraytable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 10:23:29 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/07 07:39:15 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ht_item	*insert_table(char *key, char *value)
{
	t_ht_item	*new_item;

	new_item = create_array_item(key, value);
	return (new_item);
}

t_array_table	*create_array_table(int size)
{
	t_array_table	*arraytable;
	int				i;

	i = 0;
	arraytable = (t_array_table *)malloc(sizeof(t_array_table));
	if (!arraytable)
	{
		perror("Error: ");
		free_and_exit();
	}
	arraytable->size = size;
	arraytable->item = (t_ht_item **)ft_calloc(arraytable->size,
			sizeof(t_ht_item *));
	if (!arraytable->item)
	{
		perror("Error: ");
		free_and_exit();
	}
	while (i++ < arraytable->size - 1)
	{
		arraytable->item[i] = NULL;
	}
	return (arraytable);
}

t_ht_item	*create_array_item(char *key, char *value)
{
	t_ht_item	*new;

	new = (t_ht_item *)ft_calloc(sizeof(t_ht_item), 1);
	if (!new)
	{
		perror("Error: ");
		free_and_exit();
	}
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (new->key == NULL || new->value == NULL)
	{
		perror("Error: ");
		free_and_exit();
	}
	return (new);
}

t_array_table	*envp_to_array(char **envp)
{
	t_array_table	*table;
	char			*key;
	char			*value;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	table = create_array_table(i + 60);
	while (j < i)
	{
		key = find_key(envp[j]);
		value = find_value(envp[j]);
		table->item[j] = insert_table(key, value);
		j++;
		free(key);
		free(value);
	}
	return (table);
}
