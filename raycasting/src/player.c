/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:27:13 by armitite          #+#    #+#             */
/*   Updated: 2025/01/09 16:11:50 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_player *player)
{
	player->x = (WIDTH / 2);
	player->y = (HEIGHT / 2);
	player->angle = PI / 2;

	player->p_up = 0;
	player->p_dw = 0;
	player->p_lf = 0;
	player->p_rg = 0;
    player->left_r = 0;
    player->right_r = 0;
}

void	move_player(t_player *player)
{
	int	movement;
	float angle_speed;
	float cos_player;
	float sin_player;

	movement = 2;
	angle_speed = 0.02;
	cos_player = cos(player->angle);
	sin_player = sin(player->angle);
	if(player->left_r == 1)
		player->angle -= angle_speed;
	if(player->right_r == 1)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if(player->p_up == 1)
	{
		player->x += cos_player * movement;
        player->y += sin_player * movement;	
	}
	if(player->p_dw == 1)
	{
		player->x -= cos_player * movement;
        player->y -= sin_player * movement;
	}
	if(player->p_lf == 1)
	{
		player->x += sin_player * movement;
        player->y -= cos_player * movement;
	}
	if(player->p_rg == 1)
	{
		player->x -= sin_player * movement;
        player->y += cos_player * movement;
	}
}