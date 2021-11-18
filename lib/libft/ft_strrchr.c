/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: avan-ber <avan-ber@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 14:38:55 by avan-ber      #+#    #+#                 */
/*   Updated: 2021/10/26 11:51:00 by avan-ber      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	i_pos;

	i = 0;
	i_pos = -1;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i_pos = i;
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	else if (i_pos == -1)
		return (0);
	else
		return ((char *)&s[i_pos]);
}
