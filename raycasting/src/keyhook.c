/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 19:27:10 by armitite          #+#    #+#             */
/*   Updated: 2025/01/08 20:23:33 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_true(int keycode, t_player *player)
{
	printf("%d\n", keycode);
	if (keycode == 119)
		player->p_up = 1;
	if (keycode == 115)
		player->p_dw = 1;
	if (keycode == 97)
		player->p_lf = 1;
	if (keycode == 100)
		player->p_rg = 1;
	if(keycode == LEFT)
		player->left_r = 1;
    if(keycode == RIGHT)
		player->right_r = 1;
	return (0);
}

int	key_false(int keycode, t_player *player)
{
	if (keycode == 119)
		player->p_up = 0;
	if (keycode == 115)
		player->p_dw = 0;
	if (keycode == 97)
		player->p_lf = 0;
	if (keycode == 100)
		player->p_rg = 0;
	if(keycode == LEFT)
        player->left_r = 0;
    if(keycode == RIGHT)
		player->right_r = 0;
	return (0);
}