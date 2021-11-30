/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 15:54:36 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 16:46:04 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	texture_jumptable(t_gamedata *gd, t_2int loc, char c)
{
	const int	mts = gd->window.max_texture_size;

	if (c == ENEMY_PATH_HORIZONTAL)
		write_texture_img(&gd->img, &gd->textures.path_horizontal, loc, mts);
	else if (c == ENEMY_PATH_VERTICAL)
		write_texture_img(&gd->img, &gd->textures.path_vertical, loc, mts);
	else if (c == ENEMY_PATH_CROSSING)
		write_texture_img(&gd->img, &gd->textures.path_crossing, loc, mts);
	else if (c == FLOOR_VARIATION_CHAR)
		write_texture_img(&gd->img, &gd->textures.floor_variation, loc, mts);
	else
	{
		write_texture_img(&gd->img, &gd->textures.floor, loc, mts);
		if (c == COLLECTIBLE_CHAR)
			write_texture_img(&gd->img, &gd->textures.collectible, loc, mts);
		else if (c == EXIT_CHAR
			&& gd->player.enemies_defeated != gd->enemy.amount)
			write_texture_img(&gd->img, &gd->textures.blocked_exit, loc, mts);
		else if (c == EXIT_CHAR)
			write_pikachu(gd, loc, mts);
		else if (c == WALL_CHAR)
			write_texture_img(&gd->img, &gd->textures.wall, loc, mts);
	}
}

void	write_map(t_gamedata *gamedata, t_2int *start_map_to_show)
{
	t_2int		loc;
	int			j;
	int			i;

	set_map_to_show(gamedata, start_map_to_show);
	j = 0;
	while (j < gamedata->window.viewable_mapsize.y)
	{
		i = 0;
		while (i < gamedata->window.viewable_mapsize.x)
		{
			loc.x = i * gamedata->window.max_texture_size;
			loc.y = j * gamedata->window.max_texture_size;
			texture_jumptable(gamedata, loc,
				gamedata->window.map_to_show[j][i]);
			i++;
		}
		j++;
	}
}

void	write_shrub(char **map, t_imginfo *img,
									t_imginfo *shrub_text, int max_text_size)
{
	t_2int	loc;
	t_2int	start;

	loc.y = 0;
	while (map[loc.y] != NULL)
	{
		loc.x = 0;
		while (map[loc.y][loc.x] != '\0')
		{
			if (map[loc.y][loc.x] == POKEMON_WALK_SHRUB_CHAR)
			{
				start.x = loc.x * max_text_size;
				start.y = loc.y * max_text_size;
				write_texture_img(img, shrub_text, start, max_text_size);
			}
			loc.x++;
		}
		loc.y++;
	}
}
