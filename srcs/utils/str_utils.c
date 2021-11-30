/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 17:14:43 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 17:16:33 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "so_long.h"

int	str_is_only_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_and_free(char *str1, char *str2)
{
	int		len_str1;
	int		len_str2;
	char	*new;

	len_str1 = ft_strlen(str1);
	len_str2 = ft_strlen(str2);
	new = (char *)malloc(sizeof(char) * (len_str1 + len_str2 + 1));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, str1, len_str1 + 1);
	ft_strlcpy(new + len_str1, str2, len_str2 + 1);
	new[len_str1 + len_str2] = '\0';
	free(str1);
	return (new);
}

char	*ft_strjoin3(char *str1, char *str2, char *str3)
{
	int		len_str1;
	int		len_str2;
	int		len_str3;
	char	*new;

	len_str1 = ft_strlen(str1);
	len_str2 = ft_strlen(str2);
	len_str3 = ft_strlen(str3);
	new = (char *)malloc(sizeof(char) * (len_str1 + len_str2 + len_str3 + 1));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, str1, len_str1 + 1);
	ft_strlcpy(new + len_str1, str2, len_str2 + 1);
	ft_strlcpy(new + len_str1 + len_str2, str3, len_str3 + 1);
	new[len_str1 + len_str2 + len_str3] = '\0';
	return (new);
}
