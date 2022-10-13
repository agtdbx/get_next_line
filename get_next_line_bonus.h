/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:05:46 by aderouba          #+#    #+#             */
/*   Updated: 2022/10/13 12:57:49 by aderouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_buf
{
	char	*buffer;
	int		end_file;
}	t_buf;

int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, int len);
void	free_buffer(char **buffer, int end_file);
int		get_end_line(char *buffer);

char	*read_line(char *buffer, int fd, int *end_file);
char	*complete_buffer(char *buffer, char *read_buffer, int *end_file,
			int fd);
void	buffer_shift(char *buffer, int shift);
char	*get_next_line(int fd);

#endif
