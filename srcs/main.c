/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:48:52 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/06 22:38:29 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	(*all->map.arr_map) = NULL;
	all->map.arr_map = NULL;
	all->count_steps = 0;
	all->img.width_img = 64;
	all->img.height_img = 64;
	all->map.pers_x = 0;
	all->map.pers_y = 0;
	all->j = -1;
}

void	program_logic(t_all *all, char **argv)
{
	init_var(all);
	check_map(&all->map, argv[1]);
	saving_the_map(&all->map, argv[1]);
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, (all->map.width_map) * 64,
			all->map.height_map * 64, "so_long");
	create_obj(all);
	create_map(all);
}

int	main(int argc, char **argv)
{
	t_all	all;

	check_error_argv(argc != 2, ERROR_0);
	check_error_argv(check_args(argv), ERROR_1);
	program_logic(&all, argv);
	mlx_hook(all.win, 2, 1L << 0, key_ivent, &all);
	mlx_hook(all.win, 17, 0, end_game, &all);
	mlx_loop(all.mlx);
	return (0);
}
