/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:48:52 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/03 05:56:04 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void init_var(t_all *all)
{
	all->mlx = 0;
	all->win = 0;
	all->map.width_map = 0;
	all->map.height_map = 0;
	all->map.p = 0;
	all->map.e = 0;
	all->map.c = 0;
	all->map.c_count = 0;
	all->map.x = 0;
	all->map.y = 0;
	(*all->map.arr_map) = NULL;
	all->map.arr_map = NULL;
	all->img.width_img = 64;
	all->img.height_img = 64;
	all->map.pers_x = 0;
	all->map.pers_y = 0;
	printf("===== init =====\n");
}

void program_logic(t_all *all, char const *argv[])
{
	init_var(all);
	printf("===== 2 =====\n");
	check_map(&all->map, argv[1]);
	printf("===== 3 =====\n");
	saving_the_map(&all->map, argv[1]);
	printf("===== 4 =====\n");
	all->mlx = mlx_init();
	printf("===== 5 =====\n");
	all->win = mlx_new_window(all->mlx, (all->map.width_map) * 64, all->map.height_map * 64, "so_long");
	printf("===== 6 =====\n");
	create_obj(all);
	printf("===== 7 =====\n");
	create_map(all);
	printf("===== 8 =====\n");
}

int main(int argc, char const *argv[])
{
	t_all all;

	if (argc != 2) // Должен принимать файл .ber 
	{
		write(1, "\033[1;37mError: Некорректный ввод\033[0m\n", 52);
		exit(EXIT_FAILURE);
	}
	// printf("===== 1 =====\n");
	program_logic(&all, argv);
	mlx_hook(all.win, 2, 1L<<0, key_ivent, &all);
	mlx_hook(all.win, 17, 0, end_game, &all);
	mlx_loop(all.mlx);

	return 0;
}