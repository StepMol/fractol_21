/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlevel <tlevel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:44:28 by tlevel            #+#    #+#             */
/*   Updated: 2022/01/26 15:30:44 by tlevel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_errors(char *s)
{
	ft_putstr_fd(s, 1);
	exit(2);
}

int	ft_close(void *a)
{
	(void)a;
	exit (0);
}

static int	get_color(t_fractal *data)
{
	double	t;
	int		col[4];

	t = (double)data->f->iter / (double)data->f->iter_max;
	col[0] = (int)(pow((1 - t), 2) * BLUE);
	col[1] = (int)(pow((0.99 - t), 3.5) * BLUE);
	col[2] = (int)(pow((0.9 - t), 0.6) * (GREEN));
	col[3] = (int)(pow((1 - t), 2) * t * data->color);
	if (data->color == RED)
		return (RED | col[0] | BLACK);
	else if (data->color == GREEN)
		return (GREEN | col[1] | BLACK);
	else if (data->color == BLUE)
		return (BLUE | col[2] | BLACK);
	else if (data->color == KEY_SHIFT)
	{
		return (col[data->rand % 3] << ((128 - data->rand) % 24)
			| col[(data->rand % 3)] >> (data->rand % 16)
			| col[(data->rand % 3)] >> (data->rand % 8)
			| (1 + BLACK) << (data->rand % 24));
	}
	return (WHITE);
}

void	my_mlx_pixel_put(t_fractal *data, int x, int y, int color)
{	
	if (data->f->iter == data->f->iter_max)
		*(int *)(data->addr + (y * data->line_len + x * (data->bpp / 8)))
			= color;
	else if (data->color == BLACK)
		*(int *)(data->addr + (y * data->line_len + x * (data->bpp / 8)))
			= BLACK;
	else
		*(int *)(data->addr + (y * data->line_len + x * (data->bpp / 8)))
			= get_color(data);
}

void	print_hint(t_fractal *data)
{	
	mlx_string_put(data->mlx, data->win, 50,
		W_HEIGHT - 160, 0xCCCCCC, "Help:");
	mlx_string_put(data->mlx, data->win, 50,
		W_HEIGHT - 130, 0xCCCCCC, "\"+/-\" and mouse roll - zoom");
	mlx_string_put(data->mlx, data->win, 50,
		W_HEIGHT - 100, 0xCCCCCC, "Arrows - move image");
	mlx_string_put(data->mlx, data->win, 50,
		W_HEIGHT - 70, 0xCCCCCC, "Shift - acid trip");
	mlx_string_put(data->mlx, data->win, 50,
		W_HEIGHT - 40, 0xCCCCCC, "Keyboard 1,2,3 - red/green/blue chanels");
}
