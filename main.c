/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:43:02 by aleslie           #+#    #+#             */
/*   Updated: 2021/12/01 03:54:42 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		all->pers.speed += 10;
	else if (key == S_DOWN)
		all->pers.speed -= 10;
	else if (key == UP)
		all->pers.y -= all->pers.speed;
	else if (key == DOWN)
		all->pers.y += all->pers.speed;
	else if (key == LEFT)
		all->pers.x -= all->pers.speed;
	else if (key == RIGHT)
		all->pers.x += all->pers.speed;
	else if (key == ESC)
		exit(0);
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

int	rainbow_train(int *train, int *sign, int *cur_pos)
{
	int next_step;
	int	res;

	res = train[3] << 24 | train[0] << 16 | train[1] << 8 | train[2];

	next_step = train[*cur_pos] + *sign;
	if (next_step < 0 || 255 < next_step)
	{
		*cur_pos = (*cur_pos + 2) % 3;
		*sign *= -1;
	}
	next_step = train[*cur_pos] + *sign;
	if (next_step < 0 || 255 < next_step)
	{
		*cur_pos = (*cur_pos + 2) % 3;
		*sign *= -1;
	}
	else
		train[*cur_pos] += *sign;

	return (res);
}

void	paint_square(t_img *img, ssize_t w, ssize_t h, int color)
{
	if (w > img->line_length / (img->bits_per_pixel / 8))
		w = img->line_length / (img->bits_per_pixel / 8);
	if (h > img->height)
		h = img->height;
	for (ssize_t x = 0; x < w; x++)
		for (ssize_t y = 0; y < h; y++)
			my_mlx_pixel_put(img, x, y, color);
}

int game_ivent(t_all *all)
{
	int color;

	color = rainbow_train(all->color.train, &all->color.sign, &all->color.pos);
	paint_square(&all->pers.texture, WIDTH, HEIGHT, color);
	usleep(1000000 / FPS);
	mlx_clear_window(all->mlx, all->win);
	mlx_put_image_to_window(all->mlx, all->win, 
			all->pers.texture.img, all->pers.x, all->pers.y);
	return (1);
}

void init_var(t_all *all)
{
	all->color.pos = 1;
	all->color.sign = 3; // знак больше / меньше
	all->color.train[0] = 255;
	all->color.train[1] = 0;
	all->color.train[2] = 0;
	all->color.train[3] = 112;
	all->pers.speed = 3;
	all->pers.x = 1;
	all->pers.y = 1;
	all->map.width = 0;
	all->map.height = 0;
	all->mlx = mlx_init();
	all->win = mlx_new_window(all->mlx, 1920, 1080, "so_long");
	all->pers.texture.height = HEIGHT;
	all->pers.texture.img = mlx_new_image(all->mlx, WIDTH, HEIGHT);
	all->pers.texture.addr = mlx_get_data_addr(all->pers.texture.img,
			&all->pers.texture.bits_per_pixel,
			&all->pers.texture.line_length,
			&all->pers.texture.endian);
	all->map.p = 0;
	all->map.e = 0;
	all->map.c = 0;
}

int main(int argc, char const *argv[])
{
	t_all all;
	// void	*img_check;
	// char	*relative_path = "images/test.xpm";
	// int		img_width = 500;
	// int		img_height = 500;
	
	if (argc != 2)
	{
		write(1, "\033[1;31mError!\033[0m \033[1;37mДля запуска игры введите: ./so_long map_name.ber\033[0m\n", 99);
		return (0);
	}
	parser(&all, argv);
	init_var(&all);
	
	// img_check = mlx_xpm_file_to_image(all.mlx, relative_path, &img_width, &img_height);
	// if (img_check == NULL)
	// 	{
	// 		write(1, "Error: Image reading failed\n", 28);
	// 		return (-1);
	// 	}
	// mlx_put_image_to_window(all.mlx, all.win, img_check,
	// 		all.pers.x, all.pers.y);
	
	mlx_loop_hook(all.mlx, game_ivent, &all); // анимация без события
	mlx_hook(all.win, 2, 1L<<0, key_ivent, &all); // обработчик события, 2 - нажатие клавиши
	mlx_hook(all.win, 17, 0, end_game, &all);
	mlx_loop(all.mlx);

	return 0;
}
