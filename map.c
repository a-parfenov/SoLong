/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 20:32:08 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/03 05:40:51 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_obj(t_all *all)
{
	all->img.i_pers_r = mlx_xpm_file_to_image(all->mlx, 
		PERS_R, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_pers_r));
	all->img.i_exit = mlx_xpm_file_to_image(all->mlx, 
		EXIT, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_exit));
	all->img.i_fon = mlx_xpm_file_to_image(all->mlx, 
		FON, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_fon));
	all->img.i_wall = mlx_xpm_file_to_image(all->mlx, 
		WALL, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_wall));
	all->img.i_obj = mlx_xpm_file_to_image(all->mlx, 
		OBJ, &all->img.width_img, &all->img.height_img);
	check_error(!((unsigned) all->img.i_obj));
}

void create_map(t_all *all)
{
	int		i;
	int		j;

	j = -1;
	while (all->map.arr_map[++j])
	{
		i = -1;
		while (all->map.arr_map[j][++i])
		{
			if (all->map.arr_map[j][i] == '1')
				mlx_put_image_to_window(all->mlx, all->win, 
					all->img.i_fon, all->map.x, all->map.y);
			else if (all->map.arr_map[j][i] == '0')
				mlx_put_image_to_window(all->mlx, all->win, 
					all->img.i_wall, all->map.x, all->map.y);
			else if (all->map.arr_map[j][i] == 'P')
				mlx_put_image_to_window(all->mlx, all->win, 
					all->img.i_pers_r, all->map.x, all->map.y);
			else if (all->map.arr_map[j][i] == 'E')
				mlx_put_image_to_window(all->mlx, all->win, 
					all->img.i_exit, all->map.x, all->map.y);
			else if (all->map.arr_map[j][i] == 'C')
				mlx_put_image_to_window(all->mlx, all->win,
					all->img.i_obj, all->map.x, all->map.y);
			all->map.x += 64;
		}
		all->map.y += 64;
		all->map.x = 0;
	}
}

void replacement(t_all *all, int flag)
{
		all->map.arr_map[all->map.pers_y][all->map.pers_x] = 0;
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
//				all->map.pers_x -= i; - <- 1
//				all->map.pers_y -= j; + <- -1;
//				
		all->map.arr_map[all->map.pers_y][all->map.pers_x] = 'P';
		mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_pers_r, all->map.pers_x * SIZE_X, all->map.pers_y * SIZE_Y);
}

int key_ivent(int key, t_all *all)
{
	printf("%d\n", key);
	// if (key == S_UP)
	// 	all->pers.speed += 64;
	// else if (key == S_DOWN)
	// 	all->pers.speed -= 64;
	if (key == UP && all->map.arr_map[all->map.pers_y - 1][all->map.pers_x] != '1')
	{
		if (all->map.arr_map[all->map.pers_y - 1][all->map.pers_x] == 'C')
			all->map.c_count++;
		else if (all->map.arr_map[all->map.pers_y - 1][all->map.pers_x] == 'E')
		{
			if (all->map.c_count == all->map.c)
				{
					replacement(all, 1);
					exit(0);
				}
			else
				return (0);
		}
		replacement(all, 1);
	}
	else if (key == DOWN && all->map.arr_map[all->map.pers_y + 1][all->map.pers_x] != '1')
	{
		if (all->map.arr_map[all->map.pers_y + 1][all->map.pers_x] == 'C')
			all->map.c_count++;
		else if (all->map.arr_map[all->map.pers_y + 1][all->map.pers_x] == 'E')
		{
			if (all->map.c_count == all->map.c)
				{
					replacement(all, 2);
					exit(0);
				}
			else
				return (0);
		}
		replacement(all, 2);
	}
	else if (key == LEFT && all->map.arr_map[all->map.pers_y][all->map.pers_x - 1] != '1')
	{
		if (all->map.arr_map[all->map.pers_y][all->map.pers_x - 1] == 'C')
			all->map.c_count++;
		else if (all->map.arr_map[all->map.pers_y][all->map.pers_x - 1] == 'E')
		{
			if (all->map.c_count == all->map.c)
				{
					replacement(all, 3);
					exit(0);
				}
			else
				return (0);
		}
		replacement(all, 3);
	}
	else if (key == RIGHT && all->map.arr_map[all->map.pers_y][all->map.pers_x + 1] != '1')
	{
		if (all->map.arr_map[all->map.pers_y][all->map.pers_x + 1] == 'C')
			all->map.c_count++;
		else if (all->map.arr_map[all->map.pers_y][all->map.pers_x + 1] == 'E')
		{
			if (all->map.c_count == all->map.c)
				{
					replacement(all, 4);
					exit(0);
				}
			else
				return (0);
		}
		replacement(all, 4);
	}
	else if (key == ESC)
		exit(0); // лики
	return 0;
}