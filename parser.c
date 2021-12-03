/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:59:43 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/03 04:27:34 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void saving_the_map(t_map *map, char const *file)
{
	int			fd;
	int			j;
	int			i;

	fd = open(file, O_RDONLY);
	printf("===== fd map = {%d} =====\n", fd);
	check_error(!fd);
	errno = 0;
	map->arr_map = malloc(sizeof(char *) * (map->height_map + 1)); ////
	// printf("===== arr_map = {%s} =====\n", map->arr_map);
	check_error(!map->arr_map);
	j = -1;
	while (map->height_map > ++j)
	{
		map->arr_map[j] = get_next_line(fd);
		// map->arr_map[j][ft_strlen_s(map->arr_map[j]) - 1] = 0;
		// check_error(map->arr_map[j] != '\0'); // #### добавить освобождение памяти при ошибке
	}
	close(fd);
	map->arr_map[j + 1] = NULL;
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
				printf("{%d %d}\n", map->pers_y, map->pers_x);
				break;
			}
			
		}
	}
	// ####### dell
	j = -1;
	while (map->arr_map[++j])
	{
		if (map->arr_map[j] != 0)
			printf("%s\n", map->arr_map[j]);
	}
	printf("******* sav map *******\n");
}

void check_symbols(t_map *map, char *line)
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

int check_size(char *line)
{
	int		i;
	int		j;
	
	i = 0;
	while (line[i])
	{
		j = 0;
		while (MAP_ALPHABET[j])
		{
			if (MAP_ALPHABET[j] == line[i])
				break;
			++j;
		}
		if (MAP_ALPHABET[j] == '\0')
			return (1);
		++i;
	}
	return (0);
}

void check_map(t_map *map, char const *file)
{
	char		*line;
	int			fd;
	int			len;

	fd = open(file, O_RDONLY);
	printf("===== fd size = {%d} =====\n", fd);
	check_error(!fd);
	line = (char *)1;
	len = 0;
	errno = 0;
	while (line)
	{
		line = get_next_line(fd);
		check_error(errno);
		if (line)
		{
			len = ft_strlen_s(line);
			line[len-1] = 0;
			// printf("%s\n", line);
			check_error(check_size(line));
			check_error(len != map->width_map && map->width_map);
		}
		map->width_map = len;
		map->height_map += line != NULL;
		check_symbols(map, line);
		free(line);
	}
	printf("%d %d\n", map->width_map, map->height_map);
	close(fd);
	if (!(map->c > 0 && map->e > 0 && map->p == 1))
	{
		perror("Проверьте карту");
		exit(EXIT_FAILURE);
	}
	
	printf("===== size_map =====\n");
}
