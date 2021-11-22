/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 08:43:53 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/21 10:29:51 by abelfrancis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	exit_with_message(char *message, int exitcode)
{
	printf("Error\n%s\n", message);
	exit(exitcode);
}