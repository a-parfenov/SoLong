/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:48:52 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/07 02:35:05 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	render_next_frame(t_all	*all)
{
	all->i = 0;
	all->j = 0;
	all->map.x = 0;
	all->map.y = 0;
	while (all->map.y < all->map.height_map * 64)
	{
		all->i = 0;
		while (all->map.x < all->map.width_map * 64)
		{
			create_map(all);
			all->map.x += 64;
			all->i++;
		}
		all->map.y += 64;
		all->map.x = 0;
		all->j++;
	}
	if (all->map.c_count == all->map.c)
		all->map.arr_map[all->prt_y - 1][all->prt_x] = 'E';
	print_map_arr(all);
	all->count_m += 15;
	anim_enem_time(all);
	print_step_num(all);
	return (0);
}

void	init_var(t_all *all)
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
	all->prt_x = 0;
	all->prt_y = 0;
	(*all->map.arr_map) = NULL;
	all->map.arr_map = NULL;
	all->count_steps = 0;
	all->img.width_img = 64;
	all->img.height_img = 64;
	all->map.pers_x = 0;
	all->map.pers_y = 0;
	all->line = (char *)1;
	all->j = -1;
	all->k = -1;
	all->flag = 0;
	all->count_anim = 0;
	all->count_m = 0;
}

void	program_logic(t_all *all, char **argv)
{
	init_var(all);
	check_map(all, argv[1]);
	saving_the_map(all, argv[1]);
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, (all->map.width_map) * 64,
			all->map.height_map * 64, "so_long");
	create_obj(all);
}

int	main(int argc, char **argv)
{
	t_all	all;
	pid_t	n;

	check_error_argv(argc != 2, ERROR_0);
	check_error_argv(check_argv(argv), ERROR_1);
	program_logic(&all, argv);
	mlx_hook(all.win, 2, 1L << 0, key_ivent, &all);
	mlx_hook(all.win, 17, 0, end_game, &all);
	mlx_loop_hook(all.mlx, render_next_frame, &all);
	n = fork();
	if (n == 0)
		system("afplay Enemy.mp3");
	mlx_loop(all.mlx);
	return (0);
}
