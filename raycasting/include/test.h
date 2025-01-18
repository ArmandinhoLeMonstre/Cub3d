/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:48:29 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/18 06:47:48 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_linux/mlx.h"
#include "../libft/include/libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 1280
#define HEIGHT 720

typedef struct s_sprites
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	int		*floor;
	int		*ceiling;
}	t_sprites;

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
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	double	wallX;
	int		texX;
	double	step;
	double	texPos;
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
	char			orientation;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		bool_id;
	int		s_line;
	int		lin;
	int		col;
}	t_map;

typedef struct s_game
{
	t_player	p1;
	t_map		map;
	t_img		img;
	t_sprites	sprt;
	t_wall		wall_north;
	t_wall		wall_west;
	t_wall		wall_south;
	t_wall		wall_east;
	char		*file;
	void		*mlx;
	void		*win;
}	t_game;

int		ft_game(t_game *game);
int		parse_xpm(t_wall *wall, char *file);
int		ft_atoi_base(char *str, char *base);
// Player
void 	init_player(t_game *game);

// Raycasting
void	wall_dist(t_game *game, t_draw *draw, int x);
void	wall_size(t_game *game, t_draw *draw);

// Draw utils
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_game(t_game *game, t_draw *draw, int x);

//Movements
int		move_player(t_player *player);

// Keys
int		key_true(int keycode, t_player *player);
int		key_false(int keycode, t_player *player);

//exit
void	ft_error(char *str);
void	ft_freeparse(t_game *game);
void	ft_freemap(char **map, t_game *game);
void	ft_free(char **rep);

//utils
int		ft_open(char *file);

//parsing utils
void	ft_init_pars(t_game *game);
long	ft_atorgb(char *str);
int		ft_checkeof(char *str, int fd);

//parsing map
int		ft_create_map(int fd, t_game *game);
int		ft_findo(char **map, t_game *game);
int		ft_backtrack(int x, int y, t_game *game, char **plan);
void	ft_mapinfo(int fd, t_game *game, char *str);
void	ft_checkrgb(char *str, int len);
int		ft_findpalyer(char **map, t_game *game);

//parsing
void	parsing(char *file, t_game *game);