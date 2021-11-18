/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 13:39:15 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/10/26 11:48:26 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	if (s == 0)
		return (0);
	str = (char *)malloc(ft_strlen(s) + 1);
	if (str == 0)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = (f)(i, (const char)s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
