/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlevel <tlevel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:50:42 by tlevel            #+#    #+#             */
/*   Updated: 2022/01/26 15:30:28 by tlevel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot_init(t_fractal *data)
{	
	data->f->zoom = 1;
	data->f->min_re = -2.0;
	data->f->min_im = -2.0;
	data->f->max_re = 2.0;
	data->f->max_im = data->f->min_im + (data->f->max_re - data->f->min_re)
		* W_HEIGHT / W_WIDTH;
	data->f->iter_max = 50;
	data->color = 0x000000;
	data->main_color = 0xFFFFFF;
	data->hint = 1;
	data->rand = 0;
}

static void	calculation(t_fractal *data)
{	
	t_complex	z;
	t_complex	c;
	double		tmp;

	c.re = data->f->min_re + data->f->x * (data->f->max_re - data->f->min_re)
		/ (W_WIDTH - 1);
	c.im = data->f->min_im + data->f->y * (data->f->max_im - data->f->min_im)
		/ (W_HEIGHT - 1);
	z.re = c.re;
	z.im = c.im;
	data->f->iter = 0;
	while (pow(z.re, 2) + pow(z.im, 2) <= 4
		&& data->f->iter < data->f->iter_max)
	{
		tmp = z.re;
		z.re = pow(z.re, 2) - pow(z.im, 2) + c.re;
		z.im = 2 * z.im * tmp + c.im;
		data->f->iter++;
	}
	if (data->f->iter == data->f->iter_max)
		my_mlx_pixel_put(data, data->f->x, data->f->y, data->main_color);
	else
		my_mlx_pixel_put(data, data->f->x, data->f->y, data->color);
}

void	draw_mandelbrot(t_fractal *data)
{
	data->f->x = 0;
	while (data->f->x < W_WIDTH)
	{
		data->f->y = 0;
		while (data->f->y < W_HEIGHT)
		{
			calculation(data);
			data->f->y++;
		}
		data->f->x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
