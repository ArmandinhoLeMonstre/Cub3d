/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:47:09 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/20 19:37:36 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&game->img, x, y, 0);
			x++;
		}
		y++;
	}
}

int	peutetre(t_game *game)
{
	int			x;
	t_draw		draw;

	x = -1;
	clear_image(game);
	while (++x < WIDTH)
	{
		wall_dist(game, &draw, x);
		wall_size(game, &draw);
		draw_game(game, &draw, x);
	}
	printf("dsl\n");
	move_player(&game->p1);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	// draw_map(game);
	// mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 0, 0);
	return (0);
}

int	ft_exit(t_game *game)
{
	ft_freemap(game->map.map, game);
	ft_freeparse(game);
	if (game->wall_east.wall)
		ft_freewall(game->wall_east.wall);
	if (game->wall_west.wall)
		ft_freewall(game->wall_west.wall);
	if (game->wall_north.wall)
		ft_freewall(game->wall_north.wall);
	if (game->wall_south.wall)
		ft_freewall(game->wall_south.wall);
	exit(0);
}

int	mouse_move(int x, int y, t_player *player)
{
	static int	lastmousex = -1;
	int			deltax;
	double		rot_speed;
	double		old_dirx;
	double		old_planex;

	(void)y;
	if (lastmousex == -1)
	{
		lastmousex = x;
		return (0);
	}
	deltax = 0;
	if (x > lastmousex)
		deltax = 1;
	else
		deltax = -1;
	lastmousex = x;
	rot_speed = 0.01 * deltax;
	old_dirx = player->dirx;
	player->dirx = player->dirx * cos(-rot_speed) - player->diry * sin(-rot_speed);
	player->diry = old_dirx * sin(-rot_speed) + player->diry * cos(-rot_speed);
	old_planex = player->planex;
	player->planex = player->planex * cos(-rot_speed) - player->planey * sin(-rot_speed);
	player->planey = old_planex * sin(-rot_speed) + player->planey * cos(-rot_speed);
	return (0);
}

void	game_loop(t_game *game)
{
	peutetre(game);
	mlx_hook(game->win, 2, 1L << 0, key_true, &game->p1);
	mlx_hook(game->win, 3, 1L << 1, key_false, &game->p1);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, &game->p1);
	mlx_hook(game->win, 17, 0, ft_exit, game);
	mlx_loop_hook(game->mlx, peutetre, game);
	mlx_loop(game->mlx);
}

int	ft_game(t_game *game)
{
	init_player(game);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3d");
	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	game->minimap.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (parse_xpm(&game->wall_north, game->sprt.north)
		|| parse_xpm(&game->wall_west, game->sprt.west)
		|| parse_xpm(&game->wall_south, game->sprt.south)
		|| parse_xpm(&game->wall_east, game->sprt.east))
		return (printf("Error\nInvalid XPM\n"), ft_exit(game));
	mlx_mouse_hide(game->mlx, game->win);
	game_loop(game);
	return (0);
}
