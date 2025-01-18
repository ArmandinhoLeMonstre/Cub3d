/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:23:06 by armitite          #+#    #+#             */
/*   Updated: 2025/01/18 14:41:53 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

void	calcul_ray(t_game *game, t_draw *draw, int x)
{
	draw->cameraX = 2 * x / (double)WIDTH - 1;
	draw->rayDirX = game->p1.dirx + game->p1.planex * draw->cameraX;
	draw->rayDirY = game->p1.diry + game->p1.planey * draw->cameraX;
	draw->mapX = (int) game->p1.posx;
	draw->mapY = (int) game->p1.posy;
	draw->deltaDistX = fabs(1 / draw->rayDirX);
	draw->deltaDistY = fabs(1 / draw->rayDirY);
}

void	init_ray(t_game *game, t_draw *draw, int x)
{
	calcul_ray(game, draw, x);
	if (draw->rayDirX < 0)
	{
		draw->stepX = -1;
		draw->sideDistX = (game->p1.posx - draw->mapX) * draw->deltaDistX;
	}
	else
	{
		draw->stepX = 1;
		draw->sideDistX = (draw->mapX + 1.0
				- game->p1.posx) * draw->deltaDistX;
	}
	if (draw->rayDirY < 0)
	{
		draw->stepY = -1;
		draw->sideDistY = (game->p1.posy - draw->mapY) * draw->deltaDistY;
	}
	else
	{
		draw->stepY = 1;
		draw->sideDistY = (draw->mapY + 1.0
				- game->p1.posy) * draw->deltaDistY;
	}
}

void	wall_hit(t_game *game, t_draw *draw)
{
	if (draw->sideDistX < draw->sideDistY) 
	{
		draw->sideDistX += draw->deltaDistX;
		draw->mapX += draw->stepX;
		draw->side = 0;
	}
	else
	{
		draw->sideDistY += draw->deltaDistY;
		draw->mapY += draw->stepY;
		draw->side = 1;
	}
	if (draw->mapX < 0)
		draw->mapX = 0;
	if (game->map.map[draw->mapY][draw->mapX] == '1')
		draw->hit = 1;
}

void	wall_dist(t_game *game, t_draw *draw, int x)
{
	init_ray(game, draw, x);
	draw->hit = 0;
	while (!draw->hit)
		wall_hit(game, draw);
	if (draw->side == 0)
		draw->perpWallDist = (draw->sideDistX - draw->deltaDistX);
	else
		draw->perpWallDist = (draw->sideDistY - draw->deltaDistY);
	draw->lineHeight = (int)(HEIGHT / draw->perpWallDist);
}
