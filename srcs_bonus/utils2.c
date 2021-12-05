/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 03:46:06 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/05 13:59:13 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	create_map(t_all *all)
{
	mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_wall, all->map.x, all->map.y);
	if (all->map.arr_map[all->j][all->i] == '1')
		mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_fon, all->map.x, all->map.y);
	if (all->map.arr_map[all->j][all->i] == 'P')
		mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_pers_r, all->pers_w_x, all->pers_w_y);
	else if (all->map.arr_map[all->j][all->i] == 'E')
		mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_exit, all->map.x, all->map.y);
	else if (all->map.arr_map[all->j][all->i] == 'C')
		mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_obj, all->map.x, all->map.y);
	else if (all->map.arr_map[all->j][all->i] == '2')
		mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_pers_l, all->pers_w_x, all->pers_w_y);
	else if (all->map.arr_map[all->j][all->i] == ENEM_3)
		mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_enem_r, all->map.x, all->map.y);
	else if (all->map.arr_map[all->j][all->i] == '4')
		mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_enem_l, all->map.x, all->map.y);
}

void print_map_arr(t_all *all)
{
	int	j;

	j = -1;
	write(1, "\e[1;1H\e[2J", 10);
	write(1, "Map:\n", 5);
	while (all->map.arr_map[++j])
	{
		if (all->map.arr_map[j] != 0)
			printf("\t %s\n", all->map.arr_map[j]);
	}
	write(1, "\n", 1);
	printf("\t Steps: %d\n", all->count_steps);
	printf("\t Enemy: %d | %d \n", all->enem_y, all->enem_x);
}

size_t	ft_strlen_s(char *str)
{
	size_t	res;

	res = 0;
	while (str[res])
		res++;
	return (res);
}
