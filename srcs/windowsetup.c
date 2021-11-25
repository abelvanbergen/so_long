/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   windowsetup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 13:54:12 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/25 20:11:35 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "so_long.h"

char	**get_map_to_show(t_2int mapsize)
{
	int		i;
	char	**grid;

	grid = (char**)malloc(sizeof(char*) * (mapsize.y + 1));
	if (grid == NULL)
		exit_with_message("malloc failed", 1);
	i = 0;
	while (i < mapsize.y)
	{
		grid[i] = (char*)malloc(sizeof(char) * (mapsize.x + 1));
		if (grid[i] == NULL)
			exit_with_message("malloc failed", 1);
		i++;
	}
	printf("size map_to_show: %d-%d\n", mapsize.x + 1, mapsize.y + 1);
	return (grid);
}

int	*get_tilesizes(int begin_size)
{
	int	*array;
	int	i;

	array = (int*)malloc(sizeof(int) * get_exponent(2, begin_size));
	if (array == NULL)
		exit_with_message("malloc failed", 1);
	i = 0;
	while (begin_size != 1)
	{
		array[i] = begin_size;
		begin_size /= 2;
		i++;
	}
	return (array);
}

void	get_window_size(t_window* window, t_2int mapsize)
{
	t_2int	max_frame_size;
	int		*tilesizes;
	int		i;
	
	max_frame_size.x = 1920;
	max_frame_size.y = 1080;
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
	printf("y: %d\n", window->viewable_mapsize.y);
	while (max_frame_size.x < tilesizes[i] * window->viewable_mapsize.x ||
				max_frame_size.y < tilesizes[i] * window->viewable_mapsize.y)
		i++;
	window->max_texture_size = tilesizes[i];
}

void	get_window(t_window* window, void* mlx, t_2int mapsize)
{
	t_2int	windowsize;
	get_window_size(window, mapsize);
	windowsize.x = window->viewable_mapsize.x * window->max_texture_size;
	windowsize.y = window->viewable_mapsize.y * window->max_texture_size;
	printf("windowsize\nx: %d\ny: %d\n", windowsize.x, windowsize.y);
	window->frame = mlx_new_window(mlx, windowsize.x, windowsize.y, "so_long");
	if (window->frame == NULL)
		exit_with_message("mlx_new_window failed", 1);
	window->frame_rate = 0;
	window->map_to_show = get_map_to_show(window->viewable_mapsize);
}