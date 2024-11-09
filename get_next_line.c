/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:24:40 by asene             #+#    #+#             */
/*   Updated: 2024/11/09 15:39:08 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*replace_pointer(void **dest, void *new)
{
	void *temp;

	temp = *dest;
	*dest = new;
	free(temp);
}

static char *join_and_free(char **buffer, char *new_content)
{
	char *temp;

	if (buffer)
	{
		temp = ft_strjoin(*buffer, new_content);
		free(*buffer);
		*buffer = temp;
	}
	else
		*buffer = new_content;
	return (*buffer);
}

static void	read_file_to_next_line(int fd, char **buffer, char **next_eol)
{
	size_t	bytes_read;
	char    read_buffer[BUFFER_SIZE + 1];

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			break ;
		read_buffer[bytes_read] = '\0';
		join_and_free(buffer, read_buffer);
		*next_eol = ft_strchr(*buffer, '\n');
		if (*next_eol)
			break ;
	}
}

char	*get_next_line(int	fd)
{
	static char	*buffer = NULL;
	static int	file_end = 0;
	char		*line;
	char		*eol;
	char		*temp;

	if (file_end)
		return NULL;
	if (buffer == NULL)
		buffer = malloc(BUFFER_SIZE + 1);
	eol = ft_strchr(buffer, '\n');
	if (eol == NULL)
		read_file_to_next_line(fd, &buffer, &eol);
	line = ft_substr(buffer, 0, eol - buffer + 1);
	if (eol && *(eol + 1))
		replace_pointer((void **)&buffer, ft_strdup(eol + 1));
	else
	{
		file_end = 1;
		free(buffer);
	}
	return (line);
}
