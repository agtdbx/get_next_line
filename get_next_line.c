/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:10:43 by aderouba          #+#    #+#             */
/*   Updated: 2022/10/10 15:10:15 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stdio.h>

int	get_line_end(t_buffer *buf)
{
	int		i;

	i = 0;
	while (buf->buffer[i] != '\n' && buf->buffer[i] != '\0')
		i++;
	return (i);
}

int	is_end_line(char *read_buffer, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (read_buffer[i] == '\n' || read_buffer[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	clear_buffer(char *read_buffer)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		read_buffer[i] = '\0';
		i++;
	}
}

void	buffer_shift(t_buffer *buf, int shift)
{
	int	i;

	i = 0;
	while (buf->buffer[i] != '\0')
		i++;
	if (i < shift)
		return ;
	i = 0;
	while (buf->buffer[i + shift] != '\0')
	{
		buf->buffer[i] = buf->buffer[i + shift];
		i++;
	}
	buf->buffer[i] = '\0';
	buf->size -= shift;
}
#include <stdio.h>
void	add_to_buffer(t_buffer *buf, char *read_buffer)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (buf->buffer[i] != '\0')
		i++;
	j = 0;
	while(read_buffer[j] != '\0' && j < BUFFER_SIZE)
		j++;
	res = malloc(sizeof(char) * (i + j + 1));
	if (res == NULL)
		return ;
	i = 0;
	while (buf->buffer[i] != '\0')
	{
		res[i] = buf->buffer[i];
		i++;
	}
	j = 0;
	while(read_buffer[j] != '\0' && j < BUFFER_SIZE)
	{
		res[i + j] = read_buffer[j];
		j++;
	}
	res[i + j] = '\0';
	free(buf->buffer);
	buf->buffer = res;
	buf->size = i + j - 1;
}

void	set_buffer(t_buffer *buf, int fd)
{
	int		read_len;
	char	*read_buffer;

	if (buf->buffer == NULL)
	{
		buf->buffer = malloc(sizeof(char));
		if (buf->buffer == NULL)
			return ;
		buf->buffer[0] = '\0';
		buf->size = 0;
		read_buffer = malloc(sizeof(char) * BUFFER_SIZE);
		if (read_buffer == NULL)
			return ;
	}
	if (is_end_line(buf->buffer, buf->size - 1) == 0)
	{
		read_len = read(fd, read_buffer, BUFFER_SIZE);
		while (read_len > 0 && is_end_line(read_buffer, BUFFER_SIZE) == 0)
		{
			add_to_buffer(buf, read_buffer);
			clear_buffer(read_buffer);
			read_len = read(fd, read_buffer, BUFFER_SIZE);
		}
		if (read_len > 0 && is_end_line(read_buffer, BUFFER_SIZE))
			add_to_buffer(buf, read_buffer);
	}
}

char	*get_next_line(int fd)
{
	static t_buffer	buf;
	char		*res;
	int			i;
	int			len;

	set_buffer(&buf, fd);
	len = get_line_end(&buf);
	if (len == 0)
		return (NULL);
	res = malloc(sizeof(char) * (len + 2));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		res[i] = buf.buffer[i];
		i++;
	}
	res[i] = '\0';
	buffer_shift(&buf, len + 1);
	return (res);
}
