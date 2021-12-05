/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:22:37 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/05 22:50:57 by aleslie          ###   ########.fr       */
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
	else if (all->map.arr_map[all->j][all->i] == 'P')
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

void	anim_pers(t_all *all)
{
	int	x;

	x = 3;
	all->pers_w_x = all->map.pers_x * SIZE_X;
	all->pers_w_y = all->map.pers_y * SIZE_Y;
	all->count_anim += 1;
	if (all->count_anim == 20)
		all->pers_w_x -= x;
	if (all->count_anim == 20)
		all->pers_w_y += x;	
	if (all->count_anim == 40)
		all->pers_w_x += x;
	if (all->count_anim == 40)
		all->pers_w_y -= x;
	if (all->count_anim == 60)
		all->pers_w_x -= x;
	if (all->count_anim == 60)
		all->pers_w_y += x;
	if (all->count_anim == 80)
		all->pers_w_x += x;
	if (all->count_anim == 80)
		all->pers_w_y -= x;
	if (all->count_anim > 80)
		all->count_anim = 0;
}

void	anim_enem(t_all *all)
{
    // printf("| %d %d |\n", all->enem_x, all->enem_y);
    if (all->enem_y == all->map.pers_y && all->enem_x == all->map.pers_x)
        end_game(all);
	if (!all->flag)
	{
		all->flag = -1;
	}
	if (all->map.arr_map[all->enem_y][all->enem_x + all->flag] == '0')
	{
		all->map.arr_map[all->enem_y][all->enem_x] = '0';
		all->map.arr_map[all->enem_y][all->enem_x + all->flag] = (3 + (all->flag < 0)) + 48;
		all->enem_x += all->flag;
        if (all->map.arr_map[all->enem_y][all->enem_x + all->flag] == 'P')
            printf("|");
            // end_game(all);
		if (all->map.arr_map[all->enem_y][all->enem_x + all->flag] != '0')
		{
			if (all->flag == -1)
				all->flag = 1;
			else
				all->flag = -1;
		}
		return ;
	}	
}

void	anim_enem_time(t_all *all)
{
	if (all->count_anim == 10)
		anim_enem(all);
	if (all->count_anim == 50)
		anim_enem(all);
}

void print_step_num(t_all	*all)
{
	char	*str;
	// int i = 0;

	str = NULL;
	str = ft_itoa(all->count_steps);
	check_error(str == NULL, ERROR_12, &all->map);
	
	mlx_string_put(all->mlx, all->win, 89, 18, 0x00FFFFFF, str);
	free(str);
}
