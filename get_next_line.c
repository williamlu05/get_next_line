/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlu-bjor <wlu-bjor@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 12:42:39 by wlu-bjor          #+#    #+#             */
/*   Updated: 2026/05/20 11:48:29 by wlu-bjor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*exclude_line(char *buffer)
{
	char	*exclusion_buffer;
	int		len_line;
	int		i;

	len_line = 0;
	while (buffer[len_line] && buffer[len_line] != '\n')
		len_line++;
	exclusion_buffer = malloc((ft_strlen(buffer) - len_line + 1) * sizeof(char));
	if (!exclusion_buffer)
		return (NULL);
	i = 0;
	while (buffer[len_line + i])
	{
		exclusion_buffer[i] = buffer[len_line + i];
		len_line++;
	}
	// ft_strlcpy(exclusion_buffer + i + 1, buffer, i); // Esto añadirá un \n al final del buffer que sobre, estaŕia mal creo
	free(buffer);
	return (exclusion_buffer);
}

char	*find_line(char *buffer)
{
	char	*result_line;
	int		pos_eof;

	pos_eof = 0;
	while (buffer[pos_eof] && buffer[pos_eof] != '\n')
		pos_eof++;
	// A lo mejor se debería añadir aquí un eol si no hay un eol, por si se ha leído el fin del archivo
	result_line = malloc((pos_eof + 2) * sizeof(char));
	if (!result_line)
		return (NULL);
	ft_strlcpy(result_line, buffer, pos_eof + 2);
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
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), NULL);
		buffer[bytes_read] = '\0'; // importante porque no se vacía este buffer, por lo que debes delimitar para que no se interprete ningún valor de la anterior lectura
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

	if (fd < 0)
		return (NULL);
	buffer = read_bytes(fd, buffer);
	if (!buffer)
		return (NULL);
	result_line = find_line(buffer);
	buffer = exclude_line(buffer);
	return (result_line);
}

// Utilizo calloc para tener el delimitador de string siempre disponible
// Así no tengo que ocuparme de siempre añadir \0 al final de lo que se escriba en el buffer
// lo cual puede ser cualquier cantidad