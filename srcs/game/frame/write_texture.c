/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_texture.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 15:53:09 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/12/02 10:58:49 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

unsigned int	get_color_from_texture(t_imginfo *text, int x, int y)
{
	unsigned int	res;

	res = *(unsigned int *)
		(text->addr + y * text->line_length + x * (text->bits_per_pixel / 8));
	return (res);
}

void	write_texture_img(t_imginfo *img, t_imginfo *texture, t_2int start,
														int max_texture_size)
{
	float			step;
	int				i;
	int				j;
	unsigned int	color;

	step = (float)texture->img_width / (float)max_texture_size;
	j = 0;
	while (j < max_texture_size)
	{
		i = 0;
		while (i < max_texture_size)
		{
			color = get_color_from_texture(texture,
					(int)(i * step), (int)(j * step));
			if (color != 0xFF000000 || texture->is_sprite == false)
				my_mlx_pixel_put(img, i + start.x, j + start.y, color);
			i++;
		}
		j++;
	}
}
