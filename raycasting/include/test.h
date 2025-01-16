/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:48:29 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/15 21:49:52 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_linux/mlx.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 640
#define HEIGHT 400

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	posx;
	double	posy;  //x and y start position
	double	dirx;
	double	diry; //initial direction vector
	double	planex;
	double	planey; //the 2d raycaster version of camera plane
}	t_player;

typedef struct s_map
{
	char	**map;
} t_map;

typedef struct s_game
{
	t_player	p1;
	t_map		map;
	t_img		img;
	void		*mlx;
	void		*win;
}	t_game;
