/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 08:06:17 by avan-ber       #+#    #+#                */
/*   Updated: 2020/01/16 11:14:50 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	ft_strjoin_and_free(char **s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (s1 == 0 && s2 == 0)
		return (-1);
	s3 = (char*)malloc(ft_strlen_c(*s1, '\0') + ft_strlen_c(s2, '\0') + 1);
	if (s3 == 0)
		return (-1);
	i = 0;
	j = 0;
	while ((*s1)[i] != '\0')
	{
		s3[i] = (*s1)[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	free(*s1);
	*s1 = s3;
	return (1);
}

static int	free_rest_and_return(char *rest)
{
	free(rest);
	rest = 0;
	return (-1);
}

static int	ft_split_in_two(char **rest, char **line, char c)
{
	char	*str1;
	char	*str2;
	int		i;

	str1 = ft_strdup_c(*rest, c);
	if (str1 == 0)
		return (free_rest_and_return(*rest));
	i = ft_strlen_c(*rest, c);
	str2 = ft_strdup_c(*rest + i + 1, '\0');
	if (str2 == 0)
	{
		free(str1);
		return (free_rest_and_return(*rest));
	}
	if (rest != 0)
		free(*rest);
	*line = str1;
	*rest = str2;
	return (1);
}

static int	ft_new_line(int fd, char **rest, char **line)
{
	int		b_read;
	int		check;
	char	buf[BUFFER_SIZE + 1];

	b_read = 1;
	check = 0;
	while (ft_strlen_c(*rest, '\n') == -1 && b_read != 0)
	{
		b_read = read(fd, buf, BUFFER_SIZE);
		if (b_read == -1)
			return (free_rest_and_return(*rest));
		buf[b_read] = '\0';
		check = ft_strjoin_and_free(rest, buf);
		if (check == -1)
			return (free_rest_and_return(*rest));
	}
	if (b_read == 0)
	{
		*line = *rest;
		*rest = 0;
	}
	return (b_read);
}

int			get_next_line(int fd, char **line)
{
	static char	*fd_rest[OPEN_MAX];
	int			b_read;

	if (fd < 0 || line == 0)
		return (-1);
	if (!fd_rest[fd])
	{
		fd_rest[fd] = ft_strdup_c("", '\0');
		if (fd_rest[fd] == 0)
			return (-1);
	}
	if (ft_strlen_c(fd_rest[fd], '\n') == -1)
	{
		b_read = ft_new_line(fd, &fd_rest[fd], line);
		if (b_read == -1 || b_read == 0)
			return (b_read);
	}
	if (ft_split_in_two(&fd_rest[fd], line, '\n') == -1)
		return (-1);
	return (1);
}
