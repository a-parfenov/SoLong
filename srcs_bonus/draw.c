/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 21:22:37 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/07 02:39:12 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	draw_money(t_all *all)
{
	if (all->count_m <= 200 && all->count_m >= 0)
		mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_obj, all->map.x + 15, all->map.y + 15);
	if (all->count_m <= 400 && all->count_m >= 200)
		mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_obj2, all->map.x + 15, all->map.y + 15);
	if (all->count_m <= 600 && all->count_m >= 400)
		mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_obj3, all->map.x + 15, all->map.y + 15);
	if (all->count_m <= 800 && all->count_m >= 600)
		mlx_put_image_to_window(all->mlx, all->win,
			all->img.i_obj4, all->map.x + 15, all->map.y + 15);
	if (all->count_m <= 1000 && all->count_m >= 800)
		mlx_put_image_to_window(all->mlx, all->win,
			all->i_obj5, all->map.x + 15, all->map.y + 15);
	if (all->count_m <= 1200 && all->count_m >= 1000)
		mlx_put_image_to_window(all->mlx, all->win,
			all->i_obj6, all->map.x + 15, all->map.y + 15);
	if (all->count_m <= 1400 && all->count_m >= 1200)
		mlx_put_image_to_window(all->mlx, all->win,
			all->i_obj7, all->map.x + 15, all->map.y + 15);
	if (all->count_m <= 1600 && all->count_m >= 1400)
		mlx_put_image_to_window(all->mlx, all->win,
			all->i_obj8, all->map.x + 15, all->map.y + 15);
}

void	create_map(t_all *all)
{
	if (all->count_m > 1400)
		all->count_m = 0;
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
		draw_money(all);
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

	x = 0;
	all->pers_w_x = all->map.pers_x * SIZE_X;
	all->pers_w_y = all->map.pers_y * SIZE_Y;
	all->count_anim += 5;
	if (all->count_anim == 20)
		all->pers_w_x -= x;
	if (all->count_anim == 40)
		all->pers_w_y += x;
	if (all->count_anim == 60)
		all->pers_w_x += x;
	if (all->count_anim == 80)
		all->pers_w_y -= x;
	if (all->count_anim == 100)
		all->pers_w_x -= x;
	if (all->count_anim == 120)
		all->pers_w_y += x;
	if (all->count_anim == 140)
		all->pers_w_x += x;
	if (all->count_anim == 160)
		all->pers_w_y -= x;
	if (all->count_anim > 160)
		all->count_anim = 0;
}

void	anim_enem(t_all *all)
{
	if (!all->flag)
	{
		all->flag = -1;
	}
	if (all->map.arr_map[all->enem_y][all->enem_x - 1] == 'P')
		end_game(all, 1);
	if (all->map.arr_map[all->enem_y][all->enem_x + 1] == 'P')
		end_game(all, 1);
	if (all->map.arr_map[all->enem_y][all->enem_x - 1] == '2')
		end_game(all, 1);
	if (all->map.arr_map[all->enem_y][all->enem_x + 1] == '2')
		end_game(all, 1);
	if (all->map.arr_map[all->enem_y][all->enem_x + all->flag] == '0')
	{
		all->map.arr_map[all->enem_y][all->enem_x] = '0';
		all->map.arr_map
		[all->enem_y][all->enem_x + all->flag] = (3 + (all->flag < 0)) + 48;
		all->enem_x += all->flag;
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
	anim_pers(all);
	if (all->count_anim == 10)
		anim_enem(all);
	if (all->count_anim == 50)
		anim_enem(all);
}
