/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:55:54 by armitite          #+#    #+#             */
/*   Updated: 2025/01/20 19:25:02 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

void	rotate_right(t_player *player, double rot_speed)
{
	double	oldDirX;
	double	oldPlaneX;

	if (player->right_r)
	{
		oldDirX = player->dirx;
		player->dirx = player->dirx * cos(rot_speed)
			- player->diry * sin(rot_speed);
		player->diry = oldDirX * sin(rot_speed)
			+ player->diry * cos(rot_speed);
		oldPlaneX = player->planex;
		player->planex = player->planex * cos(rot_speed)
			- player->planey * sin(rot_speed);
		player->planey = oldPlaneX * sin(rot_speed)
			+ player->planey * cos(rot_speed);
	}
}

void	rotate_left(t_player *player, double rot_speed)
{
	double	oldDirX;
	double	oldPlaneX;

	if (player->left_r)
	{
		oldDirX = player->dirx;
		player->dirx = player->dirx * cos(-rot_speed)
			- player->diry * sin(-rot_speed);
		player->diry = oldDirX * sin(-rot_speed)
			+ player->diry * cos(-rot_speed);
		oldPlaneX = player->planex;
		player->planex = player->planex * cos(-rot_speed)
			- player->planey * sin(-rot_speed);
		player->planey = oldPlaneX * sin(-rot_speed)
			+ player->planey * cos(-rot_speed);
	}
}

void	ws(t_player *player, double move_speed)
{
	if (player->p_up)
	{
		if (player->game->map.map[(int)player->posy][(int)(player->posx
			+ player->dirx * move_speed)] != '1')
			player->posx += player->dirx * move_speed;
		if (player->game->map.map[(int)(player->posy
				+ player->diry * move_speed)][(int)player->posx] != '1')
			player->posy += player->diry * move_speed;
	}
	if (player->p_dw)
	{
		if (player->game->map.map[(int)player->posy][(int)(player->posx
			- player->dirx * move_speed)] != '1')
			player->posx -= player->dirx * move_speed;
		if (player->game->map.map[(int)(player->posy
				- player->diry * move_speed)][(int)player->posx] != '1')
			player->posy -= player->diry * move_speed;
	}
}

void	ad(t_player *player, double move_speed)
{
	if (player->p_lf)
	{
		if (player->game->map.map[(int)player->posy][(int)((player->posx - 0.1)
			+ player->diry * move_speed)] != '1')
			player->posx += player->diry * move_speed;
		if (player->game->map.map[(int)(player->posy
				- player->dirx * move_speed)][(int)(player->posx - 0.1)] != '1')
			player->posy -= player->dirx * move_speed;
	}
	if (player->p_rg)
	{
		if (player->game->map.map[(int)player->posy][(int)((player->posx + 0.1)
			- player->diry * move_speed)] != '1')
			player->posx -= player->diry * move_speed;
		if (player->game->map.map[(int)(player->posy
				+ player->dirx * move_speed)][(int)(player->posx + 0.1)] != '1')
			player->posy += player->dirx * move_speed;
	}
}

int	move_player(t_player *player)
{
	double	rot_speed;
	double	move_speed;

	move_speed = 0.111;
	rot_speed = 0.1;
	if (player->p_up || player->p_dw)
		ws(player, move_speed);
	if (player->p_lf || player->p_rg)
		ad(player, move_speed);
	if (player->right_r)
		rotate_right(player, rot_speed);
	if (player->left_r)
		rotate_left(player, rot_speed);
	return (0);
}