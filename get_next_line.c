/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:10:43 by aderouba          #+#    #+#             */
/*   Updated: 2022/10/12 13:42:19 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_end_line(char *buffer)
{
	int	i;

	if (buffer == NULL)
		return (-2);
	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*read_line(char *buffer, int fd, int *end_file)
{
	char	*read_buffer;
	int		read_len;

	if (get_end_line(buffer) == -1)
	{
		read_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (read_buffer == NULL)
			return (NULL);
		read_buffer[0] = '\0';
		read_len = read(fd, read_buffer, BUFFER_SIZE);
		read_buffer[read_len] = '\0';
		if (read_len == 0 && ft_strlen(buffer) == 0)
		{
			free(read_buffer);
			free(buffer);
			*end_file = 1;
			return (NULL);
		}
		buffer = ft_strjoin(buffer, read_buffer);
		if (get_end_line(buffer) == -1 && read_len == BUFFER_SIZE)
			buffer = complete_buffer(buffer, read_buffer, end_file, fd);
		free(read_buffer);
	}
	return (buffer);
}

char	*complete_buffer(char *buffer, char *read_buffer, int *end_file, int fd)
{
	int	read_len;

	read_len = BUFFER_SIZE;
	while (get_end_line(buffer) == -1 && read_len == BUFFER_SIZE)
	{
		read_len = read(fd, read_buffer, BUFFER_SIZE);
		read_buffer[read_len] = '\0';
		buffer = ft_strjoin(buffer, read_buffer);
	}
	if (read_len != BUFFER_SIZE)
		*end_file = 1;
	return (buffer);
}

void	buffer_shift(char *buffer, int shift)
{
	int	i;

	i = 0;
	while (i + shift < ft_strlen(buffer))
	{
		buffer[i] = buffer[i + shift];
		i++;
	}
	buffer[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*res;
	int			end_line;
	static int	end_file = 0;

	if (is_invalid_params(fd))
		return (NULL);
	if (buffer == NULL && end_file == 0)
	{
		buffer = malloc(sizeof(char));
		if (buffer == NULL)
			return (NULL);
		buffer[0] = '\0';
	}
	if (end_file == 0)
		buffer = read_line(buffer, fd, &end_file);
	end_line = get_end_line(buffer) + 1;
	if (end_line == -1)
		return (NULL);
	if (end_line == 0)
		end_line = ft_strlen(buffer);
	res = ft_substr(buffer, 0, end_line);
	buffer_shift(buffer, end_line);
	free_buffer(&buffer, end_file);
	return (res);
}
