/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:39:03 by armitite          #+#    #+#             */
/*   Updated: 2025/01/18 14:43:43 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

void	wall_size(t_game *game, t_draw *draw)
{
	draw->drawStart = -draw->lineHeight / 2 + HEIGHT / 2;
	if (draw->drawStart < 0)
		draw->drawStart = 0;
	draw->drawEnd = draw->lineHeight / 2 + HEIGHT / 2;
	if (draw->drawEnd >= HEIGHT)
		draw->drawEnd = HEIGHT - 1;
	if (draw->side == 0)
		draw->wallX = game->p1.posy + draw->perpWallDist * draw->rayDirY;
	else
		draw->wallX = game->p1.posx + draw->perpWallDist * draw->rayDirX;
	draw->wallX -= floor((draw->wallX));
	draw->tex_x = (int)(draw->wallX * (double)64);
	if (draw->side == 0 && draw->rayDirX > 0)
		draw->tex_x = 64 - draw->tex_x - 1;
	if (draw->side == 1 && draw->rayDirY < 0)
		draw->tex_x = 64 - draw->tex_x - 1;
	draw->step = 1.0 * 64 / draw->lineHeight;
	draw->texPos = (draw->drawStart - HEIGHT / 2
			+ draw->lineHeight / 2) * draw->step;
}
