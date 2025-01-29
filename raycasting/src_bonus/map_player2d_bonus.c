/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player2d_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:39:25 by armitite          #+#    #+#             */
/*   Updated: 2025/01/29 18:56:40 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	draw_player(int x, int y, t_game *game, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return (0);
	while (i < 10)
	{
		j = -1;
		while (++j < 10)
			my_mlx_pixel_put(&game->minimap, x + i, y + j, color);
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
	while (++y < game->map.lin * 10)
	{
		x = -1;
		while (++x < game->map.col * 10)
			my_mlx_pixel_put(&game->minimap, x, y, 0x000000);
	}
	y = -1;
	while (++y < game->map.lin)
	{
		x = -1;
		while (++x < game->map.col)
		{
			if (map[y][x] == '1')
				draw_player(x * 10, y * 10, game, 0x00FF00);
			if (x == (int) game->p1.posx && y == (int) game->p1.posy)
				draw_player(x * 10, y * 10, game, 0xFFFF00);
		}
	}
}
