/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 12:18:56 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/25 19:37:05 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
#include <stdbool.h>
#include "so_long.h"

void	get_texture(void *mlx, t_imginfo *loc,
											char *texturename, bool is_sprite)
{
	loc->img = mlx_xpm_file_to_image(mlx, texturename, &loc->img_width,
															&loc->img_height);
	if (loc->img == NULL)
	{
		printf("%s\n", texturename);
		exit_with_message("Path to texture is invalid", 1);
	}
	loc->addr = mlx_get_data_addr(loc->img, &loc->bits_per_pixel,
											&loc->line_length, &loc->endian);
	if (loc->addr == NULL)
	{
		printf("%s\n", texturename);
		exit_with_message("mlx_get_data_addr failed", 1);
	}
	loc->is_sprite = is_sprite;
}

void	get_textures(t_textures* textures, void *mlx)
{
	get_texture(mlx, &textures->wall, WALL_TEXTURE, true);
	get_texture(mlx, &textures->player, PLAYER_TEXTURE, true);
	get_texture(mlx, &textures->collectible, COLLECTIBLE_TEXTURE, true);
	get_texture(mlx, &textures->unblocked_exit, UNBLOCKED_EXIT_TEXTURE, true);
	get_texture(mlx, &textures->blocked_exit, BLOCKED_EXIT_TEXTURE, true);
	get_texture(mlx, &textures->enemy[text_left], ENEMY_LEFT_TEXTURE, true);
	get_texture(mlx, &textures->enemy[text_right], ENEMY_RIGHT_TEXTURE, true);
	get_texture(mlx, &textures->enemy[text_up], ENEMY_UP_TEXTURE, true);
	get_texture(mlx, &textures->enemy[text_down], ENEMY_DOWN_TEXTURE, true);
	get_texture(mlx, &textures->floor, FLOOR_TEXTURE, false);
	get_texture(mlx, &textures->floor_variation, FLOOR_VARIATION_TEXTURE, false);
	get_texture(mlx, &textures->path_horizontal, PATH_HORIZONTAL, false);
	get_texture(mlx, &textures->path_vertical, PATH_VERTICAL, false);
	get_texture(mlx, &textures->path_crossing, PATH_CROSSING, false);
}
