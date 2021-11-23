/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_frame.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 11:52:22 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/23 19:22:54 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
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
	float	step;
	int		i;
	int		j;
	int		color;

	step = (float)texture->img_width / (float)max_texture_size;
	j = 0;
	while (j < max_texture_size)
	{
		i = 0;
		while (i < max_texture_size)
		{
			color = get_color_from_texture(texture, (int)(i * step), (int)(j * step));
			if ((color & 0x00FFFFFF) != 0 || texture->is_sprite == false)
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
	printf("viewable_size.y: %d\n", viewable_size.y);
	if (player_pos.x - dx < 0)
	{
		middle.x = dx;
		printf("pos_x: %d\nJUMP: 1\n", player_pos.x);
	}
	else if (player_pos.x + dx >= mapsize.x)
	{
		middle.x = mapsize.x - (dx + (viewable_size.x % 2 == 1));
		printf("pos_x: %d\nJUMP: 2\n", player_pos.x);
	}
	else
	{
		middle.x = player_pos.x;
		printf("pos_x: %d\nJUMP: 3\n", player_pos.x);
	}
	if (player_pos.y - dy < 0)
		middle.y = dy;
	else if (player_pos.y + dy >= mapsize.y)
		middle.y = mapsize.y - (dy + (viewable_size.y % 2 == 1));
	else
		middle.y = player_pos.y;
	start.x = middle.x - dx;
	start.y = middle.y - dy;
	printf("size: %d-%d\n", start.x, start.y);
	printf("--------\n");
	return start;
}

void	set_map_to_show(t_gamedata* gamedate)
{
	t_2int	start;
	t_2int	loc;
	t_2int	size;

	start = get_start(gamedate->mapinfo.size,
					gamedate->window.viewable_mapsize, gamedate->player.pos);
	size = gamedate->window.viewable_mapsize;
	loc.y = 0;
	while (loc.y < size.y)
	{
		loc.x = 0;
		while (loc.x < size.x)
		{
			gamedate->window.map_to_show[loc.y][loc.x] =
						gamedate->mapinfo.map[loc.y + start.y][loc.x + start.x];
			loc.x++;
		}
		gamedate->window.map_to_show[loc.y][loc.x] = '\0';
		loc.y++;
	}
	gamedate->window.map_to_show[loc.y] = NULL;
}

void	texture_jumptable(t_gamedata *gamedata, t_2int loc, char c)
{
	const int	max_texture_size = gamedata->window.max_texture_size;

	if (c == '1')
		write_texture_to_image(&gamedata->img, &gamedata->textures.wall,
														loc, max_texture_size);
	else
	{
		write_texture_to_image(&gamedata->img, &gamedata->textures.floor,
														loc, max_texture_size);
		if (c == 'P')
			write_texture_to_image(&gamedata->img, &gamedata->textures.player,
														loc, max_texture_size);
		else if (c == 'C')
			write_texture_to_image(&gamedata->img,
						&gamedata->textures.collectible, loc, max_texture_size);
		else if (c == 'E' && gamedata->mapinfo.tokens == 0)
			write_texture_to_image(&gamedata->img,
					&gamedata->textures.unblocked_exit, loc, max_texture_size);
		else if (c == 'E')
			write_texture_to_image(&gamedata->img,
					&gamedata->textures.blocked_exit, loc, max_texture_size);
		else if (c == 'v')
			write_texture_to_image(&gamedata->img, &gamedata->textures.enemy,
														loc, max_texture_size);
	}
}

void	make_frame(t_gamedata* gamedata)
{
	t_2int		loc;
	int			j;
	int			i;

	set_map_to_show(gamedata);
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
	mlx_put_image_to_window(gamedata->mlx, gamedata->window.frame, gamedata->img.img, 0, 0);
}