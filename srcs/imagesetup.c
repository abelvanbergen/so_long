/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   imagesetup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 19:53:26 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/22 18:08:42 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "so_long.h"

void	get_image(t_imginfo* img, void* mlx, t_2int gridsize, int texturesize)
{
	t_2int	size;

	size.x = gridsize.x * texturesize;
	size.y = gridsize.y * texturesize;
	img->img = mlx_new_image(mlx, size.x, size.y);
	if (img->img == NULL)
		exit_with_message("mlx_new_image failed", 1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
											&img->line_length, &img->endian);
	if (img->addr == NULL)
		exit_with_message("mlx_get_data_addr failed", 1);
}