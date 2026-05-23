/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlu-bjor <wlu-bjor@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 12:42:39 by wlu-bjor          #+#    #+#             */
/*   Updated: 2026/05/23 15:55:18 by wlu-bjor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*exclude_line(char *buffer)
{
	char	*exclusion_buffer;
	size_t	len_line;
	size_t	i;

	if (!buffer)
		return (NULL);
	len_line = 0;
	while (buffer[len_line] && buffer[len_line] != '\n')
		len_line++;
	if (buffer[len_line] == '\n')
		len_line++;
	exclusion_buffer = malloc((ft_strlen(buffer) - len_line + 1)
			* sizeof(char));
	if (!exclusion_buffer)
		return (free(buffer), NULL);
	i = 0;
	while (buffer[len_line + i])
	{
		exclusion_buffer[i] = buffer[len_line + i];
		i++;
	}
	exclusion_buffer[i] = '\0';
	free(buffer);
	return (exclusion_buffer);
}

char	*find_line(char *buffer)
{
	char	*result_line;
	size_t	pos_eof;

	pos_eof = 0;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[pos_eof] && buffer[pos_eof] != '\n')
		pos_eof++;
	if (buffer[pos_eof] == '\n')
		pos_eof++;
	result_line = malloc((pos_eof + 1) * sizeof(char));
	if (!result_line)
		return (NULL);
	ft_strlcpy(result_line, buffer, pos_eof + 1);
	return (result_line);
}

static char	*move(char *res, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(res, buffer);
	free(res);
	return (temp);
}

static char	*read_bytes(int fd, char *result_buffer)
{
	int		bytes_read;
	char	*buffer;

	if (!result_buffer)
		result_buffer = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(result_buffer), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(result_buffer), NULL);
		buffer[bytes_read] = '\0';
		result_buffer = move(result_buffer, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	return (result_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_bytes(fd, buffer);
	if (!buffer)
		return (NULL);
	result_line = find_line(buffer);
	if (!result_line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = exclude_line(buffer);
	return (result_line);
}
