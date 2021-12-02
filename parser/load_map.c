/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 22:53:51 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/02 02:56:27 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen_s(char *str)
{
	size_t	res;

	res = 0;
	while (str[res])
		res++;
	return (res);
}

void	check_error(unsigned int check_error)
{
	if (check_error)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
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

int check_size(char *str)
{
	int		i;
	int		j;
	
	i = 0;
	while (str[i])
	{
		j = 0;
		while (MAP_ALPHABET[j])
		{
			if (MAP_ALPHABET[j] == str[i])
				break;
			++j;
		}
		if (MAP_ALPHABET[j] == '\0')
			return (1);
		++i;
	}
	return (0);
}

void check_size_map(t_map *map, char const *file)
{
	int				fd;
	char			*line;
	int	len;

	fd = open(file, O_RDONLY);
	line = (char *)1;
	len = 0;
	errno = 0;
	while (line)
	{
		line = get_next_line(fd);
		// check_error(errno);
		if (line)
		{
			len = ft_strlen_s(line);
			line[len - 1] = '\0';
			check_error(check_size(line));
			// check_error(len != map->width && map->width);
		}
		map->width = len;
		map->height += line != NULL;
		check_symbols(map, line);
		free(line);
	}
	close(fd);
	
	// printf("-------+ %d\n", map->c);
	// printf("------- %d\n", map->e);
	// printf("------- %d\n", map->p);
	if (!(map->c > 0 && map->e > 0 && map->p == 1))
	{
		perror("На карте нет всех необходимых символов");
		exit(EXIT_FAILURE);
	}
}

void saving_the_map(t_map *map, char const *file)
{
	int			fd;
	int			j;

	fd = open(file, O_RDONLY);
	errno = 0;
	map->arr_map = calloc((map->height + 1), sizeof(char)); ////
	// map->arr_map[map->height] = NULL;
	// check_error(!map->arr_map);
	j = 0;
	while (map->height > j)
	{
		map->arr_map[j++] = get_next_line(fd);
		// check_error(errno); // добавить освобождение памяти при ошибке
	}
	close(fd);
	
	// dell
	// j = -1;
	// while (map->arr_map[++j])
	// {
	// 	printf("%s", map->arr_map[j]);
	// }
	printf("***************\n");
}

void parser(t_all *all, char const *argv[])
{
	check_size_map(&all->map, argv[1]);
	saving_the_map(&all->map, argv[1]);
	
}

