/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   windowsetup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 13:54:12 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/30 16:41:41 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "so_long.h"

char	**get_map_to_show(t_2int mapsize)
{
	int		i;
	char	**grid;

	grid = malloc_check((char **)malloc(sizeof(char *) * (mapsize.y + 1)));
	i = 0;
	while (i < mapsize.y)
	{
		grid[i] = malloc_check((char *)malloc(sizeof(char) * (mapsize.x + 1)));
		i++;
	}
	return (grid);
}

int	*get_tilesizes(int begin_size)
{
	int	*array;
	int	i;

	array = malloc_check(malloc(sizeof(int) * get_exponent(2, begin_size)));
	i = 0;
	while (begin_size != 1)
	{
		array[i] = begin_size;
		begin_size /= 2;
		i++;
	}
	return (array);
}

static void	get_window_size(t_window *window, t_2int mapsize)
{
	t_2int	max_frame_size;
	int		*tilesizes;
	int		i;

	max_frame_size.x = WINDOW_WITDH;
	max_frame_size.y = WINDOW_HEIGHT;
	if (mapsize.x < VIEWABLE_WITDH)
		window->viewable_mapsize.x = mapsize.x;
	else
		window->viewable_mapsize.x = VIEWABLE_WITDH;
	if (mapsize.y < VIEWABLE_HEIGHT)
		window->viewable_mapsize.y = mapsize.y;
	else
		window->viewable_mapsize.y = VIEWABLE_HEIGHT;
	tilesizes = get_tilesizes(VIEWABLE_TEXTURE_SIZE);
	i = 0;
	while (max_frame_size.x < tilesizes[i] * window->viewable_mapsize.x
		|| max_frame_size.y < tilesizes[i] * window->viewable_mapsize.y)
		i++;
	window->max_texture_size = tilesizes[i];
	free(tilesizes);
}

void	get_window(t_window *window, void *mlx, t_2int mapsize)
{
	t_2int	windowsize;

	get_window_size(window, mapsize);
	windowsize.x = window->viewable_mapsize.x * window->max_texture_size;
	windowsize.y = window->viewable_mapsize.y * window->max_texture_size;
	window->frame = mlx_new_window(mlx, windowsize.x, windowsize.y, "so_long");
	if (window->frame == NULL)
		exit_with_message("mlx_new_window failed", 1);
	window->frame_rate = 0;
	window->map_to_show = get_map_to_show(window->viewable_mapsize);
}
