/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 03:46:06 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/06 19:18:00 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	print_map_arr(t_all *all)
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

void	print_step_num(t_all	*all)
{
	char	*str;

	str = NULL;
	str = ft_itoa(all->count_steps);
	check_error(str == NULL, ERROR_12, &all->map);
	mlx_string_put(all->mlx, all->win, 10, 18, 0xFF0000, "Steps:");
	mlx_string_put(all->mlx, all->win, 55, 18, 0xFF0000, str);
	free(str);
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
	all->map.arr_map[all->map.pers_y][all->map.pers_x] = all->img.go_l_r;
	all->count_steps++;
}
