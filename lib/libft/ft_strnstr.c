/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 13:08:11 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/10/26 16:37:28 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (needle[i] == '\0')
		return ((char *)&haystack[i]);
	while (haystack[i] != '\0' && i + needle_len <= len)
	{
		if (ft_strncmp(haystack + i, needle, needle_len) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
