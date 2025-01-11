/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 14:39:25 by armitite          #+#    #+#             */
/*   Updated: 2025/01/11 14:39:54 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	draw_player(int x, int y, int size, t_data *data)
{
	int	i;
	int color;

	color = 0x00FF00;
	i = 0;
	if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
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
			// if (map[y][x] == '1')
			// 	draw_player(x * CUBE, y * CUBE, CUBE, data);
			x++;
		}
		y++;
	}
	
}