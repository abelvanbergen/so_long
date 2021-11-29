/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abelfranciscusvanbergen <abelfranciscus      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/21 10:09:49 by abelfrancis   #+#    #+#                 */
/*   Updated: 2021/11/29 11:14:06 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "so_long.h"

int	str_is_only_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

int		get_exponent(int base, int power)
{
	int	exponent;
	int	nb;

	exponent = 1;
	nb = base;
	while (nb != power)
	{
		nb *= base;
		exponent++;
	}
	return (exponent);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	my_mlx_pixel_put(t_imginfo *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	*malloc_check(void *content)
{
	if (content == 0)
		exit_with_message("Malloc failed", 1);
	return (content);
}

char	*ft_strjoin_and_free(char *str1, char *str2)
{
	int		len_str1;
	int		len_str2;
	char	*new;

	len_str1 = ft_strlen(str1);
	len_str2 = ft_strlen(str2);
	new = (char*)malloc(sizeof(char) * (len_str1 + len_str2 + 1));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, str1, len_str1 + 1);
	ft_strlcpy(new + len_str1, str2, len_str2 + 1);
	new[len_str1 + len_str2] = '\0';
	free(str1);
	return (new);
}