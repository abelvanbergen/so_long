/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 09:04:55 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/10/26 11:45:00 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_testsubstr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*str;

	i = 0;
	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	if (start + len <= s_len)
		str = (char *)malloc(len + 1);
	else
		str = (char *)malloc(s_len - start + 1);
	if (str == 0)
		return (0);
	while (i < len && s[start + i] != '\0')
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**free_array(char **array, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	wordcount;

	i = 0;
	wordcount = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			wordcount++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c)
			i++;
	}
	return (wordcount);
}

int	ft_wordlen(const char *str, unsigned int start, char c)
{
	while (str[start] != c && str[start] != '\0')
		start++;
	return (start);
}

char	**fill_array(char **array, const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			array[j] = ft_testsubstr(s, i, ft_wordlen(s, i, c) - i);
			if (array[j] == NULL)
				return (free_array(array, j));
			j++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c)
			i++;
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (s == NULL)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (array == NULL)
		return (NULL);
	return (fill_array(array, s, c));
}
