/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:20:17 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/04 04:53:13 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		exit(EXIT_FAILURE);
	}
}

void	check_error_argv(unsigned int check_error, char *error_number)
{
	if (check_error)
	{
		perror(error_number);
		exit(EXIT_FAILURE);
	}
}

int	end_game(t_all *all)
{
	int	i;

	i = -1;
	while (all->map.arr_map[++i])
		free(all->map.arr_map[i]);
	free(all->map.arr_map);
	exit(0);
}

int	check_args(char **argv)
{
	int	i;

	i = 0;
	if (argv[1][i] == '.' && argv[1][i + 1] == '/')
		while (argv[1][i] && argv[1][i] != '.')
			i++;
	while (argv[1][i] && argv[1][i] != '.')
		i++;
	if (argv[1][i] == '.' && argv[1][i + 1] == 'b' && \
	argv[1][i + 2] == 'e' && argv[1][i + 3] == 'r')
		return (0);
	return (1);
}

void	x_y_pers(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (map->arr_map[++j])
	{
		i = -1;
		while (map->arr_map[j][++i])
		{
			if (map->arr_map[j][i] == 'P')
			{
				map->pers_y = j;
				map->pers_x = i;
				return ;
			}
		}
	}
}
