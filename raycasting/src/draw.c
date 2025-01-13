/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:17:09 by armitite          #+#    #+#             */
/*   Updated: 2025/01/13 23:26:12 by armitite         ###   ########.fr       */
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

void draw_line(t_player *player, t_data *data, float start_angle, int i) {
    float ray_x, ray_y, cos_angle, sin_angle, dist, height;
    int start_y, end, tex_x, tex_y;
    t_wall *wall = data->wall;

    // Initialize ray
    ray_x = player->x;
    ray_y = player->y;
    cos_angle = cos(start_angle);
    sin_angle = sin(start_angle);

    // Cast ray until it hits a wall
    while (!touch(ray_x, ray_y, data)) {
        ray_x += cos_angle;
        ray_y += sin_angle;
    }

    // Calculate distance and wall height
    dist = fixed_dist(player->x, player->y, ray_x, ray_y, data);
    height = (CUBE / dist) * (WIDTH / 2);
    start_y = (HEIGHT - height) / 2;
    end = start_y + height;

    // Determine wall type and texture offset
    float wall_x;
    if (fabs(cos_angle) > fabs(sin_angle)) { // Vertical wall
        wall_x = fmod(ray_y, CUBE) / CUBE;
    } else {                                // Horizontal wall
        wall_x = fmod(ray_x, CUBE) / CUBE;
    }
    tex_x = (int)(wall_x * 64); // Assuming texture width is 64

    // Draw the wall slice
    int y = start_y;
    while (y < end) {
        // Calculate texture y-coordinate
        int d = y - start_y;
        tex_y = (d * 64) / height; // Scale y to texture height (64)

        // Fetch the character at the texture coordinate
        char tex_char = wall->wall[tex_y][tex_x];

        // Map the character to a color (e.g., '+' is white, 'o' is gray, '.' is black)
        int color;
        // if (tex_char == '+') color = 0xFFFFFF; // White
        // else if (tex_char == 'o') color = 0x808080; // Gray
        // else if (tex_char == '.') color = 0x000000; // Black
        // else color = 0xFF00FF; // Magenta (unknown character)
		color = 0xFF00FF;
		int k = 0;
		while (wall->pixels[k])
		{
			if (tex_char == wall->pixels[k][0])
			{
				color = ft_atoi_base(ft_strchr_g(wall->pixels[k], '#'), "0123456789ABCDEF");
				break ;
			}
			k++;
		}
        // Draw the pixel
        my_mlx_pixel_put(data, i, y, color);
        y++;
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