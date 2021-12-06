/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:43:46 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/06 20:10:04 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

/*
 *	Images:
 */
# define PERS_R		"sprites/personage_right.xpm"
# define EXIT		"sprites/exit.xpm"
# define FON		"sprites/fon.xpm"
# define WALL		"sprites/wall.xpm"
# define OBJ		"sprites/obj.xpm"

# define RED		"\033[1;31m"
# define YELLOW		"\033[1;33m"
# define WHITE		"\033[1;37m"
# define END		"\033[0m"

/*
 *	Errors:
 */
# define ERROR_0	"\033[1;33mERROR_0: Запуск: './so_long maps/map.ber'\033[0m"
# define ERROR_1	"\033[1;33mERROR_1: Карта должна быть формата '.ber'\033[0m"
# define ERROR_2	"\033[1;33mERROR_2: Текстура не создана\033[0m"
# define ERROR_3	"\033[1;33mERROR_3: fd map\033[0m"
# define ERROR_4	"\033[1;33mERROR_4: malloc\033[0m"
# define ERROR_5	"\033[1;33mERROR_5: malloc in get_next_line\033[0m"
# define ERROR_6	"\033[1;33mERROR_6: open map\033[0m"
# define ERROR_7	"\033[1;33mERROR_7: malloc in get_next_line\033[0m"
# define ERROR_8	"\033[1;33mERROR_8: Недопустимые символы в карте\033[0m"
# define ERROR_9	"\033[1;33mERROR_9: Расхождение в ширине карты\033[0m"
# define ERROR_10	"\033[1;33mERROR_10: Несоответствующая карта\033[0m"
# define ERROR_11	"\033[1;33mERROR_11: Поправьте границы карты\033[0m"

# define MAP_ALPHA	"01PEC"

/*
 *	Key:
 */
# define ESC 53
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2

# define SIZE_X 64
# define SIZE_Y 64

typedef struct s_map
{
	char	**arr_map;
	int		x;
	int		y;
	int		pers_x;
	int		pers_y;
	int		width_map;
	int		height_map;
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
}			t_img;

/*
 * Basic struct
 */
typedef struct s_all
{
	void	*mlx;
	void	*win;
	int		i;
	int		j;
	int		count_steps;
	t_map	map;
	t_img	img;
}			t_all;

char	*get_next_line(int fd);

void	check_map(t_map *map, char *file);
void	saving_the_map(t_map *map, char *file);

void	create_obj(t_all *all);
void	create_map(t_all *all);
int		key_ivent(int key, t_all *all);

void	check_error(unsigned int check_error, char *error_number, t_map *map);
size_t	ft_strlen_s(char *str);
int		end_game(t_all *all);
void	x_y_pers(t_map *map);
int		check_args(char **argv);
void	check_error_argv(unsigned int check_error, char *error_number);

#endif