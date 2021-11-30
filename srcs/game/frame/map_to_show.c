/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_to_show.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 15:53:55 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 17:25:23 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_map_to_show(t_gamedata *gamedata, t_2int *start)
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
			gamedata->window.map_to_show[loc.y][loc.x]
				= gamedata->mapinfo.map[loc.y + start->y][loc.x + start->x];
			loc.x++;
		}
		gamedata->window.map_to_show[loc.y][loc.x] = '\0';
		loc.y++;
	}
	gamedata->window.map_to_show[loc.y] = NULL;
}
