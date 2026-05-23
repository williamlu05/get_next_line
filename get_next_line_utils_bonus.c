/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlu-bjor <wlu-bjor@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 12:43:18 by wlu-bjor          #+#    #+#             */
/*   Updated: 2026/05/23 18:16:22 by wlu-bjor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Returns length of string 's'
size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length])
		length++;
	return (length);
}

// Returns pointer to first occ of 'c' in string 's', NULL if not found
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && (unsigned char) s[i] != (unsigned char) c)
		i++;
	if ((unsigned char) s[i] == (unsigned char) c)
		return ((char *) s + i);
	else
		return ((void *) 0);
}

// Returns new string as combination of two strings
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size_first;
	size_t	size_second;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	size_first = ft_strlen(s1);
	size_second = ft_strlen(s2);
	result = malloc((size_first + size_second + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, size_first + size_second + 1);
	ft_strlcpy(result + size_first, s2, size_second + 1);
	return (result);
}
// comprobar que funcione ultimo ft_strlcpy

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size > 0)
	{
		i = 0;
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

// Returns memory allocation, with all bytes initiated to 0
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			bytes;
	void			*ptr;
	size_t			i;
	unsigned char	*p;

	bytes = nmemb * size;
	if (size && (bytes / size) != nmemb)
		return (NULL);
	ptr = malloc(bytes);
	if (!ptr)
		return (NULL);
	i = 0;
	p = (unsigned char *) ptr;
	while (i < bytes)
		p[i++] = '\0';
	return (ptr);
}
