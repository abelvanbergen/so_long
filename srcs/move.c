/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 20:25:29 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/21 22:10:06 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

move_player(t_gamedata *gamedata, int dx, int dy)
{
	char	d_loc;
	char	loc;
	
	d_loc = gamedata->map[gamedata->p_pos.y + dy][gamedata->p_pos.x + dx];
	loc = gamedata->map[gamedata->p_pos.y][gamedata->p_pos.x];
	if (d_loc == WALL_CHAR)
		return ;
	if (d_loc == EXIT_CHAR && gamedata->amount_collectible == 0)
		exit(0); // mlx opruimen? en aparte geslaagde exit
	else if (d_loc == PLAYER_CHAR)
		gamedata->amount_collectible--;
	else if (ft_strchr(ENEMY_CHARS, d_loc) != NULL)
		exit(1); //mlx opruimen? en aparte enemy failed exit
	gamedata->map[gamedata->p_pos.y + dy][gamedata->p_pos.x] = PLAYER_CHAR;
	gamedata->map[gamedata->p_pos.y][gamedata->p_pos.x] = gamedata->p_pos_char;
	gamedata->p_pos_char = d_loc;
	gamedata->p_pos.x += dx;
	gamedata->p_pos.y += dy;
}

move_enemey(char **map, int x, int y)
{
	t_2int	delta;

	delta = 
}

void	move(t_gamedata* gamedata, int dx, int dy)
{
	t_2int	pos;

	pos.y = 0;
	while (gamedata->map[pos.y] != NULL)
	{
		pos.x = 0;
		while (gamedata->map[pos.y][pos.x] != '\0')
		{
			if (gamedata->map[pos.y][pos.x] == 'P')
				move_player(t_gamedata* )
			pos.x++;
		}
		pos.y++;
	}
}