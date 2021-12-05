/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:32:08 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/05 22:08:52 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
	all->img.i_pers_l = mlx_xpm_file_to_image(all->mlx,
			PERS_L, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_pers_l), ERROR_2, &all->map);
	all->img.i_enem_r = mlx_xpm_file_to_image(all->mlx,
			ENEM_R, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_enem_r), ERROR_2, &all->map);
	all->img.i_enem_l = mlx_xpm_file_to_image(all->mlx,
			ENEM_L, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_enem_l), ERROR_2, &all->map);
}

void	replacement(t_all *all, int flag)
{
	all->map.arr_map[all->map.pers_y][all->map.pers_x] = '0';
	if (flag == 1)
		all->map.pers_y -= 1;
	else if (flag == 2)
		all->map.pers_y += 1;
	else if (flag == 3)
		all->map.pers_x -= 1;
	else if (flag == 4)
		all->map.pers_x += 1;
	// if (all->map.arr_map[all->map.pers_y][all->map.pers_x] == '3'
	// 	|| (all->map.arr_map[all->map.pers_y][all->map.pers_x] == '4'))
	// 	end_game(all);
	all->map.arr_map[all->map.pers_y][all->map.pers_x] = all->img.go_l_r;
	all->count_steps++;
}

void	check_step_1(t_all *all, int y, int flag)
{
	all->img.go_l_r = 'P';
	if (all->map.arr_map[all->map.pers_y - y][all->map.pers_x] == 'C')
	{
		all->map.c_count++;
		replacement(all, flag);
	}
	else if (all->map.arr_map[all->map.pers_y - y][all->map.pers_x] == 'E')
	{
		replacement(all, flag);
	}
	else if (all->map.arr_map[all->map.pers_y - y][all->map.pers_x] == '3')
	{
		replacement(all, flag);
		printf("\n\t --- Game over ---\n");
		end_game(all);
	}
	else if (all->map.arr_map[all->map.pers_y - y][all->map.pers_x] == '4')
	{
		replacement(all, flag);
		printf("\n\t --- Game over ---\n");
		end_game(all);
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
		replacement(all, flag);
		printf("\n\t --- Win ---\n");
	}
	else if (all->map.arr_map[all->map.pers_y][all->map.pers_x - x] == '3')
	{
		replacement(all, flag);
		printf("\n\t --- Game over ---\n");
		end_game(all);
	}
	else if (all->map.arr_map[all->map.pers_y][all->map.pers_x - x] == '4')
	{
		replacement(all, flag);
		printf("\n\t --- Game over ---\n");
		end_game(all);
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
	{
		all->img.go_l_r = '2';
		check_step_2(all, 1, 3);
	}
	else if (key == RIGHT
		&& all->map.arr_map[all->map.pers_y][all->map.pers_x + 1] != '1')
	{
		all->img.go_l_r = 'P';
		check_step_2(all, -1, 4);
	}
	else if (key == ESC)
		end_game(all);
	return (0);
}
