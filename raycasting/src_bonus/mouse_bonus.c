/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:57:53 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/29 18:13:17 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	set_side(int *x, int *deltax, int *lastmousex)
{
	*deltax = 0;
	if (*lastmousex == -1)
	{
		*lastmousex = *x;
		return ;
	}
	if (*x == *lastmousex)
		*deltax = 0;
	else if (*x < *lastmousex)
		*deltax = 1;
	else
		*deltax = -1;
	*lastmousex = *x;
}

int	mouse_move(int x, int y, t_player *player)
{
	static int	lastmousex = -1;
	int			deltax;
	double		rot_speed;
	double		old_dirx;
	double		old_planex;

	(void)y;
	set_side(&x, &deltax, &lastmousex);
	rot_speed = 0.05 * deltax;
	old_dirx = player->dirx;
	player->dirx = player->dirx * cos(-rot_speed)
		- player->diry * sin(-rot_speed);
	player->diry = old_dirx * sin(-rot_speed)
		+ player->diry * cos(-rot_speed);
	old_planex = player->planex;
	player->planex = player->planex * cos(-rot_speed)
		- player->planey * sin(-rot_speed);
	player->planey = old_planex * sin(-rot_speed)
		+ player->planey * cos(-rot_speed);
	mlx_mouse_move(player->game->mlx, player->game->win, WIDTH / 2, HEIGHT / 2);
	lastmousex = WIDTH / 2;
	return (0);
}
