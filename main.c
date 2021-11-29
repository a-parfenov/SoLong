/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:43:02 by aleslie           #+#    #+#             */
/*   Updated: 2021/11/30 00:20:34 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

# define WIDTH 100
# define HEIGHT 100

// KEY CODES
# define ESC 53
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2

#define S_UP 24
#define S_DOWN 27

typedef struct	s_img 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel; // кол-во бит на пиксель
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_pers
{
	int			x; // + вправо
	int			y; // + вниз
	int			speed;
	t_img		texture;
}				t_pers;

typedef struct s_list
{
	void			*mlx; // инициализация
	void			*win;
	t_pers			pers;
}				t_all;

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int key_ivent(int key, t_all *all)
{
	printf("%d\n", key);
	if (key == S_UP)
		all->pers.speed++;
	else if (key == S_DOWN)
		all->pers.speed--;
	else if (key == UP)
		all->pers.y -= all->pers.speed;
	else if (key == DOWN)
		all->pers.y += all->pers.speed;
	else if (key == LEFT)
		all->pers.x -= all->pers.speed;
	else if (key == RIGHT)
		all->pers.x += all->pers.speed;
	mlx_clear_window(all->mlx, all->win);
	mlx_put_image_to_window(all->mlx, all->win, 
			all->pers.texture.img, all->pers.x, all->pers.y);
	return 0;
}

int end_game(void)
{
	exit(0);
	return 0;
}

// int game_ivent(t_all *all)
// {
// 	// менять цвет
// }

int main(void)
{
	t_all all;
	
	all.pers.speed = 1;
	all.pers.x = 1;
	all.pers.y = 1;
	all.mlx = mlx_init();
	all.win = mlx_new_window(all.mlx, 1920, 1080, "so_long");
	all.pers.texture.img = mlx_new_image(all.mlx, WIDTH, HEIGHT);
	all.pers.texture.addr = mlx_get_data_addr(all.pers.texture.img, &all.pers.texture.bits_per_pixel, &all.pers.texture.line_length,
								&all.pers.texture.endian);
								
	for (size_t x = 0; x < WIDTH; x++)
		for (size_t y = 0; y < HEIGHT; y++)
			my_mlx_pixel_put(&all.pers.texture, x, y, 0x0032CD32);
	
	mlx_put_image_to_window(all.mlx, all.win, all.pers.texture.img, all.pers.x, all.pers.y);
	// mlx_loop_hook(all.mlx, game_ivent, &all); // анимация без события
	mlx_hook(all.win, 2, 0, key_ivent, &all); // обработчик события
	mlx_hook(all.win, 17, 0, end_game, &all);
	mlx_loop(all.mlx);

	return 0;
}
