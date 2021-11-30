/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 19:25:54 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/30 16:32:57 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "so_long.h"

static int	process_movement(t_gamedata *gamedata)
{
	if (gamedata->move.up == true || gamedata->move.down == true
		|| gamedata->move.left == true || gamedata->move.right == true)
	{
		ft_bzero(&gamedata->player.delta, sizeof(t_2int));
		if (gamedata->move.up == true)
			gamedata->player.delta.y = -1;
		else if (gamedata->move.down == true)
			gamedata->player.delta.y = 1;
		else if (gamedata->move.left == true)
			gamedata->player.delta.x = -1;
		else if (gamedata->move.right == true)
			gamedata->player.delta.x = 1;
		ft_bzero(&gamedata->move, sizeof(t_move));
		move_player(&gamedata->player, &gamedata->enemy,
			&gamedata->pokemany, &gamedata->mapinfo);
		gamedata->move_counter++;
	}
	gamedata->window.frame_rate++;
	if (gamedata->window.frame_rate % MOVEMENT_SPEED_ENEMY == 0)
		move_enemies(gamedata->mapinfo.map,
			&gamedata->enemy, &gamedata->player);
	if (gamedata->window.frame_rate % MOVEMENT_SPEED_POKEMON == 0)
		move_pokemany(gamedata, &gamedata->pokemany);
	make_frame(gamedata);
	return (0);
}

static void	get_game_data(t_gamedata *gamedata, char *filename)
{
	parse_map(filename, gamedata);
	gamedata->mlx = mlx_init();
	if (gamedata->mlx == NULL)
		exit_with_message("mlx_init failed", 1);
	get_textures(&gamedata->textures, gamedata->mlx);
	get_window(&gamedata->window, gamedata->mlx, gamedata->mapinfo.size);
	get_image(&gamedata->img, gamedata->mlx,
		gamedata->window.viewable_mapsize, gamedata->window.max_texture_size);
	ft_bzero(&gamedata->move, sizeof(t_move));
}

int	main(int ac, char **av)
{
	t_gamedata	gamedata;

	if (ac != 2)
		exit_with_message(
			"Not the right amount of arguments\nUse [./solong file_name]", 1);
	srand((unsigned) time(0));
	get_game_data(&gamedata, av[1]);
	make_frame(&gamedata);
	mlx_hook(gamedata.window.frame, 2, 1L << 0, key_press, &gamedata.move);
	mlx_loop_hook(gamedata.mlx, process_movement, &gamedata);
	mlx_loop(gamedata.mlx);
}
