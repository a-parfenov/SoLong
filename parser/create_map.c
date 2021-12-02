/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 22:09:57 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/02 02:53:05 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void create_obj(t_all *all)
{
	all->pers.texture.xpm.pers = "images/personage_right.xpm";
	all->pers.texture.xpm.ex = "images/exit.xpm";
	all->pers.texture.xpm.floor = "images/fon.xpm";
	all->pers.texture.xpm.wall = "images/pesok.xpm";
	all->pers.texture.xpm.obj = "images/item.xpm";

	all->pers.texture.i_pers = mlx_xpm_file_to_image(all->mlx,
		all->pers.texture.xpm.pers, &all->pers.texture.width, &all->pers.texture.height);
	check_error(!((unsigned) all->pers.texture.i_pers));
	all->pers.texture.i_ex = mlx_xpm_file_to_image(all->mlx,
		all->pers.texture.xpm.ex, &all->pers.texture.width, &all->pers.texture.height);
	check_error(!((unsigned) all->pers.texture.i_ex));
	all->pers.texture.i_floor = mlx_xpm_file_to_image(all->mlx,
		all->pers.texture.xpm.floor, &all->pers.texture.width, &all->pers.texture.height);
	check_error(!((unsigned) all->pers.texture.i_floor));
	all->pers.texture.i_wall = mlx_xpm_file_to_image(all->mlx,
		all->pers.texture.xpm.wall, &all->pers.texture.width, &all->pers.texture.height);
	check_error(!((unsigned) all->pers.texture.i_wall));
	all->pers.texture.i_obj = mlx_xpm_file_to_image(all->mlx,
		all->pers.texture.xpm.obj, &all->pers.texture.width, &all->pers.texture.height);
	check_error(!((unsigned) all->pers.texture.i_obj));
	create_map(all);
	// mlx_put_image_to_window(all->mlx, all->win, all->pers.texture.i_pers,
	// 		all->pers.x, all->pers.y);
	
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
				mlx_put_image_to_window(all->mlx, all->win, all->pers.texture.i_floor,
					all->pers.x, all->pers.y);
			else if (all->map.arr_map[j][i] == '0')
				mlx_put_image_to_window(all->mlx, all->win, all->pers.texture.i_wall,
					all->pers.x, all->pers.y);
			else if (all->map.arr_map[j][i] == 'P')
			{
				mlx_put_image_to_window(all->mlx, all->win, all->pers.texture.i_pers,
					all->pers.x, all->pers.y);
				all->pers.pers_x = all->pers.x;
				all->pers.pers_y = all->pers.y;

				all->y = j;
				all->x = i;
					// сохранить координаты
			}
			else if (all->map.arr_map[j][i] == 'E')
				mlx_put_image_to_window(all->mlx, all->win, all->pers.texture.i_ex,
					all->pers.x, all->pers.y);
			else if (all->map.arr_map[j][i] == 'C')
				mlx_put_image_to_window(all->mlx, all->win, all->pers.texture.i_obj,
					all->pers.x, all->pers.y);
			all->pers.x += 64;
		}
		all->pers.y += 64;
		all->pers.x = 0;
	}
}