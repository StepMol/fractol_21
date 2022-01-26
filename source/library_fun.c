/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlevel <tlevel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:47:38 by tlevel            #+#    #+#             */
/*   Updated: 2022/01/26 13:07:00 by tlevel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{	
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0' && i < n - 1 && s1[i] == s2[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

void	ft_putstr_fd(char *s, int fd)
{	
	int	len;

	if (s)
	{
		len = 0;
		while (s[len] != '\0')
			len++;
		write(fd, s, len);
	}
}

double	ft_abs(double a)
{
	if (a >= 0)
		return (a);
	else
		return ((-1) * a);
}
