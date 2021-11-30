/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_entities.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 13:54:01 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 17:31:29 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "so_long.h"

void	set_entity(t_entity *dest, t_2int pos, int texture_id)
{
	ft_bzero(dest, sizeof(t_entity));
	dest->pos.x = pos.x;
	dest->pos.y = pos.y;
	dest->delta.x = 0;
	dest->delta.y = 1;
	dest->texture_id = texture_id;
	dest->pokeballs = 0;
	dest->pokemon = 0;
	dest->enemies_defeated = 0;
	dest->shown = true;
	dest->moved = true;
}

void	set_entities(t_gamedata *gamedata, int amount_pokemon_spawn)
{
	gamedata->enemy.array = malloc_check(malloc(
				sizeof(t_entity) * gamedata->enemy.amount));
	gamedata->pokemany.array = malloc_check(malloc(
				sizeof(t_entity) * gamedata->pokemany.amount));
	set_player_and_enemies(&gamedata->player,
		&gamedata->enemy, gamedata->mapinfo.map);
	set_pokemany(&gamedata->pokemany,
		amount_pokemon_spawn, gamedata->mapinfo.map);
}
