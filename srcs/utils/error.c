/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 08:43:53 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/12/02 10:59:02 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	exit_with_message(char *message, int exitcode)
{
	printf("Error\n%s\n", message);
	exit(exitcode);
}

void	exit_with_2_messages(char *message1, char *message2, int exitcode)
{
	printf("Error\n%s%s\n", message1, message2);
	exit(exitcode);
}
