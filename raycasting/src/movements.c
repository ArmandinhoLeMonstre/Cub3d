/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:55:54 by armitite          #+#    #+#             */
/*   Updated: 2025/01/17 18:00:41 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

void	rotate(t_player *player, double	rot_speed)
{
	if (player->right_r)
	{ // Rotate right
   		 double oldDirX = player->dirx;
		player->dirx = player->dirx * cos(-rot_speed) - player->diry * sin(-rot_speed);
		player->diry = oldDirX * sin(-rot_speed) + player->diry * cos(-rot_speed);
		double oldPlaneX = player->planex;
		player->planex = player->planex * cos(-rot_speed) - player->planey * sin(-rot_speed);
		player->planey = oldPlaneX * sin(-rot_speed) + player->planey * cos(-rot_speed);
	}
	if (player->left_r)
	{ // Rotate right
   		 double oldDirX = player->dirx;
		player->dirx = player->dirx * cos(rot_speed) - player->diry * sin(rot_speed);
		player->diry = oldDirX * sin(rot_speed) + player->diry * cos(rot_speed);
		double oldPlaneX = player->planex;
		player->planex = player->planex * cos(rot_speed) - player->planey * sin(rot_speed);
		player->planey = oldPlaneX * sin(rot_speed) + player->planey * cos(rot_speed);
	}
}

void	wasd(t_player *player, double move_speed)
{
	if (player->p_up)
	{ 
		if (player->game->map.map[(int)(player->posx + player->dirx * move_speed)][(int)player->posy] == '0')
			player->posx += player->dirx * move_speed;
		if (player->game->map.map[(int)player->posx][(int)(player->posy + player->diry * move_speed)] == '0')
			player->posy += player->diry * move_speed;
	}
	if (player->p_dw)
	{ 
		if (player->game->map.map[(int)(player->posx - player->dirx * move_speed)][(int)player->posy] == '0')
			player->posx -= player->dirx * move_speed;
		if (player->game->map.map[(int)player->posx][(int)(player->posy - player->diry * move_speed)] == '0')
			player->posy -= player->diry * move_speed;
	}
	if (player->p_lf) // A key
	{ 
		if (player->game->map.map[(int)(player->posx - player->diry * move_speed)][(int)player->posy] == '0')
			player->posx -= player->diry * move_speed;
		if (player->game->map.map[(int)player->posx][(int)(player->posy + player->dirx * move_speed)] == '0')
			player->posy += player->dirx * move_speed;
	}
	if (player->p_rg) // D key
	{ 
		if (player->game->map.map[(int)(player->posx + player->diry * move_speed)][(int)player->posy] == '0')
			player->posx += player->diry * move_speed;
		if (player->game->map.map[(int)player->posx][(int)(player->posy - player->dirx * move_speed)] == '0')
			player->posy -= player->dirx * move_speed;
	}
}

int	move_player(t_player *player)
{
	double	rot_speed;
	double	move_speed;

	move_speed = 0.02;
	rot_speed = 0.02;
	wasd(player, move_speed);
	rotate(player, rot_speed);
	return (0);
}