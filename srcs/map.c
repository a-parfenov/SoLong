/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:32:08 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/06 19:28:57 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_obj(t_all *all)
{
	all->img.i_pers_r = mlx_xpm_file_to_image(all->mlx,
			PERS_R, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_pers_r), ERROR_2, &all->map);
	all->img.i_exit = mlx_xpm_file_to_image(all->mlx,
			EXIT, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_exit), ERROR_2, &all->map);
	all->img.i_fon = mlx_xpm_file_to_image(all->mlx,
			FON, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_fon), ERROR_2, &all->map);
	all->img.i_wall = mlx_xpm_file_to_image(all->mlx,
			WALL, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_wall), ERROR_2, &all->map);
	all->img.i_obj = mlx_xpm_file_to_image(all->mlx,
			OBJ, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_obj), ERROR_2, &all->map);
}

void	replacement(t_all *all, int flag)
{
	all->map.arr_map[all->map.pers_y][all->map.pers_x] = '0';
	mlx_put_image_to_window(all->mlx, all->win,
		all->img.i_wall, all->map.pers_x * SIZE_X, all->map.pers_y * SIZE_Y);
	if (flag == 1)
		all->map.pers_y -= 1;
	else if (flag == 2)
		all->map.pers_y += 1;
	else if (flag == 3)
		all->map.pers_x -= 1;
	else if (flag == 4)
		all->map.pers_x += 1;
	all->map.arr_map[all->map.pers_y][all->map.pers_x] = 'P';
	mlx_put_image_to_window(all->mlx, all->win,
		all->img.i_pers_r, all->map.pers_x * SIZE_X, all->map.pers_y * SIZE_Y);
	all->count_steps++;
	printf("Steps: %d\n", all->count_steps);
}

void	check_step_1(t_all *all, int y, int flag)
{
	if (all->map.arr_map[all->map.pers_y - y][all->map.pers_x] == 'C')
	{
		all->map.c_count++;
		replacement(all, flag);
	}
	else if (all->map.arr_map[all->map.pers_y - y][all->map.pers_x] == 'E')
	{
		if (all->map.c_count == all->map.c)
		{
			replacement(all, flag);
			end_game(all);
		}
		else
			return ;
	}
	else
		replacement(all, flag);
}

void	check_step_2(t_all *all, int x, int flag)
{
	if (all->map.arr_map[all->map.pers_y][all->map.pers_x - x] == 'C')
	{
		all->map.c_count++;
		replacement(all, flag);
	}
	else if (all->map.arr_map[all->map.pers_y][all->map.pers_x - x] == 'E')
	{
		if (all->map.c_count == all->map.c)
		{
			replacement(all, flag);
			end_game(all);
		}
		else
			return ;
	}
	else
		replacement(all, flag);
}

int	key_ivent(int key, t_all *all)
{
	if (key == UP
		&& all->map.arr_map[all->map.pers_y - 1][all->map.pers_x] != '1')
		check_step_1(all, 1, 1);
	else if (key == DOWN
		&& all->map.arr_map[all->map.pers_y + 1][all->map.pers_x] != '1')
		check_step_1(all, -1, 2);
	else if (key == LEFT
		&& all->map.arr_map[all->map.pers_y][all->map.pers_x - 1] != '1')
		check_step_2(all, 1, 3);
	else if (key == RIGHT
		&& all->map.arr_map[all->map.pers_y][all->map.pers_x + 1] != '1')
		check_step_2(all, -1, 4);
	else if (key == ESC)
		end_game(all);
	return (0);
}
