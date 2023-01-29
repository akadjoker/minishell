/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrosa-do <lrosa-do@student.42lisboa>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:44:33 by lrosa-do          #+#    #+#             */
/*   Updated: 2023/01/05 18:42:32 by lrosa-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_endl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		return (1);
	return (0);
}

static char	*get_line(char **buffer_static)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer_static)
		return (NULL);
	while ((*buffer_static)[i] != '\0' && (*buffer_static)[i] != '\n')
		i++;
	line = ft_substr(*buffer_static, 0, i + is_endl(*buffer_static));
	if (!line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*get_storage(char **buffer_static)
{
	char	*backup;
	int		i;

	i = 0;
	if (!buffer_static)
		return (NULL);
	while ((*buffer_static)[i] != '\0' && (*buffer_static)[i] != '\n')
		i++;
	if ((*buffer_static)[i] == '\0')
	{
		free(*buffer_static);
		return (NULL);
	}
	backup = ft_substr(*buffer_static, i + 1, ft_strlen(*buffer_static) - i);
	if (!backup)
	{
		free(backup);
		return (NULL);
	}
	free(*buffer_static);
	return (backup);
}

static int	read_line(int fd, char **buffer, char **buffer_static, char **line)
{
	int		bytes_read;
	char	*holder;

	bytes_read = 1;
	while (is_endl(*buffer_static) != 1 && bytes_read > 0)
	{
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[bytes_read] = '\0';
		holder = *buffer_static;
		*buffer_static = ft_strjoin(holder, *buffer);
		free(holder);
	}
	free(*buffer);
	*line = get_line(buffer_static);
	if (**line == '\0')
	{
		free(*line);
		*line = NULL;
	}
	*buffer_static = get_storage(buffer_static);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*buffer_static;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (!buffer_static)
		buffer_static = ft_strdup("");
	bytes_read = read_line(fd, &buffer, &buffer_static, &line);
	if (bytes_read == 0 && !line)
		return (NULL);
	return (line);
}
