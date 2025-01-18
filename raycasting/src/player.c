/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:48:10 by armitite          #+#    #+#             */
/*   Updated: 2025/01/18 17:34:26 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

void	facing2(t_game *game)
{
	if (game->p1.orientation == 'E')
	{
		game->p1.dirx = 0;
		game->p1.diry = 1;
		game->p1.planex = 0.66;
		game->p1.planey = 0;
	}
	if (game->p1.orientation == 'W')
	{
		game->p1.dirx = 0;
		game->p1.diry = -1;
		game->p1.planex = -0.66;
		game->p1.planey = 0;
	}
}

void	facing(t_game *game)
{
	if (game->p1.orientation == 'N')
	{
		game->p1.dirx = -1;
		game->p1.diry = 0;
		game->p1.planex = 0;
		game->p1.planey = 0.66;
	}
	if (game->p1.orientation == 'S')
	{
		game->p1.dirx = 1;
		game->p1.diry = 0;
		game->p1.planex = 0;
		game->p1.planey = -0.66;
	}
	else
		facing2(game);
}

void	init_player(t_game *game)
{
	facing(game);
	game->p1.game = game;
	game->p1.left_r = 0;
	game->p1.right_r = 0;
	game->p1.p_dw = 0;
	game->p1.p_up = 0;
	game->p1.p_lf = 0;
	game->p1.p_rg = 0;
	game->wall_east.wall = NULL;
	game->wall_west.wall = NULL;
	game->wall_north.wall = NULL;
	game->wall_south.wall = NULL;
}
