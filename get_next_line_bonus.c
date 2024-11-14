/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:23:24 by asene             #+#    #+#             */
/*   Updated: 2024/11/14 20:57:56 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	replace_pointer(char **buffer, size_t eol_index)
{
	char	*temp;

	temp = *buffer;
	*buffer = ft_strdup(*buffer + eol_index + 1);
	free(temp);
}

static size_t	read_file_to_next_line(int fd, char **buffer)
{
	ssize_t	bytes_read;
	char	read_buffer[BUFFER_SIZE + 1];
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
		eol = *buffer + ft_strlen(*buffer) - 1;
	return (eol - *buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[_SC_OPEN_MAX] = {NULL};
	char		*line;
	int			eol;

	if (fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	eol = read_file_to_next_line(fd, &buffer[fd]);
	if (eol >= 0)
	{
		line = ft_substr(buffer[fd], 0, eol + 1);
		replace_pointer(&buffer[fd], eol);
	}
	else
	{
		line = NULL;
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
