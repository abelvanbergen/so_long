/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   imagesetup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 19:53:26 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/21 20:13:09 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_image(t_imginfo* img, void* mlx, t_2int size)
{
	img->img = mlx_new_image(mlx, size.x, size.y);
	if (img->img != NULL)
		exit_with_message("mlx_new_image failed", 1);
	img->addr = mlx_get_data_addr(img->img, img->bits_per_pixel,
											img->line_length, img->line_length);
	if (img->addr == NULL)
		exit_with_message("mlx_get_data_addr failed", 1);
}