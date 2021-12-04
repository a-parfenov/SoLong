/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:59:43 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/04 04:31:18 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	check_symbols(t_map *map, char *line)
{
	int		i;

	i = 0;
	if (line == NULL)
		return ;
	while (line[i])
	{
		if (line[i] == 'P')
			map->p++;
		else if (line[i] == 'E')
			map->e++;
		else if (line[i] == 'C')
			map->c++;
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

void	check_map(t_map *map, char *file)
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
			check_error_argv(len != map->width_map && map->width_map, ERROR_9);
			map->height_map += *line != 0;
		}
		map->width_map = len;
		check_symbols(map, line);
		free(line);
	}
	close(fd);
	check_error_argv(!(map->c > 0 && map->e > 0 && map->p == 1), ERROR_10);
}

void	saving_the_map(t_map *map, char *file)
{
	int			fd;
	int			j;
	char		*buf;

	fd = open(file, O_RDONLY);
	check_error(!fd, ERROR_3, map);
	errno = 0;
	map->arr_map = malloc(sizeof(char *) * (map->height_map + 1));
	check_error(!map->arr_map, ERROR_4, map);
	j = 0;
	while (map->height_map > j)
	{
		buf = get_next_line(fd);
		check_error(errno, ERROR_5, map);
		if (buf && buf[0] != 0)
			map->arr_map[j++] = buf;
	}
	close(fd);
	map->arr_map[j] = NULL;
	x_y_pers(map);
	map_boundaries(map);

	/* del */
	j = -1;
	while (map->arr_map[++j])
	{
		if (map->arr_map[j] != 0)
			printf("%s\n", map->arr_map[j]);
	}
}
