/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:20:17 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/07 01:28:29 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_error(unsigned int check_error, char *error_number, t_map *map)
{
	int	i;

	i = -1;
	if (check_error)
	{
		while (map->arr_map[++i])
			free(map->arr_map[i]);
		free(map->arr_map);
		perror(error_number);
		system("killall afplay");
		exit(EXIT_FAILURE);
	}
}

void	check_error_argv(unsigned int check_error, char *error_number)
{
	if (check_error)
	{
		perror(error_number);
		system("killall afplay");
		exit(EXIT_FAILURE);
	}
}

int	end_game(t_all *all, int flag)
{
	int		i;

	i = -1;
	(void) flag;
	while (all->map.arr_map[++i])
		free(all->map.arr_map[i]);
	free(all->map.arr_map);
	system("killall afplay");
	exit(0);
}

/*
** Вывод картинки в конце игры
int	end_game(t_all *all, int flag)
{
	int		i;
	void	*game_1;
	void	*game_2;
	all->map.x = 480;
	all->map.y = 360;

	mlx_clear_window(all->mlx, all->win);
	i = -1;
	if (flag == 1)
	{
		printf("123\n");
		game_1 = mlx_xpm_file_to_image(all->mlx,
			END_GAME_1, &all->map.x, &all->map.y);
		check_error(!((unsigned) game_1), ERROR_2, &all->map);
		mlx_put_image_to_window(all->mlx, all->win,
			game_1, 50, 50);
	}
	else if (flag == 0)
	{
		printf("456\n");
		mlx_clear_window(all->mlx, all->win);
		game_2 = mlx_xpm_file_to_image(all->mlx,
			END_GAME_2, &all->map.x, &all->map.y);
		check_error(!((unsigned) game_2), ERROR_2, &all->map);
		mlx_put_image_to_window(all->mlx, all->win,
			game_2, 50, 50);
	}
	usleep(1000000);
	while (all->map.arr_map[++i])
		free(all->map.arr_map[i]);
	free(all->map.arr_map);
	exit(0);
}
*/

int	check_argv(char **argv)
{
	int	i;

	i = 0;
	if (argv[1][i] == '.' && argv[1][i + 1] == '/')
		while (argv[1][i] && argv[1][i] != '.')
			i++;
	while (argv[1][i] && argv[1][i] != '.')
		i++;
	if (argv[1][i] == '.' && argv[1][i + 1] == 'b' &&
		argv[1][i + 2] == 'e' && argv[1][i + 3] == 'r' &&
		argv[1][i + 4] == '\0')
		return (0);
	return (1);
}

void	x_y_pers(t_all *all)
{
	int		j;

	j = -1;
	while (all->map.arr_map[++j])
	{
		all->k = -1;
		while (all->map.arr_map[j][++all->k])
		{
			if (all->map.arr_map[j][all->k] == 'P')
			{
				all->map.pers_y = j;
				all->map.pers_x = all->k;
				all->pers_w_y = j * SIZE_X;
				all->pers_w_x = all->k * SIZE_Y;
			}
			if (all->map.arr_map[j][all->k] == 'E')
				all->map.arr_map[j][all->k] = '0';
			if (all->map.arr_map[j][all->k] == ENEM_3
				|| all->map.arr_map[j][all->k] == ENEM_4)
			{
				all->enem_y = j;
				all->enem_x = all->k;
			}
		}
	}
}
