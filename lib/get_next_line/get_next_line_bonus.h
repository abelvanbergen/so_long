/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 18:25:34 by avan-ber       #+#    #+#                */
/*   Updated: 2019/12/27 13:44:44 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

int		get_next_line(int fd, char **line);
char	*ft_strdup_c(const char *s1, char c);
int		ft_strlen_c(char *str, char c);

#endif
