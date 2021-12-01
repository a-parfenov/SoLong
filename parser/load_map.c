/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 22:53:51 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/01 05:28:10 by aleslie          ###   ########.fr       */
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
	
	// printf("check_symbol\n");
	i = 0;
	while (str[i])
	{
		j = 0;
		while (MAP_ALPHABET[j])
		{
			if (MAP_ALPHABET[j] == str[i])
			{
				// printf("{%c}\n", MAP_ALPHABET[j]);
				break;
			}
			// printf("%c\n", MAP_ALPHABET[j]);
			++j;
		}
		// if (MAP_ALPHABET[j] == '\0')	
		// 	printf("error\n");
		// printf("{***}\n");
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
		check_error(errno);
		if (line)
		{
			len = ft_strlen_s(line);
			line[len - 1] = '\0';
			check_error(check_size(line));
			check_error(len != map->width && map->width);
		}
		map->width = len;
		map->height += line != NULL;
		check_symbols(map, line);
		// printf("//////\n");
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
	char		*line;
	int			len;
	int			i;
	int			j;
	
	printf("----------------------\n");
	fd = open(file, O_RDONLY);
	line = (char *)1;
	len = 0;
	errno = 0;
	// int x = map->width;
	// int y = map->height;
	map->arr_map = malloc(map->height * sizeof(t_map *));
	check_error(!map->arr_map);
	i = 0;
	while (i < map->width)
	{
		map->arr_map[i] = malloc((map->width ) * sizeof(t_map *));
		check_error(!map->arr_map); // добавить освобождение памяти при ошибках
		++i;
	}
	i = 0;
	j = -1;
	printf("------------- 2 ---------\n");
	while (line)
	{
		line = get_next_line(fd);
		check_error(errno); // добавить освобождение памяти при ошибках
		while (line[++j])
			map->arr_map[i][j] += line[j];
		map->arr_map[i][j] += '\0';
		printf("{%s}\n", map->arr_map[i]);
		++i;
		printf("----------- 3n -----------\n");
		free(line);
	}
	close(fd);

	i = 0;
	j = -1;
	printf("----------------------\n");
	while (map->arr_map[i])
	{
		while (map->arr_map[i][j])
		{
			printf("%d", map->arr_map[i][j]);
			
		}
		printf("\n");
	}
	printf("********************\n");
}

void parser(t_all *all, char const *argv[])
{
	check_size_map(&all->map, argv[1]);
	saving_the_map(&all->map, argv[1]);

}

// [0][0][0][0][0][0][0]
// [0][0][0][0][0][0][0]
// [0][0][0][0][0][0][0]
// [0][0][0][0][0][0][0]
// [0][0][0][0][0][0][0]
// [0][0][0][0][0][0][0]
