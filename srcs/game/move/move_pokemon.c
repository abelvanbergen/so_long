/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_pokemon.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:49:54 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/12/01 18:16:55 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

static bool	is_valid_place_for_pokemon(t_entity *pokemon, t_tile_sides dir,
							char *tile, t_gamedata *gamedata)
{
	t_2int	temp_delta;
	t_2int	temp_pos;

	temp_delta.x = pokemon->delta.x;
	temp_delta.y = pokemon->delta.y;
	turn(&temp_delta, dir);
	temp_pos.x = pokemon->pos.x + temp_delta.x;
	temp_pos.y = pokemon->pos.y + temp_delta.y;
	if (tile[dir] != tile[current])
		return (false);
	if (temp_pos.x == gamedata->player.pos.x
		&& temp_pos.y == gamedata->player.pos.y)
		return (false);
	return (true);
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
		if (is_valid_place_for_pokemon(pokemon, (i + order) % 5,
				tile, gamedata))
		{
			turn(&pokemon->delta, (i + order) % 5);
			break ;
		}
		i++;
	}
	tile[front] = get_tile(pokemon->pos.x + pokemon->delta.x,
			pokemon->pos.y + pokemon->delta.y, gamedata->mapinfo.map);
	pokemon->moved = true;
	if (tile[front] == tile[current] && !is_next_pos_entity(&gamedata->pokemany,
			pokemon, pokemon_moved_on_pokemon))
		move_entity_pos(pokemon);
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