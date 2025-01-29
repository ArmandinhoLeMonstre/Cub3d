/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:39:03 by armitite          #+#    #+#             */
/*   Updated: 2025/01/29 18:44:24 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	wall_size(t_game *game, t_draw *draw)
{
	draw->drawstart = -draw->lineheight / 2 + HEIGHT / 2;
	if (draw->drawstart < 0)
		draw->drawstart = 0;
	draw->drawend = draw->lineheight / 2 + HEIGHT / 2;
	if (draw->drawend >= HEIGHT)
		draw->drawend = HEIGHT - 1;
	if (draw->side == 0)
		draw->wallx = game->p1.posy + draw->perpwalldist * draw->raydiry;
	else
		draw->wallx = game->p1.posx + draw->perpwalldist * draw->raydirx;
	draw->wallx -= floor((draw->wallx));
	draw->tex_x = (int)(draw->wallx * (double)64);
	if (draw->side == 0 && draw->raydirx > 0)
		draw->tex_x = 64 - draw->tex_x - 1;
	if (draw->side == 1 && draw->raydiry < 0)
		draw->tex_x = 64 - draw->tex_x - 1;
	draw->step = 1.0 * 64 / draw->lineheight;
	draw->texpos = (draw->drawstart - HEIGHT / 2
			+ draw->lineheight / 2) * draw->step;
}
