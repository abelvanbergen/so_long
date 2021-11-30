/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_pokemon.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:28:03 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 17:33:48 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "so_long.h"

static int	set_pokemon(t_entity *pokemon, t_2int loc)
{
	set_entity(pokemon, loc, rand() % DIFFERENT_POKEMON);
	pokemon->delta.y = 1;
	pokemon->moved = false;
	return (1);
}

void	set_pokemany(t_bot *pokemany, int pokemon_spawn, char **map)
{
	t_2int		loc;
	const int	step = pokemon_spawn / pokemany->amount;
	int			pokemon_i;
	int			spawn_index;
	int			index_to_place_pokemon;

	pokemon_i = 0;
	spawn_index = 0;
	loc.y = 0;
	while (map[loc.y] != NULL)
	{
		loc.x = 0;
		while (map[loc.y][loc.x] != '\0')
		{
			if (ft_strchr(POKEMON_WALK_CHARS, map[loc.y][loc.x]) != NULL)
			{
				if (spawn_index % step == 0)
					index_to_place_pokemon = rand() % step;
				if (spawn_index % step == index_to_place_pokemon)
					pokemon_i += set_pokemon(&pokemany->array[pokemon_i], loc);
				spawn_index++;
			}
			loc.x++;
		}
		loc.y++;
	}
}
