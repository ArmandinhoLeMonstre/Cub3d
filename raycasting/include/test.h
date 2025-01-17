/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:48:29 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/17 18:02:12 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_linux/mlx.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 1280
#define HEIGHT 720

typedef struct s_col
{
	char	c;
	int		id;
}	t_col;

typedef struct s_wall
{
	int		info;
	int		x;
	int		y;
	t_col	*col;
	char	**wall;
}				t_wall;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_draw
{
	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	int stepX;
	int stepY;
	int hit;
	int side;
	double perpWallDist;
	int lineHeight;
	int drawStart;
	int drawEnd;
	double wallX;
	int texX;
	double step;
	double texPos;
}	t_draw;

typedef struct s_player
{
	double			posx;
	double			posy; //x and y start position
	double			dirx;
	double			diry; //initial direction vector
	double			planex;
	double			planey; //the 2d raycaster version of camera plane
	int				p_up;
	int				p_dw;
	int				p_lf;
	int				p_rg;
	int				left_r;
	int				right_r;
	struct s_game	*game;
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
	t_wall		wall_north;
	t_wall		wall_west;
	t_wall		wall_south;
	t_wall		wall_east;
	void		*mlx;
	void		*win;
}	t_game;


int	parse_xpm(t_wall *wall, char *file);
int	ft_atoi_base(char *str, char *base);
// Player
void init_player(t_game *game);

// Raycasting
void	wall_dist(t_game *game, t_draw *draw, int x);
void	wall_size(t_game *game, t_draw *draw);

// Draw utils
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_game(t_game *game, t_draw *draw, int x);

//Movements
int	move_player(t_player *player);

// Keys
int	key_true(int keycode, t_player *player);
int	key_false(int keycode, t_player *player);