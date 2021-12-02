/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:06:58 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/02 02:52:30 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

# define WIDTH 200
# define HEIGHT 100

# define RED	"\033[1;31m"
# define YELLOW	"\033[1;33m"
# define END	"\033[0m"

/*
** KEY CODES
*/

# define ESC 53
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2

# define S_UP 24
# define S_DOWN 27

# define FPS	100

# define MAP_ALPHABET "0123456789PEC"

typedef struct s_map
{
	int		width;
	int		height;
	int		arr;
	int		p;
	int		e;
	int		c;
	char	**arr_map;
}				t_map;

typedef struct s_color
{
	int pos;
	int sign;
	int train[4];
}				t_color;

typedef struct s_xpm
{
	char	*wall;
	char	*floor;
	char	*pers;
	char	*ex;
	char	*obj;
}				t_xpm;

typedef struct	s_img 
{
	void	*pers;
	char	*addr;
	int		bits_per_pixel; // кол-во бит на пиксель
	int		line_length;
	int		height;
	int		width;
	int		endian;
	// char	*wall;
	// char	floor;
	t_xpm	xpm;
	void	*i_wall;
	void	*i_floor;
	void	*i_pers;
	void	*i_ex;
	void	*i_obj;
}				t_img;

typedef struct s_pers
{
	int			x; // + вправо
	int			y; // + вниз
	int			pers_x;
	int			pers_y;
	int			speed;
	int			x_ps;
	int			y_ps;
	t_img		texture;
}				t_pers;

/*
** Основная структура
*/

typedef struct s_list
{
	void			*mlx;
	void			*win;
	t_pers			pers;
	t_color			color;
	t_map			map;
	int				x;
	int				y;
}					t_all;

char	*get_next_line(int fd);

void	check_error(unsigned int check_error);
int check_symbol(char *str);
void check_size_map(t_map *map, char const *file);
void load_map(t_all *all, char const *file);
size_t	ft_strlen_s(char *str);

void parser(t_all *all, char const **argv);

void create_obj(t_all *all);
void create_map(t_all *all);

#endif