/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 10:09:49 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/30 17:16:30 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "so_long.h"

int	get_exponent(int base, int power)
{
	int	exponent;
	int	nb;

	exponent = 1;
	nb = base;
	while (nb != power)
	{
		nb *= base;
		exponent++;
	}
	return (exponent);
}

void	my_mlx_pixel_put(t_imginfo *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	*malloc_check(void *content)
{
	if (content == NULL)
		exit_with_message("Malloc failed", 1);
	return (content);
}
