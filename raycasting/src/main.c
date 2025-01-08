/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:48:07 by armitite          #+#    #+#             */
/*   Updated: 2025/01/08 21:09:07 by armitite         ###   ########.fr       */
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

	color = 0x00FF00;
	i = 0;
	if(x >= 1920 || y >= 1080 || x < 0 || y < 0)
        return (0);
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

void	clear_image(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			my_mlx_pixel_put(data, x, y, 0);
			x++;
		}
		y++;
	}
}

void	draw_map(t_data *data)
{
	char	**map;
	int		y;
	int		x;

	map = data->map;
	y = 0;
	x = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_player(x * CUBE, y * CUBE, CUBE, data);
			x++;
		}
		y++;
	}
	
}

int	touch(float px, float py, t_data *data)
{
	int	x;
	int	y;

	x = px / CUBE;
	y = py / CUBE;
	if (data->map[y][x] == '1')
		return (1);
	return (0);
}

void	draw_line(t_player *player, t_data *data, float start_x, int i)
{
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;

	if (i == -23)
		return ;
	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	while (!touch(ray_x, ray_y, data))
	{
		my_mlx_pixel_put(data, ray_x, ray_y, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
}

int	draw_loop(t_data *data)
{
	t_player *player = data->player;
	float fraction;
    float start_x;
    int i;
	
	fraction = PI / 3 / 1080;
	start_x = player->angle - PI / 6;
	i = 0;
	move_player(player);
	clear_image(data);
	draw_player((player->x), (player->y), 10, data);
	draw_map(data);
    while(i < 1080)
    {
        draw_line(player, data, start_x, i);
        start_x += fraction;
        i++;
    }
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 17);
    map[0] = "11111111111111111111111111111";
    map[1] = "10000000000000000000000000001";
    map[2] = "10000000000000000000000000001";
    map[3] = "10000010000000000000000000001";
    map[4] = "10000000000000000000000000001";
    map[5] = "10000001000000000000000000001";
    map[6] = "10000100000000000000000000001";
    map[7] = "10000000000000000000000000001";
    map[8] = "10000000000000000000000000001";
	map[9] = "10000000000000000000000000001";
	map[10] = "10000000000000000000000000001";
	map[11] = "10000000000000000000000000001";
	map[12] = "10000000000000000000000000001";
	map[13] = "10000000000000000000000000001";
	map[14] = "10000000000000000000000000001";
    map[15] = "11111111111111111111111111111";
    map[16] = NULL;
    return (map);
}

int	main(void)
{
	t_data	data;
	t_player	player;

	init_player(&player);
	data.player = &player;
	data.map = get_map();
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
								&data.endian);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	mlx_hook(data.mlx_win, 2, 1L<<0, key_true, &player);
	mlx_hook(data.mlx_win, 3, 1L<<1, key_false, &player);
	mlx_loop_hook(data.mlx, draw_loop, &data);
	mlx_loop(data.mlx);
	return (0);
}

