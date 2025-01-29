/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:47:09 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/29 18:40:47 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			my_mlx_pixel_put(&game->img, x, y, 0);
	}
	y = -1;
	while (++y < game->map.lin * 5)
	{
		x = -1;
		while (++x < game->map.col * 5)
			my_mlx_pixel_put(&game->minimap, x, y, 0);
	}
}

int	raycast(t_game *game)
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
	move_player(&game->p1);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 0, 0);
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

void	game_loop(t_game *game)
{
	raycast(game);
	mlx_hook(game->win, 2, 1L << 0, key_true, &game->p1);
	mlx_hook(game->win, 3, 1L << 1, key_false, &game->p1);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, &game->p1);
	mlx_hook(game->win, 17, 0, ft_exit, game);
	mlx_loop_hook(game->mlx, raycast, game);
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
	game->minimap.img = mlx_new_image(game->mlx, game->map.col * 10,
			game->map.lin * 10);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img,
			&game->minimap.bits_per_pixel,
			&game->minimap.line_length, &game->minimap.endian);
	if (parse_xpm(&game->wall_north, game->sprt.north)
		|| parse_xpm(&game->wall_west, game->sprt.west)
		|| parse_xpm(&game->wall_south, game->sprt.south)
		|| parse_xpm(&game->wall_east, game->sprt.east))
		return (printf("Error\nInvalid XPM\n"), ft_exit(game));
	mlx_mouse_hide(game->mlx, game->win);
	game_loop(game);
	return (0);
}
