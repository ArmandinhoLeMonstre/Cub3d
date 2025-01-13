/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armitite <armitite@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:48:07 by armitite          #+#    #+#             */
/*   Updated: 2025/01/13 23:54:15 by armitite         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 17);
    map[0] = "11111111111111111111111111111";
    map[1] = "10000000000000000000000000001";
    map[2] = "10000000000000000000000000001";
    map[3] = "10000010000000000000000000001";
    map[4] = "10000000000000000000000000001";
    map[5] = "10000001000000000000000000001";
    map[6] = "10000100000000000000000000001";
    map[7] = "10000000000000000000000000001";
    map[8] = "10000000000000000000000000001";
	map[9] = "10000000000000000000000000001";
	map[10] = "10000000000000000000000000001";
	map[11] = "10000000000000000000000000001";
	map[12] = "10000000000000000000000000001";
	map[13] = "10000000000000000000000000001";
	map[14] = "10000000000000000000000000001";
    map[15] = "11111111111111111111111111111";
    map[16] = NULL;
    return (map);
}

void	test(t_data *data, t_player *player)
{
	mlx_hook(data->mlx_win, 2, 1L<<0, key_true, player);
	mlx_hook(data->mlx_win, 3, 1L<<1, key_false, player);
	mlx_loop_hook(data->mlx, draw_loop, data);
	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_player	player;
	t_wall wall;
	
	(void)ac;
	init_player(&player);
	data.player = &player;
	data.relative_path = "raycasting/src/test.xpm";
	parse_xpm(&wall, av);
	data.wall = &wall;
	data.map = get_map();
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Hello world!");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length,
								&data.endian);
	data.test = mlx_xpm_file_to_image(data.mlx, data.relative_path, &data.img_width, &data.img_height);
	//mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	test(&data, &player);
	// mlx_hook(data.mlx_win, 2, 1L<<0, key_true, &player);
	// mlx_hook(data.mlx_win, 3, 1L<<1, key_false, &player);
	// mlx_loop_hook(data.mlx, draw_loop, &data);
	// mlx_loop(data.mlx);
	return (0);
}

