/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:48:10 by armitite          #+#    #+#             */
/*   Updated: 2025/01/17 18:57:48 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

void	facing2(t_game *game, int code)
{
	if (code == 2)
	{
		// Face East
		game->p1.dirx = 0;
		game->p1.diry = 1;
		game->p1.planex = 0.66;
		game->p1.planey = 0;
	}
	if (code == 3)
	{
		// Face west
		game->p1.dirx = 0;
		game->p1.diry = -1;
		game->p1.planex = -0.66;
		game->p1.planey = 0;
	}
}

void	facing(t_game *game, int code)
{
	if (code == 0)
	{
		// Face north
		game->p1.dirx = -1;
		game->p1.diry = 0;
		game->p1.planex = 0;
		game->p1.planey = 0.66;
	}
	if (code == 1)
	{
		// Face South
		game->p1.dirx = 1;
		game->p1.diry = 0;
		game->p1.planex = 0;
		game->p1.planey = -0.66;
	}
	else
	facing2(game, code);
}

void init_player(t_game *game)
{
	game->p1.posx = 12;
	game->p1.posy = 13;
	facing(game, 0);
	game->p1.game = game;
	game->p1.left_r = 0;
	game->p1.right_r = 0;
	game->p1.p_dw = 0;
	game->p1.p_up = 0;
	game->p1.p_lf = 0;
	game->p1.p_rg = 0;
}