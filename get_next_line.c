/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:24:40 by asene             #+#    #+#             */
/*   Updated: 2024/11/12 17:45:42 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static void	replace_pointer(char **buffer, size_t eol_index)
{
    char	*temp;

	if (eol_index == -1)
		**buffer = '\0';
	else
	{
		temp = *buffer;
		*buffer = ft_strdup(*buffer + eol_index + 1);
		free(temp);
	}
}

static size_t	read_file_to_next_line(int fd, char **buffer)
{
	ssize_t	bytes_read;
	char    read_buffer[BUFFER_SIZE + 1];
	char	*eol;

	eol = ft_strchr(*buffer, '\n');
	bytes_read = 1;
	while (bytes_read > 0 && eol == NULL)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		read_buffer[bytes_read] = '\0';
		if (buffer && *buffer)
			*buffer = ft_join_and_free(buffer, read_buffer);
		else
			*buffer = ft_strdup(read_buffer);
		eol = ft_strchr(*buffer, '\n');
	}
	if (bytes_read == 0)
		eol = *buffer + ft_strlen(*buffer);
	if (eol)
		return (eol - *buffer);
	else
		return (-1);
}

char	*get_next_line(int	fd)
{
	static char	*buffer = NULL;
	char		*line;
	int			eol;

	if (fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	eol = read_file_to_next_line(fd, &buffer);
	if (eol >= 0 && buffer[eol + 1])
	{
		line = ft_substr(buffer, 0, eol + 1);
		replace_pointer(&buffer, eol);
	}
	else
	{
		line = NULL;
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
