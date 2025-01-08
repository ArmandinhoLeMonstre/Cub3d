/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:56:45 by armitite          #+#    #+#             */
/*   Updated: 2025/01/07 16:00:23 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3,14159265359


typedef struct	s_player
{
	float	x;
	float	y;
	int	p_up;
	int	p_dw;
	int	p_lf;
	int	p_rg;
}				t_player;

typedef struct	s_data 
{
	t_player	*player;
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	init_player(t_player *player);

//Key hook
int	key_false(int keycode, t_player *player);
int	key_true(int keycode, t_player *player);
void	move_player(t_player *player);