/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlevel <tlevel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:35:20 by tlevel            #+#    #+#             */
/*   Updated: 2022/01/26 14:54:33 by tlevel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	zoom_io(int x, int y, t_coord *f, double z)
{
	t_complex	m;

	m.re = (double)x / (W_WIDTH / (f->max_re - f->min_re)) + f->min_re;
	m.im = (-1) * (double)y / (W_HEIGHT / (f->max_im - f->min_im)) + f->max_im;
	f->min_re = m.re + (f->min_re - m.re) / z;
	f->min_im = m.im + (f->min_im - m.im) / z;
	f->max_re = m.re + (f->max_re - m.re) / z;
	f->max_im = m.im + (f->max_im - m.im) / z;
	if (z > 0)
		f->iter_max++;
	else
		f->iter_max--;
}

static void	hook_key_color(int key, t_fractal *data)
{
	if (key == KEY_1)
	{
		data->color = RED;
		data->main_color = 0x000000;
	}
	else if (key == KEY_2)
	{
		data->color = GREEN;
		data->main_color = 0x000000;
	}
	else if (key == KEY_3)
	{
		data->color = BLUE;
		data->main_color = 0x000000;
	}
	else if (key == KEY_SHIFT)
	{
		data->color = KEY_SHIFT;
		data->rand++;
		if (data->rand > 128)
			data->rand = 1;
		data->main_color = 0x000000;
	}
}

static void	hook_key_arrows(int key, t_fractal *data)
{
	t_complex	d;

	d.re = data->f->max_re - data->f->min_re;
	d.im = data->f->max_im - data->f->min_im;
	if (key == KEY_NUM_UP)
	{
		data->f->min_im -= d.im * 0.1;
		data->f->max_im -= d.im * 0.1;
	}
	else if (key == KEY_NUM_DOWN)
	{
		data->f->min_im += d.im * 0.1;
		data->f->max_im += d.im * 0.1;
	}
	else if (key == KEY_NUM_RIGHT)
	{
		data->f->min_re += d.re * 0.1;
		data->f->max_re += d.re * 0.1;
	}
	else if (key == KEY_NUM_LEFT)
	{
		data->f->min_re -= d.re * 0.1;
		data->f->max_re -= d.re * 0.1;
	}
}

int	hook_key(int key, t_fractal *data)
{	
	if (key == KEY_ESC)
		exit (0);
	else if (key == KEY_NUM_PLUS || key == KEY_PLUS)
		zoom_io(W_WIDTH / 2, W_HEIGHT / 2, data->f, 1.5);
	else if (key == KEY_NUM_MINUS || key == KEY_MINUS)
		zoom_io(W_WIDTH / 2, W_HEIGHT / 2, data->f, 1 / 1.5);
	else if (key == KEY_R)
		start_fractal(data);
	else if (key == KEY_H)
		data->hint *= -1;
	else if (key == KEY_SPACE && data->name == 2)
		data->julia_press *= -1;
	hook_key_arrows(key, data);
	hook_key_color(key, data);
	draw_fractal(data);
	return (0);
}

int	hook_mouse(int key, int x, int y, t_fractal *data)
{
	if (key == MOUSE_ROLL_DOWN)
		zoom_io(x, y, data->f, 1 / 1.5);
	else if (key == MOUSE_ROLL_UP)
		zoom_io(x, y, data->f, 1.5);
	else
		return (0);
	draw_fractal(data);
	return (0);
}
