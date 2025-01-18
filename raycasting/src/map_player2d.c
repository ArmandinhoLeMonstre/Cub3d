/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:39:25 by armitite          #+#    #+#             */
/*   Updated: 2025/01/18 20:06:12 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

int	draw_player(int x, int y, int size, t_game *game, int color)
{
	int	i;

	i = 0;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return (0);
	while (i < size)
	{
		my_mlx_pixel_put(&game->minimap, x + i, y, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(&game->minimap, x, y + i, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(&game->minimap, x + i, y + size, color);
		i++;
	}
	i = 0;
	while (i < size)
	{
		my_mlx_pixel_put(&game->minimap, x + size, y + i, color);
		i++;
	}
	return (0);
}

void	draw_map(t_game *game)
{
	char	**map;
	int		y;
	int		x;

	map = game->map.map;
	y = -1;
	while (++y < game->map.lin * 5)
	{
		x = -1;
		while (++x < game->map.col * 5)
		{
			if (x == (int) game->p1.posx && y == (int) game->p1.posy)
				draw_player(x * 5, y * 5, 5, game, 0xFFFFFF);
			else
				my_mlx_pixel_put(&game->minimap, x, y, 0x000000);
		}
	}
	y = -1;
	while (++y < game->map.lin)
	{
		x = -1;
		while (++x < game->map.col)
		{
			if (map[y][x] == '1')
				draw_player(x * 5, y * 5, 5, game, 0x00FF00);
		}
	}
}
