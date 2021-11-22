/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 10:09:49 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/21 18:47:05 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "so_long.h"

int		ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

int		get_exponent(int base, int power)
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

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	my_mlx_pixel_put(t_imginfo *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}