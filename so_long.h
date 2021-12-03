/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:06:58 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/03 05:00:12 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

# define PERS_R		"images/personage_right.xpm"
# define EXIT		"images/exit.xpm"
# define FON		"images/fon.xpm"
# define WALL		"images/wall.xpm"
# define OBJ		"images/obj.xpm"

// # define WIDTH 200
// # define HEIGHT 100

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

# define SIZE_X 64
# define SIZE_Y 64
// # define S_UP 24
// # define S_DOWN 27

// # define FPS	100

# define MAP_ALPHABET "0123456789PEC"

typedef struct s_map
{
	int		x;
	int		y;
	int		pers_x;
	int		pers_y;
	int		width_map;
	int		height_map;
	char	**arr_map;
	int		p;
	int		e;
	int		c;
	int		c_count;
}			t_map;

typedef struct s_img 
{
	void	*i_wall;
	void	*i_fon;
	void	*i_pers_r;
	void	*i_exit;
	void	*i_obj;

	int		height_img;
	int		width_img;
}			t_img ;

/*
** Основная структура
*/

typedef struct s_all
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_img	img;
}			t_all;

char	*get_next_line(int fd);

void check_map(t_map *map, char const *file);
void saving_the_map(t_map *map, char const *file);

void	check_error(unsigned int check_error);
size_t	ft_strlen_s(char *str);
int end_game(void);
char	*ft_calloc(size_t count, size_t size);

void	create_obj(t_all *all);
void create_map(t_all *all);

int key_ivent(int key, t_all *all);

#endif