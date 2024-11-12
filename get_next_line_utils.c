/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:25:01 by asene             #+#    #+#             */
/*   Updated: 2024/11/12 16:22:03 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdint.h"

void	*ft_calloc(size_t count, size_t element_size)
{
	unsigned char	*ptr;
	size_t			total_size;

	if (SIZE_MAX / element_size < count || count == 0 || element_size == 0)
		return (NULL);
	total_size = count * element_size;
	ptr = malloc(total_size);
	if (ptr != NULL)
	{
		while (total_size-- > 0)
		ptr[total_size] = 0;
	}
	return (ptr);
}
char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

char	*ft_join_and_free(char **s1, char const *s2)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * (ft_strlen(*s1) + ft_strlen(s2) + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (**s1)
		new_str[i++] = *(*s1++);
	while (*s2)
		new_str[i++] = *(s2++);
	new_str[i] = '\0';
	free(*s1);
	return (new_str);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t			src_len;
	unsigned int	i;
	char			*dup;

	src_len = ft_strlen(str);
	if (start >= src_len)
		len = 0;
	else if (len > src_len - start)
		len = src_len - start;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < len && (str + start)[i])
	{
		dup[i] = (str + start)[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dup;

	dup = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
