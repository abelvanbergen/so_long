/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 18:27:18 by avan-ber       #+#    #+#                */
/*   Updated: 2019/11/27 18:52:20 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_c(const char *s1, char c)
{
	int		i;
	char	*s2;

	i = 0;
	while (s1[i] != c)
		i++;
	s2 = (char *)malloc(i + 1);
	if (!s2)
		return (0);
	i = 0;
	while (s1[i] != c)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

int		ft_strlen_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}
