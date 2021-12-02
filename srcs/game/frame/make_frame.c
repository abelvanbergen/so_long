/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_frame.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/22 11:52:22 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/12/02 09:57:26 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "so_long.h"

static t_2int	get_start(t_2int mapsize,
									t_2int viewable_size, t_2int player_pos)
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
	return (start);
}

static void	write_line_on_window(char *first_part, int nbr,
											t_gamedata *gamedata, t_2int loc)
{
	char	*str_to_print;
	char	*str_nbr;

	str_nbr = malloc_check(ft_itoa(nbr));
	str_to_print = malloc_check(ft_strjoin(first_part, str_nbr));
	mlx_string_put(gamedata->mlx, gamedata->window.frame,
		loc.x, loc.y, 0x0, str_to_print);
	free(str_nbr);
	free(str_to_print);
}

static void	write_stats(t_gamedata *gamedata)
{
	t_2int	loc;

	loc.x = 5;
	loc.y = 10;
	write_line_on_window("Moves done: ",
		gamedata->player.move_counter, gamedata, loc);
	loc.x = 5;
	loc.y = 20;
	write_line_on_window("Pokeballs: ",
		gamedata->player.pokeballs, gamedata, loc);
	loc.x = 5;
	loc.y = 30;
	write_line_on_window("Pokemon catched: ",
		gamedata->player.pokemon, gamedata, loc);
	loc.x = 5;
	loc.y = 40;
	write_line_on_window("Teamrocket: ", gamedata->enemy.amount
		- gamedata->player.enemies_defeated, gamedata, loc);
}

void	make_frame(t_gamedata *gamedata)
{
	t_2int		start_map_to_show;

	start_map_to_show = get_start(gamedata->mapinfo.size,
			gamedata->window.viewable_mapsize, gamedata->player.pos);
	write_map(gamedata, &start_map_to_show);
	write_entities(gamedata, &start_map_to_show);
	write_shrub(gamedata->window.map_to_show, &gamedata->img,
		&gamedata->textures.shrub, gamedata->window.max_texture_size);
	mlx_put_image_to_window(gamedata->mlx, gamedata->window.frame,
		gamedata->img.img, 0, 0);
	write_stats(gamedata);
}
