/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 14:49:52 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/11/30 15:13:44 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_face_to_face(t_entity *a, t_entity *b)
{
	return (a->delta.x + b->delta.x + 2 * a->delta.y + 2 * b->delta.y == 0);
}

void	turn(t_2int *delta, t_tile_sides direction)
{
	int	temp;

	if (direction == back)
	{
		delta->x *= -1;
		delta->y *= -1;
	}
	else if (direction == right)
	{
		temp = delta->x;
		delta->x = delta->y * -1;
		delta->y = temp;
	}
	else if (direction == left)
	{
		temp = delta->x;
		delta->x = delta->y;
		delta->y = temp * -1;
	}
}

char	get_tile(int x, int y, char **map)
{
	return (map[y][x]);
}

char	*set_sides(char *tiles, t_entity *entity, char **map)
{
	t_2int	e_pos;
	t_2int	e_delta;

	e_pos = entity->pos;
	e_delta = entity->delta;
	tiles[current] = get_tile(e_pos.x, e_pos.y, map);
	tiles[front] = get_tile(e_pos.x + e_delta.x, e_pos.y + e_delta.y, map);
	tiles[back] = get_tile(e_pos.x - e_delta.x, e_pos.y - e_delta.y, map);
	turn(&e_delta, right);
	tiles[right] = get_tile(e_pos.x + e_delta.x, e_pos.y + e_delta.y, map);
	tiles[left] = get_tile(e_pos.x - e_delta.x, e_pos.y - e_delta.y, map);
	return (tiles);
}
