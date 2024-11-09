/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:25:01 by asene             #+#    #+#             */
/*   Updated: 2024/11/09 14:02:56 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;

	new_str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		new_str[i++] = *(s1++);
	while (*s2)
		new_str[i++] = *(s2++);
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	src_len;
	int		i;
	char	*dup;

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
