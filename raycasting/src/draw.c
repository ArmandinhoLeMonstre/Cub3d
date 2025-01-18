/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:14:07 by armitite          #+#    #+#             */
/*   Updated: 2025/01/18 07:28:37 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

t_wall	*wall_side(t_game *game, t_draw *draw)
{
	t_wall	*wall;

	if (draw->side == 1)
	{
		if (draw->stepY == -1)
			wall = &game->wall_west;
		else
			wall = &game->wall_east;
	}
	else
	{
		if (draw->stepX == -1)
			wall = &game->wall_north;
		else
			wall = &game->wall_south;
	}
	return (wall);
}

int	get_color(t_game *game, t_draw *draw, int color)
{
	int		texY;
	int		k;
	t_wall	*wall;

	texY = (int)draw->texPos & (64 - 1);
	k = 0;
	draw->texPos += draw->step;
	color = 0;
	wall = wall_side(game, draw);
	while (k < wall->info)
	{
		if (wall->wall[texY][draw->texX] == wall->col[k].c)
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
		my_mlx_pixel_put(&game->img, x, y, 0xFFFFFF);
	y--;
	while (y++ <= draw->drawEnd)
	{
		color = get_color(game, draw, color);
		my_mlx_pixel_put(&game->img, x, y, color);
	}
	y--;
	while (y++ < HEIGHT)
		my_mlx_pixel_put(&game->img, x, y, 0xFF0000);
}
