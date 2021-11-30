/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_pokemon.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:49:54 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 17:28:22 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

void	move_pokemon_away_from_player(char **map, t_entity *pokemon)
{
	char	tile[5];

	set_sides(tile, pokemon, map);
	if (tile[current] == tile[back])
		turn(&pokemon->delta, back);
	else if (tile[current] == tile[right])
		turn(&pokemon->delta, right);
	else
		turn(&pokemon->delta, left);
}

void	move_pokemon(t_entity *pokemon, t_gamedata *gamedata)
{
	char			tile[5];
	t_tile_sides	order;
	int				i;

	order = rand() % 5;
	set_sides(tile, pokemon, gamedata->mapinfo.map);
	i = 0;
	while (i < 5)
	{
		if (tile[current] == tile[(i + order) % 5])
		{
			turn(&pokemon->delta, (i + order) % 5);
			break ;
		}
		i++;
	}
	if (pokemon->pos.x + pokemon->delta.x == gamedata->player.pos.x && pokemon->pos.y + pokemon->delta.y == gamedata->player.pos.y)
		move_pokemon_away_from_player(gamedata->mapinfo.map, pokemon);
	tile[front] = get_tile(pokemon->pos.x + pokemon->delta.x, pokemon->pos.y + pokemon->delta.y, gamedata->mapinfo.map);
	if (tile[front] == tile[current] && !is_next_pos_entity(&gamedata->pokemany, pokemon, pokemon_moved_on_pokemon))
	{
		pokemon->pos.x += pokemon->delta.x;
		pokemon->pos.y += pokemon->delta.y;
		pokemon->moved = true;
	}
	else
		pokemon->moved = false;
}

void	move_pokemany(t_gamedata *gamedata, t_bot *pokemany)
{
	int			i;
	t_entity	*pokemon;

	i = 0;
	while (i < pokemany->amount)
	{
		if (pokemany->array[i].shown == true)
		{
			pokemon = &pokemany->array[i];
			move_pokemon(pokemon, gamedata);
		}
		i++;
	}
}