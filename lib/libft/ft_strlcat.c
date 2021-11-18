/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 09:56:03 by avan-ber       #+#    #+#                */
/*   Updated: 2019/11/18 10:13:35 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t src_l;
	size_t dst_l;

	src_l = ft_strlen(src);
	dst_l = ft_strlen(dst);
	if (dstsize == 0)
		return (src_l);
	if (dstsize > dst_l + 1)
		ft_strlcpy(dst + dst_l, src, dstsize - dst_l);
	if (dstsize > dst_l)
		return (dst_l + src_l);
	else
		return (dstsize + src_l);
}
