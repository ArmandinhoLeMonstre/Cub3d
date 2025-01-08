/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:48:07 by armitite          #+#    #+#             */
/*   Updated: 2025/01/07 18:54:13 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int index;

	if(x >= 1920 || y >= 1080 || x < 0 || y < 0)
        return;
	index = (y *  data->line_length) + x * (data->bits_per_pixel / 8);
	data->addr[index] = color & 0xFF;
    data->addr[index + 1] = (color >> 8) & 0xFF;
    data->addr[index + 2] = (color >> 16) & 0xFF;
}
int	draw_player(int x, int y, int size, t_data *data)
{
	int	i;
	int color;

	//printf("le x%d\n", x);
	//printf("le y%d\n", y);
	color = 0x00FF00;
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(data, x + i, y, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(data, x, y + i, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(data, x + i, y + size, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(data, x + size, y + i, color);
		i++;
	}
	return(0);
}

int	draw_loop(t_data *data)
{
	t_player *player = data->player;
	move_player(player);
	draw_player((int)round(player->x), (int)round(player->y), 10, data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_data	data;
	t_player	player;

	init_player(&player);
	data.player = &player;
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
								&data.endian);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_hook(data.mlx_win, 2, 1L<<0, key_true, &player);
	mlx_hook(data.mlx_win, 3, 1L<<0, key_false, &player);
	mlx_loop_hook(data.mlx, draw_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}

