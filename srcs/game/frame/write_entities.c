/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   write_entities.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 15:51:51 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 17:20:50 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	write_entity(t_gamedata *gamedata, t_entity *entity, t_2int *start,
															t_imginfo *texture)
{
	t_2int	pos;
	t_2int	loc;

	pos.x = entity->pos.x - start->x;
	pos.y = entity->pos.y - start->y;
	loc.x = pos.x * gamedata->window.max_texture_size;
	loc.y = pos.y * gamedata->window.max_texture_size;
	write_texture_img(&gamedata->img, texture, loc,
		gamedata->window.max_texture_size);
}

static void	jumptable_entity_textures(t_gamedata *gamedata, t_entity *entity,
			t_2int *start, t_imginfo **entity_texture)
{
	if (entity->pos.x < start->x
		|| entity->pos.x >= start->x + gamedata->window.viewable_mapsize.x)
		return ;
	if (entity->pos.y < start->y
		|| entity->pos.y >= start->y + gamedata->window.viewable_mapsize.y)
		return ;
	if (entity->moved == true)
	{
		if (entity->delta.x == 1)
			write_entity(gamedata, entity, start,
				&entity_texture[entity->texture_id][text_right]);
		else if (entity->delta.x == -1)
			write_entity(gamedata, entity, start,
				&entity_texture[entity->texture_id][text_left]);
		else if (entity->delta.y == 1)
			write_entity(gamedata, entity, start,
				&entity_texture[entity->texture_id][text_down]);
		else
			write_entity(gamedata, entity, start,
				&entity_texture[entity->texture_id][text_up]);
	}
	else
		write_entity(gamedata, entity, start,
			&entity_texture[entity->texture_id][text_current]);
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

void	write_pikachu(t_gamedata *gamedata, t_2int loc, int max_texture_size)
{
	int	texture_id;

	texture_id = (gamedata->window.frame_rate / 5) % DIFFERENT_PIKACHU;
	loc.x += max_texture_size / 4;
	loc.y += max_texture_size / 2;
	write_texture_img(&gamedata->img,
		&gamedata->textures.pikachu[texture_id], loc, max_texture_size / 2);
}
