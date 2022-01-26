/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlevel <tlevel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:55:32 by tlevel            #+#    #+#             */
/*   Updated: 2022/01/26 15:17:46 by tlevel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>

/**
** Macros
**/
# define W_WIDTH	1000
# define W_HEIGHT	1000

# define RED		0xFF0000
# define GREEN		0x00FF00
# define BLUE		0x0000FF
# define BLACK		0x000000
# define WHITE		0xFFFFFF
/**
** Warnings and Errors
**/
# ifndef ATTENTION_H
#  define ATTENTION_H

#  define WAR_HELP "\033[33mTo start use ./fractol and one from following\
 parameters:\n- Mandelbrot\n- Julia\n- Bonus\n\033[37m"
#  define ERR_WRONG_NAME "\033[91mInvalid arguments!\n\033[37m"

# endif

/**
** Keys
**/
# ifndef KEYS_H
#  define KEYS_H

#  define KEY_ESC     		53
#  define KEY_ENTER     	36
#  define KEY_SPACE     	49
#  define KEY_C				8
#  define KEY_R				15
#  define KEY_H				4
#  define KEY_1				18
#  define KEY_2				19
#  define KEY_3				20
#  define KEY_4				21
#  define KEY_PLUS			24
#  define KEY_MINUS			27
#  define KEY_SHIFT			257
#  define KEY_NUM_UP		126
#  define KEY_NUM_DOWN		125
#  define KEY_NUM_RIGHT		124
#  define KEY_NUM_LEFT		123
#  define KEY_NUM_PLUS		69
#  define KEY_NUM_MINUS		78
#  define KEY_NUM_ENTER     76

#  define MOUSE_ROLL_UP    	5
#  define MOUSE_ROLL_DOWN  	4
#  define MOUSE_KEY_LEFT  	1
#  define MOUSE_KEY_RIGHT 	2
#  define MOUSE_KEY_WHEEL	3

# endif

/**
** Structures
**/
typedef struct s_coord
{	
	double		x;
	double		y;
	double		min_re;
	double		min_im;
	double		max_re;
	double		max_im;
	int			iter;
	int			iter_max;
	double		zoom;
	double		j_re;
	double		j_im;
}			t_coord;

typedef struct s_fractal
{
	void	*win;
	void	*img;
	void	*mlx;
	char	*addr;
	int		line_len;
	int		bpp;
	int		endian;
	int		name;
	int		color;
	int		main_color;
	int		hint;
	int		julia_press;
	int		rand;
	t_coord	*f;
}				t_fractal;

typedef struct s_complex
{
	double	re;
	double	im;
}			t_complex;

/**
** library
**/
void	ft_errors(char *s);
int		ft_close(void *a);
void	my_mlx_pixel_put(t_fractal *data, int x, int y, int color);
void	print_hint(t_fractal *data);

void	start_fractal(t_fractal *data);
void	draw_fractal(t_fractal *data);

void	draw_mandelbrot(t_fractal *data);
void	mandelbrot_init(t_fractal *data);

void	draw_julia(t_fractal *data);
void	julia_init(t_fractal *data);
int		julia_moving(int x, int y, t_fractal *data);

void	draw_bonus(t_fractal *data);
void	bonus_init(t_fractal *data);

int		hook_key(int key, t_fractal *data);
int		hook_mouse(int key, int x, int y, t_fractal *data);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
double	ft_abs(double a);

#endif
