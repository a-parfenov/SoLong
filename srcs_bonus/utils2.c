/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 03:46:06 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/05 21:23:13 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

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
