/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:10:41 by aderouba          #+#    #+#             */
/*   Updated: 2022/10/13 14:17:46 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	free_buffer(char **buffer, int end_file)
{
	int	len;

	len = ft_strlen(*buffer);
	if (end_file == 1 && len == 0)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

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
