/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 03:46:06 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/06 19:15:51 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_map(t_all *all)
{
	while (all->map.arr_map[++all->j])
	{
		all->i = -1;
		while (all->map.arr_map[all->j][++all->i])
		{
			if (all->map.arr_map[all->j][all->i] == '1')
				mlx_put_image_to_window(all->mlx, all->win,
					all->img.i_fon, all->map.x, all->map.y);
			else if (all->map.arr_map[all->j][all->i] == '0')
				mlx_put_image_to_window(all->mlx, all->win,
					all->img.i_wall, all->map.x, all->map.y);
			else if (all->map.arr_map[all->j][all->i] == 'P')
				mlx_put_image_to_window(all->mlx, all->win,
					all->img.i_pers_r, all->map.x, all->map.y);
			else if (all->map.arr_map[all->j][all->i] == 'E')
				mlx_put_image_to_window(all->mlx, all->win,
					all->img.i_exit, all->map.x, all->map.y);
			else if (all->map.arr_map[all->j][all->i] == 'C')
				mlx_put_image_to_window(all->mlx, all->win,
					all->img.i_obj, all->map.x, all->map.y);
			all->map.x += 64;
		}
		all->map.y += 64;
		all->map.x = 0;
	}
}

void	print_map_arr(t_map *map)
{
	int	j;

	j = -1;
	write(1, "Map:\n", 5);
	while (map->arr_map[++j])
	{
		if (map->arr_map[j] != 0)
			printf("\t%s\n", map->arr_map[j]);
	}
	write(1, "\n", 1);
}

size_t	ft_strlen_s(char *str)
{
	size_t	res;

	res = 0;
	while (str[res])
		res++;
	return (res);
}
