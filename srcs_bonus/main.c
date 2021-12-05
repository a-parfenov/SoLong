/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:48:52 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/05 22:07:16 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int render_next_frame(t_all	*all)
{
	int 	flag;
	int		i;
	int		j;
	// static	int t;

	i = 0;
	j = 0;
	flag = 1;
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

	
	// while (all->map.arr_map[i])
	// {
	// 	j = 0;
	// 	while (all->map.arr_map[i][j])
	// 	{
	// 		if (all->map.arr_map[i][j] == 'E')
	// 			flag = 0;
	// 		j++;
	// 	}
	// 	i++;
	// }
	// if (flag)
	// {
	// 	if (!t)
	// 		t = time(NULL);
	// 	if (time(NULL) - t > 200000)
	// 		end_game(all);
	// }

	
	if (all->map.c_count == all->map.c)
		all->map.arr_map[all->prt_y - 1][all->prt_x] = 'E';
	// printf("| %d %d %d %d |\n", all->prt_y, all->prt_x, all->map.c_count, all->map.c);
	// print_map_arr(all);
	anim_pers(all);
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
	all->j = -1;
	all->flag = 0;
	all->count_anim = 0;
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

	check_error_argv(argc != 2, ERROR_0);
	check_error_argv(check_argv(argv), ERROR_1);
	program_logic(&all, argv);
	mlx_hook(all.win, 2, 1L << 0, key_ivent, &all);
	mlx_hook(all.win, 17, 0, end_game, &all);
	mlx_loop_hook(all.mlx, render_next_frame, &all);
	mlx_loop(all.mlx);
	return (0);
}
