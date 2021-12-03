/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:20:17 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/02 23:20:52 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_error(unsigned int check_error)
{
	if (check_error)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

size_t	ft_strlen_s(char *str)
{
	size_t	res;

	res = 0;
	while (str[res])
		res++;
	return (res);
}

int end_game(void)
{
	exit(0);
	return 0;
}

char	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;

	mem = malloc(count * size);
	if (!mem)
		return (0);
	i = 0;
	while (i < count * size)
	{
		mem[i] = '\0';
		i++;
	}
	return (mem);
}