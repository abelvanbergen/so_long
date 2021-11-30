/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:51:34 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 17:25:59 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "so_long.h"

void	pokemon_moved_on_pokemon(t_entity *moved, t_entity *collided)
{
	(void)moved;
	(void)collided;
	return ;
}

void	turn_enemies_backwards(t_entity *moved, t_entity *collided)
{
	if (is_face_to_face(moved, collided))
		turn(&collided->delta, back);
	turn(&moved->delta, back);
}

void	player_try_catch_pokemon(t_entity *player, t_entity *pokemon)
{
	if (player->pokeballs == 0)
		exit(0); //pokemon defeat player
	player->pokeballs--;
	player->pokemon++;
	pokemon->pos.x = 0;
	pokemon->pos.y = 0;
	pokemon->shown = false;
	pokemon->moved = false;
}

void	player_moved_on_enemy(t_entity *player, t_entity *enemy)
{
	if (player->pokemon == 0)
		exit(0); //enemy defeat player, moved against a enemy, how to exit?
	player->pokemon--;
	player->enemies_defeated++;
	enemy->pos.x = 0;
	enemy->pos.y = 0;
	enemy->shown = false;
}

bool	is_next_pos_entity(t_bot *entities, t_entity *entity,
											void (*f)(t_entity *, t_entity *))
{
	int		i;
	t_2int	next_pos;

	i = 0;
	next_pos.x = entity->pos.x + entity->delta.x;
	next_pos.y = entity->pos.y + entity->delta.y;
	while (i < entities->amount)
	{
		if (next_pos.x == entities->array[i].pos.x &&
			next_pos.y == entities->array[i].pos.y)
		{
			(f)(entity, &entities->array[i]);
			return (true);
		}
		i++;
	}
	return (false);
}