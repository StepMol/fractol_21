/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlevel <tlevel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:55:29 by tlevel            #+#    #+#             */
/*   Updated: 2022/01/26 15:21:27 by tlevel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	draw_fractal(t_fractal *data)
{
	if (data->name == 1)
		draw_mandelbrot(data);
	else if (data->name == 2)
		draw_julia(data);
	else if (data->name == 3)
		draw_bonus(data);
	if (data->hint == -1)
		print_hint(data);
	mlx_string_put(data->mlx, data->win, W_WIDTH - 200, W_HEIGHT - 50,
		0xCCCCCC, "Use -H for help");
}

void	start_fractal(t_fractal *data)
{	
	if (data->name == 1)
		mandelbrot_init(data);
	else if (data->name == 2)
		julia_init(data);
	else if (data->name == 3)
		bonus_init(data);
	draw_fractal(data);
}

static int	ft_arg_validation(char **av, t_fractal *data)
{	
	if (ft_strncmp("Mandelbrot", av[1], 10) == 0 && ft_strlen(av[1]) == 10)
		data->name = 1;
	else if (ft_strncmp("Julia", av[1], 5) == 0 && ft_strlen(av[1]) == 5)
		data->name = 2;
	else if (ft_strncmp("Bonus", av[1], 5) == 0
		&& ft_strlen(av[1]) == 5)
		data->name = 3;
	else
	{	
		ft_putstr_fd(ERR_WRONG_NAME, 1);
		ft_errors(WAR_HELP);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_fractal	data;
	t_coord		f;

	data.f = &f;
	if (ac != 2)
		ft_errors(WAR_HELP);
	else if (ft_arg_validation(av, &data))
	{
		data.mlx = mlx_init();
		data.win = mlx_new_window(data.mlx, W_WIDTH, W_HEIGHT, "Fractol");
		data.img = mlx_new_image(data.mlx, W_WIDTH, W_HEIGHT);
		data.addr = mlx_get_data_addr(data.img, &data.bpp,
				&data.line_len, &data.endian);
		start_fractal(&data);
		mlx_key_hook(data.win, hook_key, &data);
		mlx_mouse_hook(data.win, hook_mouse, &data);
		mlx_hook(data.win, 17, 0, ft_close, &data);
		if (data.name == 2)
			mlx_hook(data.win, 6, 0, julia_moving, &data);
		mlx_loop(data.mlx);
	}
	return (0);
}
