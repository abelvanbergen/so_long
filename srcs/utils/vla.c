/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vla.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 09:04:58 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/30 17:09:27 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //
#include "so_long.h"
#include <stdlib.h>

static void	resize_vla(t_vla *vla, size_t capacity)
{
	char	**new;
	int		i;

	vla->capacity = capacity;
	new = (char **)malloc(sizeof(char *) * (vla->capacity + 1));
	if (new == NULL)
		exit_with_message("malloc failed", 1);
	ft_bzero(new, sizeof(char *) * (vla->capacity + 1));
	i = 0;
	while (i < vla->size)
	{
		new[i] = vla->array[i];
		i++;
	}
	free(vla->array);
	vla->array = new;
}

void	vla_shrink(t_vla *vla)
{
	resize_vla(vla, vla->size);
}

void	vla_add_line_to_array(t_vla *vla, char *line)
{
	if (vla->size == vla->capacity)
		resize_vla(vla, vla->capacity * 2);
	vla->array[vla->size] = line;
	vla->size++;
	return ;
}

void	vla_init(t_vla *vla)
{
	vla->size = 0;
	vla->capacity = 8;
	vla->array = (char **)malloc(sizeof(char *) * (vla->capacity + 1));
	if (vla->array == NULL)
		exit_with_message("malloc failed", 1);
	ft_bzero(vla->array, sizeof(char *) * vla->capacity + 1);
	return ;
}
