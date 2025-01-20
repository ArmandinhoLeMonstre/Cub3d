/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:14:07 by armitite          #+#    #+#             */
/*   Updated: 2025/01/20 18:02:27 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

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
		if (draw->stepY == -1)
			wall = &game->wall_south;
		else
			wall = &game->wall_north;
	}
	else
	{
		if (draw->stepX == -1)
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

	tex_y = (int)draw->texPos & (64 - 1);
	k = 0;
	draw->texPos += draw->step;
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
	while (++y < draw->drawStart)
		// if (!(y > HEIGHT || x > WIDTH || x < 0 || y < 0))
		my_mlx_pixel_put(&game->img, x, y, game->ceiling);
	y--;
	while (y++ <= draw->drawEnd)
	{
		color = get_color(game, draw, color);
		// if (!(y > HEIGHT || x > WIDTH || x < 0 || y < 0))
		my_mlx_pixel_put(&game->img, x, y, color);
	}
	y--;
	while (y++ < HEIGHT)
		//if (!(y > HEIGHT || x > WIDTH || x < 0 || y < 0))
		my_mlx_pixel_put(&game->img, x, y, game->floor);
}
