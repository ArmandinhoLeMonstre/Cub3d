/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:14:07 by armitite          #+#    #+#             */
/*   Updated: 2025/01/29 18:44:24 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * img->line_length + x * img->bits_per_pixel / 8;
	img->addr[index] = color & 0xFF;
	img->addr[index + 1] = (color >> 8) & 0xFF;
	img->addr[index + 2] = (color >> 16) & 0xFF;
}

t_wall	*wall_side(t_game *game, t_draw *draw)
{
	t_wall	*wall;

	if (draw->side == 1)
	{
		if (draw->stepy == -1)
			wall = &game->wall_south;
		else
			wall = &game->wall_north;
	}
	else
	{
		if (draw->stepx == -1)
			wall = &game->wall_east;
		else
			wall = &game->wall_west;
	}
	return (wall);
}

int	get_color(t_game *game, t_draw *draw, int color)
{
	int		tex_y;
	int		k;
	t_wall	*wall;

	tex_y = (int)draw->texpos & (64 - 1);
	k = 0;
	draw->texpos += draw->step;
	color = 0;
	wall = wall_side(game, draw);
	while (k < wall->info)
	{
		if (wall->wall[tex_y][draw->tex_x] == wall->col[k].c)
		{
			color = wall->col[k].id;
			break ;
		}
		k++;
	}
	return (color);
}

void	draw_game(t_game *game, t_draw *draw, int x)
{
	int	y;
	int	color;

	y = -1;
	color = 0;
	while (++y < draw->drawstart)
		my_mlx_pixel_put(&game->img, x, y, game->ceiling);
	y--;
	while (y++ <= draw->drawend)
	{
		color = get_color(game, draw, color);
		my_mlx_pixel_put(&game->img, x, y, color);
	}
	y--;
	while (y++ < HEIGHT)
		my_mlx_pixel_put(&game->img, x, y, game->floor);
}
