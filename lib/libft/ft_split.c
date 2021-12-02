/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/11 09:04:55 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/12/02 11:14:32 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

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
			array[j] = ft_substr(s, i, ft_wordlen(s, i, c) - i);
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
