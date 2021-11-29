/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_frame.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 11:52:22 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/29 19:01:40 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "so_long.h"

unsigned int	get_color_from_texture(t_imginfo *text, int x, int y)
{
	unsigned int	res;

	res = *(unsigned int*)
		(text->addr + y * text->line_length + x * (text->bits_per_pixel / 8));
	return res;
}

void	write_texture_to_image(t_imginfo *img, t_imginfo *texture, t_2int start,
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
			color = get_color_from_texture(texture, (int)(i * step), (int)(j * step));
			if (color != 0xFF000000 || texture->is_sprite == false)
				my_mlx_pixel_put(img, i + start.x, j + start.y, color);
			i++;
		}
		j++;
	}
}

t_2int	get_start(t_2int mapsize, t_2int viewable_size, t_2int player_pos)
{
	int		dx;
	int		dy;
	t_2int	middle;
	t_2int	start;

	dx = viewable_size.x / 2;
	dy = viewable_size.y / 2;
	if (player_pos.x - dx < 0)
		middle.x = dx;
	else if (player_pos.x + dx >= mapsize.x)
		middle.x = mapsize.x - (dx + (viewable_size.x % 2 == 1));
	else
		middle.x = player_pos.x;
	if (player_pos.y - dy < 0)
		middle.y = dy;
	else if (player_pos.y + dy >= mapsize.y)
		middle.y = mapsize.y - (dy + (viewable_size.y % 2 == 1));
	else
		middle.y = player_pos.y;
	start.x = middle.x - dx;
	start.y = middle.y - dy;
	return start;
}

void	set_map_to_show(t_gamedata* gamedata, t_2int start)
{
	t_2int	loc;
	t_2int	size;

	size = gamedata->window.viewable_mapsize;
	loc.y = 0;
	while (loc.y < size.y)
	{
		loc.x = 0;
		while (loc.x < size.x)
		{
			gamedata->window.map_to_show[loc.y][loc.x] =
						gamedata->mapinfo.map[loc.y + start.y][loc.x + start.x];
			loc.x++;
		}
		gamedata->window.map_to_show[loc.y][loc.x] = '\0';
		loc.y++;
	}
	gamedata->window.map_to_show[loc.y] = NULL;
}

void	texture_jumptable(t_gamedata *gamedata, t_2int loc, char c)
{
	const int	max_texture_size = gamedata->window.max_texture_size;

	if (c == ENEMY_PATH_HORIZONTAL)
		write_texture_to_image(&gamedata->img, &gamedata->textures.path_horizontal, loc, max_texture_size);
	else if (c == ENEMY_PATH_VERTICAL)
		write_texture_to_image(&gamedata->img, &gamedata->textures.path_vertical, loc, max_texture_size);
	else if (c == ENEMY_PATH_CROSSING)
		write_texture_to_image(&gamedata->img, &gamedata->textures.path_crossing, loc, max_texture_size);
	else if (c == FLOOR_VARIATION_CHAR)
		write_texture_to_image(&gamedata->img, &gamedata->textures.floor_variation, loc, max_texture_size);
	else
	{
		write_texture_to_image(&gamedata->img, &gamedata->textures.floor, loc, max_texture_size);
		if (c == COLLECTIBLE_CHAR)
			write_texture_to_image(&gamedata->img, &gamedata->textures.collectible, loc, max_texture_size);
		else if (c == EXIT_CHAR && gamedata->mapinfo.tokens == 0)
			write_texture_to_image(&gamedata->img, &gamedata->textures.unblocked_exit, loc, max_texture_size);
		else if (c == EXIT_CHAR)
			write_texture_to_image(&gamedata->img, &gamedata->textures.blocked_exit, loc, max_texture_size);
		else if (c == WALL_CHAR)
			write_texture_to_image(&gamedata->img, &gamedata->textures.wall, loc, max_texture_size);
	}
}

void	write_entity(t_gamedata *gamedata, t_entity *entity, t_2int *start,
															t_imginfo *texture)
{
	t_2int	pos;
	t_2int	loc;

	pos.x = entity->pos.x - start->x;
	pos.y = entity->pos.y - start->y;
	loc.x = pos.x * gamedata->window.max_texture_size;
	loc.y = pos.y * gamedata->window.max_texture_size;
	write_texture_to_image(&gamedata->img, texture, loc, gamedata->window.max_texture_size);
}

void	jumptable_entity_textures(t_gamedata *gamedata, t_entity *entity, t_2int *start, t_imginfo **entity_texture)
{
	if (entity->pos.x < start->x || entity->pos.x >= start->x + gamedata->window.viewable_mapsize.x)
		return ;
	if (entity->pos.y < start->y || entity->pos.y >= start->y + gamedata->window.viewable_mapsize.y)
		return ;
	if (entity->moved == true)
	{
		if (entity->delta.x == 1)
			write_entity(gamedata, entity, start, &entity_texture[entity->texture_id][text_right]);
		else if (entity->delta.x == -1)
			write_entity(gamedata, entity, start, &entity_texture[entity->texture_id][text_left]);
		else if (entity->delta.y == 1)
			write_entity(gamedata, entity, start, &entity_texture[entity->texture_id][text_down]);
		else
			write_entity(gamedata, entity, start, &entity_texture[entity->texture_id][text_up]);
	}
	else
		write_entity(gamedata, entity, start, &entity_texture[entity->texture_id][text_current]);
}

void	write_entities(t_gamedata *gamedata, t_2int *start)
{
	int		i;

	jumptable_entity_textures(gamedata, &gamedata->player, start,
												&gamedata->textures.player);
	i = 0;
	while (i < gamedata->enemy.amount)
	{
		if (gamedata->enemy.array[i].shown == true)
			jumptable_entity_textures(gamedata, &gamedata->enemy.array[i],
				start, gamedata->textures.enemy);
		i++;
	}
	i = 0;
	while (i < gamedata->pokemany.amount)
	{
		if (gamedata->pokemany.array[i].shown == true)
			jumptable_entity_textures(gamedata, &gamedata->pokemany.array[i],
				start, gamedata->textures.pokemany);
		i++;
	}
}

void	write_shrub(char **map, t_imginfo *img, t_imginfo *shrub_text, int max_text_size)
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
				write_texture_to_image(img, shrub_text, start, max_text_size);
			}
			loc.x++;
		}
		loc.y++; 
	}
}

void	write_stats(t_gamedata* gamedata)
{
	char	*str_to_print;
	char	*nbr;

	nbr = malloc_check(ft_itoa(gamedata->player.pokeballs));
	str_to_print = malloc_check(ft_strjoin("Amount of pokeballs: ", nbr));
	// mlx_string_put(gamedata->mlx, &gamedata->img, 0, 0, 0xFFFFFF, str_to_print);
	free(nbr);
	free(str_to_print);
}

void	make_frame(t_gamedata* gamedata)
{
	t_2int		loc;
	t_2int		start_map_to_show;
	int			j;
	int			i;

	printf("amout pokemon catched: %d\n", gamedata->player.pokemon);
	start_map_to_show = get_start(gamedata->mapinfo.size, gamedata->window.viewable_mapsize, gamedata->player.pos);
	set_map_to_show(gamedata, start_map_to_show);
	j = 0;
	while (j < gamedata->window.viewable_mapsize.y)
	{
		i = 0;
		while (i < gamedata->window.viewable_mapsize.x)
		{
			loc.x = i * gamedata->window.max_texture_size;
			loc.y = j * gamedata->window.max_texture_size;
			texture_jumptable(gamedata, loc, gamedata->window.map_to_show[j][i]);
			i++;
		}
		j++;
	}
	write_entities(gamedata, &start_map_to_show);
	write_shrub(gamedata->window.map_to_show, &gamedata->img,
		&gamedata->textures.shrub, gamedata->window.max_texture_size);
	write_stats(gamedata);
	mlx_put_image_to_window(gamedata->mlx, gamedata->window.frame, gamedata->img.img, 0, 0);
}