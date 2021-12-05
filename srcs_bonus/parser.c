/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:59:43 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/05 11:24:36 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	map_boundaries(t_map *map)
{
	int	i;

	i = -1;
	while (map->arr_map[0][++i])
	{
		if (map->arr_map[0][i] != '1')
			check_error(1, ERROR_11, map);
	}
	i = 0;
	while (map->arr_map[++i])
	{
		if (map->arr_map[i][map->width_map - 1] != '1')
			check_error(1, ERROR_11, map);
		if (map->arr_map[i][0] != '1')
			check_error(1, ERROR_11, map);
	}
	i = -1;
	while (map->arr_map[map->height_map - 1][++i])
	{
		if (map->arr_map[map->height_map - 1][i] != '1')
			check_error(1, ERROR_11, map);
	}
}

void	check_symbols(t_all *all, char *line)
{
	int		i;

	i = 0;
	if (line == NULL)
		return ;
	while (line[i])
	{
		if (line[i] == 'P')
			all->map.p++;
		else if (line[i] == 'E')
		{
			all->map.e++;
			all->prt_x = i;
			all->prt_y = all->map.height_map;
		}
		else if (line[i] == 'C')
			all->map.c++;
		++i;
	}
}

int	check_alpha(char *line)
{
	int		i;
	int		j;

	i = 0;
	while (line[i])
	{
		j = 0;
		while (MAP_ALPHA[j])
		{
			if (MAP_ALPHA[j] == line[i])
				break ;
			++j;
		}
		if (MAP_ALPHA[j] == '\0')
			return (1);
		++i;
	}
	return (0);
}

void	check_map(t_all *all, char *file)
{
	char	*line;
	int		fd;
	int		len;

	fd = open(file, O_RDONLY);
	check_error_argv(!fd, ERROR_6);
	line = (char *)1;
	errno = 0;
	while (line)
	{
		line = get_next_line(fd);
		check_error_argv(errno, ERROR_7);
		if (line && line[0] != 0)
		{
			len = ft_strlen_s(line);
			check_error_argv(check_alpha(line), ERROR_8);
			check_error_argv(len != all->map.width_map && all->map.width_map, ERROR_9);
			all->map.height_map += *line != 0;
		}
		all->map.width_map = len;
		check_symbols(all, line);
		free(line);
	}
	close(fd);
	check_error_argv(!(all->map.c > 0 && all->map.e > 0 && all->map.p == 1), ERROR_10);
}

void	saving_the_map(t_all *all, char *file)
{
	int			fd;
	int			j;
	char		*buf;

	fd = open(file, O_RDONLY);
	check_error(!fd, ERROR_3, &all->map);
	errno = 0;
	all->map.arr_map = malloc(sizeof(char *) * (all->map.height_map + 1));
	check_error(!all->map.arr_map, ERROR_4, &all->map);
	j = 0;
	while (all->map.height_map > j)
	{
		buf = get_next_line(fd);
		check_error(errno, ERROR_5, &all->map);
		if (buf && buf[0] != 0)
			all->map.arr_map[j++] = buf;
	}
	close(fd);
	all->map.arr_map[j] = NULL;
	x_y_pers(all);
	map_boundaries(&all->map);
}
