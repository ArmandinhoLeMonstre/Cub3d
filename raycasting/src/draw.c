/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:17:09 by armitite          #+#    #+#             */
/*   Updated: 2025/01/13 21:40:58 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int index;

	//printf("%d\n", color);
	if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;
	index = (y *  data->line_length) + x * (data->bits_per_pixel / 8);
	data->addr[index] = color & 0xFF;
    data->addr[index + 1] = (color >> 8) & 0xFF;
    data->addr[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(data, x, y, 0);
			x++;
		}
		y++;
	}
}

void	draw_line(t_player *player, t_data *data, float start_x, int i)
{
	float	ray_x;
	float	ray_y;
	float	cos_angle;
	float	sin_angle;
	float dist;
	float height;
	int start_y;
	int	end;
	t_wall *wall;

	if (i == -23)
		return ;
	wall = data->wall;
	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	while (!touch(ray_x, ray_y, data))
	{
		//my_mlx_pixel_put(data, ray_x, ray_y, 0xFF0000);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	dist = fixed_dist(player->x, player->y, ray_x, ray_y, data);
	height = (CUBE / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	int z = 0;
	while (ft_strncmp(wall->wall[0], wall->pixels[z], 1) != 0)
	{
		z++;
	}
	end = start_y + height;
	char *color;
	color = ft_strchr_g(wall->pixels[z], '#');
	printf("1: %s\n", color);
	int color2 = ft_atoi_base("FF00FF", "0123456789");
	printf("2: %d\n", color2);
	while (start_y < end)
	{	
		my_mlx_pixel_put(data, i, start_y, 0xFFFF00);
		start_y++;
	}
}

int	draw_loop(t_data *data)
{
	t_player *player = data->player;
	float fraction;
    float start_x;
    int i;
	
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	move_player(player);
	clear_image(data);
	//draw_player((player->x), (player->y), 10, data);
	//draw_map(data);
    while(i < WIDTH)
    {
        draw_line(player, data, start_x, i);
        start_x += fraction;
        i++;
    }
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	return (0);
}