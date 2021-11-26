/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 12:18:56 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/26 13:00:43 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
#include <stdlib.h>
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


void	get_texture_entity(void *mlx, char *start_file_name, t_imginfo **texture)
{
	const char	*dir[] = {"up.xpm", "right.xpm", "down.xpm", "left.xpm", "current.xpm"};
	char		*file_name;
	int			i;
	t_imginfo	*entity_texture;

	i = 0;
	entity_texture = malloc(sizeof(t_imginfo) * 5);
	if (entity_texture == NULL)
		exit_with_message("malloc_falied", 1);
	while (i < 5)
	{
		file_name = ft_strjoin(start_file_name, dir[i]);
		if (file_name == NULL)
			exit_with_message("malloc failed", 1);
		get_texture(mlx, &entity_texture[i], file_name, true);
		free(file_name);
		i++;
	}
	*texture = entity_texture;
}

void	get_texture_entities(t_imginfo ***entities, void *mlx, char *entity_dir, int amount)
{
	char		*start_file_name;
	t_imginfo 	**array;
	int			i;
	const char	*names[] = {"woman/", "men/"};

	array = malloc(sizeof(t_imginfo*) * amount);
	if (array == NULL)
		exit_with_message("malloc failed", 1);
	i = 0;
	while (i < amount)
	{
		start_file_name = ft_strjoin(entity_dir, names[i]);
		if (start_file_name == NULL)
			exit_with_message("malloc failed", 1);
		get_texture_entity(mlx, start_file_name, &array[i]);
		free(start_file_name);
		i++;
	}
	*entities = array;
}

void	get_textures(t_textures* textures, void *mlx)
{
	get_texture(mlx, &textures->wall, WALL_TEXTURE, true);
	get_texture(mlx, &textures->player, PLAYER_TEXTURE, true);
	get_texture(mlx, &textures->collectible, COLLECTIBLE_TEXTURE, true);
	get_texture(mlx, &textures->unblocked_exit, UNBLOCKED_EXIT_TEXTURE, true);
	get_texture(mlx, &textures->blocked_exit, BLOCKED_EXIT_TEXTURE, true);
	// get_texture_entity(mlx, ENEMY_TEXTURE_LOC, textures->enemy);
	get_texture_entities(&textures->enemy, mlx, ENEMIES_TEXTURE_LOC, 2);
	get_texture(mlx, &textures->floor, FLOOR_TEXTURE, false);
	get_texture(mlx, &textures->floor_variation, FLOOR_VARIATION_TEXTURE, false);
	get_texture(mlx, &textures->path_horizontal, PATH_HORIZONTAL, false);
	get_texture(mlx, &textures->path_vertical, PATH_VERTICAL, false);
	get_texture(mlx, &textures->path_crossing, PATH_CROSSING, false);
}
