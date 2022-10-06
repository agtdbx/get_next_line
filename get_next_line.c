/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:10:43 by aderouba          #+#    #+#             */
/*   Updated: 2022/10/06 19:03:33 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include <stdio.h>

int	is_in_string(char *str, char c)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	get_line_end(char *buffer)
{
	int		i;
	//int		j;
	//int		len;
	//int		nb;
	//char	*res;

	i = 0;
	//nb = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	return (i);
	/*len = 1;
	while (buffer[i + len] != '\0' && buffer[i + len] != '\n')
		len++;
	if (len == 0)
		return (NULL);
	res = malloc(sizeof(char) * (len + 2));
	if (res == NULL)
		return (NULL);
	j = 0;
	while (j <= len)
	{
		res[j] = buffer[i + j];
		j++;
	}
	res[j] = '\0';
	return (res);*/
}

void	buffer_shift(char *buffer, int shift)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
		i++;
	if (i <= shift)
		return ;
	i = 0;
	while (buffer[i + shift] != '\0')
	{
		buffer[i] = buffer[i + shift];
		i++;
	}
	buffer[i] = '\0';
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*res;
	int			i;
	int			len;

	if (buffer == NULL)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		i = read(fd, buffer, BUFFER_SIZE);
		buffer[i] = '\0';
	}
	len = get_line_end(buffer);
	if (len == 0)
		return (NULL);
	res = malloc(sizeof(char) * (len + 2));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		res[i] = buffer[i];
		i++;
	}
	res[i] = '\0';
	buffer_shift(buffer, len);
	return (res);
}
