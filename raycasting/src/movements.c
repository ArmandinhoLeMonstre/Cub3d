/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:55:54 by armitite          #+#    #+#             */
/*   Updated: 2025/01/18 06:36:22 by rafnasci         ###   ########.fr       */
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
	// printf("%s\n", player->game->map.map[0]);
	if (player->p_up)
	{ 
		printf("c : %c\n", player->game->map.map[(int)player->posy][(int)(player->posx + player->dirx * move_speed)]);
		printf("c : %c\n", player->game->map.map[(int)player->posy][(int)(player->posx + player->dirx * move_speed)]);
		if (player->game->map.map[(int)player->posy][(int)(player->posx + player->dirx * move_speed)] != '1')
			player->posx += player->dirx * move_speed;
		if (player->game->map.map[(int)(player->posy + player->diry * move_speed)][(int)player->posx] != '1')
			player->posy += player->diry * move_speed;
	}
	if (player->p_dw)
	{ 
		printf("c3 : %c\n", player->game->map.map[(int)player->posy][(int)(player->posx - player->dirx * move_speed)]);
		printf("c 3: %c\n", player->game->map.map[(int)(player->posy - player->diry * move_speed)][(int)player->posx]);
		if (player->game->map.map[(int)player->posy][(int)(player->posx - player->dirx * move_speed)] != '1')
			player->posx -= player->dirx * move_speed;
		if (player->game->map.map[(int)(player->posy - player->diry * move_speed)][(int)player->posx] != '1')
			player->posy -= player->diry * move_speed;
	}
	if (player->p_lf) // A key
	{ 
		printf("c 2: %c\n", player->game->map.map[(int)player->posy][(int)(player->posx - player->diry * move_speed)]);
		printf("c2 : %c\n", player->game->map.map[(int)(player->posy + player->dirx * move_speed)][(int)player->posx]);
		if (player->game->map.map[(int)player->posy][(int)(player->posx - player->diry * move_speed)] != '1')
			player->posx -= player->diry * move_speed;
		if (player->game->map.map[(int)(player->posy + player->dirx * move_speed)][(int)player->posx] != '1')
			player->posy += player->dirx * move_speed;
	}
	if (player->p_rg) // D key
	{ 
		printf("c1 : %c\n", player->game->map.map[(int)player->posy][(int)(player->posx + player->diry * move_speed)]);
		printf("c 1: %c\n", player->game->map.map[(int)(player->posy - player->dirx * move_speed)][(int)player->posx]);
		if (player->game->map.map[(int)player->posy][(int)(player->posx + player->diry * move_speed)] != '1')
			player->posx += player->diry * move_speed;
		if (player->game->map.map[(int)(player->posy - player->dirx * move_speed)][(int)player->posx] != '1')
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