/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/18 19:25:54 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/18 20:55:37 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdio.h>

int main(int ac, char **av)
{
	int	i;

	i = 0;
	while (i < ac)
	{
		printf("%s\n", av[i]);
		i++;
	}
}