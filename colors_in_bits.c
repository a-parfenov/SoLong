#include <stdio.h>
#include <unistd.h>

#define MAX_TYPE_SIZE sizeof(size_t)
#define SIZE_BITE 8

typedef	u_int64_t type_var;
typedef u_int8_t type_size;

#define FPS	180

#define	GetR(color) (((color) & 0xFF0000) >> 16)
#define	GetG(color) (((color) & 0x00FF00) >> 8)
#define	GetB(color) ((color) & 0x0000FF)

/*
** Отображение изменения битов
*/

void	print_data_std_type(type_var var, type_size size_type)
{
	type_var	c_var;

	c_var = var;
	size_type = (size_type + !size_type) % (MAX_TYPE_SIZE + 1) * 8;

	printf("bits in var :\n");
	for (size_t i = size_type - 1; i < size_type; --i)
	{
		if (i % SIZE_BITE == SIZE_BITE - 1)
			printf(" |");
		printf("%llu", var >> i & 1);
		if (i % SIZE_BITE == 0)
			printf("|");
	}
	printf("\n");

	size_type /= 8;
	for (size_t i = size_type - 1; i < size_type; --i)
		printf(" |%8llu|", var >> (i * 8) & 0xff);
	printf("\n");
}

/*
** Побитовое изменение цвета
*/

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

int main(void)
{
	int pos = 1;
	int sign = -1;
	int train[4] = {255, 2, 0, 112};
	int tmp = 0x8180ff;

	while (1)
	{
		write(1, "\e[2J", 4);
		tmp = rainbow_train(train, &sign, &pos);
		printf("\e[48;2;%i;%i;%im{%10s}\e[m\n", GetR(tmp), GetG(tmp), GetB(tmp),  "");
		print_data_std_type((int)(tmp), sizeof(int));
		usleep(1000000 / FPS);
	}
	return 0;
}