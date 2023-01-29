/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 20:40:35 by gafreita          #+#    #+#             */
/*   Updated: 2022/06/20 21:44:31 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*fill_line(char *buff, char *line);
static void		reffil_buffer(char *buff);
static size_t	ft_length(const char *str);

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	char		*line;
	int			check;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1 || read(fd, 0, 0) == -1)
		return (NULL);
	line = NULL;
	while (1)
	{
		check = 1;
		if (!buff[0])
			check = read(fd, buff, BUFFER_SIZE);
		if (check > 0)
			line = fill_line(buff, line);
		reffil_buffer(buff);
		if (!check || ft_strchr(line, '\n'))
			break ;
	}
	return (line);
}

static char	*fill_line(char *buff, char *line)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	aux = line;
	line = malloc(sizeof(char) * (ft_length(buff) + ft_length(line) + 1));
	if (!line)
		return (0);
	j = 0;
	while (aux && aux[i])
	{
		line [i] = aux[i];
		i++;
	}
	while (buff[j])
	{
		line[i++] = buff[j];
		if (buff[j++] == '\n')
			break ;
	}
	line[i] = '\0';
	if (aux)
		free(aux);
	return (line);
}

static void	reffil_buffer(char *buff)
{
	int	i;
	int	j;

	j = -1;
	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n' && j == -1)
			j = 0;
		else if (j >= 0)
		{
			buff[j] = buff[i];
			j++;
		}
		buff[i++] = 0;
	}
}

static size_t	ft_length(const char *str)
{
	size_t	cont;

	cont = 0;
	if (str == NULL)
		return (0);
	while (str[cont] != '\0')
	{
		if (str[cont] == '\n')
			return (cont + 1);
		cont ++;
	}
	return (cont);
}
