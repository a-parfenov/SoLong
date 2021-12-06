/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 18:06:58 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/06 22:38:55 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../gnl/get_next_line.h"
# include <time.h>

/*
 *	Images:
 */
// # define PERS_R		"images/personage_right.xpm"
// # define PERS_L		"images/personage_left.xpm"
# define EXIT			"sprites/exit.xpm"
# define FON			"sprites/fon.xpm"
# define WALL			"sprites/wall.xpm"
# define ENEM_R			"sprites/enemy_right.xpm"
# define ENEM_L			"sprites/enemy_left.xpm"
// # define END_GAME_1		"sprites/wasted.xpm"
# define END_GAME_1		"sprites/game_over.xpm"
# define END_GAME_2		"sprites/game_over.xpm"

// # define PERS_U		"sprites/ness_b.xpm"
// # define PERS_D		"sprites/ness_2.xpm"
# define PERS_R			"sprites/xpm_money/1_r.xpm"
# define PERS_L			"sprites/xpm_money/1_l.xpm"
// # define EXIT_0		"sprites/exit.xpm"
// # define EXIT		"sprites/exit_o.xpm"
// # define FON			"sprites/el.xpm"
// # define WALL		"sprites/1.xpm"
// # define ENEM_R		"sprites/gl_r.xpm"
// # define ENEM_L		"sprites/gl_l.xpm"
# define OBJ1			"sprites/xpm_money/image-1.xpm"
# define OBJ2			"sprites/xpm_money/image-3.xpm"
# define OBJ3			"sprites/xpm_money/image-5.xpm"
# define OBJ4			"sprites/xpm_money/image-7.xpm"
# define OBJ5			"sprites/xpm_money/image-9.xpm"
# define OBJ6			"sprites/xpm_money/image-11.xpm"
# define OBJ7			"sprites/xpm_money/image-13.xpm"
# define OBJ8			"sprites/xpm_money/image-15.xpm"
# define OBJ9			"sprites/xpm_money/w.xpm"

# define RED			"\033[1;31m"
# define YELLOW			"\033[1;33m"
# define WHITE			"\033[1;37m"
# define END			"\033[0m"

/*
 *	Errors:
 */
# define ERROR_0	"\033[1;33mERROR_0: Запуск: './so_long maps/map.ber'\033[0m"
# define ERROR_1	"\033[1;33mERROR_1: Карта должна быть формата '.ber'\033[0m"
# define ERROR_2	"\033[1;33mERROR_2: Текстура не найдена\033[0m"
# define ERROR_3	"\033[1;33mERROR_3: fd map\033[0m"
# define ERROR_4	"\033[1;33mERROR_4: malloc\033[0m"
# define ERROR_5	"\033[1;33mERROR_5: malloc in get_next_line\033[0m"
# define ERROR_6	"\033[1;33mERROR_6: open map\033[0m"
# define ERROR_7	"\033[1;33mERROR_7: malloc in get_next_line\033[0m"
# define ERROR_8	"\033[1;33mERROR_8: Недопустимые символы в карте\033[0m"
# define ERROR_9	"\033[1;33mERROR_9: Расхождение в ширине карты\033[0m"
# define ERROR_10	"\033[1;33mERROR_10: Invalid card\033[0m"
# define ERROR_11	"\033[1;33mERROR_11: Поправьте границы карты\033[0m"
# define ERROR_12	"\033[1;33mERROR_12: Itoa\033[0m"

# define MAP_ALPHA	"01234PEC"

# define ENEM_3		'3'
# define ENEM_4		'4'

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
	void	*i_pers_l;
	void	*i_exit;
	void	*i_enem_r;
	void	*i_enem_l;

	void	*i_obj;
	void	*i_obj2;
	void	*i_obj3;
	void	*i_obj4;

	int		height_img;
	int		width_img;
	char	go_l_r;
}			t_img;

/*
 * Basic struct
 */
typedef struct s_all
{
	void	*i_obj5;
	void	*i_obj6;
	void	*i_obj7;
	void	*i_obj8;
	void	*i_end;
	void	*w;
	int		count_m;

	int		flag;
	char	*line;
	int		pers_w_x;
	int		pers_w_y;
	int		enem_x;
	int		enem_y;
	void	*mlx;
	void	*win;
	int		i;
	int		j;
	int		k;
	int		prt_x;
	int		prt_y;
	int		count_steps;
	int		count_anim;
	t_map	map;
	t_img	img;
}			t_all;

void	check_map(t_all *all, char *file);
void	saving_the_map(t_all *all, char *file);

int		render_next_frame(t_all *all);
char	*ft_itoa(int n);

void	create_obj(t_all *all);
int		key_ivent(int key, t_all *all);

void	print_map_arr(t_all *all);
void	replacement(t_all *all, int flag);

void	check_error(unsigned int check_error, char *error_number, t_map *map);
size_t	ft_strlen_s(char *str);
int		end_game(t_all *all, int flag);
void	x_y_pers(t_all *all);
int		check_argv(char **argv);
void	check_error_argv(unsigned int check_error, char *error_number);

void	create_map(t_all *all);
void	anim_enem(t_all *all);
void	anim_enem_time(t_all *all);
void	anim_pers(t_all *all);
void	print_step_num(t_all	*all);

#endif