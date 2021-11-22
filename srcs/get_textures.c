/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_textures.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 12:18:56 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/21 17:35:47 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_texture(void *mlx, t_imginfo *loc, char *texturename)
{
	loc->img = mlx_png_file_to_image(mlx, texturename, &loc->img_width,
															&loc->img_height);
	if (loc->img == NULL)
		exit_with_message("Path to texture is invalid", 1);
	loc->addr = mlx_get_data_addr(loc->img, &loc->bits_per_pixel,
											&loc->line_length, &loc->endian);
	if (loc->addr == NULL)
		exit_with_message("mlx_get_data_addr failed", 1);
}

void	get_textures(t_textures* textures, void *mlx)
{
	get_texture(mlx, &textures->wall, WALL_TEXTURE);
	get_texture(mlx, &textures->player, PLAYER_TEXTURE);
	get_texture(mlx, &textures->collectible, COLLECTIBLE_TEXTURE);
	get_texture(mlx, &textures->unblocked_exit, UNBLOCKED_EXIT_TEXTURE);
	get_texture(mlx, &textures->blocked_exit, BLOCKED_EXIT_TEXTURE);
	get_texture(mlx, &textures->enemy, ENEMY_TEXTURE);
}