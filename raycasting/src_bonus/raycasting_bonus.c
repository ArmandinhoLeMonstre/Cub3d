/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:23:06 by armitite          #+#    #+#             */
/*   Updated: 2025/01/29 18:43:43 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	calcul_ray(t_game *game, t_draw *draw, int x)
{
	draw->camerax = 2 * x / (double)WIDTH - 1;
	draw->raydirx = game->p1.dirx + game->p1.planex * draw->camerax;
	draw->raydiry = game->p1.diry + game->p1.planey * draw->camerax;
	draw->mapx = (int) game->p1.posx;
	draw->mapy = (int) game->p1.posy;
	draw->deltadistx = fabs(1 / draw->raydirx);
	draw->deltadisty = fabs(1 / draw->raydiry);
}

void	init_ray(t_game *game, t_draw *draw, int x)
{
	calcul_ray(game, draw, x);
	if (draw->raydirx < 0)
	{
		draw->stepx = -1;
		draw->sidedistx = (game->p1.posx - draw->mapx) * draw->deltadistx;
	}
	else
	{
		draw->stepx = 1;
		draw->sidedistx = (draw->mapx + 1.0
				- game->p1.posx) * draw->deltadistx;
	}
	if (draw->raydiry < 0)
	{
		draw->stepy = -1;
		draw->sidedisty = (game->p1.posy - draw->mapy) * draw->deltadisty;
	}
	else
	{
		draw->stepy = 1;
		draw->sidedisty = (draw->mapy + 1.0
				- game->p1.posy) * draw->deltadisty;
	}
}

void	wall_hit(t_game *game, t_draw *draw)
{
	if (draw->sidedistx < draw->sidedisty)
	{
		draw->sidedistx += draw->deltadistx;
		draw->mapx += draw->stepx;
		draw->side = 0;
	}
	else
	{
		draw->sidedisty += draw->deltadisty;
		draw->mapy += draw->stepy;
		draw->side = 1;
	}
	if (draw->mapx < 0)
		draw->mapx = 0;
	if (game->map.map[draw->mapy][draw->mapx] == '1')
		draw->hit = 1;
}

void	wall_dist(t_game *game, t_draw *draw, int x)
{
	init_ray(game, draw, x);
	draw->hit = 0;
	while (!draw->hit)
		wall_hit(game, draw);
	if (draw->side == 0)
		draw->perpwalldist = (draw->sidedistx - draw->deltadistx);
	else
		draw->perpwalldist = (draw->sidedisty - draw->deltadisty);
	draw->lineheight = (int)(HEIGHT / draw->perpwalldist);
}
