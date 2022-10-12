/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:10:41 by aderouba          #+#    #+#             */
/*   Updated: 2022/10/12 12:37:28 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*res;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	res = malloc(sizeof(char) * (i + j + 1));
	if (res == NULL)
		return (res);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	free(s1);
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, int len)
{
	char	*res;
	int		i;

	i = 0;
	while (s[start + i] != '\0' && i < len)
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	is_invalid_params(int fd)
{
	if (fd < 0 || fd >= 1024)
		return (1);
	if (read(fd, NULL, 0) == -1)
		return (1);
	if (BUFFER_SIZE <= 0)
		return (1);
	return (0);
}

void	free_buffer(char **buffer, int end_file)
{
	if (end_file == 1 && ft_strlen(*buffer) == 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
}
