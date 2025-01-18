/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:01:27 by armitite          #+#    #+#             */
/*   Updated: 2025/01/18 16:49:16 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

int	key_true(int keycode, t_player *player)
{
	if (keycode == 65307) //pour esc, pas oublier de free
		ft_exit(player->game);
	if (keycode == 119)
		player->p_up = 1;
	if (keycode == 115)
		player->p_dw = 1;
	if (keycode == 97)
		player->p_lf = 1;
	if (keycode == 100)
		player->p_rg = 1;
	if (keycode == 65361)
		player->left_r = 1;
    if (keycode == 65363)
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
	if (keycode == 65361)
        player->left_r = 0;
    if (keycode == 65363)
		player->right_r = 0;
	return (0);
}
